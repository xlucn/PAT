#! /usr/bin/env python3
import argparse
import configparser
import copy
import logging
import os
import pickle
import re
import time

import html2text
from bs4 import BeautifulSoup
from selenium.webdriver import Firefox
from selenium.webdriver.firefox.options import Options


def process_katex(soup):
    """
    replace all the 'katex' class spans with simple latex string
    """
    katex_spans = soup.find_all("span", class_="katex")
    for katex_span in katex_spans:
        katex_span.mrow.decompose()
        mathstr = katex_span.find("math")
        mathjax_string = " ${}$ ".format(mathstr.string)
        katex_span.replace_with(mathjax_string)
    return soup


def extract_sample_IO(soup):
    """
    Extract the "sample input" and "sample output" in the problem text and
    replace them with placeholders.
    """
    sample_input = soup.find_all("code", class_="language-in")
    samplt_input_text = [i.string for i in sample_input]

    sample_output = soup.find_all("code", class_="language-out")
    samplt_output_text = [i.string for i in sample_output]

    return samplt_input_text, samplt_output_text


class PATDownloader(Firefox):
    """
    Automate browser to visit pintia.cn and download problem texts. The reason
    for the tool is the content on the website is dynamically generated, so
    simply get the webpage with requests is not working.
    """
    def __init__(self, force):
        self._force = force
        self.base_url = "https://pintia.cn"
        self.problem_sets_url = self.base_url + "/problem-sets"
        self.options = Options()
        self.options.headless = True
        self.options.add_argument("--safe-mode")

        super().__init__(options=self.options, service_log_path=os.devnull)
        self.implicitly_wait(10)

        self.get(self.base_url)
        for cookie in self.get_cookies():
            self.add_cookie(cookie)

    def get_default_profile(self):
        parser = configparser.ConfigParser()
        parser.read(os.path.join(os.getenv("HOME"), ".mozilla", "firefox", "profiles.ini"))
        profile = parser.get(parser.sections()[0], "Default")
        return os.path.join(os.getenv("HOME"), ".mozilla", "firefox", profile)

    def get_cookies(self):
        if os.path.exists("cookies.pkl"):
            return pickle.load(open("cookies.pkl", "rb"))
        opts = copy.deepcopy(self.options)
        opts.profile = self.get_default_profile()
        driver = Firefox(options=opts, service_log_path=os.devnull)
        driver.get(self.base_url)
        driver.get_cookies()
        cookies = driver.get_cookies()
        pickle.dump(cookies, open("cookies.pkl", "wb"))
        return cookies

    def _parse_catatory(self, cat):
        problem_list = []

        logging.info("retrieving infomation for category {c}".format(c=cat))
        for page in range(cat_counts[cat] // number_per_page + 1):
            category_url = "{baseurl}/{ID}/problems/type/7?page={page}".format(
                baseurl=self.problem_sets_url,
                ID=urlidx[cat],
                page=page
            )

            logging.info('requesting page \'%s\'', category_url)
            self.get(category_url)
            table = self.find_element_by_tag_name('tbody')
            rows = table.find_elements_by_tag_name('tr')

            for row in rows:
                check, label, title, score, rate = row.find_elements_by_tag_name('td')
                link = title.find_element_by_tag_name('a')
                problem_list.append({
                    'index': label.text,
                    'title': f"{link.text} ({score.text})",
                    'link': link.get_property('href')
                })

        return problem_list

    def _parse_problem(self, url):
        logging.info('requesting page \'%s\'', url)
        self.get(url)

        # the first find is only to implicit wait until loaded
        self.find_elements_by_id('input-specification')
        pc_divs = self.find_elements_by_class_name('rendered-markdown')
        pc_div = pc_divs[1]
        soup = BeautifulSoup(pc_div.get_attribute("innerHTML"), 'html.parser')
        content_soup = process_katex(soup)
        for tag in content_soup.find_all('code'):
            if tag.parent.name == 'pre':
                tag.parent.replace_with(tag.wrap(soup.new_tag("pre")))
        content_md = html2text.html2text(str(content_soup))

        sample_in, sample_out = extract_sample_IO(content_soup)
        return content_md, sample_in, sample_out

    def download(self, indexes=None):
        """
        Download html files
        """
        script_dir = os.path.dirname(os.path.realpath(__file__))
        # The dir of sample input and output in the problem texts
        sample_dir = os.path.join(os.path.dirname(script_dir), "sample_test")
        # The dir of html file from patest.cn
        text_dir = os.path.join(os.path.dirname(script_dir), "_articles", "html")
        if not os.path.exists(text_dir):
            os.mkdir(text_dir)
        if not os.path.exists(sample_dir):
            os.mkdir(sample_dir)

        for c in indexes.keys():
            url_list = None
            for i in indexes[c]:
                textfile = "{}/{}{}.md".format(text_dir, c, i)
                si_file = "{}/{}{}-{{}}.in".format(sample_dir, c, i)
                so_file = "{}/{}{}-{{}}.out".format(sample_dir, c, i)
                if self._force is False and os.path.exists(textfile):
                    logging.info("%s exists", textfile)
                    continue

                # try to getch the list of urls of all problems
                while url_list is None:
                    url_list = self._parse_catatory(c)
                    if url_list is None:
                        logging.info("retrying")

                # find the corresponding url
                url_index = next((url for url in url_list
                                  if int(url['index']) == i),
                                 None)
                # download
                if url_index:
                    logging.info("downloading %s", textfile)
                    pc, si, so = self._parse_problem(url_index['link'])

                    logging.debug("saving %s", textfile)
                    with open(textfile, 'w') as f:
                        f.write("<!-- Title\n{}\n-->\n{}".format(
                                url_index['title'], pc))
                    # There might be more than one samples
                    for i in range(len(si)):
                        open(si_file.format(i + 1), 'w').write(si[i])
                        open(so_file.format(i + 1), 'w').write(so[i])
                    time.sleep(2)
                else:
                    logging.error("Index %s%s not available", c, i)


def get_parser():
    parser = argparse.ArgumentParser(description='''Python script to download
        problem content from PAT website. I will include the downloaded files
        in the repo, so this script does not need to be executed.''')
    parser.add_argument('ids', nargs='*',
                        metavar='<problem id>',
                        help='''the id of the problem, e.g. b1001 for the first
                        problem. use all for downloading all html files''')
    parser.add_argument('-f', '--force-download',
                        action='store_true',
                        help='force download html file even if it exists')
    return parser


cat_counts = {'a': 155, 'b': 95, 't': 27}

# the number of problems per page
number_per_page = 100

urlidx = {
    'b': "994805260223102976",
    'a': "994805342720868352",
    't': "994805148990160896"
}

# setting logging
logging.basicConfig(level=logging.INFO)

if __name__ == "__main__":
    # parse arguments
    parser = get_parser()
    args = parser.parse_args()

    # create downloader
    dl = PATDownloader(force=args.force_download)

    # download problem texts for corresponding indexes
    dlIndexes = {'a': [], 'b': [], 't': []}
    if args.ids is None or args.ids == [] or 'all' in args.ids:
        for c in cat_counts.keys():
            dlIndexes[c] = [i + 1001 for i in range(cat_counts[c])]
    else:
        for ID in args.ids:
            if not re.match(r"[abt]\d{4}", ID):
                logging.error('This id is not valid: %s', ID)
                exit(0)
            category = ID[0]
            index = int(ID[1:])
            if index > cat_counts[category] + 1000:
                logging.error('Index out of range: %s', index)
                exit(0)
            dlIndexes[category].append(index)

    # selenium will print some error about connection poll
    try:
        dl.download(dlIndexes)
    except KeyboardInterrupt:
        logging.info("exiting...")
    finally:
        dl.close()
        dl.quit()

#! /usr/bin/env python3
import os
import re
import time
import logging
import argparse

import html2text
from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.firefox.options import Options
from selenium.common.exceptions import WebDriverException

cat_counts = {'a': 155, 'b': 95, 't': 27}

# the number of problems per page
number_per_page = 100

urlidx = {
    'b': "994805260223102976",
    'a': "994805342720868352",
    't': "994805148990160896"
}

# setting logging
logging.basicConfig(
    format='[%(levelname)s] %(filename)s:%(lineno)d: %(message)s',
    level=logging.INFO)


def process_katex(soup):
    """
    replace all the 'katex' class spans with simple latex string
    """
    dollar_signs = soup.find_all(text=re.compile("\\$"))
    for dollar_sign in dollar_signs:
        escaped_dollar = dollar_sign.replace("$", "\\\\$")
        dollar_sign.replace_with(escaped_dollar)
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
    sample_input = soup.find_all("code", class_="lang-in")
    samplt_input_text = [i.string for i in sample_input]

    sample_output = soup.find_all("code", class_="lang-out")
    samplt_output_text = [i.string for i in sample_output]

    return samplt_input_text, samplt_output_text


class PATDownloader:
    """
    Automate browser to visit pintia.cn and download problem texts. The reason
    for the tool is the content on the website is dynamically generated, so
    simply get the webpage with requests is not working.
    """
    def __init__(self, force):
        self._phantom_is_setup = False
        self._force = force
        self._base_url = "https://pintia.cn"
        self._problem_sets_url = self._base_url + "/problem-sets"

        # phantom_setup
        options = Options()
        options.headless = True
        try:
            self._phantom_browser = webdriver.Firefox(
                options=options,
                service_log_path=os.devnull
            )
            logging.debug("Starting phantom firefox driver")
        except WebDriverException as e:
            print(e)
            logging.error("Starting phantom firefox driver failed")
            exit(1)

    def __del__(self):
        try:
            self._phantom_browser.quit()
        except AttributeError:
            pass

    def _phantom_parse_soup(self, url):
        self._phantom_browser.get(url)
        try:
            html = self._phantom_browser.page_source
        except WebDriverException as e:
            print(e)
            logging.warning("you just have to run the script again, "
                            "something unfortunate happened.")
            exit(1)
        # TODO: check return here
        soup = BeautifulSoup(html, 'html.parser')
        return soup

    def _parse_catatory(self, cat):
        problem_list = []

        logging.info("retrieving infomation for category {c}".format(c=cat))
        for page in range(cat_counts[cat] // number_per_page + 1):
            category_url = "{baseurl}/{ID}/problems/type/7?page={page}".format(
                baseurl=self._problem_sets_url,
                ID=urlidx[cat],
                page=page)

            logging.debug('requesting page \'%s\'', category_url)
            soup = self._phantom_parse_soup(category_url)
            table = soup.find('tbody')
            if table is None:
                logging.warning(
                    'requesting page \'%s\' failed, will retry '
                    '(table returned None)',
                    category_url
                )
                return None
            rows = table.find_all('tr')

            for row in rows:
                tdlist = row.find_all('td')
                link = tdlist[2].find('a')
                problem_list.append({
                    'index': tdlist[1].contents[0],
                    'title': "{content} ({score})".format(
                        content=link.contents[0],
                        score=tdlist[3].contents[0]),
                    'link': self._base_url + link['href']
                })

        return problem_list

    def _parse_problem(self, url):
        logging.debug('requesting page \'%s\'', url)

        soup = self._phantom_parse_soup(url)

        pc_divs = soup.find_all('div', 'rendered-markdown')
        if len(pc_divs) < 2:
            logging.error("Not enough div with class \'rendered-markdown\'" +
                          "for url: {}, got {}".format(url, len(pc_divs)))
            return None, None, None

        pc_div = pc_divs[1]
        content_soup = process_katex(pc_div)
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
        sample_dir = os.path.join(script_dir, "..", "sample_test")
        # The dir of html file from patest.cn
        text_dir = os.path.join(script_dir, "..", "_articles", "html")
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
                        time.sleep(1)

                # find the corresponding url
                url_index = next((url for url in url_list
                                  if int(url['index']) == i),
                                 None)
                # download
                if url_index:
                    logging.info("downloading %s", textfile)
                    pc = None
                    while pc is None:
                        pc, si, so = self._parse_problem(url_index['link'])
                        if pc is None:
                            logging.info("retrying")
                            time.sleep(1)

                    logging.debug("saving %s", textfile)
                    with open(textfile, 'w') as f:
                        f.write("<!-- Title\n{}\n-->\n{}".format(
                                url_index['title'], pc))
                    # There might be more than one samples
                    for i in range(len(si)):
                        with open(si_file.format(i + 1), 'w') as f:
                            f.write(si[i])
                        with open(so_file.format(i + 1), 'w') as f:
                            f.write(so[i])
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

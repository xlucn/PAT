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

import config


def process_katex(html):
    """
    replace all the 'katex' class spans with simple latex string
    """
    soup = BeautifulSoup(html, "html.parser")
    katex_spans = soup.find_all("span", class_="katex")
    for katex_span in katex_spans:
        katex_span.mrow.decompose()
        mathstr = katex_span.find("math")
        mathjax_string = soup.new_string(" ${}$ ".format(mathstr.string))
        katex_span.replace_with(mathjax_string)
    return str(soup)

class PATDownloader:
    def __init__(self, force):
        self._phantom_is_setup = False
        self._force = force
        self._base_url = "https://pintia.cn"
        self._problem_sets_url = self._base_url + "/problem-sets"

        # phantom_setup
        options = Options()
        options.headless = True
        try:
            self._phantom_browser = webdriver.Firefox(options=options)
            logging.info("Starting phantom firefox driver")
        except:
            logging.error("Starting phantom firefox driver failed")
            exit(1)

    def __del__(self):
        self._phantom_browser.quit()

    def _phantom_parse_soup(self, url):
        self._phantom_browser.get(url)
        # check return here
        html = self._phantom_browser.page_source
        soup = BeautifulSoup(html, 'html.parser')
        return soup

    def _parse_catatory(self, category):
        category_url = "{baseurl}/{ID}/problems".format(
            baseurl=self._problem_sets_url,
            ID=config.urlidx[category])
        logging.info('requesting page \'%s\'', category_url)
        soup = self._phantom_parseSoup(category_url)
        table = soup.find('tbody')
        if table is None:
            logging.warning('requesting page \'%s\' failed, will retry %s',
                            category_url, '(table returned None)')
            return None

        rows = table.find_all('tr')

        if len(rows) < len(config.indexes[category]):
            logging.warning('requesting page \'%s\' failed, will retry %s',
                            category_url, '(rows length not enough)')
            return None

        problem_list = []
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
        soup = self._phantom_parse_soup(url)
        pc_div = soup.find_all('div', 'ques-view')[1]
        content_html = process_katex(str(pc_div))
        content_md = html2text.html2text(content_html)
        return content_md

    def download(self, indexes=None):
        """
        Download html files
        """
        if not os.path.exists(config.text_dir):
            os.mkdir(config.text_dir)

        for c in indexes.keys():
            url_list = None
            for index in indexes[c]:
                textfile = "{}/{}{}.md".format(config.text_dir, c, index)
                if self._force is False and os.path.exists(textfile):
                    logging.info("%s exists", textfile)
                    continue

                # try to getch the list of urls of all problems
                while url_list is None:
                    url_list = self._parse_catatory(c)
                    if url_list is None:
                        time.sleep(5)

                # find the corresponding url
                url_index = next((url for url in url_list
                                  if int(url['index']) == index),
                                 None)
                # download
                if url_index:
                    logging.info("downloading %s", textfile)
                    pc = self._parse_problem(url_index['link'])
                    with open(textfile, 'w') as f:
                        f.write("<!-- Title\n" +                           \
                                "{}\n-->\n".format(url_index['title']) +   \
                                pc)
                else:
                    logging.error("Index %s%s not available", c, index)


if __name__ == "__main__":
    # setting logging
    logging.basicConfig(format='%(asctime)s [%(levelname)s]: %(message)s',
                        level=logging.INFO)

    # parse arguments
    parser = argparse.ArgumentParser(description='''Python script to download
        problem content from PAT website. I will include the downloaded files
        in the repo, so this script does not need to be executed.''')
    parser.add_argument('ids', nargs='+',
                        metavar='<problem id>',
                        help='''the id of the problem, e.g. 1001 for the first
                        problem. use all for downloading all html files''')
    parser.add_argument('-f', '--force-download',
                        action='store_true',
                        help='force download html file again even if it exists')
    args = parser.parse_args()

    dlIndexes = {'a': [], 'b': [], 't': []}
    if 'all' in args.ids:
        dlIndexes = config.indexes
    else:
        for ID in args.ids:
            if not re.match(r"[abt]\d{4}", ID):
                logging.error('This id is not valid: %s', ID)
                exit(0)
            category = ID[0]
            index = int(ID[1:])
            if index not in config.indexes[category]:
                logging.error('Index out of range: %s', index)
                exit(0)
            dlIndexes[category].append(index)

    dl = PATDownloader(force=args.force_download)
    dl.download(dlIndexes)

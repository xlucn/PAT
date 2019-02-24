#! /usr/bin/env python3
import os
import sys
import re
import time
from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.firefox.options import Options
import argparse
import logging
import config

import html2text

class PATDownloader:
    def __init__(self, force):
        self._phantomIsSetup = False
        self._force = force
        self._baseUrl = "https://pintia.cn"
        self._problemSetsUrl = self._baseUrl + "/problem-sets"

    def __del__(self):
        try:
            self._phantomBrowser.quit()
        except:
            pass

    def _phantomSetup(self):
        options = Options()
        options.headless = True
        try:
            self._phantomBrowser = webdriver.Firefox(options=options)
            logging.info("Starting phantom firefox driver")
        except:
            logging.error("Starting phantom firefox driver failed")
            exit(1)
        self._phantomIsSetup = True

    def _phantomParseSoup(self, url):
        if self._phantomIsSetup == False:
            self._phantomSetup()
        self._phantomBrowser.get(url)
        # check return here
        html = self._phantomBrowser.page_source
        soup = BeautifulSoup(html, 'html.parser')
        return soup

    def _parseCatatory(self, category):
        categoryUrl = "{baseurl}/{ID}/problems".format(
                          baseurl=self._problemSetsUrl,
                          ID=config.urlidx[category])
        logging.info('requesting page \'{}\''.format(categoryUrl))
        soup = self._phantomParseSoup(categoryUrl)
        table = soup.find('tbody')
        if table == None:
            logging.warning('requesting page \'{}\' failed, will retry {}'
                            .format(categoryUrl, '(table returned None)'))
            return None

        rows = table.find_all('tr')

        if len(rows) < len(config.indexes[category]):
            logging.warning('requesting page \'{}\' failed, will retry {}'
                            .format(categoryUrl, '(rows length not enough)'))
            return None

        problemList = []
        for row in rows:
            tdlist = row.find_all('td')
            link = tdlist[2].find('a')
            problemList.append({
                'index': tdlist[1].contents[0],
                'title': "{content} ({score})".format(
                            content=link.contents[0],
                            score=tdlist[3].contents[0]),
                'link': self._baseUrl + link['href']
            })

        return problemList

    def _processkatex(self, html):
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

    def _parseProblem(self, url):
        soup = self._phantomParseSoup(url)
        pc_div = soup.find_all('div', 'ques-view')[1]
        content_html = self._processkatex(str(pc_div))
        content_md = html2text.html2text(content_html)
        return content_md

    def download(self, indexes=config.indexes):
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
                    logging.info(textfile + " exists")
                    continue

                # try to getch the list of urls of all problems
                while url_list == None:
                    url_list = self._parseCatatory(c)
                    if url_list == None:
                        time.sleep(5)

                # find the corresponding url
                url_index = next((url for url in url_list
                                  if int(url['index']) == index),
                                 None)
                # download
                if url_index:
                    logging.info("downloading " + textfile)
                    pc = self._parseProblem(url_index['link'])
                    with open(textfile, 'w') as f:
                        f.write("<!-- Title\n" +                           \
                                "{}\n-->\n".format(url_index['title']) +   \
                                pc)
                else:
                    logging.error("Index {}{} not available".format(c, index))


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
                logging.error('This id is not valid: {}'.format(ID))
                exit(0)
            category = ID[0]
            index = int(ID[1:])
            if index not in config.indexes[category]:
                logging.error('Index out of range: {}'.format(index))
                exit(0)
            dlIndexes[category].append(index)

    dl = PATDownloader(force=args.force_download)
    dl.download(dlIndexes)

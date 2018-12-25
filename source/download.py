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

class PATDownloader:
    def __init__(self, force):
        self._force = force
        options = Options()
        options.headless = True
        self._phantomBrowser = webdriver.Firefox(options=options)
        self._baseUrl = "https://pintia.cn"
        self._problemSetsUrl = self._baseUrl + "/problem-sets"
        # the number in the website url
        self._ProblemID = {
                'b': "994805260223102976",
                'a': "994805342720868352",
                't': "994805148990160896"
                }

        self._doctype = '<!DOCTYPE html>'
        self._meta = '<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />'
        self._style = '''<style type=\"text/css\">
        .katex-html {display: none;}
        .katex-mathml {font-size: 0px;}
        .katex-mathml math mrow {font-size: 16px;}
        </style>'''

    def __del__(self):
        self._phantomBrowser.quit()

    def _phantomParseSoup(self, url):
        browser = self._phantomBrowser
        browser.get(url)
        # check return here
        html = browser.page_source
        soup = BeautifulSoup(html, 'html.parser')
        return soup

    def _parseCatatory(self, category):
        categoryUrl = "{baseurl}/{ID}/problems".format(baseurl=self._problemSetsUrl,
                      ID=self._ProblemID[category])
        logging.info('requesting page \'{}\''.format(categoryUrl))
        soup = self._phantomParseSoup(categoryUrl)
        table = soup.find('tbody')
        if table == None:
            logging.warning('requesting page \'{}\' failed, will retry (table returned None)'.format(categoryUrl))
            return None

        rows = table.find_all('tr')

        # request failed
        if len(rows) < len(config.indexes[category]):
            logging.warning('requesting page \'{}\' failed, will retry (rows length not enough)'.format(categoryUrl))
            return None

        problemList = []
        for row in rows:
            tdlist = row.find_all('td')
            link = tdlist[2].find('a')
            problemList.append({
                'index': tdlist[1].contents[0],
                'title': '<h1>{}</h1>'.format(link.contents[0]),
                'link': self._baseUrl + link['href']
            })

        return problemList

    def _parseProblem(self, url):
        soup = self._phantomParseSoup(url)
        pc = soup.find_all('div', 'ques-view')[1]
        return pc

    def download(self, indexes=config.indexes):
        """Download all html files

        Attributes:
            force: boolean, weather to redownload files that already exists.
        """
        if not os.path.exists(config.html_dir):
            os.mkdir(config.html_dir)
        for c in indexes.keys():
            if len(indexes[c]) == 0:
                continue

            url_list = None
            while url_list == None:
                url_list = self._parseCatatory(c)
                if url_list == None:
                    time.sleep(5)

            for url in url_list:
                if int(url['index']) not in indexes[c]:
                    continue

                htmlfile = "{}/{}{}.html".format(config.html_dir, c, url['index'])
                if self._force is True or\
                  (self._force is False and not os.path.exists(htmlfile)):
                    logging.info("downloading " + htmlfile)
                    pc = self._parseProblem(url['link'])
                    with open(htmlfile, 'w') as f:
                        f.write("{}\n{}\n{}\n{}\n{}".format(
                                self._doctype,
                                self._meta,
                                self._style,
                                url['title'],
                                pc
                            ))
                else:
                    logging.info(htmlfile + " exists")

if __name__ == "__main__":
    # parse arguments
    parser = argparse.ArgumentParser(description='''Python script to download
        problem content from PAT website. I will include the downloaded files
        in the repo, so this script does not need to be executed.''')
    parser.add_argument('ids', nargs='*',
                        metavar='<problem id>',
                        help='the id of the problem, e.g. 1001 for the first problem')
    parser.add_argument('-f', '--force-download',
                        action='store_true',
                        help='force download html file again even if it exists')
    args = parser.parse_args()

    # setting logging
    logging.basicConfig(format='%(asctime)s [%(levelname)s]: %(message)s',
                        level=logging.INFO)

    dl = PATDownloader(force=args.force_download)

    dlIndexes = {'a': [], 'b': [], 't': []}
    if len(args.ids) == 0:
        dlIndexes = config.indexes

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

    dl.download(dlIndexes)

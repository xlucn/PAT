#! /usr/bin/env python3

import requests
import os
import sys
import re
import config
from bs4 import BeautifulSoup

usage = """Usage: ./download.py [-f]/[id]. 
\nUse -f to force redownload
\n[id] is the combination of a category indicator 'a/b/t' and a 4-digit number,
e.g. a1001 for problem 1001 in PAT Advanced problem set.
\nWhen an id is provided, force download is default."""

class PATDownloader:
    baseurl = "https://www.patest.cn/contests"
    doctype = '<!DOCTYPE html>'
    meta = '<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />'
    
    def download_html(self, category, index):
        """Download html file for one problem.
        
        Parameters:
            category: one character, possible options: 'a' for advanced, 'b' for basic,
                't' for Top.
            index: four digit number starting from 1001.
        
        Return:
            html content
        """
        contest_name = 'pat-{}-practise'.format(category)
        url = "{}/{}/{}".format(self.baseurl, contest_name, index)
        resp = requests.get(url)
        return resp.content
    
    def parse_html(self, content):
        """
        parse html file and find h1 tag and div with id 'problemContent'
        
        :param content: 
            html content
        
        :return:
            h1 tag and div tag with id 'problemContent'
        """
        soup = BeautifulSoup(content, "html.parser")
        h1 = soup.find('h1')
        pc = soup.find(id='problemContent')
        return h1, pc
    
    def write_html(self, category, index, h1, pc):
        """
        write h1 tag and problem content div into a new html file
        """
        filename = os.path.join(config.html_dir, "{}{}.html".format(category, index))
        with open(filename, 'w') as f:
            f.write("{}\n{}\n{}\n{}".format(self.doctype, self.meta, h1, pc))

    def __download(self, category, index, force=False):
        content = self.download_html(category, index)
        h1, pc = self.parse_html(content)
        self.write_html(category, index, h1, pc)
    
    def download_all(self, indexes=config.indexes, force=False):
        """Download all html files
        
        Attributes:
            force: boolean, weather to redownload files that already exists.
        """
        if not os.path.exists(config.html_dir):
            os.mkdir(config.html_dir)
        for c in indexes.keys():
            for i in indexes[c]:
                html = "{}/{}{}.html".format(config.html_dir, c, i)
                if force is True or (force is False and not os.path.exists(html)):
                    print("downloading " + html)
                    self.__download(c, i)
                else:
                    print(html + " exists")

    def download(self, category, index, force=False):
        """
        download one html file
        """
        self.download_all({category: index}, force)

if __name__ == "__main__":
    dl = PATDownloader()
    if len(sys.argv) == 1:
        dl.download_all()
    if len(sys.argv) == 2:
        if sys.argv[1] == '-f':
            dl.download_all(force=True)
        elif sys.argv[1] == '-h' or sys.argv[1] == '--help':
            print(usage)
        elif re.match(r"[abt]\d{4}", sys.argv[1]):
            category = sys.argv[1][0]
            index = int(sys.argv[1][1:])
            if index in indexes[category]:
                dl.download(category, index)
        else:
            print(usage)

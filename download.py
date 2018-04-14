#! /usr/bin/env python3

import requests
import os
import sys
import re
import config
from bs4 import BeautifulSoup

usage = """Usage: python download [-f]/[id]. 

Use -f to force redownload

[id] is the combination of a category indicator 'a/b/t' and a 4-digit number,
e.g. a1001 for problem 1001 in PAT Advanced problem set.

When an id is provided, force download is by default."""

def download_html(category, index):
    """Download html file for one problem.
    
    Only reserve useful part: h1 title and div with id problemContent.
    
    Parameters:
        category: one character, possible options: 'a' for advanced, 'b' for basic,
            't' for Top.
        index: four digit number starting from 1001.
    """
    
    # build url and download
    baseurl = "https://www.patest.cn/contests"
    contest_name = 'pat-' + category + '-practise'
    url = "{}/{}/{}".format(baseurl, contest_name, index)
    resp = requests.get(url)
    
    # parse and get only the problem content part of the text
    html_content = resp.content
    soup = BeautifulSoup(html_content, "html.parser")
    h1 = soup.find('h1')
    pc = soup.find(id='problemContent')
    
    filename = "{}/{}{}.html".format(html_dir, category, index)
    with open(filename, 'w') as f:
        f.write("""<!DOCTYPE html>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
{}\n{}""".format(h1, pc))

def download(force=False):
    """Download all html files
    
    Attributes:
        force: boolean, weather to download files that already exists.
    """
    if not os.path.exists(html_dir):
        os.mkdir(html_dir)
    for c in "abt":
        for i in indexes[c]:
            html = "{}/{}{}.html".format(html_dir, c, i)
            if force is True or (force is False and not os.path.exists(html)):
                print("downloading " + html)
                download_html(c, i)
            else:
                print(html + " exists")

if __name__ == "__main__":
    if len(sys.argv) == 1:
        download()
    if len(sys.argv) == 2:
        if sys.argv[1] == '-f':
            download(force=True)
        elif sys.argv[1] == '-h' or sys.argv[1] == '--help':
            print(usage)
        elif re.match(r"[abt]\d{4}", sys.argv[1]):
            category = sys.argv[1][0]
            index = int(sys.argv[1][1:])
            if index in indexes[category]:
                download_html(category, index)
        else:
            print(usage)

#! /usr/bin/env python3

import requests, os, sys, re
from config import *

usage = """Usage: python download [-f]/[id]. 

Use -f to force redownload

[id] is the combination of a category indicator 'a/b/t' and a 4-digit number,
e.g. a1001 for problem 1001 in PAT Advanced problem set.

When an id is provided, force download is by default."""

def download_html(category, index):
    
    # build url
    baseurl = "https://www.patest.cn/contests"
    contest_name = 'pat-' + category + '-practise'
    url = "{}/{}/{}".format(baseurl, contest_name, index)
    resp = requests.get(url)
    filename = "{}/{}{}.html".format(html_dir, category, index)
    with open(filename, 'w') as f:
        f.write(resp.text)

def download(force=False):
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

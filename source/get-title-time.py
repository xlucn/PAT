#!/usr/bin/env python3
"""
This script is for adding date and time of every article originally published in
jianshu.com to markdown files. Hopefully it won't be used twice. It is just in
the repo for archive purpose.

Prerequisite:
This script need a file containing html code of the index page of:
    https://www.jianshu.com/nb/11728776
    https://www.jianshu.com/nb/12511746
with ALL the articles present.

What it does:
Put this script in source folder(see
https://github.com/OliverLew/PAT/tree/gh-pages, the path may change in the
future) with files in the subfolder 'analysis' named in the pattern of
'[a|b]xxxx.md' where xxxx is a four-digit number.
The date&time in the pattern of 'YYYY-MM-DD HH:MM:SS +/-TTTT'(required by
jekyll) will be added at the beginning of each file mentioned above. This line
will be processed by build.py and makefile to specify the date(in yaml front
matter) and filename of final markdown files in jekyll site.
"""

import re
import os
from bs4 import BeautifulSoup

html_file = 'title-time.html'
md_dir = 'analysis'

def get_time(raw_time):
    return raw_time.replace('T', ' ')\
                   .replace('+', ' +')\
                   .replace('08:00', '0800')

def get_filename(title):
    cat = re.findall(r'\bBasic\b | \bAdvanced\b', title)[0].strip()
    if cat == 'Basic':
        c = 'b'
    else:
        c = 'a'
    return  os.path.join(md_dir, c + re.findall(r'\d{4}', title)[0] + '.md')

content = open(html_file).read()
soup = BeautifulSoup(content, "html.parser")

titles = soup.findAll('a', {'class': 'title'})
times = soup.findAll('span', {'class': 'time'})

times = [get_time(t.attrs['data-shared-at']) for t in times]
files = [get_filename(t.string) for t in titles]

for i in range(len(times)):
    if os.path.exists(files[i]):
        os.system("sed -i \'1i{}\\n\' {}".format(times[i], files[i]))

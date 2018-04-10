#! /usr/bin/env python3

import os
import sys
import re
from subprocess import run, PIPE, CalledProcessError
from bs4 import BeautifulSoup
from config import indexes, code_dir, md_dir, html_dir, analysis_dir, configs, code_dirs


def build_file_(category, index):
    """
    build markdown files.
    """
    filename = "{}/{}{:04}.md".format(md_dir, category, index)
    
    # open the html file and read into lines
    html = "{}/{}{}.html".format(html_dir, category, index)
    lines = open(html).readlines()
    
    # code related
    code_rel_path = "{}/{}.c".format(code_dirs[category], index)
    remote_url = "https://github.com/OliverLew/PAT/blob/master"
    file_github_path = "{}/{}".format(remote_url, code_rel_path)
    raw_code = run(["git", "show", "master:" + code_rel_path],
                   check=True, stdout=PIPE, stderr=PIPE).stdout.decode("utf-8")
    code = raw_code[raw_code.index("#include"):]

    
    print("Building {}".format(filename))
    
    # write everything into a file
    with open(filename, 'w') as f:
        f.write("{}\n".format(lines[2]))
        
        # write problem content
        f.write("## 题目\n\n")
        for line in lines[3:]:
            if configs["quote_text"] is True:
                f.write("> ")
            f.write(line)
        
        # write explanation
        expl = open("{}/{}{}.md".format(analysis_dir, category, index)).read()
        f.write("\n\n## 思路\n\n")
        f.write(expl)
        
        # write code
        f.write("\n## 代码\n\n")
        f.write("[最新代码@github](" + file_github_path + ")，欢迎交流\n")
        f.write("```c\n{}\n```".format(code))


def build_file(c, i):
    try:
        build_file_(c, i)
    except (FileNotFoundError, CalledProcessError) as e:
        pass

usage = """to be continued."""

if __name__ == "__main__":
    if(not os.path.exists(md_dir)):
        os.mkdir(md_dir)
    if len(sys.argv) == 1:
        for c in list(indexes.keys()):
            for i in indexes[c]:
                build_file(c, i)
    if len(sys.argv) == 2:
        if sys.argv[1] == '-h' or sys.argv[1] == '--help':
            print(usage)
        elif re.match(r"[abt]\d{4}", sys.argv[1]):
            category = sys.argv[1][0]
            index = int(sys.argv[1][1:])
            if index in indexes[category]:
                build_file(category, index)
        else:
            print(usage)

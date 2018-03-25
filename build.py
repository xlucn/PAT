#! /usr/bin/env python3

import os

from bs4 import BeautifulSoup

from config import indexes, code_dir, md_dir, html_dir, analysis_dir


def build_file(category, index, filename):
    """
    build markdown files.
    """
    # parse using bs4
    html = "{}/{}{}.html".format(html_dir, category, index)
    content = open(html).read()
    soup = BeautifulSoup(content, "lxml")
    
    # find title and problem content
    h1 = soup.find('h1')
    pc = soup.find(id='problemContent')
    
    # write everything into a file
    with open(filename, 'w') as f:
        f.write("{}\n\n".format(soup.find('h1')))
        
        # write problem content
        f.write("## 题目\n\n")
        lines = "{}".format(pc).split('\n')
        for line in lines:
            f.write("> " + line + "\n")
        
        # write explanation
        expl = open("{}/{}{}.md".format(analysis_dir, category, index)).read()
        f.write("\n## 思路\n\n")
        f.write(expl)
        
        # write code
        file_rel_path = "{}/{}.c".format(dirs[category], index)
        github_repo = "https://github.com/OliverLew/PAT/blob/master"
        file_github_path = "{}/{}".format(github_repo, file_rel_path)
        raw_code = open(os.path.join(code_dir, file_rel_path)).read()
        code = raw_code[raw_code.index("#include"):]
        f.write("\n## 代码\n\n")
        f.write("[最新代码@github]("+ file_github_path + ")，欢迎交流\n")
        f.write("```c\n{}\n```".format(code))

dirs = {
    'a': 'PATAdvanced',
    'b': 'PATBasic',
    't': 'PATTop'
}

for c in "abt":
        for i in indexes[c]:
            md = "{}/{}{}.md".format(md_dir, c, i)
            try:
                build_file(c, i, md)
            except FileNotFoundError:
                pass

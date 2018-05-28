#! /usr/bin/env python3
"""
Build markdown files from different sources
"""

import os
import sys
import re
from subprocess import run, PIPE, CalledProcessError
import config

class FileBuilder:
    """
    build markdown files.
    """
    def __init__(self):
        self.github = "https://github.com/OliverLew/PAT/blob/master"

    def yaml_frontmatter(self, date=None, title=None):
        """
        create the yaml front matter for markdown files
        """
        tags = config.tag[self.c]
        categories = config.category[self.c]

        # Check validity
        if re.match(r'', date) is None:
            print("{}{}:".format(self.c, self.i))
            print("date should be in the pattern of 'YYYY-MM-DD HH:MM:SS +/-TTTT'")
            print("date is now: {}".format(date))
            exit(1)
        if not isinstance(title, str):
            print("{}{}:".format(self.c, self.i))
            print("title should be string")
            print("title is now: {}".format(title))
            exit(1)
        if not isinstance(categories, str):
            print("{}{}:".format(self.c, self.i))
            print("categories should be a string")
            print("categories is now: {}".format(categories))
            exit(1)
        if not isinstance(tags, list):
            print("{}{}:".format(self.c, self.i))
            print("tags should be a list")
            print("tags is now: {}".format(tags))
            exit(1)
        frontmatter = "---\n"
        frontmatter += "layout: post\n"
        frontmatter += "date: {}\n".format(date)
        frontmatter += "title:  \"{}\"\n".format(title)
        frontmatter += "categories: {}\n".format(categories)
        frontmatter += "tags: [{}]\n".format(', '.join(tags))
        frontmatter += "permalink: {}/{:04}.html\n".format(categories, self.i)
        frontmatter += "---\n\n"
        return frontmatter

    def filename(self):
        return os.path.join(config.md_dir, "{}{:04}.md".format(self.c, self.i))

    def read_html(self):
        """
        Open the html file and read into lines
        """
        html = os.path.join(config.html_dir, "{}{}.html".format(self.c, self.i))
        lines = open(html).readlines()

        h1_tag = lines[2]
        indexl = h1_tag.find("<h1>") + len("<h1>")
        indexr = h1_tag.rfind("</h1>")
        h1 = h1_tag[indexl: indexr]

        title = config.cat_string[self.c] + " " + h1 + " (C语言实现)"
        content = lines[3:]
        return title, content

    def read_code(self):
        """
        read code file from master branch
        """
        code_rel_path = os.path.join(config.code_dir[self.c],
                                     "{}.c".format(self.i))
        github_file_url = os.path.join(self.github, code_rel_path)
        raw_code = run(["git", "show", "master:" + code_rel_path], check=True,
                       stdout=PIPE, stderr=PIPE).stdout.decode("utf-8")
        code = raw_code[raw_code.index("#include"):]
        return code, github_file_url

    def read_expl(self):
        """
        read explanation.
        The file contains the date at the first line and a blank line after it.
        Hence the return has two parts.
        """
        expl_file = os.path.join(config.analysis_dir,
                                 "{}{}.md".format(self.c, self.i))
        expl = open(expl_file).readlines()
        if len(expl) < 3:
            print(expl_file + ": ")
            print("analysis file should be at least 3 lines long:")
            print("date, blank, and content")
            exit(1)
        date = expl[0].strip('\n')
        if re.match(r'', date) is None:
            print("date should be in the pattern of")
            print("'YYYY-MM-DD HH:MM:SS +/-TTTT'")
            exit(1)

        return date, "".join(expl[2:])

    def __build(self):
        """
        write everything to a final markdown file
        """
        filename = self.filename()
        title, problem_div = self.read_html()
        code, code_url = self.read_code()
        date, expl = self.read_expl()
        yaml = self.yaml_frontmatter(date, title)

        print("Building {}".format(filename))

        with open(filename, 'w') as f:
            # write the yaml front matter
            f.write(yaml)

            # write problem content
            f.write("## 题目\n\n")
            for line in problem_div:
                if config.quote_text is True:
                    f.write("> ")
                f.write(line)
            f.write("\n\n")

            # write explanation
            f.write("## 思路\n\n{}\n".format(expl))

            # write code
            f.write("## 代码\n\n")
            f.write("[最新代码@github]({})，欢迎交流\n".format(code_url))
            f.write("```c\n{}\n```".format(code))

    def build(self, c, i):
        """
        build a file with error handling
        """
        self.c = c
        self.i = i
        try:
            self.__build()
        except FileNotFoundError:
            pass
        except CalledProcessError:
            pass

usage = """Usage:
    python3 ./build.py [-h/--help] [<problem-id>]

    -h/--help: show this message

    Without <problem-id>, this script will build all the markdown files.

    <problem-id>: should be like [abt]xxxx, meaning starting with a, b or t and
        followed by a four digit number. 'a', 'b' and 't' stand for 'Advanced',
        'Basic' and 'Top', which are the names of problem sets. The four digit
        number is the problem id.
"""

def check_category_folder(folder, subfolder_list):
    """
    Check the folders for each category and create if neccesary
    """
    if not os.path.exists(folder):
        os.mkdir(folder)
    for subfolder in subfolder_list:
        subfolder_path = os.path.join(folder, "_" + subfolder)
        if not os.path.exists(subfolder_path):
            os.mkdir(subfolder_path)

if __name__ == "__main__":
    builder = FileBuilder()
    check_category_folder(config.md_dir, config.category.values())

    if len(sys.argv) == 1:
        for c in list(config.indexes.keys()):
            for i in config.indexes[c]:
                builder.build(c, i)
    if len(sys.argv) == 2:
        if sys.argv[1] == '-h' or sys.argv[1] == '--help':
            print(usage)
        elif re.match(r"[abt]\d{4}", sys.argv[1]):
            category = sys.argv[1][0]
            index = int(sys.argv[1][1:])
            if index in config.indexes[category]:
                builder.build(category, index)
        else:
            print(usage)

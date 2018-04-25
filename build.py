#! /usr/bin/env python3

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

    def read_html(self):
        """
        Open the html file and read into lines
        """
        html = os.path.join(config.html_dir, "{}{}.html".format(self.c, self.i))
        lines = open(html).readlines()
        return lines[2], lines[3:]

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
        read explanation
        """
        expl_file = os.path.join(config.analysis_dir,
                                 "{}{}.md".format(self.c, self.i))
        return open(expl_file).read()

    def __build(self):
        """
        write everything to a final markdown file
        """
        filename = "{}/{}{:04}.md".format(config.md_dir, self.c, self.i)
        h1_tag, problem_div = self.read_html()
        code, code_url = self.read_code()
        expl = self.read_expl()

        print("Building {}".format(filename))

        with open(filename, 'w') as f:
            f.write("{}\n".format(h1_tag))

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
        self.c = c
        self.i = i
        try:
            self.__build()
        except FileNotFoundError:
            pass
        except CalledProcessError:
            pass

usage = """to be continued."""

if __name__ == "__main__":
    builder = FileBuilder()
    if not os.path.exists(config.md_dir):
        os.mkdir(config.md_dir)
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

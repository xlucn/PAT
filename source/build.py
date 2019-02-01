#! /usr/bin/env python3
"""
Build markdown files from different sources
"""

import os
import sys
import re
import argparse
from bs4 import BeautifulSoup
from subprocess import run, PIPE, CalledProcessError

import html2text

import config

class FileBuilder:
    """
    build markdown files.
    """
    def __init__(self):
        self.github = "https://github.com/OliverLew/PAT/blob/master"

    def _yaml_frontmatter(self, date=None, title=None):
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

    def _filename(self):
        return os.path.join(config.md_dir, "{}{:04}.md".format(self.c, self.i))

    def _read_html(self):
        """
        Open the html file and read title and content
        """
        html = os.path.join(config.html_dir, "{}{}.html".format(self.c, self.i))
        lines = open(html).readlines()

        title = "{level} {index}. {title} {lang}".format(
                    level=config.cat_string[self.c],
                    index=self.i,
                    title=lines[0].rstrip(),
                    lang="(C语言实现)")
        content_html = self._processkatex("".join(lines[1:]))
        content = html2text.html2text(content_html)

        return title, content

    def _read_code(self):
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

    def _read_expl(self):
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

    def _build(self):
        """
        write everything to a final markdown file
        """
        filename = self._filename()
        title, problemcontent = self._read_html()
        code, code_url = self._read_code()
        date, expl = self._read_expl()
        yaml = self._yaml_frontmatter(date, title)

        print("Building {}".format(filename))

        with open(filename, 'w') as f:
            # write the yaml front matter
            f.write(yaml)

            # write problem content
            f.write("## 题目\n\n")
            f.write(problemcontent)
            f.write("\n\n")

            # write explanation
            f.write("## 思路\n\n{}\n".format(expl))

            # write code
            f.write("## 代码\n\n")
            f.write("[最新代码@github]({})，欢迎交流\n".format(code_url))
            f.write("```c\n{{% raw %}}{}{{% endraw %}}\n```".format(code))

    def build(self, c, i):
        """
        build a file with error handling
        """
        self.c = c
        self.i = i
        try:
            self._build()
        except FileNotFoundError:
            pass
        except CalledProcessError:
            pass

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="""A script to combine the
        html problem content, markdown file and the source code into a final
        markdown file for jekyll blog""")
    parser.add_argument('ids', nargs="+",
                        metavar="<problem-id>",
                        help="[abt][0-9]{4}, or 'all' for all problems.")
    args = parser.parse_args()

    builder = FileBuilder()
    if not os.path.exists(config.md_dir):
        os.mkdir(config.md_dir)

    if 'all' in args.ids:
        for c in config.indexes.keys():
            for i in config.indexes[c]:
                builder.build(c, i)
    else:
        for ID in args.ids:
            if re.match(r"[abt]\d{4}", ID):
                category = ID[0]
                index = int(ID[1:])
                if index in config.indexes[category]:
                    builder.build(category, index)

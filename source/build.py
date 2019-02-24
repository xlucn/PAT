#! /usr/bin/env python3
"""
Build markdown files from different sources
"""

import os
import sys
import re
import argparse
from subprocess import run, PIPE, CalledProcessError

import config

class FileBuilder:
    """
    build markdown files.
    """
    def __init__(self, other_platforms):
        self._github = "https://github.com/OliverLew/PAT/blob/master"
        self._other_platforms = other_platforms

    def _yaml_frontmatter(self, date=None, title=None, tags=[]):
        """
        create the yaml front matter for markdown files
        """
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
        frontmatter += "---"
        return frontmatter

    def _filename(self):
        return os.path.join(config.post_dir, "{}{:04}.md".format(self.c, self.i))

    def _read_html(self):
        """
        Open the html file and read title and content
        """
        text = os.path.join(config.text_dir, "{}{}.md".format(self.c, self.i))
        lines = open(text).readlines()

        title = "{level} {index}. {title} {lang}".format(
                    level=config.cat_string[self.c],
                    index=self.i,
                    title=lines[0].rstrip(),
                    lang="(C语言实现)")
        content_md = "".join(lines[1:])

        return title, content_md

    def _read_code(self):
        """
        read code file from master branch
        """
        code_rel_path = os.path.join(config.code_dir[self.c],
                                     "{}.c".format(self.i))
        github_file_url = os.path.join(self._github, code_rel_path)
        raw_code = run(["git", "show", "master:" + code_rel_path], check=True,
                       stdout=PIPE, stderr=PIPE).stdout.decode("utf-8")
        code = raw_code[raw_code.index("#include"):]
        return code, github_file_url

    def _read_date_tags_expl(self):
        """
        read explanation part.
        The file contains:
            the date at the first line,
            the tags at the second line,
            the actual anylasis.
        Hence the return has three parts.
        """
        expl_file = os.path.join(config.analysis_dir,
                                 "{}{}.md".format(self.c, self.i))
        expl = open(expl_file).readlines()
        if len(expl) < 2:
            print(expl_file + ": ")
            print("analysis file should be at least 2 lines long:")
            print("date, tags, and content(optional)")
            exit(1)
        date = expl[0].strip('\n')
        if re.match(r'', date) is None:
            print("date should be in the pattern of")
            print("'YYYY-MM-DD HH:MM:SS +/-TTTT'")
            exit(1)
        tags = expl[1].strip('\n').split(',')

        return date, tags, "".join(expl[2:])

    def _build(self):
        """
        write everything to a final markdown file
        """
        filename = self._filename()
        title, problemcontent = self._read_html()
        code, code_url = self._read_code()
        date, tags, expl = self._read_date_tags_expl()
        yaml = self._yaml_frontmatter(date, title, tags)

        basicContent = "## 题目\n\n{}\n\n".format(problemcontent) +          \
                       "## 思路\n\n{}\n".format(expl) +                      \
                       "## 代码\n\n" +                                       \
                       "[最新代码@github]({})，欢迎交流\n".format(code_url)

        with open(filename, 'w') as f:
            print("Building {}".format(filename))
            f.write("{}\n\n".format(yaml))
            f.write(basicContent)
            f.write("```c\n{{% raw %}}{}{{% endraw %}}```".format(code))

        if self._other_platforms == True:
            with open("others/{}{}.md".format(self.c, self.i), 'w') as f:
                print("Building {} for other platforms".format(filename))
                f.write("### 我的PAT系列文章更新重心已移至Github，" +        \
                        "欢迎来看PAT题解的小伙伴请到" +                      \
                        "[Github Pages](https://oliverlew.github.io/PAT/)" + \
                        "浏览最新内容。此处文章目前已更新至与" +             \
                        "Github Pages同步。欢迎star我的" +                   \
                        "[repo](https://github.com/OliverLew/PAT)。\n\n")
                f.write(basicContent)
                f.write("```c\n{}```".format(code))

    def build(self, category, index):
        """
        build a file with error handling
        """
        self.c = category
        self.i = index
        try:
            self._build()
        except FileNotFoundError:
            print("FileNotFoundError")
            pass
        except CalledProcessError:
            print("CalledProcessError")
            pass

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="""A script to combine the
        html problem content, markdown file and the source code into a final
        markdown file for jekyll blog""")
    parser.add_argument('ids', nargs="+",
                        metavar="<problem-id>",
                        help="[abt][0-9]{4}, or 'all' for all problems.")
    parser.add_argument('-o', '--other-platforms', action='store_true',
                        help='If generate files for other platforms')
    args = parser.parse_args()

    builder = FileBuilder(args.other_platforms)
    if not os.path.exists(config.post_dir):
        os.mkdir(config.post_dir)

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

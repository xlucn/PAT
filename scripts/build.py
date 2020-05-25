#! /usr/bin/env python3
"""
Build markdown files from different sources

A script to combine the
html problem content, markdown file and the source code into a final
markdown file for jekyll blog
"""

import os
import re
import argparse
import logging
from subprocess import run, PIPE

logging.basicConfig(format="[%(level)s] %(filename)s:%(lineno): %(message)s")

cat_counts = {'a': 155, 'b': 95, 't': 27}

category_str = {'a': 'Advanced', 'b': 'Basic', 't': 'Top'}

script_dir = os.path.dirname(os.path.realpath(__file__))

# The dir of final generated markdown file
post_dir = os.path.join(script_dir, "..", "_articles")


class FileBuilder:
    """
    build a markdown file.
    """
    def __init__(self, category, index, other_platforms):
        self._github = "https://github.com/OliverLew/PAT/blob/master"
        self._gh_pages = "https://oliverlew.github.io/PAT"

        self.c = category
        self.i = index
        self._other_platforms = other_platforms

        self._permalink = "{}/{}.html".format(category_str[self.c], self.i)
        self._filename = os.path.join(post_dir,
                                      "{}{}.md".format(self.c, self.i))
        self._text_file = os.path.join(post_dir, "html",
                                       "{}{}.md".format(self.c, self.i))
        self._expl_file = os.path.join(post_dir, "analysis",
                                       "{}{}.md".format(self.c, self.i))

    def _yaml_frontmatter(self, date=None, title=None, tags=None):
        """
        create the yaml front matter for markdown files
        """
        categories = category_str[self.c]
        # Check validity
        if re.match(r'\d{4}-\d{2}-\d{2} \d{2}:\d{2}', date) is None:
            logging.info("{}{}: "
                         "date should be 'YYYY-MM-DD HH:MM[:SS +/-TTTT]'"
                         "date is now: {}".format(self.c, self.i, date))
            exit(1)
        if not isinstance(title, str):
            logging.info("{}{}: title should be string"
                         "title is now: {}".format(self.c, self.i, title))
            exit(1)
        if not isinstance(categories, str):
            logging.info("{}{}: categories should be a string"
                         "categories is now: {}".format(self.c, self.i,
                                                        categories))
            exit(1)
        if not isinstance(tags, list):
            logging.info("{}{}: tags should be a list"
                         "tags is now: {}".format(self.c, self.i, tags))
            exit(1)
        frontmatter = "---\n"
        frontmatter += "layout: post\n"
        frontmatter += "date: {}\n".format(date)
        frontmatter += "title:  \"{}\"\n".format(title)
        frontmatter += "categories: {}\n".format(categories)
        frontmatter += "tags: [{}]\n".format(', '.join(tags))
        frontmatter += "permalink: {}\n".format(self._permalink)
        frontmatter += "---"
        return frontmatter

    def _read_text(self):
        """
        Open the html file and read title and content
        """
        lines = open(self._text_file).readlines()

        title = "PAT {level} {index}. {title} {lang}".format(
            level=category_str[self.c],
            index=self.i,
            title=lines[1].rstrip(),
            lang="(C语言实现)")
        content_md = "".join(lines[3:])

        return title, content_md

    def _read_code(self):
        """
        read code file from master branch
        """
        code_rel_path = os.path.join("PAT{}".format(category_str[self.c]),
                                     "{}.c".format(self.i))
        github_file_url = os.path.join(self._github, code_rel_path)
        result = run(["git", "show", "master:" + code_rel_path],
                     # check=True,
                     stdout=PIPE,
                     stderr=PIPE)

        if result.returncode == 0:
            raw_code = result.stdout.decode("utf-8")
            code = raw_code[raw_code.index("#include"):]
            return code, github_file_url

        return None, None

    def _read_date_tags_expl(self):
        """
        parse explanation part.
        The file contains:
            <!--
            date
            tags
            -->
            actual anylasis.
        Hence the return has three parts.
        """
        expl_file = self._expl_file
        try:
            expl = open(expl_file).readlines()
        except FileNotFoundError:
            print("No analysis file: {}".format(expl_file))
            return None, None, None

        if len(expl) < 4:
            print(expl_file + ": ")
            print("analysis file should be at least 4 lines long:")
            print("date, tags, surrounding html comment and content(optional)")
            exit(1)
        date = expl[1].strip('\n')
        if re.match(r'', date) is None:
            print("date should be in the pattern of")
            print("'YYYY-MM-DD HH:MM:SS +/-TTTT'")
            exit(1)
        tags = expl[2].strip('\n').split(',')

        return date, tags, "".join(expl[4:])

    def build(self):
        """
        write everything to a final markdown file
        """
        title, problemcontent = self._read_text()
        code, code_url = self._read_code()
        if code is None:
            return
        date, tags, expl = self._read_date_tags_expl()
        if expl is None:
            return

        yaml = self._yaml_frontmatter(date, title, tags)

        with open(self._filename, 'w') as md_file:
            print("Building {}".format(self._filename))
            md_file.write(
                "{yaml}\n\n## 题目\n\n{{% include_relative {text} %}}"
                "\n\n## 思路\n\n{{% include_relative {analysis} %}}"
                "\n\n## 代码\n\n[Github最新代码]({url})，欢迎交流\n\n"
                "```c\n{{% raw %}}{code}{{% endraw %}}```".format(
                    yaml=yaml,
                    text=os.path.join("html",
                                      "{}{}.md".format(self.c, self.i)),
                    analysis=os.path.join("analysis",
                                          "{}{}.md".format(self.c, self.i)),
                    url=code_url,
                    code=code)
            )

        if self._other_platforms:
            # The dir of markdown file prepared for other blog websites

            other_file = os.path.join(post_dir, "others",
                                      "{}{}.md".format(self.c, self.i))
            with open(other_file, 'w') as md_file:
                print("Building {} for other platforms".format(other_file))
                md_file.write(
                    "{title}\n"
                    "### 我的PAT系列文章更新重心已移至Github，"
                    "欢迎来看PAT题解的小伙伴请到[Github Pages]({gh})"
                    "浏览最新内容([本篇文章链接]({gh}/{link}))。"
                    "此处文章目前已更新至与Github Pages同步。欢迎star我的"
                    "[repo](https://github.com/OliverLew/PAT)。\n\n"
                    "## 题目\n\n{pc}\n\n"
                    "## 思路\n\n{expl}\n"
                    "## 代码\n\n"
                    "[最新代码@github]({codeurl})，欢迎交流\n"
                    "```c\n{code}```".format(
                        title=title,
                        gh=self._gh_pages,
                        link=self._permalink,
                        pc=problemcontent,
                        expl=expl,
                        codeurl=code_url,
                        code=code)
                )


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('ids', nargs="+", metavar="<problem-id>")
    parser.add_argument('-o', '--other-platforms', action='store_true')
    args = parser.parse_args()

    if not os.path.exists(post_dir):
        os.mkdir(post_dir)

    if 'all' in args.ids:
        for c in ['b', 'a', 't']:
            for i in [i + 1001 for i in range(cat_counts[c])]:
                builder = FileBuilder(c, i, args.other_platforms)
                builder.build()
    else:
        for ID in args.ids:
            if not re.match(r"[abt]\d{4}", ID):
                continue
            category = ID[0]
            index = int(ID[1:])
            if index > 1000 + cat_counts[category]:
                continue
            builder = FileBuilder(category, index, args.other_platforms)
            builder.build()

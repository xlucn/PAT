#! /usr/bin/env python3
"""
Build markdown files from different sources
"""

import os
import re
import argparse
from subprocess import run, PIPE

import config

class FileBuilder:
    """
    build markdown files.
    """
    def __init__(self, category, index, other_platforms):
        self._github = "https://github.com/OliverLew/PAT/blob/master"
        self._gh_pages = "https://oliverlew.github.io/PAT"

        self.c = category
        self.i = index
        self._other_platforms = other_platforms

        self._permalink = "{}/{}.html".format(config.category[self.c], self.i)
        self._filename = os.path.join(config.post_dir,
                                      "{}{}.md".format(self.c, self.i))
        self._text_file = os.path.join(config.post_dir, config.text_dir,
                                       "{}{}.md".format(self.c, self.i))
        self._expl_file = os.path.join(config.post_dir, config.analysis_dir,
                                       "{}{}.md".format(self.c, self.i))

    def _yaml_frontmatter(self, date=None, title=None, tags=None):
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
        frontmatter += "permalink: {}\n".format(self._permalink)
        frontmatter += "---"
        return frontmatter

    def _read_text(self):
        """
        Open the html file and read title and content
        """
        text = self._text_file
        lines = open(text).readlines()

        title = "{level} {index}. {title} {lang}".format(
            level=config.cat_string[self.c],
            index=self.i,
            title=lines[1].rstrip(),
            lang="(C语言实现)")
        content_md = "".join(lines[3:])

        return title, content_md

    def _read_code(self):
        """
        read code file from master branch
        """
        code_rel_path = os.path.join(config.code_dir[self.c],
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
        read explanation part.
        The file contains:
            the date at the first line,
            the tags at the second line,
            the actual anylasis.
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
            md_file.write("{}\n\n".format(yaml))
            md_file.write("## 题目\n\n" +                                    \
                    "{{% include_relative {} %}}".format(
                        os.path.join(config.text_dir,
                                     "{}{}.md".format(self.c, self.i))) +    \
                    "\n\n## 思路\n\n" +                                      \
                    "{{% include_relative {} %}}".format(
                        os.path.join(config.analysis_dir,
                                     "{}{}.md".format(self.c, self.i))) +    \
                    "\n## 代码\n\n" +                                        \
                    "[最新代码@github]({})，欢迎交流\n".format(code_url))
            md_file.write("```c\n{{% raw %}}{}{{% endraw %}}```".format(code))

        if self._other_platforms:
            with open("others/{}{}.md".format(self.c, self.i), 'w') as md_file:
                print("Building {} for other platforms".format(self._filename))
                md_file.write("### 我的PAT系列文章更新重心已移至Github，" +  \
                    "欢迎来看PAT题解的小伙伴请到" +                          \
                    "[Github Pages]({})".format(self._gh_pages) +            \
                    "浏览最新内容" +                                         \
                    "([本篇文章链接]({}/{}))。".format(self._gh_pages,
                                                self._permalink) +           \
                    "此处文章目前已更新至与" +                               \
                    "Github Pages同步。欢迎star我的" +                       \
                    "[repo](https://github.com/OliverLew/PAT)。\n\n" +       \
                    "## 题目\n\n{}\n\n".format(problemcontent) +             \
                    "## 思路\n\n{}\n".format(expl) +                         \
                    "## 代码\n\n" +                                          \
                    "[最新代码@github]({})，欢迎交流\n".format(code_url) +   \
                    "```c\n{}```".format(code))



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

    if not os.path.exists(config.post_dir):
        os.mkdir(config.post_dir)

    if 'all' in args.ids:
        for c in config.indexes.keys():
            for i in config.indexes[c]:
                builder = FileBuilder(c, i, args.other_platforms)
                builder.build()
    else:
        for ID in args.ids:
            if re.match(r"[abt]\d{4}", ID):
                category = ID[0]
                index = int(ID[1:])
                if index in config.indexes[category]:
                    builder = FileBuilder(category, index, args.other_platforms)
                    builder.build()

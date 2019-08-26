#! /usr/bin/env python3
import os

script_dir = os.path.dirname(os.path.realpath(__file__))

# The dir of final generated markdown file
post_dir = os.path.join(script_dir, "..", "_articles")
# The dir of markdown file prepared for other blog websites
other_dir = os.path.join(post_dir, "others")
# The dir of html file from patest.cn
text_dir = "html"
# The dir of md files of only analysis text
analysis_dir = "analysis"

# Children folders of code_dir
code_dir = {
    'a': 'PATAdvanced',
    'b': 'PATBasic',
    't': 'PATTop'
}

category = {
    'a': 'Advanced',
    'b': 'Basic',
    't': 'Top'
}

cat_string = {
    'a': "PAT Advanced",
    'b': "PAT Basic",
    't': "PAT Top"
}

# Problem indexes for each level
indexes = {
    'a': [i + 1001 for i in range(155)],
    'b': [i + 1001 for i in range(95)],
    't': [i + 1001 for i in range(27)]
}

urlidx = {
    'b': "994805260223102976",
    'a': "994805342720868352",
    't': "994805148990160896"
}

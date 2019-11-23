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


category = {
    'a': 'Advanced',
    'b': 'Basic',
    't': 'Top'
}

# Children folders of code_dir
code_dir = {
    'a': 'PAT' + category['a'],
    'b': 'PAT' + category['b'],
    't': 'PAT' + category['t']
}

cat_string = {
    'a': 'PAT ' + category['a'],
    'b': 'PAT ' + category['b'],
    't': 'PAT ' + category['t']
}

# Problem numbers
numbers = {
    'a': 155,
    'b': 95,
    't': 27
}

# Problem indexes for each level
indexes = {
    'a': [i + 1001 for i in range(numbers['a'])],
    'b': [i + 1001 for i in range(numbers['b'])],
    't': [i + 1001 for i in range(numbers['t'])]
}

urlidx = {
    'b': "994805260223102976",
    'a': "994805342720868352",
    't': "994805148990160896"
}

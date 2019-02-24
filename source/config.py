#! /usr/bin/env python3

post_dir = "../_articles"                # The dir of final generated markdown file
text_dir = "../_articles/html"           # The dir of html file from patest.cn
analysis_dir = "../_articles/analysis"   # The dir of md files of only analysis text
code_dir = {                # Children folders of code_dir
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

indexes = {                 # Problem indexes for each level
    'a': [i + 1001 for i in range(155)],
    'b': [i + 1001 for i in range(95)],
    't': [i + 1001 for i in range(27)]
}

urlidx = {
    'b': "994805260223102976",
    'a': "994805342720868352",
    't': "994805148990160896"
}

#! /usr/bin/env python3

md_dir = "../_articles"               # The dir of final generated markdown file
html_dir = "html"           # The dir of html file from patest.cn
analysis_dir = "analysis"   # The dir of md files of only analysis text
code_dir = {                # Children folders of code_dir
    'a': 'PATAdvanced',
    'b': 'PATBasic',
    't': 'PATTop'
}

tag = {
    'a': ['PAT-A'],
    'b': ['PAT-B'],
    't': ['PAT-T']
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

quote_text = False   # If add '> ' to problem text in markdown file

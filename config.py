#! /usr/bin/env python3

md_dir = "md"               # The dir of final generated markdown file
html_dir = "html"           # The dir of html file from patest.cn
analysis_dir = "analysis"   # The dir of md files of only analysis text
code_dir = {                # Children folders of code_dir
    'a': 'PATAdvanced',
    'b': 'PATBasic',
    't': 'PATTop'
}

tag = {
    'a': "PAT-A",
    'b': "PAT-B",
    't': "PAT-T"
}

indexes = {                 # Problem indexes for each level
    'a': [i + 1001 for i in range(147)],
    'b': [i + 1001 for i in range(85)],
    't': [i + 1001 for i in range(23)]
}

quote_text = True   # If add '> ' to problem text in markdown file

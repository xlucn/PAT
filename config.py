#! /usr/bin/env python3

indexes = {                 # Problem indexes for each level
    'a': [i + 1001 for i in range(147)],
    'b': [i + 1001 for i in range(85)],
    't': [i + 1001 for i in range(23)]
}

class dirs:
    md = "md"               # The dir of final generated markdown file
    html = "html"           # The dir of html file from patest.cn
    analysis = "analysis"   # The dir of md files of only analysis text
    code = {                # Children folders of code_dir
        'a': 'PATAdvanced',
        'b': 'PATBasic',
        't': 'PATTop'
    }
    
    def __init__(self):
        pass

class configs:
    quote_text = True   # If add '> ' to problem text in markdown file

    def __init__(self):
        pass

#! /usr/bin/env python3

indexes = {
    'a': [i + 1001 for i in range(110)] +
         [i + 1101 for i in range(39)],
    'b': [i + 1001 for i in range(85)],
    't': [i + 1001 for i in range(21)]
}

html_dir = "html"

md_dir = "md"

analysis_dir = "analysis"

code_dir = "../PAT"

configs = {
    "quote_text": True
}

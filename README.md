# PAT解题说明

Github Pages + Jekyll搭建的静态博客

博客地址： https://oliverlew.github.io/PAT

本地依赖的Python模块:

- selenium (需要firefox)
- html2text
- beautifulsoup

## 文件结构

最终目标：生成jekyll博客接受的markdown文件，需要：

- PAT习题题目内容。放在`_articles/html`，由`scripts/download.py`下载自PAT网站，并转换为markdown语法。
- 题解内容。写在`_articles/analysis`文件夹里的markdown文件中。
- 代码。位于master分支，利用`git show`命令读取。

`scripts/build.py`Python脚本会将上述内容汇集到一个文件中，放在`_articles`文件夹下，并在其中添加适当的标题、
副标题、markdown语法结构还有为jekyll设置的yaml front matter。

博客基于[minima](https://github.com/jekyll/minima)这个jekyll主题，增加了一下功能/特点：

- 做了一定美化，css的改变集中在`assets/css/mystyle.css`中
- 添加了分类（顶级、甲级、乙级）和标签
- 支持Mathjax，因此可以原样显示题目中的公式等
- 利用[giscus](https://github.com/giscus/giscus)评论系统

## Todo list

- [x] Get it running. First successful run in [this commit][first run]
- [x] Add correct date to filenames in [this commit][add date]
- [x] Use include to reduce code duplication in [this pull request][use include]
- [x] Use permalink to fix the page urls in [this pull request][use collections]
- [x] Add MathJax support in [this pull request][add mathjax]
- [x] Use tags/categories to manage posts.
  - [x] Add indexes of each category in [this commit][add categories]
  - [x] Add tags in [this pull request][add tags]
- [x] Add commenting system. Added Gitalk in [this pull request][add gitalk]
- [x] Add page analysis tool, added Google analytics in [this commit][add GA]

[first run]: https://github.com/OliverLew/PAT/commit/a06f099b2a64138612128b2c9227b2b2514ff617
[add date]: https://github.com/OliverLew/PAT/commit/e6e23b82b4f12b895d2504602f8b4a6b9e912f41
[use collections]: https://github.com/OliverLew/PAT/pull/10
[use include]: https://github.com/OliverLew/PAT/pull/17
[add categories]: https://github.com/OliverLew/PAT/commit/2f74e56775f5ec7c1ab31c27f23d3071b178784f
[add tags]: https://github.com/OliverLew/PAT/pull/15
[add GA]: https://github.com/OliverLew/PAT/commit/54db3d618760df626872c6fe42e861709ca1d962
[add mathjax]: https://github.com/OliverLew/PAT/pull/12
[add gitalk]: https://github.com/OliverLew/PAT/pull/16

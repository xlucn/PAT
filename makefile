MD=$(wildcard md/*.md)
ANA=$(wildcard analysis/*.md)
HTML=$(wildcard html/*.html)

all:$(MD)

md/%.md:analysis/%.md html/%.html
	echo ./build.py $()

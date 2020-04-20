MD_DIR=_articles
SRC_DIR=scripts

HTML_DIR=$(MD_DIR)/html
ANA_DIR=$(MD_DIR)/analysis

ANA=$(wildcard $(ANA_DIR)/*.md)
HTML=$(addprefix $(HTML_DIR)/,$(notdir $(ANA:.md=.html)))
MD=$(addprefix $(MD_DIR)/,$(notdir $(ANA)))
MASTER=$(shell git ls-tree -r --name-only --full-tree master)

DL_PY=$(SRC_DIR)/download.py
BD_PY=$(SRC_DIR)/build.py
CONF=$(SRC_DIR)/config.py

.PHONY: clean rebuild download force-download test

all: $(MD)

$(MD_DIR)/%.md:$(ANA_DIR)/%.md $(BD_PY) $(CONF)
	@sh scripts/build "$@"

$(ANA_DIR)/%.md:
	touch $@

$(HTML_DIR)/%.html: $(DL_PY)
	python $(SRC_DIR)/download.py $(notdir $(basename $@))

clean:
	rm -f $(MD)

rebuild: clean all

download:
	python $(SRC_DIR)/download.py

force-download:
	python $(SRC_DIR)/download.py -f

test:
	@echo -e $(MD)

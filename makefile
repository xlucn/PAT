HTML_DIR=html
ANA_DIR=analysis
MD_DIR=md

HTML=$(wildcard $(HTML_DIR)/*.html)
ANA=$(addprefix $(ANA_DIR)/,$(notdir $(HTML:.html=.md)))
MD=$(addprefix $(MD_DIR)/,$(notdir $(HTML:.html=.md)))

DL_PY=download.py
BD_PY=build.py

all:$(MD)

$(MD_DIR)/%.md:$(ANA_DIR)/%.md $(HTML_DIR)/%.html $(BD_PY)
	./build.py $(notdir $(basename $@))

$(ANA_DIR)/%.md:
	touch $@

$(HTML_DIR)/%.html: $(DL_PY)
	./download.py $(notdir $(basename $@))

clean:
	rm $(MD)

test:
	@echo -e $(MD)

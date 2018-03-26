HTML_DIR=html
ANA_DIR=analysis
MD_DIR=md

HTML=$(wildcard $(HTML_DIR)/*.html)
ANA=$(addprefix $(ANA_DIR)/,$(notdir $(HTML:.html=.md)))
MD=$(addprefix $(MD_DIR)/,$(notdir $(HTML:.html=.md)))

all:$(MD)

$(MD_DIR)/%.md:$(ANA_DIR)/%.md $(HTML_DIR)/%.html
	./build.py $(notdir $(basename $@))

$(ANA_DIR)/%.md:
	touch $@

clean:
	rm -rf $(MD_DIR)/

test:
	@echo -e $(MD)

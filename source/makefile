HTML_DIR=html
ANA_DIR=analysis
MD_DIR=../_articles

ANA=$(wildcard $(ANA_DIR)/*.md)
HTML=$(addprefix $(HTML_DIR)/,$(notdir $(ANA:.md=.html)))
MD=$(addprefix $(MD_DIR)/,$(notdir $(ANA)))
MASTER=$(shell git ls-tree -r --name-only --full-tree master)

DL_PY=download.py
BD_PY=build.py
CONF=config.py

all: $(MD)

$(MD_DIR)/%.md:$(ANA_DIR)/%.md $(HTML_DIR)/%.html $(BD_PY) $(CONF)
	@id=$(notdir $(basename $@));                                           \
	case $${id:0:1} in                                                      \
	'a')                                                                    \
	    codefile=PATAdvanced/$${id:1:4}.c;                                  \
	    ;;                                                                  \
	'b')                                                                    \
	    codefile=PATBasic/$${id:1:4}.c;                                     \
	    ;;                                                                  \
	't')                                                                    \
	    codefile=PATTop/$${id:1:4}.c;                                       \
	    ;;                                                                  \
	*)                                                                      \
	    echo file name wrong: $@;                                           \
	esac;                                                                   \
	if [[ "$(MASTER)" == *$$codefile* ]]; then                              \
	    for f in $^; do                                                     \
	        if [ ! -f $$f ]; then                                           \
	            echo $$f is missing;                                        \
	        else                                                            \
	            ./build.py $$id; break;                                     \
	        fi;                                                             \
	    done;                                                               \
	else                                                                    \
	    echo $$codefile not exist;                                          \
	fi

$(ANA_DIR)/%.md:
	touch $@

$(HTML_DIR)/%.html: $(DL_PY)
	./download.py $(notdir $(basename $@))

clean:
	rm -f $(MD)

rebuild: clean all

download:
	python ./download.py

force-download:
	./download.py -f

test:
	@echo -e $(MD)

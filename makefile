HTML_DIR=html
ANA_DIR=analysis
MD_DIR=md

HTML=$(wildcard $(HTML_DIR)/*.html)
ANA=$(addprefix $(ANA_DIR)/,$(notdir $(HTML:.html=.md)))
MD=$(addprefix $(MD_DIR)/,$(notdir $(HTML:.html=.md)))
MASTER=$(shell git ls-tree -r --name-only master)

DL_PY=download.py
BD_PY=build.py

all:$(MD)

$(MD_DIR)/%.md:$(ANA_DIR)/%.md $(HTML_DIR)/%.html $(BD_PY)
	@id=$(notdir $(basename $@)); 											\
	case $${id:0:1} in														\
	'a')																	\
		codefile=PATAdvanced/$${id:1:4}.c									\
		;;																	\
	'b')																	\
		codefile=PATBasic/$${id:1:4}.c;										\
		;;																	\
	't')																	\
		codefile=PATTop/$${id:1:4}.c;										\
		;;																	\
	*)																		\
		echo something wrong;												\
	esac;																	\
	if [[ "$(MASTER)" == *$$codefile* ]]; then								\
		for f in $^; do		 												\
			if [ ! -f $$f ]; then 											\
				echo $$f is missing; 										\
			else															\
				./build.py $$id; break;								\
			fi;																\
		done;																\
#	else 																	\
#		echo $$codefile not exist;											\
	fi

$(ANA_DIR)/%.md:
	touch $@

$(HTML_DIR)/%.html: $(DL_PY)
	./download.py $(notdir $(basename $@))

clean:
	rm $(MD)

test:
	@echo -e $(MD)

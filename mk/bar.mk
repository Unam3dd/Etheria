LINE_SIZE=75

# Top Bar, $1 = length of line

define top_bar
	echo -en "┌"
	for ((i = 0; i < $(LINE_SIZE); i++)); do echo -en "─"; done
	echo -e "┐"
endef

define top_bar_center
	echo -en "    ┌"
	for ((i = 0; i < $(LINE_SIZE)-2; i++)); do echo -en "─"; done
	echo -e "┐"
endef

# First Parameter is your string

define string_bar
	$(eval LEN_ARG:= $(shell echo -en "$(1)" | wc -m))
	$(eval PADDING:= $(shell echo -e "$(LINE_SIZE)-$(LEN_ARG)" | bc))
	echo -n "│$(1)"
	for ((i = 0; i < $(PADDING)-2; i++)); do echo -en '\x20'; done
	echo -e "│"
endef

define string_bar_center
	$(eval LEN_ARG:=$(shell echo -en "$(1)" | wc -m | tr -d '\n'))
	$(eval PADDING:=$(shell echo -e "$(LINE_SIZE)-$(LEN_ARG)" | bc | tr -d '\n'))
	echo -ne "    │$(1)"
	for ((i = 0; i < $(PADDING)-2; i++)); do echo -ne ' '; done
	echo -e "│"
endef

define write_line
	echo -ne "\t\t"
	for ((i = 0; i < $(LINE_SIZE)-2; i++)); do echo -en "─"; done
endef

# Same as Top bar

define bot_bar
	echo -en "└"
	for ((i = 0; i < $(LINE_SIZE)-2; i++)); do echo -en "─"; done
	echo -e "┘"
endef

define bot_bar_center
	echo -en "    └"
	for ((i = 0; i < $(LINE_SIZE)-2; i++)); do echo -en "─"; done
	echo -e "┘"
endef

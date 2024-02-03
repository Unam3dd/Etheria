include ./mk/colors.mk
include ./mk/icons.mk

define check_binary
	$(if $(shell command -v $(1) 2>/dev/null),\
		$(info $(shell echo -e "$(CHECK) $(GREEN)$(1)$(RST) is installed !")),\
		$(error $(info $(shell echo -e "$(FAIL) Please install $(RED)$(1)$(RST) !"))))
endef

define short_check_binary
	$(if $(shell command -v $(1) 2>/dev/null),\
		$(info $(shell echo -en "$(UNIQ_CHECK)")),\
		$(info $(shell echo -en "$(UNIQ_FAIL)")))
endef


SOURCE_DIR := $(shell pwd)

PROBLEMS := $(sort $(notdir $(shell find $(SOURCE_DIR) -maxdepth 1 -type d -exec basename \{\} \;| egrep '[0-9]{3}-*')))

DEFAULT: build

.PHONY: build
build:
	@for problem in $(PROBLEMS) ; do \
		cd $(SOURCE_DIR)/$$problem ; make ; \
	done

.PHONY: clean
clean:
	@for problem in $(PROBLEMS) ; do \
		cd $(SOURCE_DIR)/$$problem ; make clean; \
	done

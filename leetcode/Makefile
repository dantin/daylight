
SOURCE_DIR := $(shell pwd)

PROBLEMS := \
	001-two-sum \
	002-add-two-numbers \
	003-longest-substring-without-repeat \
	004-median-of-two-sorted-array

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

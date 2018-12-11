
SOURCE_DIR := $(shell pwd)

DEFAULT: build

.PHONY: build
build:
	@cd $(SOURCE_DIR)/001-two-sum; make
	@cd $(SOURCE_DIR)/002-add-two-numbers; make
	@cd $(SOURCE_DIR)/003-longest-substring-without-repeat; make

.PHONY: clean
clean:
	@cd $(SOURCE_DIR)/001-two-sum; make clean
	@cd $(SOURCE_DIR)/002-add-two-numbers; make clean
	@cd $(SOURCE_DIR)/003-longest-substring-without-repeat; make clean

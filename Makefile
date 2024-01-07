OS := $(shell uname -s)

ifeq ($(OS), Linux)
include Makefile.linux
else ifeq ($(OS), Darwin)
include Makefile.macos
else
$(error "Invalid OS")
endif
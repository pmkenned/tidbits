all:

ifeq ($(OS),Windows_NT)
	@echo "windows"
	include sources_win.mk
else

	UNAME := $(shell uname)
	ifeq ($(UNAME),Linux)
		include sources_linux.mk
	endif

endif

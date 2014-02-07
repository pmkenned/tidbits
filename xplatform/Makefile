
TARGET = xplatform

ifeq ($(OS),Windows_NT)
	@echo "windows"
	include sources_win.mk
else
	UNAME_S := $(shell uname)
	ifeq ($(UNAME_S),Linux)
		include sources_linux.mk
	endif
endif


all:
	gcc $(SOURCES) -o $(TARGET)

.PHONY: clean

clean:
	rm $(TARGET)

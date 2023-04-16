PROJ_NAME := archiver
# utils
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	OS := macOS
endif
# target source file
LAST_MODIFIED := $(shell ls -lt | egrep ".(c|cpp)$$" | head -1 | awk '{print $$NF}' | xargs -I% find . -type f -name '%')
# compile options
CC := gcc
WFLAGS := -Wall -Werror -Wextra
CFLAGS := $(WFLAGS)
LDLIBS := -lm
MEMFLAGS := --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes
# macro
RM := rm -rf
export


all:
ifeq ($(OS), macOS)
	@$(CC) -g $(LAST_MODIFIED) $(LDLIBS) && ./a.out && code output.txt
else
	@$(CC) -g $(LAST_MODIFIED) $(LDLIBS) && ./a.out
endif
d:
	$(CC) -g -DDEBUG $(CFLAGS) $(LAST_MODIFIED) $(LDLIBS) && ./a.out
valgrind:
	valgrind $(MEMFLAGS) ./a.out
container:
	bash test/run_docker_image.sh
clean:
	$(RM) *.out
	$(RM) *.dSYM
	$(RM) output.txt
re: clean
	$(MAKE) all


info:
	@echo $(LAST_MODIFIED)
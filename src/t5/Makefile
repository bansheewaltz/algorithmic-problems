PROJ_NAME := archiver
OS := macOS
#target source file
LAST_MODIFIED := $(shell ls -lt | egrep ".(c|cpp)$$" | head -1 | awk '{print $$NF}' | xargs -I% find . -type f -name '%')
#compile options
CC := gcc
WFLAGS := -Wall -Werror -Wextra
CFLAGS := $(WFLAGS)
#macro
RM := rm -rf
export


all:
	@$(CC) -g $(LAST_MODIFIED) && ./a.out && code output.txt
check:
	$(CC) $(CFLAGS) -g $(LAST_MODIFIED) && ./a.out
d:
	$(CC) -g -DDEBUG $(CFLAGS) $(LAST_MODIFIED) && ./a.out
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
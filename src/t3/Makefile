LAST_MODIFIED := $(shell ls -lt | egrep ".(c|cpp)$$" | head -1 | awk '{print $$NF}' | xargs -I% find . -type f -name '%')
#compile options
CC := gcc
WFLAGS := -Wall -Werror -Wextra
CFLAGS := $(WFLAGS)
#macro
RM := rm -rf


all:
	@$(CC) -g $(LAST_MODIFIED) && ./a.out && code output.txt
check:
	$(CC) $(CFLAGS) -g $(LAST_MODIFIED) && ./a.out
# d:
# 	$(CC) -DDEBUG $(CFLAGS) -g $(LAST_MODIFIED) && ./a.out
d:
	$(CC) -g -DDEBUG $(CFLAGS) t3.c print_tree.c && ./a.out
clean:
	$(RM) *.out
	$(RM) *.dSYM
	$(RM) output.txt
re: clean
	$(MAKE) all


info:
	@echo $(LAST_MODIFIED)
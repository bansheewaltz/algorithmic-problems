LAST_MODIFIED := $(shell ls -ltrR | egrep ".(c|cpp)$$" | head -1 | awk '{print $$NF}' | xargs -I% find . -type f -name '%')

WFLAGS := -Wall -Werror -Wextra
CFLAGS = $(WFLAGS)
# all:
# 	$(CC) -g $(LAST_MODIFIED) -o $(EXE) && ./$(EXE)
all:
	@$(CC) -g $(LAST_MODIFIED) && ./a.out
check:
	$(CC) $(CFLAGS) -g $(LAST_MODIFIED) && ./a.out
clean:
	rm -rf *.out
	rm -rf *.dSYM
info:
	@echo $(LAST_MODIFIED)
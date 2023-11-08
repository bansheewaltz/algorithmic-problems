STDFLAG := -std=c++17
WFLAGS := -Wall -Werror -Wextra -Wpedantic -pedantic-errors -fsanitize=address
TESTER_CFLAGS := -O3 -std=c++20 -Wall -Werror -Wextra -fsanitize=address,undefined
DEBUGFLAG := -g
CFLAGS := $(STDFLAG) $(WFLAGS)
EXE_NAME := 1

c: w r

n: CFLAGS := $(STDFLAG)
d: CFLAGS := $(DEBUGFLAG) $(CFLAGS)
w: CFLAGS := $(TESTER_CFLAGS)
n w d:
	clang++ $(CFLAGS) $(EXE_NAME).cpp -o $(EXE_NAME)
r: 
	./$(EXE_NAME)

rm:
	rm -rf solution

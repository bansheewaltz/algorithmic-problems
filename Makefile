WFLAGS := -Wall -Werror -Wextra -Wpedantic
all:
	g++ -O2 $(WFLAGS) tester.cpp -o test
debug:
	g++ -g -DDEBUGGING $(WFLAGS) tester.cpp -o dtest

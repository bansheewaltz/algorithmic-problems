package main

import (
	"bufio"
	"fmt"
	"os"
)

var in = bufio.NewReaderSize(os.Stdin, 1024*1024)
var out = bufio.NewWriterSize(os.Stdout, 1024*1024)

func main() {
	solve()
	out.Flush()
}

func solve() {
	const alphabetLen = 128
	var n, t int
	fmt.Fscanln(in, &n, &t)

	letters := [alphabetLen]int{}
	for i := 0; i < n; i++ {
		var letter int
		fmt.Fscanf(in, "%c ", &letter)
		letters[letter]++
	}

	for i := 0; i < t; i++ {
		var pw string
		fmt.Fscan(in, &pw)
		pwletters := [alphabetLen]int{}
		for _, v := range pw {
			pwletters[v]++
		}
		if letters == pwletters {
			fmt.Fprintln(out, "YES")
		} else {
			fmt.Fprintln(out, "NO")
		}
	}
}

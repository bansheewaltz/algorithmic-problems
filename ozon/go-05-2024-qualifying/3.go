package main

import (
	"bufio"
	"fmt"
	"os"
)

var in = bufio.NewReaderSize(os.Stdin, 1024*1024)
var out = bufio.NewWriterSize(os.Stdout, 1024*1024)

func main() {
	var testCnt int
	fmt.Fscan(in, &testCnt)
	for t := 1; t <= testCnt; t++ {
		solve()
	}
	out.Flush()
}

func solve() {
	var str string
	fmt.Fscan(in, &str)

	ichar := str[0]
	isPossible := true
	var i int
out:
	for i < len(str) {
		switch {
		case i+1 < len(str) && str[i+1] == ichar:
			i++
		case i+2 < len(str) && str[i+2] == ichar:
			i += 2
		case i+1 == len(str) && str[i] == ichar:
			i++
		default:
			isPossible = false
			break out
		}
	}

	if isPossible == false {
		fmt.Fprintln(out, "NO")
	} else {
		fmt.Fprintln(out, "YES")
	}
}

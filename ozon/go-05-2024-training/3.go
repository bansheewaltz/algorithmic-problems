package main

import (
	"bufio"
	"fmt"
	"os"
)

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

var in = bufio.NewReaderSize(os.Stdin, 1024*1024)
var out = bufio.NewWriterSize(os.Stdout, 1024*1024)

func main() {
	solve()
	out.Flush()
}

func solve() {
	var n, q int
	fmt.Fscan(in, &n, &q)

	MessageLast := make([]int, n+1)
	MessageIdx := 0

	for i := 1; i <= q; i++ {
		var t, id int
		fmt.Fscan(in, &t, &id)
		switch t {
		case 1:
			MessageIdx++
			MessageLast[id] = MessageIdx
		case 2:
			fmt.Fprintln(out, max(MessageLast[0], MessageLast[id]))
		}
	}
}

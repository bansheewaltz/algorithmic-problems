package main

import (
	"bufio"
	"fmt"
	"os"
)

var in = bufio.NewReaderSize(os.Stdin, 1024*1024)
var out = bufio.NewWriterSize(os.Stdout, 1024*1024)

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func main() {
	var testCnt int
	fmt.Fscan(in, &testCnt)
	for t := 1; t <= testCnt; t++ {
		solve()
	}
	out.Flush()
}

func solve() {
	var n, k, m int
	fmt.Fscan(in, &n, &k, &m)

	const e = 30
	boxes := [e]int{}
	for i := 0; i < m; i++ {
		var w int
		fmt.Fscan(in, &w)
		boxes[w]++
	}

	rides := 0
	for boxes != [e]int{} {
		rides++
		for i := 0; i < n; i++ {
			wLeft := k
			for i := e - 1; i >= 0; i-- {
				w := 1 << i
				cnt := min(wLeft/w, boxes[i])
				boxes[i] -= cnt
				wLeft -= w * cnt
			}
			if wLeft == k {
				break
			}
		}
	}

	fmt.Fprintln(out, rides)
}

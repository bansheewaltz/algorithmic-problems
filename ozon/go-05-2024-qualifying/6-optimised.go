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

	biggest := e - 1
	rides := 0
	for boxes != [e]int{} {
		rides++
		wLeft := k
		for i := biggest; i >= 0; i-- {
			if boxes[i] == 0 {
				if biggest == i {
					biggest = i - 1
				}
				continue
			}
			w := 1 << i
			cnt := min(wLeft/w, boxes[i])
			boxes[i] -= cnt
			wLeft -= w * cnt
		}
		if wLeft == k {
			break
		}
	}

	fmt.Fprintln(out, (rides+n-1)/n)
}

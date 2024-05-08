package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

var in = bufio.NewReader(os.Stdin)
var out = bufio.NewWriter(os.Stdout)

func main() {
	solve()
	out.Flush()
}

func solve() {
	var testCnt int
	fmt.Fscan(in, &testCnt)

	for t := 1; t <= testCnt; t++ {
		var n int
		fmt.Fscan(in, &n)

		times := make([]int, n)
		for i := 0; i < n; i++ {
			fmt.Fscan(in, &times[i])
		}

		timesSorted := append([]int(nil), times...)
		sort.Ints(timesSorted)

		places := map[int]int{timesSorted[0]: 1}
		for i := 1; i < n; i++ {
			if timesSorted[i]-timesSorted[i-1] <= 1 {
				places[timesSorted[i]] = places[timesSorted[i-1]]
			} else {
				places[timesSorted[i]] = i + 1
			}
		}

		for _, t := range times {
			fmt.Fprint(out, places[t], " ")
		}
		fmt.Fprintln(out)
	}
}

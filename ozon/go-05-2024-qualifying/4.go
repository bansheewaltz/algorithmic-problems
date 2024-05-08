package main

import (
	"bufio"
	"fmt"
	"os"
)

func max(a, b float64) float64 {
	if a > b {
		return a
	}
	return b
}

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
	const n int = 3
	const m int = 6

	const rub, usd, eur int = 0, 1, 2
	const rubusd, rubeur int = 0, 1
	const usdrub, usdeur int = 2, 3
	const eurrub, eurusd int = 4, 5

	rates := [3][6]float64{}
	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			var a, b int
			fmt.Fscan(in, &a, &b)
			rates[i][j] = float64(b) / float64(a)
		}
	}

	maxusd := 0.0
	visited := [3]bool{}
	var maxConvert func(curr int, amount float64)
	maxConvert = func(curr int, amount float64) {
		if curr == usd {
			maxusd = max(maxusd, amount)
		}
		if visited == [3]bool{true, true, true} {
			return
		}
		for i, rate := range rates { // iterate banks
			if visited[i] {
				continue
			}
			visited[i] = true
			switch curr {
			case rub:
				maxConvert(usd, rate[rubusd]*amount)
				maxConvert(eur, rate[rubeur]*amount)
			case usd:
				maxConvert(rub, rate[usdrub]*amount)
				maxConvert(eur, rate[usdeur]*amount)
			case eur:
				maxConvert(rub, rate[eurrub]*amount)
				maxConvert(usd, rate[eurusd]*amount)
			}
			visited[i] = false
		}
	}

	maxConvert(rub, 1)
	fmt.Fprintln(out, maxusd)
}

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
	info := [3][6]float64{}
	for bank := 0; bank < 3; bank++ {
		for pair := 0; pair < 6; pair++ {
			var priceFrom, priceTo int
			fmt.Fscan(in, &priceFrom, &priceTo)
			info[bank][pair] = float64(priceTo) / float64(priceFrom)
		}
	}

	maxusd := 0.0
	visited := [3]int{}
	var maxConvert func(from int, amount float64)
	maxConvert = func(from int, amount float64) {
		if from == 1 && maxusd < amount {
			maxusd = amount
		}
		if visited == [3]int{1, 1, 1} {
			return
		}
		for i, bank := range info {
			if visited[i] == 1 {
				continue
			}
			visited[i] = 1
			for pair := from * 2; pair <= from*2+1; pair++ {
				to := pair % 2
				if to >= from {
					to++
				}
				maxConvert(to, amount*bank[pair])
			}
			visited[i] = 0
		}
	}

	maxConvert(0, 1)
	fmt.Fprintln(out, maxusd)
}

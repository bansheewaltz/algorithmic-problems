package main

import (
	"bufio"
	"fmt"
	"os"
	"reflect"
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

const bankCnt = 3
const currencyCnt = 3
const (
	rub = iota
	usd
	eur
)

func solve() {
	const pairCnt = currencyCnt - 1
	const pairCntTotal = currencyCnt * (currencyCnt - 1)

	info := [bankCnt][currencyCnt][currencyCnt]float64{}
	for bank := 0; bank < bankCnt; bank++ {
		for j := 0; j < pairCntTotal; j++ {
			from := j / pairCnt
			to := j % pairCnt
			if to >= from {
				to++
			}
			var priceFrom, priceTo int
			fmt.Fscan(in, &priceFrom, &priceTo)
			info[bank][from][to] = float64(priceTo) / float64(priceFrom)
		}
	}

	maxusd := 0.0
	visited := make([]bool, bankCnt)
	visitedAll := make([]bool, bankCnt)
	for i := 0; i < bankCnt; i++ {
		visitedAll[i] = true
	}

	var maxConvert func(int, float64)
	maxConvert = func(from int, amount float64) {
		if from == usd {
			maxusd = max(maxusd, amount)
		}
		if reflect.DeepEqual(visited, visitedAll) {
			return
		}
		for i, bank := range info {
			if visited[i] {
				continue
			}
			visited[i] = true
			for to := 0; to < currencyCnt; to++ {
				if to != from {
					maxConvert(to, amount*bank[from][to])
				}
			}
			visited[i] = false
		}
	}

	maxConvert(rub, 1)
	fmt.Fprintln(out, maxusd)
}

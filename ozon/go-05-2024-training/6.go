package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strings"
)

var in = bufio.NewReaderSize(os.Stdin, 1024*1024)
var out = bufio.NewWriterSize(os.Stdout, 1024*1024)

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func main() {
	solve()
	out.Flush()
}

func solve() {
	var friendCnt, cardCnt int
	fmt.Fscan(in, &friendCnt, &cardCnt)

	friendCards := make([]struct{ cardCnt, idx int }, friendCnt)
	for i := 0; i < friendCnt; i++ {
		fmt.Fscan(in, &friendCards[i].cardCnt)
		friendCards[i].idx = i
	}

	sort.Slice(friendCards, func(i, j int) bool {
		return friendCards[i].cardCnt < friendCards[j].cardCnt
	})

	gifts := make([]int, friendCnt)
	giftPrev := 0
	for _, v := range friendCards {
		gift := max(v.cardCnt, giftPrev) + 1
		gifts[v.idx] = gift
		giftPrev = gift
	}

	if giftPrev > cardCnt {
		fmt.Fprintln(out, -1)
	} else {
		fmt.Fprintln(out, strings.Trim(fmt.Sprint(gifts), "[]"))
	}
}

package main

import (
	"bufio"
	"container/heap"
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

type Car struct{ cnt, cap int }
type CarHeap []Car

func (h CarHeap) Len() int           { return len(h) }
func (h CarHeap) Less(i, j int) bool { return h[i].cap > h[j].cap }
func (h CarHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *CarHeap) Push(x any)        { *h = append(*h, x.(Car)) }
func (h *CarHeap) Pop() any {
	old := *h
	n := len(old)
	item := old[n-1]
	*h = old[:n-1]
	return item
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

	h := &CarHeap{}
	heap.Init(h)
	carCnt := 0
	for i := e - 1; i >= 0; i-- {
		if boxes[i] == 0 {
			continue
		}
		w := 1 << i
		for boxes[i] > 0 && h.Len() > 0 {
			top := (*h)[0]
			perCar := top.cap / w
			if perCar == 0 {
				break
			}
			heap.Pop(h)
			boxesCnt := min(perCar*top.cnt, boxes[i])
			boxes[i] -= boxesCnt
			carMaxCnt := boxesCnt / perCar
			heap.Push(h, Car{carMaxCnt, top.cap - perCar*w})
			boxesCnt -= carMaxCnt * perCar
			top.cnt -= carMaxCnt
			if boxesCnt > 0 {
				heap.Push(h, Car{1, top.cap - boxesCnt*w})
				top.cnt -= 1
			}
			if top.cnt > 0 {
				heap.Push(h, top)
			}
		}
		if boxes[i] > 0 {
			perCar := k / w
			if carMaxCnt := boxes[i] / perCar; carMaxCnt > 0 {
				heap.Push(h, Car{carMaxCnt, k - perCar*w})
				carCnt += carMaxCnt
				boxes[i] -= carMaxCnt * perCar
			}
			if boxes[i] > 0 {
				heap.Push(h, Car{1, k - boxes[i]*w})
				carCnt++
				boxes[i] = 0
			}
		}
	}

	fmt.Fprintln(out, (carCnt+n-1)/n)
}

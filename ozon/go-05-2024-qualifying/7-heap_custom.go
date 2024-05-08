package main

import (
	"bufio"
	"container/heap"
	"fmt"
	"os"
	"sort"
)

type Truck struct {
	start int
	end   int
	idx   int
	cap   int
	used  int
}

var in = bufio.NewReader(os.Stdin)
var out = bufio.NewWriter(os.Stdout)

type TruckHeap []Truck

func (h TruckHeap) Len() int { return len(h) }
func (h TruckHeap) Less(i, j int) bool {
	if h[i].start == h[j].start {
		return h[i].idx < h[j].idx
	}
	return h[i].start < h[j].start
}
func (h TruckHeap) Swap(i, j int) {
	h[i], h[j] = h[j], h[i]
}
func (h *TruckHeap) Push(x any) {
	*h = append(*h, x.(Truck))
}
func (h *TruckHeap) Pop() any {
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
	var n int
	fmt.Fscan(in, &n)
	packages := make([]struct{ idx, time int }, n)
	for i := 0; i < n; i++ {
		fmt.Fscan(in, &packages[i].time)
		packages[i].idx = i
	}
	sort.Slice(packages, func(i, j int) bool {
		return packages[i].time < packages[j].time
	})

	var m int
	fmt.Fscan(in, &m)
	trucks := make(TruckHeap, m)
	for i := 0; i < m; i++ {
		fmt.Fscan(in, &trucks[i].start, &trucks[i].end, &trucks[i].cap)
		trucks[i].idx = i
	}
	trucksPQ := &trucks
	heap.Init(trucksPQ)

	pkgTruck := make([]int, n)
	for _, pkg := range packages {
		for len(trucks) > 0 && (*trucksPQ)[0].end < pkg.time {
			heap.Pop(trucksPQ)
		}
		if len(trucks) == 0 || (*trucksPQ)[0].start > pkg.time {
			pkgTruck[pkg.idx] = -1
		} else {
			pkgTruck[pkg.idx] = (*trucksPQ)[0].idx + 1
			(*trucksPQ)[0].cap--
			if (*trucksPQ)[0].cap == 0 {
				heap.Pop(trucksPQ)
			}
		}
	}

	for _, v := range pkgTruck {
		fmt.Fprint(out, v, " ")
	}
	fmt.Fprintln(out)
}

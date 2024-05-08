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
	packages := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Fscan(in, &packages[i])
	}

	var m int
	fmt.Fscan(in, &m)
	cars := make([]Truck, m)
	for i := 0; i < m; i++ {
		fmt.Fscan(in, &cars[i].start, &cars[i].end, &cars[i].cap)
		cars[i].idx = i
	}
	assignedTrucks := assignTrucks(packages, cars)
	for _, v := range assignedTrucks {
		fmt.Fprint(out, v, " ")
	}
	fmt.Fprintln(out)
}

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

func assignTrucks(arrivals []int, trucks []Truck) []int {
	n := len(arrivals)
	result := make([]int, n)
	for i := range result {
		result[i] = -1
	}

	orderIndices := make([]int, n)
	for i := range orderIndices {
		orderIndices[i] = i
	}

	sort.Slice(orderIndices, func(i, j int) bool { return arrivals[orderIndices[i]] < arrivals[orderIndices[j]] })
	sort.Slice(trucks, func(i, j int) bool { return trucks[i].start < trucks[j].start })

	available := &TruckHeap{}
	heap.Init(available)

	t := 0
	for _, i := range orderIndices {
		arrival := arrivals[i]
		for t < len(trucks) && trucks[t].start <= arrival {
			heap.Push(available, trucks[t])
			t++
		}

		for available.Len() > 0 && (*available)[0].end < arrival {
			heap.Pop(available)
		}

		if available.Len() > 0 {
			truck := heap.Pop(available).(Truck)
			result[i] = truck.idx + 1
			truck.used++
			if truck.used < truck.cap {
				heap.Push(available, truck)
			}
		}
	}

	return result
}

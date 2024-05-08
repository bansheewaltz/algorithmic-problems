package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"sync"
)

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
	var wg sync.WaitGroup

	var n int
	fmt.Fscan(in, &n)
	pkgs := make([]struct{ idx, time int }, n)
	for i := 0; i < n; i++ {
		fmt.Fscan(in, &pkgs[i].time)
		pkgs[i].idx = i
	}
	wg.Add(1)
	goSortPkgs := func() {
		sort.Slice(pkgs, func(i, j int) bool {
			return pkgs[i].time < pkgs[j].time
		})
		wg.Done()
	}
	go goSortPkgs()

	var m int
	fmt.Fscan(in, &m)
	cars := make([]struct{ idx, start, end, cap int }, m)
	for i := 0; i < m; i++ {
		fmt.Fscan(in, &cars[i].start, &cars[i].end, &cars[i].cap)
		cars[i].idx = i
	}
	wg.Add(1)
	goSortCars := func() {
		sort.Slice(cars, func(i, j int) bool {
			if cars[i].start == cars[j].start {
				return cars[i].idx < cars[j].idx
			}
			return cars[i].start < cars[j].start
		})
		wg.Done()
	}
	go goSortCars()

	wg.Wait()
	car := 0
	pkgCars := make([]int, n)
	for _, pkg := range pkgs {
		for car < m && (pkg.time > cars[car].end || cars[car].cap == 0) {
			car++
		}
		if car >= m || car < m && pkg.time < cars[car].start {
			pkgCars[pkg.idx] = -1
		} else {
			pkgCars[pkg.idx] = cars[car].idx + 1
			cars[car].cap--
		}
	}

	for _, v := range pkgCars {
		fmt.Fprint(out, v, " ")
	}
	fmt.Fprintln(out)
}

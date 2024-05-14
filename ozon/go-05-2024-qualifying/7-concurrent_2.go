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
	var n int
	fmt.Fscan(in, &n)
	pkgs := make([]struct{ idx, time int }, n)
	for i := 0; i < n; i++ {
		fmt.Fscan(in, &pkgs[i].time)
		pkgs[i].idx = i
	}

	var wg sync.WaitGroup
	wg.Add(1)
	go func() {
		defer wg.Done()
		sort.Slice(pkgs, func(i, j int) bool {
			return pkgs[i].time < pkgs[j].time
		})
	}()

	var m int
	fmt.Fscan(in, &m)
	cars := make([]struct{ idx, start, end, cap int }, m)
	for i := 0; i < m; i++ {
		fmt.Fscan(in, &cars[i].start, &cars[i].end, &cars[i].cap)
		cars[i].idx = i
	}
	sort.Slice(cars, func(i, j int) bool {
		if cars[i].start == cars[j].start {
			return cars[i].idx < cars[j].idx
		}
		return cars[i].start < cars[j].start
	})

	wg.Wait()
	car_i := 0
	pkgCars := make([]int, n)
	for _, pkg := range pkgs {
		for car_i < m && (pkg.time > cars[car_i].end || cars[car_i].cap == 0) {
			car_i++
		}
		if car_i >= m || car_i < m && pkg.time < cars[car_i].start {
			pkgCars[pkg.idx] = -1
		} else {
			pkgCars[pkg.idx] = cars[car_i].idx + 1
			cars[car_i].cap--
		}
	}

	for _, v := range pkgCars {
		fmt.Fprint(out, v, " ")
	}
	fmt.Fprintln(out)
}

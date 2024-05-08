package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strings"
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

	car := 0
	packageCars := make([]int, n)
	for _, pkg := range packages {
		for car < m && (pkg.time > cars[car].end || cars[car].cap == 0) {
			car++
		}
		if car >= m || car < m && pkg.time < cars[car].start {
			packageCars[pkg.idx] = -1
		} else {
			packageCars[pkg.idx] = cars[car].idx + 1
			cars[car].cap--
		}
	}

	fmt.Fprintln(out, strings.Trim(fmt.Sprint(packageCars), "[]"))
}

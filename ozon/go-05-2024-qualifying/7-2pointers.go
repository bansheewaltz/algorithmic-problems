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
	var pkgCnt int
	fmt.Fscan(in, &pkgCnt)
	pkgs := make([]struct{ idx, time int }, pkgCnt)
	for i := 0; i < pkgCnt; i++ {
		fmt.Fscan(in, &pkgs[i].time)
		pkgs[i].idx = i
	}
	pkgQ := pkgs
	sort.Slice(pkgQ, func(i, j int) bool {
		return pkgQ[i].time < pkgQ[j].time
	})

	var carCnt int
	fmt.Fscan(in, &carCnt)
	cars := make([]struct{ idx, start, end, cap int }, carCnt)
	for i := 0; i < carCnt; i++ {
		fmt.Fscan(in, &cars[i].start, &cars[i].end, &cars[i].cap)
		cars[i].idx = i
	}
	carQ := cars
	sort.Slice(carQ, func(i, j int) bool {
		if carQ[i].start == carQ[j].start {
			return carQ[i].idx < carQ[j].idx
		}
		return carQ[i].start < carQ[j].start
	})

	pkgCars := make([]int, pkgCnt)
	p := 0
	c := 0
	for p < pkgCnt || c < carCnt {
		if p < pkgCnt && c < carCnt {
			if carQ[c].start <= pkgQ[p].time && pkgQ[p].time <= carQ[c].end {
				pkgCars[pkgQ[p].idx] = carQ[c].idx + 1
				p++
				carQ[c].cap--
				if carQ[c].cap == 0 {
					c++
				}
			} else if pkgQ[p].time < carQ[c].start {
				pkgCars[pkgQ[p].idx] = -1
				p++
			} else if pkgQ[p].time > carQ[c].end {
				c++
			}
		} else {
			if p < pkgCnt {
				pkgCars[pkgQ[p].idx] = -1
				p++
			} else {
				c++
			}
		}
	}

	fmt.Fprintln(out, strings.Trim(fmt.Sprint(pkgCars), "[]"))
}

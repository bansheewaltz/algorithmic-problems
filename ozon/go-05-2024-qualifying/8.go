package main

import (
	"bufio"
	"fmt"
	"os"
)

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

var in = bufio.NewReader(os.Stdin)
var out = bufio.NewWriter(os.Stdout)

func main() {
	var testCnt int
	fmt.Fscanln(in, &testCnt)
	for t := 1; t <= testCnt; t++ {
		solve()
	}
	out.Flush()
}

func solve() {
	var n, m int
	fmt.Fscanln(in, &n, &m)
	const r int = 10
	city := make([][][r]int, m)
	for i := range city {
		city[i] = make([][r]int, n)
	}

	var k int
	fmt.Fscanln(in, &k)
	for i := 0; i < k; i++ {
		var count int
		fmt.Fscanln(in, &count)
		for j := 0; j < count; j++ {
			var x, y int
			fmt.Fscanln(in, &x, &y)
			city[y-1][x-1][i] = 1
		}
	}

	minArea := n * m
	for xi := 0; xi < n; xi++ {
		yr := make([]map[int]int, m)
		for yi := 0; yi < m; yi++ {
			yr[yi] = make(map[int]int, k)
		}
		for xj := xi; xj < n; xj++ {
			for yi := 0; yi < m; yi++ {
				for ki := 0; ki < k; ki++ {
					if city[yi][xj][ki] > 0 {
						yr[yi][ki] += city[yi][xj][ki]
					}
				}
			}
			yi, yj := 0, 0
			wr := make(map[int]int, 0)
			for yj < m {
				for ki := 0; ki < k; ki++ {
					if yr[yj][ki] > 0 {
						wr[ki] += yr[yj][ki]
					}
				}
				for len(wr) == k && yi < m {
					minArea = min(minArea, (xj-xi+1)*(yj-yi+1))
					for ki := 0; ki < k; ki++ {
						wr[ki] -= yr[yi][ki]
						if wr[ki] == 0 {
							delete(wr, ki)
						}
					}
					yi++
				}
				yj++
			}
		}
	}

	fmt.Fprintln(out, minArea)
}

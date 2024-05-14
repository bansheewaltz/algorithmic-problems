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
func max(a, b int) int {
	if a > b {
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
	d1 := min(n, m) // horizontal
	d2 := max(n, m) // vertical
	var k int
	fmt.Fscanln(in, &k)
	city := make([][][]int, d2)
	for i := range city {
		city[i] = make([][]int, d1)
		for j := 0; j < d1; j++ {
			city[i][j] = make([]int, k)
		}
	}

	for i := 0; i < k; i++ {
		var count int
		fmt.Fscanln(in, &count)
		for j := 0; j < count; j++ {
			var x, y int
			fmt.Fscanln(in, &x, &y)
			if n == d1 {
				city[y-1][x-1][i] = 1
			} else {
				city[x-1][y-1][i] = 1
			}
		}
	}

	minArea := d1 * d2
	for d1i := 0; d1i < d1; d1i++ {
		d2r := make([]map[int]int, d2) // resources by row
		for d2i := 0; d2i < d2; d2i++ {
			d2r[d2i] = make(map[int]int, k)
		}
		for d1j := d1i; d1j < d1; d1j++ {
			wr := make(map[int]int, 0) // resources by rectange area
			for d2i, d2j := 0, 0; d2j < d2; d2j++ {
				for ki := 0; ki < k; ki++ {
					if d2r[d2j][ki] > 0 || city[d2j][d1j][ki] > 0 {
						d2r[d2j][ki] += city[d2j][d1j][ki]
						wr[ki] += d2r[d2j][ki]
					}
				}
				for ; len(wr) == k && d2i < d2; d2i++ {
					minArea = min(minArea, (d1j-d1i+1)*(d2j-d2i+1))
					for ki := 0; ki < k; ki++ {
						if d2r[d2i][ki] > 0 {
							wr[ki] -= d2r[d2i][ki]
							if wr[ki] == 0 {
								delete(wr, ki)
							}
						}
					}
				}
			}
		}
	}

	fmt.Fprintln(out, minArea)
}

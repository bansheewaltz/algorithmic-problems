package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

var in = bufio.NewReaderSize(os.Stdin, 1024*1024)
var out = bufio.NewWriterSize(os.Stdout, 1024*1024)

func main() {
	solve()
	out.Flush()
}

func solve() {
	var testCnt int
	fmt.Fscan(in, &testCnt)

	for t := 1; t <= testCnt; t++ {
		var winCnt, ptCnt int
		fmt.Fscan(in, &winCnt, &ptCnt)

		times := make([]struct{ time, idx int }, ptCnt)
		for i := 0; i < ptCnt; i++ {
			fmt.Fscan(in, &times[i].time)
			times[i].idx = i
		}
		sort.Slice(times, func(i, j int) bool {
			return times[i].time < times[j].time
		})

		timesMap := make(map[int]int, ptCnt)
		shifts := make([]byte, ptCnt)
		err := false
		for _, v := range times {
			switch {
			case 1 <= v.time-1 && timesMap[v.time-1] == 0:
				timesMap[v.time-1]++
				shifts[v.idx] = '-'
			case timesMap[v.time] == 0:
				timesMap[v.time]++
				shifts[v.idx] = '0'
			case v.time+1 <= winCnt && timesMap[v.time+1] == 0:
				timesMap[v.time+1]++
				shifts[v.idx] = '+'
			default:
				err = true
				break
			}
		}

		if err {
			fmt.Fprintln(out, "x")
		} else {
			fmt.Fprintln(out, string(shifts))
		}
	}
}

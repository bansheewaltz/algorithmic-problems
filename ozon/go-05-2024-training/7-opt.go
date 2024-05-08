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
	var testCnt int
	fmt.Fscan(in, &testCnt)
	for t := 1; t <= testCnt; t++ {
		solve()
	}
	out.Flush()
}

func solve() {
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

	timetable := [3e5 + 1]bool{}
	shifts := make([]byte, ptCnt)
	isPossible := true
	for _, v := range times {
		switch {
		case 1 <= v.time-1 && !timetable[v.time-1]:
			timetable[v.time-1] = true
			shifts[v.idx] = '-'
		case !timetable[v.time]:
			timetable[v.time] = true
			shifts[v.idx] = '0'
		case v.time+1 <= winCnt && !timetable[v.time+1]:
			timetable[v.time+1] = true
			shifts[v.idx] = '+'
		default:
			isPossible = false
			break
		}
	}

	if !isPossible {
		fmt.Fprintln(out, "x")
	} else {
		fmt.Fprintln(out, string(shifts))
	}
}

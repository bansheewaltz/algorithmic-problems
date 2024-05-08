package main

import (
	"bufio"
	"fmt"
	"os"
)

var in = bufio.NewReaderSize(os.Stdin, 1024*1024)
var out = bufio.NewWriterSize(os.Stdout, 1024*1024)

func main() {
	var testCnt int
	fmt.Fscanln(in, &testCnt)
	for t := 1; t <= testCnt; t++ {
		solve()
	}
	out.Flush()
}

func solve() {
	var n int
	fmt.Fscanln(in, &n)
	var queue string
	fmt.Fscanln(in, &queue)

	f_cnt := 0
	s_cnt := 0
	for _, v := range queue {
		switch v {
		case 'X':
			f_cnt++
		case 'Z':
			s_cnt++
		}
	}
	y_f_left := n/2 - f_cnt
	y_s_left := n/2 - s_cnt

	var x, y_f, y_s, z int
	for _, v := range queue {
		switch v {
		case 'X':
			x++
		case 'Y':
			if y_f_left > 0 {
				y_f++
				y_f_left--
			} else {
				y_s++
				y_s_left--
			}
			if x > 0 && y_s > 0 {
				x--
				y_s--
			}
		case 'Z':
			switch {
			case y_f > 0:
				y_f--
			case x > 0:
				x--
			default:
				z++
				break
			}
		}
	}

	if x > 0 || y_f > 0 || y_s > 0 || z > 0 {
		fmt.Fprintln(out, "No")
	} else {
		fmt.Fprintln(out, "Yes")
	}
}

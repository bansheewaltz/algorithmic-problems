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

	var x, y, z, xy, xyxz int // omit yz as it is not optimal to destroy it
	for _, v := range queue {
		switch v {
		case 'X':
			x++
		case 'Y':
			switch {
			case x > 0:
				x--
				xy++
			case xyxz > 0:
				xyxz--
				// yz++
				xy++
				x++
			default:
				y++
			}
		case 'Z':
			switch {
			case y > 0:
				y--
			case x > 0:
				x--
				if xy > 0 {
					xy--
					xyxz++
				}
			case xy > 0:
				xy--
				// yz++
				x++
			case xyxz > 0:
				xyxz--
				// yz++
				// xz++
				x++
			default:
				z++
				break
			}
		}
	}

	if x > 0 || y > 0 || z > 0 {
		fmt.Fprintln(out, "No")
	} else {
		fmt.Fprintln(out, "Yes")
	}
}

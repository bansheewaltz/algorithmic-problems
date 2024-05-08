package main

import (
	"bufio"
	"fmt"
	"os"
)

var in = bufio.NewReaderSize(os.Stdin, 1024*1024)
var out = bufio.NewWriterSize(os.Stdout, 1024*1024)

func main() {
	Run(in, out)
	out.Flush()
}

func Run(in *bufio.Reader, out *bufio.Writer) {
	var t int
	fmt.Fscanln(in, &t)

	for i := 0; i < t; i++ {
		var n int
		fmt.Fscanln(in, &n)
		var events string
		fmt.Fscanln(in, &events)

		if !isEventsCorrect(events) {
			fmt.Fprintln(out, "No")
			continue
		}
		fmt.Fprintln(out, "Yes")
	}
}

func isEventsCorrect(events string) bool {
	var x, y, xy, xyxz int
	for i := 0; i < len(events); i++ {
		switch events[i] {
		case 'X':
			x++

		case 'Y':
			switch {
			case x > 0:
				x--
				xy++
			case xyxz > 0:
				xyxz--
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
					xyxz++
					xy--
				}
			case xy > 0:
				xy--
				x++
			case xyxz > 0:
				xyxz--
				x++
			default:
				return false
			}
		}
	}

	if x == 0 && y == 0 {
		return true
	}
	return false
}

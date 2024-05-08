package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	var in *bufio.Reader
	var out *bufio.Writer
	in = bufio.NewReader(os.Stdin)
	out = bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var sticker string
	fmt.Fscanln(in, &sticker)
	var cnt int
	fmt.Fscan(in, &cnt)
	for cnt > 0 {
		var a, b int
		var newsticker string
		fmt.Fscan(in, &a, &b, &newsticker)
		for i := a - 1; i <= b-1; i++ {
			sticker = sticker[:i] + string(newsticker[i-a+1]) + sticker[i+1:]
		}
		cnt--
	}
	fmt.Fprintln(out, sticker)
}

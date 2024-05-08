package main

import (
	"bufio"
	"fmt"
	"os"
)

var in = bufio.NewReader(os.Stdin)
var out = bufio.NewWriter(os.Stdout)

func main() {
	solve()
	out.Flush()
}

func solve() {
	var sticker string
	fmt.Fscanln(in, &sticker)
	sticker_bs := []byte(sticker)

	var cnt int
	fmt.Fscan(in, &cnt)

	for i := 1; i <= cnt; i++ {
		var a, b int
		var newsticker string
		fmt.Fscan(in, &a, &b, &newsticker)
		newsticker_bs := []byte(newsticker)

		for i := a - 1; i <= b-1; i++ {
			sticker_bs[i] = newsticker_bs[i-a+1]
		}
	}

	sticker_final := string(sticker_bs)
	fmt.Fprintln(out, sticker_final)
}

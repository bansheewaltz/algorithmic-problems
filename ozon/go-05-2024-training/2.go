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

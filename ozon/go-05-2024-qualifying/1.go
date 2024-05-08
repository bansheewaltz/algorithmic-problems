package main

import (
	"bufio"
	"fmt"
	"os"
)

var in = bufio.NewReaderSize(os.Stdin, 1024*1024)
var out = bufio.NewWriterSize(os.Stdout, 1024*1024)

func main() {
	solve()
	out.Flush()
}

func solve() {
	var a, b int
	fmt.Fscan(in, &a, &b)
	fmt.Fprintln(out, a-b)
}

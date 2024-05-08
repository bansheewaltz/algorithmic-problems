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
	var n, b, r, black int
	fmt.Fscanln(in, &n, &b, &r, &black)
	r += b     // count -> ending idx
	black -= 1 // 1-indexing -> 0-indexing

	words := make([]string, n)
	for i := 0; i < n; i++ {
		fmt.Fscanln(in, &words[i])
	}

	const maxWordLen = 10
	const maxSubwordCnt = (2 + maxWordLen) * (maxWordLen - 1) / 2
	wordsFreq := make(map[string]int, maxSubwordCnt*r)

	addSubstrings := func(word string, idx int) {
		isDup := make(map[string]int, maxSubwordCnt)
		for len_ := 1; len_ < len(word); len_++ {
			for i := 0; i <= len(word)-len_; i++ {
				subword := word[i : i+len_]
				switch {
				case isDup[subword] > 0:
					continue
				case idx < b:
					wordsFreq[subword]++
				case idx < r:
					if wordsFreq[subword] > 0 {
						wordsFreq[subword]--
					}
				case idx == black:
					delete(wordsFreq, subword)
				}
				isDup[subword] = 1
			}
		}
	}

	for i := 0; i < r; i++ {
		addSubstrings(words[i], i)
	}
	addSubstrings(words[black], black)
	for _, v := range words {
		delete(wordsFreq, v)
	}

	maxWord := "tkhapjiabb"
	maxFreq := 0
	for k, v := range wordsFreq {
		if maxFreq < v || maxFreq == v && len(k) > len(maxWord) {
			maxWord, maxFreq = k, v
		}
	}
	fmt.Println(maxWord, maxFreq)
}

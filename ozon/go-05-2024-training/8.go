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

	const maxWordCnt = (1 + 9) * 10 / 2
	wordsFreq := make(map[string]int, maxWordCnt*n)

	addSubstrings := func(word string, idx int) {
		wordFreq := make(map[string]int, maxWordCnt)
		for len_ := 1; len_ < len(word); len_++ {
			for i := 0; i <= len(word)-len_; i++ {
				switch {
				case idx == black:
					delete(wordsFreq, word[i:i+len_])
				case idx < b:
					wordFreq[word[i:i+len_]]++
				case idx < r:
					wordFreq[word[i:i+len_]]--
				}
			}
		}
		for k, v := range wordFreq {
			if v > 0 {
				wordsFreq[k]++
			} else if wordsFreq[k] > 0 {
				wordsFreq[k]--
			}
		}
	}

	for i, v := range words {
		if i != black {
			addSubstrings(v, i)
		}
	}
	addSubstrings(words[black], black)
	for _, v := range words {
		delete(wordsFreq, v)
	}

	maxWord := "tkhapjiabb"
	maxFreq := 0
	for k, v := range wordsFreq {
		if maxFreq < v {
			maxFreq = v
			maxWord = k
		}
	}
	fmt.Println(maxWord, maxFreq)
}

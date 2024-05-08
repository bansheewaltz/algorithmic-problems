package main

import (
	"bufio"
	"encoding/json"
	"fmt"
	"log"
	"os"
	"strings"
)

var in = bufio.NewReader(os.Stdin)
var out = bufio.NewWriter(os.Stdout)

func main() {
	solve()
	out.Flush()
}

func solve() {
	var testCnt int
	fmt.Fscanln(in, &testCnt)

	for t := 0; t < testCnt; t++ {
		var lineCnt int
		fmt.Fscanln(in, &lineCnt)

		jsonBytes := []byte{}
		for i := 0; i < lineCnt; i++ {
			line, _ := in.ReadBytes('\n')
			jsonBytes = append(jsonBytes, line...)
		}

		var jsonData map[string]interface{}
		if err := json.Unmarshal(jsonBytes, &jsonData); err != nil {
			if e, ok := err.(*json.SyntaxError); ok {
				log.Printf("syntax error at byte offset %d", e.Offset)
			}
			log.Printf("json data: %q", jsonBytes)
			panic(err)
		}

		fmt.Fprintln(out, countInfected(jsonData, false))
	}
}

func countInfected(jsonData map[string]interface{}, isInfected bool) int {
	infectedCnt := 0
	if files, ok := jsonData["files"].([]interface{}); ok {
		for _, file := range files {
			if strings.HasSuffix(file.(string), ".hack") {
				isInfected = true
				break
			}
		}
		if isInfected {
			infectedCnt += len(files)
		}
	}
	if folders, ok := jsonData["folders"].([]interface{}); ok {
		for _, folder := range folders {
			infectedCnt += countInfected(folder.(map[string]interface{}), isInfected)
		}
	}
	return infectedCnt
}

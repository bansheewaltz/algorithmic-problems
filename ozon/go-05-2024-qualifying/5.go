package main

import (
	"bufio"
	"encoding/json"
	"fmt"
	"log"
	"os"
)

var in = bufio.NewReaderSize(os.Stdin, 1024*1024)
var out = bufio.NewWriterSize(os.Stdout, 1024*1024)

func main() {
	solve()
	out.Flush()
}

func solve() {
	var fileCnt int
	fmt.Fscanln(in, &fileCnt)
	jsonPrettyList := make([]any, fileCnt)
	for i := 0; i < fileCnt; i++ {

		var n int
		fmt.Fscanln(in, &n)
		jsonBytes := []byte{}
		for i := 0; i < n; i++ {
			line, _ := in.ReadBytes('\n')
			jsonBytes = append(jsonBytes, line...)
		}

		var jsonData any
		if err := json.Unmarshal(jsonBytes, &jsonData); err != nil {
			if e, ok := err.(*json.SyntaxError); ok {
				log.Printf("syntax error at byte offset %d", e.Offset)
			}
			panic(err)
		}

		jsonPrettyList[i] = jsonPrettify(jsonData)
	}

	result, _ := json.Marshal(jsonPrettyList)
	fmt.Fprint(out, string(result))
}

func jsonPrettify(jsonData any) any {
	switch jsonData.(type) {
	case map[string]any:
		jsonObject := jsonData.(map[string]any)
		mapPretty := make(map[string]any)
		for key, val := range jsonObject {
			if valPretty := jsonPrettify(val); valPretty != nil {
				mapPretty[key] = valPretty
			}
		}
		if len(mapPretty) == 0 {
			return nil
		}
		return mapPretty
	case []any:
		jsonArray := jsonData.([]any)
		var slicePretty []any
		for _, val := range jsonArray {
			if valPretty := jsonPrettify(val); valPretty != nil {
				slicePretty = append(slicePretty, valPretty)
			}
		}
		if len(slicePretty) == 0 {
			return nil
		}
		return slicePretty
	default:
		return jsonData
	}
}

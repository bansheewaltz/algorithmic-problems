package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

var in = bufio.NewReader(os.Stdin)
var out = bufio.NewWriter(os.Stdout)

func main() {
	var testCnt int
	fmt.Fscan(in, &testCnt)
	for t := 1; t <= testCnt; t++ {
		solve()
	}
	out.Flush()
}

func solve() {
	var n int
	fmt.Fscan(in, &n)
	c := make([]int, n)
	for i := range c {
		fmt.Fscan(in, &c[i])
	}

	var m int
	fmt.Fscan(in, &m)
	edges := make([]Edge, m, n+m)
	for i := range edges {
		fmt.Fscan(in, &edges[i].u, &edges[i].v, &edges[i].w)
	}
	for i, w := range c {
		edges = append(edges, Edge{0, i + 1, w})
	}

	fmt.Fprintln(out, getMstCost(n+m+1, edges))
}

func getMstCost(e int, edges []Edge) int {
	sort.Slice(edges, func(i, j int) bool {
		return edges[i].w < edges[j].w
	})
	mstCost := 0
	s := NewDisjointSetUnion(e)
	for _, edge := range edges {
		if s.Find(edge.u) != s.Find(edge.v) {
			s.Union(edge.u, edge.v)
			mstCost += edge.w
		}
	}
	return mstCost
}

type Edge struct {
	u, v, w int
}

type DisjointSetUnion struct {
	root, rank []int
}

func NewDisjointSetUnion(size int) *DisjointSetUnion {
	root := make([]int, size)
	rank := make([]int, size)
	for i := range root {
		root[i] = i
		rank[i] = 1
	}
	return &DisjointSetUnion{root, rank}
}

func (s *DisjointSetUnion) Find(x int) int {
	if s.root[x] != x {
		s.root[x] = s.Find(s.root[x])
	}
	return s.root[x]
}

func (s *DisjointSetUnion) Union(a, b int) {
	rootA := s.Find(a)
	rootB := s.Find(b)
	if rootA != rootB {
		if s.rank[rootA] < s.rank[rootB] {
			rootA, rootB = rootB, rootA
		}
		s.root[rootB] = rootA
		s.rank[rootA] += s.rank[rootB]
	}
}

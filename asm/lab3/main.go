package main

import "fmt"

func countN(x int) int {
	count := 0
	for x != 0 {
		x = x / 10
		count++
	}
	return count - 1
}

func K(x, k, countN int) int {
	println(countN)
	for countN-k != 0 {
		x = x / 10
		countN--
	}
	return x % 10
}

func main() {
	x := 1234567890987654321
	k := 14

	fmt.Println(K(x, k, countN(x)))
	fmt.Println(1234 / 10)
}

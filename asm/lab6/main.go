package main

import "fmt"

func main() {
	// var arr = [11]int{12, -1, 1, 0, 7, 3, 0, -123, 55, 98, -29}
	// //fmt.Println(arr)
	// count := 0
	// for i := 0; i < len(arr); i++ {
	// 	if arr[i] < 0 {
	// 		count++
	// 	}
	// }
	// fmt.Println(count)

	a := 4
	b := 3
	c := 4

	if a > b && a > c {
		fmt.Println(a)
	} else if b > a && b > c {
		fmt.Println(b)
	} else if c > a && c > b {
		fmt.Println(c)
	}
}

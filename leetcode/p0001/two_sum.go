package p0001

import "sort"

func twoSum(nums []int, target int) []int {
	m := make(map[int]int)
	for k, v := range nums {
		if idx, ok := m[target-v]; ok {
			return []int{idx, k}
		}
		m[v] = k
	}
	return nil
}

type wrapper struct {
	Idx int
	Val int
}

type byValue []wrapper

func (a byValue) Len() int           { return len(a) }
func (a byValue) Less(i, j int) bool { return a[i].Val < a[j].Val }
func (a byValue) Swap(i, j int)      { a[i], a[j] = a[j], a[i] }

func twoSum2(nums []int, target int) []int {
	objs := make([]wrapper, 0, len(nums))
	for pos, num := range nums {
		objs = append(objs, wrapper{Idx: pos, Val: num})
	}
	sort.Sort(byValue(objs))

	low, high := 0, len(objs)-1
	for low < high {
		diff := target - objs[low].Val
		if diff > objs[high].Val {
			for low+1 < high && objs[low].Val == objs[low+1].Val {
				low++
			}
			low++
		} else if diff < objs[high].Val {
			for high-1 >= low && objs[high].Val == objs[high-1].Val {
				high--
			}
			high--
		} else {
			return []int{objs[low].Idx, objs[high].Idx}
		}
	}

	return nil
}

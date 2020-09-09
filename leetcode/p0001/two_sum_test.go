package p0001

import (
	"reflect"
	"testing"
)

func TestTwoSum(t *testing.T) {
	nums := []int{2, 7, 11, 15}
	target := 9
	t.Logf(" Input: nums = %v, target = %d\n", nums, target)
	actual := twoSum(nums, target)
	t.Logf(" Output: %v\n", actual)

	expected := []int{0, 1}
	if !reflect.DeepEqual(expected, actual) {
		t.Fatalf("twoSum expected %v, actual %v", expected, actual)
	}
}

func TestTwoSum2(t *testing.T) {
	nums := []int{2, 7, 11, 15}
	target := 9
	t.Logf(" Input: nums = %v, target = %d\n", nums, target)
	actual := twoSum2(nums, target)
	t.Logf(" Output: %v\n", actual)

	expected := []int{0, 1}
	if !reflect.DeepEqual(expected, actual) {
		t.Fatalf("twoSum expected %v, actual %v", expected, actual)
	}
}

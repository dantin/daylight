#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

class Object {
public:
    vector<int> nums;
    int target;
    Object (vector<int> pNums, int pTarget) : nums(pNums), target(pTarget) {}
};

class Node {
public:
    int val;
    size_t index;
    Node (int pVal, size_t pIndex) : val(pVal), index(pIndex) {}
};

bool compare(const Node &lhs, const Node &rhs)
{
    return lhs.val < rhs.val;
}

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        map<int, size_t> mapping;
        vector<int> result;
        for (size_t i = 0; i < numbers.size(); i++) {
            mapping[numbers[i]] = i;
        }

        for (size_t i = 0; i < numbers.size(); i++) {
            int searched = target - numbers[i];
            if (mapping.find(searched) != mapping.end() &&
                    i != mapping[searched]) {
                result.push_back(i+1);
                result.push_back(mapping[searched]+1);
                break;
            }
        }
        return result;
    }

    vector<int> twoSum1(vector<int>& numbers, int target) {
        vector<Node> elements;

        for (size_t i = 0; i < numbers.size(); i++) {
            elements.push_back(Node(numbers[i], i));
        }

        sort(elements.begin(), elements.end(), compare);

        size_t start = 0, end = numbers.size() - 1;
        vector<int> result;

        while (start < end) {
            int sum = elements[start].val + elements[end].val;
            if (sum == target) {
                result.push_back(elements[start].index + 1);
                if (elements[start].index < elements[end].index) {
                    result.push_back(elements[end].index + 1);
                } else {
                    result.insert(result.begin(), elements[end].index+1);
                }
                break;
            } else if (sum > target) {
                end--;
            } else {
                start++;
            }
        }

        return result;
    }
};

void print_nums(vector<int> nums)
{
    string s = "";

    cout << "[";
    for (size_t i = 0; i < nums.size(); ++i) {
        cout << s << nums[i];
        s = ", ";
    }
    cout << "]";
}

int main(int argc, char **argv) {
    vector<Object> inputs {
        Object(vector<int>{ 2, 7, 11, 15 }, 9),
    };

    for (size_t i = 0; i < inputs.size(); ++i) {
        vector<int> &nums = inputs[i].nums;
        int &target = inputs[i].target;

        cout << " Given nums: ";
        print_nums(nums);
        cout << ", target = " << target << endl;

        Solution solver;
        vector<int> idx = solver.twoSum(nums, target);
        cout << " Output: [" << idx[0] << ", " << idx[1] << ']' << endl;
        idx = solver.twoSum1(nums, target);
        cout << " Output: [" << idx[0] << ", " << idx[1] << ']' << endl;
    }

    return 0;
}

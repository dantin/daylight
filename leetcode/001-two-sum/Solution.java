import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class Solution {
    public int[] twoSum(int[] nums, int target) {
        Map<Integer, Integer> map = new HashMap<>();

        for (int i = 0; i < nums.length; i++) {
            if (map.containsKey(nums[i]) && i != map.get(nums[i])) {
                return new int[] {i, map.get(nums[i])};
            }
            map.put(target - nums[i], i);
        }

        return null;
    }

    public static void main(String[] args) {
        Input[] inputs = {
            new Input(new int[]{ 2, 7, 11, 15 }, 9),
        };

        for (int i = 0; i < inputs.length; i++) {
            int[] nums = inputs[i].nums;
            int target = inputs[i].target;

            System.out.print("\n Given nums: ");
            System.out.print(Arrays.toString(nums));
            System.out.printf(", target = %d\n", target);

            Solution solution = new Solution();
            int[] pairs = solution.twoSum(nums, target);
            System.out.print(" Output: ");
            System.out.printf("%s\n", (pairs == null) ? "Not found" : Arrays.toString(pairs));
        }
    }

    static class Input {
        int[] nums;
        int target;

        Input(int[] nums, int target) {
            this.nums = nums;
            this.target = target;
        }
    }
}

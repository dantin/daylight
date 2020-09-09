import java.util.Arrays;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static java.util.Comparator.*;

public class Solution {
    public int[] twoSum(int[] nums, int target) {
        List<Pair> objs = new ArrayList<>();
        for (int i = 0; i < nums.length; i++) {
            objs.add(new Pair(i, nums[i]));
        }
        //System.out.println(Arrays.toString(objs.toArray()));
        Collections.sort(objs);
        //System.out.println(Arrays.toString(objs.toArray()));
        int low = 0, high = objs.size() - 1;
        while (low < high) {
            int diff = target - objs.get(low).value;
            if (diff > objs.get(high).value) {
                while ((low + 1 < high)
                        && (objs.get(low).value == objs.get(low + 1).value)) {
                    low++;
                }
                low++;
            } else if (diff < objs.get(high).value) {
                while ((high - 1 >= low)
                        && (objs.get(high).value == objs.get(high - 1).value)) {
                    high--;
                }
                high--;
            } else {
                return new int[] {objs.get(low).index, objs.get(high).index};
            }
        }
        return null;
    }

    static final class Pair implements Comparable<Pair> {
        // Comparable wih comparator construction methods
        private static final Comparator<Pair> COMPARATOR =
            comparingInt((Pair p) -> p.value);

        private final int index;
        private final int value;

        Pair(int index, int value) {
            this.index = index;
            this.value = value;
        }

        @Override
        public int compareTo(Pair p) {
            return COMPARATOR.compare(this, p);
        }

        @Override
        public String toString() {
            return "(index=" + index + ", value=" + value + ")";
        }
    }

    public int[] twoSum2(int[] nums, int target) {
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

            System.out.printf("\n Given nums: %s, target = %d",
                    Arrays.toString(nums), target);

            Solution solution = new Solution();
            int[] pairs = solution.twoSum(nums, target);
            System.out.printf("\n Output: %s\n",
                    (pairs == null) ? "Not found" : Arrays.toString(pairs));
        }
    }

    static final class Input {
        private final int[] nums;
        private final int target;

        Input(int[] nums, int target) {
            this.nums = nums;
            this.target = target;
        }
    }
}

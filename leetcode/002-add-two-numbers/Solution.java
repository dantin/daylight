import java.util.Arrays;
import java.util.List;

public class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        ListNode dummy = new ListNode(-1);
        ListNode tail = dummy;
        int sum = 0;
        while (l1 != null || l2 != null) {
            sum += l1 != null ? l1.val : 0;
            sum += l2 != null ? l2.val : 0;
            int n = sum % 10;
            ListNode node = new ListNode(n);
            tail.next = node;
            tail = node;
            sum /= 10;

            if ( l1 != null ) l1 = l1.next;
            if ( l2 != null ) l2 = l2.next;
        }
        while (sum != 0) {
            int n = sum % 10;
            ListNode node = new ListNode(n);
            tail.next = node;
            tail= node;
            sum /= 10;
        }
        return dummy.next;
    }

    public static void main(String[] args) {
        List<Input> inputs = Arrays.asList(new Input[]{new Input(342, 465)});
        for (Input input : inputs) {
            ListNode num1 = makeList(input.lhs);
            ListNode num2 = makeList(input.rhs);
            System.out.printf(" Input:  %s + %s\n", num1, num2);

            Solution solution = new Solution();
            ListNode result = solution.addTwoNumbers(num1, num2);
            System.out.printf(" Output: %s\n", result);
        }
    }

    private static ListNode makeList(int val) {
        if (val < 0) return null;
        ListNode dummy = new ListNode(-1);
        ListNode head = dummy;
        while (val != 0) {
            int n = val % 10;
            ListNode node = new ListNode(n);
            head.next = node;
            head = node;
            val /= 10;
        }
        return dummy.next;
    }

    static final class Input {
        private int lhs;
        private int rhs;

        Input(int lhs, int rhs) {
            this.lhs = lhs;
            this.rhs = rhs;
        }
    }
}

class ListNode {
    int val;
    ListNode next;
    ListNode(int x) { val = x; }

    @Override
    public String toString() {
        StringBuilder buf = new StringBuilder("(");
        ListNode node = this;
        while (node != null) {
            if (node != this) {
                buf.append(" -> ");
            }
            buf.append(node.val);
            node = node.next;
        }
        buf.append(")");
        return buf.toString();
    }
}

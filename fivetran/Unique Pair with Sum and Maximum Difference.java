/*
Question: Unique Pairs with Difference at Most 1

Given an integer array nums and an integer target, find the number of unique pairs of values (a, b) such that:

a + b == target
|a - b| <= 1
Each pair of values should be counted only once, regardless of how many times the values occur in the array.
A pair can use two occurrences of the same value only if that value appears at least twice in the array.

Return the number of valid unique pairs.

Constraints
1 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
-10^9 <= target <= 10^9
A pair (a, b) and (b, a) are considered the same pair.
*/

class Solution{
    int findUniquePair(int[] nums, int target) {
        int n = nums.length;
        if(target % 2 == 0) {
            int x = target / 2;
            int count = 0;
            for(int i=0; i<n; i++) {
                if(x == nums[i]) ++count;
            }
            if(count <= 1)  return 0;
            else return 1;
        } else {
            int x = target / 2;
            int y = target / 2 + 1;
            boolean xFlag = false, yFlag = false;
            for(int i=0; i<n; i++) {
                if(x == nums[i])        xFlag = true;
                else if(y == nums[i])   yFlag = true;
            }
            if(xFlag && yFlag)  return 1;
            else return 0;
        }
    }
}

public class Main {
    public static void main(String[] args) {
        System.out.println("===== Solution ======\n");
        Solution s = new Solution();
        
        int[] nums1 = {1, 2, 3, 4};
        int target1 = 3;
        int ans1 = s.findUniquePair(nums1, target1);
        System.out.println("Answer 1 = " + ans1);
        
        int[] nums2 = {1, 2, 3, 4, 4, 5};
        int target2 = 8;
        int ans2 = s.findUniquePair(nums2, target2);
        System.out.println("Answer 2 = " + ans2);
        
        int[] nums3 = {1, 2, 3, 4, 5};
        int target3 = 5;
        int ans3 = s.findUniquePair(nums3, target3);
        System.out.println("Answer 3 = " + ans3);
        
        int[] nums4 = {1, 2, 3, 4, 5, 8};
        int target4 = 11;
        int ans4 = s.findUniquePair(nums4, target4);
        System.out.println("Answer 4 = " + ans4);
        
        
        int[] nums5 = {1, 2, 3, 4};
        int target5 = 4;
        int ans5 = s.findUniquePair(nums5, target5);
        System.out.println("Answer 5 = " + ans5);
        
    }
}

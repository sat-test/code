/*
You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.

Merge all the linked-lists into one sorted linked-list and return it.

Example 1:

Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted linked list:
1->1->2->3->4->4->5->6
Example 2:

Input: lists = []
Output: []
Example 3:

Input: lists = [[]]
Output: []
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
     ListNode* sorted_merge(ListNode* a, ListNode* b){
    	ListNode* result = NULL;
    	if (a == NULL)
    		return (b);
    	else if (b == NULL)
    		return (a);
    	if (a->val <= b->val) {
    		result = a;
    		result->next = sorted_merge(a->next, b);
    	}
    	else {
    		result = b;
    		result->next = sorted_merge(a, b->next);
    	}
    
    	return result;
    }
    ListNode* mergeKLists(vector<ListNode*>& arr) {
        int last = arr.size()-1;
        
        if(arr.size() == 0)
            return NULL;
        else if(arr.size() == 1)
            return arr[0];
        
        while (last != 0) {
    		int i = 0, j = last;
    
    		// (i, j) forms a pair
    		while (i < j) {
    			// merge List i with List j and store
    			// merged list in List i
    			arr[i] = sorted_merge(arr[i], arr[j]);
    
    			// consider next pair
    			i++, j--;
    
    			// If all pairs are merged, update last
    			if (i >= j)
    				last = j;
    		}
    	}
    
    	return arr[0];
    }
};

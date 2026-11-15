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
private:
    int small = 100005;
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int n = lists.size();
        ListNode *head = new ListNode(-1);
        ListNode *tail = head;
        
        while(true) {
            int ind = -1;
            int mini = small;
            for(int i=0; i<n; i++) {
                if(lists[i] != nullptr && mini > lists[i]-> val) {
                    mini = lists[i]-> val;
                    ind = i;
                }
            }
            if(ind == -1) {
                break;
            }
            tail-> next = lists[ind];
            lists[ind] = lists[ind]-> next;
            tail = tail-> next;
        }
        return head-> next;
    }
};

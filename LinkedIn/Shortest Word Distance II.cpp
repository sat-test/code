/*
Problem statement
You have a bookshelf in the form of an array ‘arr’ in which names of the books(single word name) are given. You are also given names of two books, ‘book1’ and ‘book2’. You are supposed to find the minimum distance between ‘book1’ and ‘book2’.

Distance between two books is defined as the absolute difference between the indices of the books i.e for two books at index 'i' and 'j' the distance is equal to |i-j|.

Note:

1. There may be multiple occurrences of any book.

2. book1 and book2 are present on the bookshelf.

3. The name of the books is in lower-case.

4. book1 is not equal to book2.
*/
#include <bits/stdc++.h> 
int inf = 100005;
int minimumDistance(vector<string> &arr, string book1, string book2) {
  	int prevBook1 = -1;
	int prevBook2 = -1;
	int res = inf;

	for(int i=0; i<arr.size(); i++) {
		if(arr[i] != book1 && arr[i] != book2) {
			continue;
		}
		if(arr[i] == book1) {
			prevBook1 = i;
		} else if(arr[i] == book2) {
			prevBook2 = i;
		}
		if(prevBook1 != -1 && prevBook2 != -1) {
			res = min(res, abs(prevBook2 - prevBook1));
		}
	}
	return res;
}

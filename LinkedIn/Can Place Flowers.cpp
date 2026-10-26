/*
You have a long flowerbed in which some of the plots are planted, and some are not. However, flowers cannot be planted in adjacent plots.

Given an integer array flowerbed containing 0's and 1's, where 0 means empty and 1 means not empty, and an integer n, return true if n new flowers can be planted in the flowerbed without violating the no-adjacent-flowers rule and false otherwise.

Example 1:

Input: flowerbed = [1,0,0,0,1], n = 1
Output: true
Example 2:

Input: flowerbed = [1,0,0,0,1], n = 2
Output: false
*/

class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        if(flowerbed.size() == 0) return 0;
        else if(flowerbed.size() == 1 && flowerbed[0] == 0) return 1;  
        int zero = 0;
        bool isflower = false;
        for(auto flower: flowerbed) {
            if(flower == 0) {
                ++zero;
            } else {
                n -= isflower == false ? zero / 2 : (zero-1) / 2;
                zero = 0;
                isflower = true;
            }
        }
        n -= isflower == false ? (zero+1) / 2 : zero / 2;
        return n <= 0 ? true : false;
    }
};

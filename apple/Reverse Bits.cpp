/*
Reverse bits of a given 32 bits signed integer.

Example 1:
Input: n = 43261596
Output: 964176192

Example 2:
Input: n = 2147483644
Output: 1073741822
*/

class Solution {
public:
    int reverseBits(int n) {
        uint32_t res = 0;
        for(int i=0; i<32; i++) {
            res <<= 1;
            if(n&1) {
                res |= 1;
            } 
            n >>= 1;
            
        }
        return res;
    }
};

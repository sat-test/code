class Solution {
    int maxElementValue(int[] freq) {
        int maxi = 0;
        for(int i=0; i<26; i++) {
            maxi = Math.max(maxi, freq[i]);
        }
        return maxi;
    }

    public int characterReplacement(String s, int k) {
        int head = 0, tail = 0, res = 0;
        int[] freq = new int[26];
        
        for(head=0; head<s.length(); head++) {
            freq[s.charAt(head) - 'A']++;
            while((head-tail+1 - maxElementValue(freq)) > k) {
                freq[s.charAt(tail)-'A']--;
                tail++;
            }

            res = Math.max(res, head-tail+1);
        }
        return res;
    }
}

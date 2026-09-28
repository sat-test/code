/*
Hyphen-Based Text Justification

Given an array of strings words and an integer maxWidth, format the words into lines such that:

Each line contains as many words as possible without exceeding maxWidth.

Each line must have exactly maxWidth characters.

Use hyphens (-) instead of spaces to separate words.

Distribute the hyphens as evenly as possible between words.

If the number of hyphens cannot be divided evenly, give the extra hyphens to the leftmost gaps.

If a line contains only one word, append hyphens to the right until the line reaches maxWidth.

Apply full justification to the last line as well; there is no special last-line exception.

Return the resulting lines as a vector of strings.

Example

Input

words = {"This", "is", "an", "example", "of", "text", "display"};
maxWidth = 16;

Output

This----is----an
example--of-text
display---------
*/

class Solution {
private:
    string createSentance(vector<string> &words, int wordCount, int sentanceLength, int maxWidth, int pos) {
        string sentance = "";
        if(wordCount == 1) {
            int r = maxWidth - sentanceLength;
            sentance = words[pos-wordCount];
            for(int i=0; i<r; i++) {
                sentance += "-";
            }
            return sentance;
        }
        int d = (maxWidth - sentanceLength) / (wordCount - 1);
        int r = (maxWidth - sentanceLength) % (wordCount - 1);
        
        for(int i=(pos-wordCount); i<pos; i++) {
            sentance += words[i];
            if(r > 0) {
                sentance += "-";
                --r;
            }
            for(int j=0; j<d && i!=(pos-1); j++) {
                sentance += "-";
            }
        }
        return sentance;
    }

public:
    vector<string> textJustification(vector<string> &words, int maxWidth) {
        vector<string> res;
        int wordCount = 0;
        int sentanceLength = 0;
        for(int i=0; i<words.size(); i++) {
            int requiredSize = sentanceLength + words[i].size() + wordCount;
            if(requiredSize <= maxWidth) {
                sentanceLength += words[i].size();
                ++wordCount;
            } else {
                string sentance = createSentance(words, wordCount, sentanceLength, maxWidth, i);
                res.push_back(sentance);
                wordCount = 1;
                sentanceLength = words[i].size();
            }
        }
        string sentance = createSentance(words, wordCount, sentanceLength, maxWidth, words.size());
        res.push_back(sentance);
        
        return res;
    }
};


int main() {
    Solution s;
    
    vector<string> words = {"This", "is", "an", "example", "of", "text", "display"};
    int maxWidth = 16;
    vector<string> vec = s.textJustification(words, maxWidth);
    for(int i=0; i<vec.size(); i++) {
        cout<<vec[i]<<"\n";
    }
}

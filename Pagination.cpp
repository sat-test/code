/*
Problem Statement: Paginate Text

You are given:
- An integer pageLength, representing the maximum number of characters per page, and
- A longText string, representing a paragraph of text without newline characters.

You must return:
- A vector<string> of pages, where each page is at most pageLength characters long.
- Words should not be split across pages—each word must be entirely on a single page.

Constraints:
- All words are separated by spaces.
- If a single word is longer than pageLength, you may:
    - Either throw an error or
    - Put it on a page by itself (if allowed in problem constraints).

*/

vector<string> paginateText(int pageLength, const string& longText) {
    vector<string> words;
    stringstream ss(longText);
    string word;
    
    while(ss >> word) {
        if((int) word.size() > pageLength) {
            return vector<string>();
        }
        words.push_back(word);
    }
    
    vector<string> res;
    string curr;
    for(const string& word : words) {
        if(curr.empty()) {
            curr = word;
        } else if(((int) curr.size() + 1 + word.size()) <= pageLength) {
            curr += " " + word;
        } else {
            res.push_back(curr);
            curr = word;
        }
    }
        
    if(!curr.empty()) {
        res.push_back(curr);
    }
    
    return res;
}

int main() {
    string text = "The quick brown fox jumps over the lazy dog";
    int pageLen = 10;

    vector<string> pages = paginateText(pageLen, text);
    for (const string& page : pages) {
        cout << "\"" << page << "\"" << endl;
    }
    return 0;
}

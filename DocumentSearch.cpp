/*

You are given a list of documents with id and text.
Eg :-
DocId, Text
1, "Cloud computing is the on-demand availability of computer system resources."
2, "One integrated service for metrics uptime cloud monitoring dashboards and alerts reduces time spent navigating between systems."
3, "Monitor entire cloud infrastructure, whether in the cloud computing is or in virtualized data centers."

Search a given phrase in all the documents in a efficient manner. Assume that you have more than 1 million docs.
Eg :-
search("cloud") >> This should output [1,2,3]
search("cloud monitoring") >> This should output [2]
search("Cloud computing is") >> This should output [1,3]

*/


#include <bits/stdc++.h>
using namespace std;

class DocumentSearch {
private:
    unordered_map<string, unordered_map<int, vector<int>>> invertedIndex;

public:
    // Function to index documents
    void indexDocuments(unordered_map<int, string>& docs) {
        for (auto& doc : docs) {
            int docId = doc.first;
            string text = doc.second;
            transform(text.begin(), text.end(), text.begin(), ::tolower); // Convert to lowercase
            
            istringstream iss(text);
            vector<string> words;
            string word;
            while (iss >> word) words.push_back(word);
            
            for (int i = 0; i < words.size(); i++) {
                invertedIndex[words[i]][docId].push_back(i);
            }
        }
    }

    // Function to search for a phrase
    vector<int> search(string phrase) {
        transform(phrase.begin(), phrase.end(), phrase.begin(), ::tolower); // Convert to lowercase
        
        istringstream iss(phrase);
        vector<string> words;
        string word;
        while (iss >> word) words.push_back(word);

        if (words.empty() || invertedIndex.find(words[0]) == invertedIndex.end()) return {};

        unordered_map<int, vector<int>>& candidateDocs = invertedIndex[words[0]];
        vector<int> result;

        for (auto& entry : candidateDocs) {
            int docId = entry.first;
            for (int pos : entry.second) {
                if (isPhrasePresent(docId, pos, words)) {
                    result.push_back(docId);
                    break;
                }
            }
        }
        return result;
    }

private:
    // Check if phrase is present in the document at a given position
    bool isPhrasePresent(int docId, int pos, vector<string>& words) {
        for (int i = 1; i < words.size(); i++) {
            if (invertedIndex.find(words[i]) == invertedIndex.end() ||
                invertedIndex[words[i]].find(docId) == invertedIndex[words[i]].end() ||
                find(invertedIndex[words[i]][docId].begin(), invertedIndex[words[i]][docId].end(), pos + i) == invertedIndex[words[i]][docId].end()) {
                return false;
            }
        }
        return true;
    }
};

// Driver Code
int main() {
    DocumentSearch searchEngine;

    unordered_map<int, string> documents = {
        {1, "Cloud computing is the on-demand availability of computer system resources."},
        {2, "One integrated service for metrics uptime cloud monitoring dashboards and alerts reduces time spent navigating between systems."},
        {3, "Monitor entire cloud infrastructure, whether in the cloud computing is or in virtualized data centers."}
    };

    searchEngine.indexDocuments(documents);

    vector<int> result1 = searchEngine.search("cloud");
    vector<int> result2 = searchEngine.search("cloud monitoring");
    vector<int> result3 = searchEngine.search("Cloud computing is");

    // Output results
    cout << "Search(\"cloud\"): ";
    for (int id : result1) cout << id << " ";
    cout << endl;

    cout << "Search(\"cloud monitoring\"): ";
    for (int id : result2) cout << id << " ";
    cout << endl;

    cout << "Search(\"Cloud computing is\"): ";
    for (int id : result3) cout << id << " ";
    cout << endl;

    return 0;
}

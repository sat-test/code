/*
Key-value store with expiration. Functions: put(key, value), get(key), and get_average() (average of non-expired values). Data streamed in order of increasing timestamps.
https://leetcode.com/discuss/interview-experience/5895828/Confluent-or-SSE-2-or-Remote
*/

// class KeyValueStore {
//     unordered_map<int, int> keyValueMap, keyTimeMap;
//     queue<pair<int, pair<int, int>>> q; 
//     int expiry, currTime = 0;
//     float sum = 0;
    
//     void checkAndPop() {
//         if(q.size() != 0) {
//             int time = q.front().first;
//             int key = q.front().second.first;
//             int value = q.front().second.second;
//             if (currTime - time > expiry) { 
//                 q.pop();
//                 if (keyTimeMap[key] == time) { 
//                     keyTimeMap.erase(key);
//                     keyValueMap.erase(key);
//                 } 
//                 sum -= value;
//             }
//         } 
//     }
    
// public:
//     KeyValueStore(int _expiry) {
//         expiry = _expiry;
//         sum = 0;
//         currTime = 1;
//     }
    
//     void put(int key, int value) {
//         checkAndPop();
//         keyValueMap[key] = value;
//         keyTimeMap[key] = currTime;
//         q.push({currTime, {key, value}});
//         sum += value;
//         ++currTime;
//     }
    
//     int get(int key) {
//         checkAndPop();
//         if(keyValueMap.find(key) == keyValueMap.end()) {
//             return -1;
//         }
//         ++currTime;
//         return keyValueMap[key];
//     }
    
//     float getAverage() {
//         if (q.empty()) return 0;
//         checkAndPop();
//         float size = q.size();
//         ++currTime;
//         return sum/size;
//     }
// };


// int main() {
//     KeyValueStore kv(3);
//     kv.put(1, 10);
//     kv.put(2, 20);
//     kv.put(3, 30);
    
//     cout << "Average: " << kv.getAverage() << endl; // (10 + 20 + 30) / 3 = 20

//     kv.put(4, 40);
//     cout << "Average after put(4, 40): " << kv.getAverage() << endl; // (20 + 30 + 40) / 3 = 30

//     kv.get(1); // Expire old values
//     cout << "Average after get(1): " << kv.getAverage() << endl; 

//     return 0;
// }


#include <bits/stdc++.h>
using namespace std;

class KeyValueStore {
    unordered_map<int, int> keyValueMap, keyTimeMap;
    queue<pair<int, pair<int, int>>> q; 
    int expiry;
    float sum = 0;

    void checkAndPop() {
        time_t currTime = time(0); // Get the current time
        while (!q.empty()) {  
            int time = q.front().first;
            int key = q.front().second.first;
            int value = q.front().second.second;

            if (currTime - time > expiry) { 
                q.pop();
                if (keyTimeMap[key] == time) { 
                    keyTimeMap.erase(key);
                    keyValueMap.erase(key);
                    sum -= value; // Adjust sum only if key is fully removed
                }
            } else {
                break; // Stop if front element is still valid
            }
        }
    }

public:
    KeyValueStore(int _expiry) : expiry(_expiry) {}

    void put(int key, int value) {
        checkAndPop();
        time_t currTime = time(0); // Get the current time

        if (keyValueMap.find(key) != keyValueMap.end()) { 
            sum -= keyValueMap[key]; // Remove old value before updating
        }
        keyValueMap[key] = value;
        keyTimeMap[key] = currTime;
        q.push({currTime, {key, value}});
        sum += value;
    }

    int get(int key) {
        checkAndPop();
        if (keyValueMap.find(key) == keyValueMap.end()) {
            return -1;
        }
        return keyValueMap[key];
    }

    float getAverage() {
        checkAndPop();
        if (keyValueMap.empty()) return 0.0;
        return sum / keyValueMap.size();
    }
};

int main() {
    KeyValueStore kv(2);
    kv.put(1, 10);
    kv.put(2, 20);
    kv.put(3, 30);
    
    cout << "Average: " << kv.getAverage() << endl; // (10 + 20 + 30) / 3 = 20
    
    this_thread::sleep_for(chrono::seconds(1));
    kv.put(4, 40);
    cout << "Average after put(4, 40): " << kv.getAverage() << endl; // (20 + 30 + 40) / 3 = 30

    this_thread::sleep_for(chrono::seconds(2)); // Simulate delay for expiration

    cout << "Average after 4 seconds: " << kv.getAverage() << endl; // Should exclude expired keys

    return 0;
}


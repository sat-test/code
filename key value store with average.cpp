/*
Key-value store with expiration. Functions: put(key, value), get(key), and get_average() (average of non-expired values). Data streamed in order of increasing timestamps.
https://leetcode.com/discuss/interview-experience/5895828/Confluent-or-SSE-2-or-Remote
*/

class KeyValueStore {
    unordered_map<int, int> keyValueMap, keyTimeMap;
    queue<pair<int, pair<int, int>>> q; 
    int expiry, currTime = 0;
    float sum = 0;
    
    void checkAndPop() {
        if(q.size() != 0) {
            int time = q.front().first;
            int key = q.front().second.first;
            int value = q.front().second.second;
            if (currTime - time > expiry) { 
                q.pop();
                if (keyTimeMap[key] == time) { 
                    keyTimeMap.erase(key);
                    keyValueMap.erase(key);
                } 
                sum -= value;
            }
        } 
    }
    
public:
    KeyValueStore(int _expiry) {
        expiry = _expiry;
        sum = 0;
        currTime = 1;
    }
    
    void put(int key, int value) {
        checkAndPop();
        keyValueMap[key] = value;
        keyTimeMap[key] = currTime;
        q.push({currTime, {key, value}});
        sum += value;
        ++currTime;
    }
    
    int get(int key) {
        checkAndPop();
        if(keyValueMap.find(key) == keyValueMap.end()) {
            return -1;
        }
        ++currTime;
        return keyValueMap[key];
    }
    
    float getAverage() {
        if (q.empty()) return 0;
        checkAndPop();
        float size = q.size();
        ++currTime;
        return sum/size;
    }
};


int main() {
    KeyValueStore kv(3);
    kv.put(1, 10);
    kv.put(2, 20);
    kv.put(3, 30);
    
    cout << "Average: " << kv.getAverage() << endl; // (10 + 20 + 30) / 3 = 20

    kv.put(4, 40);
    cout << "Average after put(4, 40): " << kv.getAverage() << endl; // (20 + 30 + 40) / 3 = 30

    kv.get(1); // Expire old values
    cout << "Average after get(1): " << kv.getAverage() << endl; 

    return 0;
}

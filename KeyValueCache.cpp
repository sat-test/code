/*
Design a key value cache system and implement set, get, delete methods to be expected. Input would be as list of strings.
["SET key1 value1"]
["GET key1"]
["DELETE key1"]

Follow up: How do we handle transactions?
A transaction starts with BEGIN and operations like SET, GET, DELETE can take place during this time. After these operation, the transaction is ended by either a COMMIT that commits everything permanently in the data store or ROLLBACK that reverts everything that was performed during the transaction window.
We need to implement commit and rollback methods

https://leetcode.com/discuss/interview-experience/5698133/Rippling-or-Senior-Software-Engineer-or-Bengaluru-or-August-Offer
*/




class KeyValueCache {
private:
    unordered_map<string, string> dataStore;
    stack<unordered_map<string, string>> transactions;

public:
    void set(const string &key, const string &value) {
        if(!transactions.empty()) {
            transactions.top()[key] = dataStore[key];
        }
        dataStore[key] = value;
        cout << "SET " << key << " = " << value << "\n";
    }
    
    string get(const string &key) {
        if(dataStore.find(key) != dataStore.end()) {
            cout << "GET " << key << " = " << dataStore[key] << "\n";
            return dataStore[key];
        }
        cout << "GET " << key << " = NULL\n";
        return "NULL";
    }
    
    void del(const string &key) {
        if(!transactions.empty() && dataStore.find(key) != dataStore.end()) {
            transactions.top()[key] = dataStore[key];
        }
        dataStore.erase(key);
        cout << "DELETE " << key << "\n";
    }
    
    void begin() {
        transactions.push(unordered_map<string, string>());
        cout << "BEGIN TRANSACTION\n";
    }
    
    void rollback() {
        if (transactions.empty()) {
            cout << "NO TRANSACTION TO ROLLBACK\n";
            return;
        }
        auto changes = transactions.top();
        for(const auto &entry : changes) {
            if(entry.second.empty()) {
                dataStore.erase(entry.first);
            } else {
                dataStore[entry.first] = entry.second;
            }
        }
        transactions.pop();
        cout << "ROLLBACK SUCCESSFUL\n";
    }
    
    void commit() {
        if (transactions.empty()) {
            cout << "NO TRANSACTION TO COMMIT\n";
            return;
        }
        transactions = stack<unordered_map<string, string>>();
        cout << "COMMIT SUCCESSFUL\n";
    }
};

void processCommands(vector<string> commands) {
    KeyValueCache cache;

    for (const auto &command : commands) {
        vector<string> tokens;
        string token = "";
        for (char ch : command) {
            if (ch == ' ') {
                if (!token.empty()) {
                    tokens.push_back(token);
                    token = "";
                }
            } else {
                token += ch;
            }
        }
        if (!token.empty()) tokens.push_back(token);

        if (tokens[0] == "SET" && tokens.size() == 3) {
            cache.set(tokens[1], tokens[2]);
        } else if (tokens[0] == "GET" && tokens.size() == 2) {
            cache.get(tokens[1]);
        } else if (tokens[0] == "DELETE" && tokens.size() == 2) {
            cache.del(tokens[1]);
        } else if (tokens[0] == "BEGIN") {
            cache.begin();
        } else if (tokens[0] == "ROLLBACK") {
            cache.rollback();
        } else if (tokens[0] == "COMMIT") {
            cache.commit();
        } else {
            cout << "INVALID COMMAND: " << command << "\n";
        }
    }
}

int main() {
    vector<string> commands = {
        "SET key1 value1",
        "GET key1",
        "DELETE key1",
        "GET key1",
        "BEGIN",
        "SET key2 value2",
        "GET key2",
        "ROLLBACK",
        "GET key2",
        "BEGIN",
        "SET key3 value3",
        "COMMIT",
        "GET key3"
    };

    processCommands(commands);

    return 0;
}

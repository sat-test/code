#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class NestedNode {
public:
    bool isInteger = false;
    int value = 0;
    vector<NestedNode> nodes;

    NestedNode(int value) {
        this->value = value;
        this->isInteger = true;
    }

    NestedNode(vector<NestedNode> nodes) {
        this->nodes = nodes;
        this->isInteger = false;
    }
};

class Solution {
public:
    int nestedWeightSum(vector<NestedNode>& nestedNodes) {
        queue<const NestedNode*> q;

        // Add top-level nodes
        for (const auto& node : nestedNodes) {
            q.push(&node);
        }

        int cumulativeSum = 0;
        int result = 0;

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                const NestedNode* node = q.front();
                q.pop();

                if (node->isInteger) {
                    cumulativeSum += node->value;
                } else {
                    for (const auto& child : node->nodes) {
                        q.push(&child);
                    }
                }
            }

            // Add the cumulative sum for this depth
            result += cumulativeSum;
        }

        return result;
    }
};

int main() {
    vector<NestedNode> nodes = {
        NestedNode({
            NestedNode(2),
            NestedNode({NestedNode(5)}),
            NestedNode({NestedNode(7)}),
            NestedNode({NestedNode(8)})
        }),
        NestedNode({
            NestedNode(10),
            NestedNode({NestedNode(2)}),
            NestedNode({NestedNode(9)}),
            NestedNode({NestedNode(5)})
        })
    };

    Solution s;

    int res = s.nestedWeightSum(nodes);

    cout << res << "\n";

    return 0;
}

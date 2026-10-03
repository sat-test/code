/*
12. Agent Voting System
Problem Statement
You are building a customer-support agent rating system.
Customers can rate support agents after an interaction. Each rating contains:
(agentId, customerId, rating)

where rating is an integer from 1 to 5.
Design a system that supports the following operations:
1. Add a rating for an agent.
2. Get the average rating of an agent.
3. Get the top-rated agents based on their average rating.
A customer can rate a particular agent at most once. If the same customer rates the same agent again, the new rating should replace the previous rating.
Input
You are given a sequence of operations.
Each operation can be one of:
RATE agentId customerId rating
GET_AVERAGE agentId
TOP_AGENTS k

Where:
- agentId — unique identifier of the support agent.
- customerId — unique identifier of the customer.
- rating — integer between 1 and 5.
- k — number of top agents to return.
Constraints
- 1 <= number of operations <= 10^5
- 1 <= agentId <= 10^5
- 1 <= customerId <= 10^6
- 1 <= rating <= 5
- 1 <= k <= 10^5
- A customer can rate an agent at most once at any point in time.
- If a customer rates the same agent again, the previous rating is replaced.
- An agent may have zero ratings.
- For TOP_AGENTS, agents are ranked by:
  1. Higher average rating first.
  2. If averages are equal, higher number of ratings first.
  3. If still tied, smaller agentId first.
Expected average complexity for RATE and GET_AVERAGE should be O(log N) or better.
Example
Input
RATE A1 C1 5
RATE A1 C2 4
RATE A1 C3 5

RATE A2 C4 4
RATE A2 C5 4
RATE A2 C6 3

GET_AVERAGE A1
GET_AVERAGE A2

TOP_AGENTS 2

Processing
For A1:
C1 -> 5
C2 -> 4
C3 -> 5

Average = (5 + 4 + 5) / 3
        = 4.67

For A2:
C4 -> 4
C5 -> 4
C6 -> 3

Average = (4 + 4 + 3) / 3
        = 3.67

Therefore:
Output
GET_AVERAGE A1
4.67

GET_AVERAGE A2
3.67

TOP_AGENTS 2
[A1, A2]
*/

class Solution {
private:
    // agentId -> total rating
    unordered_map<int, long long> totalRating;

    // agentId -> number of ratings
    unordered_map<int, int> ratingCount;

    // agentId -> (customerId -> rating)
    unordered_map<int, unordered_map<int, int>> customerRatings;

    // {average, agentId}
    set<pair<double, int>> ranking;

public:
    void rate(int agentId, int customerId, int rating) {
        // Remove old ranking entry if agent already has ratings
        if (ratingCount[agentId] > 0) {
            double oldAverage =
                (double)totalRating[agentId] / ratingCount[agentId];

            ranking.erase({oldAverage, agentId});
        }

        // Check whether customer has already rated this agent
        auto& ratings = customerRatings[agentId];
        auto it = ratings.find(customerId);

        if (it == ratings.end()) {
            // First rating from this customer
            totalRating[agentId] += rating;
            ratingCount[agentId]++;
        } else {
            // Customer is updating existing rating
            int oldRating = it->second;

            totalRating[agentId] -= oldRating;
            totalRating[agentId] += rating;
        }

        // Store/update customer's rating
        ratings[customerId] = rating;

        // Insert updated ranking
        double newAverage =
            (double)totalRating[agentId] / ratingCount[agentId];

        ranking.insert({newAverage, agentId});
    }

    double getAverageRating(int agentId) {
        if (ratingCount[agentId] == 0) {
            return 0.0;
        }

        return (double)totalRating[agentId] / ratingCount[agentId];
    }

    vector<int> topAgents(int k) {
        vector<int> agents;

        for (auto it = ranking.rbegin();
             it != ranking.rend() && k > 0;
             ++it, --k) {

            agents.push_back(it->second);
        }

        return agents;
    }
};

int main() {
    Solution s;

    // --------------------------------------------------
    // Test 1: Basic ratings
    // --------------------------------------------------
    s.rate(1, 101, 5);
    s.rate(1, 102, 4);
    s.rate(1, 103, 5);

    cout << "Agent 1 Average: "
         << s.getAverageRating(1) << endl;

    // Expected: 4.66667


    // --------------------------------------------------
    // Test 2: Another agent
    // --------------------------------------------------
    s.rate(2, 201, 4);
    s.rate(2, 202, 4);
    s.rate(2, 203, 3);

    cout << "Agent 2 Average: "
         << s.getAverageRating(2) << endl;

    // Expected: 3.66667


    // --------------------------------------------------
    // Test 3: Third agent
    // --------------------------------------------------
    s.rate(3, 301, 5);
    s.rate(3, 302, 5);

    cout << "Agent 3 Average: "
         << s.getAverageRating(3) << endl;

    // Expected: 5


    // --------------------------------------------------
    // Test 4: Top 3 agents
    // --------------------------------------------------
    vector<int> top = s.topAgents(3);

    cout << "Top 3 agents: ";

    for (int agent : top) {
        cout << agent << " ";
    }

    cout << endl;

    // Expected:
    // 3 1 2


    // --------------------------------------------------
    // Test 5: Customer 102 changes rating
    // Agent 1:
    //
    // Before:
    // 5 + 4 + 5 = 14
    // count = 3
    // average = 4.66667
    //
    // Change customer 102: 4 -> 2
    //
    // After:
    // 5 + 2 + 5 = 12
    // count = 3
    // average = 4
    // --------------------------------------------------
    s.rate(1, 102, 2);

    cout << "Agent 1 Average after update: "
         << s.getAverageRating(1) << endl;

    // Expected: 4


    // --------------------------------------------------
    // Test 6: Ranking after update
    // --------------------------------------------------
    top = s.topAgents(3);

    cout << "Top 3 agents after update: ";

    for (int agent : top) {
        cout << agent << " ";
    }

    cout << endl;

    // Expected:
    // 3 1 2


    // --------------------------------------------------
    // Test 7: Customer 102 updates again
    // 2 -> 5
    //
    // Agent 1:
    // 5 + 5 + 5 = 15
    // average = 5
    // --------------------------------------------------
    s.rate(1, 102, 5);

    cout << "Agent 1 Average after second update: "
         << s.getAverageRating(1) << endl;

    // Expected: 5


    // --------------------------------------------------
    // Test 8: Two agents with same average
    // --------------------------------------------------
    s.rate(4, 401, 5);

    cout << "Agent 4 Average: "
         << s.getAverageRating(4) << endl;

    // Expected: 5


    // --------------------------------------------------
    // Test 9: Top 2
    // --------------------------------------------------
    top = s.topAgents(2);

    cout << "Top 2 agents: ";

    for (int agent : top) {
        cout << agent << " ";
    }

    cout << endl;


    // --------------------------------------------------
    // Test 10: Agent with no ratings
    // --------------------------------------------------
    cout << "Agent 99 Average: "
         << s.getAverageRating(99) << endl;

    // Expected: 0


    // --------------------------------------------------
    // Test 11: topAgents(k) > number of agents
    // --------------------------------------------------
    top = s.topAgents(100);

    cout << "Top 100 agents: ";

    for (int agent : top) {
        cout << agent << " ";
    }

    cout << endl;


    return 0;
}

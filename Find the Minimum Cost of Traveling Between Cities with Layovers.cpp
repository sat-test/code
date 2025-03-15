/*
Given an input string: "UK:US:FedEx:4,UK:FR:Jet1:2,US:UK:RyanAir:8,CA:UK:CanadaAir:8" Which represents flights between destinations in the format: "Source:Destination:Airline:Cost,..." Write a function which will take a Source and Destination and output the cost.
*/

class FlightGraph {
private:
    unordered_map<string, unordered_map<string, int>> adjList; // Adjacency List with min-cost

public:
    void buildGraph(const string &input) {
        stringstream ss(input);
        string segment;

        while (getline(ss, segment, ',')) {
            stringstream segmentStream(segment);
            string src, dest, airline, costStr;
            getline(segmentStream, src, ':');
            getline(segmentStream, dest, ':');
            getline(segmentStream, airline, ':');
            getline(segmentStream, costStr, ':');
            
            int cost = stoi(costStr);

            if (adjList[src].find(dest) != adjList[src].end()) {
                adjList[src][dest] = min(adjList[src][dest], cost);
            } else {
                adjList[src][dest] = cost;
            }
        }
    }

    int findMinCost(const string &src, const string &dest) {
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
        unordered_map<string, int> minCost;

        pq.push({0, src});
        minCost[src] = 0;

        while (!pq.empty()) {
            int price = pq.top().first;
            string city = pq.top().second;
            pq.pop();

            if (city == dest) {
                return price;
            }

            for (auto &it : adjList[city]) {
                int newPrice = price + it.second;
                string nextCity = it.first;

                if (!minCost.count(nextCity) || newPrice < minCost[nextCity]) {
                    minCost[nextCity] = newPrice;
                    pq.push({newPrice, nextCity});
                }
            }
        }

        return -1; 
    }
};

int main() {
    string input = "A:B:AirIndia:2,A:B:Indigo:1,B:C:SpiceJet:3,C:D:AirAsia:5";
    
    FlightGraph graph;
    graph.buildGraph(input);

    string src = "A", dest = "C";
    int cost = graph.findMinCost(src, dest);

    if (cost != -1)
        cout << "Minimum cost from " << src << " to " << dest << " is: " << cost << endl;
    else
        cout << "No path found from " << src << " to " << dest << endl;

    return 0;
}

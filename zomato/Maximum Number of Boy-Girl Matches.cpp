class Solution {
public:

    bool dfs(int boy,
             vector<vector<int>>& grid,
             vector<int>& matchedBoy,
             vector<bool>& visited) {

        int n = grid[0].size();

        for (int girl = 0; girl < n; girl++) {

            // Boy cannot be matched with this girl
            if (grid[boy][girl] == 0)
                continue;

            // Already explored this girl
            if (visited[girl])
                continue;

            visited[girl] = true;

            // Girl is free OR
            // we can move her current boy to another girl
            if (matchedBoy[girl] == -1 ||
                dfs(matchedBoy[girl],
                    grid,
                    matchedBoy,
                    visited)) {

                matchedBoy[girl] = boy;
                return true;
            }
        }

        return false;
    }

    int maximumInvitations(vector<vector<int>>& grid) {

        int m = grid.size();
        int n = grid[0].size();

        // matchedBoy[g] = boy currently matched with girl g
        vector<int> matchedBoy(n, -1);

        int maximumMatching = 0;

        for (int boy = 0; boy < m; boy++) {

            vector<bool> visited(n, false);

            if (dfs(boy, grid, matchedBoy, visited)) {
                maximumMatching++;
            }
        }

        return maximumMatching;
    }
};

int main() {
    Solution s;
    vector<vector<int>> grid = {{1, 1, 0}, {1, 0, 1}, {0, 0, 1}};
    cout<<s.maximumInvitations(grid)<<"\n";
}

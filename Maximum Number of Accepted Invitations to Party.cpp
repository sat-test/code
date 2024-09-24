/*
https://www.geeksforgeeks.org/maximum-number-of-accepted-invitations-to-party/
https://leetcode.com/discuss/interview-question/4820505/Google-question/
*/

int canInvite(vector<vector<int>> &matrix, int boys, int boy, vector<int> &girlInvitedBy, vector<bool> &visit) {
    if(visit[boy]) {
        return false;
    }
    visit[boy] = true;
    for(int girl=0; girl<matrix[boy].size(); girl++) {
        if(matrix[boy][girl]) {
            if(girlInvitedBy[girl] == -1 || canInvite(matrix, boys, girlInvitedBy[girl], girlInvitedBy, visit)) {
                girlInvitedBy[girl] = boy;
                return true;
            }
        }
    }
    return false;
}


int maximumInvitations(vector<vector<int>> &matrix) {
    int boys = matrix.size();
    int girls = matrix[0].size();
    vector<int> girlInvitedBy(girls, -1);
    int res = 0;
    for(int boy=0; boy<boys; --boys) {
        vector<bool> visit(boys, false);
        if(canInvite(matrix, boys, boy, girlInvitedBy, visit)) {
            ++res;
        }
    }
    return res;
}


int main() {
    vector<vector<int> > invitationMatrix = { { 1, 1, 1 }, { 1, 0, 1 }, { 0, 0, 1 } };
    int totalInvitations = maximumInvitations(invitationMatrix);
    cout << "The maximum possible number of accepted "
            "invitations is: "
         << totalInvitations << endl;
}

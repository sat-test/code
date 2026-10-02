/*
9. Movie Recommendation System
You are given information about users, the movies they have watched, and the ratings they have given to those movies.
A user wants movie recommendations based on the movies their friends have rated highly.
Input
You are given:
1. A list of users and their friends.
2. Each user's movie ratings.
For each rating:
(userId, movieId, rating)

where rating is an integer from 1 to 5.
You are also given a target user:
targetUser

Recommendation Rules
Recommend movies that satisfy both conditions:
1. At least one friend of targetUser has rated the movie 4 or 5.
2. targetUser has not watched/rated that movie.
If multiple friends have rated the same movie highly, the movie should appear only once in the recommendation list.
Example
Friends of Alice:
Alice → [Bob, Charlie]

Ratings:
Bob:
    Movie A → 5
    Movie B → 3
    Movie C → 4

Charlie:
    Movie A → 4
    Movie D → 5
    Movie E → 2

Alice:
    Movie A → 5
    Movie D → 2

For Alice:
- Bob recommends Movie A → rating 5 ✅
- Bob's Movie B → rating 3 ❌
- Bob recommends Movie C → rating 4 ✅
- Charlie recommends Movie A → rating 4, but Alice already watched it ❌
- Charlie recommends Movie D → rating 5, but Alice already watched it ❌
- Movie E → rating 2 ❌
Therefore:
Recommendation = [Movie C]

Constraints
Assume:
1 <= U <= 10^5       // number of users
1 <= M <= 10^5       // number of movies
1 <= F <= 2 * 10^5   // total friendship relationships
1 <= R <= 10^6       // total movie ratings
1 <= friends(targetUser) <= U
1 <= rating <= 5

Additional assumptions:
- Each user can rate a particular movie at most once.
- Friendship relationships are given as user IDs.
- A user is not considered their own friend.
- Ratings are integers from 1 to 5.
- The target user's own ratings identify the movies they have already watched.
- We only need recommendations based on direct friends of the target user.
Expected Output
Return the list of recommended movieIds.
The ordering should be clarified with the interviewer. If no ordering is specified, any order is acceptable.
Follow-up 1 — Rank Recommendations
Instead of simply returning the movies, rank them by the number of friends who rated them 4 or 5.
For example:
Movie A → 4 friends rated >= 4
Movie B → 2 friends rated >= 4
Movie C → 1 friend rated >= 4

Return:
[A, B, C]

with higher friend-support first.
Follow-up 2 — Average Rating
Rank movies based on the average rating among the target user's friends who rated them.
For example:
Movie A → [5, 4, 5] → average = 4.67
Movie B → [4, 4]    → average = 4.00

Movie A would rank before Movie B.
Core DSA
The basic problem can be solved efficiently using:
unordered_set → movies already watched by target user
unordered_map → movie → recommendation count

For the basic version, the expected complexity is approximately:
\[
O(F_t + R_t)
\]
where F_t is the number of direct friends of the target user and R_t is the number of ratings made by those friends.
*/

class Solution {
public:
    vector<string> recommendMovie(
        vector<vector<string>> friends,
        vector<vector<string>> ratings,
        string targetUser
    ) {

        // user -> movies rated >= 4
        unordered_map<string, unordered_set<string>> recommendation;

        // user -> all movies watched/rated
        unordered_map<string, unordered_set<string>> watched;

        // Process ratings
        for (int i = 0; i < ratings.size(); i++) {

            string username = ratings[i][0];
            string movie = ratings[i][1];
            int rating = stoi(ratings[i][2]);

            // User has watched/rated this movie
            watched[username].insert(movie);

            // Highly rated movie
            if (rating >= 4) {
                recommendation[username].insert(movie);
            }
        }

        // Find target user's friends
        vector<string> targetUserFriends;

        for (auto& frnd : friends) {

            if (frnd[0] == targetUser) {

                for (int i = 1; i < frnd.size(); i++) {
                    targetUserFriends.push_back(frnd[i]);
                }

                break;
            }
        }

        // Collect recommendations
        unordered_set<string> resultSet;

        for (string& frnd : targetUserFriends) {

            for (const string& movie : recommendation[frnd]) {

                // Target user hasn't watched this movie
                if (watched[targetUser].find(movie) ==
                    watched[targetUser].end()) {

                    resultSet.insert(movie);
                }
            }
        }

        // Convert set to vector
        vector<string> result;

        for (auto& movie : resultSet) {
            result.push_back(movie);
        }

        return result;
    }
};

int main() {
    Solution s;

    vector<vector<string>> friends = {
        {"Alice", "Bob", "Charlie"},
        {"Bob", "Alice"},
        {"Charlie", "Alice"}
    };

    vector<vector<string>> ratings = {
        {"Bob", "MovieA", "5"},
        {"Bob", "MovieB", "3"},
        {"Bob", "MovieC", "4"},

        {"Charlie", "MovieA", "4"},
        {"Charlie", "MovieD", "5"},
        {"Charlie", "MovieE", "2"},

        {"Alice", "MovieA", "5"},
        {"Alice", "MovieD", "2"}
    };

    string targetUser = "Alice";

    vector<string> result =
        s.recommendMovie(friends, ratings, targetUser);

    for (const string& movie : result) {
        cout << movie << "\n";
    }

    return 0;
}

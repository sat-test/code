/*
10. YouTube Like / Dislike Functionality
Design a system that supports Like and Dislike functionality for videos.
Each user can have at most one active reaction on a video:
- LIKE
- DISLIKE
- No reaction
A user can change their reaction at any time.
Requirements
Implement the following operations:
1. likeVideo(userId, videoId)
The user likes the video.
Rules:
- If the user has no existing reaction → add a Like.
- If the user already likes the video → do nothing.
- If the user previously disliked the video → remove the Dislike and add a Like.
2. dislikeVideo(userId, videoId)
The user dislikes the video.
Rules:
- If the user has no existing reaction → add a Dislike.
- If the user already dislikes the video → do nothing.
- If the user previously liked the video → remove the Like and add a Dislike.
3. removeReaction(userId, videoId)
Remove the user's current reaction.
If the user has no reaction, do nothing.
4. getVideoStats(videoId)
Return the current number of:
likes
dislikes

for the video.
*/

class Solution {
public:
    unordered_map<string, unordered_set<string>> videoLikeStats;
    unordered_map<string, unordered_set<string>> videoDislikeStats;
    
    void likeVideo(string userId, string videoId){
        if((videoDislikeStats.find(videoId) != videoDislikeStats.end()) && 
           (videoDislikeStats[videoId].find(userId) != videoDislikeStats[videoId].end())) {
            videoDislikeStats[videoId].erase(userId);
        }
        videoLikeStats[videoId].insert(userId);
    }

    void dislikeVideo(string userId, string videoId){
        if((videoLikeStats.find(videoId) != videoLikeStats.end()) && 
           (videoLikeStats[videoId].find(userId) != videoLikeStats[videoId].end())) {
            videoLikeStats[videoId].erase(userId);
        }
        videoDislikeStats[videoId].insert(userId);
    }

    void removeReaction(string userId, string videoId){
        if((videoDislikeStats.find(videoId) != videoDislikeStats.end()) && 
           (videoDislikeStats[videoId].find(userId) != videoDislikeStats[videoId].end())) {
            videoDislikeStats[videoId].erase(userId);
        } else if((videoLikeStats.find(videoId) != videoLikeStats.end()) && 
           (videoLikeStats[videoId].find(userId) != videoLikeStats[videoId].end())) {
            videoLikeStats[videoId].erase(userId);
        }
    }

    pair<int, int> getVideoStats(string videoId) {
        return {videoLikeStats[videoId].size(), videoDislikeStats[videoId].size()};
    }
};

int main() {
    Solution system;

    // Test 1: Initial state
    auto stats = system.getVideoStats("video1");
    assert(stats.first == 0);
    assert(stats.second == 0);

    // Test 2: User1 likes video1
    system.likeVideo("user1", "video1");

    stats = system.getVideoStats("video1");
    assert(stats.first == 1);
    assert(stats.second == 0);

    // Test 3: User2 likes video1
    system.likeVideo("user2", "video1");

    stats = system.getVideoStats("video1");
    assert(stats.first == 2);
    assert(stats.second == 0);

    // Test 4: User3 dislikes video1
    system.dislikeVideo("user3", "video1");

    stats = system.getVideoStats("video1");
    assert(stats.first == 2);
    assert(stats.second == 1);

    // Test 5: User1 changes LIKE -> DISLIKE
    system.dislikeVideo("user1", "video1");

    stats = system.getVideoStats("video1");
    assert(stats.first == 1);
    assert(stats.second == 2);

    // Test 6: User3 changes DISLIKE -> LIKE
    system.likeVideo("user3", "video1");

    stats = system.getVideoStats("video1");
    assert(stats.first == 2);
    assert(stats.second == 1);

    // Test 7: Duplicate LIKE should not increase count
    system.likeVideo("user2", "video1");
    system.likeVideo("user2", "video1");

    stats = system.getVideoStats("video1");
    assert(stats.first == 2);
    assert(stats.second == 1);

    // Test 8: Remove reaction
    system.removeReaction("user2", "video1");

    stats = system.getVideoStats("video1");
    assert(stats.first == 1);
    assert(stats.second == 1);

    // Test 9: Remove again should be safe
    system.removeReaction("user2", "video1");

    stats = system.getVideoStats("video1");
    assert(stats.first == 1);
    assert(stats.second == 1);

    // Test 10: Different video should maintain separate stats
    system.likeVideo("user1", "video2");
    system.dislikeVideo("user2", "video2");

    stats = system.getVideoStats("video1");
    assert(stats.first == 1);
    assert(stats.second == 1);

    stats = system.getVideoStats("video2");
    assert(stats.first == 1);
    assert(stats.second == 1);

    cout << "All test cases passed!" << endl;

    return 0;
}

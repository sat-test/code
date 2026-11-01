/*
Problem statement
You are given an adjacency list representing friendships between users in a social network.

Each user is represented by a unique user ID, and each friendship is represented as an edge between two users.

Friendships are bidirectional: if user A is friends with user B, then user B is also friends with user A.

Implement a solution to support the following operations.
Part 1 — Find the shortest friendship path
Given two users, userA and userB, find the shortest path between them.

Return the sequence of user IDs representing the path from userA to userB.

If no path exists, return an empty list.

Example:
A -- B -- D
|    |
C -- E


Input:
userA = A
userB = D


Output:
[A, B, D]


The path [A, B, D] is the shortest path between A and D.
Part 2 — Find the shortest friendship distance
Given two users, return the minimum number of friendship connections required to reach from userA to userB.

Example:
A -- B -- D
|    |
C -- E


Input:
userA = A
userB = D


Output:
2


If the users are not connected, return -1.
Part 3 — Suggest friends based on mutual connections
Given a user, recommend potential friends based on the number of mutual friends they share.

A suggested friend must:
- Not be the user themselves.
- Not already be a direct friend.
- Have at least one mutual friend with the user.
Rank the recommendations by the number of mutual friends in descending order.

If two users have the same number of mutual friends, any order is acceptable unless the interviewer specifies a tie-breaking rule.

Example:
A is friends with B, C, D

B is friends with A, E, F
C is friends with A, E
D is friends with A, F
*/

import java.util.ArrayList;
import java.util.ArrayDeque;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Queue;
import java.util.Set;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        System.out.println("=========== Started ===========\n");

        FriendshipGraph graph = new FriendshipGraph();
        Friend a = new Friend("A");
        Friend b = new Friend("B");
        Friend c = new Friend("C");
        Friend d = new Friend("D");
        Friend e = new Friend("E");
        Friend f = new Friend("F");

        graph.setFriends("A", b, c);
        graph.setFriends("B", a, d, e);
        graph.setFriends("C", a, f);
        graph.setFriends("D", b);
        graph.setFriends("E", b, f);
        graph.setFriends("F", c, e);

        ArrayList<Friend> path = graph.shortedPath("A", "F");
        for (Friend friend : path) {
            System.out.print(friend.getName() + " ");
        }
        System.out.println();
        System.out.println("Shortest distance from A to F: " + graph.shortestDistance("A", "F"));

        ArrayList<Friend> recommendations = graph.friendRecommendations("A");
        System.out.print("Friend recommendations for A: ");
        for (Friend friend : recommendations) {
            System.out.print(friend.getName() + " ");
        }
        System.out.println();

        System.out.println("=========== Ended ===========\n");
    }
}

class Friend {
    private String name;

    public Friend(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}

class FriendshipGraph {
    private HashMap<String, Friend[]> friendGraph;

    public FriendshipGraph() {
        this.friendGraph = new HashMap<>();
    }

    public void setFriends(String name, Friend... friends) {
        friendGraph.put(name, friends);
    }

    public ArrayList<Friend> friendRecommendations(String name) {
        Set<String> friends = new HashSet<>();
        Friend[] directFriends = friendGraph.get(name);
        if (directFriends != null) {
            for (Friend friend : directFriends) {
                if (friend != null) {
                    friends.add(friend.getName());
                }
            }
        }

        Map<String, Integer> mutualFriendCount = new HashMap<>();
        for (String friendName : friends) {
            Friend[] theirFriends = friendGraph.get(friendName);
            if (theirFriends == null) {
                continue;
            }

            for (Friend recommendation : theirFriends) {
                if (recommendation == null) {
                    continue;
                }

                String recommendationName = recommendation.getName();
                if (!recommendationName.equals(name)
                        && !friends.contains(recommendationName)) {
                    mutualFriendCount.merge(recommendationName, 1, Integer::sum);
                }
            }
        }

        ArrayList<Map.Entry<String, Integer>> recommendations = new ArrayList<>(mutualFriendCount.entrySet());
        recommendations.sort(Map.Entry.<String, Integer>comparingByValue()
                .reversed()
                .thenComparing(Map.Entry::getKey));

        ArrayList<Friend> result = new ArrayList<>();
        for (Map.Entry<String, Integer> recommendation : recommendations) {
            Friend recommendedFriend = findFriend(recommendation.getKey());
            if (recommendedFriend != null) {
                result.add(recommendedFriend);
            }
        }
        return result;
    }

    public Integer shortestDistance(String source, String destination) {
        FriendTraversedGraph result = findPath(source, destination);
        return result == null ? -1 : result.getDistance();
    }

    public ArrayList<Friend> shortedPath(String source, String destination) {
        FriendTraversedGraph result = findPath(source, destination);
        return result == null ? new ArrayList<>() : result.getTraversed();
    }

    private FriendTraversedGraph findPath(String source, String destination) {
        if (!friendGraph.containsKey(source) || !friendGraph.containsKey(destination)) {
            return null;
        }

        Set<String> visited = new HashSet<>();
        Queue<FriendTraversedGraph> queue = new ArrayDeque<>();

        Friend sourceFriend = findFriend(source);
        if (sourceFriend == null) {
            return null;
        }
        ArrayList<Friend> sourcePath = new ArrayList<>();
        sourcePath.add(sourceFriend);
        queue.add(new FriendTraversedGraph(sourceFriend, sourcePath, 0));
        visited.add(source);

        while (!queue.isEmpty()) {
            FriendTraversedGraph current = queue.poll();
            Friend currentFriend = current.getFriend();

            if (currentFriend.getName().equals(destination)) {
                return current;
            }

            Friend[] friends = friendGraph.get(currentFriend.getName());
            if (friends == null) {
                continue;
            }

            for (Friend friend : friends) {
                if (friend != null && visited.add(friend.getName())) {
                    ArrayList<Friend> path = new ArrayList<>(current.getTraversed());
                    path.add(friend);
                    queue.add(new FriendTraversedGraph(friend, path, current.getDistance() + 1));
                }
            }
        }

        return null;
    }

    private Friend findFriend(String name) {
        for (Friend[] friends : friendGraph.values()) {
            if (friends == null) {
                continue;
            }
            for (Friend friend : friends) {
                if (friend != null && friend.getName().equals(name)) {
                    return friend;
                }
            }
        }
        return null;
    }
}

class FriendTraversedGraph {
    private Friend friend;
    private ArrayList<Friend> traversed;
    private int distance;

    public FriendTraversedGraph(Friend friend, ArrayList<Friend> traversed, int distance) {
        this.friend = friend;
        this.traversed = traversed;
        this.distance = distance;
    }

    public Friend getFriend() {
        return friend;
    }

    public void setFriend(Friend friend) {
        this.friend = friend;
    }

    public ArrayList<Friend> getTraversed() {
        return traversed;
    }

    public void setTraversed(ArrayList<Friend> traversed) {
        this.traversed = traversed;
    }

    public int getDistance() {
        return distance;
    }

    public void setDistance(int distance) {
        this.distance = distance;
    }
}

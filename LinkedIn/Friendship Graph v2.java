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

import java.util.*;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        FriendshipGraph graph = new FriendshipGraph();

        graph.addFriendship("A", "B");
        graph.addFriendship("A", "C");
        graph.addFriendship("B", "D");
        graph.addFriendship("B", "E");
        graph.addFriendship("C", "F");
        graph.addFriendship("E", "F");

        System.out.println("Shortest path A -> F: "
                + graph.shortestPath("A", "F"));

        System.out.println("Shortest distance A -> F: "
                + graph.shortestDistance("A", "F"));

        System.out.println("Recommendations for A: "
                + graph.suggestFriends("A"));
    }
}

class FriendshipGraph {

    private final Map<String, Set<String>> graph = new HashMap<>();

    // Add a user to the graph, even if they have no friends.
    public void addUser(String user) {
        graph.putIfAbsent(user, new HashSet<>());
    }

    // Friendships are assumed to be undirected.
    public void addFriendship(String userA, String userB) {
        addUser(userA);
        addUser(userB);

        if (userA.equals(userB)) {
            return;
        }

        graph.get(userA).add(userB);
        graph.get(userB).add(userA);
    }

    // Part 1: Return shortest path from source to destination.
    // Returns empty list if either user is missing or no path exists.
    public List<String> shortestPath(String source, String destination) {
        if (!graph.containsKey(source) || !graph.containsKey(destination)) {
            return Collections.emptyList();
        }

        if (source.equals(destination)) {
            return Collections.singletonList(source);
        }

        Queue<String> queue = new ArrayDeque<>();
        Set<String> visited = new HashSet<>();

        // parent maps each discovered user to the user we reached them from.
        Map<String, String> parent = new HashMap<>();

        queue.offer(source);
        visited.add(source);

        while (!queue.isEmpty()) {
            String current = queue.poll();

            for (String neighbor : graph.get(current)) {
                if (!visited.add(neighbor)) {
                    continue;
                }

                parent.put(neighbor, current);

                // Destination found. Reconstruct path only once.
                if (neighbor.equals(destination)) {
                    return buildPath(source, destination, parent);
                }

                queue.offer(neighbor);
            }
        }

        return Collections.emptyList();
    }

    private List<String> buildPath(
            String source,
            String destination,
            Map<String, String> parent) {

        LinkedList<String> path = new LinkedList<>();

        String current = destination;

        while (current != null) {
            path.addFirst(current);

            if (current.equals(source)) {
                break;
            }

            current = parent.get(current);
        }

        return path;
    }

    // Part 2: Return shortest distance.
    // Reuses shortestPath() instead of implementing BFS again.
    public int shortestDistance(String source, String destination) {
        List<String> path = shortestPath(source, destination);

        if (path.isEmpty()) {
            return -1;
        }

        // Number of edges = number of nodes - 1.
        return path.size() - 1;
    }

    // Part 3: Recommend friends based on mutual connections.
    // Returns names sorted by mutual-friend count descending.
    public List<Recommendation> suggestFriends(String user) {
        if (!graph.containsKey(user)) {
            return Collections.emptyList();
        }

        Set<String> directFriends = graph.get(user);

        // candidate -> number of mutual friends
        Map<String, Integer> mutualFriendCounts = new HashMap<>();

        // Traverse the friends of each direct friend.
        for (String friend : directFriends) {
            for (String candidate : graph.get(friend)) {

                // Exclude the user and their existing direct friends.
                if (candidate.equals(user)
                        || directFriends.contains(candidate)) {
                    continue;
                }

                mutualFriendCounts.merge(candidate, 1, Integer::sum);
            }
        }

        List<Recommendation> recommendations = new ArrayList<>();

        for (Map.Entry<String, Integer> entry
                : mutualFriendCounts.entrySet()) {

            recommendations.add(
                    new Recommendation(
                            entry.getKey(),
                            entry.getValue()
                    )
            );
        }

        // Rank by mutual connections descending.
        // Use name as deterministic tie-breaker.
        recommendations.sort(
                Comparator
                        .comparingInt(Recommendation::getMutualFriends)
                        .reversed()
                        .thenComparing(Recommendation::getUser)
        );

        return recommendations;
    }

    public static class Recommendation {
        private final String user;
        private final int mutualFriends;

        public Recommendation(String user, int mutualFriends) {
            this.user = user;
            this.mutualFriends = mutualFriends;
        }

        public String getUser() {
            return user;
        }

        public int getMutualFriends() {
            return mutualFriends;
        }

        @Override
        public String toString() {
            return user + " (mutual friends: " + mutualFriends + ")";
        }
    }
}


/**
 * LeetCode 743 — Network Delay Time
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   n nodes (1..n). Directed weighted edges: times[i] = [u, v, w] means signal
 *   travels from u to v in time w. Signal sent from node k.
 *   Return time for signal to reach ALL nodes, or -1 if impossible.
 *
 *   This is: single-source shortest path → Dijkstra's algorithm.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Dijkstra's Algorithm
 * ─────────────────────────────────────────────────────────────────────────────
 *   Greedily expand the closest unvisited node first.
 *   Use a min-heap (priority queue) of (distance, node).
 *
 *   ALGORITHM:
 *   1. dist[k] = 0; all others = INF.
 *   2. Push (0, k) to min-heap.
 *   3. While heap not empty:
 *      a. Pop (d, u) — closest unexplored node.
 *      b. If d > dist[u] → stale entry, skip. (lazy deletion)
 *      c. For each edge (u → v, weight w):
 *         If dist[u] + w < dist[v] → relax: dist[v] = dist[u] + w, push to heap.
 *   4. Answer = max(dist[1..n]). If any is INF → return -1.
 *
 *   WHY GREEDY WORKS: All edge weights are positive. The first time we pop a node,
 *   we've found its shortest path. A shorter path through a later node is impossible
 *   since all weights > 0 (adding more edges only increases distance).
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O((V + E) log V) — each edge processed once; heap ops O(log V)
 *   SPACE: O(V + E) — adjacency list + dist array
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   Node k has no outgoing edges → all others unreachable → -1
 *   Graph is disconnected → some dist remain INF → -1
 *   n == 1 → only source, answer = 0
 *
 * INTERVIEW TIP:
 *   Dijkstra = BFS + priority queue + non-negative weights.
 *   If negative weights: use Bellman-Ford (O(VE)).
 *   If all weights equal: plain BFS suffices (O(V+E)).
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (n=4, edges=[[2,1,1],[2,3,1],[3,4,1]], k=2)
 * ─────────────────────────────────────────────────────────────────────────────
 *   Signal starts at node 2. Build adjacency: 2→(1,w1),(3,w1); 3→(4,w1).
 *   dist[2]=0; push (0,2). Pop (0,2); relax 1: dist[1]=1; relax 3: dist[3]=1.
 *   Pop (1,1) or (1,3) — eventually dist[4]=dist[3]+1=2. All reachable.
 *   max(dist[1..4]) = 2  → answer 2 ✓
 *
 *   If we remove edge (3,4), node 4 stays INF → return -1.

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Dijkstra shortest path is the backbone of network routing:
 *   - Internet routing: OSPF (Open Shortest Path First) protocol uses Dijkstra
 *     to compute shortest paths in an autonomous system.
 *   - GPS / mapping (Google Maps, Apple Maps): find the fastest driving route
 *     in a weighted road graph.
 *   - CDN edge routing: route a user request to the lowest-latency edge node
 *     using measured link latencies as edge weights.
 *   - Game AI: pathfinding in weighted terrain (movement cost per tile
 *     in strategy games) uses Dijkstra or A*.
 */

#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    // Build adjacency list (1-indexed nodes)
    vector<vector<pair<int,int>>> adj(n + 1);
    for (const auto& t : times) {
        adj[t[0]].push_back({t[1], t[2]}); // {destination, weight}
    }

    vector<int> dist(n + 1, INT_MAX);
    dist[k] = 0;

    // Min-heap: {distance, node}
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, k});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();

        if (d > dist[u]) continue; // stale entry: already found a shorter path

        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    int max_dist = 0;
    for (int i = 1; i <= n; ++i) {
        if (dist[i] == INT_MAX) return -1; // unreachable node
        max_dist = max(max_dist, dist[i]);
    }
    return max_dist;
}

int main() {
    vector<vector<int>> times = {{2,1,1},{2,3,1},{3,4,1}};
    std::cout << networkDelayTime(times, 4, 2) << '\n'; // 2

    vector<vector<int>> t2 = {{1,2,1}};
    std::cout << networkDelayTime(t2, 2, 2) << '\n'; // -1 (can't reach node 1)
    return 0;
}

/**
 * LeetCode 973 — K Closest Points to Origin
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Return the k closest points to the origin (0,0) from a list of points.
 *   Distance = Euclidean: sqrt(x^2 + y^2). Answer in any order.
 *
 *   Example: points=[[-2,2],[1,3]], k=1 → [[-2,2]]
 *   (distances: sqrt(8) vs sqrt(10) → [-2,2] is closer)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Compare squared distances — no sqrt needed
 * ─────────────────────────────────────────────────────────────────────────────
 *   sqrt is monotone: a < b ↔ sqrt(a) < sqrt(b) for a,b >= 0.
 *   So we can compare x^2+y^2 directly and avoid expensive sqrt calls.
 *
 *   APPROACH 1: Max-heap of size k — O(n log k)
 *   Keep the k closest seen. If heap has k elements and new point is closer
 *   than the farthest (heap.top()), swap them.
 *
 *   APPROACH 2: Partial sort (nth_element) — O(n) average
 *   Use std::partial_sort or nth_element on squared distance. Same idea as QuickSelect.
 *
 *   WORKED EXAMPLE  (points = [[-2,2],[1,3]], k = 1)
 *   d²(-2,2) = 4+4 = 8.  d²(1,3) = 1+9 = 10.  Smaller is 8 → return [[-2,2]].
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   Max-heap:     O(n log k) time, O(k) space
 *   nth_element:  O(n) average, O(1) extra space
 *
 * CORNER CASES:
 *   k == n → return all points
 *   Points equidistant → any k of them valid
 *   Origin in input → distance 0, always in result for any k >= 1

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   K-nearest neighbors (KNN) in 2D space is widely used in location-based services:
 *   - GPS / mapping apps: find the k nearest restaurants, gas stations, or ATMs
 *     to the user current location.
 *   - Recommendation systems: find the k most similar users or items in a
 *     feature vector space (collaborative filtering, embedding similarity).
 *   - Computer graphics: k-nearest-neighbor queries in 3D point clouds for
 *     surface reconstruction and rendering (LiDAR, photogrammetry).
 *   - Machine learning (KNN classifier): classify a new point by majority vote
 *     of its k nearest training examples.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Approach 1: Max-heap of size k
vector<vector<int>> kClosestHeap(vector<vector<int>> points, int k) {
    // max-heap on squared distance
    auto dist2 = [](const vector<int>& p) {
        return p[0]*p[0] + p[1]*p[1];
    };
    auto cmp = [&](const vector<int>& a, const vector<int>& b) {
        return dist2(a) < dist2(b); // max at top
    };
    priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> heap(cmp);

    for (auto& p : points) {
        heap.push(p);
        if (static_cast<int>(heap.size()) > k) heap.pop(); // evict farthest
    }

    vector<vector<int>> result;
    while (!heap.empty()) { result.push_back(heap.top()); heap.pop(); }
    return result;
}

// Approach 2: nth_element (O(n) avg)
vector<vector<int>> kClosest(vector<vector<int>> points, int k) {
    auto dist2 = [](const vector<int>& p) { return p[0]*p[0] + p[1]*p[1]; };
    nth_element(points.begin(), points.begin() + k, points.end(),
                [&](const vector<int>& a, const vector<int>& b) {
                    return dist2(a) < dist2(b);
                });
    return {points.begin(), points.begin() + k};
}

int main() {
    auto r1 = kClosest({{1,3},{-2,2}}, 1);
    for (auto& p : r1) std::cout << '[' << p[0] << ',' << p[1] << "]\n"; // [-2,2]

    auto r2 = kClosest({{3,3},{5,-1},{-2,4}}, 2);
    for (auto& p : r2) std::cout << '[' << p[0] << ',' << p[1] << "]\n"; // [3,3],[-2,4]
    return 0;
}

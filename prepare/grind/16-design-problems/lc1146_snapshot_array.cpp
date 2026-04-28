/**
 * LeetCode 1146 — Snapshot Array
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Design a snapshot array of given length supporting:
 *   - set(index, val): set arr[index] = val
 *   - snap(): take a snapshot, return snap_id (increments each call)
 *   - get(index, snap_id): return arr[index] at the time of snap_id
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Store only changes per index, binary search for snap_id
 * ─────────────────────────────────────────────────────────────────────────────
 *   NAIVE: Store full copy on every snap() → O(length) per snap, too much memory.
 *
 *   OPTIMAL: For each index, keep a sorted list of (snap_id, value) pairs.
 *   Only store when value actually changes.
 *
 *   get(index, snap_id):
 *     Binary search in history[index] for largest snap_id ≤ requested snap_id.
 *     Returns value at that entry.
 *
 *   WHY BINARY SEARCH: Entries are sorted by snap_id (we always append).
 *   upper_bound - 1 gives the latest snap_id ≤ query.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE
 * ─────────────────────────────────────────────────────────────────────────────
 *   SnapshotArray(3): history = [{(0,0)}, {(0,0)}, {(0,0)}], snap_id=0
 *   set(0, 5):  history[0] = [(0,5)] (overwrite since still snap 0)
 *   snap():     returns 0, snap_id becomes 1
 *   set(0, 6):  history[0] = [(0,5), (1,6)]
 *   get(0, 0):  binary search in [(0,5),(1,6)] for snap_id ≤ 0 → (0,5) → return 5
 *   get(0, 1):  binary search for snap_id ≤ 1 → (1,6) → return 6
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   set:  O(1) amortized
 *   snap: O(1)
 *   get:  O(log(number of snaps for that index))
 *   SPACE: O(set operations) — only stores actual changes

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Copy-on-write snapshots with binary search are fundamental in versioned systems:
 *   - Database MVCC (Multi-Version Concurrency Control): PostgreSQL and InnoDB store
 *     multiple versions of each row so readers see a consistent snapshot without
 *     blocking writers — each version has a transaction ID (like snap_id).
 *   - Git commit history: each file blob stores only changes; reconstructing a
 *     file at a commit uses binary search over the ancestry chain.
 *   - Persistent data structures (functional programming): immutable data
 *     structures (Clojure, Scala) share unchanged nodes across versions.
 *   - Audit logs: retrieve the value of any field as of a past timestamp
 *     using binary search over the change history.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class SnapshotArray {
    // history[i] = sorted list of (snap_id, value)
    vector<vector<pair<int,int>>> history;
    int snap_id = 0;
public:
    SnapshotArray(int length) : history(length) {
        // Initialize each index with value 0 at snap 0
        for (auto& h : history) h.push_back({0, 0});
    }

    void set(int index, int val) {
        auto& h = history[index];
        if (h.back().first == snap_id) {
            h.back().second = val; // update within same snapshot
        } else {
            h.push_back({snap_id, val}); // new snapshot entry
        }
    }

    int snap() {
        return snap_id++;
    }

    int get(int index, int snap_id_query) const {
        const auto& h = history[index];
        // Find last entry with snap_id <= snap_id_query
        // upper_bound finds first > query; go one back
        auto it = upper_bound(h.begin(), h.end(),
                              make_pair(snap_id_query, INT_MAX));
        --it; // guaranteed to exist since we init with snap 0
        return it->second;
    }
};

int main() {
    SnapshotArray sa(3);
    sa.set(0, 5);
    std::cout << sa.snap()        << '\n'; // 0
    sa.set(0, 6);
    std::cout << sa.get(0, 0)     << '\n'; // 5 (value at snap 0)
    std::cout << sa.get(0, 1)     << '\n'; // 6 (value at snap 1... snap_id=1 not taken yet)
    return 0;
}

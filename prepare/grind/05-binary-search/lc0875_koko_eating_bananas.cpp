/**
 * LeetCode 875 — Koko Eating Bananas
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   piles[i] = number of bananas in pile i. Koko eats at speed k bananas/hour.
 *   Each hour she picks ONE pile and eats min(k, remaining) from it.
 *   Given h hours total, find the MINIMUM integer k that lets her finish all piles.
 *
 *   Example: piles=[3,6,7,11], h=8 → k=4
 *   At k=4: pile 3 → 1h, pile 6 → 2h, pile 7 → 2h, pile 11 → 3h. Total=8h. ✓
 *   At k=3: pile 3→1, pile 6→2, pile 7→3, pile 11→4. Total=10h. ✗
 *
 * CONSTRAINTS:
 *   1 <= piles.length <= 10^4
 *   1 <= piles[i] <= 10^9
 *   piles.length <= h <= 10^9
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Binary Search on the ANSWER
 * ─────────────────────────────────────────────────────────────────────────────
 *   The naive approach: try every speed from 1 to max(piles). O(n * max(piles)).
 *   That's too slow when piles[i] can be 10^9.
 *
 *   The key observation is that the answer space (possible values of k) has a
 *   MONOTONE property:
 *
 *     k=1   k=2   k=3   k=4   k=5   k=6  ...  k=max
 *     ✗     ✗     ✗     ✓     ✓     ✓    ...  ✓
 *                        ^
 *                   answer is here (first ✓)
 *
 *   Once k is large enough to finish in time, any larger k also finishes in time
 *   (faster speed = same or fewer hours). So the answer space looks like:
 *   [all ✗, then all ✓]. This is the exact shape binary search exploits.
 *
 *   We're not searching the piles array — we're searching the RANGE OF SPEEDS.
 *   This technique is called "binary search on the answer."
 *
 *   BOUNDS:
 *   - lo = 1           (must eat at least 1 banana/hour)
 *   - hi = max(piles)  (at this speed, every pile takes exactly 1 hour → always
 *                       feasible because h >= piles.size() is guaranteed)
 *
 *   FEASIBILITY CHECK: hours(k) = Σ ceil(piles[i] / k)
 *   "Can Koko finish at speed k?" ↔ hours(k) <= h
 *
 *   WHY ceil(piles[i] / k)?
 *   Koko eats ONE pile per session. If the pile has 7 bananas and k=4:
 *     hour 1: eats 4 (3 left), hour 2: eats 3 → 2 hours = ceil(7/4) = 2 ✓
 *   In C++: ceil(a/b) for positive integers = (a + b - 1) / b
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * BINARY SEARCH TEMPLATE: Find LEFTMOST k where condition holds
 * ─────────────────────────────────────────────────────────────────────────────
 *   This template finds the minimum valid k. Study how hi and lo move:
 *
 *   lo=1, hi=max(piles)
 *   while lo < hi:           ← loop until lo and hi converge to one value
 *     mid = lo + (hi-lo)/2   ← avoids integer overflow (vs (lo+hi)/2)
 *     if feasible(mid):
 *       hi = mid             ← mid WORKS, but a smaller value might also work.
 *                            ← CRITICAL: hi = mid, NOT hi = mid-1, because mid
 *                               itself could be the answer. We must not skip it.
 *     else:
 *       lo = mid + 1         ← mid is too slow. lo=mid would infinite-loop since
 *                            ← mid = lo when hi=lo+1. So we advance past mid.
 *   return lo                ← when loop ends, lo == hi == first feasible k
 *
 *   WHY lo == hi IS THE ANSWER:
 *   The invariant maintained is: answer is always in [lo, hi].
 *   - When mid is feasible: answer could be mid or lower → hi = mid keeps mid in range.
 *   - When mid is not feasible: answer must be > mid → lo = mid+1 is safe.
 *   When lo == hi, the range has one element — that's the answer.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (piles=[3,6,7,11], h=8)
 * ─────────────────────────────────────────────────────────────────────────────
 *   lo=1, hi=11
 *   mid=6: hours = ceil(3/6)+ceil(6/6)+ceil(7/6)+ceil(11/6) = 1+1+2+2=6 <=8 → hi=6
 *   lo=1, hi=6
 *   mid=3: hours = ceil(3/3)+ceil(6/3)+ceil(7/3)+ceil(11/3) = 1+2+3+4=10 >8  → lo=4
 *   lo=4, hi=6
 *   mid=5: hours = ceil(3/5)+ceil(6/5)+ceil(7/5)+ceil(11/5) = 1+2+2+3=8 <=8  → hi=5
 *   lo=4, hi=5
 *   mid=4: hours = ceil(3/4)+ceil(6/4)+ceil(7/4)+ceil(11/4) = 1+2+2+3=8 <=8  → hi=4
 *   lo=4, hi=4 → stop. Return 4. ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n log M) where M = max(piles)
 *          Binary search runs O(log M) iterations; each feasibility check is O(n).
 *   SPACE: O(1)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   h == piles.size(): must eat each pile in exactly 1 visit → k = max(piles).
 *   Single pile [1000000000], h=1: k = 10^9, handled correctly.
 *   Use long long in hours() to avoid overflow when summing ceil values.
 *
 * INTERVIEW TIP:
 *   When you see "find minimum/maximum X such that [condition involving X],"
 *   and the condition is monotone, think "binary search on answer."
 *   Other examples of same pattern: LC 1011 (ship packages), LC 410, LC 2064.

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Binary search on the answer (find minimum feasible rate/capacity) appears in
 *   many capacity planning problems:
 *   - CI/CD pipeline throttling: find the minimum build concurrency that finishes
 *     all builds within a deadline.
 *   - Database connection pool sizing: find the minimum pool size such that
 *     all queries complete within SLA.
 *   - Content delivery: find the minimum upload bandwidth that serves all users
 *     within a buffering deadline.
 *   - Kubernetes resource requests: binary search the minimum CPU request that
 *     keeps pod latency under a target.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

long long hoursAtSpeed(const vector<int>& piles, int k) {
    long long total = 0;
    for (int p : piles) {
        total += (static_cast<long long>(p) + k - 1) / k; // ceil(p/k)
    }
    return total;
}

int minEatingSpeed(const vector<int>& piles, int h) {
    int lo = 1;
    int hi = *max_element(piles.begin(), piles.end());
    while (lo < hi) {
        const int mid = lo + (hi - lo) / 2;
        if (hoursAtSpeed(piles, mid) <= h) {
            hi = mid; // mid works, try smaller
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

int main() {
    cout << minEatingSpeed({3, 6, 7, 11}, 8) << '\n'; // 4
    cout << minEatingSpeed({30, 11, 23, 4, 20}, 5) << '\n'; // 30
    return 0;
}

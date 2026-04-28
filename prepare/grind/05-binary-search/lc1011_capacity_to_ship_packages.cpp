/**
 * LeetCode 1011 — Capacity To Ship Packages Within D Days
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   A conveyor belt has packages in a fixed order (weights[]). A ship loads
 *   packages each day in that order — you CANNOT reorder them.
 *   Each day you load as many consecutive packages as fit without exceeding
 *   the ship's capacity C (sum of that day's packages <= C).
 *   Find the MINIMUM capacity C so that ALL packages ship within D days.
 *
 *   Example: weights=[1,2,3,4,5,6,7,8,9,10], days=5 → C=15
 *   With C=15: Day1:[1,2,3,4,5]=15, Day2:[6,7]=13, Day3:[8]=8,
 *              Day4:[9]=9, Day5:[10]=10 → 5 days ✓
 *   With C=14: Day1:[1,2,3,4]=10, Day2:[5,6]=11, Day3:[7]=7,
 *              Day4:[8]=8, Day5:[9]=9 → 6th day still has 10 → ✗
 *
 * CONSTRAINTS:
 *   1 <= days <= weights.length <= 5×10^4
 *   1 <= weights[i] <= 500
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Binary Search on the ANSWER (same pattern as LC 875)
 * ─────────────────────────────────────────────────────────────────────────────
 *   We're searching over possible values of C (capacity), not over the array.
 *   The answer space has a MONOTONE property:
 *
 *     C=lo  ...  C=ans-1  C=ans  C=ans+1  ...  C=hi
 *      ✗    ...    ✗        ✓      ✓      ...   ✓
 *                           ^
 *                      minimum feasible C
 *
 *   If capacity C is enough to finish in D days, then C+1 is also enough
 *   (more capacity → same or fewer days needed). So it's all-✗-then-all-✓.
 *   Binary search finds the first ✓ in O(log(sum)) instead of O(sum).
 *
 *   SEARCH BOUNDS — WHY THESE VALUES?
 *   - lo = max(weights): Every package must fit on the ship in one day.
 *     If C < max(weights), the heaviest package NEVER ships. So lo is a hard floor.
 *   - hi = sum(weights): Load everything in one day → always done in 1 day <= D days.
 *     This is always feasible, so it's a valid upper bound.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * FEASIBILITY CHECK: canShip(C) — greedy partitioning
 * ─────────────────────────────────────────────────────────────────────────────
 *   Given capacity C, the minimum number of days needed is found by a greedy scan:
 *   Start a new day. Keep adding packages to the current day as long as the
 *   running total doesn't exceed C. When it would exceed C, start a new day
 *   with that package.
 *
 *   WHY GREEDY IS CORRECT: Loading as much as possible each day never wastes a
 *   day slot. Any other strategy that loads LESS today would push MORE to future
 *   days, requiring >= as many days total.
 *
 *   Example: weights=[1,2,3,4,5,6,7,8,9,10], C=15
 *     Day 1: cur=1 → +2=3 → +3=6 → +4=10 → +5=15 → next(6) would exceed → new day
 *     Day 2: cur=6 → +7=13 → next(8) would exceed → new day
 *     Day 3: cur=8 → next(9) would exceed → new day
 *     Day 4: cur=9 → next(10) would exceed → new day
 *     Day 5: cur=10 → done.    need=5 <= D=5 → feasible ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (weights=[3,2,2,4,1,4], days=3)
 * ─────────────────────────────────────────────────────────────────────────────
 *   lo = max(3,2,2,4,1,4) = 4,  hi = 3+2+2+4+1+4 = 16
 *
 *   Iter 1: mid=10. canShip(10)?
 *     Day1:[3,2,2]=7→+4=11>10→new. Day2:[4,1,4]=9. need=2 <= 3 ✓ → hi=10
 *   Iter 2: lo=4,hi=10. mid=7. canShip(7)?
 *     Day1:[3,2,2]=7→+4=11>7→new. Day2:[4,1]=5→+4=9>7→new. Day3:[4]. need=3 <= 3 ✓ → hi=7
 *   Iter 3: lo=4,hi=7. mid=5. canShip(5)?
 *     Day1:[3,2]=5→+2=7>5→new. Day2:[2,1]=3→wait: [2]+[2]=4→+4=8>5→new, so [2,2]=4 then +1=5→+4=9>5→new.
 *     Actually: cur=0+2=2,+2=4,+1=5,+4=9>5→new. Day3:[4]. need=3 ✓ → hi=5
 *     Wait let me redo: weights=[3,2,2,4,1,4]:
 *     cur=0+3=3, +2=5, +2=7>5→new day. cur=2, +4=6>5→new day. cur=4, +1=5, +4=9>5→new day.
 *     cur=4. need=4 > 3 ✗ → lo=6
 *   Iter 4: lo=6,hi=7. mid=6. canShip(6)?
 *     cur=3,+2=5,+2=7>6→new. cur=2,+4=6,+1=7>6→new. cur=1,+4=5. need=3 <=3 ✓ → hi=6
 *   lo=6,hi=6 → return 6 ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n log S) where S = sum(weights)
 *          Binary search: O(log S) iterations. Each feasibility check: O(n).
 *   SPACE: O(1) — no extra data structures
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   days == weights.size() → one package per day → C = max(weights) = lo
 *   days == 1              → all packages in one day → C = sum(weights) = hi
 *   All same weights       → binary search still works correctly
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Minimum capacity to complete ordered work in D days appears everywhere:
 *   - Logistics / shipping: find the minimum truck load capacity to ship all
 *     warehouse orders within a guaranteed delivery window (same problem literally).
 *   - Distributed job scheduling: find the minimum worker throughput to process
 *     a batch job queue within a deadline (Hadoop, Spark job sizing).
 *   - Cloud cost optimization: find the minimum VM size (CPU/memory) such that
 *     all tasks in a pipeline complete within a time budget.
 *   - Content delivery: minimum CDN bandwidth to serve all video segments of a
 *     playlist within a buffering deadline.
 *
 * INTERVIEW TIP:
 *   This problem is IDENTICAL in structure to LC 875 (Koko Eating Bananas).
 *   Both are: "find minimum X such that greedy_feasibility(X) <= budget."
 *   The only difference is the feasibility function. Recognize this pattern and
 *   you can solve LC 410, LC 1482, LC 2064, and many others with the same template.
 */

#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

bool canShipWithinDays(const vector<int>& weights, int capacity, int days) {
    int need = 1;
    long long cur = 0;
    for (int w : weights) {
        if (cur + w > capacity) {
            ++need;
            cur = w;
        } else {
            cur += w;
        }
    }
    return need <= days;
}

int shipWithinDays(const vector<int>& weights, int days) {
    int lo = *max_element(weights.begin(), weights.end());
    int hi = accumulate(weights.begin(), weights.end(), 0);
    while (lo < hi) {
        const int mid = lo + (hi - lo) / 2;
        if (canShipWithinDays(weights, mid, days)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

int main() {
    cout << shipWithinDays({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5) << '\n'; // 15
    cout << shipWithinDays({3, 2, 2, 4, 1, 4}, 3) << '\n';               // 6
    return 0;
}

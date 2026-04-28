/**
 * LeetCode 11 — Container With Most Water
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   height[i] is the height of a vertical line at position i.
 *   Choose two lines i < j to form a container with the x-axis.
 *   Area = (j - i) * min(height[i], height[j]).
 *   Return the maximum area.
 *
 *   Example: height = [1,8,6,2,5,4,8,3,7]
 *   Best pair: i=1 (h=8), j=8 (h=7) → area = 7 * 7 = 49
 *
 * CONSTRAINTS:
 *   2 <= height.length <= 10^5
 *   0 <= height[i] <= 10^4
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * BRUTE FORCE
 * ─────────────────────────────────────────────────────────────────────────────
 *   Try every pair (i,j): O(n^2) time, O(1) space. Too slow for n=10^5.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Always move the shorter pointer inward
 * ─────────────────────────────────────────────────────────────────────────────
 *   Start with L=0, R=n-1 (widest possible container).
 *   Area = (R - L) * min(height[L], height[R])
 *
 *   WHY move the SHORTER side?
 *   Suppose height[L] < height[R]. Consider what happens if we move R inward:
 *   - Width decreases by 1 (always bad).
 *   - min(height[L], new_height[R]) <= height[L]   ← it was already capped by L!
 *     → Area can ONLY get worse or the same. We can safely skip ALL pairs (L, R-1),
 *       (L, R-2), … because height[L] is the bottleneck no matter what's on the right.
 *
 *   So moving the shorter side is the ONLY move that could possibly improve area.
 *   Moving the taller side is provably never better → we discard it.
 *
 *   FORMAL ARGUMENT (for interviews):
 *   Let WLOG height[L] <= height[R].
 *   For any k in (L, R), pair (L, k): area = (k-L) * min(height[L], height[k])
 *                                           <= (k-L) * height[L]
 *                                           < (R-L) * height[L]   [since k < R]
 *                                           = current area.
 *   So all pairs with L as left anchor and some k < R are guaranteed worse.
 *   Therefore we can advance L safely.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (height = [1, 8, 6, 2, 5, 4, 8, 3, 7])
 * ─────────────────────────────────────────────────────────────────────────────
 *   Indices:   0  1  2  3  4  5  6  7  8
 *   Heights:  [1, 8, 6, 2, 5, 4, 8, 3, 7]
 *
 *   L=0(h=1), R=8(h=7): area = 8*1 = 8,  best=8.   height[L]<height[R] → L++
 *   L=1(h=8), R=8(h=7): area = 7*7 = 49, best=49.  height[L]>height[R] → R--
 *   L=1(h=8), R=7(h=3): area = 6*3 = 18, best=49.  height[L]>height[R] → R--
 *   L=1(h=8), R=6(h=8): area = 5*8 = 40, best=49.  height[L]==height[R] → R--
 *   L=1(h=8), R=5(h=4): area = 4*4 = 16, best=49.  height[L]>height[R] → R--
 *   L=1(h=8), R=4(h=5): area = 3*5 = 15, best=49.  height[L]>height[R] → R--
 *   L=1(h=8), R=3(h=2): area = 2*2 = 4,  best=49.  height[L]>height[R] → R--
 *   L=1(h=8), R=2(h=6): area = 1*6 = 6,  best=49.  height[L]>height[R] → R--
 *   L=1 >= R=1: stop.
 *   Answer: 49 ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n) — L and R together take at most n-1 steps total
 *   SPACE: O(1)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   [1, 1]       → area = 1 (only one pair)
 *   [4, 4, 4, 4] → best = 3*4 = 12 (L=0, R=3)
 *   [1, 2, 4, 3] → best = 4 (L=0,R=3 → 3; L=1,R=3 → 4)
 *   Decreasing [5,4,3,2,1]: L always moves right, checking O(n) pairs.
 *
 * INTERVIEW TIP:
 *   The #1 follow-up is "prove why moving the shorter side is correct."
 *   Use the formal argument above: moving the taller side cannot improve
 *   min(h[L],h[R]) because the shorter side is already the bottleneck.

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   The two-pointer shrink-from-outside pattern applies to any max-area / max-score
 *   problem on sorted or paired data:
 *   - Cloud storage tiering: find the two storage tiers whose combined capacity
 *     and access-frequency product is maximized.
 *   - A/B test pairing: pair users from two sorted cohorts to maximize similarity score.
 *   - Network engineering: choose two routers to maximize the minimum-bandwidth path.
 *   - Image compression: find two histogram bars bounding the most content pixels.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int maxArea(const vector<int>& height) {
    int L = 0;
    int R = static_cast<int>(height.size()) - 1;
    int best = 0;
    while (L < R) {
        const int h = min(height[L], height[R]);
        best = max(best, (R - L) * h);
        if (height[L] < height[R]) {
            ++L;
        } else {
            --R;
        }
    }
    return best;
}

int main() {
    cout << maxArea({1, 8, 6, 2, 5, 4, 8, 3, 7}) << '\n'; // 49
    return 0;
}

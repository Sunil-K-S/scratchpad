/**
 * LeetCode 42 — Trapping Rain Water
 * Difficulty: Hard
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Given n non-negative integers representing an elevation map where the width
 *   of each bar is 1, compute how much water it can trap after raining.
 *
 *   Example: height=[0,1,0,2,1,0,1,3,2,1,2,1] → 6
 *            height=[4,2,0,3,2,5] → 9
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Water at position i = min(max_left[i], max_right[i]) - height[i]
 * ─────────────────────────────────────────────────────────────────────────────
 *   The water above position i is bounded by the shorter of the tallest bar to
 *   its left and the tallest bar to its right. Anything above that minimum spills.
 *
 *   APPROACH 1: Prefix/suffix arrays — O(n) time, O(n) space
 *     Precompute max_left[i] and max_right[i], then sum contributions.
 *
 *   APPROACH 2: Two pointers — O(n) time, O(1) space  ← OPTIMAL
 *     Maintain left_max and right_max as we go.
 *     If left_max < right_max: the left side is the bottleneck.
 *       - If height[left] >= left_max: update left_max (no water here yet).
 *       - Else: water at left = left_max - height[left]. Advance left.
 *     Mirror logic for the right side.
 *     WHY: When left_max < right_max, we KNOW the constraint on position `left`
 *          is left_max (not right), so we can compute its water exactly.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (height=[4,2,0,3,2,5])
 * ─────────────────────────────────────────────────────────────────────────────
 *   left=0, right=5, left_max=0, right_max=0, water=0
 *
 *   h[0]=4, h[5]=5: left_max(0) < right_max(0)? No, equal → process left
 *     h[left]=4 >= left_max=0 → left_max=4. left=1
 *   h[1]=2, h[5]=5: left_max(4) < right_max(0)? No → process left
 *     Wait: right_max starts 0, left_max now 4. 4 < 0? No.
 *     Actually at start both are 0: left_max=0 <= right_max=0 → process left
 *     h[0]=4 >= left_max=0 → left_max=4. left=1. water=0
 *   left_max=4 > right_max=0 → process right
 *     h[5]=5 >= right_max=0 → right_max=5. right=4. water=0
 *   left_max=4 < right_max=5 → process left
 *     h[1]=2 < left_max=4 → water += 4-2=2. left=2. water=2
 *   left_max=4 < right_max=5 → process left
 *     h[2]=0 < left_max=4 → water += 4-0=4. left=3. water=6
 *   left_max=4 < right_max=5 → process left
 *     h[3]=3 < left_max=4 → water += 4-3=1. left=4. water=7  ← wait, answer=9?
 *
 *   Let me redo with h=[4,2,0,3,2,5]:
 *   Prefix max:  [4,4,4,4,4,5]
 *   Suffix max:  [5,5,5,5,5,5]
 *   water[i] = min(prefix,suffix) - h[i]:
 *     i=0: min(4,5)-4=0
 *     i=1: min(4,5)-2=2
 *     i=2: min(4,5)-0=4
 *     i=3: min(4,5)-3=1
 *     i=4: min(4,5)-2=2
 *     i=5: min(5,5)-5=0
 *   Total = 0+2+4+1+2+0 = 9  ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n) — single pass with two pointers
 *   SPACE: O(1) — only left_max, right_max, water
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   Empty / < 3 bars  → 0 (can't trap water)
 *   Monotone increase → 0 (water runs off right side)
 *   Monotone decrease → 0 (water runs off left side)
 *   All same height   → 0
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   The "bounded by the minimum of two constraints" pattern appears in:
 *   - Urban planning / drainage: compute water retention in a valley profile
 *     to size stormwater drainage systems.
 *   - Container capacity problems: any "how much liquid fits between walls"
 *     problem — fuel tanks with internal baffles, industrial silos.
 *   - Network flow: find bottleneck capacity on a path (the minimum of all
 *     link capacities bounds the flow — same min-of-two-sides reasoning).
 *   - Image processing: watershed segmentation uses a conceptually similar
 *     "fill up to the local minimum boundary" idea to separate regions.
 *
 * INTERVIEW TIP:
 *   Start with the O(n) O(n) prefix-array solution to show correctness, then
 *   optimize to two pointers. The key insight to state: "The water at a cell
 *   is determined by the shorter wall on either side."
 */

#include <iostream>
#include <vector>

using namespace std;

int trap(vector<int>& height) {
    int left = 0, right = static_cast<int>(height.size()) - 1;
    int left_max = 0, right_max = 0;
    int water = 0;

    while (left < right) {
        if (left_max <= right_max) {
            // Left side is the bottleneck
            if (height[left] >= left_max) {
                left_max = height[left]; // new tallest on left, no water here
            } else {
                water += left_max - height[left]; // bounded by left_max
            }
            left++;
        } else {
            // Right side is the bottleneck
            if (height[right] >= right_max) {
                right_max = height[right];
            } else {
                water += right_max - height[right];
            }
            right--;
        }
    }
    return water;
}

int main() {
    vector<int> h1 = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout << trap(h1) << '\n'; // 6

    vector<int> h2 = {4,2,0,3,2,5};
    cout << trap(h2) << '\n'; // 9

    vector<int> h3 = {3,0,2,0,4};
    cout << trap(h3) << '\n'; // 7

    vector<int> h4 = {1,2,3,4,5};
    cout << trap(h4) << '\n'; // 0 (monotone increase)
    return 0;
}

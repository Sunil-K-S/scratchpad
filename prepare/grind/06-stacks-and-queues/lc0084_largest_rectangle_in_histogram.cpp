/**
 * LeetCode 84 — Largest Rectangle in Histogram
 * Difficulty: Hard
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Given heights[i] (each bar has width 1), find the area of the largest
 *   rectangle that fits entirely under the histogram skyline.
 *
 *   Example: [2,1,5,6,2,3]
 *   Largest rectangle: height=5, width=2 (bars at index 2 and 3) → area=10
 *
 * CONSTRAINTS:
 *   1 <= heights.length <= 10^5
 *   0 <= heights[i] <= 10^4
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Each bar as the shortest bar in its rectangle
 * ─────────────────────────────────────────────────────────────────────────────
 *   For any bar i with height h, consider the widest rectangle where bar i
 *   is the SHORTEST bar (i.e., the height of the rectangle is exactly h).
 *   That rectangle extends:
 *   - LEFT  until the first bar shorter than h  (exclusive)
 *   - RIGHT until the first bar shorter than h  (exclusive)
 *
 *   width  = (first_shorter_right) - (first_shorter_left) - 1
 *   area   = h * width
 *
 *   We need to find "first shorter bar on the left/right" efficiently for
 *   every bar. That's exactly what a MONOTONIC INCREASING STACK computes.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * MONOTONIC INCREASING STACK — Why it works
 * ─────────────────────────────────────────────────────────────────────────────
 *   Maintain a stack of indices in INCREASING height order.
 *   When we process index i with height h:
 *     While stack top j has heights[j] > h (would break increasing order):
 *       Pop j. Now j is the bar we're computing the rectangle for.
 *       - RIGHT boundary = i  (current bar is the first shorter one on the right)
 *       - LEFT boundary  = new stack top after pop (first shorter on the left)
 *       - width = i - new_top - 1
 *       - area  = heights[j] * width
 *
 *   Sentinel trick: append a virtual bar of height 0 at the end.
 *   This forces all remaining bars in the stack to be popped and computed.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * WIDTH FORMULA EXPLAINED
 * ─────────────────────────────────────────────────────────────────────────────
 *   After popping index j:
 *   - i       = index of first shorter bar to the RIGHT (current i)
 *   - st.top()= index of first shorter bar to the LEFT  (or -1 if stack empty)
 *   - width   = i - st.top() - 1
 *
 *   Example: stack had [1, 2, 3] and we pop 3 because heights[i] < heights[3].
 *   Left boundary is index 2 (stack top after pop).
 *   Right boundary is i.
 *   Valid indices for this rectangle: 3 only (if width=1) or 3,4,... until i-1.
 *   width = i - 2 - 1 = i - 3. Correct.
 *
 *   If stack is empty after pop: no shorter bar on the left → width = i (the
 *   rectangle spans from index 0 to i-1).
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (heights = [2, 1, 5, 6, 2, 3])
 * ─────────────────────────────────────────────────────────────────────────────
 *   Append sentinel → [2, 1, 5, 6, 2, 3, 0]  (index 6 = 0)
 *   best = 0, stack = []
 *
 *   i=0 (h=2): stack empty → push 0.          stack=[0]
 *   i=1 (h=1): 1<2 → pop 0 (h=2):
 *     width = 1 - (empty→) 0 = 1.  area=2*1=2. best=2.
 *     stack empty, 1<nothing → push 1.        stack=[1]
 *   i=2 (h=5): 5>=1 → push 2.                 stack=[1,2]
 *   i=3 (h=6): 6>=5 → push 3.                 stack=[1,2,3]
 *   i=4 (h=2): 2<6 → pop 3 (h=6):
 *     new top=2. width=4-2-1=1. area=6*1=6. best=6.
 *     2<5 → pop 2 (h=5):
 *     new top=1. width=4-1-1=2. area=5*2=10. best=10.
 *     2>=1 → stop. push 4.                    stack=[1,4]
 *   i=5 (h=3): 3>=2 → push 5.                 stack=[1,4,5]
 *   i=6 (h=0, sentinel): 0<3 → pop 5 (h=3):
 *     new top=4. width=6-4-1=1. area=3*1=3. best=10.
 *     0<2 → pop 4 (h=2):
 *     new top=1. width=6-1-1=4. area=2*4=8. best=10.
 *     0<1 → pop 1 (h=1):
 *     stack empty. width=6. area=1*6=6. best=10.
 *     stack empty, done.
 *
 *   Answer: 10 ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n) — each index pushed once, popped at most once
 *   SPACE: O(n) — stack holds up to n indices
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   [5]          → 5 (single bar)
 *   [3,3,3]      → 9 (whole width, height 3; sentinel flushes all at once)
 *   [1,2,3,4,5]  → 9 (increasing; sentinel pops all: 5*1, 4*2, 3*3=9, 2*4=8, 1*5=5)
 *   [5,4,3,2,1]  → 9 (decreasing; each new bar pops previous)
 *
 * INTERVIEW TIP:
 *   Compare with LC 739 (Daily Temperatures): that uses monotonic DECREASING
 *   stack for "next greater element." This uses monotonic INCREASING stack for
 *   "first smaller element on each side." Know both variants.

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Maximum rectangle in a histogram solves largest-contiguous-block problems:
 *   - Data visualization: find the largest rectangular region in a bar chart
 *     that can be highlighted / shaded uniformly.
 *   - Database column store compression: find the largest run of rows where a
 *     column value stays above a threshold for run-length encoding.
 *   - Skyline / urban planning: the building skyline problem (LC218) reduces to
 *     a similar monotonic stack approach.
 *   - Memory allocators: find the largest contiguous free block in a fragmented
 *     heap — represented as a histogram of free page counts.
 */

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int largestRectangleArea(const vector<int>& heights) {
    stack<int> st;
    int best = 0;
    const int n = static_cast<int>(heights.size());

    for (int i = 0; i <= n; ++i) {
        const int h = (i == n) ? 0 : heights[i];
        while (!st.empty() && h < heights[st.top()]) {
            const int height = heights[st.top()];
            st.pop();
            // After pop, st.top() is first index left with height < `height`
            const int width = st.empty() ? i : i - st.top() - 1;
            best = max(best, height * width);
        }
        st.push(i);
    }
    return best;
}

int main() {
    cout << largestRectangleArea({2, 1, 5, 6, 2, 3}) << '\n'; // 10
    cout << largestRectangleArea({2, 4}) << '\n';           // 4
    return 0;
}

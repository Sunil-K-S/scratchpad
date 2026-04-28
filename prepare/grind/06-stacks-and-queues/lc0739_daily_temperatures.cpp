/**
 * LeetCode 739 — Daily Temperatures
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Given an array temperatures[i], for each day i return how many days
 *   you must wait until a strictly warmer temperature. If no future warmer
 *   day exists, answer[i] = 0.
 *
 *   Example: [73,74,75,71,69,72,76,73]
 *   Output:  [ 1, 1, 4, 2, 1, 1, 0, 0]
 *
 * CONSTRAINTS:
 *   1 <= temperatures.length <= 10^5
 *   30 <= temperatures[i] <= 100
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Monotonic Decreasing Stack
 * ─────────────────────────────────────────────────────────────────────────────
 *   We want, for each i, the NEXT index j > i where temps[j] > temps[i].
 *
 *   Brute force: for each i, scan j = i+1 until temps[j] > temps[i]. O(n^2).
 *
 *   Observation: we have "pending" days waiting for their warmer future.
 *   Keep a stack of indices whose "next warmer day" we haven't found yet.
 *   The stack is maintained in DECREASING temperature order (monotonic decreasing).
 *
 *   When we see a new day i with temperature T:
 *   → Pop all days j from the stack where temps[j] < T.
 *     For each popped j: day i is the "next warmer day" → answer[j] = i - j.
 *   → Push i onto the stack (still waiting for ITS next warmer day).
 *
 *   Why decreasing order? When something warmer arrives, it resolves ALL the
 *   cooler pending days at once. Each index is pushed once and popped at most
 *   once → O(n) total.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  ([73, 74, 75, 71, 69, 72, 76, 73])
 * ─────────────────────────────────────────────────────────────────────────────
 *   Stack holds INDICES; temps shown in [] for clarity. ans starts all 0.
 *
 *   i=0, T=73: stack empty → push 0.        stack=[0(73)]
 *   i=1, T=74: 74>73 → pop 0, ans[0]=1-0=1. stack=[1(74)]
 *   i=2, T=75: 75>74 → pop 1, ans[1]=2-1=1. stack=[2(75)]
 *   i=3, T=71: 71<75 → push 3.              stack=[2(75),3(71)]
 *   i=4, T=69: 69<71 → push 4.              stack=[2(75),3(71),4(69)]
 *   i=5, T=72: 72>69 → pop 4, ans[4]=5-4=1.
 *              72>71 → pop 3, ans[3]=5-3=2.
 *              72<75 → stop. push 5.         stack=[2(75),5(72)]
 *   i=6, T=76: 76>72 → pop 5, ans[5]=6-5=1.
 *              76>75 → pop 2, ans[2]=6-2=4.
 *              stack empty. push 6.          stack=[6(76)]
 *   i=7, T=73: 73<76 → push 7.              stack=[6(76),7(73)]
 *
 *   End: remaining stack indices {6,7} have no warmer day → ans stays 0.
 *   Result: [1,1,4,2,1,1,0,0] ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n) — each index pushed once, popped at most once
 *   SPACE: O(n) — stack holds up to n indices in the worst case
 *                 (e.g., strictly decreasing temperatures: nothing gets popped)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   All equal [70,70,70]:   nothing ever popped → all zeros.
 *   Strictly decreasing:    stack fills completely → all zeros.
 *   Strictly increasing:    each new day pops the previous → ans[i] = 1 for all except last.
 *   n == 1:                 trivially [0].
 *
 * INTERVIEW TIP:
 *   The pattern is called "Next Greater Element." Same structure applies to:
 *   - LC 496 Next Greater Element I
 *   - LC 84 Largest Rectangle in Histogram (uses monotonic INCREASING stack)
 *   - LC 42 Trapping Rain Water
 *   Know the monotonic stack template cold.

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Next Greater Element (monotonic stack) is used in event-driven and streaming systems:
 *   - Stock trading alerts: how many days until price exceeds today? Generates
 *     stop-loss and take-profit trigger signals.
 *   - Server monitoring: how long until CPU/memory usage drops below current level?
 *     Used in auto-scaling cooldown logic.
 *   - Compiler optimization: find the next instruction that invalidates a register
 *     value (live variable analysis uses a similar next-use computation).
 *   - Span computation in financial systems: the span of a stock price is
 *     computed using exactly this monotonic stack pattern.
 */

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

vector<int> dailyTemperatures(const vector<int>& temperatures) {
    const int n = static_cast<int>(temperatures.size());
    vector<int> ans(n, 0);
    stack<int> st;

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
            const int j = st.top();
            st.pop();
            ans[j] = i - j;
        }
        st.push(i);
    }
    return ans;
}

int main() {
    auto a = dailyTemperatures({73, 74, 75, 71, 69, 72, 76, 73});
    for (int x : a) {
        cout << x << ' ';
    }
    cout << '\n'; // 1 1 4 2 1 1 0 0
    return 0;
}

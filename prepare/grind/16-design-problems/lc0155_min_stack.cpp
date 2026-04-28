/**
 * LeetCode 155 — Min Stack
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Design a stack that supports push, pop, top, and getMin (retrieve minimum)
 *   all in O(1) time.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Store current minimum alongside each element
 * ─────────────────────────────────────────────────────────────────────────────
 *   NAIVE IDEA: Separate min_stack that tracks minimums.
 *   - On push(x): push x to main stack. If x <= min_stack.top(), push x to min_stack.
 *   - On pop(): if popped value == min_stack.top(), pop min_stack too.
 *
 *   SIMPLER: Store pairs (value, current_min) on a single stack.
 *   Every entry records the minimum valid AT THAT POINT in history.
 *   When you pop an element, the previous minimum is automatically restored.
 *
 *   TRACE:
 *   push(5): stack=[(5,5)]           min=5
 *   push(3): stack=[(5,5),(3,3)]     min=3
 *   push(7): stack=[(5,5),(3,3),(7,3)] min=3  ← 7 is pushed but min stays 3
 *   pop():   stack=[(5,5),(3,3)]     min=3  ← min correctly still 3
 *   pop():   stack=[(5,5)]           min=5  ← min restored to 5 automatically!
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   push/pop/top/getMin: O(1) — all operations constant time
 *   SPACE: O(n) — one extra int per element (pairs)
 *
 * CORNER CASES:
 *   Single element → min = that element
 *   Pop minimum → next min correctly restored
 *   Duplicate minimums → handled correctly (each entry stores its own min)

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Tracking auxiliary state (like minimum) alongside a stack appears in many contexts:
 *   - Undo/redo with metadata: each undo operation restores not just the value
 *     but also the state minimum (e.g., minimum zoom level used in the session).
 *   - Compiler expression evaluation: track the minimum register index in use
 *     during expression parsing to optimize register allocation.
 *   - Stock span / financial dashboards: maintain a running minimum price alongside
 *     the price history stack for O(1) lowest-since-purchase queries.
 *   - Game save states: stack of game states where each frame records the
 *     minimum health across all frames above it.
 */

#include <climits>
#include <iostream>
#include <stack>

using namespace std;

class MinStack {
    // Each entry: {value, minimum-at-this-point}
    stack<pair<int,int>> stk;
public:
    void push(int val) {
        int cur_min = stk.empty() ? val : min(val, stk.top().second);
        stk.push({val, cur_min});
    }

    void pop() {
        stk.pop();
    }

    int top() const {
        return stk.top().first;
    }

    int getMin() const {
        return stk.top().second;
    }
};

int main() {
    MinStack ms;
    ms.push(-2);
    ms.push(0);
    ms.push(-3);
    std::cout << ms.getMin() << '\n'; // -3
    ms.pop();
    std::cout << ms.top()    << '\n'; // 0
    std::cout << ms.getMin() << '\n'; // -2
    return 0;
}

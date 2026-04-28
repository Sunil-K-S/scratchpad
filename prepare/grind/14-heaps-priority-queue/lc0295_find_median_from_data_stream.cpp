/**
 * LeetCode 295 — Find Median from Data Stream
 * Difficulty: Hard
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Design a data structure that supports:
 *   - addNum(int num): add integer from stream
 *   - findMedian(): return median of all elements so far
 *
 *   Example: addNum(1), addNum(2), findMedian()→1.5, addNum(3), findMedian()→2
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Two heaps that split the data at the median
 * ─────────────────────────────────────────────────────────────────────────────
 *   Maintain two heaps:
 *   - lo: max-heap  → holds the lower half of numbers (top = largest of lower half)
 *   - hi: min-heap  → holds the upper half of numbers (top = smallest of upper half)
 *
 *   INVARIANTS:
 *   1. lo.size() == hi.size()  OR  lo.size() == hi.size() + 1
 *      (lo may have one extra = odd total)
 *   2. lo.top() <= hi.top()  (lower half ≤ upper half)
 *
 *   MEDIAN:
 *   - Even total: (lo.top() + hi.top()) / 2.0
 *   - Odd total:  lo.top()  (lo holds the middle)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (addNum: 1, 2, 3)
 * ─────────────────────────────────────────────────────────────────────────────
 *   Initial: lo=[], hi=[]
 *
 *   addNum(1):
 *     → push 1 to lo: lo=[1], hi=[]
 *     → lo.size() > hi.size()+1? No (1 == 0+1). OK.
 *     → lo.top()=1, hi empty. Invariant 2 trivially satisfied.
 *
 *   addNum(2):
 *     → push 2 to lo: lo=[2,1], hi=[]
 *     → lo.size() (2) > hi.size() (0) + 1? Yes
 *       → pop lo.top()=2, push to hi: lo=[1], hi=[2]
 *     → lo.top()=1 <= hi.top()=2 ✓. Sizes equal ✓.
 *     findMedian() → (1 + 2) / 2.0 = 1.5
 *
 *   addNum(3):
 *     → push 3 to lo: lo=[3,1], hi=[2]
 *     → lo.top()=3 > hi.top()=2 → VIOLATION of invariant 2
 *       → rebalance: pop 3 from lo, push to hi: lo=[1], hi=[2,3]
 *       → hi.size() > lo.size()? Yes → pop 2 from hi, push to lo: lo=[2,1], hi=[3]
 *     → lo.top()=2 <= hi.top()=3 ✓. lo.size()=2, hi.size()=1 → lo has 1 extra ✓
 *     findMedian() → lo.top() = 2
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   addNum:     O(log n) — heap push/pop
 *   findMedian: O(1)     — peek at heap tops
 *   SPACE:      O(n)     — store all elements
 *
 * CORNER CASES:
 *   Single element  → median = that element
 *   Two elements    → median = average
 *   All same value  → median = that value

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Streaming median (and percentile) computation is critical in observability:
 *   - SRE / monitoring: compute P50 (median), P95, P99 latency of API calls
 *     from a live request stream. Prometheus and Datadog use approximate versions
 *     (t-digest, HDR histogram) of this two-heap idea.
 *   - Financial market data: real-time median bid/ask spread across all
 *     active instruments without re-sorting on every tick.
 *   - A/B testing: compute rolling median session duration for each test variant
 *     as events arrive, to detect significance faster.
 *   - IoT sensor networks: compute median sensor reading in a stream to filter
 *     outliers before forwarding to a time-series database.
 */

#include <iostream>
#include <queue>

using namespace std;

class MedianFinder {
    priority_queue<int> lo;                           // max-heap: lower half
    priority_queue<int, vector<int>, greater<int>> hi; // min-heap: upper half
public:
    void addNum(int num) {
        // Always push to lo first
        lo.push(num);

        // Maintain invariant 2: lo.top() <= hi.top()
        if (!hi.empty() && lo.top() > hi.top()) {
            hi.push(lo.top()); lo.pop();
        }

        // Maintain invariant 1: lo can have at most 1 extra
        if (lo.size() > hi.size() + 1) {
            hi.push(lo.top()); lo.pop();
        } else if (hi.size() > lo.size()) {
            lo.push(hi.top()); hi.pop();
        }
    }

    double findMedian() const {
        if (lo.size() > hi.size()) return lo.top();
        return (lo.top() + hi.top()) / 2.0;
    }
};

int main() {
    MedianFinder mf;
    mf.addNum(1);
    mf.addNum(2);
    std::cout << mf.findMedian() << '\n'; // 1.5
    mf.addNum(3);
    std::cout << mf.findMedian() << '\n'; // 2
    return 0;
}

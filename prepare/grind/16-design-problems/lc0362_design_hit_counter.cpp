/**
 * LeetCode 362 — Design Hit Counter
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Design a hit counter that counts the number of hits in the past 5 minutes (300 seconds).
 *   - hit(timestamp): record a hit at given timestamp (in seconds, not-decreasing)
 *   - getHits(timestamp): return hits in [timestamp-299 .. timestamp]
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * TWO APPROACHES
 * ─────────────────────────────────────────────────────────────────────────────
 *
 * APPROACH 1: Deque — O(n) but handles large gaps
 * ─────────────────────────────────────────────────────────────────────────────
 *   Store (timestamp, count) pairs in a deque.
 *   On hit(t): evict front entries older than t-299; push or increment.
 *   On getHits(t): evict then sum all counts.
 *   Good for: sparse hits with large time gaps.
 *
 * APPROACH 2: Circular buffer — O(1) amortized
 * ─────────────────────────────────────────────────────────────────────────────
 *   Arrays of size 300: times[i] and hits[i] where i = timestamp % 300.
 *   If times[slot] == timestamp → increment hits[slot].
 *   Else (old data) → reset times[slot]=timestamp, hits[slot]=1.
 *   getHits: sum slots where times[slot] > timestamp-300.
 *
 *   WHY: Only 300 seconds window. New timestamp wraps into the same slot as
 *   a timestamp 300 seconds earlier — and we check times[slot] to distinguish.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE (circular buffer)
 * ─────────────────────────────────────────────────────────────────────────────
 *   hit(1):   slot=1%300=1,  times[1]=1,   hits[1]=1
 *   hit(1):   slot=1,        times[1]==1 → hits[1]=2
 *   hit(300): slot=300%300=0, times[0]=300, hits[0]=1
 *   getHits(300): sum slots where times[i] > 300-300=0
 *                 times[1]=1>0 ✓ (2 hits), times[0]=300>0 ✓ (1 hit) → total=3
 *   hit(301): slot=301%300=1, times[1]=1 ≠ 301 → reset: times[1]=301, hits[1]=1
 *   getHits(301): times[1]=301>1 ✓ (1), times[0]=300>1 ✓ (1) → total=2
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   hit:     O(1)
 *   getHits: O(300) = O(1) — fixed window size
 *   SPACE:   O(300) = O(1)

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Sliding window counters are the building block of rate limiting systems:
 *   - API rate limiting (Nginx, AWS API Gateway, Stripe): enforce max N requests
 *     per 5 minutes per user using a circular timestamp buffer.
 *   - DDoS mitigation: count incoming requests per IP in a sliding window and
 *     block IPs exceeding the threshold.
 *   - Analytics / metrics: Prometheus uses a circular time-series ring buffer
 *     to store the last N minutes of metric samples.
 *   - Ad frequency capping: ensure a user sees an ad at most k times in a
 *     rolling 24-hour window.
 */

#include <array>
#include <iostream>

using namespace std;

class HitCounter {
    static constexpr int WINDOW = 300;
    array<int,WINDOW> times{};
    array<int,WINDOW> hits{};
public:
    void hit(int timestamp) {
        int slot = timestamp % WINDOW;
        if (times[slot] == timestamp) {
            hits[slot]++;
        } else {
            times[slot] = timestamp;
            hits[slot] = 1;
        }
    }

    int getHits(int timestamp) const {
        int total = 0;
        for (int i = 0; i < WINDOW; ++i) {
            if (times[i] > timestamp - WINDOW) {
                total += hits[i];
            }
        }
        return total;
    }
};

int main() {
    HitCounter hc;
    hc.hit(1); hc.hit(1); hc.hit(300);
    std::cout << hc.getHits(300) << '\n'; // 3
    hc.hit(301);
    std::cout << hc.getHits(301) << '\n'; // 2 (hit at t=1 is now outside window)
    return 0;
}

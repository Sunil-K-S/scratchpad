/**
 * Topic: Common Big-O patterns (reference, not a LeetCode problem)
 *
 * Use this file while revising: read each block and say the complexity out loud.
 *
 * WORKED EXAMPLES (tie size n to “can I use O(n²)?” in interviews)
 *   n = 1e3   → n² = 1e6  steps (usually OK)
 *   n = 1e5   → n² = 1e10 (too slow; need ≈ O(n) or O(n log n))
 *   halving:   1e9 → 5e8 → … → 0 in ~30 iterations = O(log 1e9)

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Big-O reasoning is used everywhere in production systems:
 *   - Database query planners choose join algorithms (hash join O(n) vs
 *     nested-loop O(n^2)) based on table sizes.
 *   - API gateway rate limiters choose O(1) data structures (hash maps)
 *     over O(n) linear scans because they run on every request.
 *   - Google PageRank runs on billions of nodes — knowing O(V+E) BFS/DFS
 *     vs O(V^2) matters for whether a job finishes in hours or weeks.
 *   - Memory profiling: O(n) space vs O(1) space directly determines
 *     how many instances you need in a horizontally scaled service.
 */

#include <iostream>
#include <vector>

// Pattern A: single loop over n -> O(n)
void pattern_a(int n) {
    for (int i = 0; i < n; ++i) {
        (void)i;
    }
}

// Pattern B: nested loops i,j both 0..n-1 -> O(n^2)
void pattern_b(int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            (void)i;
            (void)j;
        }
}

// Pattern C: halving -> O(log n)
void pattern_c(long long n) {
    while (n > 0) {
        n /= 2;
    }
}

// Pattern D: outer for i, inner while j only advances (never resets)
// Each index visited O(1) times total -> O(n) amortized
// (two pointers on array, sliding window with expanding/shrinking bounds)
void pattern_d_sketch(int n) {
    int j = 0;
    for (int i = 0; i < n; ++i) {
        while (j < n && j <= i) { // placeholder guard: real problems add logic
            ++j;
        }
    }
}

int main() {
    std::cout << "Reference only — see header comments.\n";
    return 0;
}

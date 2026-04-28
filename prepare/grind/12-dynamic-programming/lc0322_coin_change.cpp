/**
 * LeetCode 322 — Coin Change
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Given coin denominations and an amount, return the minimum number of coins
 *   to make that amount. Return -1 if impossible.
 *
 *   Example: coins=[1,5,11], amount=15 → 3 coins (5+5+5, NOT 11+1+1+1+1=5)
 *   Greedy FAILS here: 11+1+1+1+1 = 5 coins, but 5+5+5 = 3 coins.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: 1D Bottom-up DP
 * ─────────────────────────────────────────────────────────────────────────────
 *   dp[i] = minimum coins needed to make amount i.
 *
 *   BASE CASE: dp[0] = 0 (0 coins needed for amount 0)
 *   TRANSITION: for each amount i from 1 to target:
 *     for each coin c in coins:
 *       if i >= c and dp[i-c] != INF:
 *         dp[i] = min(dp[i], dp[i-c] + 1)
 *
 *   INTUITION: To make amount i using coin c, we need 1 coin (c) + however
 *   many coins it takes to make (i-c). We try all coins and take the minimum.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (coins=[1,2,5], amount=11)
 * ─────────────────────────────────────────────────────────────────────────────
 *   dp = [0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF]
 *   idx=  0    1    2    3    4    5    6    7    8    9   10   11
 *
 *   i=1: coin=1: dp[0]+1=1 → dp[1]=1
 *   i=2: coin=1: dp[1]+1=2; coin=2: dp[0]+1=1 → dp[2]=1
 *   i=3: coin=1: dp[2]+1=2; coin=2: dp[1]+1=2 → dp[3]=2
 *   i=4: coin=1: 3; coin=2: dp[2]+1=2 → dp[4]=2
 *   i=5: coin=1: 3; coin=2: dp[3]+1=3; coin=5: dp[0]+1=1 → dp[5]=1
 *   ...
 *   i=11: coin=1: dp[10]+1; coin=2: dp[9]+1; coin=5: dp[6]+1=3 → dp[11]=3
 *   Answer: 3 (5+5+1) ✓
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(amount * len(coins))
 *   SPACE: O(amount)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   amount == 0          → 0
 *   No combination works → -1 (dp[amount] stays INF)
 *   Single coin == amount → 1

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Unbounded knapsack / minimum-coin decomposition appears in many allocation problems:
 *   - Payment systems / vending machines: compute the minimum number of coins/bills
 *     to make change — every POS terminal and ATM dispenser solves this.
 *   - Memory allocators: find the minimum number of fixed-size memory blocks
 *     (pages) to satisfy an allocation request.
 *   - Network packet fragmentation: split a large message into the fewest
 *     fixed-size MTU packets.
 *   - Currency exchange: decompose a transfer amount into the minimum number of
 *     round-lot currency denominations.
 */

#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int coinChange(const vector<int>& coins, int amount) {
    const int INF = amount + 1; // sentinel for "impossible" (> any real answer)
    vector<int> dp(amount + 1, INF);
    dp[0] = 0; // base case: 0 coins to make amount 0

    for (int i = 1; i <= amount; ++i) {
        for (int c : coins) {
            if (c <= i && dp[i - c] != INF) {
                dp[i] = min(dp[i], dp[i - c] + 1);
            }
        }
    }
    return dp[amount] == INF ? -1 : dp[amount];
}

int main() {
    std::cout << coinChange({1,2,5},  11) << '\n'; // 3
    std::cout << coinChange({2},       3) << '\n'; // -1
    std::cout << coinChange({1},       0) << '\n'; // 0
    std::cout << coinChange({1,5,11}, 15) << '\n'; // 3  (5+5+5)
    return 0;
}

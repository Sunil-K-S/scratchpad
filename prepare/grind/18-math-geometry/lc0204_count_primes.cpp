/**
 * LeetCode 204 — Count Primes
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Return the number of prime numbers strictly less than n.
 *
 *   Example: n=10 → 4  (primes: 2,3,5,7)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Sieve of Eratosthenes
 * ─────────────────────────────────────────────────────────────────────────────
 *   NAIVE: For each i, check divisibility up to sqrt(i) → O(n sqrt(n)).
 *
 *   SIEVE: Start with all numbers marked prime. For each prime p starting at 2,
 *   mark all multiples of p (p*p, p*(p+1), ...) as composite.
 *
 *   WHY start at p*p: Any composite m = p*k where k < p would have been marked
 *   already when we processed the prime factor of k. So p*2, p*3..p*(p-1) are
 *   already marked. We only need to start marking from p*p.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (n=10)
 * ─────────────────────────────────────────────────────────────────────────────
 *   is_prime: [_,_,T,T,T,T,T,T,T,T]  (indices 0..9)
 *
 *   p=2: mark 4,6,8 as false  → is_prime[4]=is_prime[6]=is_prime[8]=F
 *   p=3: mark 9 as false (3*3=9; 3*4=12 >= n) → is_prime[9]=F
 *   p=4: is_prime[4]=F, skip
 *   p=5..sqrt(10): p*p >= 10, loop ends
 *
 *   Count trues in [2..9]: 2,3,5,7 → 4
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(n log log n) — each number is marked at most O(log log n) times
 *   SPACE: O(n) — boolean sieve array
 *
 * CORNER CASES:
 *   n <= 2 → 0 (no primes less than 2)
 *   n = 3  → 1 (only prime: 2)

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Prime generation is at the foundation of modern cryptography:
 *   - RSA key generation: generating an RSA key pair requires two large primes;
 *     the sieve precomputes small prime candidates for trial division in
 *     primality testing.
 *   - Diffie-Hellman / elliptic curve: protocols require a large prime modulus;
 *     sieve-based prime tables accelerate the search.
 *   - Hash table sizing: hash tables are often sized to the next prime to reduce
 *     clustering — prime sieves precompute these sizes.
 *   - Pseudorandom number generators: linear congruential generators use a prime
 *     modulus to maximize the period.
 */

#include <iostream>
#include <vector>

using namespace std;

int countPrimes(int n) {
    if (n <= 2) return 0;

    vector<bool> is_prime(n, true);
    is_prime[0] = is_prime[1] = false;

    for (int p = 2; (long long)p * p < n; ++p) {
        if (!is_prime[p]) continue;
        // Mark multiples of p starting from p*p
        for (int multiple = p * p; multiple < n; multiple += p) {
            is_prime[multiple] = false;
        }
    }

    int count = 0;
    for (int i = 2; i < n; ++i) {
        if (is_prime[i]) count++;
    }
    return count;
}

int main() {
    std::cout << countPrimes(10)  << '\n'; // 4
    std::cout << countPrimes(0)   << '\n'; // 0
    std::cout << countPrimes(1)   << '\n'; // 0
    std::cout << countPrimes(100) << '\n'; // 25
    return 0;
}

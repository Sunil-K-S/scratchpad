/**
 * LeetCode 50 — Pow(x, n)
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Implement pow(x, n), which calculates x raised to the power n.
 *   n can be negative. x can be a double.
 *
 *   Example: pow(2.0, 10) → 1024.0
 *            pow(2.1, 3)  → 9.261
 *            pow(2.0, -2) → 0.25
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Fast Power (Exponentiation by Squaring)
 * ─────────────────────────────────────────────────────────────────────────────
 *   NAIVE: multiply x by itself n times → O(n). Too slow for large n.
 *
 *   FAST POWER:
 *   If n is even:  x^n = (x^(n/2))^2       → halve the problem
 *   If n is odd:   x^n = x * (x^(n/2))^2   → reduce to even subproblem
 *
 *   This halves n each step → O(log n) multiplications.
 *
 *   NEGATIVE n: x^(-n) = 1 / x^n.
 *   CAUTION: INT_MIN = -2147483648. Its absolute value overflows int.
 *   Use long long for n.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (pow(2, 10))
 * ─────────────────────────────────────────────────────────────────────────────
 *   pow(2, 10):  n=10 even → half = pow(2,5) → return half*half
 *   pow(2, 5):   n=5 odd  → half = pow(2,2) → return x * half*half
 *   pow(2, 2):   n=2 even → half = pow(2,1) → return half*half
 *   pow(2, 1):   n=1 odd  → half = pow(2,0) → return x * half*half = 2*1*1 = 2
 *   pow(2, 0):   base case → return 1
 *   Unwind: pow(2,1)=2, pow(2,2)=4, pow(2,5)=32, pow(2,10)=1024
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(log n) — n halved each recursive call
 *   SPACE: O(log n) — recursion stack depth
 *
 * CORNER CASES:
 *   n = 0   → 1.0 (anything to power 0)
 *   n < 0   → 1 / pow(x, -n)
 *   x = 0   → 0 (not tested here but n must be > 0)
 *   n = INT_MIN → overflow risk; use long long

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Fast exponentiation (O(log n) squaring) is critical in cryptography and numerics:
 *   - RSA encryption/decryption: computes m^e mod n and c^d mod n where e, d, n
 *     are hundreds of digits long — modular fast exponentiation is the only
 *     feasible approach (Python pow(m, e, n) uses this).
 *   - Diffie-Hellman key exchange: both parties compute g^a mod p — again
 *     fast modular exponentiation.
 *   - Matrix exponentiation: raise a matrix to the nth power in O(k^3 log n)
 *     to compute Fibonacci(n) or solve linear recurrences in O(log n).
 *   - Physics simulations: compute compound interest, exponential decay, or
 *     signal attenuation without O(n) repeated multiplication.
 */

#include <cstdlib>
#include <iostream>

using namespace std;

double myPow(double x, long long n) {
    if (n == 0) return 1.0;
    if (n < 0) {
        x = 1.0 / x;
        n = -n; // safe: n is long long, handles INT_MIN
    }
    double half = myPow(x, n / 2);
    if (n % 2 == 0) {
        return half * half;
    } else {
        return x * half * half;
    }
}

// Wrapper to accept int n (problem signature)
double powWrapper(double x, int n) {
    return myPow(x, static_cast<long long>(n));
}

int main() {
    std::cout << powWrapper(2.0, 10)   << '\n'; // 1024
    std::cout << powWrapper(2.1, 3)    << '\n'; // 9.261
    std::cout << powWrapper(2.0, -2)   << '\n'; // 0.25
    std::cout << powWrapper(1.0, -2147483648) << '\n'; // 1.0
    return 0;
}

/**
 * LeetCode 22 — Generate Parentheses
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Generate all combinations of n pairs of well-formed parentheses.
 *
 *   Example: n=3 → ["((()))","(()())","(())()","()(())","()()()"]
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Backtracking with constraints
 * ─────────────────────────────────────────────────────────────────────────────
 *   At each step, we can add '(' or ')'. But we apply rules to prune invalid states:
 *   - Add '(' if open < n     (we still have opening parens available)
 *   - Add ')' if close < open (we have more opens than closes = unclosed parens)
 *
 *   These two rules generate ONLY valid strings — no need to validate after.
 *   Base case: open == n && close == n → complete string, record it.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * DECISION TREE for n=2
 * ─────────────────────────────────────────────────────────────────────────────
 *   open=0,close=0: only '(' possible
 *   "("  open=1,close=0: '(' or ')'
 *   "(("  open=2,close=0: only ')'
 *   "(()"  open=2,close=1: only ')'
 *   "(())"  open=2,close=2 → RECORD "(())"
 *   "()"  open=1,close=1: only '('
 *   "()(": open=2,close=1: only ')'
 *   "()()": open=2,close=2 → RECORD "()()"
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(4^n / sqrt(n)) — the nth Catalan number, which counts valid strings
 *   SPACE: O(n) recursion depth
 *
 * CORNER CASES:
 *   n=0 → [""] or [] (edge case; usually n>=1 per constraints)
 *   n=1 → ["()"]

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Constraint-guided backtracking for structured string generation is used in:
 *   - Code formatters / pretty-printers: generate all valid indentation structures
 *     for a given nesting depth; pick the one matching style guide constraints.
 *   - Regular expression engines: generate strings matching a balanced-delimiter
 *     grammar for fuzzing and test-case synthesis.
 *   - Compiler front-ends: enumerate valid parse trees for ambiguous grammars
 *     during grammar validation.
 *   - UI component libraries: generate all valid combinations of nested layout
 *     containers (rows inside columns inside rows) for layout engine testing.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void backtrack(int n, int open, int close, string& current, vector<string>& result) {
    if (open == n && close == n) {
        result.push_back(current); // valid complete combination
        return;
    }
    if (open < n) {            // can still add an opening paren
        current.push_back('(');
        backtrack(n, open + 1, close, current, result);
        current.pop_back();    // backtrack
    }
    if (close < open) {        // can close an unclosed paren
        current.push_back(')');
        backtrack(n, open, close + 1, current, result);
        current.pop_back();    // backtrack
    }
}

vector<string> generateParenthesis(int n) {
    vector<string> result;
    string current;
    backtrack(n, 0, 0, current, result);
    return result;
}

int main() {
    for (const string& s : generateParenthesis(3))
        std::cout << s << '\n';
    // ((()))
    // (()())
    // (())()
    // ()(())
    // ()()()
    return 0;
}

/**
 * LeetCode 20 — Valid Parentheses
 * Difficulty: Easy
 *
 * PROBLEM:
 *   String s of '(', ')', '{', '}', '[', ']'. Determine if brackets are valid:
 *   correct nesting and every opener closed by matching closer in order.
 *
 * CONSTRAINTS:
 *   1 <= s.length <= 10^4
 *
 * LOGIC:
 *   Use a stack of expected closing characters (or opening chars, then match).
 *   On '(', push ')'; on '{', push '}'; on '[', push ']'.
 *   On closing c: stack must be non-empty and top == c, else invalid.
 *   End: stack empty.
 *
 * TIME:  O(n)
 * SPACE: O(n) stack worst case (((...
 *
 * CORNER CASES:
 *   - Extra closing first -> invalid immediately
 *   - Opener without closer at end -> stack non-empty
 *   - s length odd -> cannot be valid (quick check optional)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE  (s = "()[]{}")
 * ─────────────────────────────────────────────────────────────────────────────
 *   '('  → push ')'.  stack: )
 *   ')'  → top is ')', pop. stack: empty
 *   '['  → push ']'.  stack: ]
 *   ']'  → top is ']', pop. stack: empty
 *   '{'  → push '}'.  stack: }
 *   '}'  → top is '}', pop. stack: empty → valid ✓
 *
 *   Invalid: "(]" after '(' push ')', see ']' != ')' → false.

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Stack-based bracket matching is at the heart of every parser:
 *   - Compilers / interpreters: validate balanced braces, brackets, and parens
 *     in source code (every language parser does this as a first pass).
 *   - JSON / XML / HTML parsers: validate that tags and delimiters are properly
 *     nested — malformed input is rejected before deserialization.
 *   - Math expression evaluators: validate operator-operand structure before
 *     building an AST.
 *   - IDE syntax highlighting: highlight unmatched brackets in real time
 *     (VS Code, IntelliJ use this exact pattern).
 */

#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isValid(const string& s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(') {
            st.push(')');
        } else if (c == '{') {
            st.push('}');
        } else if (c == '[') {
            st.push(']');
        } else {
            if (st.empty() || st.top() != c) {
                return false;
            }
            st.pop();
        }
    }
    return st.empty();
}

int main() {
    cout << boolalpha;
    cout << isValid("()") << '\n';       // true
    cout << isValid("()[]{}") << '\n';  // true
    cout << isValid("(]") << '\n';       // false
    return 0;
}

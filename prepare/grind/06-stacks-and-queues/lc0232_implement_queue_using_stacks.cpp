/**
 * LeetCode 232 — Implement Queue using Stacks
 * Difficulty: Easy
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Implement a first-in-first-out (FIFO) queue using only two stacks.
 *   Supported operations: push(x), pop(), peek(), empty().
 *   Must achieve amortized O(1) per operation.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Two stacks = one queue (amortized O(1))
 * ─────────────────────────────────────────────────────────────────────────────
 *   Two stacks: `inbox` (for pushing) and `outbox` (for popping/peeking).
 *
 *   - push(x): always push to inbox. O(1).
 *   - pop()/peek(): if outbox is EMPTY, pour all of inbox into outbox (reversing order).
 *                   Then pop/peek from outbox. O(1) amortized.
 *
 *   WHY AMORTIZED O(1):
 *   Each element is moved from inbox to outbox at most ONCE across its lifetime.
 *   Total moves over n operations = O(n). Average per operation = O(1).
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * STEP-BY-STEP TRACE
 * ─────────────────────────────────────────────────────────────────────────────
 *   push(1): inbox=[1],   outbox=[]
 *   push(2): inbox=[1,2], outbox=[]
 *   push(3): inbox=[1,2,3], outbox=[]
 *
 *   peek(): outbox empty → pour inbox into outbox:
 *           inbox=[], outbox=[3,2,1]  (top of outbox = 1 = oldest)
 *           return outbox.top() = 1
 *
 *   pop():  outbox not empty → pop outbox.top()=1. outbox=[3,2]. return 1.
 *   pop():  outbox not empty → pop outbox.top()=2. outbox=[3].   return 2.
 *
 *   push(4): inbox=[4], outbox=[3]
 *   pop():   outbox not empty → pop outbox.top()=3. outbox=[]. return 3.
 *   pop():   outbox empty → pour inbox: outbox=[4]. pop 4. return 4.
 *
 *   Output order: 1,2,3,4 — correct FIFO!
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   push:  O(1)
 *   pop:   O(1) amortized  (O(n) worst case when outbox is empty and must pour)
 *   peek:  O(1) amortized
 *   empty: O(1)
 *   SPACE: O(n) — total elements stored across both stacks
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   pop()/peek() on empty → undefined (guaranteed valid by constraints)
 *   Alternating push/pop   → outbox gets refilled only when empty; works correctly
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Two-stack queue is a classic in concurrent and functional programming:
 *   - Functional persistent queues: in purely functional languages (Haskell,
 *     Clojure), two-stack queues enable amortized O(1) FIFO on immutable stacks.
 *   - Deferred processing pipelines: some lock-free queue implementations use
 *     two separate single-producer/consumer stacks (write stack + read stack)
 *     to reduce contention between producer and consumer threads.
 *   - Undo history with replay: maintain undo-stack and redo-stack; replaying
 *     from redo-stack (pour into undo-stack) mirrors this exact pattern.
 *   - CPU instruction pipelines: conceptually, a decode stage pours batches of
 *     decoded instructions into an execution queue — similar lazy-transfer idea.
 *
 * INTERVIEW TIP:
 *   The lazy-transfer trick (only pour when outbox is empty) is the insight that
 *   achieves amortized O(1). Without it, you'd pour on every pop → O(n) per pop.
 *   Always state "amortized O(1)" and briefly explain why during the interview.
 */

#include <iostream>
#include <stack>

using namespace std;

class MyQueue {
    stack<int> inbox;  // new elements go here
    stack<int> outbox; // elements leave from here

    void pour() {
        // Transfer all inbox elements to outbox (reverses order = correct FIFO)
        while (!inbox.empty()) {
            outbox.push(inbox.top());
            inbox.pop();
        }
    }
public:
    void push(int x) {
        inbox.push(x);
    }

    int pop() {
        if (outbox.empty()) pour();
        int val = outbox.top();
        outbox.pop();
        return val;
    }

    int peek() {
        if (outbox.empty()) pour();
        return outbox.top();
    }

    bool empty() const {
        return inbox.empty() && outbox.empty();
    }
};

int main() {
    MyQueue q;
    q.push(1);
    q.push(2);
    q.push(3);
    cout << q.peek()  << '\n'; // 1
    cout << q.pop()   << '\n'; // 1
    cout << q.pop()   << '\n'; // 2
    q.push(4);
    cout << q.pop()   << '\n'; // 3
    cout << q.pop()   << '\n'; // 4
    cout << q.empty() << '\n'; // 1 (true)
    return 0;
}

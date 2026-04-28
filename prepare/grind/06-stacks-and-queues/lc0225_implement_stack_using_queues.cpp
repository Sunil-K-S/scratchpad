/**
 * LeetCode 225 — Implement Stack using Queues
 * Difficulty: Easy
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Implement a last-in-first-out (LIFO) stack using only two queues.
 *   Supported operations: push(x), pop(), top(), empty().
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Rotate the queue after each push
 * ─────────────────────────────────────────────────────────────────────────────
 *   A queue is FIFO; a stack is LIFO. To simulate LIFO with a queue:
 *
 *   APPROACH (one queue, push is O(n)):
 *   - push(x): enqueue x, then rotate the entire queue so x moves to the FRONT.
 *     Rotation: dequeue each existing element and re-enqueue it (n-1 times).
 *   - pop()/top(): just dequeue from front — the most recently pushed element
 *     is always at the front.
 *
 *   WHY ROTATION WORKS:
 *   After push(1): q=[1]. Rotate 0 times. Front=1.
 *   After push(2): enqueue 2 → q=[1,2]. Rotate 1 time: move 1 to back → q=[2,1]. Front=2.
 *   After push(3): enqueue 3 → q=[2,1,3]. Rotate 2 times: move 2→back, move 1→back → q=[3,2,1]. Front=3.
 *   pop() → returns 3, q=[2,1]. Top=2. Correct LIFO order!
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   push:  O(n) — rotate n-1 elements
 *   pop:   O(1)
 *   top:   O(1)
 *   empty: O(1)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   pop()/top() on empty → undefined (guaranteed valid by problem constraints)
 *   Single element       → push then pop works correctly
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Implementing one ADT using a different ADT is a common adapter/wrapper pattern:
 *   - Messaging systems: simulate a LIFO work queue (last job first = prioritize
 *     most recent) on top of a FIFO message queue (SQS, RabbitMQ) by re-queuing
 *     older messages — used in undo-operation queues.
 *   - Operating systems: some OS task schedulers implement LIFO priority on a
 *     FIFO hardware queue to reduce cache pressure (LIFO scheduling improves
 *     locality for recently-run threads).
 *   - Design patterns: the Adapter pattern — wrapping a queue interface to provide
 *     stack semantics without changing the underlying queue implementation.
 *
 * INTERVIEW TIP:
 *   The companion problem LC 232 (Queue using Stacks) is more common in interviews.
 *   Know both. State the trade-off: you can make either push or pop O(1), but not both.
 *   Choosing push-heavy O(n) makes pop O(1); choosing pop-heavy makes push O(1) but pop O(n).
 */

#include <iostream>
#include <queue>

using namespace std;

class MyStack {
    queue<int> q;
public:
    void push(int x) {
        q.push(x);
        // Rotate: move all elements that were already in the queue to the back
        // so the newly pushed x ends up at the front
        int sz = static_cast<int>(q.size()) - 1;
        while (sz-- > 0) {
            q.push(q.front());
            q.pop();
        }
    }

    int pop() {
        int val = q.front();
        q.pop();
        return val;
    }

    int top() const {
        return q.front();
    }

    bool empty() const {
        return q.empty();
    }
};

int main() {
    MyStack s;
    s.push(1);
    s.push(2);
    s.push(3);
    cout << s.top()  << '\n'; // 3
    cout << s.pop()  << '\n'; // 3
    cout << s.top()  << '\n'; // 2
    cout << s.empty() << '\n'; // 0 (false)
    s.pop(); s.pop();
    cout << s.empty() << '\n'; // 1 (true)
    return 0;
}

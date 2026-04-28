/**
 * LeetCode 721 — Accounts Merge
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Each account is [name, email1, email2, ...]. Two accounts belong to the same
 *   person if they share at least one email. Merge all accounts of the same person.
 *   Return merged accounts with emails sorted, first element is the name.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Union-Find on emails
 * ─────────────────────────────────────────────────────────────────────────────
 *   Emails are nodes. Two emails in the same account → same component → union them.
 *   After processing all accounts, group emails by their component root.
 *   Each component = one merged account.
 *
 *   ALTERNATIVE: BFS/DFS on a graph where edges connect emails in the same account.
 *   Union-Find is cleaner and O(α) per operation.
 *
 *   ALGORITHM:
 *   1. For each account, union all its emails with the first email as representative.
 *      Also map each email → owner name.
 *   2. After all unions, group emails by their find(root).
 *   3. Sort each group, prepend name.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * UNION-FIND REFRESHER
 * ─────────────────────────────────────────────────────────────────────────────
 *   parent[x]: representative of x's component.
 *   find(x): follow parent pointers to root. Path compression flattens tree.
 *   union(x,y): merge components by rank (attach smaller tree under larger).
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  O(N * K * α(N*K) + N*K log(K)) where N=accounts, K=avg emails
 *          α is inverse Ackermann ≈ constant. Sort per group dominates.
 *   SPACE: O(N * K) — for parent map and output

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Union-Find for grouping entities sharing identifiers is core to identity systems:
 *   - Identity resolution / entity deduplication: merge customer records that share
 *     an email or phone number (CRM deduplication, fraud detection).
 *   - Social graph: determine connected components of users who share mutual
 *     connections or linked accounts.
 *   - Distributed systems: cluster partitioning — group nodes that can reach
 *     each other to detect split-brain scenarios.
 *   - Compiler symbol tables: merge scopes that reference the same underlying
 *     variable (alias analysis).
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// ── Union-Find ────────────────────────────────────────────────────────────────
unordered_map<string, string> parent;
unordered_map<string, int> rank_;

string find(const string& x) {
    if (parent[x] != x) parent[x] = find(parent[x]); // path compression
    return parent[x];
}

void unite(const string& x, const string& y) {
    string px = find(x), py = find(y);
    if (px == py) return;
    if (rank_[px] < rank_[py]) swap(px, py);
    parent[py] = px;                        // attach smaller under larger
    if (rank_[px] == rank_[py]) rank_[px]++;
}

vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    unordered_map<string, string> email_to_name;

    // Initialize each email as its own component, record owner name
    for (const auto& acc : accounts) {
        for (int i = 1; i < static_cast<int>(acc.size()); ++i) {
            if (parent.find(acc[i]) == parent.end()) {
                parent[acc[i]] = acc[i];
                rank_[acc[i]]  = 0;
            }
            email_to_name[acc[i]] = acc[0];
        }
    }

    // Union all emails within the same account
    for (const auto& acc : accounts) {
        for (int i = 2; i < static_cast<int>(acc.size()); ++i) {
            unite(acc[1], acc[i]); // union with first email of this account
        }
    }

    // Group emails by their root representative
    unordered_map<string, vector<string>> groups;
    for (const auto& [email, _] : email_to_name) {
        groups[find(email)].push_back(email);
    }

    // Build output: [name, sorted_emails...]
    vector<vector<string>> result;
    for (auto& [root, emails] : groups) {
        sort(emails.begin(), emails.end());
        emails.insert(emails.begin(), email_to_name[root]); // prepend name
        result.push_back(std::move(emails));
    }
    return result;
}

int main() {
    vector<vector<string>> accounts = {
        {"John","johnsmith@mail.com","john_newyork@mail.com"},
        {"John","johnsmith@mail.com","john00@mail.com"},
        {"Mary","mary@mail.com"},
        {"John","johnnybravo@mail.com"}
    };
    auto res = accountsMerge(accounts);
    for (auto& acc : res) {
        for (int i = 0; i < static_cast<int>(acc.size()); ++i)
            std::cout << (i ? "," : "") << acc[i];
        std::cout << '\n';
    }
    return 0;
}

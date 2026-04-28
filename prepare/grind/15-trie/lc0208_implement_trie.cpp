/**
 * LeetCode 208 — Implement Trie (Prefix Tree)
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Implement a trie (prefix tree) with:
 *   - insert(word): insert word into trie
 *   - search(word): return true if word is in trie
 *   - startsWith(prefix): return true if any word has given prefix
 *
 *   Example: insert("apple") → search("apple")=true, search("app")=false,
 *            startsWith("app")=true
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: Tree where each edge represents one character
 * ─────────────────────────────────────────────────────────────────────────────
 *   Each TrieNode has 26 children (one per lowercase letter) and an `is_end` flag.
 *   Characters are stored implicitly as the INDEX into the children array.
 *
 *   INSERT "apple": root→a→p→p→l→e.is_end=true
 *   SEARCH "apple": traverse root→a→p→p→l→e, return e.is_end
 *   SEARCH "app":   traverse root→a→p→p, return p.is_end (false, no word ends here)
 *   STARTS "app":   traverse root→a→p→p, return true (node exists)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   insert/search/startsWith: O(L) — L = word/prefix length
 *   SPACE: O(ALPHABET * total_chars) = O(26 * sum of all word lengths)
 *
 * CORNER CASES:
 *   Searching prefix of inserted word ("app" when "apple" inserted) → false for search, true for startsWith
 *   Searching full word that is prefix of another → only true if it was inserted
 *   Empty string insert/search → is_end on root node

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Tries are the standard data structure for prefix-based retrieval:
 *   - Search autocomplete (Google search bar, IDE IntelliSense): find all words
 *     matching a typed prefix in O(prefix_length) time.
 *   - IP routing (longest prefix match): routers store IP prefixes in a trie
 *     and traverse it to find the longest matching route for a packet.
 *   - Spell checker suggestions: trie traversal with error tolerance finds all
 *     dictionary words within edit distance 1 of the typed word.
 *   - DNS lookup: DNS resolvers cache domain names in trie-like structures to
 *     enable efficient subdomain matching.
 */

#include <array>
#include <iostream>
#include <string>

using namespace std;

struct TrieNode {
    array<TrieNode*, 26> children{};  // null = no child for that letter
    bool is_end = false;
};

class Trie {
    TrieNode* root;
public:
    Trie() : root(new TrieNode()) {}

    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) {
                node->children[idx] = new TrieNode();
            }
            node = node->children[idx];
        }
        node->is_end = true; // mark end of word
    }

    bool search(const string& word) const {
        const TrieNode* node = findNode(word);
        return node && node->is_end; // node must exist AND mark a word end
    }

    bool startsWith(const string& prefix) const {
        return findNode(prefix) != nullptr; // any node existing means prefix exists
    }

private:
    const TrieNode* findNode(const string& s) const {
        const TrieNode* node = root;
        for (char c : s) {
            int idx = c - 'a';
            if (!node->children[idx]) return nullptr; // prefix not in trie
            node = node->children[idx];
        }
        return node;
    }
};

int main() {
    Trie trie;
    trie.insert("apple");
    std::cout << std::boolalpha;
    std::cout << trie.search("apple")    << '\n'; // true
    std::cout << trie.search("app")      << '\n'; // false
    std::cout << trie.startsWith("app")  << '\n'; // true
    trie.insert("app");
    std::cout << trie.search("app")      << '\n'; // true
    return 0;
}

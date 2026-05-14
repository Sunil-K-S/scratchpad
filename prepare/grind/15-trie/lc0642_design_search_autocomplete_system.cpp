/**
 * LeetCode 642 — Design Search Autocomplete System
 * Difficulty: Hard
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Design a search autocomplete system initialized with historical sentences
 *   and their usage counts.
 *
 *   AutocompleteSystem(sentences, times): Initialize. sentences[i] was searched
 *   times[i] times historically.
 *
 *   input(c): User types one character c.
 *   - If c == '#': the current typed sentence is finished. Save it (increment
 *     its count by 1) and return []. Reset current input to "".
 *   - Otherwise: append c to current prefix. Return the top 3 sentences in the
 *     system whose prefix matches current input, sorted by:
 *       1. Hot (count) descending
 *       2. Lexicographic ascending (tie-break)
 *
 *   Example:
 *     init(["i love you","island","iroman","i love leetcode"],[5,3,2,2])
 *     input('i')  → ["i love you","island","i love leetcode"]
 *     input(' ')  → ["i love you","i love leetcode"]
 *     input('a')  → []
 *     input('#')  → []   (saves "i a", count=1)
 *
 *   WORKED EXAMPLE — why input(' ') after "i" filters sentences:
 *   Prefix "i " matches only sentences starting with those two chars ("i love you",
 *   "i love leetcode"); "island" is dropped because second char is 's', not space.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * KEY INSIGHT: HashMap for O(1) updates + scan on each input character
 * ─────────────────────────────────────────────────────────────────────────────
 *   Two approaches:
 *
 *   APPROACH 1 (implemented here): HashMap + linear scan — O(n*L) per input
 *   - Store all sentences in map<string, int> sentence→count.
 *   - On each character, iterate all sentences and filter those with matching
 *     prefix, partial-sort to get top 3.
 *   - Simple to implement; acceptable when n is small or amortized for interviews.
 *
 *   APPROACH 2 (mentioned): Trie with sorted candidate lists at each node
 *   - Each trie node stores a sorted list of (count, sentence) for all sentences
 *     under that prefix.
 *   - input() is O(1) per character once trie is built.
 *   - But insert/update is expensive if you maintain sorted lists; complex to code.
 *   - The HashMap approach is preferred in interviews for clarity.
 *
 *   After '#': save current_input into the map (or increment if exists), reset.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────────────────────
 *   TIME:  init O(k) where k=number of sentences
 *          input O(n*L) per call: n sentences, L=avg length for prefix check
 *   SPACE: O(total chars across all sentences)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * CORNER CASES
 * ─────────────────────────────────────────────────────────────────────────────
 *   '#' immediately (empty sentence) → save "" (rare, but handle gracefully)
 *   Fewer than 3 matches → return all that match
 *   Same sentence typed multiple times → count accumulates correctly
 *   Sentence typed that was never in history → added with count 1 on '#'
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Autocomplete with frequency ranking is ubiquitous in production systems:
 *   - Search engines: Google's search bar returns suggestions ranked by query
 *     frequency. The underlying system uses Tries (or inverted indexes) with
 *     hit-count metadata per prefix node.
 *   - IDE IntelliSense / code completion: VS Code, IntelliJ rank completions by
 *     how often a symbol has been used, blending frequency with edit-distance.
 *   - Mobile keyboard: SwiftKey, Gboard predict next word using n-gram frequency
 *     tables (a generalization of this per-prefix frequency model).
 *   - E-commerce search: Amazon/Google Shopping autocomplete products by query
 *     frequency + click-through rate — same principle of hotness-sorted prefix match.
 *
 * INTERVIEW TIP:
 *   Start with the HashMap + linear-scan approach (simple, correct). Then discuss
 *   Trie as the optimization, explaining the trade-off: Trie gives faster lookup
 *   but more complex insert/update. Interviewers want to see you know both and
 *   can reason about the trade-offs. Mention that in production, a sorted Trie
 *   or inverted index with top-k maintained per node is the standard approach.
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class AutocompleteSystem {
    unordered_map<string,int> freq;
    string current; // characters typed so far (not yet confirmed with '#')

public:
    AutocompleteSystem(const vector<string>& sentences, const vector<int>& times) {
        for (int i = 0; i < static_cast<int>(sentences.size()); ++i) {
            freq[sentences[i]] += times[i];
        }
    }

    vector<string> input(char c) {
        if (c == '#') {
            freq[current]++; // save or increment the completed sentence
            current.clear();
            return {};
        }

        current += c;

        // Collect all sentences that start with `current`
        vector<pair<int,string>> candidates; // (-count, sentence) for sorting
        for (const auto& [sentence, count] : freq) {
            if (sentence.size() >= current.size() &&
                sentence.substr(0, current.size()) == current) {
                candidates.push_back({-count, sentence}); // negative for desc sort
            }
        }

        // Sort: ascending on -count (= descending count), then lexicographic
        sort(candidates.begin(), candidates.end());

        // Return top 3
        vector<string> result;
        for (int i = 0; i < static_cast<int>(candidates.size()) && i < 3; ++i) {
            result.push_back(candidates[i].second);
        }
        return result;
    }
};

int main() {
    AutocompleteSystem sys(
        {"i love you", "island", "iroman", "i love leetcode"},
        {5, 3, 2, 2}
    );

    auto r1 = sys.input('i');
    for (auto& s : r1) cout << '"' << s << "\" "; cout << '\n';
    // "i love you" "island" "i love leetcode"

    auto r2 = sys.input(' ');
    for (auto& s : r2) cout << '"' << s << "\" "; cout << '\n';
    // "i love you" "i love leetcode"

    auto r3 = sys.input('a');
    for (auto& s : r3) cout << '"' << s << "\" "; cout << '\n';
    // (empty)

    auto r4 = sys.input('#');
    for (auto& s : r4) cout << '"' << s << "\" "; cout << '\n';
    // (empty) — "i a" saved with count 1

    // Now typing "i a" again should surface it
    sys.input('i');
    auto r5 = sys.input(' ');
    for (auto& s : r5) cout << '"' << s << "\" "; cout << '\n';
    // "i love you" "i love leetcode" "i a"  (i a has count 1, lowest)
    return 0;
}

/**
 * LeetCode 912 — Sort an Array
 * Difficulty: Medium
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * PROBLEM
 * ─────────────────────────────────────────────────────────────────────────────
 *   Sort an integer array in ascending order without using built-in sort.
 *   This is a practice problem to implement and explain sorting algorithms.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * ALGORITHMS IMPLEMENTED (know all three for Google)
 * ─────────────────────────────────────────────────────────────────────────────
 *
 * ── MERGE SORT ───────────────────────────────────────────────────────────────
 *   Divide: split array in half recursively until size 1.
 *   Conquer: merge two sorted halves.
 *   Stable sort. Guaranteed O(n log n). Uses O(n) extra space.
 *   WHEN TO USE: When you need stable sort, or sorting linked lists (no random access).
 *
 *   MERGE step trace ([1,3] and [2,4]):
 *   Compare 1 vs 2 → take 1. Compare 3 vs 2 → take 2. Compare 3 vs 4 → take 3. Take 4.
 *   Result: [1,2,3,4]
 *
 * ── QUICK SORT ───────────────────────────────────────────────────────────────
 *   Pick a pivot, partition array so all < pivot are left, all > pivot are right.
 *   Recursively sort left and right partitions.
 *   Average O(n log n), worst case O(n^2) on sorted input (use random pivot to avoid).
 *   In-place (O(log n) stack space average). FASTER in practice than merge sort.
 *   WHEN TO USE: General purpose, in-place, cache-friendly.
 *
 * ── HEAP SORT ────────────────────────────────────────────────────────────────
 *   Build a max-heap in O(n). Repeatedly extract max and place at end.
 *   Guaranteed O(n log n), O(1) space. Not cache-friendly, not stable.
 *   WHEN TO USE: When guaranteed O(n log n) and O(1) space both required.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * COMPLEXITY COMPARISON
 * ─────────────────────────────────────────────────────────────────────────────
 *   Algorithm   Time (avg)   Time (worst)  Space   Stable?
 *   Merge Sort  O(n log n)   O(n log n)    O(n)    Yes
 *   Quick Sort  O(n log n)   O(n^2)*       O(log n) No
 *   Heap Sort   O(n log n)   O(n log n)    O(1)    No
 *   (*worst case avoided with random pivot)
 *
 * CORNER CASES:
 *   Empty array, single element, all duplicates, already sorted (quicksort worst case).

 * ─────────────────────────────────────────────────────────────────────────────
 * REAL-WORLD APPLICATIONS
 * ─────────────────────────────────────────────────────────────────────────────
 *   Understanding sort algorithm trade-offs informs infrastructure decisions:
 *   - Database query engines choose between quicksort (in-memory, cache-friendly),
 *     merge sort (external/stable, used for ORDER BY with disk I/O), and
 *     heapsort (guaranteed O(n log n) worst case for adversarial input).
 *   - C++ std::sort uses introsort (quicksort + heapsort fallback + insertion sort
 *     for small n) for exactly these performance trade-off reasons.
 *   - Distributed sorting (MapReduce, Spark): the shuffle phase is essentially a
 *     distributed merge sort of key-value pairs across machines.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// ── MERGE SORT ───────────────────────────────────────────────────────────────
void mergeHelper(vector<int>& nums, int lo, int mid, int hi) {
    vector<int> temp(nums.begin() + lo, nums.begin() + hi + 1);
    int left  = 0;
    int right = mid - lo + 1;
    int end   = hi - lo;
    int k = lo;
    while (left <= mid - lo && right <= end) {
        if (temp[left] <= temp[right]) nums[k++] = temp[left++];
        else                           nums[k++] = temp[right++];
    }
    while (left  <= mid - lo) nums[k++] = temp[left++];
    while (right <= end)      nums[k++] = temp[right++];
}

void mergeSort(vector<int>& nums, int lo, int hi) {
    if (lo >= hi) return; // base case: 0 or 1 element
    int mid = lo + (hi - lo) / 2;
    mergeSort(nums, lo, mid);
    mergeSort(nums, mid + 1, hi);
    mergeHelper(nums, lo, mid, hi);
}

// ── QUICK SORT (with random pivot to avoid O(n^2) on sorted input) ───────────
int partition(vector<int>& nums, int lo, int hi) {
    // Random pivot: swap random element with hi to use as pivot
    int pivotIdx = lo + rand() % (hi - lo + 1);
    swap(nums[pivotIdx], nums[hi]);
    int pivot = nums[hi];
    int i = lo - 1; // index of last element <= pivot
    for (int j = lo; j < hi; ++j) {
        if (nums[j] <= pivot) {
            ++i;
            swap(nums[i], nums[j]);
        }
    }
    swap(nums[i + 1], nums[hi]); // place pivot in correct position
    return i + 1;
}

void quickSort(vector<int>& nums, int lo, int hi) {
    if (lo >= hi) return;
    int pi = partition(nums, lo, hi);
    quickSort(nums, lo, pi - 1);
    quickSort(nums, pi + 1, hi);
}

// ── PUBLIC INTERFACE (uses merge sort — guaranteed O(n log n)) ────────────────
vector<int> sortArray(vector<int>& nums) {
    mergeSort(nums, 0, static_cast<int>(nums.size()) - 1);
    return nums;
}

int main() {
    vector<int> v1 = {5, 2, 3, 1};
    sortArray(v1);
    for (int x : v1) std::cout << x << ' '; // 1 2 3 5
    std::cout << '\n';

    vector<int> v2 = {5, 1, 1, 2, 0, 0};
    sortArray(v2);
    for (int x : v2) std::cout << x << ' '; // 0 0 1 1 2 5
    std::cout << '\n';
    return 0;
}

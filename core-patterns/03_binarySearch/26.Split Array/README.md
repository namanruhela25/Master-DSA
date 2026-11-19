# Split Array Largest Sum

## Problem Link
🔗 [LeetCode 410 — Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/)

---

## What is this Problem?

Split `nums` into **`k` non-empty contiguous subarrays** so that the **largest subarray sum** is as small as possible. Return that minimum possible largest sum.

```
nums=[7,2,5,10,8], k=2  → Output: 18
nums=[1,2,3,4,5],   k=2  → Output: 9
nums=[1,4,4],       k=3  → Output: 4
```

For `[7,2,5,10,8]` with 2 parts, `{7,2,5,10}` + `{8}` gives 24, `{7,2,5}` + `{10,8}` gives 18, `{7,2}` + `{5,10,8}` gives 23 — best is **18**.

This is exactly the **Book Allocation** problem with different nouns: students → subarrays, pages → values.

---

## The Idea

```
Binary search on the ANSWER (the largest allowed sum), not on the array.

"parts(limit)": minimum number of contiguous parts needed so that no part
sums above `limit`. Greedily keep extending the current part until adding the
next element would break the limit.

  limit small → many parts    (below max(nums): impossible)
  limit large → 1 part

"parts(limit) <= k" is monotone: false below the answer, true from the answer
onward → find the FIRST feasible limit.

Range:
  low  = max(nums)   ← a single element can never be split
  high = Σ nums      ← whole array as one part

  limit : 10 ... 17  [18] 19 ... 32
  parts :   3    3     2    2       1     k = 2 → first feasible = 18 ✓
```

Why the greedy is optimal: for a fixed limit, taking as many elements as possible into the current part never uses more parts than any other split. If the greedy needs more than `k` parts, every split does.

---

## Code Full Solution

```cpp
class Solution {
public:
    int solve(vector<int> &nums, int mid, int n) {
        int sm = 0;
        int partition = 1;          // first part always exists

        for(int i = 0; i < n; i++) {
            if(sm + nums[i] <= mid) {
                sm += nums[i];      // extend the current part
            } else {
                sm = nums[i];       // start a new part with nums[i]
                partition++;
            }
        }
        return partition;
    }

    int splitArray(vector<int>& nums, int k) {
        int n = nums.size();
        int low  = *max_element(nums.begin(), nums.end());   // biggest element
        int high = accumulate(nums.begin(), nums.end(), 0);  // whole array

        while(low <= high) {
            int mid = low + (high - low) / 2;
            int noofpartition = solve(nums, mid, n);

            if(noofpartition <= k) {
                high = mid - 1;     // allowed a bigger sum — try smaller
            } else {
                low = mid + 1;      // too many parts — raise the limit
            }
        }
        return low;
    }
};
```

---

## Code Explanation

### `low = max(nums)` — The Hard Lower Bound

A single element cannot be split, so any limit below the largest element is impossible. Starting at `max` skips a region where the predicate is always false.

### `high = Σ nums` — The Trivial Upper Bound

With a limit equal to the total, everything fits in one part, which is always `<= k`. No larger limit can improve the answer.

### The Greedy Partition Count

```cpp
if(sm + nums[i] <= mid) sm += nums[i];
else { sm = nums[i]; partition++; }
```

Because parts must be **contiguous**, the only decision at each element is "keep it in the current part, or start a new one". Starting a new part earlier can never reduce the total part count, so the greedy is optimal.

### `partition = 1`, Not `0`

The first part exists before any element is read. With `0` the count would be one too low and the predicate would accept limits that actually need one extra part.

### `<= k`, Not `== k`

Fewer parts than `k` is allowed because the limit only bounds the **maximum** sum — you can always split a part further to reach exactly `k` parts (as long as `k <= n`), and extra splits only lower sums.

### The `n` Parameter Adds Nothing

`solve` receives both `nums` and `n`, but `nums.size()` would do. Harmless, just redundant.

### Returning `low`

```cpp
if(noofpartition <= k) high = mid - 1;
else                   low  = mid + 1;
return low;
```

"First true" search. After the loop, `low = high + 1` holds the smallest feasible limit, which is the answer.

---

## Full Trace: `nums=[7,2,5,10,8]`, `k=2`

```
low = 10, high = 32

mid=21: 7+2+5=14, +10=24 > 21 → {10,8}=18 → 2 parts ≤ 2 → high=20

low=10, high=20
mid=15: 7+2+5=14, +10=24 > 15 → {10}, +8=18 > 15 → {8} → 3 parts > 2 → low=16

low=16, high=20
mid=18: 7+2+5=14, +10=24 > 18 → {10,8}=18 → 2 parts ≤ 2 → high=17

low=16, high=17
mid=16: 7+2+5=14, +10=24 > 16 → {10}, +8 > 16 → {8} → 3 parts > 2 → low=17

low=17, high=17
mid=17: same walk → 3 parts > 2 → low=18

low=18 > high=17 → return 18 ✓
```

## Full Trace: `nums=[1,2,3,4,5]`, `k=2`

```
low = 5, high = 15

mid=10: {1,2,3,4}=10, +5=15 > 10 → {5} → 2 ≤ 2 → high=9
mid=7:  {1,2,3}=6, +4=10 > 7 → {4}, +5=9 > 7 → {5} → 3 > 2 → low=8
mid=8:  {1,2,3}=6, +4=10 > 8 → {4}, +5=9 > 8 → {5} → 3 > 2 → low=9
mid=9:  {1,2,3}=6, +4=10 > 9 → {4,5}=9 → 2 ≤ 2 → high=8

low=9 > high=8 → return 9 ✓   ({1,2,3} + {4,5})
```

---

## Example Traces

### `k = 1` — The Whole Array

```
nums=[7,2,5,10,8], k=1 → 32
low=10, high=32
Every mid < 32 yields ≥ 2 parts, so low climbs to 32 → return 32 ✓
```

### `k = n` — One Element Per Part

```
nums=[1,4,4], k=3 → 4 = max(nums)
low=4, high=9
mid=6: {1,4}=5, +4=9 > 6 → {4} → 2 ≤ 3 → high=5
mid=4: {1}, {4}, {4} → 3 ≤ 3 → high=3
return low=4 ✓   (a part cannot be smaller than its biggest element)
```

### Everything Is a Zero Except One

```
nums=[0,0,9,0], k=2 → 9
low=9, high=9 → mid=9: {0,0,9}=9, +0=9 → 1 part ≤ 2 → high=8 → return 9 ✓
Zeros never force a split, and `<= k` accepts using fewer parts than allowed.
```

---

## Edge Cases

### `k` Larger Than `n`

LeetCode guarantees `1 <= k <= min(50, n)`. If `k > n`, exactly `k` non-empty parts cannot exist; this code would still return `max(nums)` (the predicate `parts <= k` passes immediately), which is a reasonable answer for "at most `k` parts".

### Negative Values

Not supported by the range logic. `low = max(nums)` and `high = Σ nums` both assume non-negative numbers; LeetCode constraints use `0 <= nums[i] <= 10^4`.

### Overflow

`accumulate(nums.begin(), nums.end(), 0)` sums in `int`. LeetCode caps the total at `10^9`, which fits, but `0LL` is the safe habit for larger constraints.

### Single Element

```
nums=[5], k=1 → low=high=5 → returns 5 ✓
```

### `n == 0`

`*max_element` on an empty vector is undefined behaviour. LeetCode guarantees `n >= 1`.

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(n · log(Σnums − max(nums))) |
| Space | O(1) |

```
Σ ≤ 10^9 → log2 ≈ 30 greedy passes over n ≤ 1000 elements.
Trying every possible limit would be O(n · Σ) → 10^12 → too slow.
```

---

## Key Insight

```
When the answer is a maximum over contiguous pieces and the pieces are
constrained only by COUNT, binary search the bound and count greedily.

The recipe repeats across this whole section:
  1. pick the quantity to minimise (here: max part sum)
  2. find a cheap predicate on a candidate value
  3. prove it is monotone
  4. binary search for the first true
```

---

## References

- 🔗 [LeetCode 410 — Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/)
- 🔗 [GFG — Allocate Minimum Number of Pages](https://www.geeksforgeeks.org/problems/allocate-minimum-number-of-pages0937/1) (identical structure)
- 🔗 [LeetCode 1011 — Capacity To Ship Packages Within D Days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/) (same pattern)

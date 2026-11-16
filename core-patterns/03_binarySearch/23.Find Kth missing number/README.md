# Kth Missing Positive Number

## Problem Link
🔗 [LeetCode 1539 — Kth Missing Positive Number](https://leetcode.com/problems/kth-missing-positive-number/)

---

## What is this Problem?

Given a **strictly increasing** array of positive integers and an integer `k`, return the **k-th positive integer that is missing** from the array.

```
nums=[2,3,4,7,11], k=5   → Output: 9
     1  [2 3 4]  5 6 [7]  8 9 10 [11]
     missing: 1,5,6,8,9,10,...   → 5th missing is 9

nums=[1,2,3,4], k=2 → Output: 6
nums=[1,2], k=1     → Output: 3
```

A linear scan works but is O(n). Binary search gets **O(log n)** by asking, at each index, how many numbers are missing *before* it.

---

## The Idea

```
Positive integers count 1, 2, 3, ... — so at index i the value "should" be i+1
if the array were the perfect prefix 1,2,3,...

    missingBeforeOrAt(i) = nums[i] - (i + 1)

    nums = [2, 3, 4, 7, 11]
    i    :  0  1  2  3   4
    nums[i]: 2  3  4  7  11
    expected:1  2  3  4   5
    missing: 1  1  1  3   6      ← nums[i] - i - 1

This count only GROWS with i. So "missing < k" is true for a prefix and
false afterwards: a monotone predicate.

Find the FIRST index where missing >= k, call it `low`.
Everything before it contains fewer than k missing numbers, so the k-th
missing number sits just past them:

    answer = k + low

  nums=[2,3,4,7,11], k=5
  i:     0  1  2  3  4
  miss:  1  1  1  3  6
                 ↑ first i with miss >= 5 is i=4 → answer = 5 + 4 = 9 ✓
```

Why `k + low`? Among the first `k + low` positive integers, exactly `low` are present in the array (indices `0..low-1`). So the `k`-th missing one is `k + low`.

---

## Code Full Solution

```cpp
class Solution {
public:
    int findKthPositive(vector<int>& nums, int k) {
        int n = nums.size();
        int low = 0;
        int high = n - 1;

        while(low <= high) {
            int mid = low + (high - low) / 2;
            int missing = nums[mid] - (mid + 1);

            if(missing < k) {
                low = mid + 1;    // not enough missing yet — go right
            } else {
                high = mid - 1;   // enough missing here — go left
            }
        }

        return k + low;
    }
};
```

---

## Code Explanation

### The Missing Count

```cpp
int missing = nums[mid] - (mid + 1);
```

If no numbers were missing, `nums[mid]` would equal `mid + 1`. Every gap before `mid` inflates the actual value, so the difference is exactly how many positive integers are missing up to and including index `mid`.

```
nums[3] = 7, mid = 3 → 7 - 4 = 3 numbers missing in [1..7]: 1, 5, 6 ✓
```

### The Predicate

```cpp
if(missing < k) low = mid + 1;
else            high = mid - 1;
```

`missing < k` means the k-th missing number lies further right. Otherwise it is at or left of `mid`. This is a plain "find the first true" search — no `ans` variable, because the answer is derived from the final `low`.

### `return k + low`

```cpp
return k + low;
```

After the loop, `low` counts the array elements that come **before** the k-th missing number. So the answer is the `k`-th missing value counted from `low` elements present:

```
answer = k + (number of array elements before it) = k + low
```

This holds even when *every* element is `< k`-worth of gaps — including the case where `k` runs past the whole array.

### Why It Still Works When `k` Is Huge

```
nums=[1,2,3], k=2
Every index has missing = 0 < 2 → low walks to 3 (== n), high ends at 2
return 2 + 3 = 5 ✓   (missing are 4, 5 → the 2nd is 5)
```

`low` is allowed to equal `n`, which is exactly the "answer is beyond the last element" case. No special handling needed.

---

## Full Trace: `nums=[2,3,4,7,11]`, `k=5`

```
n=5, low=0, high=4

mid=2: nums[2]=4 → missing = 4 - 3 = 1
       1 < 5 → low = 3

low=3, high=4

mid=3: nums[3]=7 → missing = 7 - 4 = 3
       3 < 5 → low = 4

low=4, high=4

mid=4: nums[4]=11 → missing = 11 - 5 = 6
       6 < 5? NO → high = 3

low=4 > high=3 → return 5 + 4 = 9 ✓
```

## Full Trace: `nums=[1,2,3,4]`, `k=2`

```
low=0, high=3

mid=1: nums[1]=2 → missing = 2 - 2 = 0
       0 < 2 → low = 2

mid=2: nums[2]=3 → missing = 3 - 3 = 0
       0 < 2 → low = 3

mid=3: nums[3]=4 → missing = 4 - 4 = 0
       0 < 2 → low = 4

low=4 > high=3 → return 2 + 4 = 6 ✓   (5 is the 1st missing, 6 is the 2nd)
```

---

## Example Traces

### The Missing Number Is Before the Array

```
nums=[3,4,5], k=1
mid=1: 4-2 = 2 >= 1 → high=0
mid=0: 3-1 = 2 >= 1 → high=-1
return 1 + 0 = 1 ✓   (1 and 2 are missing; the 1st is 1)
```

### `k` Land Exactly on a Gap Boundary

```
nums=[2,3], k=1
mid=0: 2-1 = 1 >= 1 → high=-1 → return 1 + 0 = 1 ✓
```

### Single Element

```
nums=[5], k=3
mid=0: 5-1 = 4 >= 3 → high=-1 → return 3 + 0 = 3 ✓
(1,2,3,4 are missing; the 3rd is 3)
```

### Array Starts at 1 With Gaps Later

```
nums=[1,10,11], k=8
i:     0   1   2
miss:  0   8   8
mid=1: 10-2 = 8 >= 8 → high=0
mid=0: 1-1 = 0 < 8 → low=1
return 8 + 1 = 9 ✓
(present: 1,10,11 → missing: 2..9 → 8th is 9)
```

---

## Edge Cases

### `k` Beyond All Gaps

Handled by `low` reaching `n`; the formula `k + low` stays correct ✓

### Duplicates

Not allowed — the array is strictly increasing by the constraints. With duplicates, `nums[i] - (i+1)` would no longer mean "count of missing ≤ nums[i]".

### Negative or Zero Values

The problem is about **positive** integers only, which is why the expected value at index `i` is `i + 1` rather than `i`. That "+1" is load-bearing.

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(log n) — one binary search over indices |
| Space | O(1) |

```
Linear alternative: walk i = 0..n-1, accumulate gaps, or simply count from 1.
O(n) time, O(1) space — correct but does not exploit the sorted order.
```

---

## Key Insight

```
You never search for a VALUE — you search for a POSITION where the gap count
crosses k.

  gaps up to index i = nums[i] - (i + 1)

That expression converts "how many are missing" into arithmetic on the index,
which makes the whole thing a monotone predicate over indices — exactly what
binary search needs. The final answer is then `k + low`, no counting required.
```

---

## References

- 🔗 [LeetCode 1539 — Kth Missing Positive Number](https://leetcode.com/problems/kth-missing-positive-number/)
- 🔗 [GFG — K-th missing element](https://www.geeksforgeeks.org/k-th-missing-element-in-an-unsorted-array/) (unsorted variant, uses a set)

# Maximum Subarray Sum

## Problem Link
🔗 [LeetCode 53 — Maximum Subarray](https://leetcode.com/problems/maximum-subarray/)

---

## What is this Problem?

Given an integer array `nums`, find the **contiguous subarray** with the largest sum and return that sum. The subarray must be non-empty.

```
nums = [-2,1,-3,4,-1,2,1,-5,4]  → Output: 6
        subarray [4,-1,2,1] sums to 6

nums = [1]                      → Output: 1
nums = [5,4,-1,7,8]             → Output: 23  (the whole array)
nums = [-5,-2,-9]               → Output: -2  (must pick at least one element)
```

Constraints: `1 <= nums.length <= 10^5`, `-10^4 <= nums[i] <= 10^4`, so the answer fits in `int` (at most `10^9`).

---

## The Idea

Kadane's algorithm — one pass, one running sum.

```
At every index i, ask: is a subarray ENDING at i better if it extends the
best subarray ending at i-1, or if it starts fresh at i?

    best ending at i = max( nums[i],  best ending at i-1 + nums[i] )

A negative running sum can never help a future element, so it is equivalent
to resetting to 0. Track the best value seen at any point.

nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]

  i=0  -2                        sum=-2   best=-2
  i=1   1   extend(-1) vs new(1) → 1       best=1
  i=2  -3   extend(-2) vs new(-3)→ -2      best=1
  i=3   4   extend( 2) vs new(4) → 4       best=4
  i=4  -1   extend( 3) vs new(-1)→ 3       best=4
  i=5   2   extend( 5) vs new(2) → 5       best=5
  i=6   1   extend( 6) vs new(1) → 6       best=6   ← answer
  i=7  -5   extend( 1) vs new(-5)→ 1       best=6
  i=8   4   extend( 5) vs new(4) → 5       best=6
```

The answer is the maximum of `best ending at i` over all `i` — one variable, one pass.

---

## Code Full Solution

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // [-2,1,-3,4,-1,2,1,-5,4]

        int sum = nums[0];
        int maxSum = nums[0];

        for(int i=1;i<n;i++) {
            sum+=nums[i];
            if(sum > maxSum) maxSum = sum;
            if(sum < 0) = sum = 0;
            if(sum > nums[i]) {
                maxSum = nums[i];
                sum = nums[i];
            }
        }
        return maxSum;
    }
};
```

> ⚠️ **This file does not compile as written, and even with the syntax repaired the third `if` block breaks the algorithm.** Details below. The code is kept verbatim so the defects stay visible; the corrected version is given after the explanation.

---

## ⚠️ Bugs in the Current Code

### Bug 1 — `n` is never declared (compile error)

```cpp
for(int i=1;i<n;i++)
```

There is no `n` in scope. `Solution` has no member `n` and nothing declares it. The loop bound must be `nums.size()`:

```cpp
int n = nums.size();
```

### Bug 2 — `= sum = 0` is not a statement (compile error)

```cpp
if(sum < 0) = sum = 0;
```

A statement cannot begin with `=`. The compiler stops here ("expected primary-expression before `=`"). The intent was clearly the negative-reset:

```cpp
if(sum < 0) sum = 0;
```

### Bug 3 — the third block overwrites the answer (logic error)

```cpp
if(sum > nums[i]) {
    maxSum = nums[i];
    sum = nums[i];
}
```

After `sum += nums[i]`, the condition `sum > nums[i]` is true **whenever the previous running sum was positive** — i.e. exactly in the case where extending is the *better* choice. So this block:

1. throws away the extended sum and restarts at `nums[i]`, and
2. assigns `maxSum = nums[i]`, which can *lower* the best answer (and it never even compares against the old `maxSum`).

```
nums = [4,-1,2,1]   (answer 6)

Repaired code (Bugs 1 & 2 fixed, Bug 3 still present):
  sum=4  maxSum=4
  i=1: sum=3, 3>4? no, not<0, 3 > -1 → maxSum=-1, sum=-1
  i=2: sum=1, 1>-1 → maxSum=1,  1 > 2? no
  i=3: sum=2, 2>1 → maxSum=2,   2 > 1 → maxSum=1, sum=1

  returns 1  ✗   (correct answer is 6)
```

The file's own commented example shows the same collapse: after the two syntax fixes, `[-2,1,-3,4,-1,2,1,-5,4]` returns **-1** instead of **6**.

**Fix:** delete the entire `if(sum > nums[i])` block. The reset belongs to the other branch, and "restart at `nums[i]`" is expressed by comparing, never by assigning `maxSum`.

### Bug 4 — `sum = nums[0]` plus a reset-to-zero misses some all-negative arrays

Even after removing Bug 3, the shape `sum = nums[0]` … `if(sum < 0) sum = 0` loses pure-negative subarrays:

```
nums = [-5,-2]   (answer -2)
sum=-5, maxSum=-5
i=1: sum=-7; maxSum stays -5; sum<0 → sum=0
returns -5  ✗

Starting the running sum at 0 instead of nums[0] fixes it:
sum=0, maxSum=nums[0] → i=0: sum=-5, maxSum=-5, reset 0
                      → i=1: sum=-2, maxSum=-2 ✓
```

---

## Corrected Version

The minimal, idiomatic Kadane matching the original structure (one pass from index 1, no separate reset):

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        int sum = nums[0];        // best sum of a subarray ending at i
        int maxSum = nums[0];     // best seen anywhere

        for(int i = 1; i < n; i++) {
            sum = max(nums[i], sum + nums[i]);   // extend or restart at i
            maxSum = max(maxSum, sum);
        }
        return maxSum;
    }
};
```

`max(nums[i], sum + nums[i])` is the whole algorithm: extending only wins when the carried sum is positive. This handles `n == 1` (loop never runs, returns `nums[0]`) and all-negative arrays (`sum` never exceeds `nums[i]`).

Equivalent "reset" formulation, for reference:

```cpp
int sum = 0, maxSum = nums[0];
for(int x : nums) {
    sum += x;
    maxSum = max(maxSum, sum);
    if(sum < 0) sum = 0;
}
```

---

## Code Explanation (of the corrected version)

### `sum` — Best Sum Ending Here

```cpp
sum = max(nums[i], sum + nums[i]);
```

`sum` is not "the sum so far" — it is **the best sum of a subarray that ends exactly at `i`**. Dropping that distinction is what makes the original third block wrong.

```
If sum is 5 and nums[i] is -1 → sum = 4   (extend: 5 + (-1) beats -1)
If sum is -3 and nums[i] is 2 → sum = 2   (restart: 2 beats -1)
```

### `maxSum` — Best Sum Anywhere

```cpp
maxSum = max(maxSum, sum);
```

Only ever raised. Every candidate is a value of `sum` at some index, so remembering the maximum is sufficient — no start/end indices needed.

### Why `sum` Can Be Reset to 0 Is Safe

A negative prefix can only reduce any subarray that continues past it, so any future optimum ignores it. `max(nums[i], sum + nums[i])` encodes this comparison directly.

---

## Full Trace (corrected version): `nums=[-2,1,-3,4,-1,2,1,-5,4]`

```
init: sum = -2, maxSum = -2

i=1 (1):  sum = max(1, -1)   = 1   → maxSum = max(-2, 1) = 1
i=2 (-3): sum = max(-3, -2)  = -2  → maxSum = 1
i=3 (4):  sum = max(4, 2)    = 4   → maxSum = 4
i=4 (-1): sum = max(-1, 3)   = 3   → maxSum = 4
i=5 (2):  sum = max(2, 5)    = 5   → maxSum = 5
i=6 (1):  sum = max(1, 6)    = 6   → maxSum = 6   ← [4,-1,2,1]
i=7 (-5): sum = max(-5, 1)   = 1   → maxSum = 6
i=8 (4):  sum = max(4, 5)    = 5   → maxSum = 6

return 6 ✓
```

## Full Trace (corrected version): `nums=[-5,-2,-9]`

```
init: sum = -5, maxSum = -5
i=1: sum = max(-2, -7) = -2 → maxSum = -2
i=2: sum = max(-9, -11) = -9 → maxSum = -2
return -2 ✓   (the single element -2)
```

---

## Example Traces

### The Whole Array Is the Answer

```
nums = [5,4,-1,7,8]
sum: 5 → 9 → 8 → 15 → 23 ; maxSum: 5 → 9 → 9 → 15 → 23
return 23 ✓
```

### A Single Negative

```
nums = [-1]
loop never runs → return -1 ✓
This is why initialising with nums[0] rather than 0 matters: with sum = 0 the
answer would wrongly become 0 for an all-negative array.
```

### Best Subarray in the Middle

```
nums = [-1, 4, -2, 3, -10]
sum: -1 → 4 → 2 → 5 → -5 ; maxSum: -1 → 4 → 4 → 5 → 5
return 5 ✓   ([4,-2,3])
```

### Zeros Between Negatives

```
nums = [-2, 0, -3]
sum: -2 → 0 → -3 ; maxSum: -2 → 0 → 0
return 0 ✓   (subarray [0])
```

---

## Edge Cases

### `n == 1`

Loop body never executes; both `sum` and `maxSum` are `nums[0]` → correct ✓

### All Negative

Handled by `max(nums[i], sum + nums[i])` — `sum` collapses to the largest single element ✓ (this is exactly where the original reset-only form fails)

### All Positive

`sum` is the prefix sum and `maxSum` the total → returns `Σ nums` ✓

### Zeros

Neither extend nor restart changes anything; `max` picks either ✓

### Overflow

Values are `±10^4` and `n ≤ 10^5`, so the worst `|sum| = 10^9` — inside `int32`. With larger values (`10^9` elements) use `long long`.

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(n) — one pass |
| Space | O(1) |

```
Brute force over all O(n^2) subarrays: O(n^2) time → 10^10 at n=10^5, too slow.
Divide & conquer (the LeetCode follow-up): O(n log n), useful only if you
need the actual subarray bounds or a parallel-friendly split.
Prefix sums + running minimum also give O(n), but O(n) extra space.
```

---

## Key Insight

```
The trick is to keep only ONE number per index: the best sum of a subarray
ENDING there.

That single state is enough because a subarray ending at i is either
"nums[i] alone" or "the best one ending at i-1, plus nums[i]" — nothing else
is reachable.

Hence: sum = max(nums[i], sum + nums[i]),  answer = max over all sum.
```

---

## References

- 🔗 [LeetCode 53 — Maximum Subarray](https://leetcode.com/problems/maximum-subarray/)
- 🔗 [Wikipedia — Maximum subarray problem (Kadane's algorithm)](https://en.wikipedia.org/wiki/Maximum_subarray_problem)

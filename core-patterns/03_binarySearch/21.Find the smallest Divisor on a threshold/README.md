# Find the Smallest Divisor Given a Threshold

## Problem Link
🔗 [LeetCode 1283 — Find the Smallest Divisor Given a Threshold](https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/)

---

## What is this Problem?

Given an array `nums` and an integer `threshold`, choose a divisor `d` and compute

```
sum = Σ ceil(nums[i] / d)
```

Return the **smallest** `d` for which `sum <= threshold`.

```
nums=[1,2,5,9], threshold=6  → Output: 5
nums=[44,22,33,11,1], threshold=5 → Output: 1
nums=[21212,10101,12121], threshold=1000000 → Output: 1
```

For `d=5`: `ceil(1/5)+ceil(2/5)+ceil(5/5)+ceil(9/5) = 1+1+1+2 = 5 ≤ 6` ✓ and `d=4` gives `7 > 6`, so `5` is the minimum.

---

## The Idea

```
The sum depends only on d, and it DECREASES as d grows:

  d small → each quotient is large → sum large
  d large → each quotient → 1        → sum → n

So "sum(d) <= threshold" is monotone: false ... false, true ... true.
Answer = the FIRST d where it becomes true → binary search on d.

Search range [1, max(nums)]:
  d = 1          → sum = Σ nums[i]        (largest possible)
  d = max(nums)  → sum = n                (smallest possible; can't improve after)

  d    :  1   2   3   4  [5]  6   7   8   9
  sum  : 17  10   7   7   5   5   5   5   4
                        ↑ threshold=6 → first d with sum ≤ 6 is 5 ✓
```

Note the sum is **non-increasing but not strictly decreasing**: `ceil(x / d)` is monotone in `d`, so the sum can only fall — but it stays *flat* across divisors that change no quotient (`d=5,6,7,8` all give `5` above). That is enough: the predicate `sum(d) <= threshold` is false up to a point and true from then on, which is all binary search needs.

---

## Code Full Solution

```cpp
class Solution {
public:
    int possible(vector<int>& nums, int mid) {
        int sum = 0;
        for(auto &el : nums) {
            sum += ceil(double(el) / mid);     // ceil division
        }
        return sum;
    }

    int smallestDivisor(vector<int>& nums, int threshold) {
        int low = 1;
        int high = *max_element(nums.begin(), nums.end());

        while(low <= high) {
            int mid = low + (high - low) / 2;

            if(possible(nums, mid) <= threshold) {
                high = mid - 1;      // works — try a smaller divisor
            } else {
                low = mid + 1;       // sum too big — raise the divisor
            }
        }
        return low;
    }
};
```

---

## Code Explanation

### Ceiling Division

```cpp
sum += ceil(double(el) / mid);
```

`ceil` on a `double` division. It is correct for LeetCode's ranges (values `<= 10^6` are exactly representable), but the integer form is both faster and impossible to get wrong:

```cpp
sum += (el + mid - 1) / mid;
```

### The Predicate

```cpp
if(possible(nums, mid) <= threshold) high = mid - 1;
else                                 low  = mid + 1;
return low;
```

Feasible → look left for something smaller. Infeasible → look right. The loop ends with `low` on the first feasible divisor, so no `ans` variable is needed.

### Search Bounds

```cpp
int low  = 1;
int high = *max_element(nums.begin(), nums.end());
```

`d = 0` is not a divisor, so the range starts at `1`. At `d = max(nums)` every term is `ceil(x / max) = 1`, giving `sum = n` — the smallest sum achievable, so larger divisors are pointless.

---

## ⚠️ `int` Overflow in the Sum

```cpp
int possible(vector<int>& nums, int mid) {
    int sum = 0;
```

`sum` is an `int`. At `d = 1` it becomes `Σ nums[i]`, and LeetCode allows `n = 5·10^4` values up to `10^6`:

```
max sum = 5·10^4 × 10^6 = 5·10^10   →  far beyond INT_MAX (2.147·10^9)
```

So `sum` overflows and the predicate can report a *smaller* sum than reality — which wrongly marks an infeasible divisor as feasible, and the binary search returns too small an answer.

### The fix

```cpp
long long possible(vector<int>& nums, int mid) {
    long long sum = 0;
    for(int el : nums) sum += (el + mid - 1) / mid;   // integer ceil, 64-bit
    return sum;
}
```

### Small extra win

Since only `sum <= threshold` matters, the loop can bail out early instead of adding everything:

```cpp
for(int el : nums) {
    sum += (el + mid - 1) / mid;
    if(sum > threshold) return sum;      // already infeasible, stop
}
```

This keeps every intermediate value tiny — an alternative way to sidestep the overflow entirely.

---

## Full Trace: `nums=[1,2,5,9]`, `threshold=6`

```
low=1, high=9

mid=5: sum = 1 + 1 + 1 + 2 = 5
       5 <= 6 → feasible → high=4

low=1, high=4

mid=2: sum = 1 + 1 + 3 + 5 = 10
       10 <= 6? NO → low=3

low=3, high=4

mid=3: sum = 1 + 1 + 2 + 3 = 7
       7 <= 6? NO → low=4

low=4, high=4

mid=4: sum = 1 + 1 + 2 + 3 = 7
       7 <= 6? NO → low=5

low=5 > high=4 → return 5 ✓
```

## Full Trace: `nums=[44,22,33,11,1]`, `threshold=5`

```
low=1, high=44

mid=22: sum = 2 + 1 + 2 + 1 + 1 = 7 > 5 → low=23
mid=33: sum = 2 + 1 + 1 + 1 + 1 = 6 > 5 → low=34
mid=39: sum = 2 + 1 + 1 + 1 + 1 = 6 > 5 → low=40
mid=42: sum = 2 + 1 + 1 + 1 + 1 = 6 > 5 → low=43
mid=43: sum = 2 + 1 + 1 + 1 + 1 = 6 > 5 → low=44
mid=44: sum = 1 + 1 + 1 + 1 + 1 = 5 <= 5 → high=43

low=44 > high=43 → return 44 ✓
```

Only `d = max(nums)` reaches `sum = n = 5`, so 44 is the answer.

---

## Example Traces

### Threshold Allows `d = 1`

```
nums=[21212,10101,12121], threshold=1000000
mid ranges down to 1: sum at d=1 is 44,434 << 10^6 → feasible
The search collapses to low=1 → returns 1 ✓
```

### Every Element Is 1

```
nums=[1,1,1], threshold=3 → any d gives sum 3
mid=1: 3 <= 3 → high=0 → return 1 ✓  (the smallest possible divisor)
```

### Large Values, Tight Threshold

```
nums=[1000000], threshold=1
Search over [1, 10^6] finds d=1000000: ceil(10^6/10^6)=1 ≤ 1 ✓
mid values below that give 2 and are rejected → returns 10^6 ✓
```

---

## Edge Cases

### Answer Always Exists

`d = max(nums)` gives `sum = n`. LeetCode guarantees `threshold >= n`, so the smallest feasible divisor is always inside `[1, max(nums)]` and `low` never exits above the range.

### `d` Mid-Way Is Flat

Several divisors can produce the same sum (`d=5,6,7,8` above). The predicate only cares about `<= threshold`, so flats are harmless — the search simply lands on the leftmost feasible one.

### Float Precision

`ceil(double(el) / mid)` is exact for `el <= 2^53`; LeetCode's `10^6` limit is far below that. Still, integer ceil removes the question entirely.

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(n · log(max(nums))) |
| Space | O(1) |

```
log2(10^6) ≈ 20 passes, n ≤ 5·10^4 → about 10^6 operations.
Trying d = 1, 2, 3, ... would be O(n · max(nums)) = 5·10^10 → far too slow.
```

---

## Key Insight

```
"Smallest divisor meeting a threshold" is a monotone predicate, not a search
over the array.

  sum(d) = Σ ceil(nums[i] / d)     decreases (weakly) as d increases

Find the first d where sum(d) ceases to exceed the threshold — binary search
over the divisor space, with an O(n) counting pass as the predicate.
```

---

## References

- 🔗 [LeetCode 1283 — Find the Smallest Divisor Given a Threshold](https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/)
- 🔗 [LeetCode 875 — Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/) (identical shape: minimize a rate)

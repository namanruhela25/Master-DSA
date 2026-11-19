# Median of Two Sorted Arrays

## Problem Link
🔗 [LeetCode 4 — Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/)

---

## What is this Problem?

Two sorted arrays `nums1` and `nums2` of sizes `n` and `m`. Find the **median** of their combined sorted order in `O(log(min(n, m)))` — i.e. without merging.

```
nums1=[1,3],   nums2=[2]      → Output: 2.0
nums1=[1,2],   nums2=[3,4]    → Output: 2.5
nums1=[0,0],   nums2=[0,0]    → Output: 0.0
nums1=[],      nums2=[1]      → Output: 1.0
```

For an odd total, the median is the middle element. For an even total, it is the **average of the two middle elements** — here `(2+3)/2 = 2.5`.

Merging is `O(n+m)`. The intended solution is **binary search on the partition point**, `O(log(min(n,m)))`.

---

## The Idea

```
A median splits a sorted array into a LEFT half and a RIGHT half of equal size.

For the merged array of length n+m, let half = (n+m+1)/2.
Choose Px elements from nums1 and Py = half - Px from nums2 to form the LEFT
side. The split is CORRECT when:

    max(LEFT) <= min(RIGHT)
    i.e.  x1 <= x4   and   x2 <= x3

where, for the cut nums1[0..Px-1] | nums1[Px..]:

    x1 = nums1[Px-1]   biggest element of nums1 on the LEFT
    x3 = nums1[Px]     smallest element of nums1 on the RIGHT
    x2 = nums2[Py-1]   biggest element of nums2 on the LEFT
    x4 = nums2[Py]     smallest element of nums2 on the RIGHT

If the cut is valid:
  odd total  → median = max(x1, x2)           (the last element of LEFT)
  even total → median = (max(x1,x2) + min(x3,x4)) / 2

Which way to move if invalid:
  x1 > x4  → too many elements from nums1 on the LEFT → go LEFT  (high = Px-1)
  x2 > x3  → too few  elements from nums1 on the LEFT → go RIGHT (low  = Px+1)
```

Search space: `Px` can range over `[0, n]`, so binary search over that range. Because `Px` determines `Py` exactly, only one variable needs searching — this is what makes it `O(log n)`.

Out-of-range reads are handled with sentinels: `INT_MIN` for "nothing on the left", `INT_MAX` for "nothing on the right".

---

## Code Full Solution

```cpp
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();

        // Search on the SMALLER array so Px ∈ [0, n] stays small
        if(n > m) return findMedianSortedArrays(nums2, nums1);

        int low = 0;
        int high = n;

        while(low <= high) {
            int Px = low + (high - low) / 2;        // elements taken from nums1
            int Py = ((n + m + 1) / 2) - Px;        // elements taken from nums2

            int x1 = (Px == 0) ? INT_MIN : nums1[Px - 1];
            int x2 = (Py == 0) ? INT_MIN : nums2[Py - 1];

            int x3 = (Px == n) ? INT_MAX : nums1[Px];
            int x4 = (Py == m) ? INT_MAX : nums2[Py];

            if(x1 <= x4 && x2 <= x3) {              // a valid split
                if((m + n) % 2 == 0) {
                    return (max(x1, x2) + min(x3, x4)) / 2.0;
                } else {
                    return max(x1, x2);
                }
            }

            // x1 > x4 means nums1's left part reaches too far right
            if(x1 > x4) {
                high = Px - 1;
            } else {
                low = Px + 1;
            }
        }
        return -1;   // unreachable for valid input
    }
};
```

---

## Code Explanation

### `if(n > m) return findMedianSortedArrays(nums2, nums1);`

Ensures `nums1` is the shorter array, so `n <= m`. Then `Px ∈ [0, n]` and `Py = half - Px` can never exceed `m`... but a subtle point: this recursion **returns** rather than just swapping in place, which is fine because the recursive call does the entire search. It costs one extra stack frame.

Why search on the small array? Because the loop runs `log(n)` iterations instead of `log(m)`, and the bounds stay easy to reason about.

### `Py = ((n + m + 1) / 2) - Px`

`half = (n+m+1)/2` includes the middle element for odd totals:

```
n+m = 5 → half = 3  → LEFT has 3, RIGHT has 2   (odd: median is last of LEFT)
n+m = 4 → half = 2  → LEFT has 2, RIGHT has 2   (even: average across the cut)
```

This one formula works for both parities; that is why the code does not branch until it computes the answer.

### The Four Sentinels

```cpp
x1 = (Px == 0) ? INT_MIN : nums1[Px - 1];
x2 = (Py == 0) ? INT_MIN : nums2[Py - 1];
x3 = (Px == n) ? INT_MAX : nums1[Px];
x4 = (Py == m) ? INT_MAX : nums2[Py];
```

- `Px == 0` → nums1 contributes **nothing** to LEFT → its "left max" must not constrain the check → `INT_MIN`.
- `Px == n` → nums1 contributes everything to LEFT → its "right min" must not constrain the check → `INT_MAX`.
- Same for `Py` vs `m`.

Without sentinels every iteration would need boundary `if`s in the comparison itself.

### The Validity Test

```cpp
if(x1 <= x4 && x2 <= x3)
```

Both cross-conditions are needed:

- `x1 <= x4`: the biggest LEFT element of nums1 must not exceed the smallest RIGHT element of nums2.
- `x2 <= x3`: the biggest LEFT element of nums2 must not exceed the smallest RIGHT element of nums1.

Within each array the order is already sorted, so only these two **cross** pairs can be violated.

### Choosing the Answer

```cpp
if((m + n) % 2 == 0)
    return (max(x1, x2) + min(x3, x4)) / 2.0;
return max(x1, x2);
```

- Odd total: the median is the largest of everything on the LEFT.
- Even total: average the largest of LEFT with the smallest of RIGHT.

`/ 2.0` (not `/ 2`) is what makes this return a `double` rather than truncating.

### Moving the Cut

```cpp
if(x1 > x4) high = Px - 1;
else        low  = Px + 1;
```

If `x1 > x4`, nums1 is contributing too much to LEFT — shrink `Px`. Otherwise the only possible violation is `x2 > x3`, meaning nums2 is over-contributing — increase `Px` (which decreases `Py`).

One of the two violations must hold whenever the cut is invalid, so the `else` is safe.

### `return -1`

Unreachable for well-formed input: some valid cut always exists. It exists only to satisfy the compiler.

---

## Full Trace: `nums1=[1,3]`, `nums2=[2]`

```
n=2, m=1 → n > m → recurse with nums1=[2], nums2=[1,3]   (n=1, m=2)

half = (1+2+1)/2 = 2
low=0, high=1

mid: Px=0, Py=2
  x1 = INT_MIN            (Px==0)
  x2 = nums2[1] = 3
  x3 = nums1[0] = 2
  x4 = INT_MAX            (Py==m==2)
  check: x1 <= x4 ✓, x2 <= x3 → 3 <= 2 ✗
  x1 > x4? INT_MIN > INT_MAX → no → low = 1

mid: Px=1, Py=1
  x1 = nums1[0] = 2
  x2 = nums2[0] = 1
  x3 = INT_MAX            (Px==n==1)
  x4 = nums2[1] = 3
  check: 2 <= 3 ✓, 1 <= INT_MAX ✓ → VALID

  total = 3, odd → median = max(2, 1) = 2.0 ✓
```

## Full Trace: `nums1=[1,2]`, `nums2=[3,4]`

```
n=2, m=2, no swap
half = (2+2+1)/2 = 2
low=0, high=2

mid: Px=1, Py=1
  x1 = 1, x2 = 3, x3 = 2, x4 = 4
  check: 1 <= 4 ✓, 3 <= 2 ✗
  x1 > x4? 1 > 4 → no → low = 2

mid: Px=2, Py=0
  x1 = nums1[1] = 2
  x2 = INT_MIN            (Py==0)
  x3 = INT_MAX            (Px==n==2)
  x4 = nums2[0] = 3
  check: 2 <= 3 ✓, INT_MIN <= INT_MAX ✓ → VALID

  total = 4, even → (max(2, INT_MIN) + min(INT_MAX, 3)) / 2.0
                  = (2 + 3) / 2.0 = 2.5 ✓
```

---

## Example Traces

### One Array Empty

```
nums1=[], nums2=[1]
n=0, m=1
half = (0+1+1)/2 = 1, low=0, high=0

Px=0, Py=1
  x1 = INT_MIN, x2 = nums2[0] = 1, x3 = INT_MAX, x4 = INT_MAX
  valid → total 1, odd → max(INT_MIN, 1) = 1.0 ✓
```

### All of `nums1` Below `nums2`

```
nums1=[1,2], nums2=[10,11]
Px=2, Py=0
  x1=2, x2=INT_MIN, x3=INT_MAX, x4=10 → valid
  even → (2 + 10) / 2.0 = 6.0
Combined [1,2,10,11] → (2+10)/2 = 6.0 ✓
```

### All of `nums1` Above `nums2`

```
nums1=[10,11], nums2=[1,2]
n=2,m=2 → no swap (equal sizes)
Px=2, Py=0: x1=11, x2=INT_MIN, x3=INT_MAX, x4=nums2[0]=1
  check: 11 <= 1 ✗ → x1 > x4 → high = 1
Px=0, Py=2: x1=INT_MIN, x2=nums2[1]=2, x3=nums1[0]=10, x4=INT_MAX
  check ✓ → even → (max(INT_MIN,2) + min(10,INT_MAX))/2.0 = 6.0 ✓
Combined [1,2,10,11] → 6.0 ✓
```

### Duplicates Everywhere

```
nums1=[0,0], nums2=[0,0] → 0.0
Both cuts at 1 give x1=x2=0, x3=x4=0 → (0+0)/2.0 = 0.0 ✓
The `<=` comparisons (not `<`) are what let equal values pass the validity test.
```

---

## Edge Cases

### `n + m == 1`

Odd branch, `max(x1, x2)` is that single element ✓.

### Both Arrays Empty

Not valid input (the combined array would be empty). `half = 0`, `Px = 0`, `Py = 0`, the check passes with all sentinels, and the odd/even branch divides `INT_MIN`s — meaningless. LeetCode guarantees at least one element.

### Both Arrays Same Size

No recursion — the swap only triggers when `n > m`. `Px ∈ [0, n]`, `Py ∈ [0, m]`, all in range ✓.

### Overflow in the Average

`(max(x1,x2) + min(x3,x4))` could overflow `int` if both values were near `INT_MAX`. Here the sentinels never appear simultaneously in the two terms, and real values are bounded by `10^6`, so `int` is safe. For unbounded inputs, `(a / 2.0) + (b / 2.0)` avoids it.

### The `-1` Fallback

If you ever see `-1.0`, the binary search range is wrong — the guards would have to work out to an impossible cut. Treat it as an assertion failure during development.

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(log(min(n, m))) |
| Space | O(1) besides the one recursive swap frame |

```
n=m=10^6 → about 20 iterations.
Merging both arrays would be O(n + m) = 2·10^6 and allocate a combined array.
```

---

## Key Insight

```
Don't binary search positions of elements — binary search the SPLIT.

A median is "half the elements on each side". For two sorted arrays, fixing
how many elements come from the first array fixes everything else:

    Py = half - Px

so there is only ONE variable to search, and its correctness is a two-line
comparison (x1 <= x4 and x2 <= x3). Sentinels replace all boundary handling.

The same partition trick extends directly to the "Kth element of two sorted
arrays" problem — there `half` becomes `k` and you stop at max(x1, x2).
```

---

## References

- 🔗 [LeetCode 4 — Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/)
- 🔗 [GFG — K-th Element of Two Sorted Arrays](https://www.geeksforgeeks.org/problems/k-th-element-of-two-sorted-array1317/1) (same partition idea)
- 🔗 [LeetCode 295 — Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/) (heaps, streaming variant)

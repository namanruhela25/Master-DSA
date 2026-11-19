# K-th Element of Two Sorted Arrays

## Problem Link
🔗 [GFG — K-th Element of Two Sorted Arrays](https://www.geeksforgeeks.org/problems/k-th-element-of-two-sorted-array1317/1)

---

## What is this Problem?

Two sorted arrays `a` and `b` of sizes `n` and `m`, and an integer `k`. Return the **k-th smallest element** of their combined sorted order (**1-indexed**) in `O(log(min(n, m)))` — without merging.

```
a=[2,3,6,7,9], b=[1,4,8,10,11], k=5  → Output: 6
a=[1,2,3],     b=[4],           k=2  → Output: 2
a=[1,2,3],     b=[10,11,12],    k=6  → Output: 12
```

Merged, the first example is `1,2,3,4,6,7,8,9,10,11`; the 5th smallest is **6**.

This is the **Median of Two Sorted Arrays** partition trick with `k` in place of `half`, and no parity handling — a strictly easier shape of the same problem.

---

## The Idea

```
Take the first k elements of the merged order and split them into:
    Px from a   (the first Px elements of a)
    Py from b   (the first Py elements of b)
with  Px + Py = k.

The split is CORRECT when every element on the LEFT half is <= every element
on the RIGHT half. Since each array is sorted, only the two CROSS pairs matter:

    x1 = a[Px-1]  (largest LEFT from a)   must be <=  x4 = b[Py]  (smallest RIGHT from b)
    x2 = b[Py-1]  (largest LEFT from b)   must be <=  x3 = a[Px]  (smallest RIGHT from a)

When the split is valid:
    LEFT holds exactly the k smallest elements
    → answer = max(x1, x2)          (the largest of them = the k-th)

Which way to move:
    x1 > x4  → too much of a on the LEFT → go LEFT   (high = Px - 1)
    x2 > x3  → too little of a on the LEFT → go RIGHT (low = Px + 1)

Bounds on Px — this is the only genuinely new part versus the median problem:

    low  = max(0, k - m)   b cannot supply more than m elements, so a must
                           supply at least k - m
    high = min(k, n)       a cannot supply more than k elements, and cannot
                           supply more than n

  a = [2,3,6,7,9], b = [1,4,8,10,11], k = 5
  low = max(0, 5-5) = 0,  high = min(5,5) = 5
```

---

## Code Full Solution

```cpp
class Solution {
  public:
    int kthElement(vector<int> &a, vector<int> &b, int k) {
        int n = a.size();
        int m = b.size();

        // Search on the smaller array
        if(n > m) return kthElement(b, a, k);

        // a must contribute at least k-m elements (b cannot hold more than m)
        int low = max(0, k - m);

        // a can contribute at most k, and at most n
        int high = min(k, n);

        while(low <= high) {
            int Px = low + (high - low) / 2;   // elements taken from a
            int Py = k - Px;                   // elements taken from b

            int x1 = (Px == 0) ? INT_MIN : a[Px - 1];
            int x2 = (Py == 0) ? INT_MIN : b[Py - 1];

            int x3 = (Px == n) ? INT_MAX : a[Px];
            int x4 = (Py == m) ? INT_MAX : b[Py];

            if(x1 <= x4 && x2 <= x3) {
                return max(x1, x2);            // k-th smallest
            }

            if(x1 > x4) {
                high = Px - 1;                 // taken too much of a
            } else {
                low = Px + 1;                  // taken too little of a
            }
        }
        return -1;
    }
};
```

---

## Code Explanation

### `if(n > m) return kthElement(b, a, k);`

Keeps `a` the shorter array so `Px ∈ [0, n]` is the smaller range to binary search. One recursion frame, then the whole search happens in the inner call.

### `low = max(0, k - m)` — The Important Bound

```cpp
int low = max(0, k - m);
```

If `k` exceeds `m`, `b` alone cannot fill the LEFT half: `Py = k - Px <= m` forces `Px >= k - m`. Without this bound, small `Px` values would make `Py > m` and index out of range.

```
a = [2], k = 6, b = [5 elements max]
k - m = 1 → a must contribute at least 1, otherwise b would need 6 > 5.
```

### `high = min(k, n)` — The Symmetric Bound

`a` cannot contribute more than the `k` slots available, nor more than it has. Both bounds together shrink the search to the range where `Py` is always legal.

### Sentinels Replace Boundary Checks

```cpp
x1 = (Px == 0) ? INT_MIN : a[Px - 1];   // nothing from a on the left
x3 = (Px == n) ? INT_MAX : a[Px];       // a entirely on the left
x2 = (Py == 0) ? INT_MIN : b[Py - 1];
x4 = (Py == m) ? INT_MAX : b[Py];
```

A non-existent "left max" must never reject a split → `INT_MIN`. A non-existent "right min" must never reject a split → `INT_MAX`. This is what lets `Px = 0` and `Px = n` be handled by the same comparison.

### The Validity Test

```cpp
if(x1 <= x4 && x2 <= x3)
```

Only the two cross pairs can be out of order — each array is already sorted internally. When both hold, the partition is a genuine cut of the merged order.

### Why `max(x1, x2)` Is the Answer

LEFT contains exactly `Px + Py = k` elements, all `<=` everything on the RIGHT. The k-th smallest is therefore the **largest** element of LEFT, which is `max(x1, x2)`.

Note the contrast with the median problem: no parity branch and no division by 2 — that is the entire difference between the two solutions.

### Moving the Cut

```cpp
if(x1 > x4) high = Px - 1;
else        low  = Px + 1;
```

`x1 > x4` means `a`'s cut reached past a smaller element of `b` → take fewer from `a`. Otherwise the failing condition can only be `x2 > x3` → take more from `a` (and correspondingly fewer from `b`).

### `return -1`

Unreachable for valid input (some cut always exists). It only satisfies the compiler.

---

## Full Trace: `a=[2,3,6,7,9]`, `b=[1,4,8,10,11]`, `k=5`

```
n=5, m=5 → no swap
low = max(0, 5-5) = 0
high = min(5,5)  = 5

Px=2, Py=3
  x1 = a[1] = 3,  x2 = b[2] = 8,  x3 = a[2] = 6,  x4 = b[3] = 10
  check: 3 <= 10 ✓, 8 <= 6 ✗
  x1 > x4? 3 > 10 → no → low = 3

Px=4, Py=1
  x1 = a[3] = 7,  x2 = b[0] = 1,  x3 = a[4] = 9,  x4 = b[1] = 4
  check: 7 <= 4 ✗
  x1 > x4 → yes → high = 3

Px=3, Py=2
  x1 = a[2] = 6,  x2 = b[1] = 4,  x3 = a[3] = 7,  x4 = b[2] = 8
  check: 6 <= 8 ✓, 4 <= 7 ✓ → VALID
  return max(6, 4) = 6 ✓
```

## Full Trace: `a=[1,2,3]`, `b=[4]`, `k=2`

```
n=3 > m=1 → recurse with a=[4], b=[1,2,3]     (n=1, m=3)

low = max(0, 2-3) = 0
high = min(2,1)  = 1

Px=0, Py=2
  x1 = INT_MIN          (Px==0)
  x2 = b[1] = 2
  x3 = a[0] = 4
  x4 = b[2] = 3
  check: INT_MIN <= 3 ✓, 2 <= 4 ✓ → VALID
  return max(INT_MIN, 2) = 2 ✓
```

---

## Example Traces

### The Lower Bound `k - m` Is Forced

```
a=[1,2,3], b=[10,11,12], k=6
low = max(0, 6-3) = 3, high = min(6,3) = 3

Px=3, Py=3
  x1 = a[2] = 3,  x2 = b[2] = 12,  x3 = INT_MAX (Px==n),  x4 = INT_MAX (Py==m)
  check ✓ → return max(3, 12) = 12 ✓
With k=6 both arrays must be fully consumed — the bounds pin the cut immediately.
```

### `k = 1` — The Global Minimum

```
a=[1,2,3], b=[10,11,12], k=1
low = 0, high = 1

Px=0, Py=1
  x1 = INT_MIN, x2 = b[0] = 10, x3 = a[0] = 1, x4 = b[1] = 11
  check: 10 <= 1 ✗ → low = 1

Px=1, Py=0
  x1 = a[0] = 1, x2 = INT_MIN, x3 = a[1] = 2, x4 = b[0] = 10
  check ✓ → return max(1, INT_MIN) = 1 ✓   (the smallest of all)
```

### Equal Arrays

```
a=[1,3], b=[1,3], k=2 → 1
The `<=` (not `<`) comparisons let equal values pass validity, so duplicates
never block the search.
Px=1, Py=1: x1=1, x2=1, x3=3, x4=3 → valid → max(1,1) = 1 ✓
```

### One Array Empty

```
a=[], b=[5,6,7], k=2
n=0, m=3 → no swap
low = max(0, 2-3) = 0, high = min(2,0) = 0

Px=0, Py=2
  x1 = INT_MIN, x2 = b[1] = 6, x3 = INT_MAX (Px==n==0), x4 = b[2] = 7
  check ✓ → return 6 ✓
```

---

## Edge Cases

### `k` Larger Than `n + m`

Undefined input — the bounds may produce `Py > m` and read out of range. GFG guarantees `1 <= k <= n + m`.

### `k = n + m`

Both arrays fully consumed: `low = max(0, n+m-m) = n`, `high = min(n+m, n) = n` → returns `max(a[n-1], b[m-1])`, the overall maximum ✓.

### Empty Array

Handled: `n = 0` gives `low = high = 0` and the sentinels protect `x3`. If `a` is empty and longer than `b`... impossible, so the swap is safe.

### Duplicates Across Arrays

`<=` everywhere means ties are accepted on either side of the cut, so duplicates cannot block a valid partition ✓.

### The `-1` Fallback

If it ever returns `-1`, the bounds math is wrong. Treat it as an assertion during development.

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(log(min(n, m))) |
| Space | O(1) besides one recursive swap frame |

```
min(n,m) = 10^6 → ~20 iterations.
Merging both arrays and indexing k-1 would be O(n + m).
```

---

## Key Insight

```
The median problem and the k-th element problem are the SAME algorithm:

    pick Px from a, Py = target - Px from b
    validity = (x1 <= x4) && (x2 <= x3)
    answer   = max(x1, x2)

Median:  target = (n+m+1)/2, plus a parity branch for the even case.
K-th:    target = k, no branch at all.

The only new idea for k-th is that the search range is not [0, n] but
[max(0, k-m), min(k, n)] — because Py must be a legal index into b.
```

---

## References

- 🔗 [GFG — K-th Element of Two Sorted Arrays](https://www.geeksforgeeks.org/problems/k-th-element-of-two-sorted-array1317/1)
- 🔗 [LeetCode 4 — Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/) (same partition, plus parity)
- 🔗 [GFG — K-th Smallest in Two Sorted Arrays (binary search on value)](https://www.geeksforgeeks.org/k-th-element-two-sorted-arrays/) (an O(log range) alternative)

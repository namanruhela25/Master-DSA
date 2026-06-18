# Continuous Subarray Sum

## Problem Link
🔗 [LeetCode 523 — Continuous Subarray Sum](https://leetcode.com/problems/continuous-subarray-sum/)

---

## What is this Problem?

Given an integer array `nums` and an integer `k`, return `true` if `nums` has a **continuous subarray of length at least 2** whose elements sum to a **multiple of `k`** (i.e., sum == 0, k, 2k, 3k, ...).

**Examples:**
```
nums = [23,2,4,6,7], k = 6
Output: true
Subarray [2,4] (indices 1-2), sum=6, which is 1×6. Length=2 ✓

nums = [23,2,6,4,7], k = 6
Output: true
Subarray [23,2,6,4,7], sum=42, which is 7×6. Length=5 ✓

nums = [23,2,6,4,7], k = 13
Output: false
No subarray of length ≥ 2 sums to a multiple of 13.
```

---

## The Problem Explained

Think of it like **reading a car's odometer and checking if you've returned to the same "remainder position"**:

```
You drive (add elements). The odometer shows total miles.
But you only care about miles MOD k — like clock hands.

k=6: positions are 0,1,2,3,4,5 — then they wrap back to 0.

Miles log: [23, 2, 4, 6, 7]
Running mod 6:
  Start:  0
  +23:    23%6 = 5
  +2:     25%6 = 1
  +4:     29%6 = 5   ← same as position 5 seen before!
  +6:     35%6 = 5
  +7:     42%6 = 0

When the odometer hits remainder 5 again at index 2,
it means the miles driven between those two readings
are a multiple of 6!

That stretch covers index 1 and 2 → length = 2 ≥ 2 ✓
```

**Key idea:** If `prefixSum[j] % k == prefixSum[i] % k`, then the sum of elements from `i+1` to `j` is a multiple of `k`. Track the **first occurrence of each remainder** in the hashmap. When a remainder repeats, check if the gap is at least 2.

---

## HOOK TO REMEMBER FOREVER

**"SAME REMAINDER TWICE = MULTIPLE OF k IN BETWEEN. SEED mpp[0]=-1 FOR SUBARRAYS STARTING AT INDEX 0."**

Every time you see "subarray sum is a multiple of k, length ≥ 2":
- ✅ `sum` = running prefix sum, `mpp` = hashmap of {remainder → first index it occurred}
- ✅ Initialize `mpp[0] = -1` (the "before index 0" sentinel)
- ✅ For each index `i`: compute `rem = sum % k`
- ✅ If `rem` seen before AND `i - mpp[rem] >= 2` → return `true`
- ✅ If `rem` NOT seen before → store `mpp[rem] = i` (ONLY the FIRST occurrence!)
- ✅ O(n) time, O(k) space

**Remember: Store the FIRST occurrence of each remainder, never update it. A later re-occurrence gives a LONGER gap — which can only help satisfy the length ≥ 2 condition.** 🔄

---

## Why Same Remainder = Multiple of k

```
Math behind it:

prefixSum[j] % k = r
prefixSum[i] % k = r   (same remainder, i < j)

→ prefixSum[j] - prefixSum[i] ≡ 0 (mod k)
→ sum of elements (i+1 to j) is divisible by k ✓

This is the modular arithmetic identity:
  (a % k == b % k) ↔ (a - b) is divisible by k
```

---

## Why `mpp[0] = -1` (Not 0)

This is the trickiest initialization in the problem:

```
Case: nums = [6, 2], k = 6
  i=0: sum=6, rem=0. mpp[0] is already set.
       i - mpp[0] = 0 - (-1) = 1. 1 >= 2? NO. Continue.
  i=1: sum=8, rem=2. Not seen. mpp[2]=1.
  return false ✗ — but [6] alone has length 1, so false IS correct here.

Case: nums = [6, 2, 3], k = 6
  i=0: sum=6, rem=0. i-mpp[0]=0-(-1)=1. 1>=2? NO.
  i=1: sum=8, rem=2. Not seen. mpp[2]=1.
  i=2: sum=11, rem=5. Not seen. mpp[5]=2.
  return false — [6] is length 1, and no pair works.

Case: nums = [6, 2, 4], k = 6
  i=0: sum=6, rem=0. i-mpp[0]=0-(-1)=1. 1>=2? NO.
  i=1: sum=8, rem=2. Not seen. mpp[2]=1.
  i=2: sum=12, rem=0. i-mpp[0]=2-(-1)=3. 3>=2? YES! return true.
       Subarray (0..2) = [6,2,4], sum=12=2×6, length=3 ✓

What if mpp[0]=0 instead?
  i=2: sum=12, rem=0. i-mpp[0]=2-0=2. 2>=2? YES. Still works here.

But: nums=[12], k=6
  i=0: sum=12, rem=0. With mpp[0]=0: i-mpp[0]=0-0=0. 0>=2? NO. Correct.
  i=0: sum=12, rem=0. With mpp[0]=-1: i-mpp[0]=0-(-1)=1. 1>=2? NO. Also correct.

The real difference: nums=[6,6], k=6
  With mpp[0]=-1:
    i=0: rem=0. i-(-1)=1. 1>=2? NO.
    i=1: rem=0. Already in mpp (first occurrence). 1-(-1)=2. 2>=2? YES! ✓
    return true. Subarray [6,6] sum=12=2×6 ✓

  With mpp[0]=0:
    Same result here. But consider nums=[0,0], k=6:
    i=0: sum=0, rem=0. i-0=0. 0>=2? NO.
    i=1: sum=0, rem=0. mpp[0]=0. i-mpp[0]=1-0=1. 1>=2? NO.
    return false — WRONG! [0,0] sum=0 is a multiple of 6, length=2. ❌

  With mpp[0]=-1:
    i=0: rem=0. i-(-1)=1. 1>=2? NO.
    i=1: rem=0. mpp[0]=-1. i-mpp[0]=1-(-1)=2. 2>=2? YES! ✓

Conclusion: mpp[0]=-1 is the ONLY correct sentinel value.
It represents "prefix sum 0 existed one step BEFORE index 0."
```

---

## Why Store Only the FIRST Occurrence of Each Remainder

```cpp
if (mpp.find(rem) != mpp.end()) {
    if (i - mpp[rem] >= 2) return true;
} else {
    mpp[rem] = i;   // ← only stores if NOT already present
}
```

```
If a remainder occurs at indices 2, 5, and 9:
  First occurrence: index 2
  Later occurrences: indices 5 and 9

The LONGEST possible gap is always from the FIRST occurrence.
  - Gap from 2 to 9 = 7 (best chance of satisfying length ≥ 2)
  - Gap from 5 to 9 = 4 (always smaller)

Storing only the first occurrence maximizes the gap
for every future re-occurrence → best chance of finding
a valid subarray. Updating the map would only shrink gaps.
```

---

## How It Works Step By Step

### Example: `nums = [23, 2, 4, 6, 7], k = 6`

```
mpp = {0: -1}, sum = 0

i=0: sum=23, rem=23%6=5.
  mpp has no 5 → store mpp[5]=0. mpp={0:-1, 5:0}

i=1: sum=25, rem=25%6=1.
  mpp has no 1 → store mpp[1]=1. mpp={0:-1, 5:0, 1:1}

i=2: sum=29, rem=29%6=5.
  mpp has 5 at index 0!
  i - mpp[5] = 2 - 0 = 2. 2 >= 2? YES! return true ✓

Subarray = nums[1..2] = [2, 4], sum = 6 = 1×6. Length = 2 ✓
```

### Visual — Remainder Timeline

```
Index:       -1   0   1   2   3   4
nums:             23   2   4   6   7
prefix sum:   0  23  25  29  35  42
rem (mod 6):  0   5   1   5   5   0
              ↑               ↑
          mpp[0]=-1      rem=5 at i=2
                         mpp[5]=0 from i=0
                         gap = 2-0 = 2 ≥ 2 → TRUE!
```

---

## Code Full Solution

```cpp
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> mpp;
        int sum = 0;
        mpp[0] = -1;

        for (int i = 0; i < n; i++) {
            sum += nums[i];
            int rem = sum % k;
            if (mpp.find(rem) != mpp.end()) {
                if (i - mpp[rem] >= 2) return true;
            } else {
                mpp[rem] = i;
            }
        }
        return false;
    }
};
```

---

## Code Explanation

### Initialize

```cpp
unordered_map<int, int> mpp;
int sum = 0;
mpp[0] = -1;
```

- **`sum`:** Running prefix sum
- **`mpp`:** Maps `{remainder → first index this remainder was seen}`
- **`mpp[0] = -1`:** Seeds the "before the array" state — prefix sum 0 exists at index -1 (one before index 0)

---

### The Main Loop

```cpp
sum += nums[i];
int rem = sum % k;
```

Standard prefix sum, then take modulo to get the remainder.

---

### Lookup and Length Check

```cpp
if (mpp.find(rem) != mpp.end()) {
    if (i - mpp[rem] >= 2) return true;
} else {
    mpp[rem] = i;
}
```

**Branch 1 — Remainder seen before:**
```
The gap between first occurrence and now is i - mpp[rem].
This gap = length of the subarray between those two prefix sums.

If gap >= 2: valid subarray found → return true.
If gap < 2:  subarray is only length 1 → doesn't satisfy the
             "at least 2 elements" constraint → continue.

Important: we do NOT update mpp[rem] when a duplicate is found.
First occurrence stays — maximizes gap for any future re-occurrence.
```

**Branch 2 — Remainder not seen before:**
```
First time we see this remainder.
Store mpp[rem] = i so future occurrences can measure the gap.
```

---

## Complete Example Traces

### Trace 1: Valid Subarray of Length 2

```
nums=[23,2,4,6,7], k=6

mpp={0:-1}, sum=0

i=0: sum=23, rem=5. Not in mpp → mpp[5]=0
i=1: sum=25, rem=1. Not in mpp → mpp[1]=1
i=2: sum=29, rem=5. In mpp! gap=2-0=2 ≥ 2 → return true ✓
```

### Trace 2: Valid Subarray — Entire Array

```
nums=[23,2,6,4,7], k=6

mpp={0:-1}, sum=0

i=0: sum=23, rem=5. Not in mpp → mpp[5]=0
i=1: sum=25, rem=1. Not in mpp → mpp[1]=1
i=2: sum=31, rem=1. In mpp! gap=2-1=1 < 2 → don't return
i=3: sum=35, rem=5. In mpp! gap=3-0=3 ≥ 2 → return true ✓

Subarray nums[1..3]=[2,6,4], sum=12=2×6, length=3 ✓
```

### Trace 3: No Valid Subarray

```
nums=[23,2,6,4,7], k=13

mpp={0:-1}, sum=0

i=0: sum=23, rem=23%13=10. Not in mpp → mpp[10]=0
i=1: sum=25, rem=25%13=12. Not in mpp → mpp[12]=1
i=2: sum=31, rem=31%13=5.  Not in mpp → mpp[5]=2
i=3: sum=35, rem=35%13=9.  Not in mpp → mpp[9]=3
i=4: sum=42, rem=42%13=3.  Not in mpp → mpp[3]=4

Loop ends. return false ✓
```

### Trace 4: Sum Is Exactly k at Start

```
nums=[6,2], k=6

mpp={0:-1}, sum=0

i=0: sum=6, rem=0. mpp has 0 at -1! gap=0-(-1)=1. 1<2 → no return.
i=1: sum=8, rem=2. Not in mpp → mpp[2]=1.

return false ✓ (subarray [6] has length 1 — doesn't qualify)
```

### Trace 5: Sum Is k Across 2 Elements

```
nums=[6,6], k=6

mpp={0:-1}, sum=0

i=0: sum=6, rem=0. mpp has 0! gap=0-(-1)=1. 1<2 → continue.
i=1: sum=12, rem=0. mpp has 0! gap=1-(-1)=2. 2>=2 → return true ✓

Subarray [6,6], sum=12=2×6, length=2 ✓
```

### Trace 6: Zeros in Array

```
nums=[0,0], k=6

mpp={0:-1}, sum=0

i=0: sum=0, rem=0. mpp has 0 at -1! gap=0-(-1)=1. 1<2 → continue.
i=1: sum=0, rem=0. mpp has 0 at -1! gap=1-(-1)=2. 2>=2 → return true ✓

Subarray [0,0], sum=0=0×6, length=2 ✓
```

### Trace 7: Gap Found but Too Short

```
nums=[1,5], k=6

mpp={0:-1}, sum=0

i=0: sum=1, rem=1. Not in mpp → mpp[1]=0
i=1: sum=6, rem=0. mpp has 0 at -1! gap=1-(-1)=2. 2>=2 → return true ✓

Subarray [1,5], sum=6=1×6, length=2 ✓
```

---

## Edge Cases

### Case 1: Array Length 2, Valid

```
Input: [1,5], k=6
Output: true ✓  (minimum length subarray)
```

### Case 2: All Zeros, k = Anything

```
Input: [0,0], k=100
rem always = 0%100 = 0.
mpp[0]=-1, so gap at i=1 = 1-(-1)=2 ≥ 2 → true ✓
```

### Case 3: One Element Only

```
Input: [5], k=5
Only 1 element — can't have length ≥ 2.
i=0: rem=0. gap=0-(-1)=1 < 2. No return.
return false ✓
```

### Case 4: Remainder Seen Twice But Gap Always 1

```
Input: [1,1,1], k=2

i=0: sum=1, rem=1. Not in mpp → mpp[1]=0
i=1: sum=2, rem=0. mpp has 0 at -1! gap=1-(-1)=2 ≥ 2 → return true ✓

[1,1]=2=1×2, length=2 ✓
```

---

## Time Complexity

- **O(n)** — single pass through the array
- Each hashmap operation is O(1) average
- Total: **O(n)**

---

## Space Complexity

- **O(min(n, k))** — hashmap stores at most `k` distinct remainders (0 to k-1)
- In practice bounded by both n (can't have more entries than elements) and k
- Total: **O(min(n, k))**

---

## Key Insights

### This Problem vs Subarray Sum Equals K (LeetCode 560)

```
LeetCode 560 (Sum = k exactly):
  mpp stores {prefixSum → frequency}
  mpp[0] = 1  (count, not index)
  Counts ALL valid subarrays (any length)

LeetCode 523 (Sum = multiple of k, length ≥ 2):
  mpp stores {remainder → FIRST index}
  mpp[0] = -1 (index, not count)
  Checks existence only + enforces minimum length

Key differences:
  560 → frequency map, counts everything
  523 → first-index map, checks gap length
```

### Why `mpp.find(rem)` Instead of `mpp[rem]`

```cpp
// ❌ Don't do this:
if (mpp[rem] != ...) { ... }

// ✅ Do this:
if (mpp.find(rem) != mpp.end()) { ... }
```

```
Using mpp[rem] on an unordered_map with a missing key
INSERTS the key with a default value of 0.

That would corrupt the map — suddenly rem → 0 exists,
and future lookups would incorrectly think we've seen
that remainder at index 0.

mpp.find() checks existence WITHOUT inserting. ✓
```

### The Subarray Being Counted

```
When we find rem seen at mpp[rem]=idx and the current index=i:

The valid subarray is: nums[idx+1 ... i]

Why idx+1 and not idx?
  mpp[rem]=idx means prefixSum UP TO AND INCLUDING idx had remainder rem.
  The subarray that produces a multiple of k STARTS AT idx+1
  (the element AFTER the first occurrence) and ENDS AT i.

Length = i - (idx+1) + 1 = i - idx ≥ 2
  ↔ i - idx ≥ 2
  ↔ i - mpp[rem] ≥ 2 ✓

This is exactly the check in the code.
```

---

## References

- 🔗 [LeetCode 523 — Continuous Subarray Sum](https://leetcode.com/problems/continuous-subarray-sum/)
- 🔗 [Solution leetcode 523](https://www.youtube.com/watch?v=wmn3c1mP0pY)
# 4Sum

## Problem Link
🔗 [LeetCode 18 — 4Sum](https://leetcode.com/problems/4sum/)

---

## What is this Problem?

Given an array `nums` of `n` integers and an integer `target`, return **all unique quadruplets** `[nums[a], nums[b], nums[c], nums[d]]` such that they sum to `target`. The same element cannot be used more than once (by index), and the result must not contain duplicate quadruplets.

**Examples:**
```
nums = [1,0,-1,0,-2,2], target = 0
Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

nums = [2,2,2,2,2], target = 8
Output: [[2,2,2,2]]
```

---

## The Problem Explained

Think of it like **finding four people whose combined weights hit an exact target**:

```
Sorted weights: [-2, -1, 0, 0, 1, 2]

We need to pick 4 distinct positions whose values sum to 0.

Brute force: try every combination of 4 indices → O(n⁴) — too slow.

Smarter: fix the first two with nested loops (i, j),
then use TWO POINTERS on the remaining sorted portion
to find the last two efficiently. This is "3Sum extended
by one more fixed loop" — or "2Sum extended by two more
fixed loops."
```

**Key idea:** Sort the array. Use two nested loops to fix the first two numbers (`i`, `j`). For the remaining two, use the **two-pointer technique** (like in 2Sum on a sorted array) to find pairs that complete the target sum. Skip duplicates at every level to avoid repeated quadruplets.

---

## HOOK TO REMEMBER FOREVER

**"SORT FIRST. FIX TWO WITH NESTED LOOPS. TWO-POINTER THE REST. SKIP DUPLICATES AT EVERY LEVEL."**

Every time you see "kSum" problems (2Sum, 3Sum, 4Sum):
- ✅ **Sort** the array first — duplicates become adjacent, two-pointer becomes possible
- ✅ Fix `i` and `j` with nested loops, skipping duplicates at each level
- ✅ For the remaining `[j+1, n-1]` range, use two pointers `k` (left) and `l` (right)
- ✅ `sum < target` → `k++` (need a bigger sum)
- ✅ `sum > target` → `l--` (need a smaller sum)
- ✅ `sum == target` → record the quadruplet, move BOTH pointers, **then skip duplicates**
- ✅ O(n³) time, O(1) extra space (excluding output)

**Remember: 4Sum = 2 fixed loops + 1 two-pointer pass. Each additional "Sum" level adds one more fixed loop wrapped around the same two-pointer core!** 🎯

---

## Why Sorting Enables Everything

```
1. Duplicate detection becomes trivial:
   After sorting, identical values are ADJACENT.
   Checking nums[i] == nums[i-1] catches duplicates in O(1).

2. Two-pointer technique becomes valid:
   In a sorted array, moving k right INCREASES the sum,
   moving l left DECREASES the sum — predictable, monotonic
   behavior that two pointers rely on.

3. Early termination opportunities:
   (Not used in this exact code, but a common optimization:
   if nums[i] is too large, all further sums will be too large too,
   since the array is sorted — can break early.)
```

## How It Works Step By Step

### Example: `nums = [1,0,-1,0,-2,2], target = 0`

### Step 1 — Sort

```
Before: [1, 0, -1, 0, -2, 2]
After:  [-2, -1, 0, 0, 1, 2]
          0   1  2  3  4  5  ← indices
```

### Step 2 — Outer Loops Fix `i` and `j`

```
i=0 (nums[0]=-2):
  j=1 (nums[1]=-1):
    k=2, l=5 → two-pointer search in range [2,5]

    nums[k]=0, nums[l]=2. sum = -2+-1+0+2 = -1 < 0 → k++
    nums[k]=0 (index3), nums[l]=2. sum = -2+-1+0+2 = -1 < 0 → k++
    k=4,l=5: nums[k]=1,nums[l]=2. sum=-2-1+1+2=0 == target!
      Record [-2,-1,1,2]. k++→5, l--→4. k<l fails (5<4 false). STOP this round.

  j=2 (nums[2]=0):
    k=3, l=5 → search in [3,5]
    nums[k]=0,nums[l]=2. sum=-2+0+0+2=0==target!
      Record [-2,0,0,2]. k++→4, l--→4. k<l fails (4<4 false). STOP.

  j=3 (nums[3]=0): nums[j-1]=nums[2]=0==nums[3] → SKIP (duplicate j)

  j=4 (nums[4]=1):
    k=5, l=5 → k<l fails immediately (5<5 false). No pairs to check.

i=1 (nums[1]=-1):
  j=2 (nums[2]=0):
    k=3, l=5 → search [3,5]
    nums[k]=0,nums[l]=2. sum=-1+0+0+2=1>0 → l--
    k=3,l=4: nums[k]=0,nums[l]=1. sum=-1+0+0+1=0==target!
      Record [-1,0,0,1]. k++→4,l--→3. k<l fails. STOP.

  j=3 (nums[3]=0): nums[j-1]=nums[2]=0==nums[3] → SKIP

  j=4 (nums[4]=1):
    k=5,l=5 → k<l fails immediately.

i=2 (nums[2]=0):
  j=3 (nums[3]=0):
    k=4,l=5 → search [4,5]
    nums[k]=1,nums[l]=2. sum=0+0+1+2=3>0 → l--
    k=4,l=4: k<l fails (4<4 false). STOP.

  j=4 (nums[4]=1): k=5,l=5 → fails immediately.

i=3 (nums[3]=0): nums[i-1]=nums[2]=0==nums[3] → SKIP (duplicate i)

i=4,5: not enough room for j,k,l (loop naturally produces no new results)

Final: [[-2,-1,1,2], [-2,0,0,2], [-1,0,0,1]] ✓
```

---

## Code Full Solution

```cpp
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;

        for (int i = 0; i < n; i++) {
            if (i > 0 && nums[i-1] == nums[i]) continue;

            for (int j = i + 1; j < n; j++) {
                if (j > i + 1 && nums[j-1] == nums[j]) continue;

                int k = j + 1;
                int l = n - 1;

                while (k < l) {
                    long long sum = nums[i];
                    sum += nums[j];
                    sum += nums[k];
                    sum += nums[l];

                    if (sum == target) {
                        vector<int> tmp = {nums[i], nums[j], nums[k], nums[l]};
                        ans.push_back(tmp);
                        k++;
                        l--;
                        while (k < l && nums[k] == nums[k+1]) k++;
                        while (k < l && nums[l] == nums[l-1]) l--;
                    } else if (sum < target) {
                        k++;
                    } else {
                        l--;
                    }
                }
            }
        }
        return ans;
    }
};
```

---

## Code Explanation

### Sort First

```cpp
sort(nums.begin(), nums.end());
```

Essential prerequisite — enables duplicate skipping and the two-pointer technique.

---

### Outer Loop — Fix `i`, Skip Duplicates

```cpp
for (int i = 0; i < n; i++) {
    if (i > 0 && nums[i-1] == nums[i]) continue;
    ...
}
```

```
If nums[i] equals the PREVIOUS element, skip this i entirely.

Why? Any quadruplet starting with this value of nums[i]
would have ALREADY been found when i pointed to the
previous occurrence of the same value. Skipping avoids
generating duplicate quadruplets at the OUTERMOST level.

Why i > 0 in the condition?
  Without it, nums[-1] would be accessed — out of bounds!
  i > 0 ensures there IS a previous element to compare against.
```

---

### Inner Loop — Fix `j`, Skip Duplicates

```cpp
for (int j = i + 1; j < n; j++) {
    if (j > i + 1 && nums[j-1] == nums[j]) continue;
    ...
}
```

```
Same duplicate-skipping logic, one level deeper.

Why j > i+1 (not j > 0)?
  j starts at i+1 for each new i. The FIRST value of j
  for a given i should NEVER be skipped — even if
  nums[j] happens to equal nums[j-1], that nums[j-1]
  might be nums[i] itself (already consumed) or could
  belong to an entirely different "i group."

  j > i+1 ensures we only compare j against a TRUE
  previous j-candidate WITHIN THE SAME i iteration.
```

---

### Two-Pointer Core

```cpp
int k = j + 1;
int l = n - 1;

while (k < l) {
    long long sum = nums[i] + nums[j] + nums[k] + nums[l];
    ...
}
```

**Why `long long` for `sum`?**
```
Four int values, each potentially near INT_MAX or INT_MIN,
summed together can overflow a 32-bit int.

Example: 4 × 2,000,000,000 = 8,000,000,000 — exceeds INT_MAX.

long long safely holds the sum during the comparison. ✓
```

**The three-way branch:**
```
sum == target: found a valid quadruplet — record it.
sum < target:  need a LARGER sum → move k RIGHT (k++)
               (since array is sorted, nums[k+1] ≥ nums[k])
sum > target:  need a SMALLER sum → move l LEFT (l--)
               (since array is sorted, nums[l-1] ≤ nums[l])
```

---

### Recording and Skipping Duplicates at the Two-Pointer Level

```cpp
if (sum == target) {
    vector<int> tmp = {nums[i], nums[j], nums[k], nums[l]};
    ans.push_back(tmp);
    k++;
    l--;
    while (k < l && nums[k] == nums[k+1]) k++;
    while (k < l && nums[l] == nums[l-1]) l--;
}
```

```
After finding a match, we MUST move both pointers inward
(k++ and l--) — otherwise we'd find the EXACT SAME
quadruplet again on the next loop iteration (infinite match).

Then, the two while loops skip over any further duplicate
values at the NEW k and l positions:

  while (k < l && nums[k] == nums[k+1]) k++;
    → if multiple identical values sit at position k,
      skip past all but the last one (we already used one).

  while (k < l && nums[l] == nums[l-1]) l--;
    → same logic for the right pointer.

This prevents duplicate quadruplets caused by repeated
values adjacent to k or l.
```

---

## Complete Example Traces

### Trace 1: Standard Case

```
nums=[1,0,-1,0,-2,2], target=0 → sorted: [-2,-1,0,0,1,2]

(Full step-by-step trace shown in "How It Works" section above)

Result: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]] ✓
```

### Trace 2: All Same Elements

```
nums=[2,2,2,2,2], target=8 → sorted: [2,2,2,2,2]

i=0: nums[0]=2
  j=1: nums[1]=2
    k=2,l=4: sum=2+2+2+2=8==target!
      Record [2,2,2,2]. k++→3,l--→3. k<l fails (3<3 false).
      while(k<l...): doesn't run (k<l already false)
  j=2: nums[1]==nums[2]? j>i+1 (2>1) and nums[1]==nums[2] → SKIP
  j=3: nums[2]==nums[3]? j>i+1 (3>1) and nums[2]==nums[3] → SKIP
  j=4: not enough room (k=5 would exceed bounds, l=4, k<l fails)

i=1: nums[0]==nums[1] → SKIP (duplicate i)
i=2,3,4: all skipped similarly

Result: [[2,2,2,2]] ✓ (only one unique quadruplet, even though
                        5 elements could form C(5,4)=5 combinations)
```

### Trace 3: No Valid Quadruplet

```
nums=[1,2,3,4], target=100 → sorted: [1,2,3,4]

i=0,j=1: k=2,l=3. sum=1+2+3+4=10 < 100 → k++. k<l fails (3<3 false).
i=0,j=2: k=3,l=3. k<l fails immediately.
i=1,j=2: k=3,l=3. k<l fails immediately.
... all combinations checked, sum never reaches 100.

Result: [] ✓
```

### Trace 4: Negative Target

```
nums=[-3,-2,-1,0,0,1,2,3], target=-3 (illustrative example)

After sorting (already sorted), the algorithm proceeds
identically — negative targets work the same way since
the two-pointer logic relies on relative comparisons,
not the sign of the target.
```

### Trace 5: Exactly Four Elements

```
nums=[1,2,3,4], target=10 → sorted: [1,2,3,4]

i=0,j=1: k=2,l=3. sum=1+2+3+4=10==target!
  Record [1,2,3,4]. k++→3,l--→2. k<l fails.

Result: [[1,2,3,4]] ✓
```

---

## Edge Cases

### Case 1: Fewer Than 4 Elements

```
Input: nums=[1,2,3], target=6
n=3. Outer loop i goes to n-1=2.
For any i, j: k=j+1, l=n-1. If j is already near n-1,
k could exceed l immediately, so while(k<l) never executes.
Output: [] ✓ (impossible to form a quadruplet)
```

### Case 2: All Identical Elements, Not Matching Target

```
Input: nums=[1,1,1,1], target=5
Only quadruplet possible: [1,1,1,1], sum=4≠5.
Output: [] ✓
```

### Case 3: Multiple Duplicate Groups

```
Input: nums=[0,0,0,0,0,0], target=0
Only ONE unique quadruplet possible: [0,0,0,0].
Duplicate skipping at i, j, and k/l levels ensures
this is reported exactly once, not multiple times.
Output: [[0,0,0,0]] ✓
```

### Case 4: Integer Overflow Risk

```
Input: nums=[1000000000,1000000000,1000000000,1000000000],
       target=4000000000
Sum = 4×10^9, exceeds INT_MAX (~2.1×10^9).
long long sum handles this correctly.
Output: [[1000000000,1000000000,1000000000,1000000000]] ✓
```

---

## Time Complexity

- **O(n³)** where n = array size
- Sorting: O(n log n)
- Outer loop `i`: O(n)
- Inner loop `j`: O(n)
- Two-pointer scan for each (i,j): O(n)
- Combined: O(n) × O(n) × O(n) = O(n³)
- Total: **O(n³)** (dominates the O(n log n) sort)

---

## Space Complexity

- **O(1)** extra space (excluding output and sort's internal space)
- `ans` stores the required output
- Sorting may use O(log n) stack space internally (implementation-dependent)
- Total auxiliary space: **O(1)** to **O(log n)**

---

## Key Insights

### The "kSum" Pattern Generalizes

```
2Sum (sorted array, two pointers):     O(n)
3Sum (1 fixed loop + two pointers):    O(n²)
4Sum (2 fixed loops + two pointers):   O(n³)
kSum (k-2 fixed loops + two pointers): O(n^(k-1))

Each additional "Sum" level wraps one more loop around
the same two-pointer core. The two-pointer technique is
ALWAYS the innermost engine — it's what makes the LAST
two values find-able in O(n) instead of O(n²).
```

### Three Levels of Duplicate Skipping

```
Level 1 (outer i):  if (i>0 && nums[i-1]==nums[i]) continue;
Level 2 (inner j):  if (j>i+1 && nums[j-1]==nums[j]) continue;
Level 3 (k and l):  while loops after a match is found

All THREE are necessary. Removing any one of them
can produce duplicate quadruplets in the output.

Why three different mechanisms (continue vs while)?
  Levels 1&2: skip BEFORE even starting the two-pointer search
              for this i/j combination — avoids redundant work entirely.
  Level 3:    skip AFTER finding a match — because k and l
              move dynamically and duplicates can only be
              detected once we're at a confirmed match position.
```

### Why `k++, l--` BEFORE the Duplicate-Skip While Loops

```cpp
k++;
l--;
while (k < l && nums[k] == nums[k+1]) k++;
while (k < l && nums[l] == nums[l-1]) l--;
```

```
If we skipped duplicates BEFORE moving past the current
match, we'd skip duplicates of the CURRENT value — but we
need to move PAST the current value first, then check if
the NEW position is also a duplicate of ITSELF (not the
old matched value).

k++ moves to the next position.
Then the while loop asks: "is nums[k] same as nums[k+1]?"
  — checking for duplicates AT THE NEW position, going forward.

This order ensures we don't accidentally skip valid future
quadruplets that happen to share a value with the
just-recorded one.
```

---

## References

- 🔗 [LeetCode 18 — 4Sum](https://leetcode.com/problems/4sum/)
- 🔗 [LeetCode 15 — 3Sum (related, one less fixed loop)](https://leetcode.com/problems/3sum/)
- 🔗 [LeetCode 1 — Two Sum (the core two-pointer building block)](https://leetcode.com/problems/two-sum/)
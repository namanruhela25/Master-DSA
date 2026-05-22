# Binary Search

## Problem Link
🔗 [LeetCode 704 — Binary Search](https://leetcode.com/problems/binary-search/)

---

## What is this Problem?

You have a **sorted array of integers** and a `target` value. Find the **index** of the target in the array. If it doesn't exist, return `-1`.

- The array is **sorted in ascending order**
- Every element is **unique**
- Must run in **O(log n)** time — no linear scan allowed

**Examples:**
```
nums = [-1, 0, 3, 5, 9, 12],  target = 9
Output: 4
(9 is at index 4)

nums = [-1, 0, 3, 5, 9, 12],  target = 2
Output: -1
(2 doesn't exist in the array)

nums = [5],  target = 5
Output: 0
(Only one element, it matches)
```

---

## The Problem Explained

Think of it like **finding a word in a dictionary**:

```
You want to find the word "Mango" in a dictionary.

❌ Linear search (wrong way):
   Start from page 1, flip every single page... A, B, C, D...
   Takes forever for a big dictionary!

✅ Binary search (right way):
   Open the middle → lands on "M"
   "Mango" comes AFTER "M"? No, it's near "M" → search right half
   Open the middle of right half → lands on "P"
   "Mango" comes BEFORE "P" → search left half
   ...keeps halving until "Mango" is found!

Each step ELIMINATES HALF the remaining pages.
1000 pages → 10 steps. 1,000,000 pages → 20 steps!
```

**Key idea:** Because the array is **sorted**, you can always tell from the middle element whether the target is in the **left half** or **right half**. Eliminate the wrong half every step — never look at it again!

---

## HOOK TO REMEMBER FOREVER

**"CHECK MID, ELIMINATE HALF, REPEAT UNTIL FOUND OR GONE"**

Every time you see "search in sorted array in O(log n)":
- ✅ Set `left = 0`, `right = n - 1`
- ✅ Find `mid = left + (right - left) / 2` (safe from overflow!)
- ✅ If `nums[mid] == target` → found it, return `mid`
- ✅ If `target > nums[mid]` → target is in RIGHT half → `left = mid + 1`
- ✅ If `target < nums[mid]` → target is in LEFT half → `right = mid - 1`
- ✅ If `left > right` → target not in array → return `-1`

**Remember: Each step halves your search space. log₂(1,000,000) = 20. You'll never need more than 20 steps for a million elements!** 🔍

---

## How It Works Step By Step

### The Strategy

```
nums = [-1, 0, 3, 5, 9, 12],  target = 9
idx:     0  1  2  3  4   5

Step 1: left=0, right=5
  mid = 0 + (5-0)/2 = 2
  nums[2] = 3
  target(9) > 3 → search RIGHT half
  left = mid + 1 = 3

Step 2: left=3, right=5
  mid = 3 + (5-3)/2 = 4
  nums[4] = 9
  target(9) == 9 → FOUND!
  return 4 ✓
```

### Visual Animation: nums = [-1, 0, 3, 5, 9, 12], target = 9

```
Initial:
[ -1,  0,  3,  5,  9, 12 ]
  ↑                    ↑
 left                right

Step 1: mid = 2 → nums[2] = 3
[ -1,  0,  3,  5,  9, 12 ]
  ↑         ↑         ↑
 left      mid       right

  3 < 9 → eliminate LEFT half (everything ≤ mid)
  left = mid + 1 = 3

Step 2: mid = 4 → nums[4] = 9
[ -1,  0,  3,  5,  9, 12 ]
               ↑   ↑   ↑
             left  mid right

  9 == 9 → FOUND! Return index 4 ✓

Search space shrank: 6 → 3 → 1. Done in 2 steps!
```

---

## Code Full Solution

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                return mid;
            } else if (target > nums[mid]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return -1;
    }
};
```

> ⚠️ **Bug in the original code:** `int mid = left + right` should be `int mid = left + (right - left) / 2`. Using `left + right` directly does NOT compute the midpoint — it just sums the two pointers. This is also prone to **integer overflow** when `left + right` exceeds `INT_MAX`. The correct formula is shown above.

---

## Code Explanation

### Initialize the Search Window

```cpp
int left = 0;
int right = nums.size() - 1;
```

- **`left`:** Start of the current search window (index 0)
- **`right`:** End of the current search window (last index)
- Together, `[left, right]` is the range we're currently searching

**The search window shrinks every iteration:**
```
Step 1: [0, 5]   → 6 elements to search
Step 2: [3, 5]   → 3 elements to search
Step 3: [3, 3]   → 1 element to search
Step 4: left > right → stop (or found earlier)
```

---

### The Loop Condition

```cpp
while (left <= right)
```

**Why `<=` and not `<`?**
```
If left == right, there's still ONE element left to check.
We must not skip it!

Example: nums=[5], target=5
  left=0, right=0 → left==right → still enter the loop
  mid=0, nums[0]=5==target → return 0 ✓

If we used left < right:
  left==right → skip the loop entirely → return -1 ✗
```

---

### Computing the Midpoint

```cpp
int mid = left + (right - left) / 2;
```

**Why not `(left + right) / 2`?**
```
left = 1,000,000,000
right = 2,000,000,000

left + right = 3,000,000,000 → OVERFLOWS int! (max int ≈ 2.1 billion)

left + (right - left) / 2:
  right - left = 1,000,000,000  → safe
  / 2 = 500,000,000             → safe
  left + 500,000,000            → safe ✓

Always use this form. Same mathematical result, no overflow risk.
```

---

### The Three-Way Decision

```cpp
if (nums[mid] == target) {
    return mid;
} else if (target > nums[mid]) {
    left = mid + 1;
} else {
    right = mid - 1;
}
```

**Case 1 — Found it:**
```
nums[mid] == target → return the index immediately. Done!
```

**Case 2 — Target is in the RIGHT half:**
```
target > nums[mid]

Since array is SORTED:
  everything at indices ≤ mid is ≤ nums[mid] < target
  → target cannot be anywhere in [left, mid]
  → safely discard entire left half

left = mid + 1   (mid itself is also eliminated since nums[mid] ≠ target)
```

**Case 3 — Target is in the LEFT half:**
```
target < nums[mid]

Since array is SORTED:
  everything at indices ≥ mid is ≥ nums[mid] > target
  → target cannot be anywhere in [mid, right]
  → safely discard entire right half

right = mid - 1   (mid itself is also eliminated since nums[mid] ≠ target)
```

---

### Return -1 (Not Found)

```cpp
return -1;
```

- Reached only when `left > right` — the search window collapsed
- Every element has been logically eliminated
- Target is not in the array

```
nums = [-1, 0, 3, 5, 9, 12], target = 2

Step 1: left=0, right=5, mid=2 → nums[2]=3 > 2 → right=1
Step 2: left=0, right=1, mid=0 → nums[0]=-1 < 2 → left=1
Step 3: left=1, right=1, mid=1 → nums[1]=0 < 2 → left=2
Step 4: left=2, right=1 → left > right → EXIT LOOP

return -1 ✓
```

---

## Complete Example Traces

### Trace 1: Target Found (Right Half)

```
nums=[-1,0,3,5,9,12], target=9

left=0, right=5
  mid=2, nums[2]=3, 9>3 → left=3

left=3, right=5
  mid=4, nums[4]=9, 9==9 → return 4 ✓

Steps: 2
```

### Trace 2: Target Found (Left Half)

```
nums=[-1,0,3,5,9,12], target=0

left=0, right=5
  mid=2, nums[2]=3, 0<3 → right=1

left=0, right=1
  mid=0, nums[0]=-1, 0>-1 → left=1

left=1, right=1
  mid=1, nums[1]=0, 0==0 → return 1 ✓

Steps: 3
```

### Trace 3: Target Not Found

```
nums=[-1,0,3,5,9,12], target=2

left=0, right=5
  mid=2, nums[2]=3, 2<3 → right=1

left=0, right=1
  mid=0, nums[0]=-1, 2>-1 → left=1

left=1, right=1
  mid=1, nums[1]=0, 2>0 → left=2

left=2, right=1 → left > right → EXIT

return -1 ✓
```

### Trace 4: Target is the First Element

```
nums=[1,3,5,7,9,11], target=1

left=0, right=5
  mid=2, nums[2]=5, 1<5 → right=1

left=0, right=1
  mid=0, nums[0]=1, 1==1 → return 0 ✓

Steps: 2
```

### Trace 5: Target is the Last Element

```
nums=[1,3,5,7,9,11], target=11

left=0, right=5
  mid=2, nums[2]=5, 11>5 → left=3

left=3, right=5
  mid=4, nums[4]=9, 11>9 → left=5

left=5, right=5
  mid=5, nums[5]=11, 11==11 → return 5 ✓

Steps: 3
```

### Trace 6: Single Element — Found

```
nums=[5], target=5

left=0, right=0
  mid=0, nums[0]=5, 5==5 → return 0 ✓

Steps: 1
```

### Trace 7: Single Element — Not Found

```
nums=[5], target=3

left=0, right=0
  mid=0, nums[0]=5, 3<5 → right=-1

left=0, right=-1 → left > right → EXIT

return -1 ✓
```

### Trace 8: Two Elements

```
nums=[2,8], target=8

left=0, right=1
  mid=0, nums[0]=2, 8>2 → left=1

left=1, right=1
  mid=1, nums[1]=8, 8==8 → return 1 ✓
```

---

## Edge Cases

### Case 1: Target Smaller than All Elements

```
Input: nums=[3,5,7,9], target=1
- Every mid check → target < nums[mid] → right shrinks
- right becomes -1, left=0 → left > right
Output: -1 ✓
```

### Case 2: Target Larger than All Elements

```
Input: nums=[3,5,7,9], target=100
- Every mid check → target > nums[mid] → left grows
- left becomes 4 = n, right=3 → left > right
Output: -1 ✓
```

### Case 3: Target is Mid Every Time (exact center)

```
Input: nums=[1,3,5,7,9], target=5
- left=0, right=4, mid=2 → nums[2]=5 == target
Output: 2 ✓  (found on first try!)
```

### Case 4: Large Array (Why O(log n) matters)

```
n = 1,000,000,000 (one billion elements)

Linear search: up to 1,000,000,000 steps ❌
Binary search: at most log₂(1,000,000,000) ≈ 30 steps ✓

Each doubling of array size costs only 1 extra step.
```

---

## Time Complexity

- **O(log n)** where n = array size
- Every iteration halves the search space
- After k iterations, search space = n / 2^k
- Loop ends when n / 2^k < 1 → k = log₂(n)
- Total: **O(log n)**

```
n=8:   8 → 4 → 2 → 1  (3 steps = log₂8)
n=16:  16 → 8 → 4 → 2 → 1  (4 steps = log₂16)
n=1M:  at most 20 steps
```

---

## Space Complexity

- **O(1)** — Constant extra space
- Only three integer variables: `left`, `right`, `mid`
- No extra array, no recursion stack
- Total extra space: **O(1)**

---

## Key Insights

### Why Sorted Array is Non-Negotiable

```
Unsorted: [3, 1, 4, 1, 5, 9]
  mid=2 → nums[2]=4, target=1, 1<4 → search left
  left half: [3,1] → but 1 is ALSO in the right half [5,9]? No but...
  We'd throw away half without knowing if target is there!

Sorted: [-1, 0, 3, 5, 9, 12]
  mid=2 → nums[2]=3, target=9, 9>3
  GUARANTEE: everything left of mid is ≤ 3 < 9
  → Target CANNOT be in left half → safe to eliminate

Sorted order = the guarantee that lets us eliminate halves confidently.
Binary search ONLY works because of this guarantee.
```

### The Overflow Bug — A Classic Interview Trap

```cpp
// ❌ WRONG (potential overflow):
int mid = (left + right) / 2;

// ✅ CORRECT (overflow-safe):
int mid = left + (right - left) / 2;
```

```
Both formulas give the same mathematical result.
But (left + right) can exceed INT_MAX in C++ when both are large.

This is a famous bug that caused a bug in Java's standard library
binary search implementation for years. Know it. Use the safe form.
```

### Why `left = mid + 1` and `right = mid - 1` (not just `mid`)

```
❌ left = mid  (without +1):
  If nums[mid] != target and left == mid:
    next iteration: left still == mid → same mid → infinite loop!

  Example: left=3, right=4
    mid = 3 + (4-3)/2 = 3
    nums[3] != target → left = mid = 3
    → left=3, right=4 again → same state → infinite loop! ❌

✅ left = mid + 1:
  mid itself is already checked and eliminated.
  Move past it. Progress guaranteed every iteration. ✓
```

### Binary Search — The Universal Template

```
This exact template applies far beyond simple search:
  → Find first/last occurrence of target
  → Find minimum in rotated sorted array
  → Search in 2D sorted matrix
  → Find square root (binary search on answer)
  → Capacity problems ("minimum max" / "maximum min")

The skeleton never changes:
  left = 0, right = n-1
  while (left <= right):
    mid = left + (right - left) / 2
    if condition: return or adjust
    elif go_right: left = mid + 1
    else: right = mid - 1

Master this. It's one of the most versatile tools in DSA.
```

---

## References

- 🔗 [LeetCode Problem — Binary Search](https://leetcode.com/problems/binary-search/)
- 🔗 [Binary Search](https://leetcode.com/problems/binary-search/)
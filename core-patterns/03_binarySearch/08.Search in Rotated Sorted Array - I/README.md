# Search in Rotated Sorted Array - I

## Problem Link
🔗 [LeetCode 33 — Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)

---

## What is this Problem?

A **sorted** array of **distinct** values was rotated at some unknown pivot. Given the rotated array and a `target`, return the **index** of the target, or `-1` if it is not present. Must run in **O(log n)**.

```
nums=[4,5,6,7,0,1,2], target=0
Output: 4

nums=[4,5,6,7,0,1,2], target=3
Output: -1

nums=[1], target=0
Output: -1
```

The array looks like two sorted pieces glued together:

```
[4, 5, 6, 7, 0, 1, 2]
 └── sorted ──┘ └sorted┘
        ↑ pivot between 7 and 0
```

---

## The Idea

```
Plain binary search needs the WHOLE array sorted. Here only PART of it is.

But on every step, split at mid → ONE of the two halves is ALWAYS sorted:
  - either nums[low..mid] is sorted
  - or     nums[mid..high] is sorted

So:
  1. Find which half is sorted.
  2. Check whether target lies INSIDE that sorted half (simple range test).
  3. Yes → go into that half.  No → go into the other half.

This is still ordinary binary search — the range check just tells us
which side the target can possibly be on.
```

```
nums=[4,5,6,7,0,1,2], low=0, high=6, mid=3

nums[0]=4 <= nums[3]=7  → LEFT half [4,5,6,7] is sorted
  target in [4..7]? → search left   else → search right
```

---

## Code Full Solution

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() - 1;

        while(low <= high) {
            int mid = low + (high - low) / 2;

            if(nums[mid] == target) return mid;

            if(nums[low] <= nums[mid]) {
                if(target <= nums[mid] && target >= nums[low]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            } else {
                if(target >= nums[mid] && target <= nums[high]) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }
        return -1;
    }
};
```

---

## Code Explanation

### `nums[low] <= nums[mid]` — Which Half Is Sorted?

```cpp
if(nums[low] <= nums[mid])
```

If the first element is not bigger than the middle one, the rotation point is **not** inside `[low..mid]`, so the **left half is sorted**. Otherwise the rotation point is inside the left half, meaning the **right half** `[mid..high]` is sorted.

### Left Half Sorted — Range Check Inside It

```cpp
if(target <= nums[mid] && target >= nums[low]) high = mid - 1;
else                                          low  = mid + 1;
```

`nums[low..mid]` is sorted, so a single range test says whether the target is in it. Inside → discard the right half (`high = mid - 1`). Outside → it must be in the unsorted right half.

### Right Half Sorted — Range Check Inside It

```cpp
if(target >= nums[mid] && target <= nums[high]) low  = mid + 1;
else                                           high = mid - 1;
```

Same logic mirrored: if the target is inside the sorted right half, go right, else go left.

### `mid = low + (high - low) / 2`

```cpp
int mid = low + (high - low) / 2;
```

Overflow-safe midpoint. `(low + high) / 2` can overflow for large indices — this form cannot.

---

## Full Trace: `nums=[4,5,6,7,0,1,2], target=0`

```
low=0, high=6

mid=3: nums[3]=7 ≠ 0
       nums[0]=4 <= nums[3]=7 → LEFT sorted [4,5,6,7]
       target=0 in [4..7]? NO → low = 4

low=4, high=6

mid=5: nums[5]=1 ≠ 0
       nums[4]=0 <= nums[5]=1 → LEFT sorted [0,1]
       target=0 in [0..1]? YES → high = 4

low=4, high=4

mid=4: nums[4]=0 == target → return 4 ✓
```

## Full Trace: `nums=[6,7,0,1,2,4,5], target=4`

```
low=0, high=6

mid=3: nums[3]=1 ≠ 4
       nums[0]=6 <= nums[3]=1? NO → RIGHT sorted [1,2,4,5]
       target=4 in [nums[3]..nums[6]] = [1..5]? YES → low = 4

low=4, high=6

mid=5: nums[5]=4 == target → return 5 ✓
```

---

## Example Traces

### Target Present on the Sorted Left

```
nums=[4,5,6,7,0,1,2], target=6
mid=3 (7): left sorted [4..7], 6 in range → high=2
mid=1 (5): left sorted [4,5],   6 not in range → low=2
mid=2 (6): == target → return 2 ✓
```

### Array Not Rotated At All

```
nums=[1,2,3,4,5], target=4
Every step takes the "left sorted" branch, which is true for the whole array.
mid=2 (3): 4 not in [1..3] → low=3
mid=3 (4): == target → return 3 ✓
Ordinary binary search is just the special case with no rotation.
```

### Single Element

```
nums=[1], target=1 → mid=0, == target → return 0 ✓
nums=[1], target=0 → mid=0, ≠; nums[0] <= nums[0] true, 0 not in [1..1] → low=1
                     low > high → return -1 ✓
```

---

## Edge Cases

### Target Smaller Than Everything

```
nums=[4,5,6,7,0,1,2], target=-1
Target fails every range test, low/high cross, loop exits → -1 ✓
```

### `low == mid` (half of size 1)

```
nums[low] <= nums[mid] is trivially true (same element).
The left "sorted" branch is taken, the range test is against a single value,
and low/high still move by one → no infinite loop ✓
```

### Duplicates Would Break This

```
nums=[3,1,3,3,3], target=1   (LeetCode 81)

mid=2: nums[2]=3 ≠ 1
nums[low]=3 <= nums[mid]=3 → "left sorted" [3,1] ← WRONG, not sorted
        1 in [3..3]? NO → low=3 → the 1 at index 1 is skipped forever ✗

This is exactly why "- I" requires DISTINCT values.
With duplicates you cannot tell the halves apart → use the "- II"
version, which shrinks both ends when nums[low]==nums[mid]==nums[high].
```

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(log n) — one half is discarded every iteration |
| Space | O(1) — no extra array or recursion |

---

## Key Insight

```
Binary search does not require the whole array to be sorted —
it only requires that you can decide, in O(1), which half the answer is in.

The rotation guarantees one half is always fully sorted,
and a sorted half is exactly the thing a range test can rule in or out.

So each step is:
  which half is sorted?  →  is target inside it?  →  keep that half, drop the other.
```

---

## References

- 🔗 [LeetCode 33 — Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)
- 🔗 [LeetCode 81 — Search in Rotated Sorted Array II](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/) (duplicates allowed)

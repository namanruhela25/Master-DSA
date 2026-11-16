# Search in Rotated Sorted Array - II

## Problem Link
🔗 [LeetCode 81 — Search in Rotated Sorted Array II](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/)

---

## What is this Problem?

A **sorted** array was rotated at some unknown pivot, and it **may contain duplicates**. Given the rotated array and a `target`, return `true` if the target exists, otherwise `false`.

```
nums=[2,5,6,0,0,1,2], target=0
Output: true

nums=[2,5,6,0,0,1,2], target=3
Output: false
```

Same as "Search in Rotated Sorted Array - I", except the values are **not distinct** — and that one extra permission breaks the clean version.

---

## The Idea

```
In "- I" we asked: which half is sorted? A simple comparison decided it.

With duplicates, that question sometimes has NO answer:
  nums = [1, 0, 1, 1, 1]     low=0, high=4, mid=2
  nums[low]=1, nums[mid]=1, nums[high]=1

  nums[low] <= nums[mid] is true → the code would claim [1,0] is "sorted"
  — it is not. The rotation is hiding inside the left half.

  All three values being equal gives zero information about where to go.

Fix:
  Detect that dead end (nums[low] == nums[mid] == nums[high]).
  Those two ends CANNOT be the target (they equal nums[mid], and nums[mid]
  was already checked and was not the target).
  → throw both ends away: low++, high--, and try again.

Everything else stays identical to "- I".
```

```
nums=[1,0,1,1,1], target=0

  mid=2: 1 ≠ 0, and nums[0]==nums[2]==nums[4]==1 → strip both ends
         low=1, high=3        remaining: [0,1,1]
  mid=2: 1 ≠ 0, nums[1]=0 <= nums[2]=1 → LEFT half [0,1] is sorted
         target 0 in [0..1]? YES → high=1
  mid=1: nums[1]=0 == target → true ✓
```

---

## Code Full Solution

```cpp
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() - 1;

        while(low <= high) {
            int mid = low + (high - low) / 2;

            if(nums[mid] == target) return true;

            // can't decide which side to go → strip both ends, skip this round
            // example - 1 0 1 1 1 , target = 0
            if(nums[mid] == nums[low] && nums[mid] == nums[high]) {
                low = low + 1;
                high = high - 1;
                continue;
            }

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
        return false;
    }
};
```

---

## Code Explanation

### Match Check Comes First

```cpp
if(nums[mid] == target) return true;
```

Check `mid` before anything else. This also makes the shrink branch below safe, because it guarantees `nums[mid]` is **not** the answer.

### The Ambiguous Case

```cpp
if(nums[mid] == nums[low] && nums[mid] == nums[high]) {
    low = low + 1;
    high = high - 1;
    continue;
}
```

All three pointer values are equal, so no comparison can tell us which half is sorted. Since neither end can be the target (`nums[low] == nums[high] == nums[mid] ≠ target`), discarding both ends loses nothing.

`continue` matters: it skips the sorted-half logic for this round, because that logic would be operating on stale/meaningless information for `mid`.

### Sorted-Half Logic

```cpp
if(nums[low] <= nums[mid]) { ... }   // left half sorted
else                        { ... }   // right half sorted
```

Identical to "- I". Once the duplicate dead end is removed, one half is genuinely sorted again and the range test picks the side.

### `mid = low + (high - low) / 2`

Overflow-safe midpoint, same as before.

---

## Full Trace: `nums=[2,5,6,0,0,1,2], target=3` (false)

```
low=0, high=6

mid=3: nums[3]=0 ≠ 3
       nums[0]=2, nums[3]=0, nums[6]=2 → NOT all equal
       nums[0]=2 <= nums[3]=0? NO → right half sorted [0,0,1,2]
       3 in [nums[3]..nums[6]] = [0..2]? NO → high = 2

low=0, high=2

mid=1: nums[1]=5 ≠ 3
       nums[0]=2, nums[1]=5, nums[2]=6 → NOT all equal
       nums[0]=2 <= nums[1]=5 → left half sorted [2,5]
       3 in [2..5]? YES → high = 0

low=0, high=0

mid=0: nums[0]=2 ≠ 3
       nums[0]==nums[0]==nums[0] → trivially equal → low=1, high=-1, continue

low=1 > high=-1 → EXIT → return false ✓
```

## Full Trace: `nums=[1,0,1,1,1], target=0` (true)

```
low=0, high=4

mid=2: nums[2]=1 ≠ 0
       nums[0]=1, nums[2]=1, nums[4]=1 → ALL EQUAL → low=1, high=3, continue

low=1, high=3

mid=2: nums[2]=1 ≠ 0
       nums[1]=0, nums[2]=1, nums[3]=1 → not all equal
       nums[1]=0 <= nums[2]=1 → left half [0,1] sorted
       0 in [0..1]? YES → high = 1

low=1, high=1

mid=1: nums[1]=0 == target → return true ✓
```

---

## Edge Cases

### Target Present Multiple Times

Works — the first match returns `true` immediately, no need to find a specific copy.

### All Elements Identical

```
nums=[7,7,7,7], target=7 → mid matches on the first step → true ✓
nums=[7,7,7,7], target=5 → shrink branch fires repeatedly, window empties → false ✓
```

The shrink is what makes this terminate: `low` and `high` move toward each other every round, so the loop can never stall.

### Window of Size 1

```
low == high == mid → the equality test is trivially true,
so the round just shrinks to an empty window and exits. Harmless ✓
```

### Target Smaller / Larger Than Everything

Every range test fails, the window collapses, `false` is returned ✓

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(n) worst case, O(log n) typical |
| Space | O(1) |

```
The shrink branch retires only 2 elements per iteration.
Adversarial input like [1,1,1,...,1,0,1,1,...] can force O(n) shrinks
before the rotation point is even visible.
"- I" (distinct values) was strictly O(log n) — duplicates cost that guarantee.
```

---

## Key Insight

```
Duplicates break binary search's core assumption: "a comparison tells me the side".

When nums[low] == nums[mid] == nums[high], the comparison carries no information.
The only honest move is to give up on those two ends and retry — they are provably
not the answer, because they are equal to an element already ruled out.

So the algorithm degrades from O(log n) to O(n) only for the ambiguous stretches,
never silently returning a wrong answer.
```

---

## References

- 🔗 [LeetCode 81 — Search in Rotated Sorted Array II](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/)
- 🔗 [LeetCode 33 — Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/) (distinct values)

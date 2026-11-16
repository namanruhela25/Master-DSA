# Find Minimum in Rotated Sorted Array

## Problem Link
🔗 [LeetCode 153 — Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/)

---

## What is this Problem?

A **sorted** array of **distinct** values was rotated between 1 and n times. Return its **minimum** element. Must run in **O(log n)**.

```
nums=[3,4,5,1,2]  → Output: 1
nums=[4,5,6,7,0,1,2] → Output: 0
nums=[11,13,15,17] (not rotated) → Output: 11
```

The array is two ascending runs, and the answer is the **first element of the second run**:

```
[4, 5, 6, 7, 0, 1, 2]
 └ sorted ┘ └ sorted ┘
             ↑ the minimum, exactly where the array "drops"
```

---

## The Idea

```
Never search for the minimum directly. Instead, at every step:

  if nums[low] <= nums[mid]   →  [low..mid] is one ascending run
                                 its smallest member is nums[low]  → record it
                                 everything else in it is bigger  → throw the run away
                                 low = mid + 1

  else                        →  the drop is INSIDE [low..mid]
                                 nums[mid] belongs to the second run
                                 so it is a candidate               → record it
                                 answer lies in [low..mid]          → high = mid - 1
```

Key mental model:

```
The minimum is the only element whose LEFT neighbour is bigger than it.
Binary search is used here to find WHERE THE DROP IS, not to compare with a target.
```

---

## Code Full Solution

```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        int low = 0;
        int high = nums.size() - 1;
        int ans = INT_MAX;

        while(low <= high) {
            int mid = low + (high - low) / 2;

            if(nums[low] <= nums[mid]) {
                ans = min(ans, nums[low]);
                low = mid + 1;
                // why low = mid + 1 ?
                // it is a sorted array, nums[low] is the smallest here,
                // everything to its right up to mid is already greater.
                // So skip them all and shift to the right part.
            } else {
                ans = min(ans, nums[mid]);
                high = mid - 1;
            }
        }
        return ans;
    }
};
```

---

## Code Explanation

### `nums[low] <= nums[mid]` — Is This Window's Left Half Ascending?

```cpp
if(nums[low] <= nums[mid])
```

If the first element is not bigger than the middle, the rotation point is not inside `[low..mid]`, so that slice is a clean ascending run.

### Left Slice Ascending → Record `nums[low]`, Skip the Slice

```cpp
ans = min(ans, nums[low]);
low = mid + 1;
```

`nums[low]` is the **smallest** value in `[low..mid]` (it is an ascending run). Every other element there is larger, so the only thing worth keeping from that slice is `nums[low]`. Then jump past the whole slice to `mid + 1`.

### Otherwise the Drop Is Inside → Record `nums[mid]`, Go Left

```cpp
ans = min(ans, nums[mid]);
high = mid - 1;
```

Here `nums[mid] < nums[low]`, which means `mid` is already in the **second run**. `nums[mid]` is therefore a real candidate for the minimum, and the drop can only be at `mid` or to its left → `high = mid - 1`.

### Why Collect `ans` Instead of Returning Immediately?

```cpp
int ans = INT_MAX;
```

The minimum may be found on any iteration. Keeping a running `ans` means the code never has to prove it found the exact drop index — it just shrinks the window and keeps the best value seen.

---

## Full Trace: `nums=[4,5,6,7,0,1,2]`

```
low=0, high=6

mid=3: nums[0]=4 <= nums[3]=7 → left slice [4,5,6,7] ascending
       ans = min(INF, 4) = 4
       low = 4                     (skip 4..7, all ≥ 4)

low=4, high=6

mid=5: nums[4]=0 <= nums[5]=1 → left slice [0,1] ascending
       ans = min(4, 0) = 0
       low = 6

low=6, high=6

mid=6: nums[6]=2 <= nums[6]=2 → trivially ascending (single element)
       ans = min(0, 2) = 0
       low = 7

low=7 > high=6 → EXIT → return 0 ✓
```

## Full Trace: `nums=[3,4,5,1,2]`

```
low=0, high=4

mid=2: nums[0]=3 <= nums[2]=5 → ascending [3,4,5]
       ans=3, low=3

low=3, high=4

mid=3: nums[3]=1 <= nums[3]=1 → single element, ascending
       ans=min(3,1)=1, low=4

low=4, high=4

mid=4: nums[4]=2 <= nums[4]=2 → ans=min(1,2)=1, low=5

low=5 > high=4 → EXIT → return 1 ✓
```

---

## Example Traces

### Not Rotated At All

```
nums=[11,13,15,17]
mid=1 (13): nums[0]=11 <= 13 → ans=11, low=2
mid=3 (17): nums[2]=15 <= 17 → ans=min(11,15)=11, low=4
EXIT → 11 ✓   (ans was already correct after the first step)
```

### Rotation Point at the Very End

```
nums=[2,3,4,5,1]
mid=2 (4): 2 <= 4 → ans=2, low=3
mid=3 (5): 1? nums[3]=5 <= nums[3]=5 → ans=min(2,5)=2, low=4
mid=4 (1): ans=min(2,1)=1, low=5 → EXIT → 1 ✓
```

### Two Elements

```
nums=[2,1] → mid=0: nums[0]=2 <= 2 → ans=2, low=1
             mid=1: nums[1]=1 <= 1 → ans=1 → return 1 ✓
nums=[1,2] → mid=0: 1 <= 1 → ans=1, low=1
             mid=1: 2 <= 2 → ans=min(1,2)=1 → return 1 ✓
```

### Single Element

```
nums=[5] → mid=0: ans=min(INF,5)=5, low=1 → EXIT → 5 ✓
```

---

## Edge Cases

### Duplicates Are NOT Handled

```
nums=[10,1,10,10,10]   (this is LeetCode 154, not 153)

mid=2: nums[0]=10 <= nums[2]=10 → "ascending" [10,1,10] ← WRONG
       ans=10, low=3
mid=3: nums[3]=10 <= 10 → ans=10, low=4
mid=4: ans=10, low=5 → EXIT → returns 10 ✗   (real answer: 1)

nums[low] == nums[mid] can mean either "no drop here" or "drop hidden in
identical values". With duplicates the branch becomes ambiguous, which is
exactly what LeetCode 154 adds: shrink both ends when the comparison ties.
```

### Entirely Equal Values

```
nums=[7,7,7] → every slice looks ascending, ans stays 7 → 7 ✓
```

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(log n) — half the window is discarded every iteration |
| Space | O(1) — a couple of scalars |

---

## Key Insight

```
Don't search for a value — search for the DISCONTINUITY.

Every slice you look at is either fully ascending (then its first element is
its own minimum, and you can skip the whole thing) or contains the drop
(then mid is already past the drop and worth recording).

That single test, nums[low] <= nums[mid], is all binary search needs here.
```

---

## References

- 🔗 [LeetCode 153 — Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/)
- 🔗 [LeetCode 154 — Find Minimum in Rotated Sorted Array II](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/) (duplicates allowed)

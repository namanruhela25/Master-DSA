# Find How Many Times Array Is Rotated

## Problem Link
🔗 [GFG — Rotation (Find Kth Rotation)](https://www.geeksforgeeks.org/problems/rotation4723/1)

---

## What is this Problem?

A **sorted** array of **distinct** values was rotated at some pivot. Return **how many positions** it was rotated — i.e. the index of the smallest element. Must run in **O(log n)**.

```
nums=[5,1,2,3,4]        → Output: 1
nums=[4,5,6,7,0,1,2]    → Output: 4
nums=[1,2,3,4,5]        → Output: 0   (not rotated)
```

```
Original: [0,1,2,3,4]  rotated 3 times →  [3,4,0,1,2]
                                                ↑ index 2
                          rotation count = 2 = index of the minimum
```

---

## The Idea

```
Rotation count  ==  index of the minimum element.

Why: rotating k times moves the smallest element from index 0 to index k.
So this is "Find Minimum in Rotated Sorted Array", except we return the
INDEX of the minimum instead of its value.

  Track BOTH:
    ans   = smallest value seen so far
    index = where that value lived

  Each step, look at the sorted slice and ask: is its first element
  smaller than anything recorded before? If yes, record that position.
```

```
[4, 5, 6, 7, 0, 1, 2]
 └ sorted ┘ └ sorted ┘
             ↑ minimum at index 4  →  rotated 4 times
```

---

## Code Full Solution

```cpp
class Solution {
  public:
    int findKRotation(vector<int> &nums) {
        int low = 0;
        int high = nums.size() - 1;
        int ans = INT_MAX;
        int index = 0;

        while(low <= high) {
            int mid = low + (high - low) / 2;

            // this piece of code is not needed but makes the algo faster
            if(nums[low] <= nums[high]) {
                if(nums[low] < ans) {
                    index = low;
                    ans = nums[low];
                }
            }
            // ---------------------------------------------------

            if(nums[low] <= nums[mid]) {
                if(nums[low] < ans) {
                    ans = nums[low];
                    index = low;
                }
                low = mid + 1;
            } else {
                if(nums[mid] < ans) {
                    ans = nums[mid];
                    index = mid;
                }
                high = mid - 1;
            }
        }
        return index;
    }
};
```

---

## Code Explanation

### Two Things Tracked

```cpp
int ans = INT_MAX;   // smallest value seen
int index = 0;       // where it was found
```

The answer is not the value but the **position**, so every time a new minimum is found both must be updated together.

### The Optional Fast Path

```cpp
if(nums[low] <= nums[high]) {
    if(nums[low] < ans) { index = low; ans = nums[low]; }
}
```

If `nums[low] <= nums[high]`, the **whole remaining window is already sorted** (the drop is not inside it), so its minimum is `nums[low]` at index `low`. Recording it means the window's best candidate is known.

> It earns its comment: it saves a few iterations, but as written it has **no `break`**, so the loop still walks down to an empty window instead of stopping. Adding `break;` right after recording would make this case O(1) — the same result, fewer steps.

### Left Slice Ascending

```cpp
if(nums[low] <= nums[mid]) {
    if(nums[low] < ans) { ans = nums[low]; index = low; }
    low = mid + 1;
}
```

`[low..mid]` is one ascending run, so its smallest member is `nums[low]`. Record it if it beats the current best, then skip the whole slice.

### Drop Inside the Left Slice

```cpp
} else {
    if(nums[mid] < ans) { ans = nums[mid]; index = mid; }
    high = mid - 1;
}
```

`nums[mid] < nums[low]` means `mid` is in the second run, so it is a genuine candidate; the answer is at `mid` or further left.

### Why `index` Starts at 0

If nothing ever beats `INT_MAX`… it always does, but starting `index = 0` also makes the non-rotated array fall out correctly (index 0 is recorded on the first step).

---

## Full Trace: `nums=[4,5,6,7,0,1,2]`

```
low=0, high=6, ans=INF, index=0

fast path: nums[0]=4 <= nums[6]=2? NO
mid=3: nums[0]=4 <= nums[3]=7 → ascending [4,5,6,7]
       4 < INF → ans=4, index=0
       low=4

low=4, high=6

fast path: nums[4]=0 <= nums[6]=2? YES → 0 < 4 → ans=0, index=4
mid=5: nums[4]=0 <= nums[5]=1 → ascending [0,1]
       0 < 0? NO (already have the minimum) → index stays 4
       low=6

low=6, high=6

fast path: nums[6]=2 <= nums[6]=2? YES → 2 < 0? NO
mid=6: 2 < 0? NO
       low=7

low=7 > high=6 → EXIT → return index = 4 ✓  (minimum is 0 at index 4)
```

---

## Example Traces

### Rotated Once

```
nums=[5,1,2,3,4]   → expected 1

low=0, high=4
fast: nums[0]=5 <= nums[4]=4? NO
mid=2: nums[0]=5 <= nums[2]=2? NO → drop inside [0..2]
       nums[2]=2 < INF → ans=2, index=2
       high=1

low=0, high=1
fast: nums[0]=5 <= nums[1]=1? NO
mid=0: nums[0]=5 <= nums[0]=5 → 5 < 2? NO
       low=1

low=1, high=1
fast: nums[1]=1 <= nums[1]=1 → 1 < 2 → ans=1, index=1
mid=1: 1 < 1? NO → low=2

EXIT → 1 ✓
```

### Not Rotated

```
nums=[1,2,3,4,5]   → expected 0

low=0, high=4
fast: nums[0]=1 <= nums[4]=5 → ans=1, index=0        ← answer locked in already
mid=2: nums[0]=1 <= nums[2]=3 → 1 < 1? NO → low=3
low=3, high=4
fast: nums[3]=4 <= nums[4]=5 → 4 < 1? NO
mid=3: 4 < 1? NO → low=4
mid=4: 5 < 1? NO → low=5

EXIT → 0 ✓
```

### Single Element

```
nums=[9] → fast: 9 <= 9 → ans=9, index=0
            mid=0: 9 < 9? NO → low=1 → EXIT → 0 ✓
```

---

## Edge Cases

### Minimum At Index 0 (No Rotation)

Handled — the first fast-path/left-slice step records index 0 and nothing ever beats it ✓

### Minimum At the Last Index (Rotated n-1 times)

```
nums=[2,3,4,5,1] → 4
mid=2: nums[0]=2 <= nums[2]=4 → ans=2, index=0; low=3
low=3, high=4: fast: nums[3]=5 <= nums[4]=1? NO
mid=3: nums[3]=5 <= nums[4]... nums[3]=5 <= nums[3]=5 → 5 < 2? NO; low=4
low=4, high=4: fast: nums[4]=1 <= nums[4]=1 → 1 < 2 → ans=1, index=4
mid=4: 1 < 1? NO. EXIT → 4 ✓
```

### Duplicates

Distinct values are assumed (like LeetCode 153). With repeats, `nums[low] <= nums[mid]` becomes ambiguous and `index` can point at the wrong copy — that variant needs the shrink-both-ends step from "Search in Rotated Sorted Array - II".

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(log n) — window halves each iteration |
| Space | O(1) |

---

## Key Insight

```
"Rotation count" and "index of the minimum" are the same question in disguise.

So don't write a new algorithm. Take the minimum-finding binary search and
carry the index alongside the value. Whenever the running minimum is replaced,
the index is replaced with it — two variables, one condition.
```

---

## References

- 🔗 [GFG — Rotation](https://www.geeksforgeeks.org/problems/rotation4723/1)
- 🔗 [LeetCode 153 — Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/)

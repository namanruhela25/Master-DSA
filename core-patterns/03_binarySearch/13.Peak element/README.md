# Find Peak Element

## Problem Link
🔗 [LeetCode 162 — Find Peak Element](https://leetcode.com/problems/find-peak-element/)

---

## What is this Problem?

Given an array where **no two adjacent elements are equal**, a **peak** is an element strictly greater than both neighbours. Return the **index of any** peak. Must run in **O(log n)**.

```
nums=[1,2,3,1]      → Output: 2   (3 > 2 and 3 > 1)
nums=[1,2,1,3,5,6,4] → Output: 5   (6 > 5 and 6 > 4)
```

The ends count as peaks by treating the outside as `-∞`:

```
nums=[3,1,2]  → index 0 is a peak (3 > -∞ and 3 > 1)
nums=[1,2,4]  → index 2 is a peak (4 > 2 and 4 > -∞)
```

Because `-∞` sits at both ends, **at least one peak always exists** — the array must climb from `-∞` and eventually come back down.

---

## The Idea

```
Don't look for THE peak — a mountain range can have many.

Look only at the SLOPE at mid:
  nums[mid] < nums[mid+1]   →  climbing ↑  →  a peak must exist to the RIGHT
  nums[mid] > nums[mid+1]   →  falling ↓  →  a peak must exist to the LEFT  (or mid itself)

Why the guarantee? The right wall of the array is a -∞ cliff.
If you are climbing, you cannot keep climbing forever — you must turn down
(or end) somewhere to the right. That turn is a peak.

Same argument mirrored for the falling case.

So follow the slope upward: it is a hill-climb, done by binary search.
```

```
nums=[1,2,1,3,5,6,4]

         6
       5   4
     3
   2
 1
      mid here: 3 < 5 → climbing → go RIGHT → finds 6
```

---

## Code Full Solution

```cpp
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return 0;
        if(nums[0] > nums[1]) return 0;
        if(nums[n-1] > nums[n-2]) return n-1;

        int low = 1;
        int high = n - 2;

        while(low <= high) {
            int mid = low + (high - low) / 2;

            if((nums[mid] > nums[mid-1]) && (nums[mid] > nums[mid+1])) return mid;

            if(nums[mid] < nums[mid+1]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return -1;
    }
};
```

---

## Code Explanation

### Handle the Ends Up Front

```cpp
if(n == 1) return 0;
if(nums[0] > nums[1]) return 0;
if(nums[n-1] > nums[n-2]) return n-1;
```

`n == 1` — the only element is the peak (both sides are `-∞`).  
`nums[0] > nums[1]` — the array starts by falling, so index 0 is a peak.  
`nums[n-1] > nums[n-2]` — the array ends by rising, so the last index is a peak.

These three lines let the loop treat the array as the **strict interior** `[1, n-2]`, where `nums[mid-1]` and `nums[mid+1]` always exist — no boundary conditions inside the loop.

### The Peak Test

```cpp
if((nums[mid] > nums[mid-1]) && (nums[mid] > nums[mid+1])) return mid;
```

Up on the left and down on the right → `mid` is a peak, return immediately. Any peak is accepted, so there is no need to keep searching.

### Climb the Slope

```cpp
if(nums[mid] < nums[mid+1]) low = mid + 1;
else                        high = mid - 1;
```

Since `mid` is not a peak (checked above), one of the two neighbours is bigger:

- `nums[mid] < nums[mid+1]` → rising to the right → a turn-down must exist somewhere right of `mid` → discard the left.
- otherwise `nums[mid] > nums[mid+1]` → falling to the right, and since `mid` isn't a peak, `nums[mid] < nums[mid-1]` → a turn-up must exist left of `mid` → discard `mid` and beyond.

### `mid = low + (high - low) / 2`

Overflow-safe midpoint.

### `return -1` Is Unreachable

A peak is guaranteed to exist, and the loop always moves toward one, so the fallback never fires. It only keeps the compiler happy.

---

## Full Trace: `nums=[1,2,3,1]`

```
n=4
nums[0]=1 > nums[1]=2?  NO
nums[3]=1 > nums[2]=3?  NO

low=1, high=2

mid=1: nums[1]=2
       nums[1] > nums[0] (2 > 1) ✓ but nums[1] > nums[2] (2 > 3)? NO
       → not a peak
       nums[1] < nums[2] (2 < 3) → climbing → low = 2

low=2, high=2

mid=2: nums[2]=3
       nums[2] > nums[1] (3 > 2) ✓ and nums[2] > nums[3] (3 > 1) ✓
       → return 2 ✓
```

## Full Trace: `nums=[1,2,1,3,5,6,4]`

```
n=7
nums[0]=1 > nums[1]=2?  NO
nums[6]=4 > nums[5]=6?  NO

low=1, high=5

mid=3: nums[3]=3
       3 > nums[2]=1 ✓ but 3 > nums[4]=5? NO → not a peak
       3 < 5 → climbing → low = 4

low=4, high=5

mid=4: nums[4]=5
       5 > nums[3]=3 ✓ but 5 > nums[5]=6? NO → not a peak
       5 < 6 → climbing → low = 5

low=5, high=5

mid=5: nums[5]=6
       6 > nums[4]=5 ✓ and 6 > nums[6]=4 ✓
       → return 5 ✓
```

---

## Example Traces

### Peak at the Start

```
nums=[3,1,2] → nums[0]=3 > nums[1]=1 → return 0 ✓
```

### Peak at the End

```
nums=[1,2,4] → nums[2]=4 > nums[1]=2 → return 2 ✓
```

### Strictly Increasing

```
nums=[1,2,3,4] → nums[3]=4 > nums[2]=3 → return 3 ✓
The -∞ cliff at the right end makes the last element the peak.
```

### Strictly Decreasing

```
nums=[4,3,2,1] → nums[0]=4 > nums[1]=3 → return 0 ✓
```

### Two Elements

```
nums=[2,1] → nums[0]=2 > nums[1]=1 → return 0 ✓
nums=[1,2] → nums[0] > nums[1]? NO; nums[1]=2 > nums[0]=1 → return 1 ✓
The loop range [1, 0] is empty here — the end checks already answered.
```

### Single Element

```
nums=[7] → n==1 → return 0 ✓
```

### Multiple Peaks — Any Is Accepted

```
nums=[1,3,2,4,1]

low=1, high=3
mid=2: nums[2]=2; 2 > nums[1]=3? NO → not a peak
       2 < nums[3]=4 → climbing → low=3
mid=3: nums[3]=4; 4 > nums[2]=2 ✓ and 4 > nums[4]=1 ✓ → return 3

Index 3 is a valid peak (index 1 also is). The problem accepts either ✓
```

---

## Edge Cases

### Alternating Up-Down

```
nums=[1,5,1,5,1] → low=1, high=3
mid=2 (1): not a peak, 1 < nums[3]=5 → low=3
mid=3 (5): 5 > nums[2]=1 and 5 > nums[4]=1 → return 3 ✓
(index 1 is also a peak — either answer is accepted)
```

### Equal Neighbours Are Excluded by the Constraints

```
LeetCode 162 guarantees nums[i] != nums[i+1].
If equal neighbours were allowed, nums[mid] could be equal to nums[mid+1],
neither < nor > would hold, and the else-branch would silently treat it
as "descending" — an arbitrary but still terminating choice.
```

### Returning a Peak That Is Not the Global Maximum

Fine. The problem asks for **a** peak, not the highest one. This binary search finds one in O(log n) without ever scanning the whole array.

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(log n) — half the array is discarded each step |
| Space | O(1) |

```
Linear alternative: walk left to right, return the first i where
nums[i] > nums[i+1] (or n-1). O(n) time, O(1) space.

The binary version wins because the slope comparison gives a GUARANTEE
about which side a peak lives on — that is what makes halving valid.
```

---

## Key Insight

```
A guaranteed peak + a local slope test = searchable direction.

At any mid there are only two possibilities, and both tell you where to go:
  climbing → the -∞ wall forces a turn-down to the right
  falling  → the -∞ wall forces a turn-up to the left

So binary search works on an UNSORTED array here, because the invariant
being halved is "this interval contains a peak", not "this interval is sorted".
```

---

## References

- 🔗 [LeetCode 162 — Find Peak Element](https://leetcode.com/problems/find-peak-element/)
- 🔗 [LeetCode 1901 — Find a Peak Element II](https://leetcode.com/problems/find-a-peak-element-ii/) (2D version)

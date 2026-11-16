# Search Single Element in a Sorted Array

## Problem Link
🔗 [LeetCode 540 — Single Element in a Sorted Array](https://leetcode.com/problems/single-element-in-a-sorted-array/)

---

## What is this Problem?

A **sorted** array where **every value appears exactly twice, except one value that appears once**. Return that single value. Must run in **O(log n)** with **O(1)** space.

```
nums=[1,1,2,3,3,4,4,8,8]  → Output: 2
nums=[3,3,7,7,10,11,11]   → Output: 10
```

XOR-ing everything gives the answer in O(n) — but the requirement is O(log n), so the sorted order has to be exploited.

---

## The Idea

```
Before the single element, pairs sit at (0,1), (2,3), (4,5), ...
  → every pair STARTS at an EVEN index.

After the single element everything shifts by one, so pairs sit at (1,2), (3,4), ...
  → every pair STARTS at an ODD index.

[1, 1,  2,  3, 3,  4, 4,  8, 8]
 └pair┘  ↑  └pair┘  └pair┘  └pair┘
        single
 idx:  0    2      4      6
 even  ↑          odd ↑ (shifted left by 1)

So: pick mid, look at its partner. Is that pair aligned "even-start"?
   YES → we are still LEFT of the single → move RIGHT
   NO  → we have crossed it          → move LEFT
```

```
Alignment test (either direction works):
  mid is EVEN and nums[mid] == nums[mid+1]   → pair (mid, mid+1) starts even → go RIGHT
  mid is ODD  and nums[mid] == nums[mid-1]   → pair (mid-1, mid) starts even → go RIGHT
  anything else                              → go LEFT
```

---

## Code Full Solution

```cpp
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size();
        if(nums[0] != nums[1]) return nums[0];
        if(nums[n-1] != nums[n-2]) return nums[n-1];

        int low = 1;
        int high = n - 2;

        while(low <= high) {
            int mid = low + (high - low) / 2;

            if(nums[mid] != nums[mid-1] && nums[mid] != nums[mid+1]) {
                return nums[mid];
            }

            if((mid % 2 == 0 && nums[mid] == nums[mid+1]) ||
               (mid % 2 == 1 && nums[mid] == nums[mid-1])) {
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

### Handle the Two Ends First

```cpp
if(nums[0] != nums[1]) return nums[0];
if(nums[n-1] != nums[n-2]) return nums[n-1];
```

If the first element has no partner, it is the single one. Same for the last. Doing this up front lets the loop work on the **strict interior** `[1, n-2]`, so `nums[mid-1]` and `nums[mid+1]` are always in bounds — no boundary checks inside the loop.

### The Found Check

```cpp
if(nums[mid] != nums[mid-1] && nums[mid] != nums[mid+1]) return nums[mid];
```

`mid` differs from both neighbours → it is the single element.

### The Parity Test — Which Side Is the Single On?

```cpp
if((mid % 2 == 0 && nums[mid] == nums[mid+1]) ||
   (mid % 2 == 1 && nums[mid] == nums[mid-1])) {
    low = mid + 1;
} else {
    high = mid - 1;
}
```

| Situation | Reading | Move |
|---|---|---|
| `mid` even, `nums[mid] == nums[mid+1]` | pair starts at even index → left part still "normal" | single is right → `low = mid + 1` |
| `mid` odd, `nums[mid] == nums[mid-1]` | partner is `mid-1` (even start) → left part still normal | single is right → `low = mid + 1` |
| otherwise | the pairing pattern is already shifted → single is at or left of `mid` | `high = mid - 1` |

Both branches are the same question asked from a different parity: **does this element's pair begin at an even index?**

### `mid = low + (high - low) / 2`

Overflow-safe midpoint.

---

## Full Trace: `nums=[1,1,2,3,3,4,4,8,8]`

```
n=9
nums[0]=1 == nums[1]=1      → not the first
nums[8]=8 == nums[7]=8      → not the last

low=1, high=7

mid=4: nums[4]=3
       nums[4] == nums[3]? (3 == 3) → YES, not the single
       mid=4 even && nums[4]==nums[5] (3 == 4)? NO
       mid=4 odd? NO
       → neither condition → high = 3

low=1, high=3

mid=2: nums[2]=2
       nums[2] != nums[1] (2 ≠ 1) and nums[2] != nums[3] (2 ≠ 3)
       → return 2 ✓
```

## Full Trace: `nums=[3,3,7,7,10,11,11]`

```
n=7
nums[0]=3 == nums[1]=3     → not the first
nums[6]=11 == nums[5]=11   → not the last

low=1, high=5

mid=3: nums[3]=7
       nums[3] == nums[2] (7 == 7) → paired, not the single
       mid=3 odd && nums[3]==nums[2] → YES → low = 4

low=4, high=5

mid=4: nums[4]=10
       nums[4] != nums[3] (10 ≠ 7) and nums[4] != nums[5] (10 ≠ 11)
       → return 10 ✓
```

---

## Example Traces

### Single Element At the Start

```
nums=[1,2,2,3,3] → nums[0]=1 != nums[1]=2 → return 1 immediately ✓
```

### Single Element At the End

```
nums=[1,1,2,2,3] → nums[0]=1 == nums[1]=1
                   nums[4]=3 != nums[3]=2 → return 3 immediately ✓
```

### Single Element One Step Away

```
nums=[1,1,2,2,3,4,4]   → expected 3

n=7
nums[0]=1 == nums[1]=1     → not the first
nums[6]=4 == nums[5]=4     → not the last

low=1, high=5

mid=3: nums[3]=2 == nums[2]=2 → paired
       mid=3 odd && nums[3]==nums[2] → low = 4

mid=4: nums[4]=3 != nums[3]=2 and != nums[5]=4
       → return 3 ✓
```

### Why the Two End Checks Are Not Optional

The loop searches only `[1, n-2]`. That is safe exactly because the two up-front checks have already returned whenever the single element sits at index `0` or `n-1`:

```
nums=[1,1,2,2,3,3,4]
nums[6]=4 != nums[5]=3 → returns 4 before the loop.
Without that line the loop would scan [1..5] only and fall through to -1 ✗

They also keep the loop bounds legal: inside [1, n-2], both nums[mid-1]
and nums[mid+1] are guaranteed to exist, so no boundary checks are needed.
```

---

## Edge Cases

### `n == 1`

```
nums=[7]
nums[1] → OUT OF BOUNDS READ (UB)
```

> ⚠️ **Bug:** LeetCode 540 allows `1 <= nums.length`, so a single-element array crashes or reads garbage on the first line. A guard `if(n == 1) return nums[0];` fixes it without touching the rest of the logic.

### The Single Element Is the Median of the Search

Returned directly by the found check — no parity reasoning needed ✓

### Pairs Everywhere Except One, Array of Size 3

```
nums=[1,1,2] → nums[0]=1 == nums[1]=1
               nums[2]=2 != nums[1]=1 → return 2 ✓
```

### `nums[mid] == nums[mid-1]` and `nums[mid] == nums[mid+1]` Both

Impossible for a valid input — a value appears at most twice, so `mid` cannot equal both neighbours unless the array is malformed.

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(log n) — one binary search |
| Space | O(1) |

```
Alternative: XOR every element → O(n) time, O(1) space.
The parity trick trades a linear scan for O(log n) by using the sort order,
which XOR throws away.
```

---

## Key Insight

```
The sorted order encodes a POSITION PARITY:

  pairs begin at even indices  →  still before the single
  pairs begin at odd  indices  →  already past it

That single bit of information ("is my pair even-aligned?") is enough to
halve the search space, so the answer needs no value comparisons at all.
```

---

## References

- 🔗 [LeetCode 540 — Single Element in a Sorted Array](https://leetcode.com/problems/single-element-in-a-sorted-array/)

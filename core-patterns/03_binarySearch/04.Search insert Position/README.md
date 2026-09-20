# Search Insert Position

## Problem Link
🔗 [LeetCode 35 — Search Insert Position](https://leetcode.com/problems/search-insert-position/)

> 💡 This is **Lower Bound** in disguise. Returns either the index of the target if found, or where it *would* be inserted to keep the array sorted.

---

## What is this Problem?

Given a sorted array and a target, return the index of the target if it exists. If it doesn't exist, return the index where it **would be inserted** to maintain sorted order.

```
nums=[1,3,5,6], target=5 → Output: 2  (found at index 2)
nums=[1,3,5,6], target=2 → Output: 1  (insert between 1 and 3)
nums=[1,3,5,6], target=7 → Output: 4  (insert at end)
nums=[1,3,5,6], target=0 → Output: 0  (insert at beginning)
```

---

## The Problem Explained

```
Think of it as: "Where would this card go in a sorted deck?"

  Deck:    1   3   5   6
  Insert 2:    ↑
               index 1

  Insert 7:                ↑
                           index 4 (= n, past the end)
```

**Key insight:** This is exactly **Lower Bound** — the first index where `nums[index] >= target`. If the element exists, that's its index. If not, that's where it should go.

---

## HOOK TO REMEMBER FOREVER

**"STANDARD BINARY SEARCH. IF NOT FOUND, `low` IS THE ANSWER."**

- ✅ Normal binary search: found → return `mid`
- ✅ Not found → `low` naturally lands at the correct insertion point
- ✅ O(log n) time, O(1) space

---

## Why `low` is the Insert Position

```
Binary search contracts the window around target's correct position.
When the loop exits (low > high), low and high have crossed:

    high  low
      ↓    ↓
  ... 3 | 5 ...    (looking for 4)
           ↑
           low = insertion point

low always ends up pointing at the FIRST element > target,
which is exactly where target should be inserted.

If target exists: the `if (nums[mid] == target) return mid`
line catches it before we ever need to think about insertion.
```

---

## How It Works Step By Step

### `nums=[1,3,5,6], target=2`

```
low=0, high=3

mid=1: nums[1]=3 > 2 → high=0
mid=0: nums[0]=1 < 2 → low=1
low=1 > high=0 → EXIT

return low=1 ✓  (insert before index 1, which holds 3)
```

### `nums=[1,3,5,6], target=7`

```
low=0, high=3

mid=1: 3<7 → low=2
mid=2: 5<7 → low=3  (wait: mid=low+(high-low)/2=2+(3-2)/2=2)
Actually:
mid=2: nums[2]=5<7 → low=3
mid=3: nums[3]=6<7 → low=4
low=4 > high=3 → EXIT

return low=4 = n ✓ (insert at end)
```

### `nums=[1,3,5,6], target=5`

```
low=0, high=3

mid=1: nums[1]=3<5 → low=2
mid=2: nums[2]=5==5 → return 2 ✓ (found)
```

---

## Code Full Solution

```cpp
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int low = 0, high = nums.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nums[mid] == target) return mid;
            if (nums[mid] < target) low = mid + 1;
            else high = mid - 1;
        }

        return low;
    }
};
```

---

## Edge Cases

### Target Smaller Than All Elements

```
nums=[3,5,7], target=1
All mids: nums[mid]>1 → high shrinks to -1.
Return low=0 ✓ (insert at beginning)
```

### Target Larger Than All Elements

```
nums=[3,5,7], target=9
All mids: nums[mid]<9 → low grows to n=3.
Return low=3 ✓ (insert at end)
```

### Single Element

```
nums=[5], target=3 → low=0, high=0. mid=0. 5>3 → high=-1. Return 0 ✓
nums=[5], target=7 → low=0, high=0. mid=0. 5<7 → low=1. Return 1 ✓
nums=[5], target=5 → found. Return 0 ✓
```

---

## Connection to Lower Bound

```
Lower Bound: first index where nums[index] >= target
Search Insert Position: same thing

  lowerBound([1,3,5,6], 2) = 1  ← index of first element ≥ 2
  searchInsert([1,3,5,6], 2) = 1  ← same answer ✓

The early return for exact match doesn't change the final result —
`low` would end at the same index anyway. The `==` check just
exits early without waiting for the full loop to finish.
```

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(log n) |
| Space | O(1) |

---

## References

- 🔗 [LeetCode 35 — Search Insert Position](https://leetcode.com/problems/search-insert-position/)
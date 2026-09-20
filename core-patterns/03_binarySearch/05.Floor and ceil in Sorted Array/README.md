# Floor and Ceil in Sorted Array

## Problem Link
🔗 [GFG — Floor and Ceil in a Sorted Array](https://www.geeksforgeeks.org/floor-and-ceil-from-a-bst/)

> 💡 This combines **Floor** (largest element ≤ x) and **Ceil** (smallest element ≥ x) into a single binary search pass. If you've read the individual Floor and Upper Bound READMEs, this README only covers what's new: **doing both simultaneously**.

---

## What is this Problem?

Given a sorted array and a value `x`, return `[floor, ceil]`:
- **Floor** = largest element ≤ x (or -1 if none)
- **Ceil** = smallest element ≥ x (or -1 if none)

```
arr=[1,2,8,10,11,12,19], x=5
Output: [2, 8]   → 2 is largest ≤ 5, 8 is smallest ≥ 5

arr=[1,2,8,10], x=8
Output: [8, 8]   → x exists exactly, floor = ceil = x

arr=[3,5,7], x=1
Output: [-1, 3]  → nothing ≤ 1, ceil is 3

arr=[3,5,7], x=9
Output: [7, -1]  → floor is 7, nothing ≥ 9
```

---

## The Key Insight — One Pass, Two Candidates

```
During binary search, every comparison does two things at once:
  arr[mid] < x  → mid is a FLOOR candidate (record it, go right)
  arr[mid] > x  → mid is a CEIL candidate (record it, go left)

At the end, the LAST recorded floor candidate = floor.
The LAST recorded ceil candidate = ceil.

Why "last"?
  Each time we find a floor candidate and go right, we get
  CLOSER to x from below → the most recent one is the LARGEST ≤ x.
  Each time we find a ceil candidate and go left, we get
  CLOSER to x from above → the most recent one is the SMALLEST ≥ x.
```

---

## How It Works Step By Step

### `arr=[1,2,8,10,11,12,19], x=5`

```
low=0, high=6, floorval=-1, ceilval=-1

mid=3: arr[3]=10 > 5 → ceilval=10, high=2
mid=1: arr[1]=2 < 5  → floorval=2, low=2
mid=2: arr[2]=8 > 5  → ceilval=8,  high=1
low=2 > high=1 → EXIT

return [2, 8] ✓

Notice ceilval updated twice: 10 → 8 (got closer to 5 from above).
```

---

## Code Full Solution

```cpp
class Solution {
public:
    vector<int> getFloorAndCeil(int x, vector<int>& arr) {
        sort(arr.begin(), arr.end());

        int low = 0, high = arr.size() - 1;
        int floorval = -1, ceilval = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] == x) return {x, x};

            if (arr[mid] < x) {
                floorval = arr[mid];  // candidate, go right for better
                low = mid + 1;
            } else {
                ceilval = arr[mid];   // candidate, go left for better
                high = mid - 1;
            }
        }

        return {floorval, ceilval};
    }
};
```

---

## Code Explanation

### Early Exit on Exact Match

```cpp
if (arr[mid] == x) return {x, x};
```

If `x` exists in the array, floor = ceil = x. Return immediately — no need to continue.

---

### Floor Candidate — Left Side

```cpp
if (arr[mid] < x) {
    floorval = arr[mid];
    low = mid + 1;
}
```

`arr[mid] < x` → this could be the floor. Save it. But a LARGER value to the right might also be ≤ x and be a better floor, so go right.

---

### Ceil Candidate — Right Side

```cpp
else {
    ceilval = arr[mid];
    high = mid - 1;
}
```

`arr[mid] > x` → this could be the ceil. Save it. But a SMALLER value to the left might also be ≥ x and be a better ceil, so go left.

---

## Complete Example Traces

### Trace 1: x Between Two Elements

```
arr=[1,2,8,10], x=5
(traced above)
return [2, 8] ✓
```

### Trace 2: x Exists in Array

```
arr=[1,2,8,10], x=8

mid=1: arr[1]=2 < 8 → floorval=2, low=2
mid=2: arr[2]=8 == 8 → return {8,8} ✓
```

### Trace 3: x Smaller Than All Elements

```
arr=[3,5,7], x=1

mid=1: arr[1]=5 > 1 → ceilval=5, high=0
mid=0: arr[0]=3 > 1 → ceilval=3, high=-1
EXIT.

return [-1, 3] ✓  (ceilval tracked down to 3, floorval never set)
```

### Trace 4: x Larger Than All Elements

```
arr=[3,5,7], x=9

mid=1: arr[1]=5 < 9 → floorval=5, low=2
mid=2: arr[2]=7 < 9 → floorval=7, low=3
EXIT.

return [7, -1] ✓  (floorval tracked up to 7, ceilval never set)
```

---

## Edge Cases

### All Elements Equal to x

```
arr=[5,5,5], x=5
First mid hits 5 == x → return {5,5} ✓
```

### Single Element

```
arr=[5], x=3 → arr[0]=5>3 → ceilval=5. return [-1,5] ✓
arr=[5], x=7 → arr[0]=5<7 → floorval=5. return [5,-1] ✓
arr=[5], x=5 → exact match → return {5,5} ✓
```

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(n log n) for sort + O(log n) for search |
| Space | O(1) |

> If the array is already sorted, skip the `sort()` call — then it's pure O(log n).

---

## Key Insight — Floor and Ceil as Converging Brackets

```
Before search:    [1 ........ 2 ........ 8 ........ 10]
                               x=5
                  ↑ potential floor         ↑ potential ceil

After each step, the candidates converge toward x:
  Floor candidates move RIGHT (getting larger, closer to x from below)
  Ceil candidates move LEFT  (getting smaller, closer to x from above)

The LAST candidate saved in each direction is the closest to x.
That's why we overwrite, not accumulate — we only care about
the final (closest) candidate in each direction.
```

---

## References

- 🔗 [GFG — Floor and Ceil](https://www.geeksforgeeks.org/floor-and-ceil-from-a-bst/)
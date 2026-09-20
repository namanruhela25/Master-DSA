# Floor in a Sorted Array

## Problem Link
🔗 [GFG — Floor in a Sorted Array](https://www.geeksforgeeks.org/problems/floor-in-a-sorted-array-1587115620/1)

---

## What is this Problem?

Given a sorted array and a value `k`, find the **index of the largest element ≤ k** (the "floor" of k). Return `-1` if no such element exists.

```
arr = [1, 2, 8, 10, 11, 12, 19], k = 5
Output: 1  → arr[1]=2 is the largest element ≤ 5

arr = [1, 2, 8, 10, 11, 12, 19], k = 20
Output: 6  → arr[6]=19 is the largest element ≤ 20

arr = [1, 2, 8, 10, 11, 12, 19], k = 0
Output: -1 → no element ≤ 0
```

---

## The Problem Explained

Think of it like **finding which floor of a building you'd stop at, given you can't go above `k`**:

```
Floors:  1  2  8  10  11  12  19
k = 5

You can go to floor 1, floor 2 — but not floor 8 (too high).
The HIGHEST floor you can reach = floor 2 at index 1.
```

---

## HOOK TO REMEMBER FOREVER

**"IF arr[mid] ≤ k → RECORD IT AS A CANDIDATE, SEARCH RIGHT FOR BETTER. ELSE SEARCH LEFT."**

- ✅ Standard binary search, but instead of finding an exact match, we find the **best candidate so far**
- ✅ When `arr[mid] ≤ k` → `mid` is a valid floor candidate, save it in `ans`, search right (there might be a LARGER valid element)
- ✅ When `arr[mid] > k` → too big, search left
- ✅ Return `ans` (-1 if never updated)
- ✅ O(log n) time, O(1) space

---

## How It Works

### Example: `arr=[1,2,8,10,11,12,19], k=5`

```
low=0, high=6, ans=-1

mid=3: arr[3]=10. 10≤5? NO → high=2

mid=1: arr[1]=2. 2≤5? YES → ans=1, low=2

mid=2: arr[2]=8. 8≤5? NO → high=1

low=2 > high=1 → STOP

Return ans=1  → arr[1]=2 ✓
```

**At every step:** If `arr[mid]` qualifies (≤ k), we record `mid` as the best answer so far, then look RIGHT for an even bigger valid element.

---

## Code Full Solution

```cpp
int findFloor(vector<int>& arr, int k) {
    int low = 0, high = arr.size() - 1;
    int ans = -1;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] <= k) {
            ans = mid;      // valid floor found — record it
            low = mid + 1;  // try to find a larger valid element
        } else {
            high = mid - 1; // too big — go left
        }
    }

    return ans;
}
```

---

## Code Explanation

### `ans = -1` as Default

```
If k is smaller than arr[0], the loop always takes the else branch.
ans never updates. We correctly return -1. ✓
```

### Why `low = mid + 1` When `arr[mid] ≤ k`?

```
arr[mid] ≤ k means mid is a valid floor candidate.
But there might be a LARGER value to the right that's STILL ≤ k.

We want the LARGEST element ≤ k, so we keep the current best
in ans and continue searching right for something better.
```

### Why `high = mid - 1` When `arr[mid] > k`?

```
arr[mid] > k → too big. The floor can't be here or to the right
(array is sorted, everything right is even bigger).
So we discard the right half and look left.
```

---

## Complete Traces

### Trace 1: k Exists in Array

```
arr=[1,2,8,10], k=8

mid=1: arr[1]=2 ≤ 8 → ans=1, low=2
mid=3: arr[3]=10 > 8 → high=2
mid=2: arr[2]=8 ≤ 8 → ans=2, low=3
low>high → STOP

Return 2 → arr[2]=8 ✓
```

### Trace 2: k Greater Than All Elements

```
arr=[1,2,8,10], k=20

mid=1: 2≤20 → ans=1, low=2
mid=3: 10≤20 → ans=3, low=4
low>high → STOP

Return 3 → arr[3]=10 (largest element) ✓
```

### Trace 3: k Smaller Than All Elements

```
arr=[1,2,8,10], k=0

mid=1: 2≤0? NO → high=0
mid=0: 1≤0? NO → high=-1
low>high → STOP

Return -1 ✓
```

---

## Edge Cases

### Case 1: Single Element, k Matches

```
arr=[5], k=5 → mid=0, 5≤5 → ans=0. Return 0 ✓
```

### Case 2: Single Element, k Smaller

```
arr=[5], k=3 → mid=0, 5≤3? NO. Return -1 ✓
```

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(log n) |
| Space | O(1) |

---

## Key Insight — "Record and Search Right" Pattern

This is a classic binary search variant. The pattern:

```
Looking for LAST/LARGEST position satisfying a condition:
  → When condition MET: record ans, search RIGHT (low = mid+1)
  → When condition FAILS: search LEFT (high = mid-1)

Looking for FIRST/SMALLEST position satisfying a condition:
  → When condition MET: record ans, search LEFT (high = mid-1)
  → When condition FAILS: search RIGHT (low = mid+1)

Ceil (smallest element ≥ k) uses the second pattern.
Floor (largest element ≤ k) uses the first pattern (this code).
```

---

## References

- 🔗 [GFG — Floor in a Sorted Array](https://www.geeksforgeeks.org/problems/floor-in-a-sorted-array-1587115620/1)
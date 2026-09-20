# Upper Bound (Binary Search)

## Problem
Find the **first index** in a sorted array where `arr[index] > k`. If no such element exists, return `n` (one past the end).

```
arr = [3, 5, 5, 6, 6, 6, 8, 9], k = 7

First element > 7 is 8, at index 6.
Upper bound = 6

arr = [3, 5, 5, 6, 6, 6, 8, 9], k = 9

No element > 9 exists.
Upper bound = 8 (= n, past the end)

arr = [3, 5, 5, 6, 6, 6, 8, 9], k = 2

All elements > 2. First is 3, at index 0.
Upper bound = 0
```

---

## The Problem Explained

Think of it like **sorted books on a shelf** where you want to insert `k+1` — the first slot AFTER all copies of `k`:

```
arr = [5, 5, 6, 6, 6, 8]
            ^^^^^^^
            all these are ≤ 6

For k=6: upper bound = index 5 (where 8 is).
"Insert after all 6s" → position 5.
```

---

## HOOK TO REMEMBER FOREVER

**"arr[mid] ≤ k → GO RIGHT (mid is still in the ≤k zone). arr[mid] > k → RECORD AND GO LEFT."**

This is the "last valid floor" problem but for the UPPER side:
- ✅ If `arr[mid] <= k` → mid is NOT above k yet → search right: `low = mid + 1`
- ✅ If `arr[mid] > k` → mid could be the answer, but maybe there's an earlier one → `high = mid - 1`
- ✅ Loop ends: `low` = first index where `arr[low] > k`
- ✅ Return `low` (the INDEX), not `arr[low]` (the value)

---

## ⚠️ Bug in Original Code

```cpp
return arr[low];   // ❌ WRONG — returns the VALUE and can crash
return low;        // ✅ CORRECT — returns the INDEX
```

**Why it crashes:** When `k >= arr[n-1]` (all elements ≤ k), the loop moves `low` to `n`. Then `arr[low]` = `arr[n]` → **out-of-bounds access!**

```
arr=[3,5,8], k=9

low=0,high=2 → mid=1, arr[1]=5≤9 → low=2
low=2,high=2 → mid=2, arr[2]=8≤9 → low=3
low=3 > high=2 → EXIT

arr[low] = arr[3] → OUT OF BOUNDS ❌
low = 3 = n → "insert at end" ✓
```

---

## Corrected Code

```cpp
int getUpperBound(int k, vector<int>& arr) {
    int n = arr.size();
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] <= k) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return low;  // index of first element > k, or n if none exists
}
```

---

## How It Works Step By Step

### Example: `arr=[3,5,5,6,6,6,8,9], k=7`

```
low=0, high=7

mid=3: arr[3]=6 ≤ 7 → low=4
mid=5: arr[5]=6 ≤ 7 → low=6
mid=6: arr[6]=8 > 7 → high=5
low=6 > high=5 → EXIT

return low=6  → arr[6]=8 is the first element > 7 ✓
```

### Example: `arr=[3,5,5,6,6,6,8,9], k=5`

```
low=0, high=7

mid=3: arr[3]=6 > 5 → high=2
mid=1: arr[1]=5 ≤ 5 → low=2
mid=2: arr[2]=5 ≤ 5 → low=3
low=3 > high=2 → EXIT

return low=3  → arr[3]=6 is first element > 5 ✓
(all three 5s at indices 1,2 were correctly skipped)
```

---

## Floor vs Upper Bound — The Pattern Pair

```
Floor (largest element ≤ k):
  arr[mid] <= k → record ans=mid, go RIGHT (low = mid+1)
  arr[mid] >  k → go LEFT (high = mid-1)
  Return ans (or -1 if never updated)

Upper Bound (first element > k):
  arr[mid] <= k → go RIGHT (low = mid+1)
  arr[mid] >  k → go LEFT (high = mid-1)
  Return low (always valid: 0 to n)

The only difference: floor records a candidate answer, upper bound just moves the pointers.
Both return where `low` lands, but floor uses `ans` as a fallback for the "not found" case.
```

---

## Edge Cases

### Case 1: k is Less Than All Elements

```
arr=[3,5,8], k=1
Every mid: arr[mid] > 1 → high shrinks to -1.
Return low=0 → arr[0]=3 is the first element > 1 ✓
```

### Case 2: k is Greater Than or Equal to All Elements

```
arr=[3,5,8], k=9
Every mid: arr[mid] ≤ 9 → low grows to n=3.
Return low=3 = n → "no element exists above k" ✓
```

### Case 3: k Equals an Array Element (Multiple Copies)

```
arr=[5,5,5,8], k=5
Upper bound skips ALL copies of 5 and lands on 8's index. ✓
This is why the condition is arr[mid] <= k (not <).
```

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(log n) |
| Space | O(1) |

> Note: The `sort()` call inside the original function is O(n log n) and defeats the purpose of binary search. The array should be sorted before calling this function — sort externally if needed.

---

## Lower Bound vs Upper Bound

```
Lower Bound: first index where arr[index] >= k
  Condition: arr[mid] < k → go right (low = mid+1)
             arr[mid] >= k → go left (high = mid-1)
  Return: low

Upper Bound: first index where arr[index] > k  (this problem)
  Condition: arr[mid] <= k → go right (low = mid+1)
             arr[mid] > k → go left (high = mid-1)
  Return: low

Difference: ≥ vs > in the "go left" condition.
Count of k in array = upperBound(k) - lowerBound(k).
```

---

## References

- 🔗 [GFG — Upper Bound](https://www.geeksforgeeks.org/upper_bound-in-cpp/)
- 🔗 [C++ STL `upper_bound`](https://cppreference.com/w/cpp/algorithm/upper_bound)
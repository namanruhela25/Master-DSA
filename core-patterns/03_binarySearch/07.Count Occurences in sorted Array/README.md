# Count Frequency in a Sorted Array

## Problem Link
🔗 [GFG — Count Occurrences in Sorted Array](https://www.geeksforgeeks.org/count-number-of-occurrences-or-frequency-in-a-sorted-array/)

---

## What is this Problem?

Given a sorted array and a target, count how many times the target appears. Must run in **O(log n)** — no linear scan.

```
nums=[1,1,2,2,2,3,4,5], target=2
Output: 3   (2 appears at indices 2,3,4)

nums=[1,1,2,2,2,3,4,5], target=6
Output: 0   (not in array)
```

---

## The Idea

```
All copies of target are CONTIGUOUS in a sorted array.
Find the FIRST occurrence index and LAST occurrence index.
Count = last - first + 1.

  [1, 1, 2, 2, 2, 3, 4, 5]
            ↑       ↑
           first   last
           (2)     (4)

  Count = 4 - 2 + 1 = 3 ✓
```

---

## Two Approaches

### Approach 1 — Custom Binary Search (Two Calls)

```cpp
int binarySearch(vector<int>& nums, int target, int leftTraverse) {
    int low = 0, high = nums.size() - 1, ans = -1;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (nums[mid] > target) high = mid - 1;
        else if (nums[mid] < target) low = mid + 1;
        else {
            ans = mid;                              // found — record it
            if (leftTraverse) high = mid - 1;      // look LEFT for earlier copy
            else              low  = mid + 1;      // look RIGHT for later copy
        }
    }
    return ans;
}

int countFreq(vector<int>& nums, int target) {
    int left  = binarySearch(nums, target, true);   // first occurrence
    int right = binarySearch(nums, target, false);  // last occurrence
    if (left == -1) return 0;
    return right - left + 1;
}
```

**The `leftTraverse` flag:**
```
leftTraverse=true  (finding FIRST occurrence):
  Found target at mid → record ans, go LEFT (high=mid-1)
  There might be an earlier copy. Keep searching left.
  Last recorded ans = leftmost occurrence.

leftTraverse=false (finding LAST occurrence):
  Found target at mid → record ans, go RIGHT (low=mid+1)
  There might be a later copy. Keep searching right.
  Last recorded ans = rightmost occurrence.
```

---

### Approach 2 — STL `lower_bound` + `upper_bound`

```cpp
int countFreqStdFunctions(vector<int>& arr, int target) {
    auto lower = lower_bound(arr.begin(), arr.end(), target);
    if (lower == arr.end() || *lower != target) return 0;
    auto upper = upper_bound(arr.begin(), arr.end(), target);
    return int(upper - arr.begin()) - int(lower - arr.begin());
}
```

```
lower_bound → iterator to FIRST element >= target
upper_bound → iterator to FIRST element >  target

If lower points to target: count = upper_index - lower_index
If lower points past array OR doesn't point to target: return 0

Example: arr=[1,1,2,2,2,3,4], target=2
  lower → index 2 (first 2)
  upper → index 5 (first element > 2, which is 3)
  count = 5 - 2 = 3 ✓
```

---

## How It Works Step By Step

### `nums=[1,1,2,2,2,3,4,5], target=2`

**Finding FIRST occurrence (leftTraverse=true):**
```
low=0, high=7, ans=-1

mid=3: nums[3]=2==target → ans=3, go LEFT: high=2
mid=1: nums[1]=1<2 → low=2
mid=2: nums[2]=2==target → ans=2, go LEFT: high=1
low=2 > high=1 → EXIT

first = 2
```

**Finding LAST occurrence (leftTraverse=false):**
```
low=0, high=7, ans=-1

mid=3: nums[3]=2==target → ans=3, go RIGHT: low=4
mid=5: nums[5]=3>2 → high=4
mid=4: nums[4]=2==target → ans=4, go RIGHT: low=5
low=5 > high=4 → EXIT

last = 4
```

**Count = 4 - 2 + 1 = 3 ✓**

---

## Edge Cases

### Target Not in Array

```
nums=[1,3,5], target=4
Both binary searches return -1. countFreq checks left==-1 → return 0 ✓
STL: lower points to 5 (*lower=5 ≠ 4) → return 0 ✓
```

### Target Appears Once

```
nums=[1,2,3], target=2
first=1, last=1. Count = 1-1+1 = 1 ✓
```

### All Elements Are Target

```
nums=[5,5,5,5], target=5
first=0, last=3. Count = 3-0+1 = 4 ✓
```

---

## Which Approach to Use?

| | Custom Binary Search | STL |
|---|---|---|
| Code length | More | Less |
| Interview | Shows you understand internals | Shows you know STL |
| Overflow risk | `(low+high)/2` — use `low+(high-low)/2` to be safe | Handled internally |
| Flexibility | Can adapt for any condition | Fixed semantics |

Both are **O(log n)** — two binary search calls.

> ⚠️ **Bug:** The custom `binarySearch` uses `int mid = (low + high) / 2` which can overflow for large indices. Use `low + (high - low) / 2` instead.

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(log n) — two binary search calls |
| Space | O(1) |

---

## Connection to First and Last Occurrence

```
First occurrence = Lower Bound (first index where arr[i] >= target AND arr[i] == target)
Last occurrence  = Upper Bound index - 1 (last index where arr[i] == target)

Count = last - first + 1 = upperBound(target) - lowerBound(target)

This is WHY upper_bound - lower_bound works directly:
  upper_bound gives one-past-last, lower_bound gives first.
  Difference = total count. ✓
```

---

## References

- 🔗 [GFG — Count Occurrences in Sorted Array](https://www.geeksforgeeks.org/count-number-of-occurrences-or-frequency-in-a-sorted-array/)
- 🔗 [LeetCode 34 — Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/)
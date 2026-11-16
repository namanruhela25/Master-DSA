# Find the Row with Maximum Ones

## Problem Link
🔗 [GFG — Row with Max 1s](https://www.geeksforgeeks.org/find-row-with-maximum-number-of-1s/)

---

## What is this Problem?

Given an `n × m` matrix where **every row is sorted** (all `0`s first, then all `1`s), return the index of the row with the **most 1s**. Return `-1` if there are no 1s at all.

```
mat = [[0,1,1,1],
       [0,0,1,1],
       [1,1,1,1],
       [0,0,0,0]]
Output: 2   (row 2 has four 1s)
```

Because each row is sorted, a row looks like this:

```
[0, 0, 1, 1, 1]
      ↑
  first 1 → everything from here right is a 1
 count of 1s = m - firstOneIndex
```

So "count the 1s in a row" becomes "find the first 1 in a row" — a binary search.

---

## The Idea

```
For each row:
  1. Binary search the FIRST index holding a 1.
  2. ones in that row = m - index.
  3. Keep the row that beats the best count so far.

Finding the first 1 = lower_bound(1) on a sorted row.
Rows with all zeros give index = m → count 0, which is correct.
```

```
row = [0,0,1,1,1], m=5
first 1 at index 2 → ones = 5 - 2 = 3 ✓
row = [0,0,0,0,0]
first 1 never found, low lands on 5 → ones = 5 - 5 = 0 ✓
```

---

## Code Full Solution

```cpp
int findIndex(vector<int> &row, int m) {
    int low = 0;
    int high = m - 1;

    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(row[mid] == 1) {
            high = mid - 1;   // 1 found — look further left
        } else {
            low = mid + 1;    // 0 found — first 1 must be right
        }
    }
    return low;               // first index with a 1 (m if none)
}

int rowWithMax1s(vector<vector<int>> &mat, int n, int m) {
    int ansRow = -1;
    int ones = 0;

    for(int i = 0; i < n; i++) {
        int index = findIndex(mat[i], m);
        int onecounts = m - index;
        if(onecounts > ones) {
            ones = onecounts;
            ansRow = i;
        }
    }
    return ansRow;
}
```

---

## Code Explanation

### `findIndex` — Lower Bound of 1

```cpp
if(row[mid] == 1) high = mid - 1;
else              low  = mid + 1;
return low;
```

When a `1` is found it is remembered only by **moving `high` left** — the loop ends with `low` sitting on the **first** `1`. This is `lower_bound(1)` written by hand; `std::lower_bound(row.begin(), row.end(), 1) - row.begin()` gives the same number.

### Why `return low` Is Correct Even With No 1s

```
all zeros → high keeps shrinking, low walks past the end → low == m
ones = m - m = 0 ✓
```

No special case needed — the arithmetic self-corrects.

### Counting

```cpp
int onecounts = m - index;
```

Sorted row ⇒ everything from the first `1` to the end is a `1`, so a subtraction gives the count instead of another scan.

### Strict `>` Keeps the First Best Row

```cpp
if(onecounts > ones)
```

On a tie the earlier row is kept (GFG expects the first such row). Using `>=` would return the last tied row instead.

### `ansRow = -1` Initial Value

If every row is all zeros, `onecounts` is `0` and never exceeds `ones = 0`, so `ansRow` stays `-1` — the required "no 1s present" answer.

---

## Full Trace: `mat = [[0,1,1,1],[0,0,1,1],[1,1,1,1],[0,0,0,0]]`

```
ones=0, ansRow=-1

Row 0 = [0,1,1,1]
  low=0, high=3
  mid=1: row[1]=1 → high=0
  mid=0: row[0]=0 → low=1
  low=1 > high=0 → index=1
  onecounts = 4-1 = 3 > 0 → ones=3, ansRow=0

Row 1 = [0,0,1,1]
  mid=1: 0 → low=2
  mid=2: 1 → high=1
  low=2 > high=1 → index=2
  onecounts = 4-2 = 2, not > 3 → unchanged

Row 2 = [1,1,1,1]
  mid=1: 1 → high=0
  mid=0: 1 → high=-1
  low=0 > high=-1 → index=0
  onecounts = 4-0 = 4 > 3 → ones=4, ansRow=2

Row 3 = [0,0,0,0]
  mid=1: 0 → low=2
  mid=2: 0 → low=3
  mid=3: 0 → low=4
  low=4 > high=3 → index=4
  onecounts = 4-4 = 0, not > 4 → unchanged

Return 2 ✓
```

---

## Example Traces

### No 1s Anywhere

```
mat=[[0,0],[0,0]]
row 0 → index 2 → 0 ones, not > 0
row 1 → index 2 → 0 ones
return -1 ✓
```

### Single Row, Single Column

```
mat=[[1]] → index 0 → 1 one > 0 → return 0 ✓
mat=[[0]] → index 1 → 0 ones → return -1 ✓
```

### Everything Is 1

```
mat=[[1,1],[1,1]] → row 0 gives 2 ones, row 1 ties but is not > 2 → return 0 ✓
```

---

## Edge Cases

### Tie Between Two Rows

First row wins because of the strict `>`. Matches the expected "first row with the maximum count".

### First Column Already 1

```
row=[1,1,1] → mid=1 is 1 → high=0 → mid=0 is 1 → high=-1 → index=0 → full count ✓
```

### Only Last Column Is 1

```
row=[0,0,1] → mid=1: 0 → low=2 → mid=2: 1 → high=1 → index=2 → 1 one ✓
```

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(n log m) — one binary search per row |
| Space | O(1) |

```
Alternative: scan each row right-to-left, or start from the top-right corner
and walk down/left to get O(n + m) — the staircase trick from the next problem.
This version's O(n log m) is equally acceptable; the binary search per row is
the simplest thing that reuses what's already known.
```

---

## Key Insight

```
In a sorted row, "count" is just "position":

  number of 1s = m - (index of the first 1)

So counting is free once you can locate the boundary between 0s and 1s —
and locating a boundary in a sorted array is exactly what lower_bound does.
```

---

## References

- 🔗 [GFG — Row with Max 1s](https://www.geeksforgeeks.org/find-row-with-maximum-number-of-1s/)
- 🔗 [std::lower_bound](https://en.cppreference.com/w/cpp/algorithm/lower_bound)

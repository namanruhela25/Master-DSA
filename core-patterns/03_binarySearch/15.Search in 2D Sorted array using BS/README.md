# Search in a 2D Sorted Array (Flattened Binary Search)

## Problem Link
🔗 [LeetCode 74 — Search a 2D Matrix](https://leetcode.com/problems/search-a-2d-matrix/)

---

## What is this Problem?

An `n × m` matrix where each row is sorted and the row breaks continue the order:

```
matrix = [[1,  3,  5,  7],
          [10, 11, 16, 20],
          [23, 30, 34, 60]]
```

That guarantee (`matrix[i][m-1] < matrix[i+1][0]`) means the whole matrix — read left to right, top to bottom — is **one sorted list of `n*m` elements**. Given a `target`, return `true` if it exists. Must run in **O(log(n·m))**.

```
target=3  → true
target=13 → false
```

---

## The Idea

```
The matrix is a sorted array that has been wrapped into rows.

So treat it as a 1D array of length n*m and run plain binary search on INDICES.
Only when reading a value do we convert:

    flat index  →  row = mid / m      (which row)
                   col = mid % m      (position inside that row)

    [1, 3, 5, 7, | 10, 11, 16, 20, | 23, 30, 34, 60]
     0  1  2  3    4   5   6   7     8   9  10  11
                           ↑
                     mid=5 → row 5/4=1, col 5%4=1 → matrix[1][1]=11
```

No copying, no extra array — the division turns one index into two.

---

## Code Full Solution

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        int m = matrix[0].size();

        int low = 0;
        int high = (n * m) - 1;

        while(low <= high) {
            int mid = low + (high - low) / 2;

            int i = mid / m;
            int j = mid % m;

            if(matrix[i][j] == target) return true;

            if(matrix[i][j] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return false;
    }
};
```

---

## Code Explanation

### Search Over Flat Indices

```cpp
int low = 0;
int high = (n * m) - 1;
```

The bounds are indices into the **virtual** 1D array, not rows or columns. This is the whole trick — everything else is textbook binary search.

### Index → Cell Conversion

```cpp
int i = mid / m;   // row: how many full rows fit before this index
int j = mid % m;   // column: offset inside that row
```

```
m = 4
mid=0  → i=0, j=0     mid=5 → i=1, j=1
mid=3  → i=0, j=3     mid=8 → i=2, j=0
```

`mid / m` counts complete rows; `mid % m` is the leftover.

### Standard Compare-and-Halve

```cpp
if(matrix[i][j] == target) return true;
if(matrix[i][j] < target) low = mid + 1; else high = mid - 1;
```

Because the flat order is sorted, the usual binary-search logic holds unchanged.

### `mid = low + (high - low) / 2`

Overflow-safe, and important here: `n*m` can be as large as `10^4 × 10^4`-ish in the unconstrained version, where `low + high` may overflow `int`.

---

## Full Trace: `matrix=[[1,3,5,7],[10,11,16,20],[23,30,34,60]]`, `target=3`

```
n=3, m=4, low=0, high=11

mid=5: i=1, j=1 → matrix[1][1]=11
       11 == 3? NO. 11 > 3 → high=4

low=0, high=4

mid=2: i=0, j=2 → matrix[0][2]=5
       5 > 3 → high=1

low=0, high=1

mid=0: i=0, j=0 → matrix[0][0]=1
       1 < 3 → low=1

low=1, high=1

mid=1: i=0, j=1 → matrix[0][1]=3
       == target → return true ✓
```

## Full Trace: same matrix, `target=13`

```
low=0, high=11

mid=5: matrix[1][1]=11 < 13 → low=6

low=6, high=11

mid=8: i=2, j=0 → matrix[2][0]=23 > 13 → high=7

low=6, high=7

mid=6: i=1, j=2 → matrix[1][2]=16 > 13 → high=5

low=6 > high=5 → EXIT → return false ✓
```

---

## Example Traces

### Target in the Last Cell

```
matrix=[[1,3],[10,20]], target=20, n=2, m=2
low=0, high=3
mid=1: i=0,j=1 → 3 < 20 → low=2
mid=2: i=1,j=0 → 10 < 20 → low=3
mid=3: i=1,j=1 → 20 == target → true ✓
```

### Single Row

```
matrix=[[1,3,5,7]], target=5, n=1, m=4
mid works exactly like a 1D binary search:
mid=1 (3) < 5 → low=2
mid=3 (7) > 5 → high=2
mid=2 (5) → true ✓
```

### Single Column

```
matrix=[[1],[5],[9]], target=9, n=3, m=1
i = mid/1 = mid, j = mid%1 = 0 → walks straight down the column
mid=1 (5) < 9 → low=2 → mid=2 (9) → true ✓
```

---

## Edge Cases

### Empty Matrix

```
matrix = []  →  matrix[0].size() reads out of bounds ✗
```

LeetCode 74 guarantees `n, m >= 1`, so the code is safe **under those constraints**. A guard `if(matrix.empty() || matrix[0].empty()) return false;` is what a real implementation needs.

### Target Smaller / Larger Than Everything

```
Both fall out of the loop with low > high → false ✓
```

### `n*m` Overflow

```
int high = (n * m) - 1;
```

Fine for LeetCode's limits, but if `n` and `m` could each be ~50,000, `n*m` would overflow `int` before the subtraction — use `long long` for the bounds in that case.

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(log(n·m)) — one binary search over all cells |
| Space | O(1) — no flattening copy |

```
Naive alternative: binary search for the row, then binary search inside it.
That is O(log n + log m) — the same thing, in two steps instead of one.
This code does it in a single search by never leaving index space.
```

---

## Key Insight

```
Row-major order of a matrix is a sorted array.

So there are only two questions: how many elements (n*m, for the bounds),
and how to get from an index to a cell (mid/m, mid%m).

Division and modulo replace the "find the right row, then the right column"
dance — one search instead of two.
```

---

## References

- 🔗 [LeetCode 74 — Search a 2D Matrix](https://leetcode.com/problems/search-a-2d-matrix/)
- 🔗 [LeetCode 240 — Search a 2D Matrix II](https://leetcode.com/problems/search-a-2d-matrix-ii/) (row+column sorted, staircase solution)

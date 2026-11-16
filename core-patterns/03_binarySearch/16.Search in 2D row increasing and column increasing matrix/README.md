# Search in a Row-Increasing and Column-Increasing Matrix

## Problem Link
🔗 [LeetCode 240 — Search a 2D Matrix II](https://leetcode.com/problems/search-a-2d-matrix-ii/)

---

## What is this Problem?

An `n × m` matrix where **every row is sorted left→right** and **every column is sorted top→bottom** (but the rows do *not* continue into each other). Given a `target`, return `true` if it exists.

```
matrix = [[1,  4,  7,  11, 15],
          [2,  5,  8,  12, 19],
          [3,  6,  9,  16, 22],
          [10, 13, 14, 17, 24],
          [18, 21, 23, 26, 30]]

target=5   → true
target=20  → false
```

Note the difference from the previous problem: `15 → 2` at the row break, so row-major order is **not** sorted. Flattening and binary searching does not work here.

---

## The Idea

```
Start at the TOP-RIGHT corner. That cell is special:
  - the LARGEST value in its row
  - the SMALLEST value in its column

So comparing there eliminates an entire row or an entire column:

    matrix[row][col] == target  →  found
    matrix[row][col] <  target  →  too small → nothing left in this row can
                                   help → row++     (drop the row)
    matrix[row][col] >  target  →  too big   → nothing below in this column
                                   can help → col-- (drop the column)

Walk down and left like a staircase until one pointer leaves the matrix.

  1  4  7 11 15 ←start (max of row 0, min of col 4)
  2  5  8 12 19
  3  6  9 16 22
 10 13 14 17 24
 18 21 23 26 30
```

Every step removes at least one full row or one full column, so at most `n + m` steps.

---

## Code Full Solution

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        int m = matrix[0].size();

        int row = 0;
        int col = m - 1;

        while(row < n && col >= 0) {
            if(matrix[row][col] == target) return true;

            if(matrix[row][col] < target) {
                row++;
            } else {
                col--;
            }
        }
        return false;
    }
};
```

---

## Code Explanation

### Start Where One Comparison Is Maximally Informative

```cpp
int row = 0;
int col = m - 1;
```

Top-right is chosen because it is simultaneously the **max of its row** and the **min of its column**. Any other corner gives only one useful direction. (Bottom-left works symmetrically.)

### Too Small → Move Down

```cpp
if(matrix[row][col] < target) row++;
```

The current row is sorted ascending, so everything **left** of `col` in this row is `≤ matrix[row][col] < target` — the entire row is useless. Move down one row.

### Too Big → Move Left

```cpp
else col--;
```

The current column is sorted ascending, so everything **below** `row` in this column is `≥ matrix[row][col] > target` — the entire column is useless. Move left one column.

### The Loop Condition Is the Boundary

```cpp
while(row < n && col >= 0)
```

`row` only grows and `col` only shrinks, so the walk always terminates. Falling off the bottom or the left edge means the target is not in the matrix.

---

## Full Trace: `target = 5`

```
row=0, col=4 → 15 > 5  → col=3
row=0, col=3 → 11 > 5  → col=2
row=0, col=2 →  7 > 5  → col=1
row=0, col=1 →  4 < 5  → row=1
row=1, col=1 →  5 == target → return true ✓
```

Path drawn on the matrix:

```
 1 [4] 7 11(15)
 2 [5] 8 12 19
 3  6  9 16 22
10 13 14 17 24
18 21 23 26 30
     ↑ walked left along row 0, then down to the match
```

## Full Trace: `target = 20` (absent)

```
row=0, col=4 → 15 < 20 → row=1
row=1, col=4 → 19 < 20 → row=2
row=2, col=4 → 22 > 20 → col=3
row=2, col=3 → 16 < 20 → row=3
row=3, col=3 → 17 < 20 → row=4
row=4, col=3 → 30 > 20 → col=2
row=4, col=2 → 23 > 20 → col=1
row=4, col=1 → 21 > 20 → col=0
row=4, col=0 → 18 < 20 → row=5
row=5 → row < n fails → EXIT → return false ✓
```

---

## Example Traces

### Target Smaller Than Everything

```
target=0
row=0,col=4: 15>0 → col=3 → 11>0 → col=2 → 7>0 → col=1 → 4>0 → col=0 → 1>0 → col=-1
EXIT → false ✓   (never left row 0 — the answer can only be in column 0)
```

### Target Larger Than Everything

```
target=31
row walks 0→1→2→3→4 comparing against column 4 (15,19,22,24,30), all < 31
row=5 → EXIT → false ✓   (each comparison killed one row)
```

### Single Cell

```
matrix=[[5]], target=5 → row=0,col=0 → match → true ✓
matrix=[[5]], target=4 → 5>4 → col=-1 → false ✓
```

### Single Row

```
matrix=[[1,4,7]], target=4
col walks left until 4 is hit — an ordinary linear walk in one row ✓
```

---

## Edge Cases

### Empty Matrix

```cpp
int m = matrix[0].size();   // out of bounds if matrix is empty
```

LeetCode 240 guarantees at least one row and column. For real code, guard with `if(matrix.empty() || matrix[0].empty()) return false;`.

### Value Present in Many Places

Returned on the first hit — no need to find a specific copy.

### Why Not Binary Search Each Row? (`O(n log m)`)

That also works and is a valid answer. The staircase is preferred here because it uses **both** sortings at once, is `O(n + m)` with no binary search at all, and needs no `lower_bound` calls.

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(n + m) — `row` rises at most `n` times, `col` falls at most `m` times |
| Space | O(1) |

```
Comparison of approaches:
  flatten + binary search     → INVALID here (row-major is not sorted)
  binary search each row      → O(n log m)
  staircase from a corner     → O(n + m)   ← this code
```

---

## Key Insight

```
A sorted 2D matrix has FOUR monotone directions, so pick the corner where
"increasing" and "decreasing" both point INWARD.

From the top-right, down is bigger and left is smaller — two of the four
neighbours are inside the matrix and each comparison provably discards a
whole line. That is a binary-search-style halving, just expressed as a walk.
```

---

## References

- 🔗 [LeetCode 240 — Search a 2D Matrix II](https://leetcode.com/problems/search-a-2d-matrix-ii/)
- 🔗 [LeetCode 74 — Search a 2D Matrix](https://leetcode.com/problems/search-a-2d-matrix/) (fully sorted, flattenable)

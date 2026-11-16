# Find Peak Element in a 2D Array

## Problem Link
🔗 [LeetCode 1901 — Find a Peak Element II](https://leetcode.com/problems/find-a-peak-element-ii/)

---

## What is this Problem?

Given an `n × m` matrix where **no two adjacent cells are equal**, a **peak** is a cell strictly greater than all four of its neighbours (cells outside the matrix count as `-∞`). Return the **coordinates of any peak**.

```
mat = [[10, 20, 15],
       [21, 30, 14],
       [ 7, 16, 32]]
Output: [1,1]   (30 > 10, 20, 21, 16)
```

`[2,2]` (32) is also a peak — any answer is accepted. Required complexity: **O(n log m)**.

---

## The Idea

```
Same hill-climbing as 1D Peak Element, one dimension at a time.

Binary search on COLUMNS. For the middle column:
  1. Find the biggest value in that whole column (and its row).
  2. Compare it with its LEFT and RIGHT neighbours.
  3. It beats both → it is a peak (up/down are already satisfied,
                    because nothing in its column is bigger).
     Left is bigger → a peak must exist in the left half of columns.
     Right is bigger → a peak must exist in the right half.

Why "up and down are already satisfied"? The chosen value is the MAX of its
column, so both vertical neighbours are ≤ it — and by the problem's rule
(no equal adjacent cells) they are strictly smaller.

  10 [20] 15
  21 [30] 14      ← column mid=1: max is 30 (row 1). Left=21, Right=14.
   7 [16] 32        30 > 21 and 30 > 14 → peak found at (1,1)
```

The `-∞` border guarantees a peak always exists, exactly like the 1D version.

---

## Code Full Solution

```cpp
class Solution {
public:
    int findMaxRowElement(vector<vector<int>>& mat, int mid, int n) {
        int target = INT_MIN;
        int ans = -1;
        for(int i = 0; i < n; i++) {
            if(mat[i][mid] > target) {
                ans = i;
                target = mat[i][mid];
            }
        }
        return ans;
    }

    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();

        int low = 0;
        int high = m - 1;

        while(low <= high) {
            int mid = low + (high - low) / 2;
            int row = findMaxRowElement(mat, mid, n);

            int left  = (mid - 1 >= 0) ? mat[row][mid-1] : -1;
            int right = (mid + 1 < m)  ? mat[row][mid+1] : -1;
            int maxelement = mat[row][mid];

            if(maxelement > left && maxelement > right) return {row, mid};

            if(maxelement < left) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return {-1, -1};
    }
};
```

---

## Code Explanation

### `findMaxRowElement` — Linear Scan of One Column

```cpp
for(int i = 0; i < n; i++)
    if(mat[i][mid] > target) { ans = i; target = mat[i][mid]; }
```

Returns the **row index** of the maximum in column `mid`. This is the O(n) part, which combined with O(log m) column steps gives the required O(n log m).

### Out-of-Bounds Neighbours as `-1`

```cpp
int left  = (mid - 1 >= 0) ? mat[row][mid-1] : -1;
int right = (mid + 1 < m)  ? mat[row][mid+1] : -1;
```

Outside the grid is a wall, so any real cell beats it. `-1` works because the constraints guarantee **all values are ≥ 1**; with negative values you would need `INT_MIN` instead.

### The Peak Check

```cpp
if(maxelement > left && maxelement > right) return {row, mid};
```

Only left and right need checking — the vertical neighbours are smaller automatically, since `maxelement` is the maximum of its entire column.

### Slide Toward the Bigger Neighbour

```cpp
if(maxelement < left) high = mid - 1;
else                  low  = mid + 1;
```

If the left neighbour is bigger, a peak must exist in the columns left of `mid` — the value growing toward the left cannot grow forever without turning down, and the border is `-∞`. Mirror argument for right.

### `return {-1, -1}` Is Unreachable

A peak is guaranteed, and each step moves toward one. It only satisfies the compiler.

---

## Full Trace: `mat = [[1,2,3,4]]` (single row)

```
n=1, m=4, low=0, high=3

mid=1: column 1 has only mat[0][1]=2 → row=0
       left = mat[0][0] = 1, right = mat[0][2] = 3
       2 > 1 ✓ but 2 > 3? NO → not a peak
       2 < 3 (left)? NO → low = 2

low=2, high=3

mid=2: row=0, value=3
       left = mat[0][1] = 2, right = mat[0][3] = 4
       3 > 2 ✓ but 3 > 4? NO → not a peak
       3 < 2? NO → low = 3

low=3, high=3

mid=3: row=0, value=4
       left = mat[0][2] = 3, right = -1 (out of bounds)
       4 > 3 ✓ and 4 > -1 ✓ → return {0,3} ✓
```

## Full Trace: `mat = [[10,20,15],[21,30,14],[7,16,32]]`

```
n=3, m=3, low=0, high=2

mid=1: column 1 = [20, 30, 16] → max 30 at row=1
       left  = mat[1][0] = 21
       right = mat[1][2] = 14
       maxelement = 30
       30 > 21 ✓ and 30 > 14 ✓ → return {1,1} ✓
```

---

## Example Traces

### Single Column

```
mat = [[1],[3],[2]]
low=0, high=0
mid=0: column 0 = [1,3,2] → max 3 at row=1
       left = -1, right = -1 (both out of bounds)
       3 > -1 and 3 > -1 → return {1,0} ✓
```

### Single Cell

```
mat=[[5]] → mid=0, row=0, left=-1, right=-1 → return {0,0} ✓
```

### Peak Needs Two Moves

```
mat = [[1, 2],[3, 4]]

low=0, high=1
mid=0: column 0 = [1,3] → max 3 at row=1
       left = -1, right = mat[1][1] = 4
       3 > -1 ✓ but 3 > 4? NO
       3 < -1? NO → low = 1

low=1, high=1
mid=1: column 1 = [2,4] → max 4 at row=1
       left = mat[1][0] = 3, right = -1
       4 > 3 ✓ and 4 > -1 ✓ → return {1,1} ✓
```

### Plateau-Free Requirement

```
mat = [[1,1],[1,1]] → INVALID input (adjacent equal cells).
"no two adjacent cells are equal" is what makes the vertical comparison
strict and the binary search well-defined.
```

---

## Edge Cases

### Peak on the Border

```
mat=[[9,8],[7,6]]
mid=0: column 0 = [9,7] → max 9 at row 0
       left=-1, right=8 → 9 > -1 and 9 > 8 → return {0,0} ✓
Border cells are fine — the missing neighbour is a -1 wall.
```

### Values Must Be Non-Negative

The `-1` sentinel depends on it. LeetCode 1901 guarantees `1 <= mat[i][j] <= 10^5`, so it holds; otherwise use `INT_MIN`.

### Empty Matrix

`mat[0].size()` would read out of bounds. Constraints guarantee `n, m >= 1`; add a guard in production code.

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(n log m) — `log m` column steps, each scanning `n` cells |
| Space | O(1) |

```
Why not O(log n · log m)? The max of a column cannot be binary searched —
you must inspect every cell of that column. That linear scan is the O(n)
factor. Choosing to binary search rows instead swaps the roles: O(m log n).
```

---

## Key Insight

```
A 2D peak search = 1D peak search with a "condensed" row of values.

Compress one dimension by taking the MAXIMUM of each column.
Now the problem is 1D: find a peak in that compressed array — and any peak
there is automatically a true 2D peak, because the cell already beats its
whole column.

Binary search the compressed array without ever building it.
```

---

## References

- 🔗 [LeetCode 1901 — Find a Peak Element II](https://leetcode.com/problems/find-a-peak-element-ii/)
- 🔗 [LeetCode 162 — Find Peak Element](https://leetcode.com/problems/find-peak-element/) (1D version)

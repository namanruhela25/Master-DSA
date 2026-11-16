# Matrix Median

## Problem Link
🔗 [GFG — Median in a Row-wise Sorted Matrix](https://www.geeksforgeeks.org/problems/median-in-a-row-wise-sorted-matrix1527/1)

---

## What is this Problem?

Given an `n × m` matrix where **each row is sorted** (the matrix as a whole is not), return the **median** of all `n*m` elements. `n` and `m` are odd.

```
mat = [[1, 3, 5],
       [2, 6, 9],
       [3, 6, 9]]
All elements: 1, 2, 3, 3, 5, 6, 6, 9, 9
Median (5th of 9): 5
```

Sorting everything is O(n·m·log(n·m)) — acceptable but wasteful. The expected solution runs in roughly **O(n · log m · log(maxValue))**.

---

## The Idea

```
Don't binary search the matrix — binary search the VALUE RANGE.

For a candidate value x, ask: "how many elements are ≤ x?"
Each row is sorted, so that count is one upper_bound per row:

    count(x) = Σ upper_bound(mat[i], x) - mat[i].begin()
             = Σ (number of elements ≤ x in row i)

This count is monotonic: as x grows, count(x) only grows.

The median is the smallest x whose count reaches the required rank.

    [1, 2, 3, 3, 5, 6, 6, 9, 9]
     1  2  3  4  5  6  7  8  9    ← rank
                 ↑
       median = the 5th element = 5
       count(4) = 4  → too small, rank not reached
       count(5) = 5  → reached → 5 is the answer

Search range: [smallest element, largest element] = [1, 9] here.
```

---

## Code Full Solution

```cpp
class Solution {
  public:
    int checkMid(vector<vector<int>> &mat, int &mid, int n) {
        int cnt = 0;
        for(int i = 0; i < n; i++) {
            cnt += upper_bound(mat[i].begin(), mat[i].end(), mid) - mat[i].begin();
        }
        return cnt;
    }

    int median(vector<vector<int>> &mat) {
        int low  = INT_MAX;
        int high = INT_MIN;
        int n = mat.size();
        int m = mat[0].size();

        for(int i = 0; i < n; i++) {
            low  = min(low,  mat[i][0]);      // smallest in each row
            high = max(high, mat[i][m-1]);    // largest in each row
        }

        int rqElements = ((n * m)) / 2;

        while(low <= high) {
            int mid = low + (high - low) / 2;
            int cal = checkMid(mat, mid, n);

            if(cal >= rqElements) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }
};
```

---

## Code Explanation

### Search Range From the Rows

```cpp
low  = min(low,  mat[i][0]);
high = max(high, mat[i][m-1]);
```

The true minimum is the smallest first-column value and the true maximum is the largest last-column value (rows are sorted). No full scan needed to set the range.

### `checkMid` — Count Elements ≤ `mid`

```cpp
cnt += upper_bound(mat[i].begin(), mat[i].end(), mid) - mat[i].begin();
```

`upper_bound` returns an iterator to the first element **greater than** `mid`, so its distance from `begin()` is exactly the number of elements `≤ mid`. Summed over rows, that is the global count.

```cpp
mat[i] = [1, 3, 5], mid = 3
upper_bound → points at 5 (index 2) → 2 elements ≤ 3 ✓
```

### The Halving Rule

```cpp
if(cal >= rqElements) high = mid - 1;
else                  low  = mid + 1;
return low;
```

`count` is monotone in `mid`, so `cal >= rqElements` is a **predicate that flips once**: it is false for small values and true from the median onward. The loop finds the first `mid` where it becomes true — the standard "binary search on the answer" pattern.

```
x:        1  2  3  4  5  6  7  8  9
count(x): 1  2  4  4  5  7  7  9  9
                    ↑
          rank 5 reached at x=5 → answer 5
```

---

## ⚠️ Off-By-One in the Rank

```cpp
int rqElements = ((n * m)) / 2;
```

**This is one too small.** The median of `N` (odd) sorted elements is the element at 0-based index `N/2`, which is the **`N/2 + 1`-th smallest** — not the `N/2`-th. So the code finds the element one slot *before* the median.

### Traced proof — `mat = [[1,2,3]]` (1×3, median is 2)

```
rqElements = 3/2 = 1
low=1, high=3

mid=2: count ≤ 2 = 2.  2 >= 1 → high=1
mid=1: count ≤ 1 = 1.  1 >= 1 → high=0

low=1 > high=0 → return 1 ✗   (expected 2)
```

### Traced proof — 3×3

```
mat = [[1,3,5],
       [2,6,9],
       [3,6,9]]
sorted: 1,2,3,3,5,6,6,9,9     median = 5 (5th)

rqElements = 9/2 = 4  → the loop targets the 4th smallest = 3
low=1, high=9
mid=5: count ≤5 = 5  ≥4 → high=4
mid=2: count ≤2 = 2  <4 → low=3
mid=3: count ≤3 = 4  ≥4 → high=2
low=3 > high=2 → return 3 ✗   (expected 5)
```

### The fix

```cpp
int rqElements = (n * m + 1) / 2;   // rank of the median, 1-based
```

For `N = 9` that gives `5` (the 5th smallest ✓); for `N = 3` it gives `2` (the 2nd smallest ✓).

### Also remove the debug prints

```cpp
cout<<low<<high<<endl;   // inside median()
```

Left in from testing — these pollute judge output when the harness compares stdout.

---

## Full Trace: `mat = [[1,3,5],[2,6,9],[3,6,9]]` with the fixed rank

```
low = min(1, 2, 3) = 1
high = max(5, 9, 9) = 9
rqElements = (9+1)/2 = 5

mid=5: count ≤5 = 3 + 1 + 1 = 5 → 5 >= 5 → high=4
mid=2: count ≤2 = 1 + 1 + 0 = 2 → < 5   → low=3
mid=3: count ≤3 = 2 + 1 + 1 = 4 → < 5   → low=4

low=4, high=4
mid=4: count ≤4 = 2 + 1 + 1 = 4 → < 5 → low=5

low=5 > high=4 → return 5 ✓
```

Note how `mid=4` shows the important subtlety: **`low` can land on a value that is not in the matrix** (4 does not appear). That is why the answer is taken from the loop's exit point rather than from a matched element — since the predicate flips between 4 and 5, `low` ends exactly on 5, which *is* in the matrix. The first `x` where `count(x) ≥ rank` is always an element of the array.

---

## Example Traces

### Single Element

```
mat=[[7]] → low=high=7, rq=(1+1)/2=1
mid=7: count ≤7 = 1 ≥ 1 → high=6 → return 7 ✓
```

### One Row, Already Sorted

```
mat=[[1,2,3,4,5]] → rq=(5+1)/2=3 (the 3rd smallest)
mid range 1..5:
mid=3: count=3 ≥3 → high=2
mid=1: count=1 <3 → low=2
mid=2: count=2 <3 → low=3
return 3 ✓
```

### All Rows Identical

```
mat=[[2,2],[2,2],[2,2]] → N=6 (even; GFG keeps n,m odd, but it still runs)
rq=(6+1)/2=3 → count(2)=6 ≥3, count(1)=0 → return 2 ✓
```

---

## Edge Cases

### Median Value Appears Multiple Times

`count(x) ≥ rank` is reached at the first occurrence of the value, so the returned value is correct regardless of multiplicity ✓

### Duplicate Values Across Rows

No issue — the algorithm never needs to know *which* row an element came from, only how many elements are `≤ x`.

### Large Values

`upper_bound` comparisons are `O(log m)` on integers; the value range is what gets halved, so `log(maxValue) ≈ 31` steps for values up to `10^9`.

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(n · log m · log(maxValue)) — each step does `n` upper-bounds, and there are `log(range)` steps |
| Space | O(1) besides input |

```
Sorting the whole matrix: O(n·m·log(n·m)) and O(n·m) extra memory.
Value-space binary search never materialises the sorted array — that is the win.
```

---

## Key Insight

```
When the answer is a VALUE and you can cheaply count "how many elements are
≤ x?", binary search the value range instead of the data.

The monotone predicate is  count(x) ≥ medianRank.

Row-wise sorting is exactly what makes count(x) cheap: one upper_bound per row.
```

---

## References

- 🔗 [GFG — Median in a Row-wise Sorted Matrix](https://www.geeksforgeeks.org/problems/median-in-a-row-wise-sorted-matrix1527/1)
- 🔗 [std::upper_bound](https://en.cppreference.com/w/cpp/algorithm/upper_bound)

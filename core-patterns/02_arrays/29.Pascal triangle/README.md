# Pascal's Triangle

## Problem Link
🔗 [LeetCode 118 — Pascal's Triangle](https://leetcode.com/problems/pascals-triangle/)

---

## What is this Problem?

Given an integer `numRows`, return the first `numRows` of **Pascal's Triangle**.

In Pascal's Triangle, each number is the **sum of the two numbers directly above it**. The edges are always `1`.

**Examples:**
```
numRows = 5

Output:
[[1],
 [1,1],
 [1,2,1],
 [1,3,3,1],
 [1,4,6,4,1]]

numRows = 1
Output: [[1]]
```

---

## The Problem Explained

Pascal's Triangle is a triangular arrangement of numbers where:

```
Row 0:       1
Row 1:      1 1
Row 2:     1 2 1
Row 3:    1 3 3 1
Row 4:   1 4 6 4 1

Edge rule:  first and last element of every row = 1
Inner rule: m[i][j] = m[i-1][j-1] + m[i-1][j]
            (sum of the two elements directly above)
```

**The mathematical view:** Every element at row `n`, column `k` (0-indexed) is exactly the **binomial coefficient C(n, k)** — also written as `nCk` or `ⁿCₖ`.

```
Row 4: C(4,0)  C(4,1)  C(4,2)  C(4,3)  C(4,4)
     =   1       4       6       4       1
```

**Key idea:** Generate each row by computing all C(row, col) values using an efficient incremental nCr calculation.

---

## HOOK TO REMEMBER FOREVER

**"ROW i HAS ELEMENTS C(i,0), C(i,1), ... C(i,i). COMPUTE EACH USING nCr IN O(r)."**

Every time you see "generate Pascal's triangle":
- ✅ Outer loop: rows 1 to `numRows` (or 0 to `numRows-1`)
- ✅ Inner loop: columns 1 to `i` for row `i`
- ✅ Each element at row `i`, col `j` = `C(i-1, j-1)` (1-indexed) = `C(i, j)` (0-indexed)
- ✅ Use the **incremental nCr**: multiply by `(n-i)` then divide by `(i+1)` each step
- ✅ O(numRows²) time, O(numRows²) space for the output

**Remember: The element at position (row, col) is ALWAYS a binomial coefficient. Compute it efficiently without a factorial explosion by dividing at each multiplication step!** 📐

---

## The nCr Formula — Done Efficiently

The naive formula is `C(n,r) = n! / (r! × (n-r)!)` — but factorials overflow quickly.

**The incremental approach avoids this:**

```
C(n, r) = n! / (r! × (n-r)!)
         = [n × (n-1) × ... × (n-r+1)] / [r!]
         = [n/1] × [(n-1)/2] × [(n-2)/3] × ... × [(n-r+1)/r]

Each multiplication-then-division keeps the number small.
And importantly: the result is ALWAYS an integer at each step —
so integer division is always exact. ✓

Example: C(4, 2)
  i=0: res = 1 × (4-0) / (0+1) = 4 / 1 = 4
  i=1: res = 4 × (4-1) / (1+1) = 4×3 / 2 = 6

C(4,2) = 6 ✓
```


## How It Works Step By Step

### nCr Calculation for Each Element

```
Row 1 (i=1): j=1 → nCr(0,0) = C(0,0) = 1
              → [1]

Row 2 (i=2): j=1 → nCr(1,0) = C(1,0) = 1
             j=2 → nCr(1,1) = C(1,1) = 1
              → [1,1]

Row 3 (i=3): j=1 → nCr(2,0) = 1
             j=2 → nCr(2,1) = 2
             j=3 → nCr(2,2) = 1
              → [1,2,1]

Row 4 (i=4): j=1 → nCr(3,0) = 1
             j=2 → nCr(3,1) = 3
             j=3 → nCr(3,2) = 3
             j=4 → nCr(3,3) = 1
              → [1,3,3,1]

Row 5 (i=5): j=1 → nCr(4,0) = 1
             j=2 → nCr(4,1) = 4
             j=3 → nCr(4,2) = 6
             j=4 → nCr(4,3) = 4
             j=5 → nCr(4,4) = 1
              → [1,4,6,4,1]
```

### Step Through nCr(4, 2) — Computing C(4,2)

```
n=4, r=2, res=1

i=0: res = 1 × (4-0) = 4
     res = 4 / (0+1) = 4

i=1: res = 4 × (4-1) = 12
     res = 12 / (1+1) = 6

Loop ends. Return 6 ✓

C(4,2) = 6  → the "6" at row 4, position 3 of Pascal's Triangle ✓
```

---

## Code Full Solution

```cpp
class Solution {
public:
    int nCr(int n, int r) {
        long long res = 1;
        for (int i = 0; i < r; i++) {
            res = res * (n - i);
            res = res / (i + 1);
        }
        return res;
    }

    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ans;

        for (int i = 1; i <= numRows; i++) {
            vector<int> temp;
            for (int j = 1; j <= i; j++) {
                temp.push_back(nCr(i - 1, j - 1));
            }
            ans.push_back(temp);
        }

        return ans;
    }
};
```

---

## Code Explanation

### `nCr(n, r)` — Incremental Binomial Coefficient

```cpp
long long res = 1;
for (int i = 0; i < r; i++) {
    res = res * (n - i);
    res = res / (i + 1);
}
return res;
```

**Why `long long` for `res`?**
```
During the multiplication step, res × (n-i) can temporarily
be larger than INT_MAX even if the final C(n,r) fits in an int.

Example: C(20,10) = 184756. But mid-computation:
  after multiplying numerator terms, intermediate value
  can reach hundreds of millions.

long long prevents overflow in intermediate steps.
The final result is cast back to int on return. ✓
```

**Why is integer division exact at each step?**
```
At step i, we have computed:
  res = n × (n-1) × ... × (n-i+1) / (1 × 2 × ... × i)
      = C(n, i)

C(n, i) is always a whole number (it's a count of combinations).
So dividing by (i+1) at step i gives C(n, i+1) — always exact. ✓

No rounding errors, no floating point needed.
```

---

### `generate(numRows)` — Building the Triangle

```cpp
for (int i = 1; i <= numRows; i++) {
    vector<int> temp;
    for (int j = 1; j <= i; j++) {
        temp.push_back(nCr(i - 1, j - 1));
    }
    ans.push_back(temp);
}
```

**Why `nCr(i-1, j-1)` and not `nCr(i, j)`?**
```
The code uses 1-indexed loops (i starts at 1, j starts at 1).
Row i has i elements, and in 0-indexed terms:
  Row = i - 1
  Column = j - 1

So element at (row i, position j) = C(i-1, j-1).

Example: row 3 (i=3), third element (j=3):
  nCr(2, 2) = C(2,2) = 1 ✓

Matches the 1,2,1 pattern for row 3 of Pascal's Triangle.
```

---

## Complete Example Traces

### Trace 1: numRows = 4

```
i=1: temp = [nCr(0,0)] = [1]. ans=[[1]]
i=2: temp = [nCr(1,0), nCr(1,1)] = [1,1]. ans=[[1],[1,1]]
i=3: temp = [nCr(2,0), nCr(2,1), nCr(2,2)] = [1,2,1]. ans=[[1],[1,1],[1,2,1]]
i=4: temp = [nCr(3,0), nCr(3,1), nCr(3,2), nCr(3,3)]
          = [1, 3, 3, 1]

nCr(3,1): r=1. i=0: res=1×3/1=3. return 3.
nCr(3,2): r=2. i=0: res=3. i=1: res=3×2/2=3. return 3.

ans = [[1],[1,1],[1,2,1],[1,3,3,1]] ✓
```

### Trace 2: numRows = 1

```
i=1: temp = [nCr(0,0)] = [1].
ans = [[1]] ✓
```

### Trace 3: nCr Corner Cases

```
nCr(n, 0) — any n:
  r=0, loop doesn't run. return 1. ✓ (C(n,0) = 1 always)

nCr(n, n) — choosing all:
  C(n,n) = 1 always.
  Loop: each step multiplies by (n-i) and divides by (i+1).
  After n steps: result = n!/n! = 1. ✓

nCr(5, 2):
  i=0: res = 1×5/1 = 5
  i=1: res = 5×4/2 = 10
  return 10 = C(5,2) ✓
```

---

## Edge Cases

### Case 1: numRows = 1

```
Only one row: [1]
Output: [[1]] ✓
```

### Case 2: numRows = 2

```
Rows: [1], [1,1]
Output: [[1],[1,1]] ✓
```

### Case 3: Large numRows

```
For large rows, intermediate products in nCr can get large
before the division brings them back down.

The long long in nCr handles this — long long can hold up
to ~9.2 × 10^18, enough for Pascal's Triangle values at
the constraints given by LeetCode (numRows ≤ 30). ✓
```

---

## Time Complexity

- **O(numRows²)** total
- Outer loop: numRows iterations
- Inner loop for row `i`: `i` iterations
- Each `nCr(i-1, j-1)` call: O(j) time
- Total work: sum over all rows of (row size × nCr cost per element)
- Approximately: O(1+2+...+numRows) = O(numRows²)

---

## Space Complexity

- **O(numRows²)** for the output
- The triangle itself has 1+2+...+numRows = numRows*(numRows+1)/2 elements
- Auxiliary extra space (excluding output): **O(1)**

---

## Key Insights

### Why Multiply then Divide (Not Precompute Factorials)?

```
Option A: Precompute n! then divide.
  Problem: n! overflows long long for n ≥ 21.
  C(20,10) = 184,756 — perfectly fine value.
  But 20! = 2,432,902,008,176,640,000 → barely fits long long.
  21! overflows. ❌

Option B: Incremental multiply-then-divide (this approach).
  Each intermediate result is a valid binomial coefficient.
  Binomial coefficients are much smaller than factorials.
  C(n,r) ≤ 2^n, while n! grows far faster.
  Stays safe for practical n values. ✓
```

### Alternative: Use the Row-by-Row Addition Property

```cpp
// Instead of nCr, build each row from the previous:
for (int i = 1; i <= numRows; i++) {
    vector<int> row(i, 1);
    for (int j = 1; j < i - 1; j++) {
        row[j] = ans[i-2][j-1] + ans[i-2][j];
    }
    ans.push_back(row);
}
```

```
Uses the identity: C(n,k) = C(n-1,k-1) + C(n-1,k)
(each inner element = sum of the two above it)

Advantages:
  - No multiplication needed, just addition
  - Naturally avoids overflow
  - O(numRows²) time, same complexity
  - Often slightly faster in practice (no division)

Disadvantage:
  - Requires access to the previous row
  - Both approaches are valid; pick the one you remember better
```

### Pascal's Triangle in Real Applications

```
Binomial coefficients C(n,r) appear in:
  → Probability theory (binomial distribution)
  → Combinatorics (choosing r items from n)
  → Polynomial expansion: (x+y)^n = sum of C(n,k) * x^k * y^(n-k)
  → Bit manipulation: counting set bits combinations
  → Dynamic programming: paths in a grid, coin change variants

Knowing Pascal's Triangle = knowing the building block
of all combinatorial mathematics. ✓
```

---

## References

- 🔗 [LeetCode 118 — Pascal's Triangle](https://leetcode.com/problems/pascals-triangle/)
- 🔗 [LeetCode 119 — Pascal's Triangle II (space-optimized, single row)](https://leetcode.com/problems/pascals-triangle-ii/)
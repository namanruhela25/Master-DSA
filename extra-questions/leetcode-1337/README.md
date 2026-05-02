# The K Weakest Rows in a Matrix 

**Problem Link:** https://leetcode.com/problems/the-k-weakest-rows-in-a-matrix/description/

## What is this Problem?

We have a **matrix of soldiers and civilians**. Each row represents either soldiers (1) or civilians (0), like: `[1,1,1,0,0,0]` - this means 3 soldiers then 3 civilians.

The **strength of a row** = **How many soldiers (1s) are in it**

We need to find the **k weakest rows** (rows with fewest soldiers) and return their **original row numbers**.

---

## The Problem Explained

### Example:
```
Matrix:
[1,1,1,0,0,0]   Row 0, strength = 3 soldiers
[1,0,0,0,0,0]   Row 1, strength = 1 soldier  ← 2nd weakest!
[1,1,0,0,0,0]   Row 2, strength = 2 soldiers
[0,0,0,0,0,0]   Row 3, strength = 0 soldiers ← Weakest!
[1,1,1,1,0,0]   Row 4, strength = 4 soldiers

k = 3

Sorted by weakness:
1. Row 3 (0 soldiers) ✓
2. Row 1 (1 soldier) ✓
3. Row 2 (2 soldiers) ✓

Answer: [3, 1, 2]
```

---

## HOOK TO REMEMBER FOREVER

### **"COUNT ONES, SORT, RETURN TOP K INDICES"**

Every time you see this problem:
- ✅ Count soldiers (1s) in each row = row strength
- ✅ Sort rows by weakness (ascending)
- ✅ Return the original indices of k weakest rows

**Remember: Rank soldiers by their count, pick weakest k soldiers' row numbers!** 👥

---

## Code Full Solution

```cpp
class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        int n = mat.size();      // Number of rows
        int m = mat[0].size();   // Number of columns
        
        // Add row index to each row
        for(int i=0; i<n; i++) {
            mat[i].push_back(i);
        }
        
        // Sort rows
        sort(mat.begin(), mat.end());
        
        // Get answer
        vector<int> ans;
        for(int i=0; i<k; i++) {
            ans.push_back(mat[i][m]);
        }
        
        return ans;
    }
};
```

---

## Code Explanation 💻

### Step 1: Setup

```cpp
int n = mat.size();      // How many rows total?
int m = mat[0].size();   // How many columns in each row?
```

- **`n`:** Number of rows (soldiers' units)
- **`m`:** Number of columns (soldiers per row)

**Example:** For a 4×6 matrix: n=4, m=6

### Step 2: Store Original Row Index

```cpp
for(int i=0; i<n; i++) {
    mat[i].push_back(i);
}
```

- **Why?** We need to return the **original row numbers**, not the sorted positions!
- **What it does:** Adds the row number to the END of each row

**Before:**
```
Row 0: [1, 1, 1, 0, 0, 0]
Row 1: [1, 0, 0, 0, 0, 0]
Row 2: [1, 1, 0, 0, 0, 0]
Row 3: [0, 0, 0, 0, 0, 0]
```

**After adding indices:**
```
Row 0: [1, 1, 1, 0, 0, 0, 0]  ← Added index 0
Row 1: [1, 0, 0, 0, 0, 0, 1]  ← Added index 1
Row 2: [1, 1, 0, 0, 0, 0, 2]  ← Added index 2
Row 3: [0, 0, 0, 0, 0, 0, 3]  ← Added index 3
```

### Step 3: Sort the Matrix

```cpp
sort(mat.begin(), mat.end());
```

- **Default vector sorting:** Compares element by element from LEFT to RIGHT
- **Automatically sorts by:**
  1. Number of 1s (strength) - smallest first
  2. If tied, by original row index - smallest first

**Example Trace:**
```
Before sort:
[1,1,1,0,0,0,0]  sum=3
[1,0,0,0,0,0,1]  sum=1  ← Fewest 1s!
[1,1,0,0,0,0,2]  sum=2
[0,0,0,0,0,0,3]  sum=0  ← Most 0s = Weakest!

After sort (compares element by element):
[0,0,0,0,0,0,3]  3 soldiers at end means index 3
[1,0,0,0,0,0,1]  1 soldier, so comes second
[1,1,0,0,0,0,2]  2 soldiers, comes third
[1,1,1,0,0,0,0]  3 soldiers, comes last
```

**The sorting magic:**
- Row with ALL 0s comes first (0 < 1)
- Row with mostly 0s comes next
- Row with mostly 1s comes last

### Step 4: Extract K Weakest Row Indices

```cpp
vector<int> ans;
for(int i=0; i<k; i++) {
    ans.push_back(mat[i][m]);
}
```

- **`mat[i]`:** The i-th row after sorting (it's sorted by weakness now!)
- **`mat[i][m]`:** The last element we added (the original index!)
- **Take first k rows:** These are the k weakest!

**Example with k=3:**
```
After sorting (weakness order):
mat[0] = [0,0,0,0,0,0,3]  → ans.push_back(mat[0][6]) = 3
mat[1] = [1,0,0,0,0,0,1]  → ans.push_back(mat[1][6]) = 1
mat[2] = [1,1,0,0,0,0,2]  → ans.push_back(mat[2][6]) = 2

Answer: [3, 1, 2]
```

---

## Complete Example Walkthrough

```
Input: 
mat = [[1,1,1,0,0,0],
       [1,0,0,0,0,0],
       [1,1,0,0,0,0],
       [0,0,0,0,0,0],
       [1,1,1,1,0,0]]
k = 3

Step 1: Add indices (m=6, so add to position 6)
[[1,1,1,0,0,0,0],
 [1,0,0,0,0,0,1],
 [1,1,0,0,0,0,2],
 [0,0,0,0,0,0,3],
 [1,1,1,1,0,0,4]]

Step 2: Sort (by consecutive 1s count, then index)
[[0,0,0,0,0,0,3],    ← 0 ones
 [1,0,0,0,0,0,1],    ← 1 one
 [1,1,0,0,0,0,2],    ← 2 ones
 [1,1,1,0,0,0,0],    ← 3 ones
 [1,1,1,1,0,0,4]]    ← 4 ones

Step 3: Take first k=3 and extract indices at position m=6
ans.push_back(mat[0][6]) = 3
ans.push_back(mat[1][6]) = 1
ans.push_back(mat[2][6]) = 2

Output: [3, 1, 2] ✓
```

---

## Why Does Sorting Work? 

**Vector Lexicographic Comparison:**

When C++ sorts vectors, it compares element-by-element:

```
[0,0,0,0,0,0,3] vs [1,0,0,0,0,0,1]
Compare index 0: 0 < 1? YES! 
So first row comes first. (No need to compare rest)

[1,0,0,0,0,0,1] vs [1,1,0,0,0,0,2]
Compare index 0: 1 = 1, continue
Compare index 1: 0 < 1? YES!
So [1,0,0...] comes before [1,1,0...]
```

This naturally sorts by soldier count (number of 1s)!

---

## Time Complexity

- **Adding indices:** O(n) - Add index to each row
- **Sorting:** O(n × m × log n) - Sort n rows, each comparison is O(m)
- **Extracting answer:** O(k)

**Total: O(n × m × log n)**

For a 100×100 matrix with k=4: Very fast! ✨

---

## Space Complexity

- **O(1)** - We modify the input matrix only (no extra space for result)
- Or **O(n)** if you count the space for adding indices

---

## Key Insight

**The clever trick:** Instead of manually counting 1s and storing strength separately, we let the sorting algorithm do it for us! By comparing row elements directly, it naturally sorts by soldier count! 🎯

**This is a classic technique:** Modify data → Sort → Extract what you need

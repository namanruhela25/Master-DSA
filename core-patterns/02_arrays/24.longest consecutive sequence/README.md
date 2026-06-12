# Longest Consecutive Sequence


## Problem Link
🔗 [Longest Consecutive Sequence - LeetCode](https://leetcode.com/problems/longest-consecutive-sequence/)


## What is This Problem?

Find the length of the **longest consecutive sequence** in an unsorted array. A consecutive sequence means numbers like `3, 4, 5, 6` (each number is exactly 1 more than the previous).

**Example:**
```
nums = [100, 4, 200, 1, 3, 2]
Output: 4

Explanation:
The longest consecutive sequence is [1, 2, 3, 4]
(Order doesn't matter in input; we find them)

Other sequences: [100] (length 1), [200] (length 1)
Maximum: 4
```

---

## The Problem Explained

Imagine you have puzzle pieces scattered on a table with numbers written on them. You want to find the longest chain where each piece's number is **exactly 1 more** than the previous piece's number.

**Naive approach:** Sort the array (O(n log n)) then scan for consecutive runs — still slow.

**Smart insight:** Use a **hash set** for O(1) lookups. For each number, check if `(number - 1)` exists. If not, this number **starts** a new sequence. Count from here to find the full length. If `(number - 1)` exists, skip it — the sequence was already counted starting from the earlier number.

---

## Hook to Remember

**"SKIP IF PREDECESSOR EXISTS, ELSE COUNT FROM HERE"**

- Convert array to unordered_set (O(1) lookup)
- For each number: if `(num - 1)` doesn't exist, it's a sequence start
- Count forward: check `num`, `num+1`, `num+2`, ... until gap
- Track maximum length

**Why O(n) and not O(n²)?** Each number is counted only once as a **start** of a sequence, not repeatedly from every position.

---

## Step-by-Step Walkthrough

Given: `nums = [100, 4, 200, 1, 3, 2]`

```
Step 1: Build set
  mpp = {100, 4, 200, 1, 3, 2}

Step 2: Iterate through set (order arbitrary in unordered_set)
  
  num=100:
    Is (100-1=99) in set? NO → 100 is a sequence start
    Count: 100 → 101? NO → len=1
    ans = max(0, 1) = 1

  num=4:
    Is (4-1=3) in set? YES → skip (already counted from 3)

  num=200:
    Is (200-1=199) in set? NO → 200 is a sequence start
    Count: 200 → 201? NO → len=1
    ans = max(1, 1) = 1

  num=1:
    Is (1-1=0) in set? NO → 1 is a sequence start
    Count: 1 → 2 exists? YES → 2+1=3 exists? YES → 3+1=4 exists? YES → 4+1=5 exists? NO
    len = 4
    ans = max(1, 4) = 4

  num=3:
    Is (3-1=2) in set? YES → skip (already counted from 1)

  num=2:
    Is (2-1=1) in set? YES → skip (already counted from 1)

Final: ans = 4 ✓
```

---

## Full Code + Line-by-Line Explanation

```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> mpp(nums.begin(), nums.end());
        // Convert array to unordered_set for O(1) lookups
        // Automatically removes duplicates (e.g., [1,1,1,2] → {1,2})

        int ans = 0;
        for(int num : mpp) {  // Loop through set (order doesn't matter)
            if(mpp.find(num - 1) == mpp.end()) {  
                // If predecessor doesn't exist, num is a sequence START
                // We skip numbers that aren't starts to avoid redundant counts

                int len = 1;  // At least num itself
                while(mpp.find(num + len) != mpp.end()) {
                    // Keep incrementing len while consecutive numbers exist
                    // num, num+1, num+2, ... until we hit a gap
                    len++;
                }
                ans = max(ans, len);  // Track longest sequence found
            }
        }
        return ans;
    }
};
```

### Line-by-Line Breakdown:

| Line | Why |
|------|-----|
| `unordered_set<int> mpp(...)` | O(1) average lookup. Duplicates are automatically removed |
| `for(int num : mpp)` | Iterate through set. Order is arbitrary but doesn't matter |
| `if(mpp.find(num-1)==mpp.end())` | Check if predecessor exists. If NOT, num is a sequence start |
| `int len = 1;` | Initialize length (num itself counts as 1) |
| `while(mpp.find(num+len)!=mpp.end())` | Count consecutive numbers forward: num, num+1, num+2, ... |
| `len++` | Extend sequence by 1 |
| `ans = max(ans, len)` | Update maximum length |

---

## Code Traces

### Trace 1: Mixed Unsorted Array
```
nums = [100, 4, 200, 1, 3, 2]
Expected: 4  ([1, 2, 3, 4])

mpp = {100, 4, 200, 1, 3, 2}

num=100: (99 exists?) NO → len=1, ans=1
num=4: (3 exists?) YES → skip
num=200: (199 exists?) NO → len=1, ans=1
num=1: (0 exists?) NO → check 2,3,4,5... → 2✓,3✓,4✓,5✗ → len=4, ans=4
num=3: (2 exists?) YES → skip
num=2: (1 exists?) YES → skip

Output: 4 ✓
```

### Trace 2: Consecutive from Start
```
nums = [1, 2, 3, 4, 5]
Expected: 5

mpp = {1, 2, 3, 4, 5}

num=1: (0 exists?) NO → count 2,3,4,5,6... → 2✓,3✓,4✓,5✓,6✗ → len=5, ans=5
num=2: (1 exists?) YES → skip
num=3: (2 exists?) YES → skip
num=4: (3 exists?) YES → skip
num=5: (4 exists?) YES → skip

Output: 5 ✓
```

### Trace 3: Duplicates in Input
```
nums = [99, 1, 1, 2, 2, 3, 3]
Expected: 3  ([1, 2, 3])

mpp = {99, 1, 2, 3}  (duplicates removed)

num=99: (98 exists?) NO → len=1, ans=1
num=1: (0 exists?) NO → count 2,3,4... → 2✓,3✓,4✗ → len=3, ans=3
num=2: (1 exists?) YES → skip
num=3: (2 exists?) YES → skip

Output: 3 ✓
```

### Trace 4: Multiple Separate Sequences
```
nums = [1, 2, 10, 11, 12]
Expected: 3  ([10, 11, 12])

mpp = {1, 2, 10, 11, 12}

num=1: (0 exists?) NO → count 2,3... → 2✓,3✗ → len=2, ans=2
num=2: (1 exists?) YES → skip
num=10: (9 exists?) NO → count 11,12,13... → 11✓,12✓,13✗ → len=3, ans=3
num=11: (10 exists?) YES → skip
num=12: (11 exists?) YES → skip

Output: 3 ✓
```

### Trace 5: All Isolated (No Sequences)
```
nums = [10, 20, 30, 40]
Expected: 1

mpp = {10, 20, 30, 40}

num=10: (9 exists?) NO → count 11... → 11✗ → len=1, ans=1
num=20: (19 exists?) NO → count 21... → 21✗ → len=1, ans=1
num=30: (29 exists?) NO → count 31... → 31✗ → len=1, ans=1
num=40: (39 exists?) NO → count 41... → 41✗ → len=1, ans=1

Output: 1 ✓
```

### Trace 6: Single Element
```
nums = [5]
Expected: 1

mpp = {5}

num=5: (4 exists?) NO → count 6... → 6✗ → len=1, ans=1

Output: 1 ✓
```

---

## Edge Cases

| Case | Input | Output | Why |
|------|-------|--------|-----|
| Empty array | `[]` | `0` | No elements → ans stays 0 |
| Single element | `[42]` | `1` | One element is always a sequence of length 1 |
| All isolated | `[10,20,30]` | `1` | No consecutive pairs → each is its own sequence |
| All duplicates | `[5,5,5,5]` | `1` | Set becomes {5} → one sequence of length 1 |
| Consecutive sequence | `[1,2,3,4,5]` | `5` | Perfect sequence from start to end |
| Multiple sequences | `[1,2,10,11,12]` | `3` | [1,2] and [10,11,12]; max is 3 |
| Negative numbers | `[-3,-2,-1,0,1]` | `5` | Works with negatives; one sequence |
| Gaps | `[1,3,5,7,9]` | `1` | All isolated, no consecutive pairs |
| Reverse order duplicate | `[5,4,3,2,1]` | `5` | Order in input doesn't matter |

---

## Time & Space Complexity

| Metric | Complexity | Reasoning |
|--------|-----------|-----------|
| **Time** | **O(n)** | Building set: O(n). Each number is examined as a sequence start at most once. Worst case: n sequence starts → n + (n-1) + ... + 1 checks, but amortized to O(n) total because each element in mpp is visited only once across all "while" iterations combined |
| **Space** | **O(n)** | Unordered_set stores all unique elements; worst case n if all unique |

**Why O(n) and not O(n²)?**
- Naive approach: For each number, check all neighbors → O(n²)
- This approach: Each number is counted exactly once as part of exactly one sequence → O(n) total across all iterations

**Proof by example:** `nums = [1,2,3,4,5]`
- Naive: (1 checks 5 neighbors) + (2 checks 3 neighbors) + ... = 5+4+3+2+1 = 15 checks
- Optimal: 1 starts sequence, counts 1→2→3→4→5 = 5 checks total (2,3,4,5 skip)

---

## Key Insights

### 1. **Why Check for Predecessor (`num - 1`)?**
The core optimization. Skip any number that has a predecessor in the set:
```cpp
if(mpp.find(num - 1) == mpp.end())  // Only process sequence STARTS
```
**Example:** `{1, 2, 3, 4}`
- Check 1: no 0 → process (find 1→2→3→4, len=4)
- Check 2: has 1 → skip (already counted)
- Check 3: has 2 → skip (already counted)
- Check 4: has 3 → skip (already counted)

Count each element once, not once per sequence it's in.

### 2. **Why Unordered_Set and Not Sorted Array?**

| Approach | Time | Reasoning |
|----------|------|-----------|
| Sort then scan | O(n log n) | Sorting dominates |
| Hash set (this) | O(n) | O(1) lookups; single pass optimal |

### 3. **Duplicates Are Automatically Handled**
```cpp
unordered_set<int> mpp(nums.begin(), nums.end());
// Set constructor removes duplicates automatically
// [1, 1, 2, 2, 3] → {1, 2, 3}
```
No special duplicate-removal logic needed.

### 4. **Order in the Set Doesn't Matter**
Unordered_set iteration order is arbitrary. It doesn't matter if we process 100 before 1:
- `num=100`: predecessor 99 missing → len=1
- `num=1`: predecessor 0 missing → len=4

Both correctly identify their sequence starts regardless of iteration order.

### 5. **The `while` Loop Counts Forward**
```cpp
int len = 1;
while(mpp.find(num + len) != mpp.end()) {
    len++;
}
```
This checks `num, num+len` where `len` is the **offset**, not the next number:
- Check `num + 1`: does 101 exist?
- Check `num + 2`: does 102 exist?
- Check `num + 3`: does 103 exist? NO → stop

Important: It's looking at **offset from num**, not the actual next value.

---

## Common Mistakes

❌ **Sorting the array**
- Works but O(n log n); loses O(n) optimization
- For large n, sorting is unnecessary bottleneck

❌ **Not checking for predecessor; processing every number**
```cpp
// WRONG:
for(int num : mpp) {
    int len = 1;
    while(mpp.find(num + len) != mpp.end()) len++;
    ans = max(ans, len);  // Counts [1,2,3] from 1, 2, AND 3 — redundant
}
```
Result: O(n²) in worst case (consecutive array).

❌ **Using `vector` instead of unordered_set**
```cpp
// WRONG:
vector<int> mpp(nums.begin(), nums.end());
sort(mpp.begin(), mpp.end());
// Now O(n log n) instead of O(n)
```

❌ **Forgetting duplicates in input**
```cpp
nums = [1, 1, 1, 2]
// If using linear search: might count 1 three times
// Set handles this: {1, 2} → one sequence of length 2
```

---

## Generalization & Related Problems

**Same core pattern (hash set + optimization):**
- **Max Points on a Line** — use slopes with hash map
- **Two Sum** — hash set for complement lookup
- **Shortest Word Distance** — hash map for indices

**Related consecutive problems:**
- **Maximum Gap** — find max gap between consecutive sorted elements
- **Increasing Triplet Subsequence** — O(n) without sorting
- **Longest Increasing Subsequence** — different (not necessarily consecutive)


## Complexity Summary Table

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Naive (double loop) | O(n²) | O(1) | Check each against all others |
| Sort + scan | O(n log n) | O(1) or O(n) | Sorts out the ordering requirement |
| Hash set (optimal) | **O(n)** | **O(n)** | This solution; best for LeetCode |

---

## References

- [Longest Consecutive Sequence - LeetCode](https://leetcode.com/problems/longest-consecutive-sequence/)

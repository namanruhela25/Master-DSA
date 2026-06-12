# Array Leaders

## What is This Problem?

Find all elements in an array that are **greater than all elements to their right**. These elements are called "leaders" because they "lead" (dominate) everything that comes after them.

**Example:**
```
arr = [16, 17, 4, 3, 5, 2]
Output: [17, 5, 2]

Explanation:
- 16: Has 17 to the right, so NOT a leader
- 17: Nothing to the right is greater, so 17 IS a leader
- 4: Has 5 to the right, so NOT a leader
- 3: Only 2 to the right, 3 > 2, so 3 IS a leader... 
  Wait, but output shows 5, not 3? Let me recalculate.
- Actually: 16 < 17 (not leader), 17 > all ✓, 4 < 5 (not leader), 
  3 < 5 (wait, 5 is to the right of 3), no 5 is AFTER 4, then 3. So right of 3 is [5,2]. 3 < 5, not leader.
  5 > 2 ✓ (leader), 2 > nothing (leader)
  
Final: [17, 5, 2] ✓
```

---

## The Problem Explained

Imagine you're standing in a line of people, each with a height written on their shirt. A person is a "leader" if everyone in front of them (standing further right, facing you) is shorter.

The **naive approach** checks each element against all elements to its right — O(n²).

The **smart insight**: Scan **right to left**. Keep track of the maximum seen so far from the right. If the current element is ≥ the max-so-far, it's a leader **and becomes the new max-so-far** for all elements to its left.

---

## Hook to Remember

**"RIGHT TO LEFT, KEEP THE MAX, LEADERS EMERGE"**

- Scan right to left
- Track `lastMaximum`
- If `arr[i] >= lastMaximum` → element is a leader
- Update `lastMaximum = arr[i]`
- Reverse result at the end (collected in reverse order naturally)

**Why this works:** The rightmost element is always a leader (nothing to its right). Everything left of it can check against the max of all its right neighbors instantly.

---

## Step-by-Step Walkthrough

Given: `arr = [16, 17, 4, 3, 5, 2]`

```
Step 1: Start from right (i=5)
  arr[5]=2, lastMaximum=INT_MIN
  2 >= INT_MIN? YES → ans=[2], lastMaximum=2

Step 2: i=4
  arr[4]=5, lastMaximum=2
  5 >= 2? YES → ans=[2,5], lastMaximum=5

Step 3: i=3
  arr[3]=3, lastMaximum=5
  3 >= 5? NO → skip, lastMaximum stays 5

Step 4: i=2
  arr[2]=4, lastMaximum=5
  4 >= 5? NO → skip, lastMaximum stays 5

Step 5: i=1
  arr[1]=17, lastMaximum=5
  17 >= 5? YES → ans=[2,5,17], lastMaximum=17

Step 6: i=0
  arr[0]=16, lastMaximum=17
  16 >= 17? NO → skip, lastMaximum stays 17

Final: ans=[2,5,17] → reverse → [17,5,2] ✓
```

---

## Full Code + Line-by-Line Explanation

```cpp
class Solution {
  public:
    vector<int> leaders(vector<int>& arr) {
        // code here
        int n = arr.size();
        
        int lastMaximum = INT_MIN;           // Track max from right so far
        vector<int> ans;
        
        for(int i=n-1; i>=0; i--) {          // Scan RIGHT TO LEFT
            if(lastMaximum <= arr[i]) {      // Current element >= all its right neighbors?
                lastMaximum = arr[i];        // It's a leader, update max
                ans.push_back(lastMaximum);  // Add to result
            }
        }
        
        reverse(ans.begin(), ans.end());     // Collected in reverse order, flip to original
        return ans;
    }
};
```

### Line-by-Line Breakdown:

| Line | Why |
|------|-----|
| `int n = arr.size();` | Store size once (efficiency) |
| `int lastMaximum = INT_MIN;` | Initialize to minimum so first element always qualifies (rightmost is always a leader) |
| `for(int i=n-1; i>=0; i--)` | Right-to-left scan — each element checks against max of its right neighbors |
| `if(lastMaximum <= arr[i])` | Using `<=` means equal elements are both leaders (e.g., `[5,5,3]` → both 5s are leaders) |
| `lastMaximum = arr[i];` | Update max for next iteration (upcoming elements checking from left) |
| `ans.push_back(lastMaximum);` | Add leader to result |
| `reverse(ans.begin(), ans.end());` | Result is built in reverse (right-to-left), flip it back to left-to-right |

---

## Code Traces

### Trace 1: Simple Decreasing
```
arr = [10, 7, 5, 3, 1]
Expected: [10, 7, 5, 3, 1]  (all leaders, decreasing means each > all right)

i=4: 1 >= INT_MIN? YES → ans=[1], max=1
i=3: 3 >= 1? YES → ans=[1,3], max=3
i=2: 5 >= 3? YES → ans=[1,3,5], max=5
i=1: 7 >= 5? YES → ans=[1,3,5,7], max=7
i=0: 10 >= 7? YES → ans=[1,3,5,7,10], max=10

Reverse → [10, 7, 5, 3, 1] ✓
```

### Trace 2: Mixed with Duplicates
```
arr = [16, 17, 4, 3, 5, 2]
Expected: [17, 5, 2]

i=5: 2 >= INT_MIN? YES → ans=[2], max=2
i=4: 5 >= 2? YES → ans=[2,5], max=5
i=3: 3 >= 5? NO → skip
i=2: 4 >= 5? NO → skip
i=1: 17 >= 5? YES → ans=[2,5,17], max=17
i=0: 16 >= 17? NO → skip

Reverse → [17, 5, 2] ✓
```

### Trace 3: All Same Elements
```
arr = [5, 5, 5, 5]
Expected: [5, 5, 5, 5]  (all equal to max-so-far)

i=3: 5 >= INT_MIN? YES → ans=[5], max=5
i=2: 5 >= 5? YES → ans=[5,5], max=5  (note: <= includes equality)
i=1: 5 >= 5? YES → ans=[5,5,5], max=5
i=0: 5 >= 5? YES → ans=[5,5,5,5], max=5

Reverse → [5, 5, 5, 5] ✓
```

### Trace 4: Strictly Increasing
```
arr = [1, 2, 3, 4, 5]
Expected: [5]  (only last is leader)

i=4: 5 >= INT_MIN? YES → ans=[5], max=5
i=3: 4 >= 5? NO → skip
i=2: 3 >= 5? NO → skip
i=1: 2 >= 5? NO → skip
i=0: 1 >= 5? NO → skip

Reverse → [5] ✓
```

### Trace 5: Single Element
```
arr = [42]
Expected: [42]  (always a leader)

i=0: 42 >= INT_MIN? YES → ans=[42], max=42

Reverse → [42] ✓
```

### Trace 6: Two Elements, Second Larger
```
arr = [3, 10]
Expected: [10]

i=1: 10 >= INT_MIN? YES → ans=[10], max=10
i=0: 3 >= 10? NO → skip

Reverse → [10] ✓
```

---

## Edge Cases

| Case | Input | Output | Why |
|------|-------|--------|-----|
| Single element | `[5]` | `[5]` | Rightmost always leads |
| All increasing | `[1,2,3,4,5]` | `[5]` | Only last > all right |
| All decreasing | `[5,4,3,2,1]` | `[5,4,3,2,1]` | All > everything right |
| All identical | `[7,7,7,7]` | `[7,7,7,7]` | `<=` includes equality |
| Two elements equal | `[10,10]` | `[10,10]` | Both qualify via `<=` |
| Alternating | `[1,10,2,9,3]` | `[10,9,3]` | Max from right rules |
| Plateau then drop | `[5,5,5,2,2]` | `[5,5,5,2,2]` | First 5s beat all right |

---

## Time & Space Complexity

| Metric | Complexity | Reasoning |
|--------|-----------|-----------|
| **Time** | **O(n)** | Single pass right-to-left: `for` loop O(n) + `reverse` O(n) = O(n) |
| **Space** | **O(k)** | `ans` stores k leaders. In worst case (decreasing array), k=n, so O(n). In best case (increasing), k=1, so O(1). Not counting output, only auxiliary. |

**vs. Naive O(n²) approach:**
- Naive: Every element checks all right neighbors = n + (n-1) + ... + 1 = n(n+1)/2 comparisons
- Optimized: One pass, one max value = n comparisons
- **For n=10⁵: 10¹⁰ vs 10⁵ operations** — 100,000x faster

---

## Key Insights

### 1. **Right-to-Left is Essential**
The algorithm only works scanning right-to-left because:
- Rightmost element is automatically a leader (nothing to compare)
- Next element immediately knows the max of its right neighbor
- This cascades left, building max as we go

Scanning left-to-right requires looking ahead (harder) or preprocessing (defeats the purpose).

### 2. **Why `<=` and Not `<`?**
```cpp
if(lastMaximum <= arr[i])  // Correct: includes equal elements
```
- With `<=`: `[5, 5, 2]` → both 5s are leaders (both >= all right)
- With `<`: `[5, 5, 2]` → only last 5 is leader (first 5 not > second 5)

Most problem statements use `>=`, so `<=` is the right check. Verify problem wording for your specific case.

### 3. **Why Reverse at the End?**
- Leaders collected in reverse order naturally (right-to-left scan)
- Output should be left-to-right order (index 0 leftmost)
- One `reverse()` call flips the order

### 4. **INT_MIN Initialization**
- Guarantees rightmost element qualifies (any arr value > INT_MIN)
- No special-case handling needed
- Works even if array contains negative numbers

### 5. **Relationship to Other Problems**
- **Next Greater Element (NGE):** Finds next larger to the right; this finds all larger to the right
- **Monotonic Stack Pattern:** Similar to NGE but simpler (greedy + variable vs. stack)
- **Trapping Rain Water:** Uses max-so-far concept but bidirectional


## References

- [GeeksforGeeks Array Leaders](https://www.geeksforgeeks.org/problems/missing-number-in-array1416/1)


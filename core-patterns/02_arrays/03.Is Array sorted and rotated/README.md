# Check If Array Is Sorted and Rotated

**Problem Link:** https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/

## What is this Problem?

We have an **array that was originally sorted** (like [1,2,3,4,5]). Then someone **rotated it** (moved elements from end to beginning).

Now we need to check: **Is this array a rotated version of a sorted array?**

**Examples:**
```
Array: [3, 4, 5, 1, 2]
Original sorted: [1, 2, 3, 4, 5]
Rotated by 3 positions? YES ✓

Array: [2, 1, 3, 4]
Can this be rotated sorted? NO ✗
(Wrong order, can't fix by rotation)
```

---

## The Problem Explained

Think of a **circular train track**:

```
Original: 1 → 2 → 3 → 4 → 5 (circular - ends connect to start)

Rotate by 3 stops:
Pick up at position 3 (value 3) and move to front:
3 → 4 → 5 → 1 → 2

New train arrangement: [3, 4, 5, 1, 2] ✓
(Still sorted circularly, just different starting point!)
```

**Key insight:** A rotated sorted array has:
- One part that increases normally
- Then ONE "break" where it drops
- Then continues increasing from there

---

## HOOK TO REMEMBER FOREVER

**"COUNT THE BREAKS - ONE BREAK MEANS ROTATED SORTED"**

Every time you see this problem:
- ✅ Count places where element is greater than next element (drops/breaks)
- ✅ Also check if last element is greater than first (circular check)
- ✅ If total breaks/violations <= 1, it's a rotated sorted array!
- ✅ If breaks > 1, it's just a shuffled array

**Remember: Broken chain in exactly one place = Rotated sorted!** 🔄

---

## How It Works Step By Step

### Example 1: Rotated Sorted `[3, 4, 5, 1, 2]`

**Visualize the breaks:**
```
Array: [3, 4, 5, 1, 2]

Position 0→1: 3→4  (3 < 4) ✓ increase
Position 1→2: 4→5  (4 < 5) ✓ increase
Position 2→3: 5→1  (5 > 1) ✗ BREAK! count=1
Position 3→4: 1→2  (1 < 2) ✓ increase
Last→First: 2→3   (2 < 3) ✓ no violation

Total breaks: 1 ✓
Answer: TRUE (rotated sorted!)
```

### Example 2: Not Rotated Sorted `[2, 1, 3, 4]`

**Visualize the breaks:**
```
Array: [2, 1, 3, 4]

Position 0→1: 2→1  (2 > 1) ✗ BREAK! count=1
Position 1→2: 1→3  (1 < 3) ✓ increase
Position 2→3: 3→4  (3 < 4) ✓ increase
Last→First: 4→2   (4 > 2) ✗ BREAK! count=2

Total breaks: 2 ✗
Answer: FALSE (too many breaks!)
```

---

## Code Full Solution

```cpp
class Solution {
public:
    bool check(vector<int>& nums) {
        int n = nums.size();
        int count = 0;
        
        // Count breaks in increasing order
        for (int i = 1; i < n; i++) {
            if (nums[i - 1] > nums[i]) {    // Break found!
                count++;
            }
        }
        
        // Check if last element breaks back to first
        if (nums[n - 1] > nums[0]) {
            count++;
        }
        
        // Rotated sorted has at most 1 break
        return count <= 1;
    }
};
```

---

## Code Explanation

### Initialize Counter

```cpp
int n = nums.size();
int count = 0;
```

- **`n`:** Array size
- **`count`:** Will track how many "breaks" we find
  - Break = element greater than next element (decreasing instead of increasing)

---

### Count Breaks in Array

```cpp
for (int i = 1; i < n; i++) {
    if (nums[i - 1] > nums[i]) {
        count++;
    }
}
```

- **Loop through:** From index 1 to n-1
- **Check condition:** Is previous element > current element?
  - YES → This is a break (should be increasing but it's decreasing)
  - NO → Normal increasing order

**Example with [3, 4, 5, 1, 2]:**
```
i=1: nums[0]=3 > nums[1]=4? 3 > 4? NO
i=2: nums[1]=4 > nums[2]=5? 4 > 5? NO
i=3: nums[2]=5 > nums[3]=1? 5 > 1? YES → count=1
i=4: nums[3]=1 > nums[4]=2? 1 > 2? NO
```

---

### Check Circular Constraint

```cpp
if (nums[n - 1] > nums[0]) {
    count++;
}
```

- **Why?** Array is circular - last connects to first
- **Check:** Is last element > first element?
  - YES → This violates sorted order (count++)
  - NO → Last < first (good for rotation)

**Example with [3, 4, 5, 1, 2]:**
```
last = nums[4] = 2
first = nums[0] = 3
2 > 3? NO
(This is correct for rotated sorted!)
```

**Why this test?**
```
If originally [1, 2, 3, 4, 5] was rotated to [3, 4, 5, 1, 2]:
- New first (3) must be > new last (2)? NO
- Actually last (2) < first (3) ✓

A properly rotated sorted array must have last < first!
```

---

### Final Check

```cpp
return count <= 1;
```

- **If breaks = 0:** Array wasn't rotated (already sorted)
- **If breaks = 1:** Array was rotated exactly once (perfect!)
- **If breaks > 1:** Too many violations (not a rotation)

**Logic:**
```
Sorted array [1,2,3,4,5]:
- Breaks = 0 ✓ (0 <= 1)

Rotated [3,4,5,1,2]:
- Breaks = 1 ✓ (1 <= 1)

Shuffled [2,1,3,4]:
- Breaks = 2 ✗ (2 > 1)
```

---

## Complete Example Traces

### Trace 1: Regular Sorted (Not Rotated)

```
Array: [1, 2, 3, 4, 5], n=5

Loop (i=1 to 4):
  i=1: 1 > 2? NO
  i=2: 2 > 3? NO
  i=3: 3 > 4? NO
  i=4: 4 > 5? NO
count = 0

Circular check:
  nums[4]=5 > nums[0]=1? YES → count=1

Return: count <= 1? 1 <= 1? YES ✓
(Sorted arrays return true - they're "rotated" by 0)
```

### Trace 2: Rotated Once (Rotation at End)

```
Array: [3, 4, 5, 1, 2], n=5

Loop (i=1 to 4):
  i=1: 3 > 4? NO
  i=2: 4 > 5? NO
  i=3: 5 > 1? YES → count=1
  i=4: 1 > 2? NO
count = 1

Circular check:
  nums[4]=2 > nums[0]=3? NO

Return: count <= 1? 1 <= 1? YES ✓
```

### Trace 3: Not Rotated (Shuffled)

```
Array: [2, 1, 3, 4], n=4

Loop (i=1 to 3):
  i=1: 2 > 1? YES → count=1
  i=2: 1 > 3? NO
  i=3: 3 > 4? NO
count = 1

Circular check:
  nums[3]=4 > nums[0]=2? YES → count=2

Return: count <= 1? 2 <= 1? NO ✗
```

### Trace 4: Rotated at Beginning

```
Array: [4, 5, 1, 2, 3], n=5

Loop (i=1 to 4):
  i=1: 4 > 5? NO
  i=2: 5 > 1? YES → count=1
  i=3: 1 > 2? NO
  i=4: 2 > 3? NO
count = 1

Circular check:
  nums[4]=3 > nums[0]=4? NO

Return: count <= 1? 1 <= 1? YES ✓
```

### Trace 5: Single Element

```
Array: [5], n=1

Loop (i=1 to 0):
  No iterations

Circular check:
  nums[0]=5 > nums[0]=5? NO

Return: count <= 1? 0 <= 1? YES ✓
```

### Trace 6: Two Elements Rotated

```
Array: [2, 1], n=2

Loop (i=1 to 1):
  i=1: 2 > 1? YES → count=1
count = 1

Circular check:
  nums[1]=1 > nums[0]=2? NO

Return: count <= 1? 1 <= 1? YES ✓
```

---

## Edge Cases

### Case 1: Already Sorted (No Rotation)

```
Array: [1, 2, 3, 4, 5]
Breaks in body: 0
Last > First: 5 > 1? YES → count=1
Return: true ✓
(No rotation is valid!)
```

### Case 2: Rotated Multiple Times

```
Array: [5, 1, 2, 3, 4]
Only value where break happens: 5→1
Breaks in body: 1
Last > First: 4 > 5? NO
Return: true ✓
(Multiple full rotations still look like one rotation)
```

### Case 3: Duplicates

```
Array: [3, 4, 4, 5, 1, 2]
Breaks: 5→1 gives count=1
Last > First: 2 > 3? NO
Return: true ✓
(Duplicates allowed!)
```

### Case 4: Completely Wrong Order

```
Array: [5, 3, 1, 4, 2]
Breaks: 5→3 (count=1), 3→1 (count=2), 4→2 (count=3)
Last > First: 2 > 5? NO (count still 3)
Return: false ✗
```

### Case 5: Two Elements

```
Array: [2, 1]
Breaks: 2→1 (count=1)
Last > First: 1 > 2? NO
Return: true ✓
```

---

## Time Complexity

- **O(n)** where n = array size
- Single loop through entire array
- Each comparison is O(1)

---

## Space Complexity

- **O(1)** - Only using variable `count`
- No extra arrays or data structures

---

## Key Insights

### Why One Break Means Rotation

```
Sorted array always increases:
[1, 2, 3, 4, 5]

When you rotate at position k:
- Elements [1...k] go to the end
- Elements [k+1...n] come to front
- Creates exactly ONE break point (where last part drops to first part)

[3, 4, 5, 1, 2]
       ↑
     ONE break from 5→1
```

### The Circular Check is Key

```
Normal array:
[1, 2, 3, 4, 5]
None of this wraps around

Rotated array:
[3, 4, 5, 1, 2]
This IS like: ...5, 3, 4, 5, 1, 2, 3...
Last (2) should flow back to first (3)
So last should NOT be > first!
```

### Why Count <= 1 (Not Exactly 1)

```
Unrotated sorted [1,2,3,4,5]: breaks=0 ← Still valid!
Rotated [3,4,5,1,2]: breaks=1   ← Valid!
Shuffled [2,1,3,4]: breaks=2+   ← Invalid!
```

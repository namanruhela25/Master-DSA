# Sort Integers By The Number Of 1 Bits 

**Problem Link:** https://leetcode.com/problems/sort-integers-by-the-number-of-1-bits

## What is this Problem?

Every number has a **binary representation** (made of 0s and 1s). For example:
- 5 = 0101 in binary = has **2 ones** 🔴🔴
- 2 = 0010 in binary = has **1 one** 🔴
- 3 = 0011 in binary = has **2 ones** 🔴🔴

We need to **sort the array** by:
1. **Primary:** Count of 1s in binary (ascending)
2. **Secondary:** If tied, sort by value (ascending)

---

## The Problem Explained 

### Example:
```
Input: [0, 1, 2, 3, 4, 5, 6, 7, 8]

Binary representations and bit counts:
0 = 0000 → 0 ones
1 = 0001 → 1 one  ✓
2 = 0010 → 1 one  ✓
3 = 0011 → 2 ones  ✓✓
4 = 0100 → 1 one  ✓
5 = 0101 → 2 ones  ✓✓
6 = 0110 → 2 ones  ✓✓
7 = 0111 → 3 ones  ✓✓✓
8 = 1000 → 1 one  ✓

Sort by bit count (tie-break by value):
0 (0 ones)
1, 2, 4, 8 (1 one each, sorted by value)
3, 5, 6 (2 ones each, sorted by value)
7 (3 ones)

Output: [0, 1, 2, 4, 8, 3, 5, 6, 7]
```

---

## HOOK TO REMEMBER FOREVER

### **"COUNT ONES IN BINARY, SORT BY COUNT, TIE-BREAK BY VALUE"**

Every time you see this problem:
- ✅ Convert each number to binary
- ✅ Count the 1s in binary representation
- ✅ Sort: first by bit count (low to high)
- ✅ If counts equal: sort by value (low to high)

**Remember: Binary 1s counter → Primary sort key!** 💡

---

## How It Works Step By Step 

### Example: Sort `[6, 2, 5, 3]`

**Show Binary:**
```
6 = 0110 = 2 ones
2 = 0010 = 1 one
5 = 0101 = 2 ones
3 = 0011 = 2 ones
```

**Group by bit count:**
```
1 one:   [2]
2 ones:  [6, 5, 3]
```

**Sort within each group by value:**
```
1 one:   [2]
2 ones:  [3, 5, 6]  (3 < 5 < 6)
```

**Final answer:**
```
[2, 3, 5, 6]
```

---

## Code Full Solution

```cpp
class Solution {
public:
    static bool cmp(int a, int b) {
        int a_bitcount = __builtin_popcount(a);
        int b_bitcount = __builtin_popcount(b);
        
        if(a_bitcount == b_bitcount) {
            return a < b;  // Same bit count? Sort by value
        }
        return a_bitcount < b_bitcount;  // Sort by bit count
    }
    
    vector<int> sortByBits(vector<int>& arr) {
        sort(arr.begin(), arr.end(), cmp);
        return arr;
    }
};
```

---

## Code Explanation 

### What is `__builtin_popcount()`?

```cpp
int a_bitcount = __builtin_popcount(a);
```

- **`__builtin_popcount(a)`:** Built-in C++ function
- **What it does:** Counts how many 1s are in the binary representation
- **Returns:** Integer count of 1 bits

**Examples:**
```
__builtin_popcount(0)   = 0      (0000 = 0 ones)
__builtin_popcount(1)   = 1      (0001 = 1 one)
__builtin_popcount(3)   = 2      (0011 = 2 ones)
__builtin_popcount(6)   = 2      (0110 = 2 ones)
__builtin_popcount(7)   = 3      (0111 = 3 ones)
__builtin_popcount(15)  = 4      (1111 = 4 ones)
```

### Comparator Function

```cpp
static bool cmp(int a, int b) {
```

- This is a **custom comparator** for the sort function
- Returns `true` if `a` should come before `b`
- Returns `false` otherwise

### Step 1: Count 1 bits in both numbers

```cpp
    int a_bitcount = __builtin_popcount(a);
    int b_bitcount = __builtin_popcount(b);
```

- Get bit count for number `a`
- Get bit count for number `b`

**Example:**
```
a = 6 (binary 0110) → a_bitcount = 2
b = 3 (binary 0011) → b_bitcount = 2
```

### Step 2: Check if bit counts are equal

```cpp
    if(a_bitcount == b_bitcount) {
        return a < b;
    }
```

- **If bit counts are the same:** Sort by value (ascending)
- **`a < b` means:** Put smaller value first

**Example:**
```
a = 5 (binary 0101, 2 ones)
b = 6 (binary 0110, 2 ones)

Same bit count (both 2)
5 < 6? YES, so a comes before b
Result: 5 before 6 ✓
```

### Step 3: Sort by bit count (if not equal)

```cpp
    return a_bitcount < b_bitcount;
```

- **If bit counts are different:** Sort by bit count (ascending)
- **`a_bitcount < b_bitcount` means:** Put number with fewer 1s first

**Example:**
```
a = 2 (binary 0010, 1 one)
b = 3 (binary 0011, 2 ones)

1 < 2? YES, so a comes before b
Result: 2 before 3 ✓
```

### Sort Using Custom Comparator

```cpp
vector<int> sortByBits(vector<int>& arr) {
    sort(arr.begin(), arr.end(), cmp);
    return arr;
}
```

- **`sort(arr.begin(), arr.end(), cmp)`:** Sort array using our comparator
- The comparator is called many times to decide element order
- Elements sorted according to our rules!

---

## Complete Example Trace

```
Input: [0, 1, 2, 3, 4, 5, 6, 7, 8]

Calculate bit counts:
0 → 0 ones
1 → 1 one
2 → 1 one
3 → 2 ones
4 → 1 one
5 → 2 ones
6 → 2 ones
7 → 3 ones
8 → 1 one

Sort using comparator:
Compare 0 and 1: 0 ones vs 1 one → 0 comes first
Compare 1 and 2: 1 one vs 1 one → 1<2, 1 comes first
Compare 1 and 4: 1 one vs 1 one → 1<4, 1 comes first
Compare 2 and 4: 1 one vs 1 one → 2<4, 2 comes first
Compare 4 and 8: 1 one vs 1 one → 4<8, 4 comes first

1-bit group sorted: [1, 2, 4, 8]

Compare 3 and 5: 2 ones vs 2 ones → 3<5, 3 comes first
Compare 3 and 6: 2 ones vs 2 ones → 3<6, 3 comes first
Compare 5 and 6: 2 ones vs 2 ones → 5<6, 5 comes first

2-bit group sorted: [3, 5, 6]

7 has 3 ones, comes last

Final: [0, 1, 2, 4, 8, 3, 5, 6, 7] ✓
```

---

## Binary Understanding

**Why count 1s in binary?**

```
Number → Binary → Count 1s
0      → 0000  → 0
1      → 0001  → 1
2      → 0010  → 1
3      → 0011  → 2
4      → 0100  → 1
5      → 0101  → 2
6      → 0110  → 2
7      → 0111  → 3
8      → 1000  → 1
```

- Computers work with binary internally
- Counting 1 bits is a common operation
- `__builtin_popcount()` is optimized to be very fast!

---

## Time Complexity 

- **`__builtin_popcount(x)`:** O(1) - Counts bits very fast
- **Comparator called:** O(n log n) times during sorting
- **Total:** O(n log n) where n = array size

---

## Space Complexity

- **O(1)** if we sort in-place (just comparisons)
- **O(n)** if sort creates a copy (implementation-dependent)

---

## Visual Comparison

```
Process for sorting [6, 2, 5, 3]:

Step 1: Count bits
6: 0110 → 2 ones
2: 0010 → 1 one
5: 0101 → 2 ones
3: 0011 → 2 ones

Step 2: Group by bit count
1 one: [2]
2 ones: [6, 5, 3]

Step 3: Sort within groups
1 one: [2]
2 ones: [3, 5, 6] ← sorted by value

Step 4: Concatenate
Result: [2, 3, 5, 6] ✓
```

---

## Key Insight

**`__builtin_popcount()` is magic!**
- Instead of manually counting 1s, use this function
- It's highly optimized in C++
- Common for competitive programming and DSA problems
- Works on any integer! ✨

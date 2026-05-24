# Find Number Appearing Once

## Problem Link
🔗 [LeetCode 268 — Missing number](https://leetcode.com/problems/missing-number/)

**Problem:** Given a non-empty array of integers where every element appears twice except for one element that appears once, find that single element.

## What is this Problem?

We need to **find the only number that appears once** in an array where all other numbers appear exactly twice.

**Key Points:**
- Every number appears exactly 2 times except one
- The single number appears only once
- We need to find and return that single number
- Must be space-efficient (ideally O(1) extra space)

**Examples:**
```
Input: [2, 2, 1]
Output: 1
Explanation: 2 appears twice, 1 appears once

Input: [4, 1, 2, 1, 2]
Output: 4
Explanation: 1 appears twice, 2 appears twice, 4 appears once

Input: [1]
Output: 1
Explanation: Single element is always the answer
```

---

## The Problem Explained

Imagine you have a pile of gloves. Each glove has a pair **except one odd glove**. You need to find the odd glove without counting all pairs manually.

**Naive approaches (inefficient):**
1. Use HashSet: Mark each number, if seen again remove it → O(n) space
2. Sort and compare: Find element different from neighbors → O(n log n) time
3. Use HashMap: Store frequency→ O(n) space

**Optimal approach: Use XOR!**

---

## HOOK TO REMEMBER FOREVER

### **"XOR CANCELS PAIRS, SINGLE SURVIVES"**

Every time you see this problem:
- ✅ XOR property: `a ^ a = 0` (pairs cancel)
- ✅ Identity: `a ^ 0 = a` (result remains)
- ✅ Commutative: `a ^ b = b ^ a` (order doesn't matter)
- ✅ XOR all elements: Pairs disappear, single survives
- ✅ **O(1) space, O(n) time perfection!**

**Remember: "Pairs kill each other in XOR, single stands alone!"** ⚔️

---

## XOR Properties Deep Dive

### Property 1: Self Cancellation
```
a ^ a = 0

Example:
5 ^ 5 = 0
1010 ^ 1010 = 0000 = 0

Bit-by-bit:
Position 3: 1 ^ 1 = 0
Position 2: 0 ^ 0 = 0
Position 1: 1 ^ 1 = 0
Position 0: 0 ^ 0 = 0
```

### Property 2: Identity with Zero
```
a ^ 0 = a

Example:
5 ^ 0 = 5
1010 ^ 0000 = 1010

Bit-by-bit:
Position 3: 1 ^ 0 = 1
Position 2: 0 ^ 0 = 0
Position 1: 1 ^ 0 = 1
Position 0: 0 ^ 0 = 0
```

### Property 3: Commutative (Order Doesn't Matter)
```
a ^ b ^ c = a ^ c ^ b = c ^ a ^ b

Example:
5 ^ 3 ^ 5
= (5 ^ 5) ^ 3    (reorder)
= 0 ^ 3          (5 ^ 5 = 0)
= 3              (0 ^ 3 = 3)
```

### Property 4: Associative (Grouping Doesn't Matter)
```
(a ^ b) ^ c = a ^ (b ^ c)

Example:
(5 ^ 3) ^ 5
= ((1010 ^ 0011) ^ 0101)
= (0110 ^ 0101)
= 0011 = 3
```

---

## How It Works Step By Step

### Example: [4, 1, 2, 1, 2]

**Setup:**
```
Array: [4, 1, 2, 1, 2]
ans = 0 (binary: 0000)
```

**Step 1: XOR with 4**
```
ans = 0 ^ 4
    = 0000 ^ 0100
    = 0100 = 4
ans = 4
```

**Step 2: XOR with 1**
```
ans = 4 ^ 1
    = 0100 ^ 0001
    = 0101 = 5
ans = 5
```

**Step 3: XOR with 2**
```
ans = 5 ^ 2
    = 0101 ^ 0010
    = 0111 = 7
ans = 7
```

**Step 4: XOR with 1 (duplicate)**
```
ans = 7 ^ 1
    = 0111 ^ 0001
    = 0110 = 6
ans = 6
```

**Step 5: XOR with 2 (duplicate)**
```
ans = 6 ^ 2
    = 0110 ^ 0010
    = 0100 = 4
ans = 4 ✓
```

**Why it works:**
```
0 ^ 4 ^ 1 ^ 2 ^ 1 ^ 2
= 0 ^ 4 ^ (1^1) ^ (2^2)
= 0 ^ 4 ^ 0 ^ 0
= 4 ✓
```

---

### Example: [2, 2, 1]

**Setup:**
```
Array: [2, 2, 1]
ans = 0
```

**Step 1: XOR with 2**
```
ans = 0 ^ 2 = 2
```

**Step 2: XOR with 2 (duplicate)**
```
ans = 2 ^ 2 = 0
Pair cancels!
```

**Step 3: XOR with 1**
```
ans = 0 ^ 1 = 1
Single survives! ✓
```

---

## Code Full Solution

```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans = 0;                           // Initialize with 0
        for(auto &el : nums) {                 // Iterate through array
            ans = ans ^ el;                    // XOR each element
        }
        return ans;                            // Return the single number
    }
};
```

---

## Code Explanation

### Initialization

```cpp
int ans = 0;
```

- **`ans`:** Accumulator for XOR operations
- **Start with 0:** Since `a ^ 0 = a`, first iteration gives correct result
- **Binary:** `0` in binary is `0000...0000`

**Why 0?**
```
XOR-ing with 0 doesn't change the value:
0 ^ x = x (always true)

This makes 0 the perfect starting point for XOR accumulation.
```

---

### Loop Through Array

```cpp
for(auto &el : nums) {
```

- **`auto &el`:** Range-based loop with reference
  - `auto`: Automatically deduces type (int)
  - `&el`: Reference to element (efficient, no copy)
- **Loop iterates:** Through every element in array

**Example:**
```cpp
vector<int> nums = {1, 2, 2};
for(auto &el : nums) {
    // Iteration 1: el = 1
    // Iteration 2: el = 2
    // Iteration 3: el = 2
}
```

---

### XOR Operation

```cpp
ans = ans ^ el;
```

- **`^`:** XOR operator in C++
- **Effect:** Combines `ans` and `el` using XOR
- **Accumulation:** Result stored back in `ans`

**Trace Example:**
```
Array: [4, 1, 2, 1, 2]

ans = 0
ans = 0 ^ 4 = 4
ans = 4 ^ 1 = 5
ans = 5 ^ 2 = 7
ans = 7 ^ 1 = 6
ans = 6 ^ 2 = 4 ✓
```

---

### Return Result

```cpp
return ans;
```

- After all XORs, `ans` contains the single number
- All pairs have been canceled out
- Only the unpaired number remains

---

## Complete Example Trace

### Input: [4, 1, 2, 1, 2]

```
Initialize: ans = 0000

Process 4: ans = 0000 ^ 0100 = 0100 (4)
Process 1: ans = 0100 ^ 0001 = 0101 (5)
Process 2: ans = 0101 ^ 0010 = 0111 (7)
Process 1: ans = 0111 ^ 0001 = 0110 (6)
Process 2: ans = 0110 ^ 0010 = 0100 (4)

Return: 4 ✓

Mathematical representation:
0 ^ 4 ^ 1 ^ 2 ^ 1 ^ 2
= (0) ^ (4) ^ (1 ^ 1) ^ (2 ^ 2)
= 0 ^ 4 ^ 0 ^ 0
= 4 ✓
```

---

## Why XOR Works Perfectly

### The Magic: Commutative and Associative

```
Original: ans ^ 4 ^ 1 ^ 2 ^ 1 ^ 2
Reorder:  ans ^ 4 ^ (1 ^ 1) ^ (2 ^ 2)
Simplify: ans ^ 4 ^ 0 ^ 0
Reduce:   ans ^ 4
Result:   4 (if ans started at 0)
```

**Key insight:** Order of XOR doesn't matter! We can always group pairs together and cancel them.

---

### Why Not Alternative Approaches?

#### Approach 1: HashSet (O(n) space)
```cpp
unordered_set<int> seen;
for(int num : nums) {
    if(seen.count(num)) {
        seen.erase(num);  // Remove duplicate
    } else {
        seen.insert(num); // Add new
    }
}
return *seen.begin();     // Single remaining

Time: O(n) ✓
Space: O(n) ✗ (Uses extra space)
```

#### Approach 2: HashMap Frequency (O(n) space)
```cpp
unordered_map<int, int> freq;
for(int num : nums) {
    freq[num]++;
}
for(auto& p : freq) {
    if(p.second == 1) return p.first;
}

Time: O(n) ✓
Space: O(n) ✗ (Uses extra space)
```

#### Approach 3: XOR (Best! O(1) space)
```cpp
int ans = 0;
for(int num : nums) {
    ans ^= num;
}
return ans;

Time: O(n) ✓
Space: O(1) ✓ (Only one variable)
```

**XOR is clearly superior!**

---

## XOR Truth Table

```
a | b | a ^ b
--|---|-------
0 | 0 |  0
0 | 1 |  1
1 | 0 |  1
1 | 1 |  0

Key observations:
- Same bits → 0
- Different bits → 1
- Perfect for finding odd one out!
```

---

## Edge Cases

### Case 1: Single Element
```
Input: [1]
Process: ans = 0 ^ 1 = 1
Output: 1 ✓
```

### Case 2: Large Array
```
Input: [1, 1, 2, 2, 3, 3, 4]
Process: 0 ^ 1 ^ 1 ^ 2 ^ 2 ^ 3 ^ 3 ^ 4
       = (1 ^ 1) ^ (2 ^ 2) ^ (3 ^ 3) ^ 4
       = 0 ^ 0 ^ 0 ^ 4 = 4
Output: 4 ✓
```

### Case 3: Single at Start
```
Input: [5, 2, 2]
Process: 0 ^ 5 ^ 2 ^ 2
       = 5 ^ (2 ^ 2)
       = 5 ^ 0 = 5
Output: 5 ✓
```

### Case 4: Single at End
```
Input: [1, 1, 7]
Process: 0 ^ 1 ^ 1 ^ 7
       = (1 ^ 1) ^ 7
       = 0 ^ 7 = 7
Output: 7 ✓
```

### Case 5: Negative Numbers
```
Input: [-1, -1, 2]
Process: 0 ^ (-1) ^ (-1) ^ 2
       = (-1 ^ -1) ^ 2
       = 0 ^ 2 = 2
Output: 2 ✓

Note: XOR works with negative numbers too!
-1 in binary (two's complement): ...11111111
-1 ^ -1 = 0 (same bits XOR to 0)
```

---

## Bit-Level Explanation

### How XOR Cancels Pairs at Bit Level

```
Example: [4, 1, 2, 1, 2]

Binary representations:
4 = 0100
1 = 0001
2 = 0010

XOR Step-by-step:
    0000
  ^ 0100  (4)
  ------
    0100
  
    0100
  ^ 0001  (1)
  ------
    0101
  
    0101
  ^ 0010  (2)
  ------
    0111
  
    0111
  ^ 0001  (1 again - cancels first 1)
  ------
    0110
  
    0110
  ^ 0010  (2 again - cancels first 2)
  ------
    0100 = 4 ✓

Each bit position:
- If 1 appears even number of times → bit becomes 0
- If 1 appears odd number of times → bit becomes 1
- Since all numbers appear twice except one:
  4 has its bits appearing once → survives
  1 has its bits appearing twice → cancels
  2 has its bits appearing twice → cancels
```

---

## Time and Space Complexity

### Time Complexity
- **O(n)** where n = length of array
- Single pass through entire array
- Each XOR operation is O(1)

```
T(n) = O(n) ✓
```

---

### Space Complexity
- **O(1)** excluding output
- Only uses one variable `ans`
- No additional data structures
- No recursion (no call stack)

```
S(n) = O(1) ✓

This is optimal!
```

---

## Key Insights

### Why XOR Instead of Sum Difference?

```
Alternative: sum - 2*sum_of_duplicates
Problem: Integer overflow with large numbers!

XOR avoids overflow:
- XOR result fits in same bit representation
- Never grows beyond single integer size
- Safe for all int values
```

### The Beauty of XOR

```
Property 1: a ^ a = 0
  → Pairs disappear

Property 2: a ^ 0 = a
  → Single survives

Property 3: a ^ b = b ^ a
  → Order irrelevant

Combined: Perfect for finding unpaired element!
```

### Why Reference Parameter?

```cpp
for(auto &el : nums)  // With reference (efficient)
for(auto el : nums)   // Without (copies each element)
```

- With `&`: No copy, just reference
- Without `&`: Copies each integer (wasteful)
- Minor optimization but good practice

---

## When to Use This Pattern

**Use XOR when:**
- ✅ Finding single element among pairs
- ✅ Detecting duplicates
- ✅ Finding missing number in range
- ✅ Any problem with XOR properties
- ✅ Space must be O(1)

**Don't use when:**
- ✗ Finding element appearing 3+ times
- ✗ Need maintainable code (bit manipulation confusing)
- ✗ Space isn't critical concern

---

## Key Takeaway

**XOR is the Swiss Army knife for pairing problems.** When every element appears an even number of times except one, XOR eliminates all pairs in a single elegant pass, leaving the odd one standing. It's optimal, beautiful, and teaches you the power of bit manipulation! ✨

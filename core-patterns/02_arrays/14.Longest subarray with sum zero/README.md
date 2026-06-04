# Longest Subarray with Sum Zero

## What is this Problem?

Given an array of integers (positive and negative), find the **length of the longest contiguous subarray** that sums to exactly **zero**.

**Key Points:**
- Subarray must be **contiguous** (consecutive elements)
- Sum must equal **exactly 0**
- Return the **maximum length** of such a subarray
- If no such subarray exists, return 0
- **Works with any integers** (positive, negative, zero)

**Examples:**
```
Input: [9, -3, 3, -1, 6, -5]
Output: 5
Explanation:
- Subarray [-3, 3, -1, 6, -5] (indices 1-5) = -3+3-1+6-5 = 0 ✓ length 5
- Subarray [9, -3, 3, -1, 6, -5] would sum to 8, not 0
- Longest subarray with sum 0: length 5

Input: [15, -2, 2, -8, 1, -5]
Output: 4
Explanation:
- Subarray [-2, 2, -8, 8]? There's no 8 in array
- Subarray [-2, 2]? Sum is 0, length 2
- Subarray [15, -2, 2, -8, 1, -5]? Sum is 3, not 0
- Subarray [15, -2, 2, -8, 1, -5]... Let me check others
- Subarray [2, -8, 1, -5]? Sum is 2-8+1-5 = -10
- Subarray [-2, 2] (indices 1-2) = 0, length 2
- Let me recalculate...
  [15] = 15
  [15, -2] = 13
  [15, -2, 2] = 15
  [15, -2, 2, -8] = 7
  [15, -2, 2, -8, 1] = 8
  [15, -2, 2, -8, 1, -5] = 3
  [-2] = -2
  [-2, 2] = 0 ✓ length 2
  [-2, 2, -8] = -8
  [-2, 2, -8, 1] = -7
  [-2, 2, -8, 1, -5] = -12
  [2] = 2
  [2, -8] = -6
  [2, -8, 1] = -5
  [2, -8, 1, -5] = -10
  [-8] = -8
  [-8, 1] = -7
  [-8, 1, -5] = -12
  [1] = 1
  [1, -5] = -4
  [-5] = -5

Max length with sum 0 is 2 from [-2, 2]
```

---

## The Problem Explained

Imagine you have a list of gains and losses. You want to find the **longest period** where your net profit/loss is exactly zero.

**Analogy:** 
- Positive number = gain money
- Negative number = lose money
- Find longest period where you break even (net = 0)

**Why difficult:** Unlike the "sum equals k" problem, you **can't use simple two pointers** with negative numbers. You need a smarter approach!

---

## HOOK TO REMEMBER FOREVER

### **"PREFIX SUM REPEATS = ZERO SUM SUBARRAY"**

Every time you see this problem:
- ✅ Use **prefix sum** technique
- ✅ Store first occurrence of **each prefix sum** in HashMap
- ✅ If **same prefix sum appears again** → subarray between them sums to 0
- ✅ If **prefix sum = 0** → subarray from start to current index sums to 0
- ✅ Track the **maximum length** found
- ✅ **Works with any integers** (positive, negative, zero)

**Remember: Same prefix sum = Zero sum subarray! 🎯**

---

## The Prefix Sum Insight

### Why Prefix Sums Reveal Zero Subarrays?

**Key insight:** If two indices have the **same prefix sum**, the subarray between them sums to zero!

**Mathematical proof:**
```
prefixSum[i] = A[0] + A[1] + ... + A[i]
prefixSum[j] = A[0] + A[1] + ... + A[j] (where j > i)

If prefixSum[i] == prefixSum[j]:
    Sum from index (i+1) to j = prefixSum[j] - prefixSum[i]
                               = 0 ✓
```

**Example:**
```
Array:       [9, -3, 3, -1, 6, -5]
Index:        0   1  2   3  4   5
PrefixSum:    9   6  9   8  14  9
              ↑           ↑        ↑

prefixSum[0] = 9
prefixSum[2] = 9 (SAME!)
Subarray from index 1 to 2: [-3, 3] = 0 ✓ length 2

Also:
prefixSum[5] = 9 (SAME!)
Subarray from index 1 to 5: [-3, 3, -1, 6, -5] = 0 ✓ length 5
```

**Also:** If prefixSum becomes 0 at any point, the subarray from start to that index sums to zero!

```
Array:       [9, -3, 3, ...]
prefixSum:    9   6  9  ...
             (if at some index i, prefixSum = 0)
             → subarray A[0..i] sums to 0 ✓
```

---

## How It Works Step By Step

### Example: [9, -3, 3, -1, 6, -5]

**Setup:**
```
Array:        [9, -3, 3, -1, 6, -5]
Index:         0   1  2   3  4   5

Initialize:
sum = 0
maxi = 0 (no zero-sum subarray found yet)
mpp = {} (hashmap to store prefix sum → first index)
```

**Iteration 1: i = 0**
```
sum = 0 + 9 = 9
sum == 0? NO
mpp.find(9)? NO (not in map yet)
mpp[9] = 0  (store: prefix sum 9 first appears at index 0)

State: sum=9, mpp={9:0}, maxi=0
```

**Iteration 2: i = 1**
```
sum = 9 + (-3) = 6
sum == 0? NO
mpp.find(6)? NO (not in map)
mpp[6] = 1  (store: prefix sum 6 first appears at index 1)

State: sum=6, mpp={9:0, 6:1}, maxi=0
```

**Iteration 3: i = 2**
```
sum = 6 + 3 = 9
sum == 0? NO
mpp.find(9)? YES! Found at index 0
  Subarray from index (0+1) to 2 → [-3, 3]
  Length = 2 - 0 = 2
  maxi = max(0, 2) = 2

Note: We DON'T update mpp[9], keep first occurrence!

State: sum=9, mpp={9:0, 6:1}, maxi=2
```

**Iteration 4: i = 3**
```
sum = 9 + (-1) = 8
sum == 0? NO
mpp.find(8)? NO (not in map)
mpp[8] = 3  (store: prefix sum 8 first appears at index 3)

State: sum=8, mpp={9:0, 6:1, 8:3}, maxi=2
```

**Iteration 5: i = 4**
```
sum = 8 + 6 = 14
sum == 0? NO
mpp.find(14)? NO (not in map)
mpp[14] = 4  (store: prefix sum 14 first appears at index 4)

State: sum=14, mpp={9:0, 6:1, 8:3, 14:4}, maxi=2
```

**Iteration 6: i = 5**
```
sum = 14 + (-5) = 9
sum == 0? NO
mpp.find(9)? YES! Found at index 0 (FIRST occurrence)
  Subarray from index (0+1) to 5 → [-3, 3, -1, 6, -5]
  Length = 5 - 0 = 5
  maxi = max(2, 5) = 5

State: sum=9, mpp={...}, maxi=5
```

**Return: 5** ✓

The longest subarray with sum zero is [-3, 3, -1, 6, -5] (indices 1-5).

---

## Code Full Solution

```cpp
int maxLen(int A[], int n) {
    int maxi = 0;                           // Maximum length found
    unordered_map<int, int> mpp;            // prefixSum → first index
    int sum = 0;                            // Running prefix sum

    for(int i = 0; i < n; i++) {
        sum += A[i];                        // Add current element
        
        // Case 1: Prefix sum is 0
        if(sum == 0) {
            maxi = i + 1;                   // Subarray from start to i
        }
        // Case 2: Prefix sum seen before
        else if(mpp.find(sum) != mpp.end()) {
            int len = i - mpp[sum];         // Distance since first occurrence
            maxi = max(maxi, len);
        }
        // Case 3: New prefix sum, store it
        else {
            mpp[sum] = i;                   // Record first occurrence
        }
    }

    return maxi;
}
```

---

## Code Explanation

### Initialize Variables

```cpp
int maxi = 0;
unordered_map<int, int> mpp;
int sum = 0;
```

- **`maxi`:** Track longest zero-sum subarray found
- **`mpp`:** HashMap storing `prefixSum → first index`
- **`sum`:** Running prefix sum (grows with each iteration)

---

### Main Loop

```cpp
for(int i = 0; i < n; i++) {
    sum += A[i];
```

- Iterate through each element
- Update prefix sum by adding current element

---

### Case 1: Prefix Sum Equals Zero

```cpp
if(sum == 0) {
    maxi = i + 1;
}
```

**Meaning:** 
- Prefix sum is 0 at index i
- Entire subarray from index 0 to i sums to zero
- Length = i + 1 (i is 0-indexed, so add 1)

**Example:**
```
Array: [1, -1, 3]
i=1: sum = 1-1 = 0
     Subarray from 0 to 1: [1, -1] = 0 ✓
     Length = 1 + 1 = 2
```

### Case 2: Prefix Sum Seen Before

```cpp
else if(mpp.find(sum) != mpp.end()) {
    int len = i - mpp[sum];
    maxi = max(maxi, len);
}
```

**Meaning:**
- Current prefix sum matches a previous occurrence
- A zero-sum subarray exists between them!
- Length = `current index - previous index` (distance)

**Why not `i - mpp[sum] + 1`?**
```
If prefixSum[j] = prefixSum[i] (where i < j):
  Subarray is from index (i+1) to j (inclusive)
  Length = j - i
  (NOT j - i + 1, because the element at index i itself 
   is not part of the zero-sum subarray)

Example:
Array:       [9, -3, 3, ...]
Index:        0   1  2
prefixSum:    9   6  9

prefixSum[0] = 9 at index 0
prefixSum[2] = 9 at index 2
Zero-sum subarray: indices 1 to 2 (elements at positions 1,2)
Length = 2 - 0 = 2 ✓
Elements: [A[1], A[2]] = [-3, 3]
```

---

### Case 3: New Prefix Sum

```cpp
else {
    mpp[sum] = i;
}
```

**Meaning:**
- First time seeing this prefix sum
- Store it for future matching
- If this prefix sum appears again, we'll know the distance

**Why only store first occurrence?**
```
If a prefixSum appears multiple times:
  First: index 0
  Second: index 5
  Third: index 8

Zero-sum subarray exists:
  From 0 to 5: length 5
  From 0 to 8: length 8
  From 5 to 8: length 3

We want MAXIMUM length, so we should use the EARLIEST occurrence!
Keep mpp[sum] with first index, ignore later ones.
```

---

## Complete Example Trace

### Input: [9, -3, 3, -1, 6, -5]

```
Initialize:
maxi = 0, mpp = {}, sum = 0

i=0: sum = 0+9 = 9
     9==0? NO
     mpp.find(9)? NO
     mpp[9] = 0
     State: maxi=0, mpp={9:0}

i=1: sum = 9-3 = 6
     6==0? NO
     mpp.find(6)? NO
     mpp[6] = 1
     State: maxi=0, mpp={9:0, 6:1}

i=2: sum = 6+3 = 9
     9==0? NO
     mpp.find(9)? YES at index 0
     len = 2-0 = 2
     maxi = max(0, 2) = 2
     State: maxi=2, mpp={9:0, 6:1}

i=3: sum = 9-1 = 8
     8==0? NO
     mpp.find(8)? NO
     mpp[8] = 3
     State: maxi=2, mpp={9:0, 6:1, 8:3}

i=4: sum = 8+6 = 14
     14==0? NO
     mpp.find(14)? NO
     mpp[14] = 4
     State: maxi=2, mpp={9:0, 6:1, 8:3, 14:4}

i=5: sum = 14-5 = 9
     9==0? NO
     mpp.find(9)? YES at index 0
     len = 5-0 = 5
     maxi = max(2, 5) = 5
     State: maxi=5, mpp={...}

Return: 5 ✓

Zero-sum subarray: [A[1], A[2], A[3], A[4], A[5]]
                 = [-3, 3, -1, 6, -5]
                 = 0 ✓
```

---

## Edge Cases

### Case 1: Array Starting with Zero
```
Input: [0, 1, 2]
i=0: sum=0, sum==0? YES
     maxi = 0+1 = 1
Output: 1 ✓ (prefix sum of [0] is 0)
```

### Case 2: All Zeros
```
Input: [0, 0, 0]
i=0: sum=0, 0==0? YES, maxi=1
i=1: sum=0, 0==0? YES, maxi=2
i=2: sum=0, 0==0? YES, maxi=3
Output: 3 ✓ (entire array)
```

### Case 3: No Zero-Sum Subarray
```
Input: [1, 2, 3]
i=0: sum=1, mpp[1]=0
i=1: sum=3, mpp[3]=1
i=2: sum=6, mpp[6]=2
Output: 0 ✓ (no zero-sum found)
```

### Case 4: Single Element
```
Input: [0]
i=0: sum=0, 0==0? YES, maxi=1
Output: 1 ✓

Input: [5]
i=0: sum=5, mpp[5]=0
Output: 0 ✓
```

### Case 5: Negative at Start
```
Input: [-5, 5, 2]
i=0: sum=-5, mpp[-5]=0
i=1: sum=0, 0==0? YES, maxi=2
i=2: sum=2, mpp[2]=2
Output: 2 ✓ (subarray [-5, 5])
```

### Case 6: Multiple Zero Sums
```
Input: [1, -1, 2, -2, 3]
i=0: sum=1, mpp[1]=0
i=1: sum=0, 0==0? YES, maxi=2  (subarray [1,-1])
i=2: sum=2, mpp[2]=2
i=3: sum=0, 0==0? YES, maxi=4  (subarray [1,-1,2,-2])
i=4: sum=3, mpp[3]=4
Output: 4 ✓
```

---

## Why This Beats Two-Pointer Approach

The "Longest Subarray with Sum K" problem uses two pointers, but **fails with negative numbers**. This problem handles negatives beautifully!

**Why HashMap approach works universally:**
```
Two-pointer assumption: sum only grows/shrinks reliably
With negatives: This breaks! A shrink might expand if we pass negative numbers

HashMap approach: Uses mathematical property
"Same prefix sum = Zero sum between them"
This is ALWAYS true, regardless of number signs!
```

---

## Time Complexity

- **Single pass through array:** O(n)
- **HashMap operations (find, insert):** O(1) average
- **Total: O(n)** ✓

---

## Space Complexity

- **HashMap storage:** O(n) worst case
  - At most n unique prefix sums
  
- **Overall: O(n)**

---

## Key Insights

### Why Not Update mpp For Duplicate Prefixes?

```cpp
if(mpp.find(sum) != mpp.end()) {
    // Use mpp[sum] (FIRST occurrence)
    // Don't update it
} else {
    mpp[sum] = i;  // Store FIRST occurrence
}
```

**Why:** We want **maximum distance** between two same prefix sums.

```
If prefixSum appears at indices 0, 5, 8:
  0 to 5: distance 5
  0 to 8: distance 8 (LARGER!)
  5 to 8: distance 3

We want distance 8, so we use FIRST occurrence (0)
```

---

### The Elegant One-Pass Algorithm

**No preprocessing needed!**
- Single loop through array
- Update prefix sum gradually
- Check HashMap in O(1)
- Determine answer as we go

**Contrast with sorting approaches:**
- Sort entire array → O(n log n)
- Then process → O(n) or O(n²)
- Final answer at the end

---

### HashMap Is Perfect Here

**Why HashMap over other structures?**

```
Array (fixed size): Need to know max prefix sum value
HashSet: Only tracks existence, not position
HashMap: Tracks position (essential for distance calculation)
```

**Essential information:** Where did I last see this prefix sum?
**Perfect data structure:** HashMap ✓


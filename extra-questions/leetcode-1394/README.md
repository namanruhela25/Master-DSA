# Find Lucky Integer in an Array

**Problem Link:** https://leetcode.com/problems/find-lucky-integer-in-an-array

## What is this Problem?

A **lucky integer** is an integer where the value of the integer is **equal to its frequency** in the array.

We need to find the **largest lucky integer** in the array. If no lucky integer exists, return `-1`.

**Key Points:**
- Lucky integer: value equals frequency (e.g., if 3 appears 3 times, it's lucky)
- Return the **maximum** lucky integer
- If multiple lucky integers exist, return the largest
- If no lucky integer exists, return `-1`

**Examples:**
```
Input: [1, 2, 2, 3, 3, 3]
Output: 3
Explanation:
  - 1 appears 1 time → Lucky! (1 == 1)
  - 2 appears 2 times → Lucky! (2 == 2)
  - 3 appears 3 times → Lucky! (3 == 3)
  Maximum lucky integer: 3

Input: [2, 2, 3, 4]
Output: 2
Explanation:
  - 2 appears 2 times → Lucky! (2 == 2)
  - 3 appears 1 time → Not lucky (3 != 1)
  - 4 appears 1 time → Not lucky (4 != 1)
  Maximum lucky integer: 2

Input: [1, 1, 1, 3]
Output: -1
Explanation:
  - 1 appears 3 times → Not lucky (1 != 3)
  - 3 appears 1 time → Not lucky (3 != 1)
  No lucky integer found
```

---

## The Problem Explained

Think of it as a **matching game**:

**Rule:** An integer is lucky if the number itself matches how many times it appears.

**Example:** In a group of people:
- If you have 5 people named "5" → Lucky! (value 5, frequency 5)
- If you have 3 people named "3" → Lucky! (value 3, frequency 3)
- If you have 4 people named "2" → Not lucky (value 2, frequency 4)

Find the person with the highest lucky number!

---

## HOOK TO REMEMBER FOREVER

### **"VALUE EQUALS FREQUENCY = LUCKY!"**

Every time you see this problem:
- ✅ Count **frequency** of each number
- ✅ Compare: **value == frequency?**
- ✅ Collect all lucky numbers
- ✅ Return the **maximum** lucky number
- ✅ If none, return **-1**

**Remember: Lucky numbers match their own frequency!** 🍀

---

## How It Works Step By Step

### Example: [1, 2, 2, 3, 3, 3]

**Step 1: Count Frequencies**
```
Build frequency map:
1 → appears 1 time
2 → appears 2 times
3 → appears 3 times

Map: {1: 1, 2: 2, 3: 3}
```

**Step 2: Check for Lucky Numbers**
```
Check 1: value=1, frequency=1 → 1 == 1? YES! Lucky ✓
Check 2: value=2, frequency=2 → 2 == 2? YES! Lucky ✓
Check 3: value=3, frequency=3 → 3 == 3? YES! Lucky ✓

Lucky numbers: [1, 2, 3]
```

**Step 3: Return Maximum**
```
Maximum of [1, 2, 3] = 3
Return: 3 ✓
```

---

### Example: [2, 2, 3, 4]

**Step 1: Count Frequencies**
```
2 → appears 2 times
3 → appears 1 time
4 → appears 1 time

Map: {2: 2, 3: 1, 4: 1}
```

**Step 2: Check for Lucky Numbers**
```
Check 2: value=2, frequency=2 → 2 == 2? YES! Lucky ✓
Check 3: value=3, frequency=1 → 3 == 1? NO! ✗
Check 4: value=4, frequency=1 → 4 == 1? NO! ✗

Lucky numbers: [2]
```

**Step 3: Return Maximum**
```
Maximum of [2] = 2
Return: 2 ✓
```

---

### Example: [1, 1, 1, 3]

**Step 1: Count Frequencies**
```
1 → appears 3 times
3 → appears 1 time

Map: {1: 3, 3: 1}
```

**Step 2: Check for Lucky Numbers**
```
Check 1: value=1, frequency=3 → 1 == 3? NO! ✗
Check 3: value=3, frequency=1 → 3 == 1? NO! ✗

Lucky numbers: []
```

**Step 3: Return Maximum**
```
No lucky numbers found
Return: -1 ✓
```

---

## Code Full Solution

```cpp
class Solution {
public:
    int findLucky(vector<int>& arr) {
        unordered_map<int, int> mpp;           // Frequency map
        
        // Step 1: Count frequency of each number
        for(auto &el : arr) {
            mpp[el]++;
        }
        
        // Step 2: Find maximum lucky integer
        int ans = -1;                          // Initialize with -1 (no lucky found)
        for(auto &el : mpp) {
            if(el.second == el.first) {        // Check: frequency == value?
                ans = max(ans, el.first);      // Update max lucky number
            }
        }
        
        return ans;                            // Return result
    }
};
```

---

## Code Explanation

### Step 1: Build Frequency Map

```cpp
unordered_map<int, int> mpp;
for(auto &el : arr) {
    mpp[el]++;
}
```

- **`unordered_map<int, int> mpp`:** Map from value → frequency
  - Key: The number itself
  - Value: How many times it appears
  
- **Loop through array:** For each element, increment its count

**Example Trace:**
```cpp
arr = [1, 2, 2, 3, 3, 3]

Iteration 1: el=1, mpp[1]=0+1=1 → {1:1}
Iteration 2: el=2, mpp[2]=0+1=1 → {1:1, 2:1}
Iteration 3: el=2, mpp[2]=1+1=2 → {1:1, 2:2}
Iteration 4: el=3, mpp[3]=0+1=1 → {1:1, 2:2, 3:1}
Iteration 5: el=3, mpp[3]=1+1=2 → {1:1, 2:2, 3:2}
Iteration 6: el=3, mpp[3]=2+1=3 → {1:1, 2:2, 3:3}

Final map: {1:1, 2:2, 3:3}
```

---

### Step 2: Find Maximum Lucky Integer

```cpp
int ans = -1;
for(auto &el : mpp) {
    if(el.second == el.first) {
        ans = max(ans, el.first);
    }
}
```

- **`int ans = -1`:** Initialize result
  - Starts with -1 (no lucky number found yet)
  - If we find lucky numbers, this will be updated to max

- **Loop through map:** Check each key-value pair
  - `el.first`: The number itself (key)
  - `el.second`: Its frequency (value)

- **Lucky condition:** `el.second == el.first`
  - Check if frequency equals the number value

- **Update maximum:** `ans = max(ans, el.first)`
  - If current element is lucky, update ans to larger value

**Example Trace:**
```cpp
mpp = {1:1, 2:2, 3:3}
ans = -1

Check (1, 1): 1 == 1? YES!
  ans = max(-1, 1) = 1

Check (2, 2): 2 == 2? YES!
  ans = max(1, 2) = 2

Check (3, 3): 3 == 3? YES!
  ans = max(2, 3) = 3

Final ans = 3 ✓
```

---

## Complete Example Trace

### Input: [1, 2, 2, 3, 3, 3]

```
Building frequency map:
Iterate: 1 → mpp[1]=1
Iterate: 2 → mpp[2]=1
Iterate: 2 → mpp[2]=2
Iterate: 3 → mpp[3]=1
Iterate: 3 → mpp[3]=2
Iterate: 3 → mpp[3]=3

After counting: mpp = {1:1, 2:2, 3:3}

Finding lucky integers:
Initialize: ans = -1

Check pair (1, 1):
  el.first = 1, el.second = 1
  1 == 1? YES! Lucky
  ans = max(-1, 1) = 1

Check pair (2, 2):
  el.first = 2, el.second = 2
  2 == 2? YES! Lucky
  ans = max(1, 2) = 2

Check pair (3, 3):
  el.first = 3, el.second = 3
  3 == 3? YES! Lucky
  ans = max(2, 3) = 3

Return: 3 ✓
```

---

### Input: [1, 1, 1, 3]

```
Building frequency map:
Iterate: 1 → mpp[1]=1
Iterate: 1 → mpp[1]=2
Iterate: 1 → mpp[1]=3
Iterate: 3 → mpp[3]=1

After counting: mpp = {1:3, 3:1}

Finding lucky integers:
Initialize: ans = -1

Check pair (1, 3):
  el.first = 1, el.second = 3
  3 == 1? NO! Not lucky

Check pair (3, 1):
  el.first = 3, el.second = 1
  1 == 3? NO! Not lucky

Return: -1 ✓
(No lucky integers found)
```

---

## Edge Cases

### Case 1: All Numbers Are Lucky
```
Input: [1, 2, 2, 3, 3, 3]
All numbers satisfy value == frequency
Answer: 3 (maximum)
```

### Case 2: No Lucky Numbers
```
Input: [1, 1, 1, 3]
No number matches its frequency
Answer: -1
```

### Case 3: Single Element
```
Input: [1]
1 appears 1 time → 1 == 1? YES!
Answer: 1
```

### Case 4: Single Element (Not Lucky)
```
Input: [5]
5 appears 1 time → 5 == 1? NO!
Answer: -1
```

### Case 5: Multiple Same Numbers
```
Input: [5, 5, 5, 5, 5]
5 appears 5 times → 5 == 5? YES!
Answer: 5
```

### Case 6: Large Array
```
Input: [1, 2, 3, 4, 4, 4, 5, 5, 5, 5]
Frequencies: 1→1, 2→1, 3→1, 4→3, 5→4
Lucky: 1 (1==1)
Answer: 1
(Note: 4 appears 3 times, 5 appears 4 times - neither is lucky)
```

### Case 7: Multiple Lucky with Different Values
```
Input: [1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5]
Frequencies: 1→1, 2→2, 3→3, 4→4, 5→5
Lucky: 1, 2, 3, 4, 5 (all lucky!)
Answer: 5 (maximum)
```

---

## Why HashMap?

**HashMap approach advantages:**
- ✅ **Efficient counting:** O(1) per element
- ✅ **Easy lookup:** Check frequency in O(1)
- ✅ **Natural for frequency problems**
- ✅ **Clean code:** Simple and readable

**Alternative approaches:**

#### Approach 1: Sort + Compare
```cpp
sort(arr.begin(), arr.end());
int count = 1;
for(int i = 1; i < arr.size(); i++) {
    if(arr[i] == arr[i-1]) {
        count++;
    } else {
        if(count == arr[i-1]) return arr[i-1];
        count = 1;
    }
}
if(count == arr.back()) return arr.back();
return -1;

Time: O(n log n) - slower due to sorting
Space: O(1) - better space
```

#### Approach 2: Array Indexing (if range limited)
```cpp
// If values fit in reasonable range [1, n]
int freq[n+1] = {0};
for(int x : arr) freq[x]++;
for(int i = n; i >= 1; i--) {
    if(freq[i] == i) return i;
}
return -1;

Time: O(n) - same as hashmap
Space: O(n) - uses array instead of map
```

**HashMap is best for general case!**

---

## Understanding unordered_map Iteration

```cpp
for(auto &el : mpp) {
    // el is a pair<const int, int>
    // el.first  = key (the number)
    // el.second = value (frequency)
}
```

**Example:**
```cpp
unordered_map<int, int> mpp = {{1, 1}, {2, 2}, {3, 3}};

for(auto &el : mpp) {
    cout << "Number: " << el.first 
         << ", Frequency: " << el.second << endl;
}

Output:
Number: 1, Frequency: 1
Number: 2, Frequency: 2
Number: 3, Frequency: 3
```

---

## Key Insights

### Why `int ans = -1`?

```cpp
int ans = -1;
```

- **-1 means "not found"** (valid integer values are positive)
- **Why use max() instead of direct assignment?**
  - We want MAXIMUM lucky integer
  - `max(-1, x)` ensures:
    - If no lucky found: `max(-1, nothing) = -1`
    - If one lucky x found: `max(-1, x) = x`
    - If multiple lucky: `max(prev, curr) = larger value`

```cpp
// With max:
ans = -1
ans = max(-1, 1) = 1    // First lucky
ans = max(1, 2) = 2     // Second lucky
ans = max(2, 3) = 3     // Third lucky

// Without max (would be wrong):
ans = -1
if(lucky) ans = 1       // Only stores first lucky
if(lucky) ans = 2       // Only stores... wait, we need maximum!
```

---

### Why Use Reference in Loop?

```cpp
for(auto &el : mpp)  // With reference
for(auto el : mpp)   // Without reference
```

**With `&` (reference):**
- No copy of pair created
- Efficient memory usage
- Preferred in competitive programming

**Without `&`:**
- Creates copy of pair for each iteration
- Wasteful for large maps
- Less efficient

```cpp
// Reference: just accesses existing data
for(auto &el : mpp) {
    // el points to existing element, no copy
}

// Non-reference: creates copies
for(auto el : mpp) {
    // el is a copy of the pair
    // wasteful!
}
```

---

## Time Complexity

- **Phase 1: Build frequency map**
  - Loop through array: O(n)
  - HashMap insert/update: O(1) average
  - Total: O(n)

- **Phase 2: Find maximum lucky**
  - Loop through map: O(k) where k = unique elements
  - Comparison: O(1)
  - Total: O(k)

- **Overall: O(n + k) = O(n)** since k ≤ n

---

## Space Complexity

- **HashMap storage:**
  - Worst case: n unique elements → O(n)
  - Best case: 1 unique element → O(1)
  - Average: O(k) where k = unique elements

- **Overall: O(n)** worst case

---

## Key Takeaway

**HashMap transforms frequency counting into an elegant search.** Count frequencies, then simply check which numbers match their own frequency. The beauty lies in simplicity - a perfect lucky integer makes itself known! 🍀

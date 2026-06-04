# Two Sum

**Problem Link:** https://leetcode.com/problems/two-sum/

## What is this Problem?

Given an array of integers `nums` and an integer `target`, return the **indices of the two numbers** that add up to the target.

**Key Points:**
- Return indices (not values) of the two numbers
- Each element used **at most once**
- Must have exactly one solution (guaranteed by problem)
- **Case-insensitive:** Can be 0-indexed or 1-indexed depending on variant
- Order doesn't matter (can return [1, 0] or [0, 1])

**Examples:**
```
Input: nums = [2, 7, 11, 15], target = 9
Output: [0, 1]
Explanation: nums[0] + nums[1] = 2 + 7 = 9 ✓

Input: nums = [3, 2, 4], target = 6
Output: [1, 2]
Explanation: nums[1] + nums[2] = 2 + 4 = 6 ✓

Input: nums = [3, 3], target = 6
Output: [0, 1]
Explanation: nums[0] + nums[1] = 3 + 3 = 6 ✓
```

---

## The Problem Explained

Imagine you're at a store with prices, and you have a budget. You want to find **two items** whose combined price equals your budget exactly.

**Simple approach:** Try every pair (brute force - O(n²))
```
Item 1: check against Item 2, Item 3, Item 4...
Item 2: check against Item 3, Item 4...
Item 3: check against Item 4...
```

**Smart approach:** HashMap (O(n))
```
For each item:
  - Calculate: "What other price do I need?" (complement)
  - Check: "Have I seen that other price before?"
  - If yes: Found the pair!
  - If no: Remember this price for future checks
```

---

## HOOK TO REMEMBER FOREVER

### **"COMPLEMENT + HASHMAP = INSTANT PAIR"**

Every time you see this problem:
- ✅ Calculate **complement:** `target - current_element`
- ✅ Check if **complement exists** in HashMap
- ✅ If **YES:** Return the pair immediately
- ✅ If **NO:** Store current element in HashMap for future checks
- ✅ Continue until found (guaranteed by problem)

**Remember: Know what you need, check if you've seen it, remember what you have!** 🔍

---

## How It Works Step By Step

### Example: nums = [2, 7, 11, 15], target = 9

**Setup:**
```
Array:  [2, 7, 11, 15]
Index:   0  1   2   3
target = 9

Initialize:
mpp = {} (empty HashMap)
```

**Iteration 1: i = 0**
```
Current element: nums[0] = 2
Complement needed: rem = 9 - 2 = 7
mpp.find(7)? NO (not in map yet)
Store: mpp[2] = 0

State: mpp = {2: 0}
```

**Iteration 2: i = 1**
```
Current element: nums[1] = 7
Complement needed: rem = 9 - 7 = 2
mpp.find(2)? YES! Found at index mpp[2] = 0
Return: {0, 1} ✓

Solution found: nums[0] + nums[1] = 2 + 7 = 9
```

---

### Example: nums = [3, 2, 4], target = 6

**Setup:**
```
Array:  [3, 2, 4]
Index:   0  1  2
target = 6

Initialize:
mpp = {}
```

**Iteration 1: i = 0**
```
Current element: nums[0] = 3
Complement needed: rem = 6 - 3 = 3
mpp.find(3)? NO
Store: mpp[3] = 0

State: mpp = {3: 0}
```

**Iteration 2: i = 1**
```
Current element: nums[1] = 2
Complement needed: rem = 6 - 2 = 4
mpp.find(4)? NO
Store: mpp[2] = 1

State: mpp = {3: 0, 2: 1}
```

**Iteration 3: i = 2**
```
Current element: nums[2] = 4
Complement needed: rem = 6 - 4 = 2
mpp.find(2)? YES! Found at index mpp[2] = 1
Return: {1, 2} ✓

Solution found: nums[1] + nums[2] = 2 + 4 = 6
```

---

### Example: nums = [3, 3], target = 6

**Setup:**
```
Array:  [3, 3]
Index:   0  1
target = 6

Initialize:
mpp = {}
```

**Iteration 1: i = 0**
```
Current element: nums[0] = 3
Complement needed: rem = 6 - 3 = 3
mpp.find(3)? NO
Store: mpp[3] = 0

State: mpp = {3: 0}
```

**Iteration 2: i = 1**
```
Current element: nums[1] = 3
Complement needed: rem = 6 - 3 = 3
mpp.find(3)? YES! Found at index mpp[3] = 0
Return: {0, 1} ✓

Key insight: Can use the same number (index 0) if it appears twice
nums[0] + nums[1] = 3 + 3 = 6
```

---

## Code Full Solution

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mpp;       // value → index mapping
        int n = nums.size();

        for(int i = 0; i < n; i++) {
            int rem = target - nums[i];    // What complement do we need?

            if(mpp.find(rem) != mpp.end()) {
                // Found the pair!
                return {mpp[rem], i};
            } else {
                // Store current element for future checks
                mpp[nums[i]] = i;
            }
        }

        return {-1, -1};                   // No solution (shouldn't reach)
    }
};
```

---

## Code Explanation

### Initialize HashMap

```cpp
unordered_map<int, int> mpp;
int n = nums.size();
```

- **`mpp`:** Maps number value → its index
  - Key: the number itself
  - Value: its index in the array
- **`n`:** Size of array

---

### Main Loop

```cpp
for(int i = 0; i < n; i++) {
```

- Iterate through each element exactly once
- **One-pass algorithm:** No second nested loop needed

---

### Calculate Complement

```cpp
int rem = target - nums[i];
```

- **Complement:** What number do we need to reach the target?
- Example: target=9, current=2 → need 7 (because 2+7=9)
- Formula: `complement = target - current`

---

### Check if Complement Exists

```cpp
if(mpp.find(rem) != mpp.end()) {
    return {mpp[rem], i};
}
```

- **`mpp.find(rem)`:** Search for complement in HashMap
- **`!= mpp.end()`:** If found (iterator is valid)
- **Return:** `{index_of_complement, current_index}`

**Why `mpp[rem]` for first index?**
- We stored earlier elements in the map
- `mpp[rem]` gives us the index of the complement we need
- Current index `i` is automatically second element

**Example:**
```
When i=1, nums[1]=7, rem=2
If mpp[2] = 0, we found it!
Return {0, 1} → {index of 2, index of 7}
```

---

### Store Current Element

```cpp
else {
    mpp[nums[i]] = i;
}
```

- If complement not found yet, store this element
- Store its value (not index used as key)
- Store its index as the value

**Why not return immediately?**
- Complement might appear later in the array
- Continue scanning to find the pair

---

## Complete Example Trace

### Input: nums = [2, 7, 11, 15], target = 9

```
Initialize:
mpp = {}, n = 4

i=0:
  nums[0] = 2
  rem = 9 - 2 = 7
  mpp.find(7)? NO
  mpp[2] = 0
  State: mpp = {2: 0}

i=1:
  nums[1] = 7
  rem = 9 - 7 = 2
  mpp.find(2)? YES at index 0
  return {0, 1}

Output: {0, 1} ✓
```

---

## Edge Cases

### Case 1: Same Element Twice
```
Input: nums = [3, 3], target = 6
i=0: rem=3, mpp[3]=0
i=1: rem=3, mpp.find(3)? YES
     return {0, 1} ✓
```

### Case 2: Negative Numbers
```
Input: nums = [-1, -2, -3, 5, 10], target = 8
i=0: rem=9, mpp[-1]=0
i=1: rem=10, mpp[-2]=1
i=2: rem=11, mpp[-3]=2
i=3: rem=3, mpp[5]=3
i=4: rem=-2, mpp.find(-2)? YES at index 1
     return {1, 4} → nums[1]=-2, nums[4]=10, -2+10=8 ✓
```

### Case 3: Large Numbers
```
Input: nums = [1000000, 1], target = 1000001
i=0: rem=1, mpp[1000000]=0
i=1: rem=1000000, mpp.find(1000000)? YES at index 0
     return {0, 1} ✓
```

### Case 4: Zero in Array
```
Input: nums = [0, 4, 3, 0], target = 0
i=0: rem=0, mpp[0]=0
i=1: rem=-4, mpp[4]=1
i=2: rem=-3, mpp[3]=2
i=3: rem=0, mpp.find(0)? YES at index 0
     return {0, 3} → nums[0]+nums[3] = 0+0 = 0 ✓
```

---

## Alternative Approaches

### Approach 1: Brute Force (Two Loops)
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        for(int i = 0; i < n; i++) {
            for(int j = i+1; j < n; j++) {
                if(nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return {-1, -1};
    }
};
```

**Complexity:**
- Time: O(n²) - nested loops
- Space: O(1) - no extra structures
- **Inefficient for large arrays!**

---

### Approach 2: Sorting + Two Pointers
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<pair<int,int>> indexed;
        int n = nums.size();
        
        // Store value and original index
        for(int i = 0; i < n; i++) {
            indexed.push_back({nums[i], i});
        }
        
        // Sort by value
        sort(indexed.begin(), indexed.end());
        
        // Two pointers
        int left = 0, right = n-1;
        while(left < right) {
            int sum = indexed[left].first + indexed[right].first;
            if(sum == target) {
                return {indexed[left].second, indexed[right].second};
            }
            else if(sum < target) left++;
            else right--;
        }
        return {-1, -1};
    }
};
```

**Complexity:**
- Time: O(n log n) - sorting dominates
- Space: O(n) - for indexed array
- **Better than brute force, but still slower than HashMap**

---

### Approach 3: HashMap (Our Solution) ✓
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mpp;
        for(int i = 0; i < nums.size(); i++) {
            int rem = target - nums[i];
            if(mpp.find(rem) != mpp.end()) {
                return {mpp[rem], i};
            }
            mpp[nums[i]] = i;
        }
        return {-1, -1};
    }
};
```

**Complexity:**
- Time: O(n) - single pass ✓
- Space: O(n) - HashMap storage
- **Optimal! Single pass, linear time**

---

## Comparison Table

| Approach | Time | Space | Traits |
|----------|------|-------|--------|
| **Brute Force** | O(n²) | O(1) | Slow, simple |
| **Sorting + 2-Ptr** | O(n log n) | O(n) | Sorted, not original indices |
| **HashMap** | O(n) | O(n) | **Optimal, one-pass** |

---

## Why HashMap Works Perfectly

**Key insight:** For every element, ask: "Do I have what I need?"

```
At each position i:
  Need: complement = target - nums[i]
  Check: Have we seen 'complement' yet?
    YES → Found the pair! Return immediately
    NO → Remember this element for future
```

**Why this is efficient:**
- HashMap lookup: O(1) per element
- Single pass through array: O(n)
- Total: O(n) ✓

---

## Time Complexity

- **HashMap insertion and lookup:** O(1) average case
- **Single loop through array:** O(n)
- **Total: O(n)** ✓ Linear time (optimal!)

---

## Space Complexity

- **HashMap storage:** O(n) worst case
  - At most n-1 elements stored before finding the pair
  
- **Overall: O(n)**

---

## Key Insights

### Why Process Left-to-Right?

```cpp
for(int i = 0; i < n; i++) {
    int rem = target - nums[i];
    if(mpp.find(rem) != mpp.end()) {
        return {mpp[rem], i};  // Earlier index first
    }
    mpp[nums[i]] = i;
}
```

- Check hashmap first (find earlier element)
- Only store after checking
- Ensures we return indices in "first found" order
- Avoids using same element twice (because we check BEFORE storing)

---

### Why Unordered_map?

```cpp
unordered_map<int, int> mpp;  // O(1) average lookup
// vs map for O(log n) lookup
```

- **unordered_map:** Hash-based, O(1) lookup average
- **map:** Tree-based, O(log n) lookup
- For this problem, unordered_map is faster

---

### The Complement Insight

```
Given: nums = [2, 7, 11, 15], target = 9
      
For 2: need 7 (because 2+7 = 9)
For 7: need 2 (because 7+2 = 9)
For 11: need -2 (because 11-2 = 9)
For 15: need -6 (because 15-6 = 9)

When we see 7 (at i=1):
  We already processed 2 (at i=0)
  We know we need 2 for 7
  We stored 2 in HashMap: mpp[2] = 0
  Perfect match! Return immediately
```

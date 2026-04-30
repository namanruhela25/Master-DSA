# Find All Duplicates in an Array 

**Problem Link:** https://leetcode.com/problems/find-all-duplicates-in-an-array/

## What is this problem?

We are given an array of numbers. **Every number appears either once or twice**. We need to find all numbers that appear **exactly twice**.

### Constraint:
- Numbers are from **1 to n** (where n is the size of array)
- We **cannot use extra space** (no new arrays allowed!)
- We **cannot modify the input** - or we can undo our changes

### Example:
```
Input:  [4, 3, 2, 7, 8, 2, 3, 1]
Output: [2, 3]
```
- **2 appears twice** ✓
- **3 appears twice** ✓
- Others appear once

---

## The Main Idea (Intuition) 

### Normal Approach (Not Allowed)
We could use a separate array/set to mark which numbers we've seen. But the problem says **NO EXTRA SPACE!**

### Smart Approach (Mark-Negative Strategy)
The trick: **Use the array itself as a marking system!**

Since numbers are from **1 to n**, we can use their **indices** to mark them:
- When we see number `x`, go to `index (x-1)`
- **Mark that index as negative** (like a flag: "I've seen this number!")
- If we see the same number again, that index is already negative → **This number is duplicate!**

### Example:
```
Array: [4, 3, 2, 7, 8, 2, 3, 1]
Index:  0  1  2  3  4  5  6  7

Step 1: See 4 → Mark index 3 as negative → [4, 3, 2, -7, 8, 2, 3, 1]
Step 2: See 3 → Mark index 2 as negative → [4, 3, -2, -7, 8, 2, 3, 1]
Step 3: See 2 → Mark index 1 as negative → [4, -3, -2, -7, 8, 2, 3, 1]
Step 4: See 7 → Mark index 6 as negative → [4, -3, -2, -7, 8, 2, -3, 1]
Step 5: See 8 → Mark index 7 as negative → [4, -3, -2, -7, 8, 2, -3, -1]
Step 6: See 2 → Index 1 is ALREADY negative! → DUPLICATE FOUND: 2
Step 7: See 3 → Index 2 is ALREADY negative! → DUPLICATE FOUND: 3
Step 8: See 1 → Mark index 0 as negative → [-4, -3, -2, -7, 8, 2, -3, -1]

Answer: [2, 3]
```

---

## Step-by-Step Approach

### Step 1: Read each number from the array
### Step 2: Calculate which index it points to
  - If number is `x`, then index is `x - 1`
### Step 3: Check if that index is already negative
  - **If YES:** This is a duplicate number → Add to answer
  - **If NO:** Mark that index as negative
### Step 4: Return all duplicates found

---

## Code Explanation 

### Line 1-2: Start the function
```cpp
vector<int> findDuplicates(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans;
```
- Create a result vector `ans` to store duplicates
- `n` = total numbers in the array

### Line 3-4: Loop through each number
```cpp
for(int i=0; i<n; i++) {
    int index = abs(nums[i]) - 1;
```
- Go through each number one by one
- **`abs(nums[i])`**: Get absolute value (because we'll mark with negative!)
  - Example: If `nums[i]` is `-7`, get `7`
- **`- 1`**: Convert to index (number 7 → index 6)

### Line 5-6: Check if already marked (duplicate?)
```cpp
    if(nums[index] < 0) {
        ans.push_back(index+1);
```
- If the value at `index` is **negative**, we've seen this number before!
- **This is a DUPLICATE** → Add it to answers
- `index+1` converts back from index to number

### Line 7-8: Mark as seen
```cpp
    } else{
        nums[index] = -nums[index];
```
- If not seen before, mark it by making it **negative**
- Example: `nums[6] = 3` becomes `nums[6] = -3`

### Line 9-10: Return results
```cpp
    }
}
return ans;
```
- Give back all duplicate numbers we found

---

## Why This Works ✨

1. **No Extra Space:** We use the array itself as storage
2. **No Data Loss:** We only flip signs (can get original values back with `abs()`)
3. **Efficient:** We go through array only once → **O(n) time!**

---

## Time & Space Complexity

- **Time:** O(n) - visit each element once
- **Space:** O(1) - only use the input array (ignoring output)

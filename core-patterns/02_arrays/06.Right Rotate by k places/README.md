# Right Rotate Array by K Places

**Problem Link:** https://leetcode.com/problems/rotate-array/description/

## What is this Problem?

You have an **array of numbers** and you need to **rotate it right by k positions**.

This means:
- Move the **last k elements to the front**
- Shift everything else **k positions to the right**

**Examples:**
```
Input: [1, 2, 3, 4, 5], k=2
Output: [4, 5, 1, 2, 3]
(Last 2 elements [4, 5] moved to front)

Input: [1, 2, 3, 4, 5], k=1
Output: [5, 1, 2, 3, 4]
(Last 1 element [5] moved to front)

Input: [1, 2, 3, 4, 5], k=7 (k > array size)
Output: [4, 5, 1, 2, 3]
(k=7, but only 5 elements, so k becomes 7%5=2)
```

---

## The Problem Explained

Think of it like **rotating a circular disk**:

```
Original: [1, 2, 3, 4, 5]
           ↑ starting point

Rotate right by 2 positions:
The last 2 elements wrap around:
[4, 5, 1, 2, 3]
 ↑ moved to front

Like spinning a wheel - elements fall off the end and appear at the start!
```

**Key insight:** The last k elements become the first k elements, everything else shifts right.

---

## HOOK TO REMEMBER FOREVER

**"REVERSE THREE TIMES - MAGIC ROTATION"**

Every time you see "rotate array right by k":
- ✅ Handle k > array size using modulo (k = k % size)
- ✅ Reverse entire array three times in specific sections:
  - Part 1: Reverse first (n-k) elements
  - Part 2: Reverse last k elements
  - Part 3: Reverse entire array
- ✅ Three reverses = one perfect rotation!
- ✅ O(n) time, O(1) space (in-place!)

**Remember: Three reversals create one rotation - clever and efficient!** 🔄

---

## How It Works Step By Step

### The Reverse-Three-Times Strategy

The magic is: **Three reversals = One rotation!**

```
Array: [1, 2, 3, 4, 5], k=2
Goal: [4, 5, 1, 2, 3]

Key calculation: n=5, k=2
Split point = n - k = 5 - 2 = 3

Step 1: Reverse first (n-k)=3 elements [1, 2, 3]
  Result: [3, 2, 1, 4, 5]
            ↑ reversed ↑

Step 2: Reverse last k=2 elements [4, 5]
  Result: [3, 2, 1, 5, 4]
                 ↑ reversed ↑

Step 3: Reverse entire array
  Result: [4, 5, 1, 2, 3]
  ✓ Perfect rotation!
```

### Why Does This Work?

Let's trace what happens:

```
Original: [1, 2, 3, 4, 5]
          Part1 Part2
          (n-k) (k)

After reverse part 1:
[3, 2, 1, 4, 5]

After reverse part 2:
[3, 2, 1, 5, 4]

After reverse entire:
[4, 5, 1, 2, 3]
 ↑ last k elements at front!
```

The three reversals rearrange elements exactly as needed!

---

## Code Full Solution

```cpp
class Solution {
public:
    void reverse(vector<int> &nums, int start, int end) {
        while(start < end) {
            swap(nums[start], nums[end]);
            start++;
            end--;
        }
    }
    
    void rotate(vector<int>& nums, int k) {
        k = k % nums.size();
        k = nums.size() - k;
        reverse(nums, 0, k - 1);
        reverse(nums, k, nums.size() - 1);
        reverse(nums, 0, nums.size() - 1);
    }
};
```

---

## Code Explanation

### Helper Function: reverse()

```cpp
void reverse(vector<int> &nums, int start, int end) {
    while(start < end) {
        swap(nums[start], nums[end]);
        start++;
        end--;
    }
}
```

**Purpose:** Reverse elements between start and end indices (inclusive)

**How it works:**
- **Two pointers:** `start` from beginning, `end` from end of range
- **Loop condition:** `while(start < end)` - keep going until they meet
- **Swap:** Exchange elements at start and end positions
- **Move pointers:** Start moves right, end moves left (toward each other)

**Example: Reverse [1, 2, 3, 4, 5] from index 0 to 3**
```
Initial: [1, 2, 3, 4, 5], start=0, end=3
  swap(nums[0], nums[3]): [4, 2, 3, 1, 5]
  start=1, end=2
  
Iteration 2:
  swap(nums[1], nums[2]): [4, 3, 2, 1, 5]
  start=2, end=1
  
Loop ends (2 < 1 is false)
Result: [4, 3, 2, 1, 5] (indices 0-3 reversed!)
```

---

### Main Function: rotate()

```cpp
void rotate(vector<int>& nums, int k) {
    k = k % nums.size();
    k = nums.size() - k;
    reverse(nums, 0, k - 1);
    reverse(nums, k, nums.size() - 1);
    reverse(nums, 0, nums.size() - 1);
}
```

#### Step 1: Handle k > array size

```cpp
k = k % nums.size();
```

- **Problem:** If k=7 and array size=5, what does rotate by 7 mean?
  - Rotate right 5 = back to original
  - Rotate right 7 = rotate right 2 (7 - 5)
  
- **Solution:** Use modulo to find equivalent k
  - 7 % 5 = 2 (rotate right 7 is same as rotate right 2)
  - 12 % 5 = 2 (rotate right 12 is same as rotate right 2)

**Example:**
```cpp
Array size = 5, k = 7
k = 7 % 5 = 2
(Now treat as k=2, which is manageable)
```

#### Step 2: Convert Right Rotation to Left Rotation Index

```cpp
k = nums.size() - k;
```

- **Why?** The algorithm splits array into two parts and uses k as split point
- **Formula:** If rotating right by r positions:
  - This is same as rotating left by (n - r) positions
  - So split point = n - r

**Example for rotate right by 2 on size 5:**
```cpp
k = 5 - 2 = 3
Split point = 3

Array: [1, 2, 3, 4, 5]
Part 1: indices 0 to 2 (first 3 elements)
Part 2: indices 3 to 4 (last 2 elements)
```

#### Step 3: Reverse First (n-k) Elements

```cpp
reverse(nums, 0, k - 1);
```

- **Range:** From index 0 to k-1
- **Effect:** Reverses the first (n-k) elements

**Example with [1, 2, 3, 4, 5], k becomes 3:**
```cpp
reverse(nums, 0, 3-1)
reverse(nums, 0, 2)

Reverses indices 0, 1, 2: [1, 2, 3]
Result: [3, 2, 1, 4, 5]
```

#### Step 4: Reverse Last k Elements

```cpp
reverse(nums, k, nums.size() - 1);
```

- **Range:** From index k to end
- **Effect:** Reverses the last k elements

**Example with [3, 2, 1, 4, 5], k=3:**
```cpp
reverse(nums, 3, 5-1)
reverse(nums, 3, 4)

Reverses indices 3, 4: [4, 5]
Result: [3, 2, 1, 5, 4]
```

#### Step 5: Reverse Entire Array

```cpp
reverse(nums, 0, nums.size() - 1);
```

- **Range:** From index 0 to end
- **Effect:** Reverses everything, giving us the rotated result!

**Example with [3, 2, 1, 5, 4]:**
```cpp
reverse(nums, 0, 5-1)
reverse(nums, 0, 4)

Reverses entire array:
Result: [4, 5, 1, 2, 3] ✓
(This is our target right rotation!)
```

---

## Complete Example Traces

### Trace 1: Standard Case [1, 2, 3, 4, 5], k=2

```
Initial: nums=[1, 2, 3, 4, 5], k=2

Step 1: k = k % nums.size()
  k = 2 % 5 = 2

Step 2: k = nums.size() - k
  k = 5 - 2 = 3

Step 3: reverse(nums, 0, 2)
  Reverses [1, 2, 3]
  nums = [3, 2, 1, 4, 5]

Step 4: reverse(nums, 3, 4)
  Reverses [4, 5]
  nums = [3, 2, 1, 5, 4]

Step 5: reverse(nums, 0, 4)
  Reverses entire array
  nums = [4, 5, 1, 2, 3] ✓

Result: [4, 5, 1, 2, 3]
(Last 2 elements moved to front!)
```

### Trace 2: k Greater Than Size [1, 2, 3, 4, 5], k=7

```
Initial: nums=[1, 2, 3, 4, 5], k=7

Step 1: k = k % nums.size()
  k = 7 % 5 = 2
  (7 rotations = 2 rotations on size 5 circle)

Step 2: k = nums.size() - k
  k = 5 - 2 = 3

Steps 3-5: (Same as trace 1)
  reverse(nums, 0, 2): [3, 2, 1, 4, 5]
  reverse(nums, 3, 4): [3, 2, 1, 5, 4]
  reverse(nums, 0, 4): [4, 5, 1, 2, 3]

Result: [4, 5, 1, 2, 3] ✓
(Same as rotating by 2!)
```

### Trace 3: k = 1 [1, 2, 3, 4, 5], k=1

```
Initial: nums=[1, 2, 3, 4, 5], k=1

Step 1: k = 1 % 5 = 1

Step 2: k = 5 - 1 = 4

Step 3: reverse(nums, 0, 3)
  Reverses [1, 2, 3, 4]
  nums = [4, 3, 2, 1, 5]

Step 4: reverse(nums, 4, 4)
  Reverses [5] (single element, no change)
  nums = [4, 3, 2, 1, 5]

Step 5: reverse(nums, 0, 4)
  Reverses entire array
  nums = [5, 1, 2, 3, 4] ✓

Result: [5, 1, 2, 3, 4]
(Last element moved to front!)
```

### Trace 4: k = Size [1, 2, 3, 4, 5], k=5

```
Initial: nums=[1, 2, 3, 4, 5], k=5

Step 1: k = 5 % 5 = 0
  (Rotating by size brings us back to start!)

Step 2: k = 5 - 0 = 5

Step 3: reverse(nums, 0, 4)
  Reverses entire array
  nums = [5, 4, 3, 2, 1]

Step 4: reverse(nums, 5, 4)
  start=5, end=4, condition 5 < 4 is false
  No iterations (empty range)
  nums = [5, 4, 3, 2, 1]

Step 5: reverse(nums, 0, 4)
  Reverses entire array again
  nums = [1, 2, 3, 4, 5] ✓

Result: [1, 2, 3, 4, 5]
(Back to original - correct!)
```

### Trace 5: Single Element [1], k=1

```
Initial: nums=[1], k=1

Step 1: k = 1 % 1 = 0

Step 2: k = 1 - 0 = 1

Step 3: reverse(nums, 0, 0)
  start=0, end=0, condition 0 < 0 is false
  No iterations (single element)
  nums = [1]

Step 4: reverse(nums, 1, 0)
  start=1, end=0, condition 1 < 0 is false
  No iterations (empty range)
  nums = [1]

Step 5: reverse(nums, 0, 0)
  No iterations (single element)
  nums = [1] ✓

Result: [1]
(No change - correct!)
```

### Trace 6: Two Elements [1, 2], k=1

```
Initial: nums=[1, 2], k=1

Step 1: k = 1 % 2 = 1

Step 2: k = 2 - 1 = 1

Step 3: reverse(nums, 0, 0)
  start=0, end=0, condition 0 < 0 is false
  No iterations
  nums = [1, 2]

Step 4: reverse(nums, 1, 1)
  start=1, end=1, condition 1 < 1 is false
  No iterations
  nums = [1, 2]

Step 5: reverse(nums, 0, 1)
  Swap nums[0] and nums[1]
  nums = [2, 1] ✓

Result: [2, 1]
(Elements swapped - correct right rotate by 1!)
```

### Trace 7: Negative k [1, 2, 3, 4, 5], k=0

```
Initial: nums=[1, 2, 3, 4, 5], k=0

Step 1: k = 0 % 5 = 0

Step 2: k = 5 - 0 = 5

Step 3: reverse(nums, 0, 4)
  Reverses entire array
  nums = [5, 4, 3, 2, 1]

Step 4: reverse(nums, 5, 4)
  No iterations (5 < 4 false)
  nums = [5, 4, 3, 2, 1]

Step 5: reverse(nums, 0, 4)
  Reverses entire array again
  nums = [1, 2, 3, 4, 5]

Result: [1, 2, 3, 4, 5] ✓
(No rotation - array unchanged!)
```

---

## Edge Cases

### Case 1: k = 0

```
Input: [1, 2, 3, 4, 5], k=0
- k = 0 % 5 = 0
- k = 5 - 0 = 5
- Reverse first 5 elements: [5, 4, 3, 2, 1]
- Reverse last 0 elements: no change
- Reverse all: [1, 2, 3, 4, 5]
Output: [1, 2, 3, 4, 5] ✓ (no rotation)
```

### Case 2: Single Element

```
Input: [7], k=1
- k = 1 % 1 = 0
- k = 1 - 0 = 1
- All reverse operations on single element do nothing
Output: [7] ✓
```

### Case 3: k Equals Array Size

```
Input: [1, 2, 3], k=3
- k = 3 % 3 = 0
- Returns to original
Output: [1, 2, 3] ✓
```

### Case 4: k Much Larger Than Size

```
Input: [1, 2, 3], k=100
- k = 100 % 3 = 1
- Same as k=1
Output: [3, 1, 2] ✓
```

### Case 5: Two Elements

```
Input: [1, 2], k=1
- k = 1 % 2 = 1
- k = 2 - 1 = 1
- Ends up swapping them
Output: [2, 1] ✓
```

### Case 6: All Same Elements

```
Input: [5, 5, 5, 5], k=2
- Reversals don't change anything if all elements same
Output: [5, 5, 5, 5] ✓
```

---

## Time Complexity

- **O(n)** where n = array size
- **Reverse function:** Each element visited once, O(n) per call
- **Three reverse calls:** 3 × O(n) = O(n)
- Modulo operation: O(1)

---

## Space Complexity

- **O(1)** - Constant space
- Only using two integer variables (start, end) in reverse function
- Modifying array in-place, no extra arrays
- Swap operation uses no extra space

---

## Key Insights

### Why Three Reversals Work

```
Think of it mathematically:

Original: [1, 2, 3, 4, 5]
Want: [4, 5, 1, 2, 3] (rotate right by 2)

Step 1: Split and reverse parts separately
[3, 2, 1] [5, 4]

Step 2: Reverse entire thing
[4, 5, 1, 2, 3] ✓

The three reversals perfectly shuffle elements
to the right by k positions!
```

### Why Modulo Matters

```
Rotating right by 7 on array of size 5:
- Full rotation = 5 steps (back to start)
- So 7 = 5 + 2
- 7 mod 5 = 2

Rotating right 7 times = rotating right 2 times!
This prevents unnecessary iterations.
```

### The Clever Conversion

```
Right rotation by k = Left rotation by (n - k)

Our algorithm treats it as:
- Split at position (n - k)
- Reverse both parts
- Reverse whole

This works because of symmetry in reversals!
```

### Why In-Place?

```
Alternative approach (extra space):
vector<int> temp(n);
for (int i = 0; i < n; i++)
    temp[(i + k) % n] = nums[i];
// Uses O(n) extra space

Our approach:
Just shuffle existing array with swaps
// Uses O(1) extra space

Reversals are powerful for in-place rotations!
```

### Visual Understanding

```
Array: [1, 2, 3, 4, 5], rotate right by 2

Position changes:
- Index 0 (value 1) → Index 2
- Index 1 (value 2) → Index 3
- Index 2 (value 3) → Index 4
- Index 3 (value 4) → Index 0
- Index 4 (value 5) → Index 1

New position = (old position + k) % n

Our three reversals achieve exactly this!
```

# Left Rotate Array by One

## What is this Problem?

You have an **array of numbers** and you need to **rotate it left by exactly one position**. 

This means:
- Move the **first element to the end**
- Shift all other elements **one position to the left**

**Examples:**
```
Input: [1, 2, 3, 4, 5]
Output: [2, 3, 4, 5, 1]
(First element 1 moved to end, everything shifted left)

Input: [7, 8, 9]
Output: [8, 9, 7]
(7 moves to end, 8 and 9 shift left)
```

---

## The Problem Explained

Think of it like **people standing in a line**:

```
Original line:
Position: 1    2    3    4    5
Person:   Alice Bob  Chris Dave Eve

Rotate left by one (Alice steps out, everyone moves left):
Position: 1    2    3    4    5
Person:   Bob  Chris Dave Eve  Alice

Alice was first, now she's at the end!
Everyone else moved one step forward!
```

**Key idea:** It's just shifting things around! No sorting, no swapping - just **move and place**.

---

## HOOK TO REMEMBER FOREVER

**"SAVE FIRST, SHIFT LEFT, PLACE AT END"**

Every time you see "rotate array left by one":
- ✅ Save the first element (don't lose it!)
- ✅ Shift all elements one position to the left
- ✅ Put the saved element at the last position
- ✅ One pass is enough (O(n))
- ✅ No extra array needed (O(1) space)

**Remember: First element becomes last, everyone else moves forward!** 🔄

---

## How It Works Step By Step

### The Strategy

```
Array: [1, 2, 3, 4, 5]

Step 1: Save first element (temp = 1)
Step 2: Shift all elements left (start from position 1)
  - nums[0] = nums[1] (1 becomes 2)
  - nums[1] = nums[2] (2 becomes 3)
  - nums[2] = nums[3] (3 becomes 4)
  - nums[3] = nums[4] (4 becomes 5)
Step 3: Place saved element at end (last = 1)

Result: [2, 3, 4, 5, 1]
```

### Visual Animation: [1, 2, 3, 4, 5]

```
Initial:
[1, 2, 3, 4, 5]
 ↑ save this

After saving:
temp = 1
[?, ?, ?, ?, ?]  (ready to fill)

Shift step by step:
[2, ?, ?, ?, ?]  ← nums[0] = nums[1]
[2, 3, ?, ?, ?]  ← nums[1] = nums[2]
[2, 3, 4, ?, ?]  ← nums[2] = nums[3]
[2, 3, 4, 5, ?]  ← nums[3] = nums[4]

Place saved element:
[2, 3, 4, 5, 1]  ← nums[4] = temp
     ↑ saved element placed at end
```

---

## Code Full Solution

```cpp
class Solution {
public:
    void rotateArrayByOne(vector<int>& nums) {
        int temp = nums[0];
        
        for (int i = 1; i < nums.size(); ++i) {
            nums[i - 1] = nums[i];
        }

        nums[nums.size() - 1] = temp;
    }
};
```

---

## Code Explanation

### Save the First Element

```cpp
int temp = nums[0];
```

- **Why save?** If we move nums[1] to nums[0], we lose the original first element
- **`temp`:** Temporary storage for the first element
- **Plan:** We'll put this at the end after shifting everything left

**Example:** For [1, 2, 3, 4, 5]
```
temp = 1  (saved!)
We can now safely overwrite position 0
```

---

### Shift All Elements Left

```cpp
for (int i = 1; i < nums.size(); ++i) {
    nums[i - 1] = nums[i];
}
```

**Loop:** `i` starts at 1 and goes to end of array

**Key operation:** `nums[i - 1] = nums[i]`
- Take element at position i
- Put it at position i-1 (one position to the left)

**Why this works:**
```
i=1: nums[0] = nums[1]  (2 goes to position 0)
i=2: nums[1] = nums[2]  (3 goes to position 1)
i=3: nums[2] = nums[3]  (4 goes to position 2)
i=4: nums[3] = nums[4]  (5 goes to position 3)

Example with [1, 2, 3, 4, 5]:
Before: [1, 2, 3, 4, 5]
After i=1: [2, 2, 3, 4, 5]
After i=2: [2, 3, 3, 4, 5]
After i=3: [2, 3, 4, 4, 5]
After i=4: [2, 3, 4, 5, 5]
           ↑ last position still has 5
```

---

### Place Saved Element at End

```cpp
nums[nums.size() - 1] = temp;
```

- **`nums.size() - 1`:** Index of the last position
- **`temp`:** The first element we saved
- **Put saved first element at the end**

**Why now?** We've already shifted everything left, so the last position is now empty (has duplicate of previous element).

**Example:**
```cpp
nums[4] = temp;  // For array of size 5, last index is 4
// Place the saved 1 at position 4

Result: [2, 3, 4, 5, 1] ✓
```

---

## Complete Example Traces

### Trace 1: Standard Case [1, 2, 3, 4, 5]

```
Initial: nums=[1, 2, 3, 4, 5], size=5

Step 1: Save first element
  temp = nums[0] = 1
  temp = 1 ✓

Step 2: Shift left loop (i=1 to 4)
  i=1: nums[0] = nums[1] → nums = [2, 2, 3, 4, 5]
  i=2: nums[1] = nums[2] → nums = [2, 3, 3, 4, 5]
  i=3: nums[2] = nums[3] → nums = [2, 3, 4, 4, 5]
  i=4: nums[3] = nums[4] → nums = [2, 3, 4, 5, 5]

Step 3: Place saved at end
  nums[4] = temp = 1
  nums = [2, 3, 4, 5, 1] ✓

Return: void (array modified in-place)
```

### Trace 2: Negative Numbers [-5, -3, -1, 0, 2]

```
Initial: nums=[-5, -3, -1, 0, 2], size=5

Step 1: Save first
  temp = -5

Step 2: Shift left loop
  i=1: nums[0] = nums[1] → nums = [-3, -3, -1, 0, 2]
  i=2: nums[1] = nums[2] → nums = [-3, -1, -1, 0, 2]
  i=3: nums[2] = nums[3] → nums = [-3, -1, 0, 0, 2]
  i=4: nums[3] = nums[4] → nums = [-3, -1, 0, 2, 2]

Step 3: Place saved at end
  nums[4] = -5
  nums = [-3, -1, 0, 2, -5] ✓

(Even negative numbers work!)
```

### Trace 3: Two Elements [10, 20]

```
Initial: nums=[10, 20], size=2

Step 1: Save first
  temp = 10

Step 2: Shift left loop (i=1 to 1)
  i=1: nums[0] = nums[1] → nums = [20, 20]

Step 3: Place saved at end
  nums[1] = 10
  nums = [20, 10] ✓

(Just swaps the two elements!)
```

### Trace 4: Single Element [7]

```
Initial: nums=[7], size=1

Step 1: Save first
  temp = 7

Step 2: Shift left loop (i=1 to 0)
  No iterations (loop doesn't run since 1 < 1 is false)

Step 3: Place saved at end
  nums[0] = 7
  nums = [7] ✓

(Single element stays in place!)
```

### Trace 5: Duplicates [3, 3, 3, 3, 3]

```
Initial: nums=[3, 3, 3, 3, 3], size=5

Step 1: Save first
  temp = 3

Step 2: Shift left loop
  i=1: nums[0] = nums[1] → nums = [3, 3, 3, 3, 3]
  i=2: nums[1] = nums[2] → nums = [3, 3, 3, 3, 3]
  i=3: nums[2] = nums[3] → nums = [3, 3, 3, 3, 3]
  i=4: nums[3] = nums[4] → nums = [3, 3, 3, 3, 3]

Step 3: Place saved at end
  nums[4] = 3
  nums = [3, 3, 3, 3, 3] ✓

(All same, stays the same!)
```

### Trace 6: Large Values [100, 200, 300, 400]

```
Initial: nums=[100, 200, 300, 400], size=4

Step 1: Save first
  temp = 100

Step 2: Shift left loop
  i=1: nums[0] = nums[1] → nums = [200, 200, 300, 400]
  i=2: nums[1] = nums[2] → nums = [200, 300, 300, 400]
  i=3: nums[2] = nums[3] → nums = [200, 300, 400, 400]

Step 3: Place saved at end
  nums[3] = 100
  nums = [200, 300, 400, 100] ✓

(Works with any integer values!)
```

---

## Edge Cases

### Case 1: Single Element

```
Input: [5]
- temp = 5
- Loop doesn't run (i=1, size=1, 1 < 1 is false)
- nums[0] = temp = 5
Output: [5] ✓
(No change, which is correct!)
```

### Case 2: Two Elements

```
Input: [1, 2]
- temp = 1
- i=1: nums[0] = nums[1] → [2, 2]
- nums[1] = temp = 1 → [2, 1]
Output: [2, 1] ✓
(Elements swapped!)
```

### Case 3: All Zeros

```
Input: [0, 0, 0, 0]
- temp = 0
- All shifts just copy 0
- nums[3] = 0
Output: [0, 0, 0, 0] ✓
```

### Case 4: Alternating Values

```
Input: [1, 2, 1, 2, 1]
- temp = 1
- Shift: [2, 1, 2, 1, 1]
- Place: [2, 1, 2, 1, 1]
Output: [2, 1, 2, 1, 1] ✓
```

### Case 5: Very Large Array

```
Input: [1, 2, 3, ..., 1000]
- temp = 1
- Shift all 1000 elements
- nums[999] = 1
Output: [2, 3, 4, ..., 1000, 1] ✓
(Still O(n) time, no issues!)
```

### Case 6: Mixed Positive and Negative

```
Input: [-10, 5, -3, 8, 0]
- temp = -10
- Shift: [5, -3, 8, 0, 0]
- Place: [5, -3, 8, 0, -10]
Output: [5, -3, 8, 0, -10] ✓
```

---

## Time Complexity

- **O(n)** where n = array size
- Loop runs through all elements exactly once (from index 1 to n-1)
- Saving and placing are O(1) operations
- Total: 1 + n-1 + 1 = O(n)

---

## Space Complexity

- **O(1)** - Constant space
- Only using one variable `temp` to store one integer
- Modifying array in-place, no extra array created

---

## Key Insights

### Why We Need temp?

```
If we don't save first element:
[1, 2, 3, 4, 5]

Do nums[0] = nums[1]:
[2, 2, 3, 4, 5]

Oops! We lost the 1 forever! :(

By saving first:
temp = 1
[2, 2, 3, 4, 5]
...then place at end:
[2, 3, 4, 5, 1] ✓
(The 1 lives again at the end!)
```

### The Loop Pattern

```
Why start i from 1, not 0?

If we start from i=0:
nums[0-1] = nums[0]  ← nums[-1] is invalid!

Starting from i=1:
nums[0] = nums[1]  ← First valid operation
nums[1] = nums[2]  ← All good
nums[2] = nums[3]  ← All good
```

### Why Last Position Works

```
After the shift loop, the last position has:
[2, 3, 4, 5, 5]
               ↑ position size-1

This is a duplicate of position size-2.
We need to replace it with our saved first element:
[2, 3, 4, 5, 1]
               ↑ now has original first element
```

### Visualization of Motion

```
Original positions of elements:
[1, 2, 3, 4, 5]
 0  1  2  3  4

After left rotate by 1:
[2, 3, 4, 5, 1]
 0  1  2  3  4

Element tracking:
- 1 went from position 0 → position 4
- 2 went from position 1 → position 0
- 3 went from position 2 → position 1
- 4 went from position 3 → position 2
- 5 went from position 4 → position 3

Everyone moved one step left (cyclically!)
```

### In-Place Advantage

```
We could create new array:
vector<int> result;
for (int i=1; i<n; i++) result.push_back(nums[i]);
result.push_back(nums[0]);
// Extra O(n) space! ❌

Our approach:
Just shuffle elements in current array
// O(1) extra space! ✓
```

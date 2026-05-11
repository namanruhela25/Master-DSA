# Find First and Last Position of Element in Sorted Array

**Problem Link:** https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/

## What is this Problem?

Given a **sorted array** and a **target number**, you need to find:
- **First position** where the target appears
- **Last position** where the target appears

If the target doesn't exist, return `[-1, -1]`.

**Examples:**
```
Input: nums = [5, 7, 7, 8, 8, 10], target = 8
Output: [3, 4]
(8 appears at positions 3 and 4)

Input: nums = [5, 7, 7, 8, 8, 10], target = 6
Output: [-1, -1]
(6 doesn't exist)

Input: nums = [5, 7, 7, 8, 8, 10], target = 7
Output: [1, 2]
(7 appears at positions 1 and 2)
```

---

## The Problem Explained

Think of it like **finding a name in a sorted phone book**:

```
Phone book (sorted):
[Alice, Bob, Bob, Bob, Charlie, David]

Search for "Bob":
- Where does "Bob" START? Position 1
- Where does "Bob" END? Position 3
- Return: [1, 3]

You can't just find any "Bob" - need FIRST and LAST!
```

**Key insight:** Being sorted makes binary search possible. But we can't just find one occurrence - we need to find boundaries!

---

## HOOK TO REMEMBER FOREVER

**"TWO BINARY SEARCHES - FIND FIRST, FIND LAST"**

Every time you see "find first and last position":
- ✅ The array is sorted → use binary search!
- ✅ Do one binary search for leftmost position
- ✅ Do another binary search for rightmost position
- ✅ When target found, keep searching in that direction
- ✅ Return both positions as answer
- ✅ O(log n) is much faster than linear search!

**Remember: One find = any position, Two finds = boundaries!** 🎯

---

## How It Works Step By Step

### The Binary Search Approach

We use **binary search TWICE** with a twist:

**First search (find earliest):**
- When we find target, remember position
- Keep searching LEFT (high = mid - 1)
- This finds the leftmost occurrence

**Second search (find latest):**
- When we find target, remember position
- Keep searching RIGHT (low = mid + 1)
- This finds the rightmost occurrence

### Visual Example: [5, 7, 7, 8, 8, 10], target=8

```
Array: [5, 7, 7, 8, 8, 10]
Index:  0  1  2  3  4   5

FINDING FIRST POSITION (leftmost 8):

Binary search iteration 1:
  low=0, high=5, mid=2
  nums[2]=7 < 8 → low=3

Binary search iteration 2:
  low=3, high=5, mid=4
  nums[4]=8 == 8 → Found!
  ans=4, but search LEFT (high=3)

Binary search iteration 3:
  low=3, high=3, mid=3
  nums[3]=8 == 8 → Found!
  ans=3, search LEFT (high=2)

Binary search iteration 4:
  low=3, high=2 → Stop (low > high)
  First position = 3 ✓

FINDING LAST POSITION (rightmost 8):

Binary search iteration 1:
  low=0, high=5, mid=2
  nums[2]=7 < 8 → low=3

Binary search iteration 2:
  low=3, high=5, mid=4
  nums[4]=8 == 8 → Found!
  ans=4, search RIGHT (low=5)

Binary search iteration 3:
  low=5, high=5, mid=5
  nums[5]=10 > 8 → high=4

Binary search iteration 4:
  low=5, high=4 → Stop (low > high)
  Last position = 4 ✓

Answer: [3, 4] ✓
```

---

## Code Full Solution

### Approach 1: Custom Binary Search

```cpp
class Solution1WithBinarySearch {
public:
    int binarySearch(vector<int>& nums, int target, int leftTraverse) {
        int low = 0;
        int high = nums.size() - 1;
        int ans = -1;

        while(low <= high) {
            int mid = (low + high) / 2;
            if(nums[mid] > target) {
                high = mid - 1;
            } else if(nums[mid] < target) {
                low = mid + 1;
            } else {
                // Found target!
                ans = mid;
                if(leftTraverse) {
                    high = mid - 1;  // Search left for first
                } else {
                    low = mid + 1;   // Search right for last
                }
            }
        }
        return ans;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        int left = binarySearch(nums, target, true);   // Find first
        int right = binarySearch(nums, target, false); // Find last
        return {left, right};
    }
};
```

### Approach 2: Using STL Bounds

```cpp
class Solution2WithUpperBound {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        // lower_bound: first position >= target
        auto lower = lower_bound(nums.begin(), nums.end(), target);

        // Check if target exists
        if(lower == nums.end() || *lower != target) 
            return {-1, -1};

        // upper_bound: first position > target
        auto upper = upper_bound(nums.begin(), nums.end(), target);

        // Convert iterators to indices
        return {int(lower - nums.begin()), int((upper - nums.begin()) - 1)};
    }
};
```

---

## Code Explanation (Approach 1 - Clearer for Learning)

### Helper Function: binarySearch()

```cpp
int binarySearch(vector<int>& nums, int target, int leftTraverse) {
    int low = 0;
    int high = nums.size() - 1;
    int ans = -1;
```

- **`low, high`:** Binary search boundaries
- **`ans = -1`:** Default if target not found
- **`leftTraverse`:** Flag to determine direction:
  - `true` = find first position (search left)
  - `false` = find last position (search right)

---

### Standard Binary Search Logic

```cpp
while(low <= high) {
    int mid = (low + high) / 2;
    if(nums[mid] > target) {
        high = mid - 1;
    } else if(nums[mid] < target) {
        low = mid + 1;
    } else {
        // Found target - HERE'S THE TRICK!
```

- **Compare:** nums[mid] with target
- **Standard binary search:** Would just return mid here
- **Our approach:** Found it! But keep searching for boundaries

---

### The Boundary Search

```cpp
    } else {
        // Target found!
        ans = mid;
        if(leftTraverse) {
            high = mid - 1;  // Continue searching LEFT
        } else {
            low = mid + 1;   // Continue searching RIGHT
        }
    }
}
```

**When target found:**
- Save current position in `ans`
- **If leftTraverse=true:** Search left (high = mid-1)
  - Looking for earlier occurrences
  - Will update ans if found more to the left
- **If leftTraverse=false:** Search right (low = mid+1)
  - Looking for later occurrences
  - Will update ans if found more to the right

```cpp
return ans;
```

- Return -1 if never found
- Return first occurrence if leftTraverse=true
- Return last occurrence if leftTraverse=false

---

### Main Function

```cpp
vector<int> searchRange(vector<int>& nums, int target) {
    int left = binarySearch(nums, target, true);   // First position
    int right = binarySearch(nums, target, false); // Last position
    return {left, right};
}
```

- Call binary search twice
- First with `leftTraverse=true` to find leftmost
- Second with `leftTraverse=false` to find rightmost
- Return both as array `[left, right]`

---

## Complete Example Traces

### Trace 1: Standard Case [5, 7, 7, 8, 8, 10], target=8

```
FINDING FIRST POSITION:
binarySearch(nums, 8, true)

Iteration 1:
  low=0, high=5, mid=2
  nums[2]=7 < 8 → low=3

Iteration 2:
  low=3, high=5, mid=4
  nums[4]=8 == 8 → ans=4
  leftTraverse=true → high=3

Iteration 3:
  low=3, high=3, mid=3
  nums[3]=8 == 8 → ans=3
  leftTraverse=true → high=2

Iteration 4:
  low=3, high=2 → low > high, stop

Return: 3 ✓

FINDING LAST POSITION:
binarySearch(nums, 8, false)

Iteration 1:
  low=0, high=5, mid=2
  nums[2]=7 < 8 → low=3

Iteration 2:
  low=3, high=5, mid=4
  nums[4]=8 == 8 → ans=4
  leftTraverse=false → low=5

Iteration 3:
  low=5, high=5, mid=5
  nums[5]=10 > 8 → high=4

Iteration 4:
  low=5, high=4 → low > high, stop

Return: 4 ✓

Final answer: [3, 4] ✓
```

### Trace 2: Target Not Found [5, 7, 7, 8, 8, 10], target=6

```
FINDING FIRST POSITION:
binarySearch(nums, 6, true)

Iteration 1:
  low=0, high=5, mid=2
  nums[2]=7 > 6 → high=1

Iteration 2:
  low=0, high=1, mid=0
  nums[0]=5 < 6 → low=1

Iteration 3:
  low=1, high=1, mid=1
  nums[1]=7 > 6 → high=0

Iteration 4:
  low=1, high=0 → low > high, stop

Return: -1 ✓

FINDING LAST POSITION:
(Also returns -1)

Final answer: [-1, -1] ✓
```

### Trace 3: Single Element [8], target=8

```
FINDING FIRST POSITION:
binarySearch(nums, 8, true)

Iteration 1:
  low=0, high=0, mid=0
  nums[0]=8 == 8 → ans=0
  leftTraverse=true → high=-1

Iteration 2:
  low=0, high=-1 → low > high, stop

Return: 0 ✓

FINDING LAST POSITION:
binarySearch(nums, 8, false)

Iteration 1:
  low=0, high=0, mid=0
  nums[0]=8 == 8 → ans=0
  leftTraverse=false → low=1

Iteration 2:
  low=1, high=0 → low > high, stop

Return: 0 ✓

Final answer: [0, 0] ✓
```

### Trace 4: Element Entire Array [7, 7, 7, 7], target=7

```
FINDING FIRST POSITION:
binarySearch(nums, 7, true)

Iteration 1:
  low=0, high=3, mid=1
  nums[1]=7 == 7 → ans=1
  leftTraverse=true → high=0

Iteration 2:
  low=0, high=0, mid=0
  nums[0]=7 == 7 → ans=0
  leftTraverse=true → high=-1

Iteration 3:
  low=0, high=-1 → stop

Return: 0 ✓

FINDING LAST POSITION:
binarySearch(nums, 7, false)

Iteration 1:
  low=0, high=3, mid=1
  nums[1]=7 == 7 → ans=1
  leftTraverse=false → low=2

Iteration 2:
  low=2, high=3, mid=2
  nums[2]=7 == 7 → ans=2
  leftTraverse=false → low=3

Iteration 3:
  low=3, high=3, mid=3
  nums[3]=7 == 7 → ans=3
  leftTraverse=false → low=4

Iteration 4:
  low=4, high=3 → stop

Return: 3 ✓

Final answer: [0, 3] ✓
```

### Trace 5: Target at Start [8, 8, 9, 10], target=8

```
FINDING FIRST POSITION:
binarySearch(nums, 8, true)

Iteration 1:
  low=0, high=3, mid=1
  nums[1]=8 == 8 → ans=1
  leftTraverse=true → high=0

Iteration 2:
  low=0, high=0, mid=0
  nums[0]=8 == 8 → ans=0
  leftTraverse=true → high=-1

Iteration 3:
  low=0, high=-1 → stop

Return: 0 ✓

FINDING LAST POSITION:
binarySearch(nums, 8, false)

Iteration 1:
  low=0, high=3, mid=1
  nums[1]=8 == 8 → ans=1
  leftTraverse=false → low=2

Iteration 2:
  low=2, high=3, mid=2
  nums[2]=9 > 8 → high=1

Iteration 3:
  low=2, high=1 → stop

Return: 1 ✓

Final answer: [0, 1] ✓
```

### Trace 6: Target at End [5, 6, 7, 8, 8], target=8

```
FINDING FIRST POSITION:
binarySearch(nums, 8, true)

Iteration 1:
  low=0, high=4, mid=2
  nums[2]=7 < 8 → low=3

Iteration 2:
  low=3, high=4, mid=3
  nums[3]=8 == 8 → ans=3
  leftTraverse=true → high=2

Iteration 3:
  low=3, high=2 → stop

Return: 3 ✓

FINDING LAST POSITION:
binarySearch(nums, 8, false)

Iteration 1:
  low=0, high=4, mid=2
  nums[2]=7 < 8 → low=3

Iteration 2:
  low=3, high=4, mid=3
  nums[3]=8 == 8 → ans=3
  leftTraverse=false → low=4

Iteration 3:
  low=4, high=4, mid=4
  nums[4]=8 == 8 → ans=4
  leftTraverse=false → low=5

Iteration 4:
  low=5, high=4 → stop

Return: 4 ✓

Final answer: [3, 4] ✓
```

---

## Edge Cases

### Case 1: Target Not in Array

```
Input: [5, 7, 9, 10], target = 8
- binary search never finds nums[mid]==8
- ans stays -1
- Return: [-1, -1] ✓
```

### Case 2: Single Element (Match)

```
Input: [5], target = 5
- First binary search finds at 0, searches left (no more)
- Last binary search finds at 0, searches right (no more)
- Return: [0, 0] ✓
```

### Case 3: Single Element (No Match)

```
Input: [5], target = 3
- Binary search never finds match
- Return: [-1, -1] ✓
```

### Case 4: All Same Elements

```
Input: [7, 7, 7, 7, 7], target = 7
- First search finds any 7, keeps going left to 0
- Last search finds any 7, keeps going right to 4
- Return: [0, 4] ✓
```

### Case 5: Target at Boundaries

```
Input: [1, 2, 3, 4, 5], target = 1
- Find first at index 0
- Find last at index 0 (only one occurrence)
- Return: [0, 0] ✓

Input: [1, 2, 3, 4, 5], target = 5
- Find first at index 4
- Find last at index 4 (only one occurrence)
- Return: [4, 4] ✓
```

### Case 6: Large Array

```
Input: [1, 2, ..., 50000, 50000, 50000, ..., 100000], target = 50000
- Binary search efficiently finds boundaries
- Works in O(log n) time ✓
```

---

## Time Complexity

- **O(log n)** where n = array size
- Binary search = O(log n) per call
- We call it twice = 2 × O(log n) = O(log n)
- Much faster than linear scan O(n)!

---

## Space Complexity

- **O(1)** - Constant space
- Only using integer variables (low, high, mid, ans)
- No extra arrays or data structures
- Approach 2 with iterators also O(1) space

---

## Key Insights

### Why Binary Search Works Here?

```
Linear scan would be O(n):
[5, 7, 7, 8, 8, 10]
Scan every element until finding 8

Binary search is O(log n):
Check middle, eliminate half, repeat
Much faster!

And sorted array makes binary search possible!
```

### The Boundary Search Trick

```
Normal binary search:
When found target → return immediately

Our approach:
When found target → remember position
But keep searching in that direction!

First search looks left:
[5, 7, 7, 8, 8, 10]
        ↑ found 8, but is there an earlier 8?

Last search looks right:
[5, 7, 7, 8, 8, 10]
              ↑ found 8, but is there a later 8?
```

### Why Two Calls?

```
We could do one binary search and:
- From position found, scan left to find first
- From position found, scan right to find last
Time: O(log n) + O(k) where k = occurrences of target ❌

Our approach:
- Two binary searches
- Each one efficiently finds boundary
Time: 2 × O(log n) = O(log n) ✓

Better because we don't scan!
```

### Approach 1 vs Approach 2

```
Approach 1: Custom binary search
- More code to write
- Clearer logic
- Good for learning

Approach 2: STL Functions
- Less code
- Standard library handles details
- More concise

Both are O(log n) time!
```

### Why leftTraverse Parameter?

```
Instead of writing two separate binary searches,
we use one function with a flag:

leftTraverse=true:
- When target found, search LEFT
- Finds first occurrence

leftTraverse=false:
- When target found, search RIGHT
- Finds last occurrence

This avoids code duplication!
```

### Why Not Just Find Any Occurrence?

```
If we could return any occurrence:
[5, 7, 7, 8, 8, 10]
Return [3, 3] or [3, 4]

But problem asks for FIRST and LAST
Real use case: "Show all products with rating 4-stars"
Need to find entire range, not just one!
```

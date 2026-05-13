# Intersection of Two Arrays II

**Problem Link:** https://leetcode.com/problems/intersection-of-two-arrays-ii/

## What is this Problem?

Given two **arrays**, find all elements that **appear in both arrays**. 

Key points:
- **Each element in result must appear as many times as shown in both arrays**
- You can return the result in any order
- **If an element appears 2 times in nums1 and 3 times in nums2, it should appear 2 times in result** (minimum of occurrences)

**Examples:**
```
Input: nums1 = [1, 2, 2, 1], nums2 = [2, 2]
Output: [2, 2]
(2 appears in both, so include both occurrences of 2)

Input: nums1 = [4, 9, 5], nums2 = [9, 4, 9, 8, 4]
Output: [4, 9] or [9, 4]
(4 and 9 appear in both, just once each)

Input: nums1 = [1, 2, 3], nums2 = [4, 5, 6]
Output: []
(No common elements)
```

---

## The Problem Explained

Think of it like **finding common friends between two people**:

```
Person A's friends: [Alice, Bob, Charlie, Bob]
Person B's friends: [Bob, Charlie, David, Bob]

Common friends: [Bob, Charlie]

Why Bob twice? Because both have Bob in their list twice!
(minimum of 2 and 2 = 2)

If Person A had Bob 3 times and Person B had Bob 2 times:
Common would be [Bob, Bob] (minimum = 2)
```

**Key insight:** Count occurrences! Return minimum of how many times element appears in both arrays.

---

## HOOK TO REMEMBER FOREVER

**"SORT BOTH, TWO POINTERS, FIND COMMON"**

Every time you see "intersection of two arrays":
- ✅ Sort both arrays first
- ✅ Use two pointers starting at beginning of each
- ✅ Compare elements at both pointers:
  - If equal → common element! Add to result, move both forward
  - If first smaller → move first pointer forward
  - If second smaller → move second pointer forward
- ✅ Handles duplicates automatically (count based on minimum)
- ✅ O(n log n) due to sorting, O(1) space for pointers!

**Remember: When sorted, find common by walking forward together!** 🤝

---

## How It Works Step By Step

### The Two-Pointer Strategy After Sorting

```
nums1 = [1, 2, 2, 1]
nums2 = [2, 2]

Step 1: Sort both arrays
  nums1 = [1, 1, 2, 2]
  nums2 = [2, 2]

Step 2: Use two pointers
  i = 0 (points to nums1)
  j = 0 (points to nums2)

Step 3: Compare and move
  - If nums1[i] < nums2[j]: move i forward (1 < 2, so i++)
  - If nums1[i] > nums2[j]: move j forward
  - If nums1[i] == nums2[j]: found common! Add and move both forward
```

### Visual Example: [1, 2, 2, 1] and [2, 2]

```
After sorting:
nums1 = [1, 1, 2, 2]
nums2 = [2, 2]

Iteration 1:
  i=0, j=0
  nums1[0]=1, nums2[0]=2
  1 < 2? YES → i++
  
Iteration 2:
  i=1, j=0
  nums1[1]=1, nums2[0]=2
  1 < 2? YES → i++

Iteration 3:
  i=2, j=0
  nums1[2]=2, nums2[0]=2
  2 == 2? YES! Common found!
  ans = [2]
  i++, j++

Iteration 4:
  i=3, j=1
  nums1[3]=2, nums2[1]=2
  2 == 2? YES! Common found!
  ans = [2, 2]
  i++, j++

i=4, j=2
Both reached end (i < n is false, j < m is false)

Result: [2, 2] ✓
```

---

## Code Full Solution

```cpp
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ans;

        // Sort both arrays
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());

        // Two pointers approach
        int i = 0, j = 0;
        int n = nums1.size();
        int m = nums2.size();

        while(i < n && j < m) {
            if(nums1[i] < nums2[j]) {
                i++;
            } else if(nums2[j] < nums1[i]) {
                j++;
            } else {
                // Found common element
                ans.push_back(nums1[i]);
                i++;
                j++;
            }
        }

        return ans;
    }
};
```

---

## Code Explanation

### Initialize Result Array

```cpp
vector<int> ans;
```

- **`ans`:** Stores common elements found
- Will add elements when both pointers match
- Return this at the end

---

### Sort Both Arrays

```cpp
sort(nums1.begin(), nums1.end());
sort(nums2.begin(), nums2.end());
```

- **Why sort?** Makes finding common elements efficient with two pointers
- **How?** Identical elements will be adjacent after sorting
- **Example:** [1, 2, 2, 1] → [1, 1, 2, 2]
- **Time:** O(n log n) for each array

**Benefits of sorting:**
```
Before: [4, 1, 9, 9] and [9, 4, 9, 8, 4]
After:  [1, 4, 9, 9] and [4, 4, 8, 9, 9]

Now can walk through simultaneously!
```

---

### Initialize Two Pointers

```cpp
int i = 0, j = 0;
int n = nums1.size();
int m = nums2.size();
```

- **`i = 0`:** Pointer for nums1 (starts at beginning)
- **`j = 0`:** Pointer for nums2 (starts at beginning)
- **`n`:** Size of nums1
- **`m`:** Size of nums2

---

### Two-Pointer Loop

```cpp
while(i < n && j < m) {
```

- **Continue while:** Both pointers haven't reached end
- **Stops when:** Either pointer reaches end of its array
- **Why?** Once one array is exhausted, no more matches possible

```
Example:
nums1 = [1, 1] (n=2)
nums2 = [2, 2] (m=2)

- When i reaches 2, stop (exhausted nums1)
- When j reaches 2, stop (exhausted nums2)
```

---

### Compare and Move Logic

```cpp
if(nums1[i] < nums2[j]) {
    i++;
} else if(nums2[j] < nums1[i]) {
    j++;
} else {
    // nums1[i] == nums2[j]
    ans.push_back(nums1[i]);
    i++;
    j++;
}
```

**Three cases:**

1. **`nums1[i] < nums2[j]`:** First smaller
   - nums1[i] can't match anything in nums2 (nums2 is sorted)
   - Move i forward to try next element
   - Skip j for now

2. **`nums2[j] < nums1[i]`:** Second smaller
   - nums2[j] can't match anything remaining in nums1
   - Move j forward to try next element
   - Skip i for now

3. **`nums1[i] == nums2[j]`:** Match found!
   - This element is in both arrays
   - Add to result
   - Move both forward (already used both)

**Example walkthrough:**
```cpp
nums1 = [1, 2, 3], nums2 = [2, 3, 4]

i=0, j=0: 1 < 2? YES → i++
i=1, j=0: 2 == 2? YES → ans=[2], i++, j++
i=2, j=1: 3 == 3? YES → ans=[2,3], i++, j++
i=3: exit loop (i < 3 is false)

Result: [2, 3] ✓
```

---

## Complete Example Traces

### Trace 1: With Duplicates [1, 2, 2, 1], [2, 2]

```
Initial: nums1=[1, 2, 2, 1], nums2=[2, 2]

After sort:
  nums1=[1, 1, 2, 2], nums2=[2, 2]
  ans=[], i=0, j=0, n=4, m=2

Iteration 1:
  i=0, j=0
  nums1[0]=1, nums2[0]=2
  1 < 2? YES → i=1

Iteration 2:
  i=1, j=0
  nums1[1]=1, nums2[0]=2
  1 < 2? YES → i=2

Iteration 3:
  i=2, j=0
  nums1[2]=2, nums2[0]=2
  2 == 2? YES!
  ans=[2], i=3, j=1

Iteration 4:
  i=3, j=1
  nums1[3]=2, nums2[1]=2
  2 == 2? YES!
  ans=[2, 2], i=4, j=2

Loop condition: i < 4? 4 < 4 is false → exit

Return: [2, 2] ✓
```

### Trace 2: No Common Elements [1, 2], [3, 4]

```
Initial: nums1=[1, 2], nums2=[3, 4]

After sort:
  nums1=[1, 2], nums2=[3, 4]
  ans=[], i=0, j=0, n=2, m=2

Iteration 1:
  i=0, j=0
  nums1[0]=1, nums2[0]=3
  1 < 3? YES → i=1

Iteration 2:
  i=1, j=0
  nums1[1]=2, nums2[0]=3
  2 < 3? YES → i=2

Loop condition: i < 2? 2 < 2 is false → exit

Return: [] ✓
(No elements added, both pointed to non-matching)
```

### Trace 3: All Common [1, 2, 3], [3, 2, 1]

```
Initial: nums1=[1, 2, 3], nums2=[3, 2, 1]

After sort:
  nums1=[1, 2, 3], nums2=[1, 2, 3]
  ans=[], i=0, j=0, n=3, m=3

Iteration 1:
  nums1[0]=1, nums2[0]=1
  1 == 1? YES
  ans=[1], i=1, j=1

Iteration 2:
  nums1[1]=2, nums2[1]=2
  2 == 2? YES
  ans=[1, 2], i=2, j=2

Iteration 3:
  nums1[2]=3, nums2[2]=3
  3 == 3? YES
  ans=[1, 2, 3], i=3, j=3

Loop condition: i < 3? 3 < 3 is false → exit

Return: [1, 2, 3] ✓
```

### Trace 4: Different Lengths [1, 2], [1, 2, 3, 4]

```
Initial: nums1=[1, 2], nums2=[1, 2, 3, 4]

After sort:
  nums1=[1, 2], nums2=[1, 2, 3, 4]
  ans=[], i=0, j=0, n=2, m=4

Iteration 1:
  nums1[0]=1, nums2[0]=1
  1 == 1? YES
  ans=[1], i=1, j=1

Iteration 2:
  nums1[1]=2, nums2[1]=2
  2 == 2? YES
  ans=[1, 2], i=2, j=2

Loop condition: i < 2? 2 < 2 is false → exit

Return: [1, 2] ✓
(nums2 has 3, 4 but nums1 exhausted)
```

### Trace 5: Unsorted Input [4, 9, 5], [9, 4, 9, 8, 4]

```
Initial: nums1=[4, 9, 5], nums2=[9, 4, 9, 8, 4]

After sort:
  nums1=[4, 5, 9], nums2=[4, 4, 8, 9, 9]
  ans=[], i=0, j=0, n=3, m=5

Iteration 1:
  i=0, j=0
  nums1[0]=4, nums2[0]=4
  4 == 4? YES
  ans=[4], i=1, j=1

Iteration 2:
  i=1, j=1
  nums1[1]=5, nums2[1]=4
  5 > 4? 4 < 5? YES → j=2

Iteration 3:
  i=1, j=2
  nums1[1]=5, nums2[2]=8
  5 < 8? YES → i=2

Iteration 4:
  i=2, j=2
  nums1[2]=9, nums2[2]=8
  9 > 8? 8 < 9? YES → j=3

Iteration 5:
  i=2, j=3
  nums1[2]=9, nums2[3]=9
  9 == 9? YES
  ans=[4, 9], i=3, j=4

Loop condition: i < 3? 3 < 3 is false → exit

Return: [4, 9] ✓
```

### Trace 6: Single Element [1], [1]

```
Initial: nums1=[1], nums2=[1]

After sort:
  nums1=[1], nums2=[1]
  ans=[], i=0, j=0, n=1, m=1

Iteration 1:
  i=0, j=0
  nums1[0]=1, nums2[0]=1
  1 == 1? YES
  ans=[1], i=1, j=1

Loop condition: i < 1? 1 < 1 is false → exit

Return: [1] ✓
```

### Trace 7: Multiple Duplicates [1, 1, 1], [1, 1]

```
Initial: nums1=[1, 1, 1], nums2=[1, 1]

After sort:
  nums1=[1, 1, 1], nums2=[1, 1]
  ans=[], i=0, j=0, n=3, m=2

Iteration 1:
  nums1[0]=1, nums2[0]=1
  1 == 1? YES
  ans=[1], i=1, j=1

Iteration 2:
  nums1[1]=1, nums2[1]=1
  1 == 1? YES
  ans=[1, 1], i=2, j=2

Loop condition: j < 2? 2 < 2 is false → exit

Return: [1, 1] ✓
(Takes minimum occurrences: min(3, 2) = 2)
```

---

## Edge Cases

### Case 1: Empty Array

```
Input: nums1 = [], nums2 = [1, 2]
- After sort: nums1 = [], nums2 = [1, 2]
- Loop condition: 0 < 0 is false (doesn't run)
Output: [] ✓
```

### Case 2: Both Empty

```
Input: nums1 = [], nums2 = []
- Loop doesn't run
Output: [] ✓
```

### Case 3: Single Element Each (No Match)

```
Input: nums1 = [1], nums2 = [2]
- i=0, j=0: 1 < 2? YES → i=1
- Loop ends (i < 1 is false)
Output: [] ✓
```

### Case 4: All Duplicates in First Only

```
Input: nums1 = [1, 1, 1, 1], nums2 = [1]
- After sort: same
- i=0, j=0: 1==1? YES → ans=[1], i=1, j=1
- Loop ends (j < 1 is false)
Output: [1] ✓
(Minimum of 4 and 1 = 1)
```

### Case 5: Negative Numbers

```
Input: nums1 = [-1, 0, 1], nums2 = [0, -1, 1]
- After sort: [-1, 0, 1] and [-1, 0, 1]
- Finds all: [-1, 0, 1]
Output: [-1, 0, 1] ✓
```

### Case 6: Large Array with Few Common

```
Input: nums1 = [1, 2, 3, ..., 1000], nums2 = [500, 1000]
- Efficient two-pointer approach O(n log n)
Output: [500, 1000] ✓
```

---

## Time Complexity

- **Sorting nums1:** O(n log n)
- **Sorting nums2:** O(m log n)
- **Two-pointer traversal:** O(n + m)
- **Total:** O(n log n + m log m)

Where n = length of nums1, m = length of nums2

---

## Space Complexity

- **O(1)** excluding output array
- Only using two integer pointers (i, j)
- Some systems count sorting space:
  - If in-place sort: O(1)
  - If not in-place: O(log n) or O(log m)
- Output array size: O(min(n, m)) in worst case

---

## Key Insights

### Why Sort First?

```
Unsorted approach:
[1, 4, 9, 5] and [9, 4, 9, 8, 4]

For each element in nums1, search in nums2:
- Search for 1: not found
- Search for 4: found (but where? scan entire nums2)
- Search for 9: found
- Search for 5: not found

Time: O(n × m) with searching ❌

Sorted approach:
[4, 5, 9, 1] → [1, 4, 5, 9]
[4, 4, 8, 9, 9] → [4, 4, 8, 9, 9]

Two pointers walk together efficiently
Time: O(n log n + m log m) ✓
```

### Two-Pointer Magic

```
Both sorted arrays enable efficient traversal:

nums1 = [1, 4, 5, 9]
nums2 = [4, 4, 8, 9, 9]
         ↑
         If nums1[i] < nums2[j]:
         nums1[i] can't match anything after nums2[j]
         (since nums2 is sorted, everything after is >= nums2[j])
         So skip nums1[i], move i forward ✓
```

### Duplicate Handling

```
nums1 = [1, 1, 1], nums2 = [1, 1]

After sorting, both have 1s grouped:
Compare position by position:
- 1 == 1? YES (first from each)
- 1 == 1? YES (second from each)
- nums1 has third 1, but nums2 exhausted

Result: [1, 1] (exactly minimum occurrences!) ✓

No special duplicate logic needed!
```

### Alternative Approaches

```
Approach 1 (Our solution): Two pointers with sorting
- Time: O(n log n + m log m)
- Space: O(1) extra (excluding output)
- Clean, efficient

Approach 2: HashMap counter
- Time: O(n + m)
- Space: O(min(n, m))
- Fast but uses extra space

Approach 3: Binary search in sorted array
- Time: O(n log m) or O(m log n)
- Space: O(1)
- Good if one array very large

For this problem, two-pointer is elegant!
```

### Why Compare at Same Position?

```
After sorting:
nums1 = [1, 2, 4, 6]
nums2 = [2, 4, 5, 7]

Two pointers guarantee:
- All elements to left of i in nums1 < all to right
- All elements to left of j in nums2 < all to right

When nums1[i] < nums2[j]:
- nums1[i] is smaller than current nums2[j]
- nums1[i] can't match anything from j onwards (all are >= nums2[j])
- Skip nums1[i] safely ✓

This only works because arrays are sorted!
```

### Why Return Minimum Count?

```
Problem: "Each element must appear as many times
         as shown in both arrays"

This means minimum of occurrences!

nums1 = [1, 1, 1], nums2 = [1, 1]
- Element 1 appears 3 times in nums1
- Element 1 appears 2 times in nums2
- Answer should have 1 twice (minimum)

Two pointers naturally does this!
When both match, both move forward.
If one exhausts before other, stop getting matches.
```

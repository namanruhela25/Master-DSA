# Linear Search

**Problem Link:** https://www.geeksforgeeks.org/problems/search-an-element-in-an-array-1587115621/1

## What is this Problem?

You have an **unsorted array** and you need to **find the position of a target element**.

Simply:
- **Scan through the array from start to end**
- **When you find the target, return its index**
- **If not found, return -1**

**Examples:**
```
Array: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 56, 67, 89, 45]
Search for: 10
Output: 9 (element 10 is at index 9)

Search for: 45
Output: 14 (element 45 is at index 14)

Search for: 100
Output: -1 (element 100 not found)
```

---

## The Problem Explained

Think of it like **searching for a book in a messy library shelf**:

```
Shelf: [Math, Science, History, English, Art, History, Music]

Looking for: History

Step 1: Check position 0 → Math (not it)
Step 2: Check position 1 → Science (not it)
Step 3: Check position 2 → History (FOUND!)
Return position 2

Keep moving forward until you find it!
```

**Key insight:** Books aren't organized, so you can't use binary search. Just check each one!

---

## HOOK TO REMEMBER FOREVER

**"START AT ZERO, CHECK EACH, RETURN INDEX"**

Every time you see "search in array" or "find element":
- ✅ Start from first element (index 0)
- ✅ Compare each element with target
- ✅ When match found, return that index immediately
- ✅ If reached the end without finding, return -1
- ✅ O(n) time - simple but works for unsorted arrays!
- ✅ Sometimes called "sequential search"

**Remember: One element at a time, check, move forward!** 🔍

---

## How It Works Step By Step

### The Simple Strategy

```
Array: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
Search for: 8

Step 1: Check index 0, value 1
  1 == 8? NO → continue

Step 2: Check index 1, value 2
  2 == 8? NO → continue

Step 3: Check index 2, value 3
  3 == 8? NO → continue

... (similar checks) ...

Step 8: Check index 7, value 8
  8 == 8? YES! → return 7

Answer: 7 ✓
```

### Visual Example: [1, 2, 3, 4, 5], search for 4

```
Array:    [1, 2, 3, 4, 5]
Index:     0  1  2  3  4

i=0: arr[0]=1 == 4? NO
  ❌

i=1: arr[1]=2 == 4? NO
  ❌

i=2: arr[2]=3 == 4? NO
  ❌

i=3: arr[3]=4 == 4? YES!
  ✓ FOUND! Return 3
```

---

## Code Full Solution

```cpp
int search(int arr[], int n, int num) {
    int i;
    
    // Loop through each element
    for(i = 0; i < n; i++) {
        // Check if current element matches target
        if(arr[i] == num) {
            return i;  // Found! Return index
        }
    }
    
    // Reached end without finding
    return -1;
}
```

---

## Code Explanation

### Function Signature

```cpp
int search(int arr[], int n, int num) {
```

- **`arr[]`:** Array to search in
- **`n`:** Number of elements in array
- **`num`:** Target element to find
- **Returns:** Index if found, -1 if not found

---

### Initialize Loop Variable

```cpp
int i;
```

- **`i`:** Loop counter (index position)
- Will go from 0 to n-1
- Checks each position in array

---

### Loop Through Each Element

```cpp
for(i = 0; i < n; i++) {
```

- **`i = 0`:** Start from first element (index 0)
- **`i < n`:** Continue while i is less than array size
- **`i++`:** Move to next element after each iteration

**Example for array of size 5:**
```
i=0 → check arr[0]
i=1 → check arr[1]
i=2 → check arr[2]
i=3 → check arr[3]
i=4 → check arr[4]
i=5 → condition false, exit
```

---

### Check Current Element

```cpp
    if(arr[i] == num) {
        return i;
    }
```

- **Compare:** arr[i] with target num
- **If match:** We found it! Return the index i immediately
- **No match:** Continue to next element

**Why return immediately?**
- First occurrence is all we need
- No point checking rest of array
- Saves time on average

---

### Not Found Path

```cpp
return -1;
```

- If loop completes without finding match
- Array doesn't contain the target
- Return -1 as "not found" signal

---

## Complete Example Traces

### Trace 1: Element Found at Different Positions [1, 2, 3, 4, 5], search 3

```
Initial: arr=[1, 2, 3, 4, 5], n=5, num=3

i=0: arr[0]=1
  1 == 3? NO → continue

i=1: arr[1]=2
  2 == 3? NO → continue

i=2: arr[2]=3
  3 == 3? YES! → return 2

Result: 2 ✓
(3 is at index 2)
```

### Trace 2: Element at Start [10, 20, 30, 40], search 10

```
Initial: arr=[10, 20, 30, 40], n=4, num=10

i=0: arr[0]=10
  10 == 10? YES! → return 0

Result: 0 ✓
(Found immediately at first position!)
```

### Trace 3: Element at End [1, 2, 3, 4, 5], search 5

```
Initial: arr=[1, 2, 3, 4, 5], n=5, num=5

i=0: arr[0]=1
  1 == 5? NO

i=1: arr[1]=2
  2 == 5? NO

i=2: arr[2]=3
  3 == 5? NO

i=3: arr[3]=4
  4 == 5? NO

i=4: arr[4]=5
  5 == 5? YES! → return 4

Result: 4 ✓
(Found at last position after checking all previous)
```

### Trace 4: Element Not Found [1, 2, 3, 4, 5], search 10

```
Initial: arr=[1, 2, 3, 4, 5], n=5, num=10

i=0: arr[0]=1
  1 == 10? NO

i=1: arr[1]=2
  2 == 10? NO

i=2: arr[2]=3
  3 == 10? NO

i=3: arr[3]=4
  4 == 10? NO

i=4: arr[4]=5
  5 == 10? NO

i=5: condition 5 < 5 is false, exit loop

return -1

Result: -1 ✓
(Not found, searched all elements)
```

### Trace 5: Single Element Array [7], search 7

```
Initial: arr=[7], n=1, num=7

i=0: arr[0]=7
  7 == 7? YES! → return 0

Result: 0 ✓
```

### Trace 6: Duplicates [1, 3, 3, 3, 5], search 3

```
Initial: arr=[1, 3, 3, 3, 5], n=5, num=3

i=0: arr[0]=1
  1 == 3? NO

i=1: arr[1]=3
  3 == 3? YES! → return 1

Result: 1 ✓
(Returns first occurrence of 3)
```

### Trace 7: Large Array [56, 67, 89, 45, ...], search 89

```
Initial: arr=[...many elements...], n=?, num=89

i=0: arr[0]=56
  56 == 89? NO

i=1: arr[1]=67
  67 == 89? NO

i=2: arr[2]=89
  89 == 89? YES! → return 2

Result: 2 ✓
```

---

## Edge Cases

### Case 1: Single Element (Found)

```
Input: arr=[5], n=1, num=5
- i=0: 5 == 5? YES
Output: 0 ✓
```

### Case 2: Single Element (Not Found)

```
Input: arr=[5], n=1, num=3
- i=0: 5 == 3? NO
- Loop ends
Output: -1 ✓
```

### Case 3: Empty Array

```
Input: arr=[], n=0, num=5
- Loop condition 0 < 0 is false (doesn't run)
Output: -1 ✓
```

### Case 4: All Same Elements

```
Input: arr=[5, 5, 5, 5], n=4, num=5
- i=0: 5 == 5? YES!
Output: 0 ✓
(Returns first occurrence)
```

### Case 5: Negative Numbers

```
Input: arr=[-1, -5, 3, -10], n=4, num=-5
- i=0: -1 == -5? NO
- i=1: -5 == -5? YES!
Output: 1 ✓
```

### Case 6: Zero in Array

```
Input: arr=[1, 0, 3, 0, 5], n=5, num=0
- i=0: 1 == 0? NO
- i=1: 0 == 0? YES!
Output: 1 ✓
```

---

## Time Complexity

- **Best case: O(1)**
  - Element found at first position
  - Return immediately
  - Example: search 1 in [1, 2, 3, 4, 5]

- **Worst case: O(n)**
  - Element found at last position or not found
  - Check every element
  - Example: search 5 in [1, 2, 3, 4, 5]

- **Average case: O(n)**
  - On average, need to check half the array
  - Still O(n) complexity

---

## Space Complexity

- **O(1)** - Constant space
- Only using one variable `i` for loop counter
- No extra arrays or data structures
- Array passed by reference, not copied

---

## Key Insights

### Why Not Binary Search?

```
Linear Search:
- Works on ANY array (sorted or unsorted)
- O(n) time
- Simple to implement

Binary Search:
- Only works on SORTED arrays
- O(log n) time
- Requires sorting first (O(n log n))

For unsorted arrays: Linear search is only option!
```

### When Linear Search is Good?

```
✓ Array is small (< 100 elements)
  O(n) is fine, implementation simple

✓ Array is unsorted
  Binary search not possible

✓ Searching once
  Sorting cost isn't worth it

✓ Array changes frequently
  Maintaining sorted order is expensive
```

### When Linear Search is Bad?

```
✗ Large unsorted array (millions of elements)
  O(n) is slow

✗ Many searches on same array
  Should sort once, then binary search each time
  Cost of sorting amortized over many searches

✗ Array is already sorted
  Should use binary search O(log n)
```

### Return Early Optimization

```
Bad approach:
for(i = 0; i < n; i++) {
    if(arr[i] == num)
        count++;  // Keep counting after found ❌
}
return count > 0 ? index : -1;

Good approach:
for(i = 0; i < n; i++) {
    if(arr[i] == num)
        return i;  // Return immediately ✓
}
return -1;

Our solution does this correctly!
```

### Why Return Index, Not Value?

```
Could return:
- The value itself: arr[i]
  Problem: Can't distinguish "not found"
  What if searching for -1 but not found?
  
Should return:
- The index: i
  Easy to tell "not found" = -1
  Index can't be -1 (invalid array index)
  
Our solution returns index (correct!)
```

### Sequential vs Random Access

```
Linear search works with:
- Sequential arrays ✓
- Linked lists ✓
- Any collection accessed one-by-one

Binary search requires:
- Direct access to middle element
- Not possible with linked lists ✗
```

### Comparison Count

```
Linear search on array of 1000 elements:

Best case: 1 comparison (found at start)
Worst case: 1000 comparisons (not found)
Average: 500 comparisons

Each comparison: O(1)
Total: O(n) algorithm
```

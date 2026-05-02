# Selection Sort 

## What is Selection Sort?

Selection Sort is a **simple sorting algorithm** that arranges numbers in order by repeatedly **finding the smallest number** and putting it in the right place.

### The Idea:
1. Find the **smallest number** in the array
2. Move it to the **beginning**
3. Find the **next smallest** number
4. Move it to the **next position**
5. Repeat until sorted!

---

## How It Works (Step by Step) 

### Example: Sort `[64, 34, 25, 12, 22]`

**Initial Array:**
```
[64, 34, 25, 12, 22]
```

**Pass 1:** Find smallest overall
- Smallest is **12**
- Swap 12 with first position (64)
```
[12, 34, 25, 64, 22]  ✓ (12 is in correct position)
```

**Pass 2:** Find smallest in remaining
- Remaining: `[34, 25, 64, 22]`
- Smallest is **22**
- Swap 22 with second position (34)
```
[12, 22, 25, 64, 34]  ✓ (12, 22 are correct)
```

**Pass 3:** Find smallest in remaining
- Remaining: `[25, 64, 34]`
- Smallest is **25**
- Already in correct position!
```
[12, 22, 25, 64, 34]  ✓ (12, 22, 25 are correct)
```

**Pass 4:** Find smallest in remaining
- Remaining: `[64, 34]`
- Smallest is **34**
- Swap 34 with 64
```
[12, 22, 25, 34, 64]  ✓ SORTED!
```

---

## Real-Life Example 

Imagine you have **5 boxes with random numbers** and you want to arrange them in order:

1. Look at all boxes → Find the one with **smallest number** → Put it first
2. Look at remaining boxes → Find the **next smallest** → Put it second
3. Continue until all are in order...

**Result:** All boxes arranged from smallest to biggest!

---

## Code Explanation 

### Lines 1-2: Outer Loop
```cpp
for (int i = 0; i < n - 1; i++) {
    int mini = i;
```
- **`i`**: Position where we want to place the smallest number
- **`mini`**: Index of smallest number found so far
- We loop `n-1` times because the last element will automatically be in place
- **Why `n-1`?** If we've sorted first `n-1` elements, the last one must be largest!

### Lines 4-8: Inner Loop (Find Minimum)
```cpp
    for (int j = i + 1; j < n; j++) {
        if (arr[j] < arr[mini]) {
            mini = j;
        }
    }
```
- **`j`**: Searches from position `i+1` to end
- **`if (arr[j] < arr[mini])`**: Found a smaller number?
  - Update `mini` to track where the smallest is
- **Example:** If searching `[34, 25, 64, 22]` starting at index 1
  - Compare 25 with 34 → 25 is smaller, so `mini = 2`
  - Compare 64 with 25 → 64 is bigger, `mini` stays 2
  - Compare 22 with 25 → 22 is smaller, so `mini = 4`
  - **Result:** `mini = 4` (index of smallest = 22)

### Line 9: Swap
```cpp
    swap(arr[i], arr[mini]);
```
- Swap the value at position `i` with the smallest value found
- Puts the smallest number in its correct position!
- **Example:** Swap `arr[1]=34` with `arr[4]=22` → Now 22 is at position 1

### Complete Example Trace:
```
Array: [64, 34, 25, 12, 22]

i=0: mini=3 (value 12), swap arr[0] with arr[3] → [12, 34, 25, 64, 22]
i=1: mini=4 (value 22), swap arr[1] with arr[4] → [12, 22, 25, 64, 34]
i=2: mini=2 (value 25), no swap needed → [12, 22, 25, 64, 34]
i=3: mini=4 (value 34), swap arr[3] with arr[4] → [12, 22, 25, 34, 64]

Result: [12, 22, 25, 34, 64] ✓ SORTED
```

---

## Time & Space Complexity 

### Time Complexity:
- **Best Case:** O(n²) - Even if array is sorted, we still check all pairs
- **Average Case:** O(n²)
- **Worst Case:** O(n²)

**Why?** 
- Outer loop runs n times
- Inner loop runs up to n times for each outer loop
- Total: n × n = n²

### Space Complexity:
- **O(1)** - We don't need extra space, just swap in place!

---

## Advantages 
- **Simple to understand** - Easy logic
- **In-place sorting** - No extra memory needed
- **Good for small arrays**

---

## Disadvantages 
- **Slow for large arrays** - O(n²) is not efficient
- **Not stable** - May change order of equal elements
- **Not adaptive** - Same time even if almost sorted

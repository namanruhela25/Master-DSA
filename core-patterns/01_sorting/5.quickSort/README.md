# Quick Sort 

## What is Quick Sort?

Quick Sort is like **picking a random student as a divider, then separating students into two groups (shorter and taller), and repeating until everyone is sorted**.

The key idea: **Pick a pivot, divide, then conquer both sides**
- Choose a pivot element
- Arrange all smaller elements to the left
- Arrange all larger elements to the right
- Recursively sort both sides

---

## The Key Concept 

**Three Main Steps:**
1. **PARTITION:** Pick a pivot and arrange elements around it
2. **DIVIDE:** Left side has smaller elements, right side has larger
3. **CONQUER:** Recursively sort left and right parts

This is one of the fastest sorting algorithms!

---

## How It Works Step By Step 

### Example: Sort `[5, 4, 3, 2, 1]`

**First Partition:** Pick first element `5` as pivot

```
Pivot = 5 (marked with *)
[5*, 4, 3, 2, 1]
 ↑ start=0, end=4

Step 1: i=1, j=4
  nums[1]=4 < 5? YES, move i → i=2
  nums[4]=1 < 5? YES (not > pivot), move j → j=3
  i < j? YES, swap nums[2] and nums[3]
  
  [5*, 4, 2, 3, 1] → i=2, j=3

Step 2: i=2, j=3
  nums[2]=2 < 5? YES, move i → i=3
  nums[3]=3 < 5? YES (not > pivot), move j → j=2
  i < j? NO (i=3, j=2), STOP

Step 3: Swap pivot with nums[j]
  Swap nums[0]=5 with nums[2]=2
  [2, 4, 5*, 3, 1]
  
Pivot 5 is now in position 2! ✓
```

**Left part:** `[2, 4]` (smaller than 5)
**Right part:** `[3, 1]` (larger than 5, but they need sorting)

**Recursively sort left [2, 4]:**
```
Pivot = 2
[2*, 4]
  Swap 2 with 4? 4 > 2, so move j left
  Final: [2, 4] ✓
```

**Recursively sort right [3, 1]:**
```
Pivot = 3
[3*, 1]
  1 < 3? YES, move j left
  Swap 3 with 1
  [1, 3*] ✓
```

**Final Result:** `[1, 2, 3, 4, 5]` 

---

## 🎯 HOOK TO REMEMBER FOREVER

### **"PICK PIVOT, SPLIT LEFT-RIGHT, SORT BOTH"**

Every time you see quick sort:
- ✅ Choose a pivot element
- ✅ Put smaller on left, larger on right
- ✅ Recursively sort both sides
- ✅ Eventually array is sorted!

**Remember: Like separating students by height with one student as reference** 📏

---

## Code Explanation 

### Partition Function (Finding Pivot Position)

```cpp
int partition(vector<int> &nums, int start, int end) {
    int pivot = nums[start];      // Choose first element as pivot
    int i = start + 1;            // Pointer starting from next element
    int j = end;                  // Pointer starting from end
```

- **`pivot`:** The element we compare everything against
- **`i`:** Moves RIGHT looking for element > pivot
- **`j`:** Moves LEFT looking for element ≤ pivot

### Step 1: Find Elements Out of Place

```cpp
    while(i < j) {
        while(i <= end-1 && nums[i] <= pivot) {
            i++;              // Skip elements that are already <= pivot
        }
        while(j >= start+1 && nums[j] > pivot) {
            j--;              // Skip elements that are already > pivot
        }
```

- **i-pointer:** Moves right until it finds an element > pivot (out of place!)
- **j-pointer:** Moves left until it finds an element ≤ pivot (out of place!)

**Example:** With `[5, 4, 3, 2, 1]` and pivot=5
```
i starts at 4 (already <= 5), moves right
j starts at 1 (< 5), means it's not > pivot, moves left
```

### Step 2: Swap Out-of-Place Elements

```cpp
        if(i < j) {
            swap(nums[i], nums[j]);   // Swap the out-of-place elements
        }
    }
```

- If pointers haven't crossed, swap what they found
- Now left element is ≤ pivot and right element is > pivot ✓

**Example:**
```
After finding positions with i=2, j=3
nums[2]=3 (should be on left)
nums[3]=2 (should be on right)
Swap them → [5, 4, 2, 3, 1]
```

### Step 3: Place Pivot in Final Position

```cpp
    swap(nums[start], nums[j]);
    return j;
```

- **Why swap with `j` (not `i`)?**
  - `j` moved LEFT, so it found the last element ≤ pivot
  - This is the correct spot for the pivot!
  - Everything to the left of j is now ≤ pivot
  - Everything to the right of j is now > pivot ✓

**Example:**
```
Before: [5, 4, 2, 3, 1], j=2
Swap nums[0]=5 with nums[2]=2
After:  [2, 4, 5, 3, 1]
        
Pivot 5 is now between smaller (left) and larger (right) elements!
```

### Complete Partition Trace:

```
Initial: [5, 4, 3, 2, 1]

i=1, j=4:
  nums[1]=4 ≤ 5? YES, i++        i=2
  nums[4]=1 > 5? NO, j--         j=3
  i < j? YES, swap(3,2)          [5, 4, 2, 3, 1]

i=2, j=3:
  nums[2]=2 ≤ 5? YES, i++        i=3
  nums[3]=3 > 5? NO, j--         j=2
  i < j? NO, STOP

Final swap(nums[0], nums[2]):
  Result: [2, 4, 5, 3, 1]
  Pivot index: 2 ✓
```

---

## QuickSort Function (Recursive Part)

```cpp
void quickSort(int start, int end, vector<int> &nums) {
    if(start < end) {
        int pivotIndex = partition(nums, start, end);
        quickSort(start, pivotIndex - 1, nums);      // Sort left
        quickSort(pivotIndex + 1, end, nums);        // Sort right
    }
}
```

- **`if(start < end)`:** Stop when left reaches right (1 element sorted!)
- **`partition(...)`:** Find pivot position
- **`quickSort(start, pivotIndex-1, ...)`:** Sort everything left of pivot
- **`quickSort(pivotIndex+1, end, ...)`:** Sort everything right of pivot

### Complete Example Trace:

```
Array: [5, 4, 3, 2, 1]

quickSort(0, 4):
  partition(0, 4) → returns 2, result: [2, 4, 5, 3, 1]
  
  quickSort(0, 1):           // Sort [2, 4]
    partition(0, 1) → returns 0, result: [2, 4, 5, 3, 1]
      quickSort(0, -1): STOP (start > end)
      quickSort(1, 1): STOP (start = end, 1 element)
  
  quickSort(3, 4):           // Sort [3, 1]
    partition(3, 4) → returns 3, result: [2, 4, 5, 1, 3]
      quickSort(3, 2): STOP (start > end)
      quickSort(4, 4): STOP (start = end, 1 element)

Final: [1, 2, 3, 4, 5] ✓
```

---

## Time Complexity 

- **Best Case:** O(n log n) - When pivot divides array evenly
- **Average Case:** O(n log n) - Usually picks good pivot
- **Worst Case:** O(n²) - When pivot is always smallest/largest!

**Why so fast usually?**
- Each partition step eliminates the pivot position
- We divide the problem in half each time
- O(n) work per level × O(log n) levels = O(n log n)

**Why worst case is slow?**
```
If array is [1,2,3,4,5] and we always pick first:
Partition picks 1 → [1, 2,3,4,5]  1 left, 4 right (unbalanced!)
Next partition picks 2 → [1, 2, 3,4,5]  1 left, 3 right
...keeps getting unbalanced = O(n²)
```

---

## Space Complexity

- **O(log n)** - For recursion call stack (not O(1) like bubble/insertion)
  - Best case: log n depth (balanced tree)
  - Worst case: n depth (unbalanced tree)

---

## Why Quick Sort ROCKS

✅ **Fastest in practice** - Better cache locality than merge sort
✅ **In-place sorting** - Uses little extra memory
✅ **Divide & Conquer** - Elegant recursive approach
✅ **Used everywhere** - C++ standard library, Java, Python
✅ **Usually O(n log n)** - Worst case rare with random pivots

---

## When NOT to Use Quick Sort

- **Guaranteed worst case danger** - O(n²) possible
- **Stability needed** - Not stable (equal elements may reorder)
- **Already sorted data** - Can hit worst case
- **Real-time systems** - Unpredictable performance

# Merge Sort 

## What is Merge Sort?

Merge Sort is like **dividing a big pile of cards into smaller piles, sorting each pile, then merging them back together in order**.

The key idea: **Divide and Conquer**
- Break the array into tiny pieces (divide)
- Sort the tiny pieces (conquer)
- Merge them back sorted (combine)

---

## The Key Concept

**Two Main Steps:**
1. **DIVIDE:** Keep splitting the array until each part has 1 element (1 element is always sorted!)
2. **MERGE:** Combine the sorted parts back together, keeping them sorted

This is the most efficient way to sort!

---

## How It Works Step By Step

### Example: Sort `[38, 27, 43, 3, 9, 82, 10]`

**DIVIDE Phase: Break it down** 

```
[38, 27, 43, 3, 9, 82, 10]         Level 0 (full array)
        ↓ (keep dividing)
    /                    \
[38, 27, 43, 3]    [9, 82, 10]      Level 1
    /        \         /      \
[38,27]  [43,3]   [9,82]    [10]    Level 2
  /  \    /  \     /  \       |
[38][27][43][3]  [9][82]     [10]   Level 3 (each is 1 element)
```

Each piece is now sorted! ✓ (single elements are always sorted)

**MERGE Phase: Put it back together** 

Now merge back, comparing and keeping sorted:

```
Level 3 (Already sorted):
[38][27][43][3]  [9][82]  [10]

Merge pairs:
[27,38]  [3,43]  [9,82]  [10]       Level 2

Merge again:
[3,27,38,43]  [9,10,82]             Level 1

Merge final:
[3, 9, 10, 27, 38, 43, 82]          Level 0 (SORTED!)
```

---

## 🎯 HOOK TO REMEMBER FOREVER

### **"DIVIDE UNTIL ONE, MERGE KEEPING SORTED"**

Every time you see merge sort:
- ✅ Break into individual elements
- ✅ Keep merging them back, comparing and sorting as you go
- ✅ You get a fully sorted array!

**Remember: Like Lego blocks - break into pieces, then build back assembled** 🧱

---

## Code Explanation 

### Merge Function (Combining sorted arrays)

```cpp
void merge(vector<int> &nums, int low, int high, int mid) {
    int i = low;           // Pointer for left part
    int j = mid+1;         // Pointer for right part
    vector<int> temp;      // Temporary array to store merged result
```

- **`low, mid, high`:** Boundaries
  - Left part: `low` to `mid`
  - Right part: `mid+1` to `high`
- **`i, j`:** Pointers to track position in each part
- **`temp`:** Stores the merged result

### Step 1: Compare and Merge Two Sorted Parts

```cpp
    while(i<=mid && j<=high) {
        if(nums[i] <= nums[j]) {
            temp.push_back(nums[i]);
            i++;
        } else{
            temp.push_back(nums[j]);
            j++;
        }
    }
```

- **Compare elements from both parts:** Which one is smaller?
- **Take the smaller one** and add to `temp`
- **Move the pointer forward** of the part we took from

**Example:** Merging `[3, 27, 38, 43]` and `[9, 10, 82]`
```
Compare 3 vs 9  → 3 smaller, take 3    temp=[3]
Compare 27 vs 9 → 9 smaller, take 9    temp=[3,9]
Compare 27 vs 10→ 10 smaller, take 10  temp=[3,9,10]
Compare 27 vs 82→ 27 smaller, take 27  temp=[3,9,10,27]
Compare 38 vs 82→ 38 smaller, take 38  temp=[3,9,10,27,38]
Compare 43 vs 82→ 43 smaller, take 43  temp=[3,9,10,27,38,43]
Left part empty, take remaining from right: 82
Final: [3,9,10,27,38,43,82]
```

### Step 2: Add Remaining Elements

```cpp
    while(i<=mid) {
        temp.push_back(nums[i]);
        i++;
    }

    while(j<=high) {
        temp.push_back(nums[j]);
        j++;
    }
```

- One part might have leftover elements
- **Add all remaining elements to temp**
- Order doesn't matter since we already compared everything

### Step 3: Copy Back to Original Array

```cpp
    for(int i=low; i <= high; i++) {
        nums[i] = temp[i - low];
    }
```

- **Why `i - low`?**
  - `temp` array starts at index 0
  - But we want to put elements back starting from `low`
  - So we subtract `low` to get the correct index in temp

**Example:**
```
temp indices:     0  1  2  3  4  5  6
temp values:   [3, 9, 10, 27, 38, 43, 82]

nums indices:     0  1  2  3  4  5  6
nums values:   [38, 27, 43, 3, 9, 82, 10]

If low=2, high=6:
  i=2: nums[2] = temp[2-2=0] = 3
  i=3: nums[3] = temp[3-2=1] = 9
  i=4: nums[4] = temp[4-2=2] = 10
  i=5: nums[5] = temp[5-2=3] = 27
  i=6: nums[6] = temp[6-2=4] = 38
```

---

## MergeSort Function (Divide Part)

```cpp
void mergSort(vector<int> &nums, int low, int high) {
    int mid = (low + high) / 2;
    if(low < high) {
        mergSort(nums, low, mid);         // Divide left
        mergSort(nums, mid+1, high);      // Divide right
        merge(nums, low, high, mid);      // Merge
    }
}
```

- **`mid = (low + high) / 2`:** Find middle point
- **`if(low < high)`:** Stop when left equals right (1 element)
- **Recursively divide left:** From `low` to `mid`
- **Recursively divide right:** From `mid+1` to `high`
- **After both sides sorted, MERGE them**

### Complete Example Trace:

```
Array: [38, 27, 43, 3, 9, 82, 10]

Call mergSort(0, 6):
  mid = 3
  
  Call mergSort(0, 3):              // Sort left half
    mid = 1
    Call mergSort(0, 1):
      mid = 0
      Call mergSort(0, 0): STOP (1 element)
      Call mergSort(1, 1): STOP (1 element)
      merge(0, 1, 0): [38,27] → [27,38]
    
    Call mergSort(2, 3):
      mid = 2
      Call mergSort(2, 2): STOP
      Call mergSort(3, 3): STOP
      merge(2, 3, 2): [43,3] → [3,43]
    
    merge(0, 3, 1): [27,38] + [3,43] → [3,27,38,43]
  
  Call mergSort(4, 6):              // Sort right half
    mid = 5
    Call mergSort(4, 5):
      mid = 4
      Call mergSort(4, 4): STOP
      Call mergSort(5, 5): STOP
      merge(4, 5, 4): [9,82] → [9,82]
    
    Call mergSort(6, 6): STOP
    merge(4, 6, 5): [9,82] + [10] → [9,10,82]
  
  merge(0, 6, 3): [3,27,38,43] + [9,10,82] → [3,9,10,27,38,43,82]

Final Result: [3, 9, 10, 27, 38, 43, 82] ✓
```

---

## Time Complexity 

- **Best Case:** O(n log n)
- **Average Case:** O(n log n)
- **Worst Case:** O(n log n)

**Why?**
- **n log n:** We divide n elements into log n levels, and at each level we process all n elements
- Level 1: n elements divided into 2 parts = 2 × (n/2) = n comparisons
- Level 2: n elements divided into 4 parts = 4 × (n/4) = n comparisons
- ... and so on for log n levels
- Total: n × log n = **O(n log n)**

---

## Space Complexity

- **O(n)** - We create a `temp` array to hold merged results

---

## Why Merge Sort is POWERFUL 

✅ **Always O(n log n)** - Never gets slower!
✅ **Stable** - Equal elements keep their order
✅ **Divide & Conquer** - Clean, elegant approach
✅ **Best for large arrays** - Much faster than bubble/insertion sort
✅ **Used in real world** - JavaScript uses it!

---

## When NOT to Use Merge Sort

- **Extra memory needed** - O(n) space
- **Small arrays** - Overkill, simpler sorts faster
- **Memory limited systems** - Can't afford extra array

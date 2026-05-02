# Insertion Sort 

## What is Insertion Sort?

Insertion Sort is like **arranging playing cards in your hand**. You pick cards one by one and insert them in the correct position among the cards you already have sorted.

The idea: Keep the left part sorted, and keep inserting new elements into the sorted part.

---

## The Key Concept 

**Two Parts At All Times:**
- **Left part:** Already sorted ✓
- **Right part:** Not sorted yet ✗

We move forward, and for each card, we find where it belongs in the sorted part!

---

## How It Works Step By Step 

### Example: Sort `[5, 2, 8, 1, 9]`

**Start:**
```
[5, 2, 8, 1, 9]
 ↑
Left part (sorted) = [5]
Right part = [2, 8, 1, 9]
```

**Step 1: Insert 2**
- 2 should go before 5
- Shift 5 right → Insert 2 left
```
[2, 5, 8, 1, 9]
 ↑↑↑
Left part (sorted) = [2, 5] ✓
Right part = [8, 1, 9]
```

**Step 2: Insert 8**
- 8 is bigger than 5, stays where it is
```
[2, 5, 8, 1, 9]
 ↑↑↑↑
Left part (sorted) = [2, 5, 8] ✓
Right part = [1, 9]
```

**Step 3: Insert 1**
- 1 is smaller than everyone!
- Shift all right and put 1 at the beginning
```
Compare 1 with 8: 1 < 8, swap → [2, 5, 1, 8, 9]
Compare 1 with 5: 1 < 5, swap → [2, 1, 5, 8, 9]
Compare 1 with 2: 1 < 2, swap → [1, 2, 5, 8, 9]
```
```
[1, 2, 5, 8, 9]
 ↑↑↑↑↑
Left part (sorted) = [1, 2, 5, 8] ✓
Right part = [9]
```

**Step 4: Insert 9**
- 9 is bigger than 8, stays at the end
```
[1, 2, 5, 8, 9]
 ↑↑↑↑↑↑
FULLY SORTED! ✓
```

---

## HOOK TO REMEMBER FOREVER

### **"LEFT IS SORTED, PUSH RIGHT INTO LEFT"**

Every time you see insertion sort:
- ✅ Left side = Sorted
- ✅ Right side = Unsorted
- ✅ Keep pushing right elements into their correct position in the left sorted part

**Remember: Playing cards in hand = Insertion Sort** 🃏

---

## Code Explanation 

### Line 1-2: Set up the loop
```cpp
int n = nums.size();
for(int i=0; i<=n-1; i++) {
    int j=i;
```
- **`i`:** Current element we want to insert
- **`j=i`:** Position of current element (we'll move it left if needed)
- **Start from i=0:** The first element is already "sorted"

### Lines 3-7: Compare and Shift
```cpp
    while(j>0 && nums[j-1] > nums[j]) {
        swap(nums[j-1], nums[j]);
        j--;
    }
```
- **`j>0`:** Stop at the beginning (can't go left of index 0)
- **`nums[j-1] > nums[j]`:** Left element is bigger than current?
  - YES → They're in wrong order, SWAP them!
  - NO → We found the correct position, STOP
- **`j--`:** Move left to check the previous element
- **Keep swapping until correct position found!**

### Full Code:
```cpp
vector<int> insertionSort(vector<int>& nums) {
    int n = nums.size();
    for(int i=0; i<=n-1; i++) {          // For each element
        int j=i;
        while(j>0 && nums[j-1] > nums[j]) {   // While not at start AND left is bigger
            swap(nums[j-1], nums[j]);    // Swap them
            j--;                         // Move left
        }
    }
    return nums;
}
```

### Complete Execution Trace:
```
Initial: [5, 2, 8, 1, 9]

i=0: [5]              (First element, skip loop)
i=1: j=1
     5>2? YES → swap   [2, 5]
     j=0 (stop)
     
i=2: j=2
     5>8? NO → stop    [2, 5, 8]
     
i=3: j=3
     8>1? YES → swap   [2, 5, 1, 8]
     5>1? YES → swap   [2, 1, 5, 8]
     2>1? YES → swap   [1, 2, 5, 8]
     j=0 (stop)
     
i=4: j=4
     8>9? NO → stop    [1, 2, 5, 8, 9]

Final: [1, 2, 5, 8, 9] ✓
```

---

## Quick Walkthrough of the While Loop 

Let's focus on when we insert **1** into `[2, 5, 8]`:

```
Before: [2, 5, 8] ← sorted part, and [1, 9]
Now we want to insert 1

Position before insertion:
[2, 5, 8, 1, 9]
       j=3

Compare nums[2]=8 with nums[3]=1:
8 > 1? YES → SWAP
[2, 5, 1, 8, 9]
    j=2

Compare nums[1]=5 with nums[2]=1:
5 > 1? YES → SWAP
[2, 1, 5, 8, 9]
 j=1

Compare nums[0]=2 with nums[1]=1:
2 > 1? YES → SWAP
[1, 2, 5, 8, 9]
j=0

j=0, so stop!
1 is now in the correct position! ✓
```

---

## Time Complexity ⏱

- **Best Case:** O(n) - Array already sorted (just one pass, no swaps)
- **Average Case:** O(n²)
- **Worst Case:** O(n²) - Array is reverse sorted (maximum swaps)

**Why sometimes O(n)?** If numbers are already in order, the while loop never executes!

---

## Space Complexity 

- **O(1)** - No extra space, everything is sorted in place!

---

## When to Use Insertion Sort? 

- Small arrays (less than 50 elements)
- Almost sorted data (runs fast!)
- Online sorting (can sort data as it arrives)
- Very simple code needed

---

## When NOT to Use Insertion Sort? 

- Large arrays (too slow O(n²))
- Random data (lots of comparisons)
- Performance critical code

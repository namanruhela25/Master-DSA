# Remove Duplicates from Sorted Array

**Problem Link:** https://leetcode.com/problems/remove-duplicates-from-sorted-array/

## What is this Problem?

You have a **sorted array with duplicate numbers** repeated multiple times. You need to:

1. **Remove the duplicates** - Keep only one copy of each number
2. **In-place** - Don't use extra space (modify the original array)
3. **Return the count** - How many unique elements are left?

**Examples:**
```
Input: [1, 1, 2, 2, 2, 3]
Output: 3 (unique count)
Array becomes: [1, 2, 3, ...]
(The first 3 elements are [1, 2, 3] - we return 3)

Input: [0, 0, 1, 1, 1, 2, 2, 3, 3, 4]
Output: 5 (unique count)
Array becomes: [0, 1, 2, 3, 4, ...]
(The first 5 elements contain all unique values)
```

---

## The Problem Explained

Imagine you have a **sorted email list with duplicates**:

```
[john@, john@, john@, mike@, mike@, sara@]

Goal: Move duplicates away, keep one of each:
[john@, mike@, sara@, john@, ...]
 ↑ unique section ↑

Return: 3 (three unique emails at the start)
```

**Key insight:** Since the array is **already sorted**, all duplicates are **right next to each other**. This makes it easy to spot!

```
Sorted = duplicates grouped together
[1, 1, 2, 2, 2, 3] ← Easy to find where 1→2, 2→3 changes!
       ↑ change here
```

---

## HOOK TO REMEMBER FOREVER

**"TWO POINTERS - WRITE UNIQUE, SKIP DUPLICATES"**

Every time you see "remove duplicates from sorted array":
- ✅ Use one pointer to write unique elements
- ✅ Use one pointer to read through array
- ✅ When you see a different element, write it forward
- ✅ Keep track of previous element to detect changes
- ✅ Return how many unique elements you wrote

**Remember: Write pointer moves forward only when element changes!** ✍️

---

## How It Works Step By Step

### The Two-Pointer Strategy

```
Array: [1, 1, 2, 2, 2, 3]

index=0 (write pointer, where to place next unique)
prevelement=1 (what was the last unique we saw)

Read through array with each element:
  - If element != previous: we found something new! Write it at index
  - If element == previous: skip it (already have this value)
```

### Visual Example: [1, 1, 2, 2, 2, 3]

```
Initial state:
Array: [1, 1, 2, 2, 2, 3]
        ↑
   index=0, prevelement=1

Step 1: Read 1, compare with prevelement=1
  1 != 1? NO → Skip (we already have 1)

Step 2: Read 1, compare with prevelement=1
  1 != 1? NO → Skip

Step 3: Read 2, compare with prevelement=1
  2 != 1? YES! New element!
  index++ → index=1
  nums[1] = 2
  prevelement = 2
  Array: [1, 2, 2, 2, 2, 3]
        ↑ write here

Step 4: Read 2, compare with prevelement=2
  2 != 2? NO → Skip

Step 5: Read 2, compare with prevelement=2
  2 != 2? NO → Skip

Step 6: Read 3, compare with prevelement=2
  3 != 2? YES! New element!
  index++ → index=2
  nums[2] = 3
  prevelement = 3
  Array: [1, 2, 3, 2, 2, 3]
        ↑ unique section ↑

Return: index + 1 = 3
(The first 3 elements [1, 2, 3] are our unique values!)
```

---

## Code Full Solution

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int index = 0;
        int prevelement = nums[0];

        for(auto &el : nums){
            if(el != prevelement){
                index++;
                nums[index] = el;
                prevelement = el;
            }
        }
        return index + 1;
    }
};
```

---

## Code Explanation

### Initialize Pointers

```cpp
int index = 0;
int prevelement = nums[0];
```

- **`index = 0`:** Write pointer - position where next unique element should go
  - Starts at 0 because the first element (nums[0]) is always unique
  - We'll increment this each time we find a new unique element

- **`prevelement = nums[0]`:** Tracks the last unique element we processed
  - Remember what value we just added to keep track of changes
  - When we see a different value, we know it's unique

**Example:** For [1, 1, 2, 2, 2, 3]
```
index = 0 (position 0 already has unique element 1)
prevelement = 1 (we've seen value 1)
```

---

### Loop Through Array

```cpp
for(auto &el : nums) {
    if(el != prevelement){
        index++;
        nums[index] = el;
        prevelement = el;
    }
}
```

**`for(auto &el : nums)`:** Go through each element in array
- `auto` - automatically determine type is int
- `&el` - reference (not copy, but actual element)

**`if(el != prevelement)`:** Found a new unique element!
- Compare current element with previous element we tracked
- If different, it's unique (sorted array groups duplicates)

**`index++`:** Move write pointer forward
- Next unique element will go to this new position

**`nums[index] = el`:** Write unique element
- Place current element at the new index position
- Example: If index becomes 1, put element at position 1

**`prevelement = el`:** Update what we're tracking
- Remember this element for next comparison
- Next iteration will compare against this value

---

### Return Unique Count

```cpp
return index + 1;
```

- **Why `index + 1`?**
  - index tracks positions 0, 1, 2, ...
  - If index = 2 (last written position), we wrote 3 elements total (positions 0, 1, 2)
  - So count = index + 1 = 3

**Example:** If we wrote to positions 0, 1, 2:
```
index goes: 0 → (finds new) 1 → (finds new) 2
Count = 2 + 1 = 3 unique elements
```

---

## Complete Example Traces

### Trace 1: Simple Case [1, 1, 2, 2, 2, 3]

```
Initial: index=0, prevelement=1, nums=[1, 1, 2, 2, 2, 3]

Iteration 1: el=1
  1 != 1? NO → Skip

Iteration 2: el=1
  1 != 1? NO → Skip

Iteration 3: el=2
  2 != 1? YES → New!
  index++ → index=1
  nums[1]=2 → nums=[1, 2, 2, 2, 2, 3]
  prevelement=2

Iteration 4: el=2
  2 != 2? NO → Skip

Iteration 5: el=2
  2 != 2? NO → Skip

Iteration 6: el=3
  3 != 2? YES → New!
  index++ → index=2
  nums[2]=3 → nums=[1, 2, 3, 2, 2, 3]
  prevelement=3

Loop ends
Return: index+1 = 2+1 = 3 ✓
Result: First 3 elements [1, 2, 3] are unique
```

### Trace 2: No Duplicates [1, 2, 3, 4, 5]

```
Initial: index=0, prevelement=1, nums=[1, 2, 3, 4, 5]

Iteration 1: el=1
  1 != 1? NO → Skip

Iteration 2: el=2
  2 != 1? YES → New!
  index++ → index=1
  nums[1]=2 → nums=[1, 2, 3, 4, 5] (no change)
  prevelement=2

Iteration 3: el=3
  3 != 2? YES → New!
  index++ → index=2
  nums[2]=3 → nums=[1, 2, 3, 4, 5]
  prevelement=3

Iteration 4: el=4
  4 != 3? YES → New!
  index++ → index=3
  nums[3]=4 → nums=[1, 2, 3, 4, 5]
  prevelement=4

Iteration 5: el=5
  5 != 4? YES → New!
  index++ → index=4
  nums[4]=5 → nums=[1, 2, 3, 4, 5]
  prevelement=5

Loop ends
Return: index+1 = 4+1 = 5 ✓
Result: All 5 elements are unique
```

### Trace 3: All Duplicates [2, 2, 2, 2, 2]

```
Initial: index=0, prevelement=2, nums=[2, 2, 2, 2, 2]

Iteration 1: el=2
  2 != 2? NO → Skip

Iteration 2: el=2
  2 != 2? NO → Skip

Iteration 3: el=2
  2 != 2? NO → Skip

Iteration 4: el=2
  2 != 2? NO → Skip

Iteration 5: el=2
  2 != 2? NO → Skip

Loop ends
Return: index+1 = 0+1 = 1 ✓
Result: Only 1 unique element
```

### Trace 4: Multiple Groups [1, 1, 1, 2, 2, 3, 3, 3, 3, 4]

```
Initial: index=0, prevelement=1, nums=[1, 1, 1, 2, 2, 3, 3, 3, 3, 4]

Iterations 1-3: el=1 each time
  1 != 1? NO → Skip (3 times)

Iteration 4: el=2
  2 != 1? YES → New!
  index=1, nums[1]=2, prevelement=2

Iteration 5: el=2
  2 != 2? NO → Skip

Iteration 6: el=3
  3 != 2? YES → New!
  index=2, nums[2]=3, prevelement=3

Iterations 7-9: el=3 each time
  3 != 3? NO → Skip (3 times)

Iteration 10: el=4
  4 != 3? YES → New!
  index=3, nums[3]=4, prevelement=4

Loop ends
Return: index+1 = 3+1 = 4 ✓
Result: 4 unique elements [1, 2, 3, 4]
```

### Trace 5: Single Element [5]

```
Initial: index=0, prevelement=5, nums=[5]

Iteration 1: el=5
  5 != 5? NO → Skip

Loop ends
Return: index+1 = 0+1 = 1 ✓
Result: 1 unique element
```

### Trace 6: Two Unique [0, 0, 1, 1, 1, 2, 2, 3, 3, 4]

```
Initial: index=0, prevelement=0, nums=[0, 0, 1, 1, 1, 2, 2, 3, 3, 4]

Iterations 1-2: el=0
  0 != 0? NO → Skip

Iteration 3: el=1
  1 != 0? YES → New!
  index=1, nums[1]=1, prevelement=1

Iterations 4-5: el=1
  1 != 1? NO → Skip

Iteration 6: el=2
  2 != 1? YES → New!
  index=2, nums[2]=2, prevelement=2

Iteration 7: el=2
  2 != 2? NO → Skip

Iteration 8: el=3
  3 != 2? YES → New!
  index=3, nums[3]=3, prevelement=3

Iteration 9: el=3
  3 != 3? NO → Skip

Iteration 10: el=4
  4 != 3? YES → New!
  index=4, nums[4]=4, prevelement=4

Loop ends
Return: index+1 = 4+1 = 5 ✓
Result: 5 unique elements [0, 1, 2, 3, 4]
```

---

## Edge Cases

### Case 1: Single Element

```
Input: [1]
- index=0, prevelement=1
- Loop runs once with el=1
- 1 != 1? NO
- Return: 0+1 = 1
Output: 1 ✓
```

### Case 2: All Same Elements

```
Input: [5, 5, 5, 5, 5]
- index never increments (no new elements found)
- Return: 0+1 = 1
Output: 1 ✓
```

### Case 3: Already Unique

```
Input: [1, 2, 3, 4]
- index increments for every element (all different)
- Return: 3+1 = 4
Output: 4 ✓
```

### Case 4: Negative Numbers

```
Input: [-3, -3, -1, -1, 0, 0, 2]
- Sorted array with negatives works same way
- finds changes: -3→-1, -1→0, 0→2
- index goes: 0→1→2→3
- Return: 3+1 = 4
Output: 4 ✓
```

### Case 5: Very Large Array

```
Input: [1, 1, ..., 1, 2, 2, ..., 2, 3, 3, ..., 3] (1000 elements)
- Still works in one pass
- Only write when element changes
- Return: 3 ✓
```

### Case 6: Two Unique Only

```
Input: [1, 1, 1, 1, 2, 2, 2]
- index=0, prevelement=1
- Skip 1s
- At 2: index=1, write 2, prevelement=2
- Return: 1+1 = 2
Output: 2 ✓
```

---

## Time Complexity

- **O(n)** where n = array size
- Single loop through entire array one time
- Each operation inside loop is O(1)

---

## Space Complexity

- **O(1)** - Constant space
- Only using two variables: `index` and `prevelement`
- Modifying array in-place (no extra space)

---

## Key Insights

### Why This Works on Sorted Arrays

```
Sorted = duplicates grouped:
[1, 1, 2, 2, 2, 3] ← All 1s together, all 2s together

Unsorted would be:
[1, 2, 1, 3, 2] ← Can't tell what's unique at a glance!

With sorted array, we know:
- First occurrence of value = unique
- Every occurrence after that = duplicate
```

### Why Two Pointers?

```
index = write pointer (where to place next unique)
el = read pointer (scanning through array)

They move at different speeds:
- el moves every iteration
- index only moves when we find new element

[1, 1, 2, 2, 2, 3]
    ↑ el keeps going
 ↑ index jumps only on changes
```

### Why We Track Previous Element?

```
We could compare el to nums[index]:
  if (el != nums[index])  ✓ works

But prevelement is cleaner:
  if (el != prevelement)  ✓ more efficient

Both work, but prevelement doesn't need extra array lookup!
```

### Why Return index + 1?

```
index is the POSITION of last unique element
  index = 0 → mean 1 element at position 0
  index = 1 → means 2 elements at positions 0,1
  index = 2 → means 3 elements at positions 0,1,2

So count = index + 1
```

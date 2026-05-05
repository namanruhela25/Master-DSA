# Find Second Largest and Second Smallest Elements 

## What is this Problem?

We have an **array of numbers**. We need to find:
1. **Second Largest** element - the second biggest number
2. **Second Smallest** element - the second smallest number

**Example:**
```
Array: [3, 5, 7, 2, 8]

Largest: 8, Second Largest: 7
Smallest: 2, Second Smallest: 3

Answer: [7, 3]
```

---

## The Problem Explained

Think of a **ranking at school**:
```
Marks: [3, 5, 7, 2, 8]

Ranked (highest to lowest): 8, 7, 5, 3, 2
1st position (largest): 8
2nd position (second largest): 7  ← What we want!

Ranked (lowest to highest): 2, 3, 5, 7, 8
1st position (smallest): 2
2nd position (second smallest): 3  ← What we want!
```

---

## HOOK TO REMEMBER FOREVER

### **"TRACK TWO WINNERS, ONE GETS BUMPED DOWN, SKIP THE TIED"**

Every time you see finding second largest/smallest:
- ✅ Keep **largest and second_largest** (or **smallest and second_smallest**)
- ✅ When new element beats largest → bump largest to second, update largest
- ✅ Else if new element beats second AND not equal to largest → update second
- ✅ **KEY:** Must check `!= large` to avoid duplicates of same element!

**Remember: Like medal podium - first moves to second, new becomes first!** 🏅

---

## How It Works Step By Step

### Example 1: Find Second Largest in `[3, 5, 7, 2, 8]`

**Start:**
```
Array: [3, 5, 7, 2, 8]
Large: INT_MIN (negative infinity)
Second_Large: INT_MIN
```

**Step 1: Check 3**
```
3 > INT_MIN? YES (3 is biggest so far)
second_large = INT_MIN (bump down)
large = 3
```

**Step 2: Check 5**
```
5 > 3? YES (5 is bigger!)
second_large = 3 (bump 3 down!)
large = 5
```

**Step 3: Check 7**
```
7 > 5? YES (7 is bigger!)
second_large = 5 (bump 5 down!)
large = 7
```

**Step 4: Check 2**
```
2 > 7? NO
2 > INT_MIN and 2 != 7? YES
second_large = 2
Result: second_large = 2? WAIT...

Actually:
Position of 2: middle
Already have second_large = 5
2 is not > 5, so NO update
```

**Step 5: Check 8**
```
8 > 7? YES (8 is the new largest!)
second_large = 7 (bump 7 down!)
large = 8
```

**Final Result:**
```
Large: 8
Second_Large: 7 ✓
```

### Example 2: Find Second Smallest in `[3, 5, 7, 2, 8]`

**Start:**
```
Array: [3, 5, 7, 2, 8]
Small: INT_MAX (positive infinity)
Second_Small: INT_MAX
```

**Step 1: Check 3**
```
3 < INT_MAX? YES (3 is smallest so far)
second_small = INT_MAX (bump down)
small = 3
```

**Step 2: Check 5**
```
5 < 3? NO
5 < INT_MAX and 5 != 3? YES
second_small = 5
```

**Step 3: Check 7**
```
7 < 3? NO
7 < 5 and 7 != 3? NO (7 is not < 5)
No update
```

**Step 4: Check 2**
```
2 < 3? YES (2 is the new smallest!)
second_small = 3 (bump 3 down!)
small = 2
```

**Step 5: Check 8**
```
8 < 2? NO
8 < 3 and 8 != 2? NO (8 is not < 3)
No update
```

**Final Result:**
```
Small: 2
Second_Small: 3 ✓
```

---

## Code Full Solution

```cpp
// Find Second Largest Element
int secondLargest(int arr[], int n) {
    if (n < 2)
        return -1;                  // Need at least 2 elements
    
    int large = INT_MIN;            // Largest so far
    int second_large = INT_MIN;     // Second largest so far
    
    for (int i = 0; i < n; i++) {
        if (arr[i] > large) {
            second_large = large;   // Bump down current largest
            large = arr[i];         // New largest
            
        } else if (arr[i] > second_large && arr[i] != large) {
            second_large = arr[i];  // Found new second largest
        }
    }
    
    return second_large;
}

// Find Second Smallest Element
int secondSmallest(int arr[], int n) {
    if (n < 2)
        return -1;                  // Need at least 2 elements
    
    int small = INT_MAX;            // Smallest so far
    int second_small = INT_MAX;     // Second smallest so far
    
    for (int i = 0; i < n; i++) {
        if (arr[i] < small) {
            second_small = small;   // Bump down current smallest
            small = arr[i];         // New smallest
            
        } else if (arr[i] < second_small && arr[i] != small) {
            second_small = arr[i];  // Found new second smallest
        }
    }
    
    return second_small;
}
```

---

## Code Explanation

### Edge Case Check

```cpp
if (n < 2)
    return -1;
```

- **Why?** Need at least 2 elements to have a "second"
- Return -1 if impossible (indicates error)

**Examples:**
```
n = 0: Array empty → return -1
n = 1: Only [5] → return -1 (no second element)
n = 2: Array [3, 5] → can find second → proceed
```

### Initialize with Extremes

```cpp
int large = INT_MIN;
int second_large = INT_MIN;
```

- **`INT_MIN`:** Smallest possible integer (negative infinity concept)
- **Why?** Any real array element is definitely > INT_MIN
- Ensures we find the actual maximum in array

**For smallest:**
```cpp
int small = INT_MAX;
int second_small = INT_MAX;
```

- **`INT_MAX`:** Largest possible integer (positive infinity concept)
- Any real array element is definitely < INT_MAX

---

## For Second Largest: The Two Conditions

### Condition 1: New Element Beats Largest

```cpp
if (arr[i] > large) {
    second_large = large;   // Move current largest down to second
    large = arr[i];         // New element becomes largest
}
```

**Like a promotion:**
```
Current state: large=7, second_large=5

New element: 8

After update: large=8, second_large=7
              
The old largest (7) gets bumped to second position!
```

### Condition 2: New Element Beats Second Largest (But Not Equal to Largest)

```cpp
else if (arr[i] > second_large && arr[i] != large) {
    second_large = arr[i];
}
```

- **`arr[i] > second_large`:** Is it bigger than current second?
- **`arr[i] != large`:** Is it different from the largest?

**Why the inequality check?**
```
Array: [5, 5, 5]

Without check:
  large = 5, second_large = 5
  Both are the same element! (Wrong!)

With check:
  large = 5, second_large = INT_MIN
  Correct - we only have duplicates of one value
```

---

## For Second Smallest: Mirror Logic

```cpp
if (arr[i] < small) {
    second_small = small;   // Bump down
    small = arr[i];         // New smallest
    
} else if (arr[i] < second_small && arr[i] != small) {
    second_small = arr[i];
}
```

**Exactly the same pattern, just with < instead of >!**

---

## Complete Example Trace

```
Array: [3, 5, 7, 2, 8]

SECOND LARGEST:
large = INT_MIN, second_large = INT_MIN

i=0: arr[0]=3
     3 > INT_MIN? YES
     second_large = INT_MIN
     large = 3

i=1: arr[1]=5
     5 > 3? YES
     second_large = 3
     large = 5

i=2: arr[2]=7
     7 > 5? YES
     second_large = 5
     large = 7

i=3: arr[3]=2
     2 > 7? NO
     2 > 5 and 2 != 7? NO (2 is not > 5)
     No update

i=4: arr[4]=8
     8 > 7? YES
     second_large = 7
     large = 8

Return: 7 ✓


SECOND SMALLEST:
small = INT_MAX, second_small = INT_MAX

i=0: arr[0]=3
     3 < INT_MAX? YES
     second_small = INT_MAX
     small = 3

i=1: arr[1]=5
     5 < 3? NO
     5 < INT_MAX and 5 != 3? YES
     second_small = 5

i=2: arr[2]=7
     7 < 3? NO
     7 < 5 and 7 != 3? NO
     No update

i=3: arr[3]=2
     2 < 3? YES
     second_small = 3
     small = 2

i=4: arr[4]=8
     8 < 2? NO
     8 < 3 and 8 != 2? NO
     No update

Return: 3 ✓
```

---

## Edge Cases

### Case 1: Array with duplicates (largest)
```
Array: [5, 7, 7, 7]

After processing all:
large = 7, second_large = 5 ✓
(Correctly skips duplicate 7s)
```

### Case 2: Array with duplicates (same value)
```
Array: [5, 5, 5]

After processing all:
large = 5, second_large = INT_MIN
Return: INT_MIN (no true second element)
```

### Case 3: Negative numbers
```
Array: [-8, -3, -5, -1]

Second largest: -3 ✓
Second smallest: -5 ✓
```

### Case 4: Exactly 2 elements
```
Array: [3, 7]

n=2, so proceed
large = 3, second_large is updated when 7 comes
Result: 3 ✓
```

---

## Time Complexity 

- **Both functions: O(n)** where n = number of elements
- Single loop through array
- Each operation inside loop is O(1)

---

## Space Complexity

- **Both functions: O(1)**
- Only using fixed variables (large, second_large, etc.)
- No extra arrays or data structures

---

## Why Check `arr[i] != large`? 🤔

**This is the CRITICAL insight!**

```
Without check:
  Array: [5, 5, 5]
  Result: large=5, second_large=5 (same value!)

With check:
  Array: [5, 5, 5]
  5 != 5 is false, so second_large stays INT_MIN
  Result: second_large = INT_MIN (correct - no true second element)
```

**Without this, we might return the same element as both largest and second largest!**

---

## Key Insights

### The Promotion Pattern
```
When a new element beats the king:
- King gets bumped to second
- New element becomes king

Like a game ranking:
Old state: King=7, Second=5
New challenger: 8
New state: King=8, Second=7
```

### Why Separate Checks
```
Check 1: arr[i] > large
- If true, handle promotion

Check 2: else if arr[i] > second_large && arr[i] != large
- Only if not already handled in Check 1
- Additional safety: arr[i] != large prevents duplicate confusion
```

### Time Efficiency
```
Alternative (bad): Sort array, return arr[n-2]
- Time: O(n log n) - sorting is expensive!

Our approach: One pass, two variables
- Time: O(n) - much faster!
- Space: O(1) - much less memory!
```

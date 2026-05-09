# Move Zeroes

**Problem Link:** https://leetcode.com/problems/move-zeroes/

## What is this Problem?

You have an **array with zeros and non-zero numbers** mixed together. You need to:

1. **Move all zeros to the end** of the array
2. **Keep non-zero numbers in the same order** (relative order matters!)
3. **Do it in-place** - don't use extra space

**Examples:**
```
Input: [0, 1, 0, 3, 12]
Output: [1, 3, 12, 0, 0]
(All zeros moved to end, order of 1,3,12 preserved)

Input: [0]
Output: [0]
(Already at end)

Input: [1, 0, 2, 0, 3, 0]
Output: [1, 2, 3, 0, 0, 0]
(Zeros grouped at end, non-zeros stay in order)
```

---

## The Problem Explained

Imagine a **classroom with students and empty seats**:

```
Original: [Empty, Alice, Empty, Bob, Charlie]
          [0,     1,      0,     3,   12]

Goal: Move all empty seats to the back:
Result: [Alice, Bob, Charlie, Empty, Empty]
        [1,     3,   12,      0,     0]

Alice stayed where she was first
Bob stayed in position between Alice and Charlie
Charlie stayed after Bob
Empties just moved to end!
```

**Key insight:** We want to **move zeros without changing the order of non-zeros**.

---

## HOOK TO REMEMBER FOREVER

**"TWO POINTERS - WRITE NON-ZERO, SWAP IN PLACE"**

Every time you see "move zeros to end":
- ✅ Use left pointer to track where next non-zero should go
- ✅ Use right pointer to scan for non-zero elements
- ✅ When non-zero found, swap it to left position
- ✅ Increment left pointer
- ✅ Right pointer keeps scanning
- ✅ Zeros automatically end up at the end!

**Remember: Non-zeros move forward, zeros get pushed back!** 🎯

---

## How It Works Step By Step

### The Two-Pointer Strategy

```
Array: [0, 1, 0, 3, 12]

left = 0 (where to place next non-zero)
right scans from beginning to end

When right finds a non-zero:
- Swap it with position left
- Move left forward
- This pushes zeros backward
```

### Visual Example: [0, 1, 0, 3, 12]

```
Initial: [0, 1, 0, 3, 12]
         left=0

Iteration 1: right=0, nums[0]=0
  0 != 0? NO → Skip (is zero)

Iteration 2: right=1, nums[1]=1
  1 != 0? YES! Non-zero found!
  swap(nums[0], nums[1])
  [1, 0, 0, 3, 12]
  left=1

Iteration 3: right=2, nums[2]=0
  0 != 0? NO → Skip

Iteration 4: right=3, nums[3]=3
  3 != 0? YES! Non-zero found!
  swap(nums[1], nums[3])
  [1, 3, 0, 0, 12]
  left=2

Iteration 5: right=4, nums[4]=12
  12 != 0? YES! Non-zero found!
  swap(nums[2], nums[4])
  [1, 3, 12, 0, 0]
  left=3

Done! Result: [1, 3, 12, 0, 0] ✓
(All zeros at end, non-zeros in same order!)
```

### Why This Maintains Order

```
Key insight: left and right pointers have different speeds!

right always scans forward (every iteration)
left only moves when we find non-zero

[0, 1, 0, 3, 12]

When right finds 1 at index 1:
  - Swap with position 0
  - left moves to 1
  
When right finds 3 at index 3:
  - Swap with position 1
  - left moves to 2

When right finds 12 at index 4:
  - Swap with position 2
  - left moves to 3

Elements maintain relative order because:
- We encounter them in order (right scans left to right)
- We place them in order (left marks positions in order)
```

---

## Code Full Solution

```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int left = 0;
        for(int right = 0; right < nums.size(); right++) {
            if(nums[right] != 0) {
                swap(nums[left], nums[right]);
                left++;
            }
        }
    }
};
```

---

## Code Explanation

### Initialize Left Pointer

```cpp
int left = 0;
```

- **`left = 0`:** Position where next non-zero element should go
- **Think of it as:** "Left is the boundary of non-zero elements"
- **Incrementing left:** Extends the boundary as we add non-zeros

**Example:** For [0, 1, 0, 3, 12]
```
left = 0 means position 0 is empty and waiting for first non-zero
```

---

### Scan for Non-Zero Elements

```cpp
for(int right = 0; right < nums.size(); right++) {
    if(nums[right] != 0) {
        swap(nums[left], nums[right]);
        left++;
    }
}
```

**`for(int right = 0...`:** Scan entire array from start to end
- `right` is our **read pointer** (looking for non-zeros)
- Moves every iteration regardless

**`if(nums[right] != 0)`:** Found a non-zero!
- Compare current element with 0
- If not zero, it needs to be placed at left position

**`swap(nums[left], nums[right])`:** Move non-zero to correct position
- Take non-zero from position right
- Place it at position left
- Whatever was at left goes to right (usually a zero)

**Why swap?** 
- Keeps zeros that were at left → they move to right (end)
- Brings non-zero to correct early position
- In-place operation, O(1) space!

**`left++`:** Extend the boundary
- Next non-zero will go one position further right
- This is how the "non-zero section" grows!

---

## Complete Example Traces

### Trace 1: Mixed Zeros and Non-Zeros [0, 1, 0, 3, 12]

```
Initial: nums=[0, 1, 0, 3, 12], left=0

right=0: nums[0]=0
  0 != 0? NO → Skip

right=1: nums[1]=1
  1 != 0? YES
  swap(nums[0], nums[1]): [1, 0, 0, 3, 12]
  left=1

right=2: nums[2]=0
  0 != 0? NO → Skip

right=3: nums[3]=3
  3 != 0? YES
  swap(nums[1], nums[3]): [1, 3, 0, 0, 12]
  left=2

right=4: nums[4]=12
  12 != 0? YES
  swap(nums[2], nums[4]): [1, 3, 12, 0, 0]
  left=3

Result: [1, 3, 12, 0, 0] ✓
```

### Trace 2: No Zeros [1, 2, 3, 4, 5]

```
Initial: nums=[1, 2, 3, 4, 5], left=0

right=0: nums[0]=1
  1 != 0? YES
  swap(nums[0], nums[0]): [1, 2, 3, 4, 5] (no change, same position)
  left=1

right=1: nums[1]=2
  2 != 0? YES
  swap(nums[1], nums[1]): [1, 2, 3, 4, 5] (no change)
  left=2

right=2: nums[2]=3
  3 != 0? YES
  swap(nums[2], nums[2]): [1, 2, 3, 4, 5]
  left=3

right=3: nums[3]=4
  4 != 0? YES
  swap(nums[3], nums[3]): [1, 2, 3, 4, 5]
  left=4

right=4: nums[4]=5
  5 != 0? YES
  swap(nums[4], nums[4]): [1, 2, 3, 4, 5]
  left=5

Result: [1, 2, 3, 4, 5] ✓
(No change - all non-zeros already at front!)
```

### Trace 3: All Zeros [0, 0, 0, 0]

```
Initial: nums=[0, 0, 0, 0], left=0

right=0: nums[0]=0
  0 != 0? NO → Skip

right=1: nums[1]=0
  0 != 0? NO → Skip

right=2: nums[2]=0
  0 != 0? NO → Skip

right=3: nums[3]=0
  0 != 0? NO → Skip

left stays at 0 (never incremented)

Result: [0, 0, 0, 0] ✓
(No non-zeros to move!)
```

### Trace 4: Zeros at Beginning [0, 0, 1, 2, 3]

```
Initial: nums=[0, 0, 1, 2, 3], left=0

right=0: nums[0]=0
  0 != 0? NO → Skip

right=1: nums[1]=0
  0 != 0? NO → Skip

right=2: nums[2]=1
  1 != 0? YES
  swap(nums[0], nums[2]): [1, 0, 0, 2, 3]
  left=1

right=3: nums[3]=2
  2 != 0? YES
  swap(nums[1], nums[3]): [1, 2, 0, 0, 3]
  left=2

right=4: nums[4]=3
  3 != 0? YES
  swap(nums[2], nums[4]): [1, 2, 3, 0, 0]
  left=3

Result: [1, 2, 3, 0, 0] ✓
```

### Trace 5: Single Non-Zero and Zeros [0, 5, 0, 0]

```
Initial: nums=[0, 5, 0, 0], left=0

right=0: nums[0]=0
  0 != 0? NO → Skip

right=1: nums[1]=5
  5 != 0? YES
  swap(nums[0], nums[1]): [5, 0, 0, 0]
  left=1

right=2: nums[2]=0
  0 != 0? NO → Skip

right=3: nums[3]=0
  0 != 0? NO → Skip

Result: [5, 0, 0, 0] ✓
```

### Trace 6: Negative Numbers [-1, 0, -2, 0, 3]

```
Initial: nums=[-1, 0, -2, 0, 3], left=0

right=0: nums[0]=-1
  -1 != 0? YES
  swap(nums[0], nums[0]): [-1, 0, -2, 0, 3]
  left=1

right=1: nums[1]=0
  0 != 0? NO → Skip

right=2: nums[2]=-2
  -2 != 0? YES
  swap(nums[1], nums[2]): [-1, -2, 0, 0, 3]
  left=2

right=3: nums[3]=0
  0 != 0? NO → Skip

right=4: nums[4]=3
  3 != 0? YES
  swap(nums[2], nums[4]): [-1, -2, 3, 0, 0]
  left=3

Result: [-1, -2, 3, 0, 0] ✓
(Negative numbers treated as non-zero!)
```

---

## Edge Cases

### Case 1: Single Element Zero

```
Input: [0]
- left=0
- right=0: nums[0]=0
  0 != 0? NO → Skip
Output: [0] ✓
```

### Case 2: Single Element Non-Zero

```
Input: [1]
- left=0
- right=0: nums[0]=1
  1 != 0? YES
  swap(nums[0], nums[0]): [1]
  left=1
Output: [1] ✓
```

### Case 3: Two Elements [0, 1]

```
Input: [0, 1]
- left=0
- right=0: 0 → Skip
- right=1: 1 != 0? YES
  swap(nums[0], nums[1]): [1, 0]
  left=1
Output: [1, 0] ✓
```

### Case 4: Already Sorted [1, 2, 0, 0]

```
Input: [1, 2, 0, 0]
- right=0: 1 → swap at 0 (no change), left=1
- right=1: 2 → swap at 1 (no change), left=2
- right=2: 0 → Skip
- right=3: 0 → Skip
Output: [1, 2, 0, 0] ✓
```

### Case 5: Large Numbers with Zeros

```
Input: [1000, 0, 2000, 0, 3000]
- Processes same way as any numbers
Output: [1000, 2000, 3000, 0, 0] ✓
```

### Case 6: Alternating [0, 1, 0, 2, 0, 3]

```
Input: [0, 1, 0, 2, 0, 3]
- left=0
- right=0: 0 → Skip
- right=1: 1 → swap at 0: [1, 0, 0, 2, 0, 3], left=1
- right=2: 0 → Skip
- right=3: 2 → swap at 1: [1, 2, 0, 0, 0, 3], left=2
- right=4: 0 → Skip
- right=5: 3 → swap at 2: [1, 2, 3, 0, 0, 0], left=3
Output: [1, 2, 3, 0, 0, 0] ✓
```

---

## Time Complexity

- **O(n)** where n = array size
- Single pass through entire array with right pointer
- Each swap is O(1)
- Total: n iterations × O(1) per iteration = O(n)

---

## Space Complexity

- **O(1)** - Constant space
- Only using two integer variables: `left` and `right`
- Modifying array in-place with swaps
- No extra data structures needed

---

## Key Insights

### Why Two Pointers?

```
With one pointer:
[0, 1, 0, 3, 12]

Just shift everything when we encounter zero?
That would be O(n²) shifting operations!

With two pointers:
left = position to place non-zeros
right = scanner for non-zeros

Each operation is O(1), total O(n) ✓
```

### Why Maintain Order?

```
Using our approach:
[0, 1, 0, 3, 12] → [1, 3, 12, 0, 0]

Why relative order maintained?
- right pointer scans left-to-right
- We place non-zeros in encounter order
- First non-zero (1) goes to first position
- Second non-zero (3) goes to second position
- Third non-zero (12) goes to third position

Order is automatically preserved!
```

### Swap Instead of Shift

```
Shifting approach:
[0, 1, 0, 3, 12]
Move 1 left: [1, 0, 0, 3, 12] (shift all right elements)
Move 3 left: [1, 3, 0, 0, 12] (shift again)
Move 12 left: [1, 3, 12, 0, 0]
Time: O(n²) ❌

Swap approach:
[0, 1, 0, 3, 12]
Swap 0 and 1: [1, 0, 0, 3, 12]
(No shifting, just one swap)
Swap 0 and 3: [1, 3, 0, 0, 12]
(No shifting, just one swap)
Swap 0 and 12: [1, 3, 12, 0, 0]
(No shifting, just one swap)
Time: O(n) ✓
```

### Why Swap Works

```
When left != right:
Swapping nums[left] with nums[right] means:
- Non-zero from position right goes to position left ✓
- Whatever was at left (a zero) goes to position right
- Zero naturally ends up further right! ✓

When left == right:
Swapping with itself does nothing
- Element is already in correct place
- No harm in extra swap ✓
```

### When left == right

```
If no zeros encountered yet:
[1, 2, 3, 4, 5]

right=0: 1 != 0? YES
  swap(nums[0], nums[0]) → same position
  left=1

right=1: 2 != 0? YES
  swap(nums[1], nums[1]) → same position
  left=2

Array never changes because left == right!
```

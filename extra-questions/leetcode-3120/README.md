# Count the Number of Special Characters I

**Problem Link:** http://leetcode.com/problems/count-the-number-of-special-characters-i/description/

## What is this Problem?

A **special character** is a letter that appears in the word in **both lowercase and uppercase forms**.

We need to count how many **unique letters** have both lowercase and uppercase versions in the word.

**Key Points:**
- A letter is "special" if both 'a' and 'A' exist (or 'b'/'B', etc.)
- Count unique letters that appear in both forms
- Case matters (must have both forms)
- Return the count of special characters

**Examples:**
```
Input: "aBBBbb"
Output: 1
Explanation:
  - 'a' appears (lowercase), 'A' does NOT appear
  - 'b' appears (lowercase), 'B' appears (uppercase) → Special! ✓
  Count: 1

Input: "abc"
Output: 0
Explanation:
  - 'a' appears (lowercase), 'A' does NOT appear
  - 'b' appears (lowercase), 'B' does NOT appear
  - 'c' appears (lowercase), 'C' does NOT appear
  Count: 0

Input: "AaBbCc"
Output: 3
Explanation:
  - 'A' and 'a' both appear → Special! ✓
  - 'B' and 'b' both appear → Special! ✓
  - 'C' and 'c' both appear → Special! ✓
  Count: 3
```

---

## The Problem Explained

Imagine a word and you want to find all **matching pairs** where a letter appears both uppercase and lowercase.

**Example:** "HeLLo"
- 'H' (uppercase) → 'h' (lowercase) exists? NO
- 'e' (lowercase) → 'E' (uppercase) exists? NO
- 'L' (uppercase) → 'l' (lowercase) exists? YES → Special! ✓
- 'o' (lowercase) → 'O' (uppercase) exists? NO

Result: 1 special character (the letter 'l'/'L')

---

## HOOK TO REMEMBER FOREVER

### **"BITMASKS MATCH PAIRS PERFECTLY"**

Every time you see this problem:
- ✅ Use **bitmasks** for each case (uppercase, lowercase)
- ✅ Each bit represents a letter (a-z → 26 bits)
- ✅ Set bits where letters appear
- ✅ Use **bitwise AND** to find common letters
- ✅ Count set bits in result

**Remember: Bits reveal which letters have both forms!** 🔤

---

## How It Works Step By Step

### Solution Approach: Bitmasks (Optimal)

This approach uses **26-bit bitmasks** where each bit represents a letter (a-z).

### Example: "aBBBbb"

**Step 1: Initialize Bitmasks**
```
lower = 00000000000000000000000000  (26 bits, all 0)
upper = 00000000000000000000000000
```

**Step 2: Process Each Character**
```
Process 'a' (lowercase):
  'a' - 'a' = 0
  Set bit 0 in lower bitmask
  lower = 00000000000000000000000001
  
Process 'B' (uppercase):
  'B' - 'A' = 1
  Set bit 1 in upper bitmask
  upper = 00000000000000000000000010

Process 'B' (uppercase, again):
  Bit 1 already set
  upper = 00000000000000000000000010 (no change)

Process 'B' (uppercase, again):
  upper = 00000000000000000000000010 (no change)

Process 'b' (lowercase):
  'b' - 'a' = 1
  Set bit 1 in lower bitmask
  lower = 00000000000000000000000011

Process 'b' (lowercase, again):
  Bit 1 already set
  lower = 00000000000000000000000011 (no change)

Final bitmasks:
lower = 00000000000000000000000011  (letters: a, b)
upper = 00000000000000000000000010  (letters: b)
```

**Step 3: Find Common Letters Using AND**
```
common = lower & upper
       = 00000000000000000000000011
       & 00000000000000000000000010
       = 00000000000000000000000010

Bit 1 is set → letter 'b' is common
```

**Step 4: Count Set Bits**
```
popcount(00000000000000000000000010) = 1

Result: 1 ✓
```

---

### Example: "AaBbCc"

**Step 1: Initialize**
```
lower = 00000000000000000000000000
upper = 00000000000000000000000000
```

**Step 2: Process Characters**
```
'A' → upper |= (1 << 0) → upper = ...00000001
'a' → lower |= (1 << 0) → lower = ...00000001

'B' → upper |= (1 << 1) → upper = ...00000011
'b' → lower |= (1 << 1) → lower = ...00000011

'C' → upper |= (1 << 2) → upper = ...00000111
'c' → lower |= (1 << 2) → lower = ...00000111

Final:
lower = ...00000111  (a, b, c)
upper = ...00000111  (A, B, C)
```

**Step 3: Find Common**
```
common = ...00000111 & ...00000111
       = ...00000111

All 3 bits set!
```

**Step 4: Count Set Bits**
```
popcount(...00000111) = 3

Result: 3 ✓
```

---

## Code Full Solution

```cpp
class Solution {
public:
    int numberOfSpecialChars(string word) {
        int lower = 0;                         // Bitmask for lowercase letters
        int upper = 0;                         // Bitmask for uppercase letters

        // Step 1: Build bitmasks for each case
        for(char ch : word) {
            if(islower(ch)) {
                lower |= (1 << (ch - 'a'));   // Set bit for lowercase letter
            }
            else {
                upper |= (1 << (ch - 'A'));   // Set bit for uppercase letter
            }
        }
        
        // Step 2: Find letters that appear in both cases
        int common = lower & upper;            // AND to find common bits

        // Step 3: Count set bits in common
        return __builtin_popcount(common);     // Count 1's in binary
    }
};
```

---

## Code Explanation

### Initialize Bitmasks

```cpp
int lower = 0;
int upper = 0;
```

- **`lower`:** 26-bit mask for lowercase letters (a-z)
- **`upper`:** 26-bit mask for uppercase letters (A-Z)
- Each bit position represents a letter:
  - Bit 0 = 'a' or 'A'
  - Bit 1 = 'b' or 'B'
  - ...
  - Bit 25 = 'z' or 'Z'

---

### Build Bitmasks

```cpp
for(char ch : word) {
    if(islower(ch)) {
        lower |= (1 << (ch - 'a'));
    }
    else {
        upper |= (1 << (ch - 'A'));
    }
}
```

**For lowercase letters:**
```cpp
if(islower(ch)) {
    lower |= (1 << (ch - 'a'));
}
```

- **`ch - 'a'`:** Get position (0-25)
  - 'a' - 'a' = 0
  - 'b' - 'a' = 1
  - ...
  - 'z' - 'a' = 25

- **`1 << (ch - 'a')`:** Create bitmask with single bit set
  - For 'a': 1 << 0 = 00...0001
  - For 'b': 1 << 1 = 00...0010
  - For 'c': 1 << 2 = 00...0100

- **`|=`:** Bitwise OR assignment (set the bit)
  - Combines masks
  - Setting same bit twice: no change (idempotent)

**Example:**
```cpp
word = "aBbCc"

'a': ch - 'a' = 0
     1 << 0 = 1 (binary: 00...00001)
     lower |= 1 → lower = 1

'B': islower? NO, uppercase
     ch - 'A' = 1
     1 << 1 = 2 (binary: 00...00010)
     upper |= 2 → upper = 2

'b': ch - 'a' = 1
     1 << 1 = 2
     lower |= 2 → lower = 1 | 2 = 3 (00...00011)

'C': ch - 'A' = 2
     1 << 2 = 4 (binary: 00...00100)
     upper |= 4 → upper = 2 | 4 = 6 (00...00110)

'c': ch - 'a' = 2
     1 << 2 = 4
     lower |= 4 → lower = 3 | 4 = 7 (00...00111)

Final:
lower = 7 (00...00111) → a, b, c present
upper = 6 (00...00110) → B, C present
```

---

### Find Common Letters

```cpp
int common = lower & upper;
```

- **Bitwise AND (`&`):** Intersection of both masks
- Result has bits set **only where both** lower and upper have bits set
- These represent letters that appear in **both forms**

**Example:**
```
lower = 00...00111  (a, b, c)
upper = 00...00110  (B, C)
common = lower & upper
       = 00...00111
       & 00...00110
       = 00...00110  (B and C only)
```

Wait, that's wrong in my example. Let me recalculate:
- 'a': bit 0 in lower
- 'B': bit 1 in upper
- 'b': bit 1 in lower
- 'C': bit 2 in upper
- 'c': bit 2 in lower

```
lower = 00...00111  (bits 0, 1, 2 set for a, b, c)
upper = 00...00110  (bits 1, 2 set for B, C)
common = 00...00111 & 00...00110 = 00...00110
```

This gives bits 1 and 2, which represent 'b'/'B' and 'c'/'C' = 2 common letters.
But 'A' and 'a' should also match! Let me reconsider:

'A' (uppercase, not lowercase) should set bit 0 in upper
'a' (lowercase) sets bit 0 in lower

```
'A': uppercase, ch - 'A' = 0, bit 0 in upper
'a': lowercase, ch - 'a' = 0, bit 0 in lower
'B': uppercase, ch - 'A' = 1, bit 1 in upper
'b': lowercase, ch - 'a' = 1, bit 1 in lower
'C': uppercase, ch - 'A' = 2, bit 2 in upper
'c': lowercase, ch - 'a' = 2, bit 2 in lower

lower = 00...00111 (bits 0,1,2)
upper = 00...00111 (bits 0,1,2)
common = 00...00111 & 00...00111 = 00...00111 = 3 bits set
```

That's correct for "AaBbCc"!

---

### Count Set Bits

```cpp
return __builtin_popcount(common);
```

- **`__builtin_popcount()`:** Built-in GCC function
  - Counts number of 1's (set bits) in binary representation
  - O(1) time complexity on modern CPUs

**Examples:**
```cpp
__builtin_popcount(0b00000001) = 1    // One 1-bit
__builtin_popcount(0b00000011) = 2    // Two 1-bits
__builtin_popcount(0b00000111) = 3    // Three 1-bits
__builtin_popcount(0b00001111) = 4    // Four 1-bits
__builtin_popcount(0) = 0             // Zero 1-bits
```

---

## Complete Example Trace

### Input: "aBBBbb"

```
Initialize:
lower = 0 (00...00000)
upper = 0 (00...00000)

Process 'a' (lowercase):
  islower('a')? YES
  'a' - 'a' = 0
  lower |= (1 << 0) = 1
  lower = 00...00001

Process 'B' (uppercase):
  islower('B')? NO
  'B' - 'A' = 1
  upper |= (1 << 1) = 2
  upper = 00...00010

Process 'B' (uppercase):
  'B' - 'A' = 1
  upper |= (1 << 1) = 2
  upper = 00...00010 (no change, bit already set)

Process 'B' (uppercase):
  upper = 00...00010 (no change)

Process 'b' (lowercase):
  islower('b')? YES
  'b' - 'a' = 1
  lower |= (1 << 1) = 2
  lower = 00...00001 | 00...00010 = 00...00011

Process 'b' (lowercase):
  lower = 00...00011 (no change)

Find common:
common = lower & upper
       = 00...00011 & 00...00010
       = 00...00010

Count set bits:
__builtin_popcount(00...00010) = 1

Return: 1 ✓
```

---

### Input: "abc"

```
Initialize:
lower = 0
upper = 0

Process 'a': lower = 00...00001
Process 'b': lower = 00...00011
Process 'c': lower = 00...00111

upper remains 0 (no uppercase letters)

Find common:
common = 00...00111 & 00...00000 = 00...00000

Count set bits:
__builtin_popcount(0) = 0

Return: 0 ✓
```

---

## Alternative Approach: HashMap

```cpp
class Solution {
public:
    int numberOfSpecialChars(string word) {
        unordered_set<char> hasLower, hasUpper;
        
        for(char ch : word) {
            if(islower(ch)) {
                hasLower.insert(ch);
            } else {
                hasUpper.insert(ch);
            }
        }
        
        int count = 0;
        for(char ch : hasLower) {
            if(hasUpper.count(toupper(ch)) > 0) {
                count++;
            }
        }
        return count;
    }
};
```

**Comparison:**
```
Bitmask approach (Optimal):
  Time: O(n) - single pass
  Space: O(1) - only two integers

HashMap approach:
  Time: O(n) - single pass
  Space: O(1) - at most 26 unique chars per set

Both have similar complexity, but bitmask is more elegant!
```

---

## Edge Cases

### Case 1: No Uppercase
```
Input: "abc"
No uppercase letters present
common = 0
Result: 0 ✓
```

### Case 2: No Lowercase
```
Input: "ABC"
No lowercase letters present
common = 0
Result: 0 ✓
```

### Case 3: All Special
```
Input: "AaBbCc"
All letters have both forms
lower = 00...00111, upper = 00...00111
common = 00...00111
Result: 3 ✓
```

### Case 4: Single Special Character
```
Input: "AaBbBb"
'A' → 'a' works (bit 0)
'B' → 'b' works (bit 1)
lower = 00...00011, upper = 00...00011
common = 00...00011
Result: 2 ✓
```

### Case 5: Repeated Characters
```
Input: "aaAAaa"
'a' and 'A' both present multiple times
Still only counts once!
lower = 00...00001, upper = 00...00001
common = 00...00001
Result: 1 ✓
```

### Case 6: Mixed Order
```
Input: "AaBbCc" vs "abcABC"
Order doesn't matter (bitmasks capture presence)
Result: 3 ✓ in both cases
```

---

## Bitmask Operations Deep Dive

### Bitwise OR (|)
```
Combines bits: if either is 1, result is 1
1010 | 0101 = 1111
Sets new bits while preserving existing ones
```

### Bitwise AND (&)
```
Intersection: both must be 1 for result to be 1
1010 & 0101 = 0000
1010 & 1010 = 1010
Finds common bits
```

### Left Shift (<<)
```
Moves bits left, fills with 0 on right
1 << 0 = 00...00001
1 << 1 = 00...00010
1 << 2 = 00...00100
Creates single-bit masks at specific positions
```

### Popcount
```
Counts the number of 1-bits
00...00000 → 0
00...00001 → 1
00...00011 → 2
00...00111 → 3
00...01111 → 4
```

---

## Why Bitmask Over HashMap?

**Bitmask advantages:**
- ✅ **Faster access:** Direct bit operations vs hash lookups
- ✅ **Predictable:** O(1) guaranteed, no collisions
- ✅ **Memory efficient:** Single integer vs set of characters
- ✅ **Elegant:** Shows bit masking patterns

**HashMap advantages:**
- ✅ **Intuitive:** Easier to understand for some
- ✅ **Scalable:** Works if alphabet grows
- ✅ **Readable:** More recognizable code

**For this problem:** Bitmask is superior!

---

## Time Complexity

- **Building bitmasks:** O(n)
  - Single pass through word
  - Each operation (islower, |=, <<) is O(1)

- **Finding common:** O(1)
  - Single bitwise AND operation

- **Counting bits:** O(1)
  - popcount is O(1) on modern CPUs

- **Total: O(n)** where n = length of word

---

## Space Complexity

- **O(1)** constant space
- Only two integers: `lower` and `upper`
- No additional data structures
- No recursion

**This is optimal!**

---

## Key Insights

### Why `|=` Instead of `=`?

```cpp
lower |= (1 << pos);     // Set bit
lower = (1 << pos);      // Replace entire mask (WRONG!)
```

- `|=` preserves existing bits
- `=` overwrites entire mask
- Multiple characters would lose previous bits

**Example:**
```cpp
lower = 0

// Wrong way:
'a' → lower = (1 << 0) = 00...00001
'b' → lower = (1 << 1) = 00...00010  (lost 'a' bit!)

// Right way:
'a' → lower |= (1 << 0) = 00...00001
'b' → lower |= (1 << 1) = 00...00011 (keeps 'a' bit!)
```

---

### Why `___builtin_popcount()`?

```cpp
// Manual counting (slower):
int count = 0;
while(common) {
    count += common & 1;
    common >>= 1;
}
return count;

// Built-in (faster):
return __builtin_popcount(common);
```

- **Built-in is optimized:** CPU has special instruction
- **Single cycle:** On modern processors
- **Standard in competitive programming**

---

## Key Takeaway

**Bitmasks are the Swiss Army knife for set operations.** When dealing with a fixed alphabet (26 letters), use bits instead of data structures! Each bit's presence/absence answers the question: "Is this letter present?" Efficient, elegant, and lightning-fast! ⚡

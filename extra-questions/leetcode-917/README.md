# Reverse Only Letters

**Problem Link:** https://leetcode.com/problems/reverse-only-letters

## What is this Problem?

We need to **reverse only the letters in a string**, leaving all non-letter characters in their original positions.

**Key Points:**
- Letters get reversed
- Non-letters (digits, special characters) stay in place
- Both uppercase and lowercase are letters

**Example:**
```
Input: "ab-cd"
Output: "dc-ba"

Letters in order: a, b, c, d
Reversed: d, c, b, a
Place them back: d, c (at positions for a, b), then -, then b, a (at positions for c, d)
Result: "dc-ba"
```

```
Input: "a-bC-dEf-ghIj"
Output: "j-Ih-gfE-dCba"

Original positions: a b C d E f g h I j (non-letters ignored for reversal)
Reversed order: j I h g f E d C B a
Put back: j - I h - g f E - d C b a
Result: "j-Ih-gfE-dCba"
```

---

## The Problem Explained

Imagine you have a password: `"ab-cd"`

You want to reverse only the letters: `"dc-ba"`

The **hyphens stay where they are**, but letters swap around.

Think of it as:
1. **Find all letters** and remember their order
2. **Reverse that order**
3. **Fill back the letters** into letter positions, keeping non-letters unchanged

---

## HOOK TO REMEMBER FOREVER

### **"TWO POINTERS: SKIP NON-LETTERS, SWAP LETTERS"**

Every time you see this problem:
- ✅ Use **two pointers** (start and end)
- ✅ Move them towards each other
- ✅ Skip non-letter characters
- ✅ When both point to letters, **swap them**
- ✅ Continue until pointers meet

**Remember: Letters reverse in place, non-letters watch!** 🔤

---

## How It Works Step By Step

### Example: Process `"ab-cd"`

**Setup:**
```
String: a b - c d
Index:  0 1 2 3 4
Left pointer (i): 0
Right pointer (j): 4
```

**Step 1: Both point to letters**
```
i=0 (pointing to 'a'), j=4 (pointing to 'd')
Both are letters → SWAP them
String: d b - c a
i++, j--
```

**Step 2: Both point to letters**
```
i=1 (pointing to 'b'), j=3 (pointing to 'c')
Both are letters → SWAP them
String: d c - b a
i++, j--
```

**Step 3: Pointers cross**
```
i=2, j=2
i is not < j, STOP
```

**Result:** `"dc-ba"` ✓

---

### Example: Process `"a-bC-dEf-ghIj"`

**Setup:**
```
String: a - b C - d E f - g h I j
Index:  0 1 2 3 4 5 6 7 8 9 10 11 12
i = 0, j = 12
```

**Step 1:**
```
i=0 (a), j=12 (j) → Both letters → SWAP
String: j - b C - d E f - g h I a
i=1, j=11
```

**Step 2:**
```
i=1 (-) → Not a letter, skip → i=2
j=11 (I) → Letter
i=2 (b), j=11 (I) → Both letters → SWAP
String: j - I C - d E f - g h b a
i=3, j=10
```

**Step 3:**
```
i=3 (C), j=10 (h) → Both letters → SWAP
String: j - I h - d E f - g C b a
i=4, j=9
```

**Step 4:**
```
i=4 (-) → Not a letter, skip → i=5
j=9 (g) → Letter
i=5 (d), j=9 (g) → Both letters → SWAP
String: j - I h - g E f - d C b a
i=6, j=8
```

**Step 5:**
```
i=6 (E), j=8 (f) → Both letters → SWAP
String: j - I h - g f E - d C b a
i=7, j=7
```

**Step 6:**
```
i=7 (-) → Not a letter, skip → i=8
i=8 > j=7 → STOP
```

**Result:** `"j-Ih-gfE-dCba"` ✓

---

## Code Full Solution

```cpp
class Solution {
public:
    string reverseOnlyLetters(string s) {
        int n = s.size();
        int i = 0;                              // Left pointer
        int j = n - 1;                          // Right pointer

        while(i < j) {                          // While pointers haven't crossed
            
            while(i < n && !isalpha(s[i])) i++;  // Skip non-letters from left
            while(j >= 0 && !isalpha(s[j])) j--; // Skip non-letters from right
            
            if(i < j) {                         // If valid positions to swap
                swap(s[i], s[j]);               // Swap the letters
                i++;                            // Move left pointer right
                j--;                            // Move right pointer left
            }
        }
        return s;                               // Return reversed string
    }
};
```

---

## Code Explanation

### Setup

```cpp
int n = s.size();
int i = 0;
int j = n - 1;
```

- **`n`:** Size of string (length)
- **`i`:** Left pointer, starts at beginning
- **`j`:** Right pointer, starts at end

---

### Main Loop

```cpp
while(i < j) {
```

- Continue while pointers haven't crossed
- Stop when they meet or pass

---

### Skip Non-Letters (Left Side)

```cpp
while(i < n && !isalpha(s[i])) i++;
```

- **`i < n`:** Don't go out of bounds
- **`!isalpha(s[i])`:** While current character is NOT a letter
  - **`isalpha()`:** Returns true if character is a letter (a-z, A-Z)
  - **`!`:** NOT operator, so we keep looping while NOT alpha
- **`i++`:** Move left pointer right

**Example:**
```
String: "a-bcd"
i=0: s[0]='a', isalpha('a')=true, stop (don't increment)
i=0 (position of 'a')

String: "-abcd"
i=0: s[0]='-', isalpha('-')=false, i++ → i=1
i=1: s[1]='a', isalpha('a')=true, stop
i=1 (position of 'a')
```

---

### Skip Non-Letters (Right Side)

```cpp
while(j >= 0 && !isalpha(s[j])) j--;
```

- **`j >= 0`:** Don't go out of bounds
- **`!isalpha(s[j])`:** While current character is NOT a letter
- **`j--`:** Move right pointer left

**Example:**
```
String: "abcd-"
j=4: s[4]='-', isalpha('-')=false, j-- → j=3
j=3: s[3]='d', isalpha('d')=true, stop
j=3 (position of 'd')

String: "abcd"
j=3: s[3]='d', isalpha('d')=true, stop (don't decrement)
j=3 (position of 'd')
```

---

### Check Before Swapping

```cpp
if(i < j) {
    swap(s[i], s[j]);
    i++;
    j--;
}
```

- **`if(i < j)`:** Only swap if pointers haven't crossed
  - Prevents double-swapping or swapping same character
- **`swap(s[i], s[j])`:** Exchange characters at both pointers
  - Example: swap('a', 'z') → string becomes "...z...a..."
- **`i++`:** Move left pointer towards center
- **`j--`:** Move right pointer towards center

---

## Complete Example Trace

```
Input: "ab-cd"

Initial: i=0, j=4, s="ab-cd"

Iteration 1:
  while(i<4 && !isalpha('a')): isalpha('a')=true, stop, i=0
  while(j>=0 && !isalpha('d')): isalpha('d')=true, stop, j=4
  if(0<4): true
    swap(s[0], s[4]) → s="db-ca"
    i=1, j=3

Iteration 2:
  while(1<4 && !isalpha('b')): isalpha('b')=true, stop, i=1
  while(3>=0 && !isalpha('c')): isalpha('c')=true, stop, j=3
  if(1<3): true
    swap(s[1], s[3]) → s="dc-ba"
    i=2, j=2

Loop Check:
  i<j? 2<2? false → EXIT

Return: "dc-ba" ✓
```

---

## Edge Cases

### Case 1: No Letters
```
Input: "---"
i moves to index 3 (out of bounds)
j moves to index -1 (out of bounds)
while condition fails
Output: "---"
```

### Case 2: No Non-Letters
```
Input: "abcd"
i=0 → 'a', j=3 → 'd', swap → "dbca"
i=1 → 'b', j=2 → 'c', swap → "dcba"
i=2, j=1, i>j, stop
Output: "dcba"
```

### Case 3: Single Character
```
Input: "a"
i=0, j=0
while(i<j): 0<0 false → EXIT immediately
Output: "a"
```

### Case 4: Mixed Case
```
Input: "Aa-B"
i=0 → 'A', j=3 → 'B', swap → "Ba-A"
i=1 → 'a', j=2 → '-', j skip to j=1
i=1 → 'a', j=1
while(1<1): false → EXIT
Output: "Ba-A"
```

### Case 5: Empty String
```
Input: ""
n=0, i=0, j=-1
while(i<j): 0<-1 false → EXIT
Output: ""
```

---

## Why Two Pointers?

**Two-pointer approach is optimal here:**
- ✅ **O(1) space:** Only pointers, no extra data structure
- ✅ **O(n) time:** Each character visited once
- ✅ **In-place:** Modifies original string directly
- ✅ **Simple logic:** Just skip and swap

**Alternative approach (would be less efficient):**
```
// Could extract letters, reverse them, put back
// But this uses O(n) extra space!
vector<char> letters;
for(char c : s) {
    if(isalpha(c)) letters.push_back(c);
}
reverse(letters.begin(), letters.end());
int idx = 0;
for(int i = 0; i < s.size(); i++) {
    if(isalpha(s[i])) s[i] = letters[idx++];
}
```

**Two-pointers is better!**

---

## Key Insights

### `isalpha()` Function
```cpp
isalpha('a')   → true
isalpha('Z')   → true
isalpha('5')   → false
isalpha('-')   → false
isalpha(' ')   → false
```

- **Returns true** for any letter (uppercase or lowercase)
- **Returns false** for digits, special chars, spaces

### `swap()` Function
```cpp
string s = "ab";
swap(s[0], s[1]);  // s becomes "ba"
```

- **Built-in function** that exchanges values
- Works for any data type

### Why Check `i < j` Before Swap?
```
If we don't check:
String: "ab"
Iteration 1: i=0, j=1, swap → "ba", i=1, j=0
Iteration 2: while(1<0) false → exit
Seems okay...

String: "a"
Iteration 1: i=0, j=0, no check → swap('a','a') → "a", i=1, j=-1
Pointers crossed, but we swapped same character!
The check prevents this.
```

---

## Time Complexity

- **O(n)** where n = length of string
- Each character is visited at most once
- All operations (swap, isalpha) are O(1)

---

## Space Complexity

- **O(1)** (excluding output string)
- Only uses two pointers `i` and `j`
- Modifies string in-place

---

## Key Takeaway

**Two pointers moving towards each other is the perfect strategy for reversing with exceptions.** Instead of reversing everything and then fixing non-letters, we skip non-letters and reverse only letters in one pass! ✨

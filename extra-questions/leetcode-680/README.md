# Valid Palindrome II

**Problem Link:** https://leetcode.com/problems/valid-palindrome-ii/

## What is this Problem?

We need to check if a string is a **valid palindrome after deleting at most one character**.

**Key Points:**
- A palindrome reads the same forwards and backwards
- We can delete **at most one character**
- If it's already a palindrome, return true
- If we can remove one character to make it a palindrome, return true
- Otherwise, return false

**Examples:**
```
Input: "aba"
Output: true
Explanation: Already a palindrome, no deletion needed

Input: "abca"
Output: true
Explanation: Delete 'c', becomes "aba" which is palindrome

Input: "abc"
Output: false
Explanation: Can't form palindrome even by deleting one character
```

---

## The Problem Explained

Imagine you have a word and you want to check if it's a palindrome. But here's the catch - you have **one free pass** to delete a character if needed!

**Scenarios:**
1. **Already palindrome?** → Return true immediately
2. **Found mismatch?** → Try deleting left character OR right character, then check if remaining is palindrome
3. **Neither works?** → Return false

Think of it as:
1. **Compare characters from both ends** using two pointers
2. **If they match**, move both pointers inward
3. **If they don't match**, you have **two choices**:
   - Skip the left character and check if rest is palindrome
   - Skip the right character and check if rest is palindrome
4. **If either choice works**, return true

---

## HOOK TO REMEMBER FOREVER

### **"TWO POINTERS: MATCH OR MAKE A CHOICE"**

Every time you see this problem:
- ✅ Use **two pointers** from both ends
- ✅ Compare characters
- ✅ **If match** → Move both inward
- ✅ **If mismatch** → We get **one delete**: skip left OR skip right
- ✅ Check if remaining (with gap) is palindrome
- ✅ Return true if either deletion works

**Remember: Match perfectly, or get one do-over!** 🎯

---

## How It Works Step By Step

### Example 1: "aba" (Already Palindrome)

**Setup:**
```
String: a b a
Index:  0 1 2
i = 0, j = 2
```

**Step 1:**
```
s[0]='a', s[2]='a' → Match! ✓
i=1, j=1
```

**Step 2:**
```
i < j? 1 < 1? No → Exit loop
```

**Result:** `true` (palindrome, no deletion needed) ✓

---

### Example 2: "abca" (Can be Fixed by Deleting One)

**Setup:**
```
String: a b c a
Index:  0 1 2 3
i = 0, j = 3
```

**Step 1:**
```
s[0]='a', s[3]='a' → Match! ✓
i=1, j=2
```

**Step 2:**
```
s[1]='b', s[2]='c' → Mismatch! ✗
Now we have two choices:

Option 1: Delete left character 'b'
  Check if s[2..2] is palindrome
  Remaining: "c"
  Single char = palindrome ✓
  
Option 2: Delete right character 'c'
  Check if s[1..1] is palindrome
  Remaining: "b"
  Single char = palindrome ✓

Either works! Return true
```

**Result:** `true` (can be made palindrome by deleting one char) ✓

---

### Example 3: "abc" (Cannot be Fixed)

**Setup:**
```
String: a b c
Index:  0 1 2
i = 0, j = 2
```

**Step 1:**
```
s[0]='a', s[2]='c' → Mismatch! ✗

Try Option 1: Delete left 'a'
  Check if "bc" is palindrome
  b ≠ c → Not a palindrome ✗
  
Try Option 2: Delete right 'c'
  Check if "ab" is palindrome
  a ≠ b → Not a palindrome ✗

Both fail! Return false
```

**Result:** `false` (cannot be made palindrome) ✓

---

## Code Full Solution

```cpp
class Solution {
private:
    // Helper function: check if substring is palindrome
    bool isPalindrome(string& s, int left, int right) {
        while(left < right) {
            if(s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }

public:
    bool validPalindrome(string s) {
        int n = s.size();
        int i = 0;
        int j = n - 1;

        while(i < j) {
            if(s[i] != s[j]) {
                // Mismatch found - try two options:
                // Option 1: Delete left character, check s[i+1..j]
                // Option 2: Delete right character, check s[i..j-1]
                return isPalindrome(s, i + 1, j) || isPalindrome(s, i, j - 1);
            }
            i++;
            j--;
        }

        // No mismatches found - already a palindrome
        return true;
    }
};
```

---

## Code Explanation

### Helper Function: `isPalindrome()`

```cpp
bool isPalindrome(string& s, int left, int right) {
    while(left < right) {
        if(s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}
```

- **Purpose:** Check if substring from `left` to `right` is a palindrome
- **`string& s`:** Reference to string (efficient, no copy)
- **`left`, `right`:** Starting and ending indices
- **Loop:** Compare characters from opposite ends moving inward
- **Return:** true if all pairs match, false if any mismatch

**Example:**
```cpp
s = "abca", left = 2, right = 2
s[2] = 'c'
left < right? 2 < 2? No → return true
Single character is always palindrome ✓
```

---

### Main Function: `validPalindrome()`

#### Setup
```cpp
int n = s.size();
int i = 0;
int j = n - 1;
```

- **`n`:** Size of string
- **`i`:** Left pointer (start)
- **`j`:** Right pointer (end)

---

#### Main Loop

```cpp
while(i < j) {
    if(s[i] != s[j]) {
        // Character mismatch - one deletion allowed
        return isPalindrome(s, i + 1, j) || isPalindrome(s, i, j - 1);
    }
    i++;
    j--;
}
```

**Loop Logic:**
1. **Check if characters match:**
   - If `s[i] == s[j]`: Move both pointers inward
   - If `s[i] != s[j]`: We found the mismatch point!

2. **On mismatch, we have two choices:**
   - **Option 1:** Skip left character → Check `isPalindrome(s, i+1, j)`
   - **Option 2:** Skip right character → Check `isPalindrome(s, i, j-1)`
   - Return true if **either** works (using OR operator `||`)

**Example Trace:**
```
String: "racecar"
i=0, j=6: s[0]='r', s[6]='r' → Match, i=1, j=5
i=1, j=5: s[1]='a', s[5]='a' → Match, i=2, j=4
i=2, j=4: s[2]='c', s[4]='c' → Match, i=3, j=3
i=3, j=3: i < j? No → Exit loop, return true
```

---

#### No Mismatch Case

```cpp
return true;
```

If the loop completes without finding a mismatch, the string is already a palindrome.

---

## Complete Example Trace

### Trace 1: "abca"

```
Input: "abca"
n = 4, i = 0, j = 3

Iteration 1:
  s[0]='a', s[3]='a' → Match
  i=1, j=2

Iteration 2:
  s[1]='b', s[2]='c' → Mismatch!
  isPalindrome(s, 2, 2)? (check "c")
    left=2, right=2: left < right? No → return true ✓
  return true || ... → return true

Output: true ✓
```

---

### Trace 2: "abc"

```
Input: "abc"
n = 3, i = 0, j = 2

Iteration 1:
  s[0]='a', s[2]='c' → Mismatch!
  
  Try Option 1: isPalindrome(s, 1, 2)? (check "bc")
    left=1, right=2: s[1]='b', s[2]='c'
    'b' != 'c' → return false ✗
  
  Try Option 2: isPalindrome(s, 0, 1)? (check "ab")
    left=0, right=1: s[0]='a', s[1]='b'
    'a' != 'b' → return false ✗
  
  return false || false → return false

Output: false ✓
```

---

### Trace 3: "deeee"

```
Input: "deeee"
n = 5, i = 0, j = 4

Iteration 1:
  s[0]='d', s[4]='e' → Mismatch!
  
  Try Option 1: isPalindrome(s, 1, 4)? (check "eeee")
    Compare: 'e'=='e' && 'e'=='e' → return true ✓
  
  return true || ... → return true

Output: true ✓
(Explanation: Delete 'd', "eeee" is palindrome)
```

---

## Edge Cases

### Case 1: Already Palindrome
```
Input: "racecar"
i=0: 'r'=='r' ✓
i=1: 'a'=='a' ✓
i=2: 'c'=='c' ✓
i=3: 'c'=='c' ✓
All match, return true
```

### Case 2: Single Character
```
Input: "a"
n=1, i=0, j=0
while(0 < 0): false → exit, return true
Single char is always palindrome
```

### Case 3: Two Characters - Match
```
Input: "aa"
n=2, i=0, j=1
s[0]='a', s[1]='a' → Match, i=1, j=0
while(1 < 0): false → exit, return true
```

### Case 4: Two Characters - Mismatch
```
Input: "ab"
n=2, i=0, j=1
s[0]='a', s[1]='b' → Mismatch!
isPalindrome(s, 1, 1)? "b" → true ✓
OR
isPalindrome(s, 0, 0)? "a" → true ✓
Either works, return true
(Delete either 'a' or 'b', single char left)
```

### Case 5: Needs Specific Deletion
```
Input: "aguokepatgbnvfqmgmlcupuufxoohdfpgjdmysgvhmvffcnqxjjxqncffvmhvgsymdjgpfdhooxfuupmlcugmqfvnbgtapekouga"

This is a long palindrome with one extra character
that needs to be removed strategically.
Algorithm finds the mismatch and checks both options.
```

---

## Key Insights

### Why Helper Function?

We need to **verify palindromes multiple times**:
- When checking original string with left deleted
- When checking original string with right deleted

Creating a helper function avoids code duplication.

```cpp
// Without helper (messy):
bool isPalindromeLeftSkip = true;
int l = i + 1, r = j;
while(l < r) {
    if(s[l] != s[r]) {
        isPalindromeLeftSkip = false;
        break;
    }
    l++;
    r--;
}

bool isPalindromeRightSkip = true;
l = i, r = j - 1;
while(l < r) {
    if(s[l] != s[r]) {
        isPalindromeRightSkip = false;
        break;
    }
    l++;
    r--;
}

return isPalindromeLeftSkip || isPalindromeRightSkip;

// With helper (clean):
return isPalindrome(s, i + 1, j) || isPalindrome(s, i, j - 1);
```

---

### Why Two Pointers?

**Optimal approach:**
- ✅ **O(n) time:** Each character visited at most twice
- ✅ **O(1) space:** Only pointers, no extra data structure
- ✅ **Early termination:** Stops at first mismatch
- ✅ **Minimal comparisons:** Skips middle characters

**Alternative (convert to array):**
```cpp
// Less efficient
string s2 = removeCharAt(s, i);
if(isPalindrome(s2)) return true;

string s3 = removeCharAt(s, j);
if(isPalindrome(s3)) return true;

return false; // O(n²) in worst case
```

---

### Why Use Reference Parameter?

```cpp
bool isPalindrome(string& s, int left, int right)
                          ↑ reference
```

- **`&`:** Pass by reference (efficient)
- **Avoids copying** the entire string
- **Common optimization** in competitive programming

```cpp
// Without reference (creates copy):
bool isPalindrome(string s, int left, int right) // Copies entire string!

// With reference (efficient):
bool isPalindrome(string& s, int left, int right) // No copy ✓
```

---

## Time Complexity

- **Worst case: O(n)**
  - First scan: O(n) comparing with two pointers
  - On mismatch: O(n) to check remaining substring
  - Total: O(n) + O(n) = O(n)

- **Best case: O(1)**
  - Already a palindrome, no checking needed
  - Actually O(n) since we scan the whole string

- **Overall: O(n)** where n = length of string

```
Example: "racecar" (no mismatch)
Compare all n pairs: O(n)

Example: "abca"
Compare first 2 pairs: O(2)
Find mismatch
Check remaining "c": O(1)
Total: O(n)
```

---

## Space Complexity

- **O(1)** excluding output
- Only uses pointers `i`, `j` and function call stack
- Recursion depth: O(1) (isPalindrome is not recursive)

---

## Key Takeaway

**Two pointers find the problem, helper function solves it gracefully.** When you encounter a mismatch in a palindrome check, leverage the "one deletion" rule by trying both skip options. This greedy approach works because we only need to skip one character! ✨

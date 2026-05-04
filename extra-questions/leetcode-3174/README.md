# Clear Digits 

## What is this Problem?

We have a **string with letters and digits mixed**. When we encounter a **digit**, we must:
1. **Remove that digit**
2. **Remove the character before it** (the closest letter to the left)

We keep processing until there are no more digits.

**Example:**
```
String: a1bcd2e9f4g
Process digit 1: Remove '1' and 'a' before it → bcd2e9f4g
Process digit 2: Remove '2' and 'd' before it → bce9f4g
Process digit 9: Remove '9' and 'e' before it → bcf4g
Process digit 4: Remove '4' and 'f' before it → bcg

Final: bcg
```

---

## The Problem Explained 

### Think of it Like a Blackboard 

```
Teacher writes on board:
a 1 b c d 2 e 9 f 4 g

When teacher sees a digit (eraser), erases it AND the letter before:
a → erase with 1 → gone
    1 b c d 2 e 9 f 4 g
d → erase with 2 → gone
    1 b c → gone
e → erase with 9 → gone
    1 b c 2 → gone
f → erase with 4 → gone
    1 b c 2 9 → gone

What's left on board: b c g
```

---

## HOOK TO REMEMBER FOREVER

### **"LETTERS TO STACK, DIGIT REMOVES TOP STACK"**

Every time you see this problem:
- ✅ Build a stack of characters as you go
- ✅ When you hit a digit, pop from stack (remove letter before it)
- ✅ Result is what remains in stack

**Remember: Like an undo button - digit erases itself and previous letter!** ↩️

---

## How It Works Step By Step

### Example: Process `"a1bcd2e9f4g"`

**Start:**
```
String: a 1 b c d 2 e 9 f 4 g
Stack:  (empty)
```

**Step 1: Read 'a' (letter)**
```
Add to stack: push('a')
Stack: [a]
String remaining: 1 b c d 2 e 9 f 4 g
```

**Step 2: Read '1' (digit)**
```
It's a digit! Pop from stack
Stack: [] (remove 'a')
String remaining: b c d 2 e 9 f 4 g
```

**Step 3: Read 'b' (letter)**
```
Add to stack: push('b')
Stack: [b]
String remaining: c d 2 e 9 f 4 g
```

**Step 4: Read 'c' (letter)**
```
Add to stack: push('c')
Stack: [b, c]
String remaining: d 2 e 9 f 4 g
```

**Step 5: Read 'd' (letter)**
```
Add to stack: push('d')
Stack: [b, c, d]
String remaining: 2 e 9 f 4 g
```

**Step 6: Read '2' (digit)**
```
It's a digit! Pop from stack
Stack: [b, c] (remove 'd')
String remaining: e 9 f 4 g
```

**Step 7: Read 'e' (letter)**
```
Add to stack: push('e')
Stack: [b, c, e]
String remaining: 9 f 4 g
```

**Step 8: Read '9' (digit)**
```
It's a digit! Pop from stack
Stack: [b, c] (remove 'e')
String remaining: f 4 g
```

**Step 9: Read 'f' (letter)**
```
Add to stack: push('f')
Stack: [b, c, f]
String remaining: 4 g
```

**Step 10: Read '4' (digit)**
```
It's a digit! Pop from stack
Stack: [b, c] (remove 'f')
String remaining: g
```

**Step 11: Read 'g' (letter)**
```
Add to stack: push('g')
Stack: [b, c, g]
String remaining: (empty)
```

**Final Result:**
```
Stack: [b, c, g]
Return as string: "bcg" ✓
```

---

## Code Full Solution

```cpp
class Solution {
public:
    string clearDigits(string s) {
        string ans;                    // Use string as a stack
        
        for(auto &el : s) {            // Go through each character
            if(isdigit(el)) {          // Is it a digit?
                ans.pop_back();        // YES: Remove letter before (pop stack)
            } else {
                ans.push_back(el);     // NO: Add this letter to stack
            }
        }
        
        return ans;                    // Return what's left in stack
    }
};
```

---

## Code Explanation

### Step 1: Initialize Answer String (Stack)

```cpp
string ans;
```

- We use a `string` like a stack
- **Push:** `ans.push_back(char)` - add to end
- **Pop:** `ans.pop_back()` - remove from end
- **Top:** `ans.back()` - view last character

**Why string as stack?**
- Easy to build final answer
- No need for separate data structures
- Last character we add is easiest to remove

### Step 2: Loop Through Each Character

```cpp
for(auto &el : s) {
```

- **`auto &el`:** Reference to each character in string `s`
- Go through string one character at a time, left to right

**Example with `"a1bcd2"`:**
```
Iteration 1: el = 'a'
Iteration 2: el = '1'
Iteration 3: el = 'b'
Iteration 4: el = 'c'
Iteration 5: el = 'd'
Iteration 6: el = '2'
```

### Step 3: Check if Character is a Digit

```cpp
if(isdigit(el)) {
```

- **`isdigit(el)`:** Returns true if el is '0' to '9'
- Returns false if el is a letter

**Examples:**
```
isdigit('a') = false
isdigit('1') = true
isdigit('z') = false
isdigit('5') = true
```

### Step 4a: If Digit - Remove Previous Letter

```cpp
    ans.pop_back();
}
```

- **`ans.pop_back()`:** Remove the last character from ans
- This is the letter before the digit!

**Example:**
```
ans = "bcd"
After digit: ans.pop_back() → ans = "bc"
(Removed 'd', the letter before the digit)
```

### Step 4b: If Letter - Add to Stack

```cpp
} else {
    ans.push_back(el);
}
```

- **`ans.push_back(el)`:** Add this character to the end
- Store it in our stack for potential removal later

**Example:**
```
ans = "bc"
Add 'd': ans.push_back('d') → ans = "bcd"
```

### Step 5: Return the Stack Contents

```cpp
return ans;
```

- The answer string now contains only letters (digits erased them!)
- Return it as the final result

---

## Complete Example Trace

```
Input: s = "a1bcd2e9f4g"

Initial: ans = ""

i=0: el='a', not digit
     ans.push_back('a') → ans = "a"

i=1: el='1', is digit
     ans.pop_back() → ans = ""

i=2: el='b', not digit
     ans.push_back('b') → ans = "b"

i=3: el='c', not digit
     ans.push_back('c') → ans = "bc"

i=4: el='d', not digit
     ans.push_back('d') → ans = "bcd"

i=5: el='2', is digit
     ans.pop_back() → ans = "bc"

i=6: el='e', not digit
     ans.push_back('e') → ans = "bce"

i=7: el='9', is digit
     ans.pop_back() → ans = "bc"

i=8: el='f', not digit
     ans.push_back('f') → ans = "bcf"

i=9: el='4', is digit
     ans.pop_back() → ans = "bc"

i=10: el='g', not digit
      ans.push_back('g') → ans = "bcg"

Return: "bcg" ✓
```

---

## Edge Cases 

### Case 1: All Digits
```
Input: "123"
Process:
  '1' → pop (nothing to pop, stack empty) → ans = ""
  '2' → pop (nothing to pop, stack empty) → ans = ""
  '3' → pop (nothing to pop, stack empty) → ans = ""

Output: "" (empty string)

Note: pop_back() on empty string is safe in C++
```

### Case 2: No Digits
```
Input: "abc"
Process:
  'a' → push → ans = "a"
  'b' → push → ans = "ab"
  'c' → push → ans = "abc"

Output: "abc" (unchanged)
```

### Case 3: More Digits Than Letters
```
Input: "a1b2c3"
Process:
  'a' → push → ans = "a"
  '1' → pop → ans = ""
  'b' → push → ans = "b"
  '2' → pop → ans = ""
  'c' → push → ans = "c"
  '3' → pop → ans = ""

Output: "" (all letters removed)
```

### Case 4: Consecutive Digits
```
Input: "ab12cd"
Process:
  'a' → push → ans = "a"
  'b' → push → ans = "ab"
  '1' → pop → ans = "a"
  '2' → pop → ans = ""
  'c' → push → ans = "c"
  'd' → push → ans = "cd"

Output: "cd"

Note: Each digit removes the letter before it sequentially
```

---

## Time Complexity 

- **O(n)** where n = length of string
- We go through each character exactly once
- Each operation (push_back, pop_back) is O(1)

---

## Space Complexity

- **O(n)** for the answer string
- In worst case (no digits), we store entire input

---

## Key Insights

### Why String Works as Stack
```
Stack operations needed:
- Push letter ✓ (ans.push_back(char))
- Pop letter ✓ (ans.pop_back())
- View top ✓ (ans.back())
- Check empty ✓ (ans.empty())

String provides all of these!
```

### Stack Pattern This Problem Uses
```
Many problems use stack:
1. Parentheses matching: ( ) [ ] { }
2. Expression evaluation
3. Undo/redo functionality
4. (THIS PROBLEM) Remove element and its predecessor
```

**Stack is perfect because:**
- Last In, First Out (LIFO)
- Digit removes most recent letter
- Natural order of removal!

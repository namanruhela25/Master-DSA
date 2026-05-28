# Keyboard Row

**Problem Link:** https://leetcode.com/problems/keyboard-row/

## What is this Problem?

We need to find all words that **can be typed using letters from only one row** of a QWERTY keyboard.

The keyboard has 3 rows:
- **Row 1:** `qwertyuiop`
- **Row 2:** `asdfghjkl`
- **Row 3:** `zxcvbnm`

**Key Points:**
- A word is valid if all its letters come from the **same keyboard row**
- Case-insensitive (e.g., 'Q' and 'q' are equivalent)
- Order of letters in the word doesn't matter
- Return all valid words as a vector

**Examples:**
```
Input: ["Hello", "Alaska", "Dad", "peace"]
Output: ["Alaska", "Dad"]

Explanation:
- "Hello": H(row2), e(row1), l(row2), l(row2), o(row1) → Multiple rows ✗
- "Alaska": A(row2), l(row2), a(row2), s(row2), k(row2), a(row2) → Row 2 only ✓
- "Dad": D(row2), a(row2), d(row2) → Row 2 only ✓
- "peace": p(row1), e(row1), a(row2), c(row3), e(row1) → Multiple rows ✗

Input: ["omk", "say", "cbs"]
Output: ["omk", "say"]

Explanation:
- "omk": o(row1), m(row3), k(row2) → Multiple rows ✗
Wait, let me recalculate:
- o is in row1 (qwertyuiop)
- m is in row3 (zxcvbnm)
- k is in row2 (asdfghjkl)
So "omk" uses all 3 rows → should NOT be in output

Actually the output should be ["say"]
- "say": s(row2), a(row2), y(row1) → Wait, y is in row1

Let me check again:
Row1: qwertyuiop (q,w,e,r,t,y,u,i,o,p)
Row2: asdfghjkl  (a,s,d,f,g,h,j,k,l)
Row3: zxcvbnm     (z,x,c,v,b,n,m)

- "say": s(row2), a(row2), y(row1) → Multiple rows ✗

Let me use correct examples:
- "qwerty": q(1), w(1), e(1), r(1), t(1), y(1) → Row 1 only ✓
- "asdf": a(2), s(2), d(2), f(2) → Row 2 only ✓
- "zxcv": z(3), x(3), c(3), v(3) → Row 3 only ✓
- "hello": h(2), e(1), l(2), l(2), o(1) → Multiple rows ✗
```

---

## The Problem Explained

Imagine you're checking which words can be typed by only pressing **one row** of your keyboard without moving your hand vertically.

**Scenario:** If you rest your hand on the middle row (asdfghjkl):
- "ask" ✓ (all keys within reach: a, s, k)
- "pad" ✗ (p is in top row, out of reach)

**Questions asked:**
1. **Which row does each letter belong to?**
2. **Do all letters in the word belong to the same row?**
3. **If yes, include it in the result.**

---

## HOOK TO REMEMBER FOREVER

### **"MAP TO ROWS, CHECK CONSISTENCY, COLLECT VALID WORDS"**

Every time you see this problem:
- ✅ **Map each character** to its keyboard row
- ✅ For **each word**, check if **all characters** are in the **same row**
- ✅ Use **case-insensitive comparison** (convert to lowercase)
- ✅ **Collect and return** all valid words

**Remember: All letters must come from the same row!** ⌨️

---

## How It Works Step By Step

### Example: ["Alaska", "Hello"]

**Step 1: Create Keyboard Row Mapping**
```
Row 1: qwertyuiop → map[q]=1, map[w]=1, ..., map[p]=1
Row 2: asdfghjkl  → map[a]=2, map[s]=2, ..., map[l]=2
Row 3: zxcvbnm     → map[z]=3, map[x]=3, ..., map[m]=3

Mapping complete:
a→2, b→3, c→3, d→2, e→1, f→2, g→2, h→2, i→1, j→2, k→2, l→2, 
m→3, n→3, o→1, p→1, q→1, r→1, s→2, t→1, u→1, v→3, w→1, x→3, 
y→1, z→3
```

**Step 2: Check "Alaska"**
```
Word: "Alaska"
Characters: A(uppercase), l, a, s, k, a
Convert to lowercase: a, l, a, s, k, a

Check mappings:
- a: map[a] = 2
- l: map[l] = 2
- a: map[a] = 2
- s: map[s] = 2
- k: map[k] = 2
- a: map[a] = 2

All characters map to row 2! ✓
Add "Alaska" to result
```

**Step 3: Check "Hello"**
```
Word: "Hello"
Characters: H, e, l, l, o
Convert to lowercase: h, e, l, l, o

Check mappings:
- h: map[h] = 2
- e: map[e] = 1  ← Different row!
- (Stop checking)

Characters from different rows! ✗
Don't add "Hello" to result
```

**Result:** ["Alaska"] ✓

---

## Code Full Solution

```cpp
class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        unordered_map<char, int> wordMap;      // Map char to row number
        vector<string> ans;                    // Result vector

        // Step 1: Build keyboard row mapping
        for(auto &c : "qwertyuiop") wordMap[c] = 1;  // Row 1
        for(auto &c : "asdfghjkl")  wordMap[c] = 2;  // Row 2
        for(auto &c : "zxcvbnm")    wordMap[c] = 3;  // Row 3

        // Step 2: Check each word
        for(auto &word : words) {
            int val = wordMap[tolower(word[0])];     // Row of first char
            bool add = true;                         // Assume valid
            
            // Check if all characters are in same row
            for(int i = 0; i < word.size(); i++) {
                if(val != wordMap[tolower(word[i])]) {
                    add = false;                     // Found different row
                    break;
                }
            }
            
            if(add) ans.push_back(word);             // Add if all same row
        }

        return ans;
    }
};
```

---

## Code Explanation

### Step 1: Build Keyboard Mapping

```cpp
unordered_map<char, int> wordMap;
for(auto &c : "qwertyuiop") wordMap[c] = 1;
for(auto &c : "asdfghjkl")  wordMap[c] = 2;
for(auto &c : "zxcvbnm")    wordMap[c] = 3;
```

**What it does:**
- Iterates through each keyboard row string
- Maps each character to its row number (1, 2, or 3)
- Uses `&c` to get reference to character in loop

**Example:**
```cpp
// First loop: "qwertyuiop"
for(auto &c : "qwertyuiop") wordMap[c] = 1;
// c iterates: 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'
// Each character maps to 1

// Result:
wordMap = {
    'q': 1, 'w': 1, 'e': 1, 'r': 1, 't': 1, 
    'y': 1, 'u': 1, 'i': 1, 'o': 1, 'p': 1,
    'a': 2, 's': 2, 'd': 2, 'f': 2, 'g': 2,
    'h': 2, 'j': 2, 'k': 2, 'l': 2,
    'z': 3, 'x': 3, 'c': 3, 'v': 3, 'b': 3,
    'n': 3, 'm': 3
}
```

---

### Step 2: Process Each Word

```cpp
for(auto &word : words) {
```

- Loop through each word in input vector
- `&word` for efficiency (reference, no copy)

---

### Get First Character's Row

```cpp
int val = wordMap[tolower(word[0])];
```

- **`word[0]`:** First character of word
- **`tolower(word[0])`:** Convert to lowercase for lookup
  - Handles uppercase letters (e.g., 'A' → 'a')
- **`wordMap[...]`:** Get row number of first character
- Store in `val` to compare all other characters

**Why first character?**
- All characters should be in the **same row as the first one**
- Set it as the reference point

**Example:**
```cpp
word = "Alaska"
word[0] = 'A'
tolower('A') = 'a'
wordMap['a'] = 2
val = 2
```

---

### Check All Characters

```cpp
bool add = true;
for(int i = 0; i < word.size(); i++) {
    if(val != wordMap[tolower(word[i])]) {
        add = false;
        break;
    }
}
```

- **`bool add = true`:** Assume word is valid initially
- **Loop through all characters:** Check each one
- **Compare:** `val != wordMap[tolower(word[i])]`
  - Get row of current character (with tolower for case-insensitivity)
  - Compare with reference row (`val`)
  - If different, mark as invalid
- **Break:** Stop checking once mismatch found (optimization)

**Example:**
```cpp
word = "Alaska", val = 2

i=0: 'A' → tolower→ 'a' → wordMap['a']=2, 2==2? YES ✓
i=1: 'l' → tolower→ 'l' → wordMap['l']=2, 2==2? YES ✓
i=2: 'a' → tolower→ 'a' → wordMap['a']=2, 2==2? YES ✓
i=3: 's' → tolower→ 's' → wordMap['s']=2, 2==2? YES ✓
i=4: 'k' → tolower→ 'k' → wordMap['k']=2, 2==2? YES ✓
i=5: 'a' → tolower→ 'a' → wordMap['a']=2, 2==2? YES ✓

Loop completes, add = true ✓
```

---

### Add Valid Words

```cpp
if(add) ans.push_back(word);
```

- If `add` is true (all characters in same row), add the word to result
- Otherwise, skip this word

---

## Complete Example Trace

### Input: ["Hello", "Alaska", "Bob"]

```
Build mapping:
wordMap = {'q':1, ..., 'p':1, 'a':2, ..., 'l':2, 'z':3, ..., 'm':3}

ans = []

Process "Hello":
  val = wordMap[tolower('H')] = wordMap['h'] = 2
  Check 'H': tolower→'h'→2, 2==2? YES
  Check 'e': tolower→'e'→1, 1==2? NO! add=false, break
  add is false, don't add to ans
  
Process "Alaska":
  val = wordMap[tolower('A')] = wordMap['a'] = 2
  Check 'A': tolower→'a'→2, 2==2? YES
  Check 'l': tolower→'l'→2, 2==2? YES
  Check 'a': tolower→'a'→2, 2==2? YES
  Check 's': tolower→'s'→2, 2==2? YES
  Check 'k': tolower→'k'→2, 2==2? YES
  Check 'a': tolower→'a'→2, 2==2? YES
  add is true, add "Alaska" to ans
  ans = ["Alaska"]

Process "Bob":
  val = wordMap[tolower('B')] = wordMap['b'] = 3
  Check 'B': tolower→'b'→3, 3==3? YES
  Check 'o': tolower→'o'→1, 1==3? NO! add=false, break
  add is false, don't add to ans

Return: ["Alaska"] ✓
```

---

## Edge Cases

### Case 1: Single Character Word
```
Input: ["a"]
val = wordMap['a'] = 2
Loop: i=0: 'a'→2, 2==2? YES
Output: ["a"] ✓
```

### Case 2: All Words Invalid
```
Input: ["Hello", "World"]
"Hello": h(2), e(1) → Different rows ✗
"World": w(1), o(1), r(1), l(2), d(2) → Multiple rows ✗
Output: [] (empty)
```

### Case 3: All Words Valid
```
Input: ["as", "df", "zx"]
"as": a(2), s(2) → Same row ✓
"df": d(2), f(2) → Same row ✓
"zx": z(3), x(3) → Same row ✓
Output: ["as", "df", "zx"]
```

### Case 4: Mixed Case
```
Input: ["QWERTY", "AsDF"]
"QWERTY": Q(1), W(1), E(1), R(1), T(1), Y(1) → All row 1 ✓
"AsDF": A(2), s(2), D(2), F(2) → All row 2 ✓
Output: ["QWERTY", "AsDF"] ✓
(tolower handles case conversion)
```

### Case 5: Empty Input
```
Input: []
No words to process
Output: [] (empty)
```

### Case 6: Repeated Characters
```
Input: ["aaa", "eee"]
"aaa": a(2), a(2), a(2) → Same row ✓
"eee": e(1), e(1), e(1) → Same row ✓
Output: ["aaa", "eee"]
```

---

## Why HashMap?

**HashMap approach advantages:**
- ✅ **Fast lookup:** O(1) per character check
- ✅ **Simple mapping:** Character → row number
- ✅ **Clear intent:** Easy to understand

**Alternative approaches:**

#### Approach 1: String Contains
```cpp
string row1 = "qwertyuiop";
string row2 = "asdfghjkl";
string row3 = "zxcvbnm";

for(auto &word : words) {
    string lower_word = "";
    for(char c : word) lower_word += tolower(c);
    
    if(row1.find(lower_word[0]) != string::npos) {
        bool valid = true;
        for(char c : lower_word) {
            if(row1.find(c) == string::npos) {
                valid = false;
                break;
            }
        }
        if(valid) ans.push_back(word);
    }
    // ... similar for row2, row3
}

Time: O(n*m) where n=words, m=avg word length
Space: O(m) for lower_word string
```

#### Approach 2: Set for Each Row
```cpp
unordered_set<char> row1, row2, row3;
for(char c : "qwertyuiop") row1.insert(c);
for(char c : "asdfghjkl") row2.insert(c);
for(char c : "zxcvbnm") row3.insert(c);

// Check if word matches any row
Time: O(n*m) similar to above
Space: O(26) = O(1)
```

**HashMap is cleanest!**

---

## Understanding tolower()

```cpp
tolower('A') → 'a'
tolower('a') → 'a'
tolower('Z') → 'z'
tolower('z') → 'z'
tolower('1') → '1' (non-letters unchanged)
```

- **Converts uppercase to lowercase**
- **Leaves lowercase unchanged**
- **Returns character code as int** (but implicitly cast to char)

**Why important?**
```
Keyboard mapping only has lowercase letters
tolower enables case-insensitive matching
'A' and 'a' both map to same row
```

---

## Key Insights

### Early Break Optimization

```cpp
for(int i = 0; i < word.size(); i++) {
    if(val != wordMap[tolower(word[i])]) {
        add = false;
        break;  // Stop immediately
    }
}
```

- **Break on first mismatch:** No need to check remaining characters
- **Saves time:** Especially for long words

**Example:**
```
word = "hello" (5 chars)
val = wordMap['h'] = 2

i=0: 'h'→2, match ✓
i=1: 'e'→1, mismatch! break

Checked 2 chars instead of 5 (60% faster!)
```

---

### Reference vs Copy in Loops

```cpp
for(auto &word : words)      // Reference (efficient)
for(auto word : words)       // Copy (wasteful)
```

- **`&word`:** Points to original string (no copy)
- **`word`:** Creates copy of entire string
- For large strings, reference is **much faster**

```cpp
// With reference:
vector<string> words = {"Hello", "Alaska", "Bob"};
for(auto &word : words) {
    // word is reference to "Hello", then "Alaska", etc.
    // No copying happens
}

// Without reference (wasteful):
for(auto word : words) {
    // word is a copy of "Hello", then copy of "Alaska"
    // Creates 3 copies (memory + time waste)
}
```

---

### Why Store First Row Value?

```cpp
int val = wordMap[tolower(word[0])];
```

Instead of:
```cpp
for(int i = 0; i < word.size(); i++) {
    if(wordMap[tolower(word[i])] != wordMap[tolower(word[0])]) {
        // Wrong: compares word[i] with word[0] each time
    }
}
```

**Advantages of storing in `val`:**
- ✅ Cleaner comparison
- ✅ Avoid repeated lookups (though minor)
- ✅ More readable intent

---

## Time Complexity

**Building mapping:**
- O(26) = O(1) constant
- Three short loops over keyboard rows

**Processing words:**
- For each word, check all characters
- O(n * m) where n = number of words, m = average word length

**Overall: O(n * m)** where n = words, m = avg length

---

## Space Complexity

- **Mapping:** O(26) = O(1) (26 letters max)
- **Result:** O(k) where k = number of valid words
- **Other:** O(1) for variables

**Overall: O(k)** where k = output size

---

## Key Takeaway

**HashMap mapping transforms character classification into instant lookup.** By pre-mapping each letter to its keyboard row, checking word validity becomes a simple loop of comparisons. Elegant, efficient, and easy to understand! ⌨️

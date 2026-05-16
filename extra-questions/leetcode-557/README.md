# Reverse Words in a String III

**Problem Link:** https://leetcode.com/problems/reverse-words-in-a-string-iii/

## What is this Problem?

We need to **reverse each word in a string individually**, while keeping the words in the same order.

**Key Points:**
- Reverse each word character by character
- Words stay in the same positions
- Spaces remain unchanged
- Single spaces between words in the input

**Example:**
```
Input: "Hello World"
Output: "olleH dlroW"

Words: ["Hello", "World"]
Reversed: ["olleH", "dlroW"]
Result: "olleH dlroW"
```

```
Input: "The quick brown fox jumps over the lazy dog"
Output: "ehT kciuq nworb xof spmuj revo eht yzal god"

Each word reversed individually:
"The" → "ehT"
"quick" → "kciuq"
"brown" → "nworb"
"fox" → "xof"
"jumps" → "spmuj"
"over" → "revo"
"the" → "eht"
"lazy" → "yzal"
"dog" → "god"

Result: "ehT kciuq nworb xof spmuj revo eht yzal god"
```

---

## The Problem Explained

Imagine you have a sentence and you want to scramble each word but keep their positions:

**Original:** "I love coding"

**Want:** "I" stays first, "love" reversed becomes "evol", "coding" reversed becomes "gnidoc"

**Result:** "I evol gnidoc"

Think of it as:
1. **Extract each word** from the string
2. **Reverse each word** independently
3. **Join them back** with spaces

---

## HOOK TO REMEMBER FOREVER

### **"EXTRACT, REVERSE EACH, RECONSTRUCT"**

Every time you see this problem:
- ✅ **Extract words** from the string (split by spaces)
- ✅ **Reverse each word** independently
- ✅ **Join them back** with spaces
- ✅ Two approaches:
  - Stream-based: `istringstream` (elegant, handles multiple spaces automatically)
  - Two-pointer: Reverse each word in-place (space-efficient)

**Remember: Words move, characters within words get scrambled!** 🔤

---

## How It Works Step By Step

### Example: Process `"Hello World"`

**Approach 1: Stream (Our Solution)**

**Setup:**
```
Input: "Hello World"
Create istringstream from input
```

**Step 1: Extract first word**
```
iss >> word → word = "Hello"
Reverse word → word = "olleH"
ans += "olleH" + " " → ans = "olleH "
```

**Step 2: Extract second word**
```
iss >> word → word = "World"
Reverse word → word = "dlroW"
ans += "dlroW" + " " → ans = "olleH dlroW "
```

**Step 3: Remove trailing space**
```
ans.pop_back() → ans = "olleH dlroW"
```

**Result:** `"olleH dlroW"` ✓

---

### Example: Process `"The quick brown fox"`

**Step 1:**
```
word = "The" → reverse to "ehT"
ans = "ehT "
```

**Step 2:**
```
word = "quick" → reverse to "kciuq"
ans = "ehT kciuq "
```

**Step 3:**
```
word = "brown" → reverse to "nworb"
ans = "ehT kciuq nworb "
```

**Step 4:**
```
word = "fox" → reverse to "xof"
ans = "ehT kciuq nworb xof "
```

**Step 5:**
```
pop_back() → remove trailing space
ans = "ehT kciuq nworb xof"
```

**Result:** `"ehT kciuq nworb xof"` ✓

---

## Code Full Solution

```cpp
class Solution {
public:
    string reverseWords(string s) {
        istringstream iss(s);                   // Create input string stream
        string ans;                             // Result string
        string word;                            // Current word
        
        while(iss >> word) {                    // Extract each word
            reverse(word.begin(), word.end());  // Reverse the word
            ans += word + " ";                  // Add reversed word + space
        }
        
        ans.pop_back();                         // Remove trailing space
        return ans;                             // Return result
    }
};
```

---

## Code Explanation

### Setup

```cpp
istringstream iss(s);
string ans;
string word;
```

- **`istringstream iss(s)`:** 
  - Create an input string stream from string `s`
  - Allows us to extract words word-by-word
  - Automatically handles whitespace
  
- **`ans`:** Result string (accumulator)
  
- **`word`:** Temporary variable to hold each word

**Why istringstream?**
```
Regular approach would need manual parsing:
- Find spaces
- Extract substrings
- Complex logic

istringstream handles all this! ✨
```

---

### Main Loop

```cpp
while(iss >> word) {
```

- **`iss >> word`:** Extract next word from stream
  - Automatically skips whitespace
  - Returns true if word extracted, false if stream empty
  - Loop continues until all words extracted

**Example:**
```cpp
istringstream iss("Hello World Test");
string word;

iss >> word;  // word = "Hello", returns true
iss >> word;  // word = "World", returns true
iss >> word;  // word = "Test", returns true
iss >> word;  // returns false (stream exhausted), loop exits
```

---

### Reverse Each Word

```cpp
reverse(word.begin(), word.end());
```

- **`reverse()`:** Built-in function in C++
- **`word.begin()`:** Iterator to start of string
- **`word.end()`:** Iterator to end of string
- **Effect:** Reverses the string in-place

**Example:**
```cpp
string word = "Hello";
reverse(word.begin(), word.end());
// word is now "olleH"
```

---

### Build Result String

```cpp
ans += word + " ";
```

- **`ans += x`:** Append to string `ans`
- **`word + " "`:** Concatenate reversed word with space
- Each iteration adds: `reversed_word + " "`

**Trace:**
```
Iteration 1: word = "olleH", ans = "" → ans = "olleH "
Iteration 2: word = "dlroW", ans = "olleH " → ans = "olleH dlroW "
Iteration 3: No more words, exit loop
```

---

### Remove Trailing Space

```cpp
ans.pop_back();
```

- **`pop_back()`:** Remove the last character
- Last character is the space we added after final word
- Result has correct spacing

**Why do this?**
```
After loop: ans = "olleH dlroW "
                                 ↑ unwanted space

pop_back(): ans = "olleH dlroW"
                               ✓ correct!
```

---

## Complete Example Trace

```
Input: "Hello World"

Initialization:
  iss = input stream of "Hello World"
  ans = ""
  word = ""

Iteration 1:
  iss >> word → word = "Hello"
  reverse(word.begin(), word.end()) → word = "olleH"
  ans += "olleH" + " " → ans = "olleH "

Iteration 2:
  iss >> word → word = "World"
  reverse(word.begin(), word.end()) → word = "dlroW"
  ans += "dlroW" + " " → ans = "olleH dlroW "

Check: iss >> word → false (no more words), exit loop

Finalization:
  ans.pop_back() → ans = "olleH dlroW"

Return: "olleH dlroW" ✓
```

---

## Alternative Approach: Two-Pointer In-Place

```cpp
class Solution {
public:
    string reverseWords(string s) {
        int n = s.size();
        int start = 0;
        
        // Find each word and reverse it
        for(int end = 0; end <= n; end++) {
            // If we hit a space or end of string
            if(end == n || s[end] == ' ') {
                // Reverse word from start to end-1
                reverse(s.begin() + start, s.begin() + end);
                start = end + 1;  // Next word starts after space
            }
        }
        return s;
    }
};
```

**How it works:**
```
Input: "Hello World"
Index: 0123456789...

Word 1: start=0, end=5 (space position)
  Reverse s[0..4] → "olleH World"
  start = 6 (after space)

Word 2: start=6, end=11 (end of string)
  Reverse s[6..10] → "olleH dlroW"
  start = 12 (past end)

Output: "olleH dlroW" ✓
```

**Comparison:**
```
istringstream approach:
  ✓ Clean, easy to read
  ✓ Handles spacing automatically
  ✗ O(n) extra space (copy words)
  
Two-pointer approach:
  ✓ O(1) extra space
  ✓ In-place modification
  ✗ Slightly more complex logic
```

---

## Edge Cases

### Case 1: Single Word
```
Input: "Hello"
Extract: "Hello"
Reverse: "olleH"
Output: "olleH"
```

### Case 2: Single Character Words
```
Input: "a b c"
"a" → "a" (reversing single char -> same)
"b" → "b"
"c" → "c"
Output: "a b c"
```

### Case 3: Already Reversed
```
Input: "olleH dlroW"
"olleH" → "Hello"
"dlroW" → "World"
Output: "Hello World"
```

### Case 4: Long Words
```
Input: "programming is fun"
"programming" → "gnimmargorP"
"is" → "si"
"fun" → "nuf"
Output: "gnimmargorP si nuf"
```

### Case 5: Multiple Spaces (istringstream)
```
Input: "Hello  World" (two spaces)
istringstream automatically handles multiple spaces!
"Hello" → "olleH"
"World" → "dlroW"
Output: "olleH dlroW"
(Note: istringstream treats consecutive spaces as single separator)
```

---

## Why istringstream?

**istringstream advantages:**
- ✅ **Automatic word extraction:** No manual parsing needed
- ✅ **Whitespace handling:** Automatically skips multiple spaces
- ✅ **Clean code:** More readable than manual index tracking
- ✅ **Safe:** No index out-of-bounds errors

**When to use alternatives:**
- Need in-place modification → Use two-pointer approach
- Memory is extremely limited → Use manual index tracking
- Performance-critical → Two-pointer (minimal overhead)

---

## Key Insights

### `istringstream` vs Manual Parsing

**istringstream (our solution):**
```cpp
istringstream iss("The quick brown");
string word;
while(iss >> word) {
    // Process word
}
// Clean, 4 lines!
```

**Manual parsing:**
```cpp
int start = 0;
for(int i = 0; i <= s.size(); i++) {
    if(i == s.size() || s[i] == ' ') {
        string word = s.substr(start, i - start);
        // Process word
        start = i + 1;
    }
}
// Complex, error-prone
```

### `reverse()` Function

```cpp
reverse(word.begin(), word.end());     // Reverse entire string
reverse(s.begin() + 2, s.begin() + 5); // Reverse range
```

- **Works on any container** (string, vector, etc.)
- **In-place modification** (doesn't create copy)
- **O(n) time** where n = length of range

### Why Build String This Way?

```cpp
// Approach 1: Using += (our solution)
ans += word + " ";

// Approach 2: Using push_back (character by character)
for(char c : word) ans.push_back(c);
ans.push_back(' ');

// Approach 3: Using append
ans.append(word);
ans.append(" ");
```

All work, but `+=` is **most idiomatic** in C++.

---

## Time Complexity

- **O(n)** where n = length of input string
- Each character is:
  - Extracted once: O(1) per char
  - Reversed once: O(1) per char
  - Added to result: O(1) per char (amortized)
- Total: O(n)

```
istringstream: O(n) scanning
reverse(): O(n) for all words combined
Building ans: O(n)
Total: O(n) ✓
```

---

## Space Complexity

- **O(n)** for the output string
- **O(n)** for istringstream buffer (internal)
- **O(1)** additional space for word variables

Overall: **O(n)** for output space.

**Alternative (two-pointer):** O(1) additional space ✓

---

## Key Takeaway

**istringstream makes word-by-word processing effortless.** Instead of manually tracking spaces and indices, let the stream handle parsing while you focus on reversing logic. When simplicity matters, streams shine! ✨

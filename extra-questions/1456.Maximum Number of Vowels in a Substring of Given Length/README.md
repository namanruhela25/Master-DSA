# Maximum Vowels in a Substring of Given Length

## Problem Link
🔗 [LeetCode 1456 — Maximum Number of Vowels in a Substring of Given Length](https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/)

---

## What is this Problem?

Given a string `s` and an integer `k`, return the **maximum number of vowels** in any substring of length **exactly `k`**.

```
s = "abciiidef", k = 3
Output: 3   → substring "iii" has 3 vowels

s = "aeiou", k = 2
Output: 2   → any window of size 2 has 2 vowels

s = "leetcode", k = 3
Output: 2   → "lee", "eet", "etc"... max is 2 ("lee"→1, "eet"→2)
```

---

## The Problem Explained

Think of it like a **sliding window camera frame of fixed width k** scanning across the string:

```
s = "abciiidef", k = 3

Frame 1: [a b c] → 1 vowel (a)
Frame 2: [b c i] → 1 vowel (i)
Frame 3: [c i i] → 2 vowels
Frame 4: [i i i] → 3 vowels ← MAXIMUM
Frame 5: [i i d] → 2 vowels
Frame 6: [i d e] → 2 vowels
Frame 7: [d e f] → 1 vowel (e)

Answer: 3
```

Instead of recomputing vowels for each frame from scratch (O(n×k)), we **slide the window**: when we move right, we add the new character on the right and drop the character that left on the left. O(n) total.

---

## HOOK TO REMEMBER FOREVER

**"FIXED SIZE WINDOW. EXPAND RIGHT. WHEN WINDOW = k, UPDATE MAX, DROP LEFT, SHRINK."**

- ✅ `j` = right pointer, `i` = left pointer
- ✅ Add `s[j]` to window: if vowel, `count++`
- ✅ When window reaches size k (`j - i + 1 == k`):
  - Update `maxVal`
  - If `s[i]` is a vowel, `count--` (dropping it)
  - `i++` (shrink from left)
- ✅ `j++` every iteration
- ✅ O(n) time, O(1) space

---

## How It Works Step By Step

### Example: `s = "abciiidef", k = 3`

```
i=0, j=0, count=0, maxVal=0

j=0: s[j]='a' vowel → count=1. window size=1≠3. j++
j=1: s[j]='b' → count=1. size=2≠3. j++
j=2: s[j]='c' → count=1. size=3==k!
  maxVal=max(0,1)=1. s[i='a'] is vowel → count=0. i=1. j++

j=3: s[j]='i' vowel → count=1. size=3==k!
  maxVal=max(1,1)=1. s[i='b'] not vowel → count stays 1. i=2. j++

j=4: s[j]='i' vowel → count=2. size=3==k!
  maxVal=max(1,2)=2. s[i='c'] not vowel → count=2. i=3. j++

j=5: s[j]='i' vowel → count=3. size=3==k!
  maxVal=max(2,3)=3. s[i='i'] vowel → count=2. i=4. j++

j=6: s[j]='d' → count=2. size=3==k!
  maxVal=max(3,2)=3. s[i='i'] vowel → count=1. i=5. j++

j=7: s[j]='e' vowel → count=2. size=3==k!
  maxVal=3. s[i='i'] vowel → count=1. i=6. j++

j=8: s[j]='f' → count=1. size=3==k!
  maxVal=3. s[i='d'] not vowel → count=1. i=7. j++

j=9: j==n → exit

Return 3 ✓
```

### Visual — Sliding Window

```
s:  a  b  c  i  i  i  d  e  f
    0  1  2  3  4  5  6  7  8

[a  b  c]              count=1
   [b  c  i]           count=1
      [c  i  i]        count=2
         [i  i  i]     count=3  ← MAX
            [i  i  d]  count=2
               [i  d  e] count=2
                  [d  e  f] count=1
```

---

## Code Full Solution

```cpp
class Solution {
public:
    bool isVowel(char ch) {
        return ch=='a' || ch=='e' || ch=='i' || ch=='o' || ch=='u';
    }

    int maxVowels(string s, int k) {
        int i = 0, j = 0;
        int maxVal = 0, count = 0;
        int n = s.size();

        while (j < n) {
            if (isVowel(s[j])) count++;

            if (j - i + 1 == k) {
                maxVal = max(maxVal, count);
                if (isVowel(s[i])) count--;
                i++;
            }
            j++;
        }
        return maxVal;
    }
};
```

---

## Code Explanation

### Add Right Element

```cpp
if (isVowel(s[j])) count++;
```

Every iteration, `j` moves right and we include `s[j]` in the window. If it's a vowel, increment count.

---

### Window Reached Size k

```cpp
if (j - i + 1 == k) {
    maxVal = max(maxVal, count);
    if (isVowel(s[i])) count--;
    i++;
}
```

`j - i + 1` = current window size. When it hits exactly `k`:
1. **Record** the vowel count for this window
2. **Remove** the leftmost character — if it was a vowel, decrement count
3. **Slide** left pointer forward

**Why this order?** We update `maxVal` BEFORE removing `s[i]` — because `count` currently reflects the full window of size k. Then we drop `s[i]` to prepare the count for the next window.

---

## Edge Cases

### Case 1: All Vowels

```
s="aeiou", k=2 → every window has 2 vowels. Output: 2 ✓
```

### Case 2: No Vowels

```
s="bcd", k=2 → count stays 0. Output: 0 ✓
```

### Case 3: k = s.length()

```
s="abcd", k=4 → only one window: the whole string. Output: 1 (just 'a') ✓
```

### Case 4: k = 1

```
s="aeiou", k=1 → each single character is a window.
Best window = any vowel. Output: 1 ✓
```

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(n) — each character added and removed at most once |
| Space | O(1) — only a few integers |

---

## Key Insights

### Why Not Recompute Each Window?

```
Brute force: for each of n-k+1 windows, count vowels in O(k) → O(n×k)

Sliding window: when window slides right by 1:
  Add 1 character (check if vowel): O(1)
  Remove 1 character (check if vowel): O(1)

We maintain a LIVE COUNT that updates in O(1) per step → O(n) total.

This is the core sliding window technique:
  What changes when window slides = only the ONE element entering
  and the ONE element leaving. Everything else stays the same.
```

### Fixed vs Variable Window

```
This is a FIXED-SIZE window (size always = k).
  → Window never exceeds k, never shrinks below k (once started).
  → Trigger exactly when j-i+1 == k.

Compare to VARIABLE-SIZE windows (like "longest substring without repeating chars"):
  → Window grows until a condition breaks, then shrinks.
  → Different trigger logic.

Recognizing which type you have is the first step in any sliding window problem.
```

---

## References

- 🔗 [LeetCode 1456 — Maximum Number of Vowels in a Substring of Given Length](https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/)
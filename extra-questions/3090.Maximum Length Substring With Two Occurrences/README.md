# Maximum Length Substring With Two Occurrences

## Problem Link
🔗 [LeetCode 3090 — Maximum Length Substring With Two Occurrences](https://leetcode.com/problems/maximum-length-substring-with-two-occurrences/)

---

## What is this Problem?

Given a string `s`, find the length of the **longest substring** where **every character appears at most twice**.

```
s = "bcbbbcba"
Output: 4  → "bcbb"? No wait, let's check "bcbbbcba":
  Substring "bcbbbc" has 'b' appearing 4 times — invalid.
  The answer substring is "bcbb"... actually the correct
  longest valid substring here is "bcbbbcba" checked piece by piece
  (see trace below for the real walkthrough)

s = "aaaa"
Output: 2  → "aa" (can't have 3+ of the same char)
```

---

## The Problem Explained

Think of it like a **variable-size sliding window** where you're allowed **at most 2 copies** of any character inside the window:

```
Expand the window (move r right) — add characters.
If any character's count exceeds 2 → shrink from the left
  until that character's count drops back to 2.
Track the maximum window size seen.
```

This is the classic "at most K occurrences" sliding window pattern.

---

## HOOK TO REMEMBER FOREVER

**"EXPAND RIGHT, ADD TO FREQUENCY. IF ANY CHAR EXCEEDS 2, SHRINK LEFT UNTIL VALID. TRACK MAX WINDOW."**

- ✅ `freq[26]` tracks character counts inside the current window `[l, r]`
- ✅ Expand: add `s[r]` to freq, increment `r`
- ✅ Shrink: WHILE the just-added character's count > 2, remove `s[l]` and move `l` forward
- ✅ After shrinking (window is valid again), update `res = max(res, r-l+1)`
- ✅ O(n) time, O(1) space (fixed 26-size array)

---

## How It Works Step By Step

### Example: `s = "bcbbbcba"`

```
l=0, r=0, freq=[0]*26, res=0

r=0: s[r]='b'. freq[b]=1. 1>2? NO. res=max(0,0-0+1)=1. r=1
r=1: s[r]='c'. freq[c]=1. 1>2? NO. res=max(1,1-0+1)=2. r=2
r=2: s[r]='b'. freq[b]=2. 2>2? NO. res=max(2,2-0+1)=3. r=3
r=3: s[r]='b'. freq[b]=3. 3>2? YES!
    shrink: freq[s[0]='b']--→2. l=1. freq[b] now 2, check again: 2>2? NO, stop shrinking.
    res=max(3,3-1+1)=3. r=4
r=4: s[r]='b'. freq[b]=3. 3>2? YES!
    shrink: freq[s[1]='c']--→0. l=2. freq[b] still 3>2? YES, keep shrinking!
    shrink: freq[s[2]='b']--→2. l=3. freq[b] now 2, 2>2? NO, stop.
    res=max(3,4-3+1)=3. r=5
r=5: s[r]='c'. freq[c]=1. 1>2? NO. res=max(3,5-3+1)=3. r=6
r=6: s[r]='b'. freq[b]=3. 3>2? YES!
    shrink: freq[s[3]='b']--→2. l=4. 2>2? NO, stop.
    res=max(3,6-4+1)=3. r=7
r=7: s[r]='a'. freq[a]=1. 1>2? NO. res=max(3,7-4+1)=4. r=8

r=8=n → STOP

Return 4 ✓
```

### Visual — Window Growing and Shrinking

```
s:  b  c  b  b  b  c  b  a
    0  1  2  3  4  5  6  7

Window at r=2: [b c b]         size=3, valid (b:2, c:1)
Window at r=3: [c b b] (shrunk) size=3, valid (b:2, c... wait l moved)
Window at r=4: [b b]  (shrunk more) size=2
Window at r=7: [b c b a]       size=4 ← MAX
```

---

## Code Full Solution

```cpp
class Solution {
public:
    int maximumLengthSubstring(string s) {
        int l = 0, r = 0;
        vector<int> freq(26, 0);
        int n = s.size();
        int res = 0;

        while (r < n) {
            freq[s[r] - 'a']++;

            while (freq[s[r] - 'a'] > 2) {
                freq[s[l] - 'a']--;
                l++;
            }

            res = max(res, r - l + 1);
            r++;
        }
        return res;
    }
};
```

---

## Code Explanation

### Add Current Character

```cpp
freq[s[r] - 'a']++;
```

Every step, include `s[r]` in the window and update its frequency.

---

### Shrink While Invalid

```cpp
while (freq[s[r] - 'a'] > 2) {
    freq[s[l] - 'a']--;
    l++;
}
```

**Why check `freq[s[r]-'a']` (not some other character)?**

```
Only the character we JUST ADDED (s[r]) can be the one that
just crossed the threshold — every other character's count
was already valid (≤2) before this step, since we always
restore validity before moving on.

So we only need to check IF s[r]'s count exceeds 2, and
shrink until IT specifically drops back to 2 or below.
```

**Why `while` and not `if`?**

```
Shrinking might need MULTIPLE steps. Removing s[l] once might
remove a DIFFERENT character (not s[r]), so s[r]'s count could
still be > 2 after one shrink. We keep shrinking until
s[r]'s specific count is back to ≤2.

Example from trace: at r=4, we had to shrink TWICE — once
removed a 'c' (didn't help 'b's count), then removed a 'b'
(finally fixed it).
```

---

### Update Result

```cpp
res = max(res, r - l + 1);
```

After ensuring the window is valid (every character ≤ 2 occurrences), record its size if it's the best seen so far.

---

## Edge Cases

### Case 1: All Same Character

```
s="aaaa"
r=0: freq[a]=1, valid, res=1
r=1: freq[a]=2, valid, res=2
r=2: freq[a]=3, invalid! shrink: freq[a]=2,l=1. res=max(2,2-1+1)=2
r=3: freq[a]=3, invalid! shrink: freq[a]=2,l=2. res=max(2,3-2+1)=2

Return 2 ✓
```

### Case 2: All Unique Characters

```
s="abcdef" → no character ever exceeds 2. Window grows to full length.
Return 6 ✓
```

### Case 3: Single Character

```
s="a" → freq[a]=1, valid. res=1. Return 1 ✓
```

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(n) — `l` and `r` each move at most n times total (amortized) |
| Space | O(26) = O(1) — fixed-size frequency array |

---

## Key Insight — "At Most K" Sliding Window Template

```cpp
while (r < n) {
    // add s[r] to window state
    while (/* window invalid */) {
        // remove s[l] from window state
        l++;
    }
    res = max(res, r - l + 1);  // window is now guaranteed valid
    r++;
}
```

This exact template solves:
- Longest substring with at most K distinct characters
- Longest substring where each character appears at most K times (this problem, K=2)
- Longest subarray with at most K zeros, etc.

**The pattern:** expand right unconditionally, shrink left only when a violation occurs, and the window is always valid right before you record `res`.

---

## References

- 🔗 [LeetCode 3090 — Maximum Length Substring With Two Occurrences](https://leetcode.com/problems/maximum-length-substring-with-two-occurrences/)
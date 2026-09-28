# Maximum Nesting Depth of Parentheses

## Problem Link
🔗 [LeetCode 1614 — Maximum Nesting Depth of the Parentheses](https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/)

---

## What is this Problem?

Given a valid parentheses string `s`, return the **maximum nesting depth** — how deeply the parentheses are nested at any point.

```
s = "(1+(2*3)+((8)/4))+1"
Output: 3   → "(( (8) ))" has depth 3

s = "(1)+((2))+(((3)))"
Output: 3   → "((( 3 )))" has depth 3

s = "()()()()()"
Output: 1   → no nesting, just sequential pairs
```

---

## The Idea

```
Think of a counter that tracks how many brackets are currently open.
It goes up on '(' and down on ')'.

Its MAXIMUM value during the scan = the deepest nesting.

s = "(1+(2*3)+((8)/4))+1"

( → cnt=1
( → cnt=2
) → ans=max(ans,2)=2. cnt=1
( → cnt=2
( → cnt=3
) → ans=max(ans,3)=3. cnt=2
) → ans=max(ans,2)=3. cnt=1
) → ans=max(ans,1)=3. cnt=0

Answer: 3 ✓
```

---

## HOOK TO REMEMBER FOREVER

**"COUNT OPEN BRACKETS. PEAK COUNT = MAX DEPTH."**

- ✅ `cnt++` on `(`
- ✅ Record `ans = max(ans, cnt)` BEFORE or at `)`
- ✅ `cnt--` on `)`

> ⚠️ **Order matters:** In this code, `ans` is updated BEFORE `cnt--` (when `)` is seen, we snapshot the current depth first). That's correct — at the moment of `)`, you're still at that depth.

---

## Code Full Solution

```cpp
class Solution {
public:
    int maxDepth(string s) {
        int cnt = 0, ans = 0;

        for (auto &el : s) {
            if (el == '(') {
                cnt++;
            } else if (el == ')') {
                ans = max(ans, cnt);  // snapshot before decrement
                cnt--;
            }
        }
        return ans;
    }
};
```

---

## Why Update `ans` on `)` and not `(`?

Both work — the depth is the same at the matching `(` and just before its `)`. This code snapshots on `)` because at that moment `cnt` reflects the full depth INCLUDING the bracket being closed.

**Alternative (update on `(`):**
```cpp
if (el == '(') {
    cnt++;
    ans = max(ans, cnt);
} else if (el == ')') {
    cnt--;
}
```

Both return the same answer.

---

## Example Traces

### `s="()(())"`

```
'(' → cnt=1
')' → ans=1. cnt=0
'(' → cnt=1
'(' → cnt=2
')' → ans=max(1,2)=2. cnt=1
')' → ans=max(2,1)=2. cnt=0

Return 2 ✓  (the "(())" part has depth 2)
```

### `s="(((())))"` (4 levels deep)

```
( cnt=1, ( cnt=2, ( cnt=3, ( cnt=4,
) ans=4 cnt=3, ) ans=4 cnt=2, ) ans=4 cnt=1, ) ans=4 cnt=0

Return 4 ✓
```

### `s="()"`

```
( cnt=1
) ans=1. cnt=0
Return 1 ✓
```

---

## Edge Cases

### No Parentheses

```
s="abc" → neither branch runs. Return 0 ✓
```

### All Sequential

```
s="()()()" → cnt never exceeds 1. Return 1 ✓
```

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(n) — single pass |
| Space | O(1) |

---

## References

- 🔗 [LeetCode 1614 — Maximum Nesting Depth of the Parentheses](https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/)
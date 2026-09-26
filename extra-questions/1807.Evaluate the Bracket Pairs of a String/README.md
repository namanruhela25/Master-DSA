# Evaluate the Bracket Pairs of a String

## Problem Link
🔗 [LeetCode 1807 — Evaluate the Bracket Pairs of a String](https://leetcode.com/problems/evaluate-the-bracket-pairs-of-a-string/)

---

## What is this Problem?

Given a string `s` with `(key)` bracket pairs and a `knowledge` list of `[key, value]` pairs — replace every `(key)` with its value. Unknown keys become `"?"`.

```
s = "(name)is(age)yearsold"
knowledge = [["name","bob"],["age","two"]]
Output: "bobistwoyearsold"

s = "hi(name)"
knowledge = []
Output: "hi?"
```

---

## The Idea

```
Walk through s one character at a time:
  Normal char → append directly
  '(' found   → find matching ')', extract key,
                look up in map, append value or "?"
                jump i to position of ')'
```

Pre-load knowledge into a hashmap for O(1) lookup per key.

---

## Code Full Solution

```cpp
class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mpp;
        for (auto el : knowledge) mpp[el[0]] = el[1];

        string ans;
        int n = s.size();

        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                int j = s.find(')', i + 1);
                string key = s.substr(i + 1, j - i - 1);
                ans += mpp.count(key) ? mpp[key] : "?";
                i = j;   // jump i to ')', then i++ moves past it
            } else {
                ans += s[i];
            }
        }
        return ans;
    }
};
```

---

## Code Explanation

### `s.find(')', i+1)` — Find Closing Bracket

```
Starts searching from i+1 (just after the '(').
Keys contain no brackets, so the FIRST ')' found is
always the matching one. Returns index j.
```

### `s.substr(i+1, j-i-1)` — Extract Key

```
s = "...(  k  e  y  )..."
         i  i+1      j

start  = i+1        (skip the '(')
length = j - i - 1  (chars between '(' and ')')

Example: i=3, j=7 → substr(4, 3) = "key" ✓
```

### `i = j` — Skip Past the Bracket Pair

```
After processing (key), set i = j (the ')' position).
The for loop's i++ then moves i to j+1 — the character
right after ')'. Correctly skips the entire (key) block.
```

---

## Example Trace

### `s="(name)is(age)yearsold"`

```
mpp = {name:bob, age:two}
ans = ""

i=0: '(' → j=5. key="name". ans+="bob". i=5.
i=6: 'i' → ans="bobi"
i=7: 's' → ans="bobis"
i=8: '(' → j=12. key="age". ans+="two". i=12.
i=13: 'y' → ans="bobistowy"... (continuing "yearsold")

Final: "bobistwoyearsold" ✓
```

---

## Edge Cases

### Key Not Found → `"?"`

```
s="(x)", knowledge=[]
mpp empty. mpp.count("x")=0 → append "?".
Output: "?" ✓
```

### No Bracket Pairs

```
s="hello", knowledge=[["a","b"]]
All chars are regular → ans="hello" ✓
```

### Empty String

```
s="", loop doesn't run. Return "" ✓
```

### Adjacent Bracket Pairs

```
s="(a)(b)", knowledge=[["a","x"],["b","y"]]
i=0: key="a" → ans="x". i=2.
i=3: key="b" → ans="xy". i=5.
Output: "xy" ✓
```

---

## Time and Space Complexity

| | Value |
|---|---|
| Build map | O(k) — k = knowledge size |
| Main loop | O(n) — each character visited once |
| `s.find` per bracket | O(n) worst case, but total work across all brackets is O(n) |
| **Total** | **O(n + k)** |
| Space | O(k) for the map |

---

## Key Insight

```
Why not use a stack to match brackets?

The problem GUARANTEES keys contain only lowercase letters
(no nested brackets). So the first ')' after any '(' is
ALWAYS its correct match. s.find(')', i+1) is safe and clean.

If the problem allowed nested brackets, you'd need a stack.
Here, the single-scan with find is sufficient and simpler.
```

---

## References

- 🔗 [LeetCode 1807 — Evaluate the Bracket Pairs of a String](https://leetcode.com/problems/evaluate-the-bracket-pairs-of-a-string/)
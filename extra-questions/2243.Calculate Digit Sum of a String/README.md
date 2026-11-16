# Calculate Digit Sum of a String

## Problem Link
🔗 [LeetCode 2243 — Calculate Digit Sum of a String](https://leetcode.com/problems/calculate-digit-sum-of-a-string/)

---

## What is this Problem?

Given a digit string `s` and integer `k`, repeatedly apply this transformation until `s.length() <= k`:
- Split `s` into groups of `k` consecutive characters (last group may be shorter)
- Replace each group with the **sum of its digits** (as a string)

Return the final string.

```
s = "11111222223", k = 3

Round 1: ["111", "112", "222", "23"]
  → ["3", "4", "6", "5"]  → s = "3465"

Round 2: s.size()=4 > k=3
  ["346", "5"] → ["13", "5"] → s = "135"

Round 3: s.size()=3 == k=3 → STOP

Output: "135"
```

---

## The Idea

```
Simulate exactly as described:
  While s is longer than k, apply one round of group-sum compression.
  Each round, the string gets SHORTER (sums replace multi-digit groups).
  Eventually length ≤ k and we stop.
```

---

## Code Full Solution

```cpp
class Solution {
public:
    string digitSum(string s, int k) {
        while (s.size() > k) {
            string str = "";
            for (int i = 0; i < s.size(); i += k) {
                int sum = 0;
                for (int j = i; j < s.size() && j < i + k; j++) {
                    sum += (s[j] - '0');
                }
                str += to_string(sum);
            }
            s = str;
        }
        return s;
    }
};
```

---

## Code Explanation

### Outer `while` — Repeat Until Done

```cpp
while (s.size() > k)
```

Keep compressing as long as the string is longer than `k`. Once `s.size() <= k`, the string is already a valid final answer.

### Outer `for` — Walk Through Groups

```cpp
for (int i = 0; i < s.size(); i += k)
```

`i` jumps by `k` each iteration, processing one group per step.

### Inner `for` — Sum One Group

```cpp
for (int j = i; j < s.size() && j < i + k; j++)
    sum += (s[j] - '0');
```

`j < s.size()` handles the last group being shorter than `k`.  
`j < i + k` caps the group at exactly `k` characters.

### Append Sum

```cpp
str += to_string(sum);
```

The sum of a group of `k` single digits can be at most `9k`. For `k=100`, max sum is 900 — still a 3-digit number. `to_string` handles any size automatically.

---

## Full Trace: `s="11111222223", k=3`

```
Round 1: s.size()=11 > 3

Groups: i=0→"111"=3, i=3→"112"=4, i=6→"222"=6, i=9→"23"=5
str = "3465". s = "3465"

Round 2: s.size()=4 > 3

Groups: i=0→"346"=13, i=3→"5"=5
str = "135". s = "135"

Round 3: s.size()=3 == k=3 → EXIT while

Return "135" ✓
```

---

## Example Traces

### Already Short Enough

```
s="1", k=1 → s.size()=1, not > 1 → return "1" immediately ✓
```

### Single Round

```
s="1234", k=4 → s.size()=4, not > 4 → return "1234" immediately ✓
```

### Group Sum Becomes Multi-Digit

```
s="99999", k=2

Round 1: ["99","99","9"] → ["18","18","9"] → s="18189"
Round 2: ["18","18","9"] → ["9","9","9"] → s="999"
Round 3: s.size()=3 > 2
["99","9"] → ["18","9"] → s="189"
Round 4: s.size()=3 > 2
["18","9"] → ["9","9"] → s="99"
Round 5: s.size()=2 == k=2 → EXIT

Return "99" ✓
```

---

## Edge Cases

### Last Group Smaller Than k

```
s="12345", k=2

Groups: ["12","34","5"] → ["3","7","5"] → s="375"
The "5" group has only 1 digit — handled by j < s.size() ✓
```

### k = 1

```
Every group is a single digit. Sum = that digit. s never changes.
Loop: s.size() > 1 is true only when s has multiple chars, but
each single-char group contributes exactly that char, so s stays the same.
Actually wait — groups of 1 char, sum = digit itself, s stays same → infinite loop?

No: if k=1, groups are single chars, str = same digits as s.
s.size() > 1 would loop forever?

Actually constraints say k ≥ 1, but also that the process terminates
because problem guarantees result exists. For k=1, s is already all
single digits, and each group of 1 produces the same digit.
If s has >1 char, s.size() stays > k=1 forever.

BUT: the problem constraints ensure k ≤ s.length() for the initial call,
AND that the process terminates. For k=1, the while never exits for
multi-digit strings. This edge case doesn't appear in valid test inputs
per the problem constraints (1 ≤ k ≤ s.length()).
```

---

## Time and Space Complexity

```
Let n = initial length of s.
Each round, a group of k chars collapses to at most ceil(log10(9k))+1 chars.
For k ≤ n, each round reduces length significantly.

In practice:
  Round 1: n → roughly n/k * digits_per_sum
  For large n and k, converges quickly.

Worst case across all rounds: O(n) total character work.
Space: O(n) for the intermediate string.
```

| | Value |
|---|---|
| Time | O(n) amortized across all rounds |
| Space | O(n) |

---

## Key Insight

```
Direct simulation — no clever trick needed here.

The two bounds on the inner loop:
  j < s.size()   → safe for the last (possibly short) group
  j < i + k      → cap each group at exactly k chars

Both must be AND-ed together. Dropping either:
  Drop j < s.size()  → out-of-bounds read on the last group
  Drop j < i + k     → entire string summed as one group every time
```

---

## References

- 🔗 [LeetCode 2243 — Calculate Digit Sum of a String](https://leetcode.com/problems/calculate-digit-sum-of-a-string/)
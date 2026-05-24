# Maximum Consecutive Ones

## Problem Link
🔗 [LeetCode 485 — Max Consecutive Ones](https://leetcode.com/problems/max-consecutive-ones/)

---

## What is this Problem?

Given a **binary array** (containing only 0s and 1s), find the **maximum number of consecutive 1s** in the array.

**Examples:**
```
nums = [1, 1, 0, 1, 1, 1]
Output: 3
(Last three 1s form the longest consecutive streak)

nums = [1, 0, 1, 1, 0, 1]
Output: 2

nums = [0, 0, 0]
Output: 0
(No 1s at all)

nums = [1, 1, 1, 1]
Output: 4
(Entire array is 1s)
```

---

## The Problem Explained

Think of it like **counting a winning streak in a game**:

```
Match results: W W L W W W L W
               1 1 0 1 1 1 0 1

Streak counter:
  W → streak = 1
  W → streak = 2
  L → streak RESETS to 0
  W → streak = 1
  W → streak = 2
  W → streak = 3  ← best streak so far!
  L → streak RESETS to 0
  W → streak = 1

Best streak ever seen = 3
```

**Key idea:** Walk through the array once. Keep a running count of current consecutive 1s. The moment you hit a 0, reset the counter to 0. At every step, update the maximum seen so far.

---

## HOOK TO REMEMBER FOREVER

**"SEE 1 → INCREMENT. SEE 0 → RESET. ALWAYS UPDATE MAX."**

Every time you see "longest consecutive streak of 1s":
- ✅ Maintain `cnt` — current streak of 1s
- ✅ On `1` → `cnt++`
- ✅ On `0` → `cnt = 0` (streak broken, start over)
- ✅ After every update → `maxi = max(maxi, cnt)`
- ✅ O(n) time, O(1) space — single pass, two variables

**Remember: The 0 is a wall. It doesn't just stop the streak — it erases it. Max is updated every step, not just at the end of a streak!** 🧱

---

## How It Works Step By Step

### The Strategy

```
nums = [1, 1, 0, 1, 1, 1]

cnt = 0, maxi = 0

num=1 → cnt=1, maxi=max(0,1)=1
num=1 → cnt=2, maxi=max(1,2)=2
num=0 → cnt=0, maxi=max(2,0)=2   ← wall hit, streak gone
num=1 → cnt=1, maxi=max(2,1)=2
num=1 → cnt=2, maxi=max(2,2)=2
num=1 → cnt=3, maxi=max(2,3)=3

Return 3 ✓
```

### Visual — Counter Behaviour

```
Index:   0  1  2  3  4  5
nums:    1  1  0  1  1  1
         ↓  ↓  ↓  ↓  ↓  ↓
cnt:     1  2  0  1  2  3
                ↑
              RESET here (hit a 0)

maxi:    1  2  2  2  2  3
                    ↑     ↑
              max holds  new max
              old best
```

---

## Code Full Solution

```cpp
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int cnt = 0;
        int maxi = 0;

        for (auto num : nums) {
            if (num == 1) {
                cnt++;
            } else {
                cnt = 0;
            }
            maxi = max(maxi, cnt);
        }

        return maxi;
    }
};
```

---

## Code Explanation

### Initialize

```cpp
int cnt = 0;
int maxi = 0;
```

- **`cnt`:** Current streak of consecutive 1s. Resets on every 0.
- **`maxi`:** Best streak seen so far. Never decreases.

Both start at 0 — handles the edge case of an all-zero array naturally (returns 0).

---

### The Loop

```cpp
for (auto num : nums) {
    if (num == 1) {
        cnt++;
    } else {
        cnt = 0;
    }
    maxi = max(maxi, cnt);
}
```

**On seeing a `1`:**
```
cnt++  → extend the current streak
```

**On seeing a `0`:**
```
cnt = 0  → wall hit, streak completely reset
           The next 1 will start a fresh streak from 1
```

**`maxi = max(maxi, cnt)` runs every iteration, not just on reset:**
```
Why update every step and not just when streak ends?

nums = [1, 1, 1, 1]  (no 0s at all, streak never resets)

If we only updated maxi on reset:
  Loop ends, maxi never got updated → returns 0 ❌

Updating every step:
  After each 1, maxi catches the growing streak.
  When loop ends, maxi already holds the correct answer ✓
```

---

## Complete Example Traces

### Trace 1: Mixed Array

```
nums = [1, 1, 0, 1, 1, 1]

num=1: cnt=1, maxi=1
num=1: cnt=2, maxi=2
num=0: cnt=0, maxi=2
num=1: cnt=1, maxi=2
num=1: cnt=2, maxi=2
num=1: cnt=3, maxi=3

Return 3 ✓
```

### Trace 2: Multiple Streaks of Equal Length

```
nums = [1, 1, 0, 1, 1, 0, 1]

num=1: cnt=1, maxi=1
num=1: cnt=2, maxi=2
num=0: cnt=0, maxi=2
num=1: cnt=1, maxi=2
num=1: cnt=2, maxi=2   ← ties with first streak, maxi holds
num=0: cnt=0, maxi=2
num=1: cnt=1, maxi=2

Return 2 ✓
```

### Trace 3: No 1s

```
nums = [0, 0, 0]

num=0: cnt=0, maxi=0
num=0: cnt=0, maxi=0
num=0: cnt=0, maxi=0

Return 0 ✓
```

### Trace 4: All 1s

```
nums = [1, 1, 1, 1]

num=1: cnt=1, maxi=1
num=1: cnt=2, maxi=2
num=1: cnt=3, maxi=3
num=1: cnt=4, maxi=4

Return 4 ✓  (no reset ever happens)
```

### Trace 5: Alternating

```
nums = [1, 0, 1, 0, 1]

num=1: cnt=1, maxi=1
num=0: cnt=0, maxi=1
num=1: cnt=1, maxi=1
num=0: cnt=0, maxi=1
num=1: cnt=1, maxi=1

Return 1 ✓  (every streak is just length 1)
```

### Trace 6: Single Element

```
nums = [1]
num=1: cnt=1, maxi=1
Return 1 ✓

nums = [0]
num=0: cnt=0, maxi=0
Return 0 ✓
```

### Trace 7: Streak at the Very End

```
nums = [0, 0, 1, 1, 1]

num=0: cnt=0, maxi=0
num=0: cnt=0, maxi=0
num=1: cnt=1, maxi=1
num=1: cnt=2, maxi=2
num=1: cnt=3, maxi=3

Return 3 ✓
(Streak at the end is captured correctly — no reset needed to record it,
 maxi updates on every step.)
```

---

## Edge Cases

### Case 1: Single 1

```
Input: [1]
Output: 1 ✓
```

### Case 2: Single 0

```
Input: [0]
Output: 0 ✓
```

### Case 3: All Zeros

```
Input: [0, 0, 0, 0]
cnt stays 0 throughout. maxi stays 0.
Output: 0 ✓
```

### Case 4: All Ones

```
Input: [1, 1, 1, 1, 1]
cnt grows to n. Never resets. maxi = n.
Output: 5 ✓
```

### Case 5: Streak at the Start

```
Input: [1, 1, 1, 0, 0]
cnt peaks at 3 then resets. maxi holds 3.
Output: 3 ✓
```

### Case 6: Streak at the End (No Trailing 0)

```
Input: [0, 1, 1, 1]
cnt climbs to 3 at the end. Since maxi updates every step,
no trailing reset needed.
Output: 3 ✓
```

---

## Time Complexity

- **O(n)** where n = length of `nums`
- Single pass through the array
- Every element processed exactly once in O(1)
- Total: **O(n)**

---

## Space Complexity

- **O(1)** — constant extra space
- Only two variables: `cnt` and `maxi`
- No extra array, no hash map
- Total: **O(1)**

---

## Key Insights

### Why `maxi` is Updated Inside the Loop, Not Outside

```
Wrong intuition: "Update maxi only when a streak ends (on seeing 0)."

Counterexample: [1, 1, 1, 1]
  No 0s → streak never "ends" → maxi never updated → returns 0 ❌

Correct: update maxi after EVERY element.
  When cnt grows, maxi grows with it.
  When cnt resets, maxi holds the old best — it never shrinks.
  Works for all cases: streak at start, middle, end, or entire array. ✓
```

### Why Reset to 0 and Not 1

```
When we see a 0, the streak is broken.
The very next element (if it's a 1) starts a BRAND NEW streak from 1.

If we reset to 1 instead of 0:
  [0, 0, 1] → num=0: cnt=1? That's wrong — 0 is not a 1!

Resetting to 0 is the only correct choice.
The next 1 will bring it back to 1 via cnt++. ✓
```

### `cnt` and `maxi` — Two Separate Jobs

```
cnt  → "how long is my CURRENT run?"  (resets freely)
maxi → "what's the BEST run I've ever seen?" (never decreases)

They work together:
  cnt does the real-time tracking.
  maxi acts as a "high score board" — only ever goes up.

This two-variable pattern appears in many streak/subarray problems:
  → Max consecutive zeros
  → Longest subarray of equal elements
  → Streak counting in any condition
```

---

## References

- 🔗 [LeetCode 485 — Max Consecutive Ones](https://leetcode.com/problems/max-consecutive-ones/)
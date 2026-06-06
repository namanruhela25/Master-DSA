# Majority Element (Boyer-Moore Voting Algorithm)

## Problem Link
🔗 [LeetCode 169 — Majority Element](https://leetcode.com/problems/majority-element/)

---

## What is this Problem?

Given an array of size `n`, find the **majority element** — the element that appears **more than ⌊n/2⌋ times**. The majority element always exists in the given input.

**Examples:**
```
nums = [3, 2, 3]
Output: 3   (3 appears 2 times out of 3, > 3/2 = 1.5)

nums = [2, 2, 1, 1, 1, 2, 2]
Output: 2   (2 appears 4 times out of 7, > 7/2 = 3.5)

nums = [1]
Output: 1   (only element, trivially majority)
```

---

## The Problem Explained

Think of it like a **political election with votes cancelling each other out**:

```
Votes: [A, B, A, A, B, A, A]
       Majority: A (appears 5 out of 7 times)

Voting process:
  Pick A as candidate. count=1
  See B → B ≠ A, cancel! count=0
  Candidate eliminated. Pick next: A. count=1
  See A → same! count=2
  See B → cancel! count=1
  See A → same! count=2
  See A → same! count=3

Last standing candidate = A ✓

Key insight: If the majority exists, it has MORE votes than all
others COMBINED. No matter how many times others cancel it,
the majority always survives with count > 0.
```

**Key idea:** The majority element appears more than n/2 times. Even if every other element gangs up to cancel it one-by-one, the majority always has votes left over. The last candidate standing is the answer.

---

## HOOK TO REMEMBER FOREVER

**"COUNT HITS ZERO → SWITCH CANDIDATE. SAME ELEMENT → COUNT UP. DIFFERENT → COUNT DOWN."**

Every time you see "find the element appearing more than n/2 times":
- ✅ Maintain `el` (current candidate) and `cnt` (its "net votes")
- ✅ `cnt == 0` → adopt current element as new candidate, `cnt = 1`
- ✅ `nums[i] == el` → same as candidate → `cnt++`
- ✅ `nums[i] != el` → different → `cnt--` (cancel one vote)
- ✅ Return `el` at the end — the majority always survives
- ✅ O(n) time, O(1) space — single pass, two variables

**Remember: The majority element has more than n/2 votes. It can absorb ALL cancellations from every other element and still survive. That's the mathematical guarantee behind this algorithm.** 🗳️

---

## Why This Works — The Math

```
Say majority element M appears k times where k > n/2.
All other elements together appear n - k times.

Worst case: every non-M element cancels exactly one M vote.
Cancellations possible = n - k

Surviving M votes = k - (n - k) = 2k - n

Since k > n/2:
  2k > n
  2k - n > 0

So M always survives with at least 1 net vote. ✓
No matter what order elements appear in,
the majority element is always the last candidate standing.
```

---

## How It Works Step By Step

### The Strategy

```
nums = [2, 2, 1, 1, 1, 2, 2]

el=-1, cnt=0

i=0: cnt==0 → el=2, cnt=1
i=1: el==nums[1]=2 → cnt=2
i=2: el≠nums[2]=1 → cnt=1
i=3: el≠nums[3]=1 → cnt=0
i=4: cnt==0 → el=1, cnt=1
i=5: el≠nums[5]=2 → cnt=0
i=6: cnt==0 → el=2, cnt=1

Return el=2 ✓
```

### Visual — Candidate and Count Over Time

```
nums:  [2,  2,  1,  1,  1,  2,  2]
        ↓   ↓   ↓   ↓   ↓   ↓   ↓
el:    [2,  2,  2,  2,  1,  1,  2]
cnt:   [1,  2,  1,  0,  1,  0,  1]
            ↑               ↑
         count peaks     dropped
         after 2 same    to 0 again
         elements
```

## Code Full Solution

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int el = -1;
        int cnt = 0;
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            if (cnt == 0) {
                el = nums[i];
                cnt++;
            } else if (el != nums[i]) {
                cnt--;
            } else {
                cnt++;
            }
        }

        return el;
    }
};
```

---

## Code Explanation

### Initialize

```cpp
int el = -1;
int cnt = 0;
```

- **`el`:** Current candidate for majority. `-1` is just a placeholder — it gets overwritten on the very first element (since `cnt` starts at 0).
- **`cnt`:** Net "vote count" for the current candidate. When it hits 0, the candidate is dropped.

---

### Case 1 — No Current Candidate (`cnt == 0`)

```cpp
if (cnt == 0) {
    el = nums[i];
    cnt++;
}
```

```
The previous candidate (if any) was fully cancelled out.
We have no allegiance — adopt the current element as the new candidate.
Start fresh with cnt=1 ("I support this one").
```

---

### Case 2 — Different from Candidate

```cpp
} else if (el != nums[i]) {
    cnt--;
}
```

```
The current element opposes our candidate.
One vote cancels out. cnt drops by 1.

If cnt hits 0 next iteration, the candidate is abandoned
and we pick the next element fresh.
```

---

### Case 3 — Same as Candidate

```cpp
} else {
    cnt++;
}
```

```
The current element reinforces our candidate.
cnt goes up. The candidate becomes more entrenched.
```

**Why these three cases cover everything:**

```
cnt == 0    → no candidate, adopt immediately
cnt > 0 and nums[i] == el → reinforce
cnt > 0 and nums[i] != el → cancel

There is no fourth case. ✓
```

---

## Complete Example Traces

### Trace 1: Standard Case

```
nums = [2, 2, 1, 1, 1, 2, 2]

i  nums[i]  cnt  el   action
─────────────────────────────
0    2       0   -1   cnt==0 → el=2, cnt=1
1    2       1    2   el==2  → cnt=2
2    1       2    2   el≠1   → cnt=1
3    1       1    2   el≠1   → cnt=0
4    1       0    2   cnt==0 → el=1, cnt=1
5    2       1    1   el≠2   → cnt=0
6    2       0    1   cnt==0 → el=2, cnt=1

Return 2 ✓
```

### Trace 2: Majority All Grouped Together

```
nums = [1, 1, 1, 2, 2]

i  nums[i]  cnt  el   action
─────────────────────────────
0    1       0   -1   cnt==0 → el=1, cnt=1
1    1       1    1   el==1  → cnt=2
2    1       2    1   el==1  → cnt=3
3    2       3    1   el≠2   → cnt=2
4    2       2    1   el≠2   → cnt=1

Return 1 ✓  (majority was front-loaded, count stayed positive)
```

### Trace 3: Majority All at the End

```
nums = [2, 2, 1, 1, 1]

i  nums[i]  cnt  el   action
─────────────────────────────
0    2       0   -1   cnt==0 → el=2, cnt=1
1    2       1    2   el==2  → cnt=2
2    1       2    2   el≠1   → cnt=1
3    1       1    2   el≠1   → cnt=0
4    1       0    2   cnt==0 → el=1, cnt=1

Return 1 ✓  (majority was back-loaded, still wins)
```

### Trace 4: Alternating, Majority Wins

```
nums = [1, 2, 1, 2, 1]

i  nums[i]  cnt  el   action
─────────────────────────────
0    1       0   -1   cnt==0 → el=1, cnt=1
1    2       1    1   el≠2   → cnt=0
2    1       0    1   cnt==0 → el=1, cnt=1
3    2       1    1   el≠2   → cnt=0
4    1       0    1   cnt==0 → el=1, cnt=1

Return 1 ✓  (1 appears 3/5 times, keeps getting re-elected)
```

### Trace 5: Single Element

```
nums = [7]

i=0: cnt==0 → el=7, cnt=1
Return 7 ✓
```

### Trace 6: All Same Elements

```
nums = [5, 5, 5, 5]

i=0: cnt==0 → el=5, cnt=1
i=1: el==5  → cnt=2
i=2: el==5  → cnt=3
i=3: el==5  → cnt=4

Return 5 ✓  (count only ever grew)
```

---

## Edge Cases

### Case 1: Two Elements, One Majority

```
Input: [1, 2, 1]
i=0: el=1, cnt=1
i=1: cnt-- → 0
i=2: el=1, cnt=1
Output: 1 ✓
```

### Case 2: Majority Appears Exactly ⌊n/2⌋ + 1 Times

```
Input: [1, 2, 1, 2, 1]  (n=5, majority 1 appears 3 times = 5/2+1)
Always returns the majority. The math guarantees survival. ✓
```

### Case 3: Large Array, Majority Scattered

```
The voting algorithm doesn't care about order.
Whether majority elements are grouped or scattered,
their count always outlasts all opposition. ✓
```

---

## Time Complexity

- **O(n)** — single pass through the array
- Each element processed exactly once in O(1)
- Total: **O(n)**

---

## Space Complexity

- **O(1)** — constant extra space
- Only two variables: `el` and `cnt`
- No hash map, no sorted copy, no extra array
- Total: **O(1)**

---

## Key Insights

### Why `-1` as Initial Candidate Doesn't Matter

```
el = -1 is just a placeholder.
The very first element always triggers cnt == 0 (since cnt starts at 0).
So el gets overwritten on the first iteration regardless.

It could be initialized to anything —
0, INT_MAX, or left uninitialized (though that's bad practice).
The algorithm's correctness doesn't depend on the initial value of el. ✓
```

### Boyer-Moore vs Other Approaches

```
Approach 1 — HashMap (count frequencies):
  Time: O(n)   Space: O(n)
  Store count of each element, return the one with count > n/2.

Approach 2 — Sort:
  Time: O(n log n)   Space: O(1)
  Middle element of sorted array is always the majority.

Approach 3 — Boyer-Moore Voting (this solution):
  Time: O(n)   Space: O(1)
  Best of both worlds.
```

### The Guarantee — Majority Must Exist

```
⚠️ This algorithm ASSUMES a majority element exists.

If no majority element exists:
  nums = [1, 2, 3]
  Algorithm returns some element (whichever survives last).
  That element may NOT actually be a majority.
  The result would be wrong!

The problem statement guarantees a majority always exists,
so this is safe. If the guarantee is removed,
add a second pass to verify the returned element's count. ✓
```

### Why The Last Candidate Standing Wins

```
Imagine two teams fighting: Team Majority vs Team Everyone-Else.

Team Everyone-Else has at most n/2 - 1 members.
Team Majority has at least n/2 + 1 members.

Even if every non-majority element uses its one cancellation
perfectly to cancel one majority vote, majority still wins:

  (n/2 + 1) - (n/2 - 1) = 2 remaining votes for majority

No matter how the battle plays out, majority always survives.
The last candidate standing must be the majority element.
```

---

## References

- 🔗 [LeetCode 169 — Majority Element](https://leetcode.com/problems/majority-element/)
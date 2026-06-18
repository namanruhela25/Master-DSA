# Majority Element II

## Problem Link
🔗 [LeetCode 229 — Majority Element II](https://leetcode.com/problems/majority-element-ii/)

---

## What is this Problem?

Given an integer array `nums` of size `n`, find **all elements that appear more than ⌊n/3⌋ times**. Return them in any order.

**Examples:**
```
nums = [3, 2, 3]
Output: [3]
n=3, threshold = ⌊3/3⌋ = 1. Elements appearing > 1 time: 3 (appears 2 times).

nums = [1, 1, 1, 3, 3, 2, 2, 2]
Output: [1, 2]
n=8, threshold = ⌊8/3⌋ = 2. Elements appearing > 2 times: 1 (3 times), 2 (3 times).

nums = [1, 2, 3]
Output: []
n=3, threshold = 1. No element appears > 1 time.
```

---

## The Problem Explained

Think of it like a **3-party election where any candidate with more than 1/3 of the votes wins**:

```
3-party election rule: only candidates with more than 33% of
votes are "winners" (appear more than ⌊n/3⌋ times).

Key mathematical fact:
  At MOST 2 such candidates can exist.

  Proof: If 3 candidates each had > n/3 votes:
    total votes > 3×(n/3) = n. IMPOSSIBLE — only n total votes exist.

So there are always AT MOST 2 elements to find.
That lets us extend Boyer-Moore to track TWO candidates instead of one.
```

**Key idea:** Run an extended Boyer-Moore Voting algorithm with **two candidates and two counters**. Then verify both candidates with an actual frequency count (since the algorithm might retain "survivor" candidates that don't meet the threshold).

---

## HOOK TO REMEMBER FOREVER

**"TWO CANDIDATES, TWO COUNTERS — MATCH INCREMENTS, MISMATCH DECREMENTS BOTH, THEN VERIFY."**

Every time you see "find elements appearing more than n/3 times":
- ✅ Two candidates `maj1`, `maj2` and two counters `cnt1`, `cnt2`
- ✅ On `el == maj1` → `cnt1++`
- ✅ On `el == maj2` → `cnt2++`
- ✅ On `cnt1 == 0` → adopt `el` as new `maj1`, `cnt1 = 1`
- ✅ On `cnt2 == 0` → adopt `el` as new `maj2`, `cnt2 = 1`
- ✅ Otherwise → `cnt1--`, `cnt2--` (this element cancels one vote from EACH)
- ✅ After first pass: **verify** both candidates with a real frequency count
- ✅ O(n) time, O(1) space

**Remember: The verification pass is NOT optional. The two survivors of the voting phase are only CANDIDATES — they might not actually exceed ⌊n/3⌋. Always count their real frequencies!** ✅

---

## Why At Most 2 Elements Can Qualify

```
n = total elements
threshold = ⌊n/3⌋

Suppose 3 different elements each appear > ⌊n/3⌋ times:
  Each appears at least ⌊n/3⌋ + 1 times.
  Combined appearances ≥ 3 × (⌊n/3⌋ + 1) > 3 × (n/3) = n

But the total can't exceed n elements! Contradiction.

→ At most 2 elements can appear more than ⌊n/3⌋ times.
→ We only need TWO candidates. ✓
```

## How It Works Step By Step

### Example: `nums = [1, 1, 1, 3, 3, 2, 2, 2]`

**Phase 1 — Voting:**

```
maj1=?, maj2=?, cnt1=0, cnt2=0

el=1: cnt1==0 → maj1=1, cnt1=1.        maj1=1,cnt1=1 | maj2=?,cnt2=0
el=1: el==maj1 → cnt1=2.              maj1=1,cnt1=2 | maj2=?,cnt2=0
el=1: el==maj1 → cnt1=3.              maj1=1,cnt1=3 | maj2=?,cnt2=0
el=3: cnt2==0 → maj2=3, cnt2=1.       maj1=1,cnt1=3 | maj2=3,cnt2=1
el=3: el==maj2 → cnt2=2.              maj1=1,cnt1=3 | maj2=3,cnt2=2
el=2: el≠maj1, el≠maj2, cnt1≠0, cnt2≠0 → cnt1--,cnt2--.
                                       maj1=1,cnt1=2 | maj2=3,cnt2=1
el=2: el≠maj1, el≠maj2 → cnt1--,cnt2--.
                                       maj1=1,cnt1=1 | maj2=3,cnt2=0
el=2: cnt2==0 → maj2=2, cnt2=1.       maj1=1,cnt1=1 | maj2=2,cnt2=1

Candidates after Phase 1: maj1=1, maj2=2
```

**Phase 2 — Verify:**

```
Count frequency of 1 and 2 in nums=[1,1,1,3,3,2,2,2]:
  freq1 (count of 1) = 3
  freq2 (count of 2) = 3
  n = 8, threshold = ⌊8/3⌋ = 2

  freq1=3 > 2 → add 1 to ans
  freq2=3 > 2 → add 2 to ans

Return [1, 2] ✓
```

### Visual — Counter State Over Time

```
Index:  0    1    2    3    4    5    6    7
nums:   1    1    1    3    3    2    2    2

maj1:   1    1    1    1    1    1    1    1
cnt1:   1    2    3    3    3    2    1    1

maj2:   ?    ?    ?    3    3    3    3    2
cnt2:   0    0    0    1    2    1    0    1
```

---

## Code Full Solution

```cpp
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int maj1;
        int maj2;
        int cnt1 = 0;
        int cnt2 = 0;
        int n = nums.size();

        // Phase 1: Extended Boyer-Moore voting
        for (int &el : nums) {
            if (el == maj1) {
                cnt1++;
            } else if (el == maj2) {
                cnt2++;
            } else if (cnt1 == 0) {
                maj1 = el;
                cnt1++;
            } else if (cnt2 == 0) {
                maj2 = el;
                cnt2++;
            } else {
                cnt1--;
                cnt2--;
            }
        }

        // Phase 2: Verify actual frequencies
        int freq1 = 0, freq2 = 0;
        for (int &num : nums) {
            if (num == maj1) freq1++;
            else if (num == maj2) freq2++;
        }

        vector<int> ans;
        if (freq1 > floor(n / 3)) ans.push_back(maj1);
        if (freq2 > floor(n / 3)) ans.push_back(maj2);

        return ans;
    }
};
```

> ⚠️ **Note on uninitialized variables:** `maj1` and `maj2` are declared without initialization. This is technically undefined behavior in C++. Safe fix: initialize them to values that can never appear in the input, or use the `cnt == 0` checks carefully. In practice on LeetCode this compiles and runs correctly, but a cleaner approach is `int maj1 = INT_MIN, maj2 = INT_MAX;` or a separate sentinel like `int maj1 = 0, cnt1 = 0;` (since the first `cnt1 == 0` branch will overwrite `maj1` before it's ever compared meaningfully).

---

## Code Explanation

### Phase 1 — The Five Cases

```cpp
if (el == maj1)          { cnt1++; }
else if (el == maj2)     { cnt2++; }
else if (cnt1 == 0)      { maj1 = el; cnt1++; }
else if (cnt2 == 0)      { maj2 = el; cnt2++; }
else                     { cnt1--; cnt2--; }
```

**The order of these checks is critical:**

```
Check 1 & 2 FIRST: "Does this element match an existing candidate?"
  If yes, reinforce that candidate. Do NOT fall through to adoption checks.

  Why first? If cnt1==0 and el==maj1 (leftover from a previous round),
  we should REINFORCE, not adopt again. The match check must come before
  the cnt==0 check.

Check 3 & 4: "Can we adopt a new candidate?"
  Only reached if el doesn't match either existing candidate.
  cnt1==0 means the first slot is vacant — fill it.
  cnt2==0 means the second slot is vacant — fill it.

Check 5: "Both slots occupied, element is new."
  This element opposes BOTH candidates.
  In the original Boyer-Moore (1 candidate), this cancels one.
  Extended (2 candidates): cancel one vote from EACH.
  Conceptually: 1 element cancels 1 from candidate 1 AND 1 from candidate 2
  (this triple {el, maj1, maj2} disappears together from the "vote pool").
```

---

### Why `cnt1--` AND `cnt2--` Together?

```
Mathematical basis:
  We can divide ANY sequence into groups of 3 distinct elements.
  Each such group: {a, b, c} where a≠b, a≠c, b≠c.
  Each group cancels the other.

  If the majority elements appear > n/3 times each, they can
  survive all these 3-way cancellations and at least one
  (possibly both) will have cnt > 0 at the end.

Why decrement BOTH and not just one?
  Decrementing only cnt1 would give cnt2 an artificial advantage
  — an element that's not a majority could accumulate a high cnt2
  by never being "cancelled" when a non-maj1 element appears.

  Both must be decremented to ensure the cancellation is symmetric
  and truly 3-way. ✓
```

---

### Phase 2 — Why Verification Is Mandatory

```
The voting phase GUARANTEES: if a majority element exists,
it will be among the two candidates.

BUT: it does NOT guarantee both candidates are majority elements!

Counter-example:
  nums = [1, 2, 3], k implicitly n/3=1, threshold > 1

  Phase 1:
    el=1: cnt1==0 → maj1=1, cnt1=1
    el=2: cnt2==0 → maj2=2, cnt2=1
    el=3: cnt1--, cnt2-- → cnt1=0, cnt2=0

  Candidates: maj1=1, maj2=2

  Phase 2:
    freq1=1, freq2=1. n=3, threshold=1.
    freq1 > 1? NO. freq2 > 1? NO.

  Return [] ✓ (no element appears more than once)

Without verification: we'd incorrectly return [1, 2]. ❌
```

---

## Complete Example Traces

### Trace 1: Two Majority Elements

```
nums = [1, 1, 1, 3, 3, 2, 2, 2], n=8, threshold=2

Phase 1: (traced above)
  Survivors: maj1=1, maj2=2

Phase 2:
  freq1=3 (count of 1s), freq2=3 (count of 2s)
  3>2 → add 1. 3>2 → add 2.

Return [1, 2] ✓
```

### Trace 2: One Majority Element

```
nums = [3, 2, 3], n=3, threshold=1

Phase 1:
  el=3: cnt1==0 → maj1=3, cnt1=1
  el=2: cnt2==0 → maj2=2, cnt2=1
  el=3: el==maj1 → cnt1=2

  Candidates: maj1=3, maj2=2

Phase 2:
  freq1=2 (count of 3s), freq2=1 (count of 2s)
  2>1 → add 3. 1>1? NO.

Return [3] ✓
```

### Trace 3: No Majority Element

```
nums = [1, 2, 3], n=3, threshold=1

Phase 1:
  el=1: maj1=1, cnt1=1
  el=2: maj2=2, cnt2=1
  el=3: cnt1--, cnt2-- → cnt1=0, cnt2=0

  Candidates: maj1=1, maj2=2

Phase 2:
  freq1=1, freq2=1
  1>1? NO. 1>1? NO.

Return [] ✓
```

### Trace 4: All Same Elements

```
nums = [5, 5, 5, 5], n=4, threshold=1

Phase 1:
  el=5: cnt1==0 → maj1=5, cnt1=1
  el=5: el==maj1 → cnt1=2
  el=5: el==maj1 → cnt1=3
  el=5: el==maj1 → cnt1=4

  Candidates: maj1=5, maj2=? (never adopted)

Phase 2:
  freq1=4. freq2=0 (maj2 never set, but counting never matches garbage value).
  4>1 → add 5.

Return [5] ✓
```

### Trace 5: Candidates Keep Switching

```
nums = [1, 2, 1, 2, 1, 2, 1], n=7, threshold=2

Phase 1:
  el=1: maj1=1, cnt1=1
  el=2: maj2=2, cnt2=1
  el=1: el==maj1 → cnt1=2
  el=2: el==maj2 → cnt2=2
  el=1: el==maj1 → cnt1=3
  el=2: el==maj2 → cnt2=3
  el=1: el==maj1 → cnt1=4

  Candidates: maj1=1, maj2=2

Phase 2:
  freq1=4 (count of 1s), freq2=3 (count of 2s)
  4>2 → add 1. 3>2 → add 2.

Return [1, 2] ✓
```

---

## Edge Cases

### Case 1: Single Element

```
Input: [1], n=1, threshold=0
Phase 1: maj1=1, cnt1=1
Phase 2: freq1=1. 1>0 → add 1.
Output: [1] ✓
```

### Case 2: Two Different Elements

```
Input: [1, 2], n=2, threshold=0
Phase 1: maj1=1, cnt1=1. maj2=2, cnt2=1.
Phase 2: freq1=1, freq2=1. 1>0 → add 1. 1>0 → add 2.
Output: [1, 2] ✓
```

### Case 3: Exactly ⌊n/3⌋ Occurrences (Does NOT Qualify)

```
Input: [1, 1, 2, 2, 3, 3], n=6, threshold=2
Each element appears exactly 2 times.
2 > 2? NO. 2 > 2? NO.
Output: [] ✓ (threshold is STRICTLY greater than n/3)
```

---

## Time Complexity

- **O(n)** — two separate linear passes
- Phase 1: O(n)
- Phase 2: O(n)
- Total: **O(n)**

---

## Space Complexity

- **O(1)** extra space
- Only `maj1`, `maj2`, `cnt1`, `cnt2`, `freq1`, `freq2` used
- Output vector holds at most 2 elements — O(1)
- Total: **O(1)**

---

## Key Insights

### This vs Majority Element I (LeetCode 169)

```
LeetCode 169 — Element appearing more than n/2 times:
  At most 1 such element exists.
  ONE candidate, ONE counter.
  No verification needed (guaranteed to exist).

LeetCode 229 — Elements appearing more than n/3 times:
  At most 2 such elements exist.
  TWO candidates, TWO counters.
  Verification REQUIRED (elements not guaranteed to exist).

Generalizes: "more than n/k times" → at most k-1 elements →
  k-1 candidates and counters → extended Boyer-Moore. ✓
```

### The "3-Way Cancellation" Intuition

```
Every time we hit the else branch (cnt1--, cnt2--),
conceptually we're removing a group of 3 elements:
  {el, one occurrence of maj1, one occurrence of maj2}

The three cancel each other out.
After all cancellations, what remains are elements that
couldn't be cancelled — i.e., the majority candidates.

Since any majority element (> n/3) outnumbers the
"cancellation capacity" of all others combined,
at least one majority candidate will survive. ✓
```

### Why the Order of `if-else if` Checks Matters

```
Correct order:
  1. el == maj1   (reinforce existing)
  2. el == maj2   (reinforce existing)
  3. cnt1 == 0    (adopt to vacant slot)
  4. cnt2 == 0    (adopt to vacant slot)
  5. else         (cancel both)

If checks 3 and 4 came BEFORE checks 1 and 2:
  When cnt1=0 and el==maj1 (which has been "abandoned"):
  The code would REINFORCE the old maj1 via check 3 (cnt1==0)
  instead of properly adopting the new element.

  Actually: cnt1==0 means maj1 has no votes. If el==maj1
  but cnt1==0, either path (reinforce vs. re-adopt) gives
  cnt1=1 with maj1 unchanged. So numerically equivalent here.

BUT: if cnt1==0 and el==maj2, the wrong check order would
cause el to overwrite maj1 (vacant slot) instead of
reinforcing maj2. That's the real bug to avoid.

The given order handles all cases correctly. ✓
```

---

## References

- 🔗 [LeetCode 229 — Majority Element II](https://leetcode.com/problems/majority-element-ii/)
- 🔗 [LeetCode 169 — Majority Element (n/2 version)](https://leetcode.com/problems/majority-element/)
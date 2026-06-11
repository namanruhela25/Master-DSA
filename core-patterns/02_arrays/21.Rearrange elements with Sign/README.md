# Rearrange Elements by Sign

**Problem Link:** https://leetcode.com/problems/rearrange-array-elements-by-sign/

---

## What is this Problem?

Given an integer array `nums` of even length consisting of equal numbers of positive and negative integers, rearrange the elements so that positive and negative numbers alternate. The relative order of positives or negatives does not need to be preserved — any valid alternating arrangement is acceptable.

Return an array `ans` of the same length where `ans[0]` is positive, `ans[1]` is negative, `ans[2]` is positive, and so on.

**Examples:**
```
Input:  nums = [3,1,-2,-5,2,-4]
Output: [3, -2, 1, -5, 2, -4]

Input:  nums = [-1,1]
Output: [1, -1]

Input:  nums = [1,2,-1,-2]
Output: [1, -1, 2, -2]
```

---

## The Problem Explained

You are given an array with equal counts of positive and negative numbers. The goal is to produce an array where signs alternate, starting with a positive at index 0. Since the counts are equal and the array length is even, this is always possible.

Naive approaches:
- Two queues (positives and negatives) and pop alternately → O(n) time, O(n) extra space.
- In-place swaps with two pointers scanning for misplaced signs → doable but more bookkeeping.

Optimal approach used here:
- Create an output array `ans` of same size.
- Keep two write pointers: one for positive positions (even indices 0,2,4...) and one for negative positions (odd indices 1,3,5...).
- Scan the input once and place each element directly into its next correct slot.

This is simple, linear time, and uses O(n) output space (required when returning a new array).

---

## HOOK TO REMEMBER FOREVER

**"WRITE POSAT EVEN, NEG AT ODD — TWO WRITE POINTERS, SINGLE SCAN."**

- `pos = 0` → next even index for a positive
- `neg = 1` → next odd index for a negative
- Iterate `nums`, place into `ans[pos]` or `ans[neg]` and advance pointer by 2

---

## How It Works Step By Step

Given: `nums = [3, 1, -2, -5, 2, -4]`

Initialize:
```
pos = 0, neg = 1, n = 6
ans = [_, _, _, _, _, _]
```

Scan:
- 3 > 0 → ans[pos]=3 → pos=2 → ans=[3, _, _, _, _, _]
- 1 > 0 → ans[pos]=1 → pos=4 → ans=[3, _, 1, _, _, _]
- -2 < 0 → ans[neg]=-2 → neg=3 → ans=[3, -2, 1, _, _, _]
- -5 < 0 → ans[neg]=-5 → neg=5 → ans=[3, -2, 1, -5, _, _]
- 2 > 0 → ans[pos]=2 → pos=6 → ans=[3, -2, 1, -5, 2, _]
- -4 < 0 → ans[neg]=-4 → neg=7 → ans=[3, -2, 1, -5, 2, -4]

Return `ans` which alternates positive and negative.

---

## Code Full Solution

```cpp
class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int pos = 0;
        int neg = 1;
        int n = nums.size();
        vector<int> ans(n);

        for(int i = 0; i < n; i++) {
            if(nums[i] > 0) {
                ans[pos] = nums[i];
                pos += 2;
            } else {
                ans[neg] = nums[i];
                neg += 2;
            }
        }
        return ans;
    }
};
```

---

## Code Explanation

- `pos` starts at 0 and moves by +2 each time we place a positive number (next even index).
- `neg` starts at 1 and moves by +2 each time we place a negative number (next odd index).
- The input is scanned once; each element is written into `ans` exactly once.
- Because counts of positive and negative numbers are equal and array length is even, `pos` and `neg` never go out of bounds.

This yields a clear invariant:
- After processing k elements, the first `pos/2` positive slots and `neg/2` negative slots are filled correctly.

---

## Edge Cases

- Minimal length: `n = 2`, e.g., `[-1, 1]` → becomes `[1, -1]`.
- Already alternating: function preserves a valid alternating order (may produce a different valid ordering).
- All positives/negatives not possible under problem constraints (input guarantees equal counts).

---

## Time Complexity

- Single scan of `nums`: O(n)
- Each placement O(1)
- Total: **O(n)**

---

## Space Complexity

- Extra array `ans` of size `n`: **O(n)**
- Two integer pointers: O(1)
- Note: Problem requires returning an array; this is the standard approach.

---

## Key Insights

- Use two write pointers stepping by 2 to place positives at even indices and negatives at odd indices.
- This avoids extra queue structures and does all placement with one pass.
- The algorithm is deterministic, simple, and efficient for the guaranteed input constraints.

---

## Variations & Practice

- In-place rearrangement (without extra array) — more complex: swap misplaced elements using two pointers.
- Maintain original relative order of positives/negatives (stable partition) — requires additional work (queues or stable in-place techniques).
- Handle unbalanced counts (more positives than negatives) — must define policy (e.g., leftover elements at end).

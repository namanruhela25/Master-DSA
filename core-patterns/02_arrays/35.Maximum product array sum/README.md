# Maximum Product Subarray

## Problem Link
🔗 [LeetCode 152 — Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/)

---

## Problem Statement

Given an integer array `nums`, find a contiguous subarray that has the maximum product and return that product.

Example:

```cpp
nums = [2, 3, -2, 4]
Output: 6
```

The optimal subarray is `[2, 3]` with product `6`.

---

## Intuition

A brute-force approach would check every subarray, which is too slow for large arrays.

The key observation is:

- A subarray product can become very large or very small depending on negative numbers.
- If we track the product of subarrays ending at each index, we can update the answer efficiently.
- Zeros break the continuity, so they must reset the running product.

This solution uses two running products:

- `prefix`: product of the current subarray from the left
- `suffix`: product of the current subarray from the right

At every step, it updates the best answer and handles zeros safely.

---

## Approach

The code uses a single pass over the array:

1. Start with `prefix = 1`, `suffix = 1`, and `ans = INT_MIN`.
2. For each index `i`:
   - If `nums[i] == 0`, reset `prefix = 1`.
   - If `nums[n - i - 1] == 0`, reset `suffix = 1`.
   - Multiply the current values into the running products.
   - Update the answer with the larger of the current prefix/suffix product.
3. Return `ans`.

This works because the maximum product subarray must either end at the current position or start at the current position after considering sign changes.

[2, 4, 5, -1, 22, 5, 1, 4]

Either : [2, 4, 5]
Or : [22, 5, 1, 4]

That's why calculating prefix and suffix product which one is max store it.

---

## Why This Works

The product of a subarray can be affected by:

- positive numbers, which increase the product
- negative numbers, which can flip the sign
- zeros, which reset the subarray

By tracking products from both directions, the algorithm captures the best possible subarray ending at or starting from each index without needing extra space.

---

## Complexity Analysis

- Time Complexity: `O(n)`
- Space Complexity: `O(1)`

The solution processes each element a constant number of times.

---

## C++ Code

```cpp
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int prefix = 1;
        int suffix = 1;
        int n = nums.size();
        int ans = INT_MIN;

        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) prefix = 1;
            if (nums[n - i - 1] == 0) suffix = 1;

            prefix *= nums[i];
            suffix *= nums[n - i - 1];

            ans = max(ans, max(prefix, suffix));
        }

        return ans;
    }
};
```

---

## Example Walkthrough

For:

```cpp
nums = [2, 3, -2, 4]
```

### Step-by-step trace

Initial values:

- `prefix = 1`
- `suffix = 1`
- `ans = -∞`

#### Iteration 1: `i = 0`
- `nums[0] = 2`
- `prefix = 1 * 2 = 2`
- `suffix = 1 * nums[3] = 1 * 4 = 4`
- `ans = max(-∞, 2, 4) = 4`

#### Iteration 2: `i = 1`
- `nums[1] = 3`
- `prefix = 2 * 3 = 6`
- `suffix = 4 * nums[2] = 4 * -2 = -8`
- `ans = max(4, 6, -8) = 6`

#### Iteration 3: `i = 2`
- `nums[2] = -2`
- `prefix = 6 * -2 = -12`
- `suffix = -8 * nums[1] = -8 * 3 = -24`
- `ans = max(6, -12, -24) = 6`

#### Iteration 4: `i = 3`
- `nums[3] = 4`
- `prefix = -12 * 4 = -48`
- `suffix = -24 * nums[0] = -24 * 2 = -48`
- `ans = max(6, -48, -48) = 6`

So the maximum product found is `6`, which corresponds to the subarray `[2, 3]`.

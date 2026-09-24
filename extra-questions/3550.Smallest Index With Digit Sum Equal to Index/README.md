# Smallest Index With Equal Digit Sum

## Problem Link
🔗 [LeetCode 3120 — Count the Number of Special Characters I](https://leetcode.com/problems/smallest-index-with-equal-digit-sum/)

---

## What is this Problem?

Given a 0-indexed integer array `nums`, return the **smallest index `i`** where the **sum of digits of `nums[i]` equals `i`**. Return `-1` if no such index exists.

```
nums = [1, 3, 2]
Output: 2
  i=0: digit_sum(1)=1 ≠ 0
  i=1: digit_sum(3)=3 ≠ 1
  i=2: digit_sum(2)=2 == 2 ✓ → return 2

nums = [1, 10, 11]
Output: 1
  i=0: digit_sum(1)=1 ≠ 0
  i=1: digit_sum(10)=1+0=1 == 1 ✓ → return 1
```

---

## HOOK TO REMEMBER FOREVER

**"FOR EACH INDEX, SUM THE DIGITS OF nums[i]. IF SUM == i, RETURN i."**

- ✅ Linear scan from left — guarantees we return the SMALLEST valid index first
- ✅ Convert number to string to iterate over digits easily
- ✅ `ch - '0'` converts char digit to int
- ✅ O(n × d) time where d = max number of digits

---

## Code Full Solution

```cpp
class Solution {
public:
    int smallestIndex(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            string number = to_string(nums[i]);
            int sum = 0;
            for (char ch : number) {
                sum += (ch - '0');
            }
            if (sum == i) return i;
        }
        return -1;
    }
};
```

---

## Code Explanation

### Convert to String for Easy Digit Access

```cpp
string number = to_string(nums[i]);
for (char ch : number) {
    sum += (ch - '0');
}
```

```
to_string(123) = "123"
  '1' - '0' = 1
  '2' - '0' = 2
  '3' - '0' = 3
  sum = 6

Alternative without string:
  while (n > 0) { sum += n % 10; n /= 10; }
  (math-based, no string allocation)
```

### Why Scan Left to Right

```
We want the SMALLEST index. Linear scan left-to-right
returns the first match, which is guaranteed to be smallest.
No need to check the whole array after finding one.
```

---

## Example Traces

### Trace 1

```
nums=[1,3,2]

i=0: sum(1)=1. 1==0? NO
i=1: sum(3)=3. 3==1? NO
i=2: sum(2)=2. 2==2? YES → return 2 ✓
```

### Trace 2

```
nums=[1,10,11]

i=0: sum(1)=1.   1==0? NO
i=1: sum(10)=1.  1==1? YES → return 1 ✓
```

### Trace 3: No Match

```
nums=[5,5,5]

i=0: sum(5)=5. 5==0? NO
i=1: sum(5)=5. 5==1? NO
i=2: sum(5)=5. 5==2? NO

return -1 ✓
```

---

## Edge Cases

### nums[0] = 0

```
digit_sum(0) = 0 == i=0 → return 0 immediately ✓
```

### Large Number at Matching Index

```
nums[19] = 91: digit_sum(91) = 9+1 = 10 ≠ 19. No match.
nums[19] = 991: digit_sum(991) = 9+9+1 = 19 == 19. Match! ✓
```

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(n × d), d = digits in max element ≈ O(n) in practice |
| Space | O(d) for the string conversion |

---

## References

- 🔗 [LeetCode 3120 — Smallest Index With Equal Digit Sum](https://leetcode.com/problems/smallest-index-with-equal-digit-sum/)
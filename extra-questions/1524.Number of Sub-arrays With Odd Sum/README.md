# Number of Sub-arrays With Odd Sum

## Problem Link
🔗 [LeetCode 1524 — Number of Sub-arrays With Odd Sum](https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/)

---

## What is this Problem?

Given an array of integers, return the number of subarrays with an **odd sum**. Answer modulo `10^9 + 7`.

```
arr = [1, 3, 5]
Subarrays: [1]=1✓  [3]=3✓  [5]=5✓  [1,3]=4  [3,5]=8  [1,3,5]=9✓
Output: 4

arr = [2, 4, 6]
All sums even. Output: 0

arr = [1, 2, 3, 4, 5]
Output: 8
```

---

## The Core Insight — Prefix Sum Parity

```
subarray sum arr[i..j] = prefix[j] - prefix[i-1]

This sum is ODD when:
  prefix[j] and prefix[i-1] have DIFFERENT parities
  (odd - even = odd,  even - odd = odd)

This sum is EVEN when:
  prefix[j] and prefix[i-1] have the SAME parity

So for each index j:
  If prefix[j] is EVEN → count all previous prefix sums that were ODD
  If prefix[j] is ODD  → count all previous prefix sums that were EVEN
```

---

## HOOK TO REMEMBER FOREVER

**"DIFFERENT PARITIES = ODD SUM. TRACK ODD AND EVEN PREFIX COUNTS."**

- ✅ `even = 1` at start — the empty prefix (sum=0) is even, accounts for subarrays starting at index 0
- ✅ Current prefix even → it pairs with any past odd prefix → `count += odd`
- ✅ Current prefix odd  → it pairs with any past even prefix → `count += even`
- ✅ Then increment the appropriate counter for the current prefix

---

## Why `even = 1` Initially

```
Before seeing any element, there's one "prefix sum" that matters:
the empty prefix with sum = 0 (even).

If arr[0] = 1 (odd), the subarray [arr[0]] has odd sum.
How does the code detect this?

  sum = 1 (odd) → count += even = 1 ✓

The seed `even = 1` represents prefix[−1] = 0.
Without it, single-element odd subarrays at the start would be missed.
```

---

## Code Full Solution

```cpp
class Solution {
public:
    int M = 1e9 + 7;

    int numOfSubarrays(vector<int>& arr) {
        int n = arr.size();
        int sum = 0, count = 0;
        int odd = 0, even = 1;   // even=1 seeds the empty prefix (sum=0)

        for (int i = 0; i < n; i++) {
            sum += arr[i];

            if (sum % 2 == 0) {
                count = (count + odd) % M;
                even++;
            } else {
                count = (count + even) % M;
                odd++;
            }
        }

        return count;
    }
};
```

---

## Code Explanation

### The Two Cases

```
sum is EVEN after adding arr[i]:
  Any previous prefix with ODD sum → their difference is odd.
  Add `odd` to count.
  Then record current prefix as even: even++.

sum is ODD after adding arr[i]:
  Any previous prefix with EVEN sum → their difference is odd.
  Add `even` to count.
  Then record current prefix as odd: odd++.

Order matters: query BEFORE updating the counter.
Otherwise the current prefix would count itself.
```

---

## Full Trace: `arr = [1, 3, 5]`

```
odd=0, even=1, sum=0, count=0

i=0: sum=1 (odd)  → count+=even=1 → count=1. odd=1.
i=1: sum=4 (even) → count+=odd=1  → count=2. even=2.
i=2: sum=9 (odd)  → count+=even=2 → count=4. odd=2.

Return 4 ✓

Verification:
[1]=1✓, [3]=3✓, [5]=5✓, [1,3,5]=9✓ → 4 odd-sum subarrays
```

---

## Full Trace: `arr = [1, 2, 3, 4, 5]`

```
odd=0, even=1, sum=0, count=0

i=0: sum=1 (odd)   → count+=1=1.  odd=1.
i=1: sum=3 (odd)   → count+=1=2.  odd=2.
i=2: sum=6 (even)  → count+=2=4.  even=2.
i=3: sum=10 (even) → count+=2=6.  even=3.
i=4: sum=15 (odd)  → count+=3=9.  odd=3.

Hmm, return 9?

Let me verify manually:
[1]=1✓ [2]=2 [3]=3✓ [4]=4 [5]=5✓
[1,2]=3✓ [2,3]=5✓ [3,4]=7✓ [4,5]=9✓
[1,2,3]=6 [2,3,4]=9✓ [3,4,5]=12
[1,2,3,4]=10 [2,3,4,5]=14
[1,2,3,4,5]=15✓

Count: [1],[3],[5],[1,2],[2,3],[3,4],[4,5],[2,3,4],[1,2,3,4,5] = 9 ✓
```

---

## Example Traces

### All Even: `arr = [2, 4, 6]`

```
i=0: sum=2 (even)  → count+=odd=0=0.  even=2.
i=1: sum=6 (even)  → count+=odd=0=0.  even=3.
i=2: sum=12 (even) → count+=odd=0=0.  even=4.

Return 0 ✓
```

### Single Element: `arr = [3]`

```
i=0: sum=3 (odd) → count+=even=1 → count=1. odd=1.
Return 1 ✓  ([3] is the only subarray, and it's odd)
```

---

## Edge Cases

### Single Even Element

```
arr=[2]: sum=2 (even) → count+=odd=0. Return 0 ✓
```

### Alternating Parity

```
arr=[1,2,1,2]:
i=0: sum=1(odd)  → +=1=1.  odd=1.
i=1: sum=3(odd)  → +=1=2.  odd=2.
i=2: sum=4(even) → +=2=4.  even=2.
i=3: sum=6(even) → +=2=6.  even=3.

Return 6
```

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(n) — single pass |
| Space | O(1) — only 4 counters |

---

## Key Insight

```
The naive approach checks all O(n²) subarrays and sums each → O(n³) or O(n²).

This approach observes:
  We don't need the actual prefix values — only their PARITIES.
  Two integers are "compatible" (difference is odd) based solely on parity.

Tracking odd/even prefix counts compresses all prior information
into 2 numbers, making each step O(1).

This is the same prefix-hashmap pattern as subarray-sum=k,
but simplified: instead of a full hashmap of prefix values,
parity reduces it to just two counters.
```

---

## Connection to Subarray Sum = K

```
Subarray Sum = K (LC 560):
  For each prefix[j], count prior prefixes where prefix[i] = prefix[j] - k.
  Uses full hashmap: mpp[prefix_value] = count.

This problem (Odd Sum):
  For each prefix[j], count prior prefixes with different parity.
  Parity has only 2 states → two counters replace the full hashmap.

Same idea, simpler structure because we only care about odd/even, not exact value.
```

---

## References

- 🔗 [LeetCode 1524 — Number of Sub-arrays With Odd Sum](https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/)
- 🔗 Related: [LeetCode 560 — Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/)
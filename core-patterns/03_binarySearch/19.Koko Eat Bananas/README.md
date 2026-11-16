# Koko Eating Bananas

## Problem Link
🔗 [LeetCode 875 — Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/)

---

## What is this Problem?

There are `n` piles of bananas. Koko picks an eating speed `k` (bananas per hour) and, **each hour, picks one pile** and eats up to `k` from it. If the pile has fewer than `k` bananas she finishes it and **wastes the rest of the hour** (she does not move to another pile in the same hour). Return the **minimum** `k` that lets her finish all piles within `h` hours.

```
piles=[3,6,7,11], h=8  → Output: 4
piles=[30,11,23,4,20], h=5 → Output: 30
piles=[30,11,23,4,20], h=6 → Output: 23
```

Hours needed for one pile of size `p` at speed `k` is `ceil(p / k)` — integer division rounded up.

---

## The Idea

```
Hours needed is a function of the speed k:

    hours(k) = Σ ceil(pile / k)

  k small  → more hours   (monotonically DECREASING in k)
  k large  → fewer hours

So "is hours(k) ≤ h?" is a monotone predicate: false, false, ..., true, true.

The answer is the SMALLEST k where it becomes true →
binary search on k over the range [1, max(piles)].

  k:       1   2   3  [4]  5   6  ...
  hours:  27  15  10  8   8   6  ...

  h = 8 → first k with hours(k) ≤ 8 is 4 ✓

Going above max(piles) can never help: one pile per hour is already the
floor once k ≥ max(pile), so the range stops there.
```

---

## Code Full Solution

```cpp
class Solution {
public:
    long long calculateHrs(int k, vector<int>& piles) {
        long long totalhrs = 0;
        for(auto &el : piles) {
            totalhrs += (el / k);
            if(el % k != 0) totalhrs++;      // ceil division, no floats
        }
        return totalhrs;
    }

    int minEatingSpeed(vector<int>& piles, int h) {
        int low  = 1;
        int high = *max_element(piles.begin(), piles.end());

        while(low <= high) {
            int mid = low + (high - low) / 2;
            long long hrs = calculateHrs(mid, piles);

            if(hrs <= h) {
                high = mid - 1;      // feasible — try a slower speed
            } else {
                low = mid + 1;       // too slow — must speed up
            }
        }
        return low;
    }
};
```

---

## Code Explanation

### Ceiling Division Without Floats

```cpp
totalhrs += (el / k);
if(el % k != 0) totalhrs++;
```

`ceil(el / k)` written with integers. If `el` is not a multiple of `k`, the leftover needs one more full hour (the waste is allowed by the rules). Equivalent one-liner: `(el + k - 1) / k`.

### Search Range

```cpp
int low = 1;                                    // cannot eat 0 per hour
int high = *max_element(piles.begin(), piles.end());
```

- Below `1` is meaningless (she would never finish).
- Above `max(piles)` every pile takes exactly 1 hour, so `hours` stops improving — no need to search higher.

### The Predicate

```cpp
if(hrs <= h) high = mid - 1;
else         low  = mid + 1;
return low;
```

`hrs ≤ h` means this speed works. Since we want the **minimum** working speed, record feasibility by moving `high` left, and finish with `low` sitting on the first feasible value. This is the classic "first true" binary search — no `ans` variable needed.

### Why `long long` for `hrs`

```cpp
long long totalhrs = 0;
```

At `k = 1`, hours = sum of all piles, up to `10^4 × 10^9 = 10^{13}` — far past `int`. The function return type must be 64-bit; `h` itself is small, but the *computed* hours are not.

---

## Full Trace: `piles=[3,6,7,11]`, `h=8`

```
low=1, high=11

mid=6: hrs = ceil(3/6)+ceil(6/6)+ceil(7/6)+ceil(11/6)
           = 1 + 1 + 2 + 2 = 6
       6 <= 8 → feasible → high = 5

low=1, high=5

mid=3: hrs = 1 + 2 + 3 + 4 = 10
       10 <= 8? NO → low = 4

low=4, high=5

mid=4: hrs = 1 + 2 + 2 + 3 = 8
       8 <= 8 → feasible → high = 3

low=4 > high=3 → return 4 ✓
```

The feasibility map for reference:

```
k    :  1   2   3   4   5   6   7   8   9  10  11
hrs  : 27  15  10   8   8   6   5   5   5   5   4
                  ↑ h=8 first satisfied here

(check k=2: ceil(3/2)+ceil(6/2)+ceil(7/2)+ceil(11/2) = 2+3+4+6 = 15)
```

## Full Trace: `piles=[30,11,23,4,20]`, `h=5`

```
low=1, high=30

mid=15: hrs = 2+1+2+1+2 = 8 > 5 → low=16
mid=23: hrs = 2+1+1+1+1 = 6 > 5 → low=24
mid=27: hrs = 2+1+1+1+1 = 6 > 5 → low=28
mid=29: hrs = 2+1+1+1+1 = 6 > 5 → low=30
mid=30: hrs = 1+1+1+1+1 = 5 ≤ 5 → high=29

low=30 > high=29 → return 30 ✓
```

---

## Example Traces

### Bigger Hour Budget

```
piles=[30,11,23,4,20], h=6 → 23
mid=15: 8 > 6 → low=16
mid=23: 6 ≤ 6 → high=22
mid=19: 2+1+2+1+2 = 8 > 6 → low=20
mid=21: 2+1+2+1+1 = 7 > 6 → low=22
mid=22: 2+1+2+1+1 = 7 > 6 → low=23
low=23 > high=22 → return 23 ✓
```

### Single Pile

```
piles=[7], h=3 → answer 3 (ceil(7/3)=3 must be ≤ 3)
low=1, high=7
mid=4: ceil(7/4)=2 ≤3 → high=3
mid=2: ceil(7/2)=4 >3 → low=3
mid=3: ceil(7/3)=3 ≤3 → high=2
return 3 ✓
```

### `h` Equal to Number of Piles

```
piles=[1,1,1], h=3 → each pile needs its own hour → k=1
low=1, high=1: mid=1 → hrs = 3 ≤ 3 → high=0 → return 1 ✓
```

---

## Edge Cases

### Pile Smaller Than `k`

```
el=3, k=10 → el/k = 0, el%k != 0 → +1 → 1 hour ✓
The leftover capacity is wasted, exactly as the problem states.
```

### Largest Possible Hours

```
piles = 10^4 × 10^9, k=1 → 10^13 hours
Needs long long — an int accumulator would silently wrap ✗
```

### Very Small `h` (infeasible-looking but always solvable)

LeetCode guarantees the answer exists (`h ≥ piles.size()`), and `k = max(piles)` always gives exactly `n` hours, which is the minimum possible. So the search range `[1, max]` always contains an answer.

### Debug Print Left In

```cpp
cout<<low<<high;   // inside minEatingSpeed
```

Harmless for LeetCode (extra stdout is ignored) but noisy — delete it.

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(n · log(max(piles))) — each of the `log` steps scans all piles |
| Space | O(1) |

```
log2(10^9) ≈ 30, n ≤ 10^4 → about 3·10^5 operations. Comfortably fast.
Linear scan over k from 1 upward would be O(n · max(piles)) → far too slow.
```

---

## Key Insight

```
The question is not "search the piles" — it's "search the SPEED".

hours(k) is monotone decreasing, so the feasible set is a suffix of the speed
range. Finding the boundary of a monotone predicate is binary search, even
though nothing being searched is itself an array.
```

---

## References

- 🔗 [LeetCode 875 — Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/)
- 🔗 [LeetCode 1011 — Capacity To Ship Packages Within D Days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/) (same pattern, different story)

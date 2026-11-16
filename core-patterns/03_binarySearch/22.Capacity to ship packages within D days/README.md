# Capacity to Ship Packages Within D Days

## Problem Link
🔗 [LeetCode 1011 — Capacity To Ship Packages Within D Days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/)

---

## What is this Problem?

Packages with weights `w[i]` must be shipped **in order**, on a ship with a fixed daily capacity. Each day the ship loads packages from the front of the remaining list, as many as fit, then sails. **Packages cannot be split or reordered.** Return the **minimum capacity** that ships everything within `days` days.

```
w=[1,2,3,4,5,6,7,8,9,10], days=5  → Output: 15
w=[3,2,2,4,1,4], days=3           → Output: 6
w=[1,2,3,1,1], days=4             → Output: 3
```

For capacity `15`: `{1..5}` `{6,7}` `{8}` `{9}` `{10}` → 5 days ✓. For capacity `14` it takes 6 days, so 15 is minimal.

---

## The Idea

```
Capacity is the quantity being searched, and days-needed DECREASES with it:

  capacity small → many trips  (never smaller than the biggest package)
  capacity huge  → 1 trip      (everything in one day)

So "days needed at capacity c" is monotone non-increasing, and
"days(c) <= D" is a false...false, true...true predicate.

Answer = FIRST c where it becomes true → binary search on capacity.

Range:
  low  = max(w)      ← a package can never be split, so capacity below the
                       heaviest package is impossible
  high = Σ w         ← everything in a single day

  cap  : 10  ...  14  [15]  16  17  20  ...  55
  days :      >5   6    5    5   4   4   ...    1
                           ↑ D=5 → first feasible capacity is 15 ✓

Feasibility check is a single greedy pass: fill today's load until the next
package would overflow, then start a new day.
```

---

## Code Full Solution

```cpp
class Solution {
public:
    int find(vector<int>& w, int mid) {
        int days = 1;          // day 1 always exists
        int currW = 0;

        for(auto &el : w) {
            if(currW + el <= mid) {
                currW += el;   // fits today — load it
            } else {
                currW = el;    // start a new day with this package
                days++;
            }
        }
        return days;
    }

    int shipWithinDays(vector<int>& w, int days) {
        int low  = *max_element(w.begin(), w.end());   // heaviest package
        int high = accumulate(w.begin(), w.end(), 0);  // everything at once

        while(low <= high) {
            int mid = low + (high - low) / 2;

            if(find(w, mid) <= days) {
                high = mid - 1;   // works — try a smaller ship
            } else {
                low = mid + 1;    // too small — need more capacity
            }
        }
        return low;
    }
};
```

---

## Code Explanation

### `low = max(w)` — The Hard Lower Bound

```cpp
int low = *max_element(w.begin(), w.end());
```

A package cannot be split across days, so any capacity below the heaviest single package can never ship it. Starting there skips a whole region of infeasible capacities.

### `high = Σ w` — The Trivial Upper Bound

```cpp
int high = accumulate(w.begin(), w.end(), 0);
```

With capacity equal to the total weight, everything ships in one day. No larger capacity can help, so the search stops there. (`accumulate` on `int` is safe here: at most `500 × 5·10^4 = 2.5·10^7`.)

### The Greedy Simulation

```cpp
if(currW + el <= mid) currW += el;
else { currW = el; days++; }
```

This is the **only** correct greedy for "ship in order": you can never do better by cutting a day short, because moving a package to tomorrow cannot reduce the number of days. Note it correctly handles the case where `el` alone exceeds `mid` — though `low` guarantees that never happens during the search.

### `days = 1` to Start

```cpp
int days = 1;   // should be counted
```

The first day exists before any package is loaded. Starting at `0` would under-count by one and make the predicate too permissive.

### Returning `low`

```cpp
if(find(w, mid) <= days) high = mid - 1;
else                     low  = mid + 1;
return low;
```

Standard "first feasible value" search — no answer variable needed.

### Name Shadowing

`find` is also a `std::` algorithm name; `days` shadows nothing here but reads ambiguously against the parameter in `shipWithinDays`. Both compile fine (member function vs. `std::find`), but `packagesPerDay` / `simulate` would be clearer names.

---

## Full Trace: `w=[1,2,3,4,5,6,7,8,9,10]`, `days=5`

```
low = max(w) = 10, high = Σw = 55

mid=32: load: 1..7 = 28, +8=36 > 32 → day 2: 8+9+10 = 27 → 2 days
        2 <= 5 → high=31

mid=20: day1 1,2,3,4,5 (15), +6=21>20 → day2 6,7 (13), +8=21>20
        → day3 8,9 (17), +10=27>20 → day4 10    → 4 days
        4 <= 5 → high=19

mid=14: day1 1,2,3,4 (10), +5=15>14 → day2 5,6 (11), +7=18>14
        → day3 7, +8=15>14 → day4 8, +9=17>14 → day5 9, +10=19>14 → day6 10
        → 6 days
        6 <= 5? NO → low=15

mid=17: day1 1,2,3,4,5 (15), +6=21>17 → day2 6,7 (13), +8=21>17
        → day3 8,9 (17), +10=27>17 → day4 10   → 4 days
        4 <= 5 → high=16

mid=15: day1 1,2,3,4,5 (15), +6=21>15 → day2 6,7 (13), +8=21>15
        → day3 8, +9=17>15 → day4 9, +10=19>15 → day5 10   → 5 days
        5 <= 5 → high=14

low=15 > high=14 → return 15 ✓
```

## Full Trace: `w=[3,2,2,4,1,4]`, `days=3`

```
low=4, high=16

mid=10: day1 3+2+2=7, +4=11>10 → day2 4+1+4=9 → 2 days ≤3 → high=9
mid=6:  day1 3+2=5, +2=7>6 → day2 2+4=6 → +1=7>6 → day3 1+4=5 → 3 days ≤3 → high=5
mid=4:  day1 3, +2=5>4 → day2 2+2=4, +4=8>4 → day3 4, +1=5>4 → day4 1, +4=5>4 → day5 4
        → 5 days >3 → low=5
mid=5:  day1 3+2=5, +2=7>5 → day2 2, +4=6>5 → day3 4+1=5, +4=9>5 → day4 4
        → 4 days >3 → low=6

low=6 > high=5 → return 6 ✓
```

---

## Example Traces

### `days` Large Enough for One Package Per Day

```
w=[1,2,3,1,1], days=4 → 3
low=3, high=8
mid=5: day1 1+2=3, +3=6>5 → day2 3, +1=4, +1=5 → 2 days ≤4 → high=4
mid=3: day1 1+2=3, +3=6>3 → day2 3, +1=4>3 → day3 1, +1=2 → 3 days ≤4 → high=2
low=3 > high=2 → return 3 ✓  (capacity below the heaviest package is impossible)
```

### One Enormous Package Drives the Answer

```
w=[100,1,1,1], days=2 → 100
low=100, high=103
mid=101: day1 100+1=101, +1=102>101 → day2 1+1=2 → 2 days ≤2 → high=100
mid=100: day1 100 (adding 1 gives 101>100) → day2 1+1+1=3 → 2 days ≤2 → high=99
return 100 ✓
```

### `days` = Number of Packages

```
w=[5,5,5], days=3 → 5
low=high=5: 3 days ≤3 → high=4 → return 5 ✓
```

---

## Edge Cases

### Single Package

```
w=[7], days=1 → low=high=7 → returns 7 ✓
```

### `days` More Than Enough

The binary search still lands on `max(w)` — the tightest capacity that works — not on an arbitrarily large one ✓

### Loading Order Matters (and Is Not a Choice)

```
w=[1,2,3,1,1], capacity=4
Greedy: {1,2} {3,1} {1} → 3 days
Reordering could give {1,3} {2,1,1} → 2 days, but reordering is forbidden.
That is exactly why a greedy prefix fill is valid here.
```

### Overflow Guard

If weights could be `10^9`, `high = accumulate(...)` as `int` would overflow. Use `accumulate(w.begin(), w.end(), 0LL)`. LeetCode's `500` limit keeps `int` safe, but it costs nothing to be explicit.

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(n · log(Σw − max(w))) |
| Space | O(1) |

```
log2(2.5·10^7) ≈ 25 passes over 5·10^4 weights → ~10^6 operations.
Simulating every capacity from max(w) to Σw would be O(n · Σw) → 10^12 → too slow.
```

---

## Key Insight

```
When the answer is a single SCALAR and checking a candidate is a cheap linear
scan, binary search the scalar — not the data.

Two bounds to always look for:
  an impossible lower bound (max package)   → makes the predicate obviously false
  a trivial upper bound (total weight)      → makes the predicate obviously true

Between them the predicate flips exactly once.
```

---

## References

- 🔗 [LeetCode 1011 — Capacity To Ship Packages Within D Days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/)
- 🔗 [LeetCode 875 — Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/) (same pattern)
- 🔗 [LeetCode 410 — Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/) (same pattern)

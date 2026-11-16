# Aggressive Cows

## Problem Link
🔗 [GFG — Aggressive Cows](https://www.geeksforgeeks.org/problems/aggressive-cows/1)

---

## What is this Problem?

There are `n` stalls at positions `arr[i]` and `k` aggressive cows. Every cow gets its own stall, and cows fight if they are too close — so you want to **maximise the minimum distance between any two cows**. Return that largest possible minimum distance.

```
arr=[1,2,4,8,9], k=3  → Output: 3
arr=[10,1,2,7,5], k=3 → Output: 4
arr=[1,2,3,4,5], k=3  → Output: 2
```

For `[1,2,4,8,9]` with 3 cows: placing at `1, 4, 8` gives gaps `3` and `4` → minimum `3`. No placement achieves a minimum of 4 with 3 cows, so the answer is 3.

The array is **not sorted** — it gets sorted first, because only relative order matters.

---

## The Idea

```
Binary search on the ANSWER (the distance), not on the array.

For a candidate minimum distance d, ask: "can k cows be placed so that every
pair is at least d apart?"

Greedy check on sorted stalls:
  put the first cow at the first stall
  walk right; put the next cow at the first stall whose distance from the
  last placed cow is >= d
  count cows; if we reach k → feasible

"feasible(d)" only becomes HARDER as d grows → it is monotone:
  small d → easy (true)      large d → impossible (false)

  We want the LARGEST feasible d → find the last true.

  d   :  1  2 [3]  4  5  6  7  8
  ok  :  ✓  ✓  ✓   ✗  ✗  ✗  ✗  ✗      k=3 → last feasible is 3 ✓

Range:
  low  = 1                  ← smallest possible distance between two stalls
  high = arr[n-1] - arr[0]  ← first and last stall: the widest gap possible
```

Why the greedy is optimal: putting a cow as far left as allowed leaves the most room on the right, so if the greedy fails, no other placement can succeed.

---

## Code Full Solution

```cpp
class Solution {
  public:

    bool canWePlace(vector<int> &arr, int mid, int k) {
        int cows = 1;              // first cow at arr[0]
        int last = arr[0];
        int n = arr.size();

        for(int i = 1; i < n; i++) {
            if(arr[i] - last >= mid) {
                last = arr[i];     // place a cow here
                cows++;
            }
            if(cows == k) return true;
        }

        return false;
    }

    int aggressiveCows(vector<int> &arr, int k) {
        std::sort(arr.begin(), arr.end());
        int n = arr.size();

        int low  = 1;
        int high = arr[n-1] - arr[0];

        while(low <= high) {
            int mid = low + (high - low) / 2;

            if(canWePlace(arr, mid, k)) {
                low = mid + 1;     // feasible — try a bigger distance
            } else {
                high = mid - 1;    // too big — shrink
            }
        }
        return high;
    }
};
```

---

## Code Explanation

### Sort First

```cpp
std::sort(arr.begin(), arr.end());
```

Distances only make sense in sorted order, and the greedy walk depends on moving left to right. Note this **mutates the caller's vector** — acceptable here (GFG passes by reference expecting the work to be done), but a defensive `vector<int> s = arr;` copy would avoid surprising a caller.

### The First Cow Is Always at `arr[0]`

```cpp
int cows = 1;
int last = arr[0];
```

Placing the first cow at the leftmost stall is never worse: it leaves the entire remaining range available. This is the anchor of the greedy.

### Placing Subsequent Cows

```cpp
if(arr[i] - last >= mid) { last = arr[i]; cows++; }
```

Take the **first** stall far enough from the last placed cow. Skipping a valid nearer stall would only reduce room for later cows.

### Early Exit

```cpp
if(cows == k) return true;
```

As soon as `k` cows are placed, feasibility is proven — no need to scan the rest.

### Returning `high`, Not `low`

```cpp
if(canWePlace(...)) low = mid + 1;
else                high = mid - 1;
return high;
```

This is a "find the **last** true" search. When the loop ends, `low` has moved one past the last feasible value and `high` sits exactly on it — which is the maximum achievable distance.

```
d feasible → low climbs past it
d infeasible → high drops below it
at exit: high = last feasible, low = high + 1
```

### `high = arr[n-1] - arr[0]`

The widest possible separation uses the two extreme stalls. Any larger candidate is automatically impossible, so the search need not go higher.

---

## Full Trace: `arr=[1,2,4,8,9]`, `k=3`

```
sorted: [1,2,4,8,9]
low=1, high = 9 - 1 = 8

mid=4: cow 1 at 1, last=1
       i=1: 2-1=1 < 4
       i=2: 4-1=3 < 4
       i=3: 8-1=7 >= 4 → last=8, cows=2
       i=4: 9-8=1 < 4
       cows=2 ≠ 3 → NOT feasible → high = 3

low=1, high=3

mid=2: last=1, cows=1
       i=1: 2-1=1 < 2
       i=2: 4-1=3 >= 2 → last=4, cows=2
       i=3: 8-4=4 >= 2 → last=8, cows=3 → return true
       → low = 3

low=3, high=3

mid=3: last=1, cows=1
       i=1: 2-1=1 < 3
       i=2: 4-1=3 >= 3 → last=4, cows=2
       i=3: 8-4=4 >= 3 → last=8, cows=3 → return true
       → low = 4

low=4 > high=3 → return high = 3 ✓
```

## Full Trace: `arr=[10,1,2,7,5]`, `k=3`

```
sorted: [1,2,5,7,10]
low=1, high = 10 - 1 = 9

mid=5: last=1, cows=1
       i=1: 2-1=1 < 5
       i=2: 5-1=4 < 5
       i=3: 7-1=6 >= 5 → last=7, cows=2
       i=4: 10-7=3 < 5
       cows=2 ≠ 3 → infeasible → high=4

mid=2: 1 → 2? 2-1=1 < 2; 5-1=4 >= 2 → last=5, cows=2; 7-5=2 >= 2 → cows=3 → true
       → low=3

low=3, high=4

mid=3: 5-1=4 >= 3 → cows=2, last=5; 7-5=2 < 3; 10-5=5 >= 3 → cows=3 → true
       → low=4

low=4, high=4

mid=4: 5-1=4 >= 4 → last=5, cows=2
       7-5=2 < 4
       10-5=5 >= 4 → last=10, cows=3 → true
       → low=5

low=5 > high=4 → return high = 4 ✓
```

---

## Example Traces

### `k = 2` — The Whole Span

```
arr=[1,2,4,8,9], k=2
low=1, high=8

mid=4: 8-1=7 ≥ 4 → cows=2 → true → low=5
mid=6: 8-1=7 ≥ 6 → cows=2 → true → low=7
mid=7: 8-1=7 ≥ 7 → cows=2 → true → low=8
mid=8: 9-1=8 ≥ 8 → cows=2 → true → low=9

EXIT → high = 8 = arr[n-1] - arr[0] ✓
With only two cows the best placement is always the two extreme stalls.
```

### `k = n` — Every Stall Used

```
arr=[1,2,3,4,5], k=5
The minimum gap is forced to be the smallest adjacent gap = 1
mid sweep: d=2 fails (only 3 stalls fit: 1,3,5) → high=1 → return 1 ✓
```

### All Stalls Equally Spaced

```
arr=[1,3,5,7], k=2, possible pair distances: 2, 4, 6 → answer 6
low=1, high=6

mid=3: 5-1=4 ≥ 3 → cows=2 → true → low=4
mid=5: 7-1=6 ≥ 5 → true → low=6
mid=6: 7-1=6 ≥ 6 → true → low=7

EXIT → return high = 6 ✓
```

---

## Edge Cases

### Duplicate Stall Positions

Not present in valid input — two cows cannot share a stall. With duplicates, distance `0` would appear and `low = 1` would silently exclude it.

### `k = 1`

```
canWePlace starts with cows = 1 but only checks `cows == k` INSIDE the loop,
after an increment — so with k=1 the condition `2 == 1` never fires and every
candidate returns false → high collapses to 0 → returns 0.
GFG's constraints use k >= 2, and for one cow the answer is conceptually
unbounded, so this is a documented limitation rather than a real gap.
An early `if(k == 1) return arr[n-1] - arr[0];` would cover it.
```

### Two Stalls, Two Cows

```
arr=[3,9], k=2 → low=1, high=6
mid=3: 9-3=6 ≥ 3 → cows=2 → true → low=4
mid=5: 6 ≥ 5 → true → low=6
mid=6: 6 ≥ 6 → true → low=7
EXIT → return 6 ✓
```

### Mutation of the Input

`std::sort(arr...)` sorts in place, so the caller's array ends up sorted. Worth knowing if the caller reuses it.

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(n log n + n log(range)) — sort, then `log(range)` greedy passes |
| Space | O(1) besides the sort's internal stack |

```
range <= 10^9 → log2 ≈ 30 passes over n stalls. Fast.
Checking every possible distance from 1 to range would be O(n · range).
```

---

## Key Insight

```
Max-min problems ("maximise the minimum gap") are binary search on the answer.

  "Can I achieve a minimum distance of d?" is easy: a greedy left-to-right scan.
  And the answer is monotone: if d is achievable, so is every smaller d.

That combination — cheap monotone predicate — is the entire signal for
binary search on the answer. Then it is just a matter of finding the LAST
true instead of the first.
```

---

## References

- 🔗 [GFG — Aggressive Cows](https://www.geeksforgeeks.org/problems/aggressive-cows/1)
- 🔗 [SPOJ — AGGRCOW](https://www.spoj.com/problems/AGGRCOW/)
- 🔗 [LeetCode 1552 — Magnetic Force Between Two Balls](https://leetcode.com/problems/magnetic-force-between-two-balls/) (identical problem)

# Painter's Partition Problem

## Problem Link
🔗 [GFG — The Painter's Partition Problem-II](https://www.geeksforgeeks.org/problems/the-painters-partition-problem1535/1)

---

## What is this Problem?

`nums[i]` is the time needed to paint the `i`-th board. There are `k` painters, and each painter takes a **contiguous** run of boards (no skipping, no sharing). The painters work **in parallel**, so the total time is the **slowest painter's total**. Minimise that maximum.

```
nums=[5,10,30,20,15], k=3  → Output: 35
nums=[10,20,30,40],   k=2  → Output: 60
nums=[5,5,5,5],       k=2  → Output: 10
```

For `[5,10,30,20,15]` with 3 painters: `{5,10}=15`, `{30}=30`, `{20,15}=35` → max **35**. No split gets below 35, because `30` and `20` must land somewhere and 20 costs 35 with its neighbour or 20 alone — but 20 alone pushes 30 with 15 or 5.

Identical to **Book Allocation** and **Split Array Largest Sum**: contiguous parts, minimise the maximum part sum.

---

## The Idea

```
Binary search on the ANSWER (minutes per painter), not on the boards.

"minPainters(limit)": fewest painters needed if no painter may exceed `limit`.
Greedy: give the current painter boards until the next one would overflow,
then start a new painter.

  limit small → many painters     (below max(nums): impossible)
  limit large → 1 painter

"minPainters(limit) <= k" flips once from false to true
→ find the FIRST feasible limit.

Range:
  low  = max(nums)   ← one board must be finishable by one painter
  high = Σ nums      ← one painter does every board

  limit     : 30 ...  34  [35] 36 ...  80
  painters  :  4       4     3    3      1     k = 3 → answer 35 ✓
```

Since painters work simultaneously, we never need to balance the load beyond keeping every painter under the cap — that is precisely what the predicate checks.

---

## Code Full Solution

```cpp
int solve(vector<int> &nums, int mid, int n) {
    int hrs = 0;                 // time for the current painter
    int painters = 1;            // first painter exists

    for(int i = 0; i < n; i++) {
        if(nums[i] + hrs <= mid) {
            hrs += nums[i];      // this board still fits
        } else {
            hrs = nums[i];       // hand it to a new painter
            painters++;
        }
    }
    return painters;
}

int findLargestMinDistance(vector<int> &nums, int k)
{
    int n = nums.size();
    int low  = *max_element(nums.begin(), nums.end());   // biggest board
    int high = accumulate(nums.begin(), nums.end(), 0);  // all boards

    while(low <= high) {
        int mid = low + (high - low) / 2;
        int painters = solve(nums, mid, n);

        if(painters <= k) {
            high = mid - 1;      // feasible — try a smaller cap
        } else {
            low = mid + 1;       // too many painters — raise the cap
        }
    }
    return low;
}
```

---

## Code Explanation

### `low = max(nums)` — The Hard Lower Bound

A board cannot be shared between painters, so any cap below the longest board makes every split infeasible. Starting at `max` skips a whole false region.

### `high = Σ nums` — The Trivial Upper Bound

One painter takes every board, always `<= k` painters. No larger cap helps.

### The Greedy Assignment

```cpp
if(nums[i] + hrs <= mid) hrs += nums[i];
else { hrs = nums[i]; painters++; }
```

Load the current painter as much as possible before moving on. A painter who stops early just hands work to the next one — the number of painters can only grow, never shrink — so the greedy gives the minimum painter count for that cap.

`hrs = nums[i]`, not `hrs += nums[i]`: the new painter starts fresh with this board.

### `painters = 1`

The first painter is already working before any board is assigned. Starting at `0` would make the predicate accept caps that need one more painter than `k`.

### `<= k`, Not `== k`

Handing some painter fewer boards is always legal, and splitting a load further never raises the maximum. So any solution using **at most** `k` painters can be padded to exactly `k` (idle painters), while using more than `k` is genuinely infeasible.

### The Misleading Function Name

```cpp
int findLargestMinDistance(vector<int> &nums, int k)
```

The name echoes the "largest minimum distance" template, but this problem **minimises a maximum**, not maximises a minimum. The mechanism is the same; only the direction of the predicate and `low`/`high` swap. Worth renaming to `minTimeToPaint` if you keep the file.

### Returning `low`

```cpp
if(painters <= k) high = mid - 1;
else              low  = mid + 1;
return low;
```

"First true" search — the smallest cap that still fits in `k` painters.

---

## Full Trace: `nums=[5,10,30,20,15]`, `k=3`

```
low = 30, high = 80

mid=55: {5,10,30}=45, +20=65 > 55 → {20,15}=35 → 2 ≤ 3 → high=54

low=30, high=54
mid=42: {5,10}=15, +30=45 > 42 → {30}, +20=50 > 42 → {20,15}=35
        → 3 ≤ 3 → high=41

low=30, high=41
mid=35: {5,10}=15, +30=45 > 35 → {30}, +20=50 > 35 → {20,15}=35
        → 3 ≤ 3 → high=34

low=30, high=34
mid=32: {5,10}=15, +30 > 32 → {30}, +20 > 32 → {20}, +15=35 > 32 → {15}
        → 4 > 3 → low=33

low=33, high=34
mid=33: same → 4 > 3 → low=34

low=34, high=34
mid=34: same → 4 > 3 → low=35

low=35 > high=34 → return 35 ✓
```

## Full Trace: `nums=[10,20,30,40]`, `k=2`

```
low = 40, high = 100

mid=70: {10,20,30}=60, +40=100 > 70 → {40} → 2 ≤ 2 → high=69

low=40, high=69
mid=54: {10,20}=30, +30=60 > 54 → {30}, +40=70 > 54 → {40}
        → 3 > 2 → low=55

low=55, high=69
mid=62: {10,20,30}=60, +40 > 62 → {40} → 2 ≤ 2 → high=61
mid=58: {10,20}=30, +30 > 58 → {30}, +40 > 58 → {40} → 3 > 2 → low=59
mid=60: {10,20,30}=60, +40 > 60 → {40} → 2 ≤ 2 → high=59
mid=59: {10,20}=30, +30 > 59 → {30}, +40 > 59 → {40} → 3 > 2 → low=60

low=60 > high=59 → return 60 ✓   ({10,20,30} + {40})
```

---

## Example Traces

### Uniform Boards

```
nums=[5,5,5,5], k=2 → 10
low=5, high=20
mid=12: {5,5}, {5,5} → 2 ≤ 2 → high=11
mid=8:  {5}, {5}, {5}, {5} → 4 > 2 → low=9
mid=10: {5,5}, {5,5} → 2 ≤ 2 → high=9
mid=9:  4 painters > 2 → low=10
return 10 ✓
```

### `k = 1` — One Painter, Full Sum

```
nums=[5,10,30,20,15], k=1 → 80
Every cap < 80 needs ≥ 2 painters, so low climbs to Σnums → return 80 ✓
```

### `k >= n` — One Board Each

```
nums=[10,20], k=5 → 20
low=20, high=30
mid=25: {10,20}=30 > 25 → {10}, {20} → 2 ≤ 5 → high=24
mid=22: same → 2 ≤ 5 → high=21
mid=20: {10}, {20} → 2 ≤ 5 → high=19
return low=20 ✓   (idle painters are fine — the cap is just max(nums))
```

---

## Edge Cases

### `k = 0`

Not guarded. Every cap would need at least 1 painter, the predicate never passes, and `low` overshoots to `Σnums + 1`. GFG constraints use `k >= 1`.

### Single Board

```
nums=[7], k=1 → low=high=7 → returns 7 ✓
```

### Empty/n=0 input

`*max_element` on an empty vector is undefined behaviour; constraints guarantee `n >= 1`.

### Sum Overflow

`accumulate(nums.begin(), nums.end(), 0)` accumulates in `int`. If board times can reach `10^5` each with `10^5` boards the total is `10^10` and overflows — use `0LL`.

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(n · log(Σnums − max(nums))) |
| Space | O(1) |

```
n ≤ 10^5, times ≤ 10^5 → range ≈ 10^10, log2 ≈ 34 greedy passes over n boards.
Brute force over every cap would be O(n · Σ) → unusable.
```

---

## Key Insight

```
Contiguous partition into at most k parts, minimise the largest part sum —
one skeleton serves at least four classic problems:

  ship packages in D days      (part = a day's load)
  split array largest sum      (part = a subarray)
  allocate books to students   (part = a student's pages)
  painter's partition          (part = a painter's boards)

All four: low = max element, high = sum, greedy count of parts,
binary search for the FIRST cap whose part count fits.
```

---

## References

- 🔗 [GFG — The Painter's Partition Problem-II](https://www.geeksforgeeks.org/problems/the-painters-partition-problem1535/1)
- 🔗 [LeetCode 410 — Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/)
- 🔗 [LeetCode 1011 — Capacity To Ship Packages Within D Days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/)

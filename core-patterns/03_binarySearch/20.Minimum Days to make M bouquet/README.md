# Minimum Number of Days to Make m Bouquets

## Problem Link
🔗 [LeetCode 1482 — Minimum Number of Days to Make m Bouquets](https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/)

---

## What is this Problem?

`bloomDay[i]` is the day flower `i` blooms. To make **one** bouquet you need exactly `k` flowers that are **adjacent** in the array and all bloomed. Return the **minimum number of days** needed to make `m` bouquets, or `-1` if impossible.

```
bloomDay=[1,10,3,10,2], m=3, k=1  → Output: 3
bloomDay=[1,10,3,10,2], m=3, k=2  → Output: -1
bloomDay=[7,7,7,7,12,7,7], m=2, k=3 → Output: 12
```

On day `d`, every flower with `bloomDay[i] <= d` is open. A run of `k` consecutive open flowers becomes one bouquet, and the run resets.

---

## The Idea

```
"Days" is the thing being searched, not the array.

For a candidate day d, count how many bouquets can be made — a single greedy
left-to-right pass:

    walk the array; keep a counter of CONSECUTIVE open flowers
    whenever it reaches k → +1 bouquet, reset the counter to 0
    any closed flower → counter resets to 0

bouquets(d) only GROWS as d grows → the predicate "bouquets(d) >= m" is
monotone: false ... false, true ... true.

The answer is the FIRST d where it flips →
binary search over days in [min(bloomDay), max(bloomDay)].

  day:       1  2  3  4 ... 12
  bouquets:  0  0  3  3 ...  2     (k=1, m=3 → first day with 3 is day 3)
```

Why the range stops at `max(bloomDay)`: waiting longer never opens another flower.

---

## Code Full Solution

```cpp
class Solution {
public:
    int calculateBouquet(vector<int>& bloomDay, int k, int mid) {
        int consecutive_cnt = 0;
        int bouque_cnt = 0;

        for(auto &el : bloomDay) {
            if(el <= mid) {
                consecutive_cnt++;
            } else {
                consecutive_cnt = 0;
            }
            if(consecutive_cnt == k) {
                bouque_cnt++;
                consecutive_cnt = 0;      // this run is used up
            }
        }
        return bouque_cnt;
    }

    int minDays(vector<int>& bloomDay, int m, int k) {
        int low  = *min_element(bloomDay.begin(), bloomDay.end());
        int high = *max_element(bloomDay.begin(), bloomDay.end());

        int minDays = -1;
        while(low <= high) {
            int mid = low + (high - low) / 2;
            int bouquetMade = calculateBouquet(bloomDay, k, mid);

            if(bouquetMade >= m) {
                minDays = mid;        // works — record and try earlier
                high = mid - 1;
            } else {
                low = mid + 1;        // too early — wait longer
            }
        }
        return minDays;
    }
};
```

---

## Code Explanation

### The Greedy Counter

```cpp
if(el <= mid) consecutive_cnt++;
else          consecutive_cnt = 0;
```

`consecutive_cnt` is the length of the current streak of bloomed flowers. A closed flower breaks the streak — adjacency is required, so the count must restart at `0`, not at `1`.

### Cutting a Bouquet

```cpp
if(consecutive_cnt == k) {
    bouque_cnt++;
    consecutive_cnt = 0;
}
```

The moment `k` consecutive open flowers exist, one bouquet is formed and those flowers are consumed — so the streak restarts. Using `>= k` with a `-= k` would also be correct and keeps a longer run usable:

```
run of 6 open, k=3
  == k, reset  → bouquets: 3,3 → 1, then 3 → 2 bouquets ✓
  -= k         → 6-3=3 → bouquets: 1, then 2 ✓
Both agree here; resetting is simpler and never loses a bouquet because
the counter always stops exactly at k.
```

### Search Range

```cpp
int low  = *min_element(...);   // no flower is open before the earliest bloom
int high = *max_element(...);   // everything open
```

Starting at `min(bloomDay)` instead of `1` skips days where nothing can bloom — a pure speed-up, not a correctness requirement.

### Recording the Answer

```cpp
if(bouquetMade >= m) { minDays = mid; high = mid - 1; }
```

This is "find the **first** true", so the feasible day is stored and the search continues left, unlike Koko's version which returns `low` directly. Both work; the explicit `minDays` makes the `-1` case natural.

### Where `-1` Comes From

If `m * k > bloomDay.size()` no day can ever produce enough bouquets. Then `bouquetMade >= m` is never true, `minDays` stays `-1`, and it is returned. No explicit check needed (though `if((long long)m * k > n) return -1;` up front is a common optimisation).

---

## Full Trace: `bloomDay=[1,10,3,10,2], m=3, k=1`

```
low = 1, high = 10

mid=5: open (≤5): 1 ✓, 10 ✗, 3 ✓, 10 ✗, 2 ✓
       k=1 → every open flower is its own bouquet → 3 bouquets
       3 >= 3 → minDays=5, high=4

low=1, high=4

mid=2: open: 1 ✓, 10 ✗, 3 ✗, 10 ✗, 2 ✓ → 2 bouquets
       2 >= 3? NO → low=3

low=3, high=4

mid=3: open: 1 ✓, 10 ✗, 3 ✓, 10 ✗, 2 ✓ → 3 bouquets
       3 >= 3 → minDays=3, high=2

low=3 > high=2 → return 3 ✓
```

## Full Trace: `bloomDay=[1,10,3,10,2], m=3, k=2` (impossible)

```
low=1, high=10

mid=5: streaks at day 5: [1] then break (10) then [1] then break(10) then [1]
       longest streak = 1 < k=2 → 0 bouquets
       0 >= 3? NO → low=6

mid=8: same layout → 0 bouquets → low=9
mid=9: 0 bouquets → low=10
mid=10: all open → streak 5 → k=2 → bouquets: 2 (uses 4 flowers), leftover 1
        2 >= 3? NO → low=11

low=11 > high=10 → minDays never set → return -1 ✓
```

## Full Trace: `bloomDay=[7,7,7,7,12,7,7], m=2, k=3`

```
low=7, high=12

mid=9: open (≤9): 7,7,7,7, ✗, 7,7
       streak: 1,2,3 → bouquet #1, reset; 1; break; 1,2
       1 bouquet < 2 → low=10

mid=11: same open set → 1 bouquet < 2 → low=12

mid=12: all open → streak 1,2,3 → bouquet #1, reset
        1,2,3 → bouquet #2
        2 >= 2 → minDays=12, high=11

low=12 > high=11 → return 12 ✓
```

---

## Example Traces

### A Single Bouquet From the First Day

```
bloomDay=[1,2,3], m=1, k=3 → answer 3
day 1: only flower 0 open → streak 1
day 2: flowers 0,1 → streak 2
day 3: all → streak 3 → 1 bouquet ✓
Bouquets need adjacency, so m=1, k=3 answers with max(bloomDay) here.
```

### `k = 1`, `m` Equals Length

```
bloomDay=[5,1,3], m=3, k=1 → answer 5 (every flower must be open)
mid sweeps: day 3 gives 2 bouquets, day 5 gives 3 ✓
```

### Adjacency Really Matters

```
bloomDay=[1,1,1,100,1,1,1], m=2, k=3
day 1 → one run of 3 → 1 bouquet, then a run of 3 → 2 bouquets ✓
The 100 in the middle splits the array, but each side supplies a bouquet.
```

---

## Edge Cases

### Impossible Request

`m * k > n` → `-1` (see trace above). Note `m*k` can overflow `int` for large inputs — cast to `long long` if you add the explicit check.

### `k` Larger Than Any Streak

Never reaches `k` → `0` bouquets every day → `-1` ✓

### Duplicate Bloom Days

Fine — `el <= mid` compares values only; ties are all open together.

### Late Blooming Flower Inside a Run

```
[1,1,100,1,1], k=2 → day 1: run [1,1] → 1 bouquet, break at 100, then run [1,1] → 2 bouquets
The break resets consecutive_cnt to 0, so the two sides are counted separately ✓
```

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(n · log(max(bloomDay) − min(bloomDay) + 1)) |
| Space | O(1) |

```
Each binary-search step does one O(n) greedy pass.
log2(10^9) ≈ 30 → about 30n operations, well within limits.
Simulating day 1..max and recounting each time would be O(n · maxDay) — too slow.
```

---

## Key Insight

```
The days are a monotone coordinate: more days can only help.

So the question "what is the earliest day on which m bouquets exist?" is
exactly "where does a monotone predicate become true?" — and the predicate
itself is just a greedy count, which is cheap because bouquets are formed
left to right the instant a run reaches k.
```

---

## References

- 🔗 [LeetCode 1482 — Minimum Number of Days to Make m Bouquets](https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/)
- 🔗 [LeetCode 875 — Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/) (same binary-search-on-answer pattern)

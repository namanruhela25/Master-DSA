# Minimum Distance Between Gas Stations

## Problem Link
🔗 [GFG — Minimize Max Distance to Gas Station](https://www.geeksforgeeks.org/problems/minimize-max-distance-to-gas-station/1)

*(LeetCode 774 — Minimize Max Distance to Gas Station — is the premium version of the same problem.)*

---

## What is this Problem?

`arr` holds the positions of existing gas stations on a number line, **in sorted order**. You may add `k` more stations at **any real positions**. Minimise the **maximum distance between two adjacent stations** after all `k` are added. Return that minimum possible maximum distance.

```
arr=[1,2,8], k=1      → Output: 3
arr=[1,2,3,4,5], k=2  → Output: 0.5
arr=[1,2,3,4,5,6,7,8,9,10], k=9 → Output: 0.5
```

For `[1,2,8]` with 1 new station: the gap `1→8` is 6. Putting the station at `4.5` gives gaps `3.5` and `3.5`... better is `2→8` split in half → `3` and `3`, with the max being **3** (the `1→2` gap is 1). So the answer is 3.

Key constraints from the statement: existing stations cannot be moved, new stations may be placed anywhere (non-integer coordinates are allowed), and the answer only depends on the **gaps between consecutive existing stations**.

---

## The Idea

```
Only the gaps matter:
    arr = [1, 2, 8]  →  gaps = [1, 6]

Putting s new stations into a gap of length L splits it into s+1 equal parts,
each of length L / (s + 1). Equal parts are always optimal — any uneven split
just makes one part the new maximum.

So the question becomes:
    distribute k extra stations among the gaps so that max over gaps of
    L / (count+1) is minimised.

Greedy (this code): always split the CURRENTLY LARGEST section.

    push every gap into a MAX-HEAP keyed by its current section length
    repeat k times:
        pop the largest section
        add one station to it  (count[i]++)
        its new section length = originalGap[i] / (count[i] + 1)
        push it back
    answer = the largest section remaining = heap top

  gaps=[1,6], k=1
    heap: (6, gap1) is largest → split → 6/2 = 3 → push 3
    heap: (3, gap1), (1, gap0) → answer 3 ✓
```

Why greedy works: splitting the largest section is the only move that can lower the overall maximum; splitting a smaller one leaves the largest untouched, so the answer cannot improve. Each greedy step is locally forced.

Binary search alternative (also O(log) passes, no heap): binary search the answer `d ∈ [0, maxGap]`; for each gap, the stations needed is `ceil(L / d) - 1`; feasible when the total ≤ k. Find the smallest feasible `d`.

---

## Code Full Solution

```cpp
#include<bits/stdc++.h>
double minimiseMaxDistance(vector<int> &arr, int k) {
    int n = arr.size();
    vector<int> howMany(n - 1, 0);                 // stations added per gap

    priority_queue<pair<long double,int>> pq;      // (section length, gap index)
    for(int i = 0; i < n - 1; i++) {
        pq.push({arr[i + 1] - arr[i], i});
    }

    for(int station = 1; station <= k; station++) {
        auto tp = pq.top();
        pq.pop();

        int secInd = tp.second;
        howMany[secInd]++;                         // one more station here

        long double iniDiff = arr[secInd + 1] - arr[secInd];
        long double secLength = iniDiff / (howMany[secInd] + 1);
        pq.push({secLength, secInd});
    }

    return pq.top().first;                         // largest section left
}
```

---

## Code Explanation

### `howMany` — Stations Per Gap

```cpp
vector<int> howMany(n - 1, 0);
```

A gap `i` (between `arr[i]` and `arr[i+1]`) is divided into `howMany[i] + 1` equal sections. This counter is what converts "one more station" into "one more piece".

### The Max-Heap

```cpp
priority_queue<pair<long double,int>> pq;
```

`priority_queue` is a max-heap by default, so `top()` is the largest section. The pair's second component (gap index) is only a tiebreaker — it makes the ordering total so the heap is deterministic.

`long double` avoids accumulating floating-point error across many divisions.

### Seeding With the Original Gaps

```cpp
for(int i = 0; i < n - 1; i++) pq.push({arr[i + 1] - arr[i], i});
```

Before any station is added, every section is just an original gap.

### The k-Step Greedy

```cpp
for(int station = 1; station <= k; station++) {
    auto tp = pq.top(); pq.pop();
    int secInd = tp.second;
    howMany[secInd]++;
    long double iniDiff = arr[secInd + 1] - arr[secInd];
    long double secLength = iniDiff / (howMany[secInd] + 1);
    pq.push({secLength, secInd});
}
```

Each iteration spends exactly one station on the largest current section. Note the section length is recomputed from the **original** gap and the new count — never from the previous section length — so there is no compounding rounding error.

The `station` variable is unused inside the body; `for(int _ = 0; _ < k; _++)` would read cleaner.

### Returning the Heap Top

```cpp
return pq.top().first;
```

After all `k` stations are placed, the largest section in the heap is exactly the maximum adjacent distance — the value being minimised.

### Complexity of the Heap Approach

`O((n + k) log n)`. When `k` is huge (`10^9`), this is far too slow — that is exactly why the binary-search formulation exists (`O(n log(maxGap/eps))`, independent of `k`).

---

## Full Trace: `arr=[1,2,8]`, `k=1`

```
gaps: gap0 = 2-1 = 1, gap1 = 8-2 = 6
howMany = [0, 0]

heap: (6, gap1), (1, gap0)      top = 6

station 1:
  pop (6, gap1)
  howMany[1] = 1
  secLength = 6 / (1+1) = 3
  push (3, gap1)

heap: (3, gap1), (1, gap0)      top = 3

→ return 3.0 ✓        place the station at 5: gaps 1, 3, 3
```

## Full Trace: `arr=[1,2,8]`, `k=2`

```
gaps = [1, 6], howMany = [0, 0]

station 1: largest is 6 (gap1) → howMany[1]=1 → 6/2 = 3 → push (3, gap1)
station 2: largest is 3 (gap1) → howMany[1]=2 → 6/3 = 2 → push (2, gap1)

heap: (2, gap1), (1, gap0) → return 2.0 ✓   (stations at 4 and 6)
```

---

## Example Traces

### Uniform Gaps, `k` Less Than the Gap Count

```
arr=[1,2,3,4,5], k=2
gaps = [1,1,1,1] → heap has four 1s

station 1: pop (1, gap0) → howMany[0]=1 → 1/2 = 0.5 → push (0.5, gap0)
station 2: pop (1, gap1) → howMany[1]=1 → 0.5 → push (0.5, gap1)

heap top = 1 (gap2 / gap3 untouched) → return 1.0 ✓
```

### Uniform Gaps, One Station in Every Gap

```
arr=[1..10], k=9
nine gaps of 1, k=9

Each iteration pops a 1 and pushes 0.5, so all nine gaps become 0.5.
heap top = 0.5 → return 0.5 ✓
```

### One Dominant Gap

```
arr=[0,100], k=3
gaps = [100]
station1: 100/2 = 50
station2: 50  → 100/3 ≈ 33.33
station3: 33.33 → 100/4 = 25
→ return 25.0 ✓   (four equal sections of 25)
```

### Two Very Different Gaps

```
arr=[0,1,100], k=2
gaps = [1, 99]
station1: top is 99 (gap1) → howMany[1]=1 → 99/2 = 49.5 → push (49.5, gap1)
station2: top is 49.5 (gap1) → howMany[1]=2 → 99/3 = 33 → push (33, gap1)
heap: (33, gap1), (1, gap0) → return 33.0 ✓   (max of 33 and 1)
Both stations go into the same gap, because that gap stays the largest.
```

---

## Edge Cases

### `k = 0`

The loop body never runs and the function returns the largest original gap ✓. (GFG constraints use `k >= 1`, but the behaviour is still correct.)

### Two Stations Only

```
arr=[1,10], k=1 → gaps=[9] → 9/2 = 4.5 ✓
```

### Duplicate Positions

A gap of `0` sits in the heap with length 0 and is never chosen while any positive gap exists ✓. (Not valid input per the constraints.)

### Very Large `k`

The heap loop is `O(k log n)` — with `k = 10^9` it will time out. Switch to the binary search on the answer:

```cpp
double low = 0, high = maxGap;
for(int iter = 0; iter < 100; iter++) {
    double mid = (low + high) / 2;
    int needed = 0;
    for(int i = 0; i + 1 < n; i++) {
        int gap = arr[i+1] - arr[i];
        needed += (int)ceil(gap / mid) - 1;     // stations to make sections <= mid
    }
    if(needed <= k) high = mid; else low = mid;
}
return high;
```

100 fixed iterations avoid the classic pitfall of `while(high - low > 1e-6)` — with gaps up to `10^9`, that condition can loop hundreds of times or, in float form, never terminate.

### Precision

GFG accepts answers within `1e-6`. The heap approach is exact up to `long double` precision, and returning the stored section length (rather than recomputing) keeps it stable.

---

## Time and Space Complexity

| Approach | Time | Space |
|---|---|---|
| Max-heap (this code) | O((n + k) log n) | O(n) |
| Binary search on the answer | O(n · iterations) | O(1) |

```
Heap: n gaps seeded, then one pop+push per station.
Binary search: ~60-100 passes over n gaps, independent of k.
When k is up to 10^5 the heap is fine; when k is up to 10^9 only BS is viable.
```

---

## Key Insight

```
"Split the biggest gap" is a greedy that is easy to see but expensive to run
once per station. Rewrite it as a decision problem instead:

    given a candidate max distance d, can k stations achieve it?
    gap L needs ceil(L/d) - 1 stations.

The predicate is monotone in d, so binary search d. Whenever a greedy repeats
"pick the largest / smallest" k times, look for a counting predicate over the
answer instead — that is the same trade-off as heap-Dijkstra vs. binary-searched
edge weights.
```

---

## References

- 🔗 [GFG — Minimize Max Distance to Gas Station](https://www.geeksforgeeks.org/problems/minimize-max-distance-to-gas-station/1)
- 🔗 [LeetCode 774 — Minimize Max Distance to Gas Station](https://leetcode.com/problems/minimize-max-distance-to-gas-station/) (premium)
- 🔗 [LeetCode 1552 — Magnetic Force Between Two Balls](https://leetcode.com/problems/magnetic-force-between-two-balls/) (the max-min mirror image)

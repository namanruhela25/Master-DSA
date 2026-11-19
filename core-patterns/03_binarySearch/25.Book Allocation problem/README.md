# Book Allocation Problem

## Problem Link
🔗 [GFG — Allocate Minimum Number of Pages](https://www.geeksforgeeks.org/problems/allocate-minimum-number-of-pages0937/1)

---

## What is this Problem?

`arr[i]` is the number of pages in the `i`-th book, and `m` students must each get a **contiguous** block of books. Every book goes to exactly one student, every student gets at least one book, and **a block cannot be split** across students. Minimise the **maximum pages given to any one student**.

```
arr=[12,34,67,90], m=2   → Output: 113
arr=[25,46,28,49,24], m=4 → Output: 71
arr=[15,17,20], m=2       → Output: 32
```

For `[12,34,67,90]` with 2 students: `{12,34} = 46` and `{67,90} = 157` → max `157`; `{12,34,67} = 113` and `{90}` → max `113`; `{12}` and `{34,67,90} = 191` → max `191`. The best split is the middle one, so the answer is **113**.

If `m > n` the problem is impossible — some student would get zero books — and the answer is `-1`.

---

## The Idea

```
Binary search on the ANSWER (pages per student), not on the array.

"canFinish(p)": with a cap of p pages per student, how many students do we
need? Walk the books left to right, keep filling the current student until
the next book would overflow the cap, then open a new student.

Fewer books per student → MORE students needed. So:

  p small → students(n) large     (p below the biggest book: impossible)
  p large → students = 1

"students(p) <= m" is a false...false, true...true predicate.
Answer = FIRST p where it becomes true.

Range:
  low  = max(arr)      ← the biggest single book must fit in one student's block
  high = Σ arr         ← one student takes every book

  p    : 90 ... 112  [113] 114 ... 195
  stds :  4     3      2     2       1      m = 2 → first feasible = 113 ✓
```

Two things make this the same problem as **Capacity to Ship Packages** and **Aggressive Cows**:

1. Order is fixed, so a greedy prefix fill is the only choice — no reordering to exploit.
2. The predicate is monotone in the guess, so binary search applies.

---

## Code Full Solution

```cpp
int possible(vector<int>& arr, int m, int mid) {
    int std = 1;               // first student exists
    int allocatedPages = 0;

    for(auto &p : arr) {
        if(p + allocatedPages <= mid) {
            allocatedPages += p;   // fits with the current student
        } else {
            allocatedPages = p;    // start a new student with this book
            std++;
        }
    }
    return std;
}

int findPages(vector<int>& arr, int n, int m) {
    if(m > arr.size()) return -1;

    int low  = *max_element(arr.begin(), arr.end());      // biggest book
    int high = accumulate(arr.begin(), arr.end(), 0);     // all books

    while(low <= high) {
        int mid = low + (high - low) / 2;
        int stduents = possible(arr, m, mid);

        if(stduents <= m) {
            high = mid - 1;    // feasible — try a tighter cap
        } else {
            low = mid + 1;     // too tight — allow more pages
        }
    }
    return low;
}
```

---

## Code Explanation

### `if(m > arr.size()) return -1;`

Each student needs at least one book, so more students than books cannot be satisfied. This is the only `-1` case.

### `low = max(arr)` — The Hard Lower Bound

```cpp
int low = *max_element(arr.begin(), arr.end());
```

Books cannot be split. If the cap is smaller than the heaviest book, the student holding it always overflows — the predicate is false for every such cap, so skip them all.

### `high = Σ arr` — The Trivial Upper Bound

```cpp
int high = accumulate(arr.begin(), arr.end(), 0);
```

One student takes everything, which always works. Larger caps cannot improve the answer.

### The Greedy Fill

```cpp
if(p + allocatedPages <= mid) allocatedPages += p;
else { allocatedPages = p; std++; }
```

Fill the current student as much as possible before starting a new one. Cutting a student's block short can only push books to later students and **cannot reduce the number of students**, so the greedy uses the minimum students for a given cap. That is exactly the question the predicate asks.

Note `allocatedPages = p` (not `+= p`): the new student begins with this book.

### The Unused Parameter Is Harmless

```cpp
int possible(vector<int>& arr, int m, int mid)   // m is never read
```

`m` is dead inside `possible`. It compiles fine but the two branches of the search already encode the decision — removing the parameter would make that clearer.

### `possible` Never Returns More Than `n`

Since `low >= max(arr)`, no book alone exceeds the cap, so each book fits at least alone and `std <= n`. The `std = 1` init plus one increment per split is exact, never off by one.

### Returning `low`

```cpp
if(stduents <= m) high = mid - 1;
else              low  = mid + 1;
return low;
```

Standard "first feasible value" search. When the loop exits, `low` sits one past `high` and holds the first cap that works.

---

## Full Trace: `arr=[12,34,67,90]`, `m=2`

```
low = 90, high = 203

mid = 146: {12,34,67}=113, +90=203 > 146 → new student, 90
           students = 2 ≤ 2 → high = 145

low=90, high=145
mid = 117: {12,34,67}=113, +90 > 117 → new student, 90
           students = 2 ≤ 2 → high = 116

low=90, high=116
mid = 103: {12,34,67}=113 > 103 → break at 67 → {12,34}=46 then {67} then 90
           students = 3 > 2 → low = 104

low=104, high=116
mid = 110: {12,34}=46, +67=113 > 110 → {67}, +90=157 > 110 → {90}
           students = 3 > 2 → low = 111

low=111, high=116
mid = 113: {12,34,67}=113, +90 > 113 → {90}
           students = 2 ≤ 2 → high = 112

low=111, high=112
mid = 111: {12,34,67}=113 > 111 → {12,34}=46, {67}, {90} → 3 students → low=112

low=112, high=112
mid = 112: 3 students > 2 → low = 113

low=113 > high=112 → return 113 ✓
```

## Full Trace: `arr=[25,46,28,49,24]`, `m=4`

```
low = 49, high = 172

mid=110: {25,46,28}=99, +49 > 110 → {49,24}=73 → 2 students ≤ 4 → high=109
mid=79:  {25,46}=71, +28=99 > 79 → {28,49}=77, +24=101 > 79 → {24}
         → 3 students ≤ 4 → high=78
mid=63:  {25,46}=71 > 63 → {25}, {46}, {28,49}=77 > 63 → {28}, {49}, {24}
         → 5 students > 4 → low=64
mid=71:  {25,46}=71, +28 > 71 → {28}, {49}, {24}
         → 4 students ≤ 4 → high=70
low=71 > high=70 → return 71 ✓
```

---

## Example Traces

### `m = 1` — One Student Takes All

```
arr=[15,17,20], m=1 → 52
low=20, high=52
Every mid < 52 makes `possible` return ≥ 2, so low climbs up to 52 → return 52 ✓
```

### `m = n` — One Book Each

```
arr=[15,17,20], m=3 → 20 = max(arr)
low=high=20 → possible: each book its own student → 3 ≤ 3 → high=19 → return 20 ✓
```

### The `m > n` Guard

```
arr=[10,20], m=3
m > arr.size() → return -1 ✓   (no cap can give every student a book)
```

### Two Books

```
arr=[5,9], m=2 → 9
low=9, high=14
mid=11: {5,9}=14 > 11 → {5}, {9} → 2 ≤ 2 → high=10
mid=9:  {5} (5+9=14 > 9), {9} → 2 ≤ 2 → high=8
return low=9 ✓
```

---

## Edge Cases

### `m == 0`

Not guarded. `possible` would return `n >= 1` students for every cap, so the predicate never passes, `low` runs past `high` and the function returns `Σarr + 1` instead of `-1`. GFG constraints use `m >= 1`, but `if(m == 0 || m > arr.size()) return -1;` costs nothing.

### Empty Array

`*max_element` on an empty vector is undefined behaviour. Guarded in practice by the `m > arr.size()` check only when `m >= 1` and `arr` is empty — which does trigger the early return. Adding an explicit `n == 0` check is safer.

### Large Totals

`accumulate(arr.begin(), arr.end(), 0)` sums in `int`. Sums above `2^31` would overflow; `0LL` avoids it if the constraints ever grow.

### Duplicate / Zero Page Counts

Handled naturally — a book of `0` pages never forces a split.

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(n · log(Σarr − max(arr))) |
| Space | O(1) |

```
n ≤ 10^5, pages ≤ 10^5 → Σ ≈ 10^10, log2 ≈ 34 passes over n books.
Testing every cap from max(arr) to Σarr would be O(n · Σarr) → far too slow.
accumulate over 10^10 would need a long long.
```

---

## Key Insight

```
Same skeleton as Capacity to Ship Packages and Aggressive Cows:

  answer is a scalar + a cheap greedy feasibility check + monotone predicate
  → binary search on the answer, and decide whether you want the FIRST or
    the LAST feasible value.

Books and students are interchangeable with packages and days, or cows and
stalls — only the greedy predicate changes.
```

---

## References

- 🔗 [GFG — Allocate Minimum Number of Pages](https://www.geeksforgeeks.org/problems/allocate-minimum-number-of-pages0937/1)
- 🔗 [LeetCode 410 — Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/) (same problem, no `m > n` case)
- 🔗 [LeetCode 1011 — Capacity To Ship Packages Within D Days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/) (same pattern)

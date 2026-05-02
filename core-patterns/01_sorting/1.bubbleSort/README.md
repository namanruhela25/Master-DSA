# Bubble Sort 

## What is Bubble Sort?

Bubble Sort is a **simple sorting algorithm** that **compares neighbors** and **swaps them if they're in the wrong order**. It's like bubbles rising to the top - bigger numbers "bubble up" to the end!

### The Idea:
1. Compare adjacent pairs of numbers
2. If left number is bigger than right, swap them
3. Repeat until the array is sorted!

---

## How It Works (Step by Step) 

### Example: Sort `[5, 2, 8, 1, 9]`

**Initial Array:**
```
[5, 2, 8, 1, 9]
```

**Pass 1:** Compare and swap neighbors
```
Compare 5 and 2 → 5 > 2, swap     [2, 5, 8, 1, 9]
Compare 5 and 8 → 5 < 8, no swap  [2, 5, 8, 1, 9]
Compare 8 and 1 → 8 > 1, swap     [2, 5, 1, 8, 9]
Compare 8 and 9 → 8 < 9, no swap  [2, 5, 1, 8, 9]
                                    ↑ 9 bubbled to end!
```

**Pass 2:** Repeat (but don't touch last element, it's sorted!)
```
Compare 2 and 5 → 2 < 5, no swap   [2, 5, 1, 8, 9]
Compare 5 and 1 → 5 > 1, swap      [2, 1, 5, 8, 9]
Compare 5 and 8 → 5 < 8, no swap   [2, 1, 5, 8, 9]
                                     ↑ 8 is in place!
```

**Pass 3:** Keep going
```
Compare 2 and 1 → 2 > 1, swap      [1, 2, 5, 8, 9]
Compare 2 and 5 → 2 < 5, no swap   [1, 2, 5, 8, 9]
                                     ↑ 5 is in place!
```

**Pass 4:** One more check
```
Compare 1 and 2 → 1 < 2, no swap   [1, 2, 5, 8, 9]
                                     ✓ SORTED!
```

---

## Real-Life Example 

Imagine kids standing in a line trying to stand by height from shortest to tallest:

1. Start from the left
2. Compare neighbors - if left is taller, they swap positions
3. The tallest person "bubbles" to the right end
4. Repeat with remaining people
5. Eventually everyone is in perfect order!

---

## Code Explanation 

### Line 1-2: Class and Function Start
```cpp
class BubbleSort {
    void bubble_sort(vector<int>& arr) {
        int n = arr.size();
```
- Create a class to organize the sorting function
- `arr` is our array to sort
- `n` is the size (number of elements)

### Line 3: Outer Loop
```cpp
for (int i = n - 1; i >= 0; i--) { // Start setting last element
```
- **`i`**: Marks the end position of the unsorted part
- **`i = n - 1`**: Start from last position
- **`i >= 0`**: Keep going until we reach the beginning
- **Why countdown?** Each pass places one element in its final position
- **Example:** First pass sorts elements 0 to n-1, second pass sorts 0 to n-2, etc.

### Line 4: Inner Loop
```cpp
    for (int j = 0; j <= i - 1; j++) {
```
- **`j`**: Starting position of comparison
- **`j <= i - 1`**: Compare up to position `i` (because largest is already at `i`)
- This inner loop does the actual comparisons and swaps

### Lines 5-6: Compare and Swap
```cpp
        if (arr[j] > arr[j + 1]) {
            swap(arr[j], arr[j + 1]);
        }
```
- **`arr[j] > arr[j + 1]`**: Check if left number is bigger
- **`swap()`**: If yes, exchange their positions!
- **Example:** If positions have `[8, 1]` and `8 > 1`, swap to get `[1, 8]`

### Complete Example Trace:
```
Initial: [5, 2, 8, 1, 9]

i=4 (j goes 0 to 3):
  j=0: 5>2? Yes, swap   → [2, 5, 8, 1, 9]
  j=1: 5>8? No          → [2, 5, 8, 1, 9]
  j=2: 8>1? Yes, swap   → [2, 5, 1, 8, 9]
  j=3: 8>9? No          → [2, 5, 1, 8, 9]  ✓ 9 in place

i=3 (j goes 0 to 2):
  j=0: 2>5? No          → [2, 5, 1, 8, 9]
  j=1: 5>1? Yes, swap   → [2, 1, 5, 8, 9]
  j=2: 5>8? No          → [2, 1, 5, 8, 9]  ✓ 8 in place

i=2 (j goes 0 to 1):
  j=0: 2>1? Yes, swap   → [1, 2, 5, 8, 9]
  j=1: 2>5? No          → [1, 2, 5, 8, 9]  ✓ 5 in place

i=1 (j goes 0 to 0):
  j=0: 1>2? No          → [1, 2, 5, 8, 9]  ✓ SORTED!

Final: [1, 2, 5, 8, 9]
```

### Lines 10-14: Print Output
```cpp
cout << "After Using Bubble Sort:\n";
for (int num : arr) {
    cout << num << " ";
}
cout << endl;
```
- Display the sorted array on screen
- Output: `After Using Bubble Sort: 1 2 5 8 9`

---

## Time & Space Complexity 

### Time Complexity:
- **Best Case:** O(n) - If array is already sorted (with optimization)
- **Average Case:** O(n²)
- **Worst Case:** O(n²) - If array is reverse sorted

**Why n²?**
- Outer loop runs n times
- Inner loop runs up to n times for each outer loop pass
- Total: n × n = n²

### Space Complexity:
- **O(1)** - We swap in place, no extra memory needed!

---

## Comparison Table 📊

| Feature | Bubble Sort |
|---------|------------|
| **Difficulty** | Very Easy ✓ |
| **Speed** | Slow ✗ |
| **Extra Space** | None ✓ |
| **Stable** | Yes ✓ |
| **Good for** | Learning, Small arrays |
| **Bad for** | Large arrays ✗ |

---

## Why is it Called "Bubble" Sort?

Because larger numbers "bubble up" to their correct positions at the end, just like air bubbles rising to the surface of water!

---

## Advantages 
- **Super simple** - Easy to understand and code
- **No extra memory** - Sorts in place
- **Stable** - Equal elements keep their order
- **Good for learning** - Great first sorting algorithm

---

## Disadvantages
- **Very slow** - O(n²) is terrible for big lists
- **Not practical** - Never used in real applications
- **Many comparisons** - Even when mostly sorted

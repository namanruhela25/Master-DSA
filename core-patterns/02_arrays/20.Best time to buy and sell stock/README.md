# Best Time to Buy and Sell Stock

## Problem Link
🔗 [LeetCode 121 — Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)

---

## What is this Problem?

Given an array `prices` where `prices[i]` is the price of a stock on day `i`, find the **maximum profit** you can achieve by buying on one day and selling on a later day. You may only complete **one transaction**. If no profit is possible, return `0`.

**Examples:**
```
prices = [7, 1, 5, 3, 6, 4]
Output: 5
Buy on day 1 (price=1), sell on day 4 (price=6), profit=5.

prices = [7, 6, 4, 3, 1]
Output: 0
Prices only decrease — no profitable transaction possible.

prices = [2, 4, 1, 7]
Output: 6
Buy on day 2 (price=1), sell on day 3 (price=7), profit=6.
```

---

## The Problem Explained

Think of it like **watching a stock ticker and circling the best buy/sell pair**:

```
Day:    1    2    3    4    5    6
Price:  7    1    5    3    6    4

As you scan left to right, you track:
  "What's the cheapest price I've seen so far?"
  "If I sold TODAY at this price, what's my profit?"

Day 1: price=7. Cheapest so far=7. Profit if sell=0.
Day 2: price=1. NEW LOW! Cheapest=1. Profit=0.
Day 3: price=5. Profit=5-1=4. Best so far=4.
Day 4: price=3. Profit=3-1=2. No improvement.
Day 5: price=6. Profit=6-1=5. NEW BEST! Best=5.
Day 6: price=4. Profit=4-1=3. No improvement.

Answer: 5 ✓
```

**Key idea:** Scan left to right. Track the **minimum price seen so far** (best buy day). At every price, compute profit if you sold today. The answer is the maximum of all those profits.

---

## HOOK TO REMEMBER FOREVER

**"TRACK THE VALLEY. PROFIT FROM EVERY PEAK ABOVE IT."**

Every time you see "buy low, sell high, one transaction":
- ✅ `minPrice = INT_MAX` — lowest buy price seen so far
- ✅ `maxProfit = 0` — best profit seen so far
- ✅ If current price is a new low → update `minPrice`
- ✅ Else if `price - minPrice > maxProfit` → update `maxProfit`
- ✅ Return `maxProfit` (0 if no profitable transaction exists)
- ✅ O(n) time, O(1) space — single pass, two variables

**Remember: You only need to track one number — the lowest price seen so far. Every other price is a potential sell day. The gap between them is the profit.** 📈

---

## How It Works Step By Step

### Strategy

```
prices = [7, 1, 5, 3, 6, 4]

minPrice = INT_MAX, maxProfit = 0

Day 0: price=7. 7 < INT_MAX → minPrice=7
Day 1: price=1. 1 < 7      → minPrice=1  (new valley!)
Day 2: price=5. 5-1=4 > 0  → maxProfit=4
Day 3: price=3. 3-1=2 < 4  → no change
Day 4: price=6. 6-1=5 > 4  → maxProfit=5 (new peak above the valley!)
Day 5: price=4. 4-1=3 < 5  → no change

Return 5 ✓
```

### Visual — Price Chart with Valley and Peak

```
Price
  7 |  *
  6 |           *
  5 |     *
  4 |               *
  3 |        *
  2 |
  1 |     *   ← BUY HERE (minPrice=1)
    +--+--+--+--+--+--→ Day
       0  1  2  3  4  5

Best sell: day 4 (price=6)
Profit = 6 - 1 = 5
```

### Tracking minPrice and maxProfit Over Time

```
Day  Price  minPrice  profit(today)  maxProfit
  0    7       7           0            0
  1    1       1           0            0     ← new low, reset valley
  2    5       1           4            4
  3    3       1           2            4
  4    6       1           5            5     ← new best!
  5    4       1           3            5
```

---

## Code Full Solution

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minPrice = INT_MAX;
        int maxProfit = 0;
        int n = prices.size();

        for (int i = 0; i < n; i++) {
            if (prices[i] < minPrice) {
                minPrice = prices[i];
            } else if (prices[i] - minPrice > maxProfit) {
                maxProfit = prices[i] - minPrice;
            }
        }

        return maxProfit;
    }
};
```

---

## Code Explanation

### Initialize

```cpp
int minPrice = INT_MAX;
int maxProfit = 0;
```

- **`minPrice = INT_MAX`:** Any real price will immediately become the new minimum on day 0. Safe starting point that requires no special first-element handling.
- **`maxProfit = 0`:** If prices only decrease, no transaction is profitable. Returning 0 means "don't trade."

---

### The `if-else if` Structure

```cpp
if (prices[i] < minPrice) {
    minPrice = prices[i];
} else if (prices[i] - minPrice > maxProfit) {
    maxProfit = prices[i] - minPrice;
}
```

**Why `else if` and not two separate `if`s?**

```
If we used two separate ifs:
  prices[i] = 1 (new low)
  → minPrice = 1
  → then: prices[i] - minPrice = 1 - 1 = 0, no profit update (fine here)

  But semantically: when we find a new low, we're BUYING.
  You can't buy and sell on the same day for a profit.
  Using else if makes the logic explicit:
    "Either update the buy price OR compute sell profit — not both."

  Both approaches give the same result numerically here,
  but else if is the cleaner, more intentional expression. ✓
```

---

### Why `INT_MAX` for `minPrice`

```
Alternative: minPrice = prices[0], loop from i=1.

INT_MAX approach: loop from i=0.
  Day 0: prices[0] < INT_MAX always → minPrice = prices[0].
  Functionally identical, but avoids the special case.

Caveat: prices[i] - INT_MAX would overflow if we computed
  profit before minPrice was updated. The else if prevents this —
  when minPrice is INT_MAX, prices[i] < INT_MAX is always true,
  so we always hit the first branch first. ✓
```

---

## Complete Example Traces

### Trace 1: Standard Case

```
prices = [7, 1, 5, 3, 6, 4]

i=0: 7  < INT_MAX → minPrice=7
i=1: 1  < 7      → minPrice=1
i=2: 5-1=4 > 0   → maxProfit=4
i=3: 3-1=2 < 4   → no change
i=4: 6-1=5 > 4   → maxProfit=5
i=5: 4-1=3 < 5   → no change

Return 5 ✓
```

### Trace 2: Monotonically Decreasing (No Profit)

```
prices = [7, 6, 4, 3, 1]

i=0: minPrice=7
i=1: 6 < 7  → minPrice=6
i=2: 4 < 6  → minPrice=4
i=3: 3 < 4  → minPrice=3
i=4: 1 < 3  → minPrice=1

maxProfit never updated → stays 0.

Return 0 ✓  (never sell if buying means a loss)
```

### Trace 3: Monotonically Increasing (Best Profit = Full Range)

```
prices = [1, 2, 3, 4, 5]

i=0: minPrice=1
i=1: 2-1=1  → maxProfit=1
i=2: 3-1=2  → maxProfit=2
i=3: 4-1=3  → maxProfit=3
i=4: 5-1=4  → maxProfit=4

Return 4 ✓  (buy first day, sell last day)
```

### Trace 4: New Low After a Profitable Stretch

```
prices = [3, 7, 2, 9]

i=0: minPrice=3
i=1: 7-3=4  → maxProfit=4
i=2: 2 < 3  → minPrice=2  (new low — but maxProfit still holds!)
i=3: 9-2=7  → maxProfit=7

Return 7 ✓

Key: When minPrice updates, maxProfit is NOT reset.
The old profit (4) is preserved until something better (7) beats it.
```

### Trace 5: Profit on Second-to-Last Day

```
prices = [5, 1, 7, 3]

i=0: minPrice=5
i=1: 1 < 5  → minPrice=1
i=2: 7-1=6  → maxProfit=6
i=3: 3-1=2  < 6

Return 6 ✓
```

### Trace 6: Single Element

```
prices = [5]
minPrice=5. Loop runs once, first branch taken.
maxProfit stays 0.

Return 0 ✓  (can't sell without a second day)
```

### Trace 7: Two Elements, Profitable

```
prices = [2, 9]
i=0: minPrice=2
i=1: 9-2=7 → maxProfit=7

Return 7 ✓
```

### Trace 8: Two Elements, Not Profitable

```
prices = [9, 2]
i=0: minPrice=9
i=1: 2 < 9 → minPrice=2. No profit computed.

Return 0 ✓
```

---

## Edge Cases

### Case 1: All Same Price

```
Input: [5, 5, 5, 5]
No price ever beats minPrice. else if never triggers.
Output: 0 ✓  (no profit in flat market)
```

### Case 2: Two-Day Dip then Spike

```
Input: [10, 1, 2]
New low at day 1 → minPrice=1.
Day 2: profit=2-1=1.
Output: 1 ✓  (not the initial price=10, because we can't sell before buying)
```

### Case 3: Best Buy Not Day 0

```
Input: [9, 3, 8]
Day 0: minPrice=9
Day 1: minPrice=3 (new low)
Day 2: 8-3=5 > 0 → maxProfit=5
Output: 5 ✓
```

---

## Time Complexity

- **O(n)** — single pass through the array
- Each element processed once in O(1)
- Total: **O(n)**

---

## Space Complexity

- **O(1)** — constant extra space
- Only `minPrice` and `maxProfit` used
- No auxiliary array
- Total: **O(1)**

---

## Key Insights

### Never Reset `maxProfit` When `minPrice` Updates

```
prices = [3, 7, 2, 9]

When we see price=2 (new low), minPrice updates to 2.
maxProfit stays at 4 — the best profit found so far.

If we reset maxProfit when minPrice changes:
  We'd lose the knowledge that [3,7] gave profit=4.
  Final answer would be 7 (from buying at 2, selling at 9) = 7.
  Wait — that's actually better here. But consider:

prices = [1, 10, 2, 3]
  minPrice hits 1, maxProfit = 9 from selling at 10.
  Then minPrice updates to 2 (new low).
  If we reset maxProfit: only profit of 1 (selling at 3) recorded. WRONG! ❌
  If we keep maxProfit: 9 is preserved correctly. ✓

maxProfit is the GLOBAL best — it never rolls back.
```

### The Algorithm = Tracking the Running Minimum

```
At every index i, we implicitly know:
  "The best I could have bought for, from day 0 to day i, is minPrice."

So for every sell candidate (current day), the maximum possible
profit is: prices[i] - minPrice.

We just track the maximum of that across all days. ✓

This is equivalent to:
  maxProfit = max over all j > i of (prices[j] - prices[i])
But solved in O(n) instead of O(n²). ✓
```

### Why Not Two Pointers Here?

```
Two-pointer approach (buy=0, sell=1):
  If prices[sell] > prices[buy] → compute profit, advance sell
  Else → advance buy to sell, advance sell

This also works in O(n) and O(1).
The minPrice approach is cleaner — one pointer, simpler logic.

For THIS problem (one transaction), minPrice tracking is canonical.
For MULTIPLE transactions (LeetCode 122), a greedy approach is used.
For K transactions (LeetCode 123, 188), dynamic programming is needed.
```

---

## References

- 🔗 [LeetCode 121 — Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)
- 🔗 [LeetCode 122 — Best Time to Buy and Sell Stock II (multiple transactions)](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/)
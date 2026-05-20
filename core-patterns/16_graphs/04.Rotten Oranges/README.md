# Rotting Oranges

## Problem Link
🔗 [LeetCode 994 : Rotting Oranges](https://leetcode.com/problems/rotting-oranges/)

---

## What is this Problem?

You have a **grid of cells**, where each cell contains:
- `0` → Empty
- `1` → Fresh orange
- `2` → Rotten orange

Every minute, a rotten orange **spreads rot to all 4 adjacent fresh oranges** (up, down, left, right).

You need to find the **minimum number of minutes** until no fresh orange remains. If it's **impossible** to rot all oranges, return `-1`.

**Examples:**
```
Grid:                      Grid:
[[2,1,1],                  [[2,1,1],
 [1,1,0],                   [0,1,1],
 [0,1,1]]                   [1,0,1]]

Minute 0: [[2,1,1],        Fresh orange at (2,0) is
            [1,1,0],        unreachable from any rotten orange.
            [0,1,1]]
Minute 1: [[2,2,1],        Return -1 ✗
            [2,1,0],        (Impossible to rot all!)
            [0,1,1]]
Minute 2: [[2,2,2],
            [2,2,0],
            [0,1,1]]
Minute 3: [[2,2,2],
            [2,2,0],
            [0,2,1]]
Minute 4: [[2,2,2],
            [2,2,0],
            [0,2,2]]

Return 4 ✓
```

---

## The Problem Explained

Think of it like a **virus spreading in a hospital ward**:

```
Ward layout (grid):
  [Sick, Healthy, Healthy]
  [Healthy, Healthy, Empty]
  [Empty, Healthy, Healthy]

Minute 0: The sick person (rotten orange) exists.
Minute 1: They infect all adjacent healthy people.
Minute 2: Those newly infected people infect their neighbors.
...and so on, spreading outward like ripples.

Key insight:
  ALL sick people spread SIMULTANEOUSLY each minute.
  Not one at a time — all at once, every minute.
  → This is MULTI-SOURCE BFS, not single-source!
```

**Key idea:** This is not a single starting point problem. ALL rotten oranges spread simultaneously → push **all rotten oranges into the queue at time=0** and run BFS together!

---

## HOOK TO REMEMBER FOREVER

**"ALL ROTTEN FIRST, BFS SPREADS LEVEL BY LEVEL, CHECK FOR SURVIVORS"**

Every time you see "minimum time to spread from multiple sources":
- ✅ Push ALL source nodes (rotten oranges) into the queue at time 0
- ✅ BFS naturally handles simultaneous spreading level by level
- ✅ Track the time at which each cell gets infected (`t + 1`)
- ✅ Keep `tm = max(t, tm)` to record the last infection time
- ✅ After BFS, check if any fresh orange (`grid==1`) was never visited (`vis!=2`) → return -1
- ✅ O(n×m) time and space

**Remember: Multi-source BFS = seed ALL starting points at time 0. The queue level = the minute. Last level processed = answer!** 🍊

---

## How It Works Step By Step

### The Strategy

```
Grid:
[[2, 1, 1],
 [1, 1, 0],
 [0, 1, 1]]

Phase 1: Seed all rotten oranges into queue at time 0
  Rotten at (0,0) → push {(0,0), 0}
  vis[0][0] = 2

Phase 2: BFS spreads rot minute by minute
  Minute 0: Process (0,0)
    Infect (0,1) → push {(0,1), 1}
    Infect (1,0) → push {(1,0), 1}

  Minute 1: Process (0,1) and (1,0)
    From (0,1): Infect (0,2) → push {(0,2), 2}
                Infect (1,1) → push {(1,1), 2}
    From (1,0): (1,1) already queued → skip

  Minute 2: Process (0,2) and (1,1)
    From (1,1): Infect (2,1) → push {(2,1), 3}

  Minute 3: Process (2,1)
    From (2,1): Infect (2,2) → push {(2,2), 4}

  Minute 4: Process (2,2)
    No fresh neighbors

Phase 3: Check survivors
  All cells either 0 (empty) or vis==2 → no survivors

tm = 4 → Return 4 ✓
```

### Visual Animation: Spread by Minute

```
Minute 0 (initial):         vis grid:
[2, 1, 1]                   [2, 0, 0]
[1, 1, 0]                   [0, 0, 0]
[0, 1, 1]                   [0, 0, 0]

Minute 1 (from (0,0)):      vis grid:
[2, 2, 1]   ← (0,1) rots   [2, 2, 0]
[2, 1, 0]   ← (1,0) rots   [2, 0, 0]
[0, 1, 1]                   [0, 0, 0]

Minute 2 (from (0,1),(1,0)):  vis grid:
[2, 2, 2]   ← (0,2) rots   [2, 2, 2]
[2, 2, 0]   ← (1,1) rots   [2, 2, 0]
[0, 1, 1]                   [0, 0, 0]

Minute 3 (from (0,2),(1,1)): vis grid:
[2, 2, 2]                   [2, 2, 2]
[2, 2, 0]                   [2, 2, 0]
[0, 2, 1]   ← (2,1) rots   [0, 2, 0]

Minute 4 (from (2,1)):      vis grid:
[2, 2, 2]                   [2, 2, 2]
[2, 2, 0]                   [2, 2, 0]
[0, 2, 2]   ← (2,2) rots   [0, 2, 2]

Queue empty. tm = 4.

Check: any cell where grid==1 and vis!=2?
  (2,0): grid==0 (empty) → skip ✓
  All others vis==2 ✓

Return 4 ✓
```

---

## Code Full Solution

```cpp
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        queue<pair<pair<int,int>,int>> q;
        int vis[n][m];

        // Phase 1: Seed all rotten oranges + initialize vis
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 2) {
                    q.push({{i, j}, 0});
                    vis[i][j] = 2;
                } else {
                    vis[i][j] = 0;
                }
            }
        }

        // Phase 2: Multi-source BFS
        int tm = 0;
        int drow[] = {-1, 0, 1, 0};
        int dcol[] = {0, 1, 0, -1};

        while (!q.empty()) {
            int r = q.front().first.first;
            int c = q.front().first.second;
            int t = q.front().second;
            q.pop();
            tm = max(t, tm);

            for (int i = 0; i < 4; i++) {
                int nrow = r + drow[i];
                int ncol = c + dcol[i];
                if (nrow >= 0 && nrow < n && ncol < m && ncol >= 0
                    && vis[nrow][ncol] != 2 && grid[nrow][ncol] == 1) {
                    q.push({{nrow, ncol}, t + 1});
                    vis[nrow][ncol] = 2;
                }
            }
        }

        // Phase 3: Check for unreachable fresh oranges
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (vis[i][j] != 2 && grid[i][j] == 1) return -1;
            }
        }

        return tm;
    }
};
```

---

## Code Explanation

### Phase 1: Seed All Rotten Oranges

```cpp
queue<pair<pair<int,int>,int>> q;
int vis[n][m];

for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        if (grid[i][j] == 2) {
            q.push({{i, j}, 0});
            vis[i][j] = 2;
        } else {
            vis[i][j] = 0;
        }
    }
}
```

**The queue stores:** `{ {row, col}, time }`
- Position as a pair, plus the minute at which this cell became rotten

**Why push ALL rotten oranges at time 0?**
```
Single-source BFS: one starting point → answers "shortest path from A"
Multi-source BFS:  many starting points at t=0 → answers "shortest
                   distance from ANY rotten orange"

If we pushed only one rotten orange and processed others later,
cells near the "later" rotten oranges would get wrong (larger) times.

Pushing all at t=0 = they all spread simultaneously. ✓
```

**`vis` array:** Separate from the grid — we don't mutate the input.
- `vis[i][j] = 2` → this cell has been visited/rotted
- `vis[i][j] = 0` → not yet visited

---

### Phase 2: BFS — Spreading the Rot

```cpp
int drow[] = {-1, 0, 1, 0};
int dcol[] = {0, 1, 0, -1};
```

Direction arrays — the classic 4-directional movement trick:

```
drow + dcol pairs:
  (-1, 0) → Up
  ( 0, 1) → Right
  ( 1, 0) → Down
  ( 0,-1) → Left

Loop i=0 to 3 covers all 4 directions in one clean loop.
No if-else chains needed. 4 pairs = 4 directions. ✓
```

```cpp
int r = q.front().first.first;
int c = q.front().first.second;
int t = q.front().second;
q.pop();
tm = max(t, tm);
```

- Extract row, col, and time from the front of the queue
- `tm = max(t, tm)` → tracks the largest time we've seen so far (last cell to rot)

```cpp
if (nrow >= 0 && nrow < n && ncol < m && ncol >= 0
    && vis[nrow][ncol] != 2 && grid[nrow][ncol] == 1) {
    q.push({{nrow, ncol}, t + 1});
    vis[nrow][ncol] = 2;
}
```

**Five conditions must all be true to infect a neighbor:**

```
1. nrow >= 0          → not above the grid
2. nrow < n           → not below the grid
3. ncol >= 0          → not left of the grid
4. ncol < m           → not right of the grid
5. vis[nrow][ncol]!=2 → not already rotten/visited
6. grid[nrow][ncol]==1 → it's a fresh orange (not empty)
```

**Why `t + 1` when pushing?**
```
Current cell got rotten at minute t.
Its neighbor gets rotten one minute later → t + 1.

This is how BFS naturally encodes "distance from source."
Each level of the queue = one more minute elapsed.
```

**Why mark `vis[nrow][ncol] = 2` on PUSH, not pop?**
```
Same reason as BFS: if we don't mark on push, the same fresh
orange can be pushed multiple times by different rotten neighbors.

Example: Fresh orange at (1,1) has two rotten neighbors (0,1) and (1,0).
  → Both would push (1,1) if we don't mark immediately.
  → (1,1) gets counted twice! Wrong time! ❌

Mark on push → first rotten neighbor to reach (1,1) claims it. ✓
```

---

### Phase 3: Check for Unreachable Fresh Oranges

```cpp
for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        if (vis[i][j] != 2 && grid[i][j] == 1) return -1;
    }
}
return tm;
```

After BFS completes, any cell where:
- `grid[i][j] == 1` → was a fresh orange originally
- `vis[i][j] != 2` → was never reached by any rotten orange

means it is **trapped / unreachable** → return -1.

```
Why check vis instead of grid?
  We never modified grid during BFS.
  vis tracks what our BFS actually reached.
  grid[i][j]==1 && vis[i][j]!=2 = "fresh and untouched" = unreachable.
```

---

## Complete Example Traces

### Trace 1: Normal Case — Returns 4

```
Grid:
[[2,1,1],
 [1,1,0],
 [0,1,1]]

Seed: push (0,0) at t=0. vis[0][0]=2.
Queue: [{(0,0),0}]

Pop (0,0),t=0. tm=0.
  Up: (-1,0) out of bounds → skip
  Right: (0,1) → grid==1, vis==0 → push {(0,1),1}, vis[0][1]=2
  Down: (1,0) → grid==1, vis==0 → push {(1,0),1}, vis[1][0]=2
  Left: (0,-1) out of bounds → skip
Queue: [{(0,1),1},{(1,0),1}]

Pop (0,1),t=1. tm=1.
  Up: (-1,1) out of bounds → skip
  Right: (0,2) → grid==1 → push {(0,2),2}, vis[0][2]=2
  Down: (1,1) → grid==1 → push {(1,1),2}, vis[1][1]=2
  Left: (0,0) → vis==2 → skip
Queue: [{(1,0),1},{(0,2),2},{(1,1),2}]

Pop (1,0),t=1. tm=1.
  Up: (0,0) → vis==2 → skip
  Right: (1,1) → vis==2 already → skip
  Down: (2,0) → grid==0 → skip
  Left: (1,-1) out of bounds → skip
Queue: [{(0,2),2},{(1,1),2}]

Pop (0,2),t=2. tm=2.
  Down: (1,2) → grid==0 → skip
  Others: out of bounds or vis==2
Queue: [{(1,1),2}]

Pop (1,1),t=2. tm=2.
  Down: (2,1) → grid==1 → push {(2,1),3}, vis[2][1]=2
  Others: vis==2 or out of bounds
Queue: [{(2,1),3}]

Pop (2,1),t=3. tm=3.
  Right: (2,2) → grid==1 → push {(2,2),4}, vis[2][2]=2
  Others: vis==2 or empty
Queue: [{(2,2),4}]

Pop (2,2),t=4. tm=4.
  All neighbors visited or empty.
Queue: []

Check survivors: all grid==1 cells have vis==2 ✓

Return tm = 4 ✓
```

### Trace 2: Impossible Case — Returns -1

```
Grid:
[[2,1,1],
 [0,1,1],
 [1,0,1]]

Seed: push (0,0) at t=0.

BFS runs and rots everything reachable from (0,0):
  (0,0)→(0,1)→(0,2)
            ↓      ↓
          (1,1)→(1,2)

Cell (2,0) is blocked by 0s on all sides → never reached.
Cell (2,2) is blocked too.

After BFS:
  vis[2][0] = 0, but grid[2][0] = 1 → fresh and unreachable!

Check phase: vis[2][0]!=2 && grid[2][0]==1 → return -1 ✓
```

### Trace 3: No Fresh Oranges — Returns 0

```
Grid:
[[0, 2, 0],
 [2, 0, 2],
 [0, 2, 0]]

Seed: push all 4 rotten oranges at t=0.

BFS runs — every neighbor is either 0 (empty) or already rotten.
No fresh oranges ever get pushed.
Queue empties immediately after processing all seeds.

tm stays 0.

Check: no cell has grid==1 → no fresh oranges → no survivors.

Return 0 ✓
```

### Trace 4: All Fresh, No Rotten — Returns -1

```
Grid:
[[1, 1],
 [1, 1]]

Seed phase: no cell has grid==2 → nothing pushed into queue.

BFS: queue is empty from the start → while loop never runs.

tm = 0.

Check: vis[0][0]!=2 && grid[0][0]==1 → return -1 ✓

(No rotten source → impossible to rot any orange)
```

### Trace 5: Single Rotten, Single Fresh (Adjacent)

```
Grid: [[2, 1]]

Seed: push (0,0) at t=0.

Pop (0,0),t=0. tm=0.
  Right: (0,1) → fresh → push {(0,1),1}, vis[0][1]=2

Pop (0,1),t=1. tm=1.
  No fresh neighbors. Queue empty.

Check: all grid==1 have vis==2 ✓

Return 1 ✓
```

### Trace 6: Multiple Rotten Sources Spread Simultaneously

```
Grid:
[[2, 1, 1, 1, 2]]
  ^             ^
  rotten        rotten

Seed: push (0,0) at t=0, push (0,4) at t=0.

Minute 1:
  From (0,0): rot (0,1) at t=1
  From (0,4): rot (0,3) at t=1

Minute 2:
  From (0,1): rot (0,2) at t=2
  From (0,3): (0,2) already claimed by (0,1)? → vis check!

(0,2) gets pushed by (0,1) first, marked vis=2.
When (0,3) tries to push (0,2), vis[0][2]==2 → skip.

tm = 2

Return 2 ✓
(Both ends attack simultaneously — middle reached at t=2, not t=4!)
```

---

## Edge Cases

### Case 1: Grid with Only Empty Cells

```
Input: [[0, 0], [0, 0]]
- No rotten, no fresh. Queue empty. tm=0.
- Check: no grid==1 cells.
Output: 0 ✓
```

### Case 2: Single Cell — Rotten

```
Input: [[2]]
- Push (0,0), BFS pops it, no neighbors. tm=0.
Output: 0 ✓
```

### Case 3: Single Cell — Fresh

```
Input: [[1]]
- Nothing pushed. tm=0.
- Check: vis[0][0]!=2 && grid[0][0]==1 → return -1
Output: -1 ✓
```

### Case 4: Fresh Orange Surrounded by Empty Cells

```
Input: [[2,0,1]]
- Rotten at (0,0). Fresh at (0,2). Empty at (0,1) blocks spread.
- BFS from (0,0) → right is empty (grid==0) → skip.
- (0,2) never reached.
Output: -1 ✓
```

### Case 5: All Already Rotten

```
Input: [[2,2],[2,2]]
- All pushed at t=0, vis=2 everywhere.
- BFS: no fresh neighbors ever found.
- tm=0. Check: no grid==1 cells.
Output: 0 ✓
```

---

## Time Complexity

- **O(n × m)** where n = rows, m = columns
- Phase 1 (seeding): scan all cells → O(n×m)
- Phase 2 (BFS): each cell is pushed and popped at most once → O(n×m)
- Phase 3 (survivor check): scan all cells → O(n×m)
- Total: **O(n × m)**

---

## Space Complexity

- **O(n × m)** extra space
- `vis[n][m]` array → O(n×m)
- Queue holds at most O(n×m) entries in worst case (all cells rotten)
- Total extra space: **O(n × m)**

---

## Key Insights

### Why Multi-Source BFS, Not Single-Source?

```
Wrong approach (single source):
  Pick one rotten orange, BFS from it.
  Problem: other rotten oranges also spread simultaneously!
  Oranges near the "ignored" rotten ones get wrong (larger) times.

Correct approach (multi-source):
  Push ALL rotten oranges at t=0.
  BFS treats them as one unified "wave front."
  Every cell gets the time from its CLOSEST rotten orange. ✓

Multi-source BFS = run BFS as if all sources are one "super node."
```

### Why BFS and Not DFS?

```
DFS goes deep first, not level by level.
  → It would compute the path distance along one branch at a time.
  → Gives wrong minimum times for cells reachable from multiple sources.

BFS spreads level by level = minute by minute.
  → Guarantees every cell gets the MINIMUM time to rot. ✓

Minimum time → always BFS.
```

### The Direction Array Trick

```
int drow[] = {-1, 0, 1, 0};
int dcol[] = { 0, 1, 0,-1};

Index:  0      1      2      3
Move:   Up   Right  Down   Left

One loop replaces four separate if-blocks:
for (int i = 0; i < 4; i++) {
    int nrow = r + drow[i];
    int ncol = c + dcol[i];
    ...
}

Clean, compact, and easy to extend to 8 directions if needed!
```

### vis Array vs Modifying Grid Directly

```
Option A (modify grid): grid[nrow][ncol] = 2 when rotted
  → Simpler code
  → But mutates the input! Bad practice in interviews.

Option B (separate vis array): vis[nrow][ncol] = 2
  → Keeps original grid intact
  → Clean separation of "what's in the grid" vs "what BFS visited"
  → The final check compares vis against grid safely ✓

Both work, but vis array is the cleaner approach.
```

### Why `tm = max(t, tm)` and Not Just `tm = t`?

```
Queue processes cells roughly in time order, but not strictly
for multi-source BFS with different path lengths.

Using max ensures we capture the LAST cell to get infected,
regardless of the exact processing order in the queue.

tm = t directly would only work if queue is strictly ordered
by time — which holds here but max() is the safe habit. ✓
```

---

## References

- [Video Explanation](https://www.youtube.com/watch?v=yf3oUhkvqA0)
- 🔗 [LeetCode Problem — Rotting Oranges](https://leetcode.com/problems/rotting-oranges/)
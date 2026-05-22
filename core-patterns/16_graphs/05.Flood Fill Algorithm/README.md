# Flood Fill

## Problem Link
🔗 [LeetCode 733 — Flood Fill](https://leetcode.com/problems/flood-fill/)

---

## What is this Problem?

You have a **2D image grid** where each cell holds a **color value**. Given a starting pixel `(sr, sc)` and a `newColor`, perform a **flood fill**:

- Change the starting pixel to `newColor`
- Change all **4-directionally adjacent pixels** that share the **same original color** as the starting pixel
- Keep spreading to their neighbors with the same original color
- Return the modified image

**Examples:**
```
image:              sr=1, sc=1, color=2
[[1, 1, 1],
 [1, 1, 0],         Starting pixel (1,1) has color 1.
 [1, 0, 1]]         Fill all connected 1s with 2.

Output:
[[2, 2, 2],
 [2, 2, 0],         The isolated 1 at (2,2) is NOT filled —
 [2, 0, 1]]         it's not connected to (1,1) through same-color cells!
```

```
image:              sr=0, sc=0, color=0
[[0, 0, 0],
 [0, 0, 0]]         All cells are 0 and connected.

Output:
[[0, 0, 0],         newColor == iniColor → everything already
 [0, 0, 0]]         looks the same. No visible change.
```

---

## The Problem Explained

Think of it like the **paint bucket tool** in MS Paint:

```
You click on a pixel. The paint bucket:
  1. Looks at the color you clicked.
  2. Spreads paint in all 4 directions.
  3. Only paints cells that have the SAME original color.
  4. Stops when it hits a different color or the edge.

Image:              Click (1,1), fill with 🔵

⬜ ⬜ ⬜             🔵 🔵 🔵
⬜ ⬜ ⬛      →      🔵 🔵 ⬛
⬜ ⬛ ⬜             🔵 ⬛ ⬜

The isolated ⬜ at (2,2) doesn't get filled —
the ⬛ cells act as a wall blocking the spread!
```

**Key idea:** This is just a **DFS/BFS on a 2D grid**, where you only traverse cells that match the **original starting color**. Spread and recolor until no more connected same-color cells remain.

---

## HOOK TO REMEMBER FOREVER

**"SAVE ORIGINAL COLOR, DFS ONLY INTO SAME-COLOR NEIGHBORS, RECOLOR AS YOU GO"**

Every time you see "flood fill / paint bucket / connected region recolor":
- ✅ Save the `iniColor` (original color at starting pixel) before touching anything
- ✅ Copy the image into `ans` — fill `ans`, read checks from `image`
- ✅ DFS into 4-directional neighbors that have `iniColor` in `image` AND `newColor` not yet set in `ans`
- ✅ The `ans[nrow][ncol] != newColor` check acts as the visited guard
- ✅ O(n×m) time — at most every cell is visited once

**Remember: You spread only where the original color matches. The moment a cell has a different original color, it's a wall. Stop there!** 🎨

---

## How It Works Step By Step

### The Strategy

```
image:                      sr=1, sc=1, newColor=2
[[1, 1, 1],
 [1, 1, 0],    iniColor = image[1][1] = 1
 [1, 0, 1]]    ans starts as a copy of image

DFS(1,1):
  ans[1][1] = 2          → recolor starting cell
  Go Up    (0,1): image[0][1]==1, ans[0][1]!=2 → DFS(0,1)
    ans[0][1]=2
    Go Up    (-1,1): out of bounds → skip
    Go Right (0,2): image[0][2]==1, ans[0][2]!=2 → DFS(0,2)
      ans[0][2]=2, no valid unvisited neighbors
    ← return
    Go Left  (0,0): image[0][0]==1, ans[0][0]!=2 → DFS(0,0)
      ans[0][0]=2, no valid unvisited neighbors
    ← return
  ← return
  Go Right (1,2): image[1][2]==0 != iniColor(1) → skip (wall!)
  Go Down  (2,1): image[2][1]==0 != iniColor(1) → skip (wall!)
  Go Left  (1,0): image[1][0]==1, ans[1][0]!=2 → DFS(1,0)
    ans[1][0]=2
    Go Down (2,0): image[2][0]==1, ans[2][0]!=2 → DFS(2,0)
      ans[2][0]=2, no valid unvisited neighbors
    ← return
  ← return

ans:
[[2, 2, 2],
 [2, 2, 0],
 [2, 0, 1]]    ← (2,2) untouched: blocked by 0s ✓
```

### Visual Animation: DFS Spread

```
image (never changes):     ans (fills up as DFS runs):

[[1, 1, 1],                Step 0: [[1, 1, 1],
 [1, 1, 0],                          [1, 1, 0],
 [1, 0, 1]]                          [1, 0, 1]]

                           Step 1 — DFS(1,1):
                                    [[1, 1, 1],
                                     [1, 2, 0],   ← (1,1) filled
                                     [1, 0, 1]]

                           Step 2 — DFS(0,1):
                                    [[1, 2, 1],   ← (0,1) filled
                                     [1, 2, 0],
                                     [1, 0, 1]]

                           Step 3 — DFS(0,2):
                                    [[1, 2, 2],   ← (0,2) filled
                                     [1, 2, 0],
                                     [1, 0, 1]]

                           Step 4 — DFS(0,0):
                                    [[2, 2, 2],   ← (0,0) filled
                                     [1, 2, 0],
                                     [1, 0, 1]]

                           Step 5 — DFS(1,0):
                                    [[2, 2, 2],
                                     [2, 2, 0],   ← (1,0) filled
                                     [1, 0, 1]]

                           Step 6 — DFS(2,0):
                                    [[2, 2, 2],
                                     [2, 2, 0],
                                     [2, 0, 1]]   ← (2,0) filled

Final ans:
[[2, 2, 2],
 [2, 2, 0],
 [2, 0, 1]]  ✓
```

---

## Code Full Solution

```cpp
class Solution {
public:
    void dfs(vector<vector<int>>& image, vector<vector<int>>& ans,
             int delRow[], int delCol[],
             int row, int col, int iniColor, int newColor) {

        ans[row][col] = newColor;
        int n = image.size();
        int m = image[0].size();

        for (int i = 0; i < 4; i++) {
            int nrow = row + delRow[i];
            int ncol = col + delCol[i];

            if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m
                && image[nrow][ncol] == iniColor
                && ans[nrow][ncol] != newColor) {
                dfs(image, ans, delRow, delCol, nrow, ncol, iniColor, newColor);
            }
        }
    }

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int iniColor = image[sr][sc];
        int delRow[] = {-1, 0, 1, 0};
        int delCol[] = { 0, 1, 0,-1};
        vector<vector<int>> ans = image;
        dfs(image, ans, delRow, delCol, sr, sc, iniColor, color);
        return ans;
    }
};
```

---

## Code Explanation

### The Driver Function

```cpp
int iniColor = image[sr][sc];
```

**Save the original color BEFORE anything changes:**
```
If we read iniColor during DFS, we might accidentally
read already-updated values from ans and lose track
of what color we're supposed to be spreading from.

Capturing it once here guarantees all DFS calls
check against the same original reference color. ✓
```

```cpp
vector<vector<int>> ans = image;
```

**Copy image into ans — DFS writes to `ans`, reads from `image`:**
```
Why two grids?
  image → the "original truth" — used to check if a neighbor
          has the right color to be filled (iniColor check)
  ans   → the "result being built" — cells get recolored here

If we modified image directly:
  We might overwrite a cell's original color before a neighbor
  has a chance to check whether it should spread there.

Keeping image unchanged = clean, safe reads throughout. ✓
```

---

### The DFS Function

```cpp
ans[row][col] = newColor;
```

**Recolor first, then explore:**
- Sets this cell to `newColor` in the answer grid immediately
- This is also our "visited" marker — the `ans[nrow][ncol] != newColor` check later uses this

---

### The Neighbor Check

```cpp
if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m
    && image[nrow][ncol] == iniColor
    && ans[nrow][ncol] != newColor)
```

**Six conditions, three purposes:**

```
Boundary check (4 conditions):
  nrow >= 0 && nrow < n    → neighbor is within row bounds
  ncol >= 0 && ncol < m    → neighbor is within col bounds

Color check:
  image[nrow][ncol] == iniColor  → neighbor has the ORIGINAL color
                                    (checked against unmodified image)

Visited check:
  ans[nrow][ncol] != newColor    → neighbor hasn't been filled yet
                                    (acts as the visited guard!)
```

**Why `ans[nrow][ncol] != newColor` as a visited guard?**
```
We don't use a separate visited array.
Instead: once a cell is filled with newColor, it won't be
visited again because ans[nrow][ncol] != newColor is false.

This is elegant — the fill itself is the visited marker!

Edge case this handles:
  What if iniColor == newColor?
  Without this check → DFS would revisit every already-filled cell
  infinitely (since image[nrow][ncol]==iniColor is always true).

  With this check → ans[nrow][ncol]==newColor (since we just set it)
  → skip → no infinite recursion. ✓
```

---

### Direction Arrays

```cpp
int delRow[] = {-1, 0, 1, 0};
int delCol[] = { 0, 1, 0,-1};
```

```
i=0: (-1, 0) → Up
i=1: ( 0, 1) → Right
i=2: ( 1, 0) → Down
i=3: ( 0,-1) → Left

One loop, four directions. Same pattern used in
Rotting Oranges, Number of Islands, and many other grid problems.
Memorize this pair — it's universal for 4-directional grid traversal.
```

---

## Complete Example Traces

### Trace 1: Standard Case

```
image=[[1,1,1],[1,1,0],[1,0,1]], sr=1, sc=1, color=2

iniColor = image[1][1] = 1
ans = [[1,1,1],[1,1,0],[1,0,1]]

DFS(1,1): ans[1][1]=2
  Up    (0,1): img==1, ans!=2 → DFS(0,1): ans[0][1]=2
    Up    (-1,1): OOB → skip
    Right (0,2): img==1, ans!=2 → DFS(0,2): ans[0][2]=2, no neighbors
    Down  (1,1): img==1, ans[1][1]==2 → skip (visited!)
    Left  (0,0): img==1, ans!=2 → DFS(0,0): ans[0][0]=2, no neighbors
  Right (1,2): img[1][2]==0 != iniColor → skip (wall!)
  Down  (2,1): img[2][1]==0 != iniColor → skip (wall!)
  Left  (1,0): img==1, ans!=2 → DFS(1,0): ans[1][0]=2
    Down (2,0): img==1, ans!=2 → DFS(2,0): ans[2][0]=2, no neighbors

Final ans:
[[2,2,2],
 [2,2,0],
 [2,0,1]] ✓    ← (2,2) isolated by 0-walls, never reached
```

### Trace 2: newColor == iniColor

```
image=[[1,1,1],[1,1,0]], sr=0, sc=0, color=1

iniColor = 1, newColor = 1

DFS(0,0): ans[0][0]=1
  Right (0,1): img==1, ans[0][1]!=1? → ans[0][1] is still 1 (from copy)
               → 1 != 1 is FALSE → skip! ← visited guard saves us

DFS terminates immediately after the first cell.

Return: [[1,1,1],[1,1,0]] (unchanged) ✓
(No infinite loop thanks to ans[nrow][ncol] != newColor check!)
```

### Trace 3: Single Cell Grid

```
image=[[5]], sr=0, sc=0, color=3

iniColor = 5
DFS(0,0): ans[0][0]=3
  All 4 directions: out of bounds → skip

Return: [[3]] ✓
```

### Trace 4: Fill Entire Grid

```
image=[[1,1],[1,1]], sr=0, sc=0, color=9

iniColor=1
DFS(0,0): ans[0][0]=9
  Right (0,1): img==1, ans!=9 → DFS(0,1): ans[0][1]=9
    Down (1,1): img==1, ans!=9 → DFS(1,1): ans[1][1]=9
      Left (1,0): img==1, ans!=9 → DFS(1,0): ans[1][0]=9
        Up (0,0): ans[0][0]==9 → skip (visited)
        Down/Right: OOB → skip

Return: [[9,9],[9,9]] ✓
```

### Trace 5: L-shaped Connected Region

```
image=[[1,0,1],[1,0,1],[1,1,1]], sr=2, sc=2, color=5
iniColor = 1

The 1s form an L-shape:
  (0,0)       (0,2)
  (1,0)       (1,2)
  (2,0)(2,1)(2,2)  ← all connected through the bottom row

DFS from (2,2) floods through the entire L.
(0,0) and (1,0) are connected via (2,0)-(2,1)-(2,2)-(1,2)-(0,2).

Return:
[[5,0,5],
 [5,0,5],
 [5,5,5]] ✓

The 0s at (0,1),(1,1) act as walls — untouched.
```

### Trace 6: No Neighbors to Fill (Island of 1)

```
image=[[0,0,0],[0,1,0],[0,0,0]], sr=1, sc=1, color=7

iniColor = 1
DFS(1,1): ans[1][1]=7
  All 4 neighbors: image value == 0 != iniColor(1) → all skip

Return:
[[0,0,0],
 [0,7,0],
 [0,0,0]] ✓  (Only the single starting pixel changed)
```

---

## Edge Cases

### Case 1: newColor Same as iniColor

```
Input: image=[[1,1,1]], sr=0, sc=0, color=1
- iniColor==newColor
- DFS(0,0): ans[0][0]=1. Neighbors: ans already==1 → visited guard triggers.
- No infinite loop.
Output: [[1,1,1]] (unchanged) ✓
```

### Case 2: Single Pixel, Same Color

```
Input: image=[[3]], sr=0, sc=0, color=3
- DFS(0,0): ans[0][0]=3. No neighbors.
Output: [[3]] ✓
```

### Case 3: Starting Pixel Surrounded by Walls

```
Input: image=[[0,1,0],[1,5,1],[0,1,0]], sr=1, sc=1, color=9
- iniColor=5. All 4 neighbors have value 1 ≠ 5 → walls.
- Only (1,1) gets filled.
Output: [[0,1,0],[1,9,1],[0,1,0]] ✓
```

### Case 4: Full Grid Same Color

```
Input: n×m grid all same color. DFS visits every cell.
- Recursion depth up to n×m. May stack overflow for very large grids.
- Use iterative BFS for grids larger than ~10^4 cells.
Output: entire grid filled with newColor ✓
```

---

## Time Complexity

- **O(n × m)** where n = rows, m = columns
- Each cell is visited at most once (visited guard prevents revisits)
- Creating the `ans` copy: O(n×m)
- DFS traversal: O(n×m) in worst case (all cells same color)
- Total: **O(n × m)**

---

## Space Complexity

- **O(n × m)** extra space
- `ans` grid (copy of image): O(n×m)
- Recursion call stack: O(n×m) in worst case (entire grid same color, DFS goes n×m deep)
- Total extra space: **O(n × m)**

---

## Key Insights

### Why Separate `image` and `ans`?

```
Reading from image (original) + writing to ans (result):

Benefit 1 — Correct iniColor checks:
  image[nrow][ncol] == iniColor always checks the TRUE original color.
  If we wrote to image directly and then checked it, we'd be
  checking the already-changed color → wrong spread decisions.

Benefit 2 — Clean visited tracking:
  ans[nrow][ncol] != newColor is our visited guard.
  If we only had one grid, filled cells would confuse the
  "is this original color?" check.

Separation = clean logic. Two roles, two grids.
```

### `ans[nrow][ncol] != newColor` — Doing Double Duty

```
This single condition serves two purposes simultaneously:

Purpose 1 — Visited guard:
  Prevents revisiting an already-filled cell.
  Once ans[r][c] = newColor, no neighbor will recurse into it again.

Purpose 2 — iniColor == newColor safety:
  If iniColor == newColor, every cell matching iniColor would
  pass the image[nrow][ncol] == iniColor check forever.
  But ans[nrow][ncol] == newColor (already filled) → condition false → stop. ✓

One elegant check, two problems solved.
```

### Flood Fill vs Number of Islands vs Rotting Oranges

```
All three are "spread through a 2D grid" problems.
The difference is the goal:

Flood Fill:
  → Recolor a connected region
  → DFS, use ans != newColor as visited guard
  → Return modified grid

Number of Islands:
  → Count separate connected regions of 1s
  → DFS/BFS, use visited[][] or modify grid to 0
  → Return count

Rotting Oranges:
  → Find minimum time for spread to complete
  → Multi-source BFS with time tracking
  → Return max time or -1

Pattern is the same. Goal changes the implementation details.
```

### This IS the Paint Bucket Tool

```
Every image editor's paint bucket (fill tool) uses
exactly this algorithm:

Click pixel (sr, sc):
  1. Record the color at that pixel (iniColor).
  2. DFS/BFS outward.
  3. Recolor every connected same-color pixel to newColor.
  4. Stop at color boundaries or image edges.

You've just implemented a real-world tool from scratch. 🎨
```

---

## References

- 🔗 [LeetCode Problem — Flood Fill](https://leetcode.com/problems/flood-fill/)
- 🔗 [Flood Fill](https://www.youtube.com/watch?v=C-2_uSRli8o)
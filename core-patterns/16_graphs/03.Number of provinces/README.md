# Number of Provinces (Connected Components)

**Problem Link:** https://leetcode.com/problems/number-of-provinces/

## What is this Problem?

You have **n cities** and an `isConnected` matrix telling you which cities are **directly connected**. Cities that are directly or indirectly connected form a **province**. You need to **count how many provinces exist**.

- `isConnected[i][j] = 1` → city i and city j are directly connected
- `isConnected[i][j] = 0` → not directly connected
- A **province** = a group of cities all reachable from each other (directly or indirectly)

**Examples:**
```
isConnected:        isConnected:
[[1,1,0],           [[1,0,0],
 [1,1,0],            [0,1,0],
 [0,0,1]]            [0,0,1]]

Cities 0 and 1      All 3 cities are
are connected.      isolated from each other.
City 2 is alone.

Provinces = 2       Provinces = 3
```

---

## The Problem Explained

Think of it like **friend groups at a party**:

```
Party guests: Alice, Bob, Chris, Dave, Eve

Alice knows Bob  (connected)
Bob knows Chris  (connected → Alice, Bob, Chris are one group)
Dave knows Eve   (connected)

Groups (Provinces):
  Group 1: Alice, Bob, Chris
  Group 2: Dave, Eve

Answer = 2 provinces

It doesn't matter that Alice and Chris don't know each other directly —
they're in the same province because Bob connects them!
```

**Key idea:** Count how many **separate islands of connectivity** exist in the graph. Each time you start a fresh DFS from an unvisited node, you've found a new province!

---

## HOOK TO REMEMBER FOREVER

**"UNVISITED NODE = NEW PROVINCE, DFS FLOODS IT COMPLETELY"**

Every time you see "count connected components / provinces":
- ✅ Loop through every node 0 to n-1
- ✅ If a node is unvisited → it's a new province! Increment counter
- ✅ DFS from that node to mark ALL nodes in the same province as visited
- ✅ Continue the loop — next unvisited node is yet another province
- ✅ O(n²) time for adjacency matrix input
- ✅ O(n) extra space for visited array + recursion stack

**Remember: DFS is the flood fill — one DFS call colors an entire province. Count how many times you had to start a fresh DFS!** 🏝️

---

## How It Works Step By Step

### The Strategy

```
isConnected:
     0  1  2
0 [[ 1, 1, 0 ],
1  [ 1, 1, 0 ],
2  [ 0, 0, 1 ]]

vis = [0, 0, 0]
cnt = 0

i=0: vis[0]==0 → NEW PROVINCE! cnt=1
  DFS(0):
    Mark vis[0]=1
    Check row 0: isConnected[0][0]=1 but 0==node, isConnected[0][1]=1 and vis[1]=0 → DFS(1)
      DFS(1):
        Mark vis[1]=1
        Check row 1: isConnected[1][0]=1 but vis[0]=1, isConnected[1][2]=0 → skip
      ← return
  ← return
  vis = [1, 1, 0]

i=1: vis[1]==1 → skip (already in province 1)

i=2: vis[2]==0 → NEW PROVINCE! cnt=2
  DFS(2):
    Mark vis[2]=1
    Check row 2: isConnected[2][0]=0, isConnected[2][1]=0 → nothing to visit
  ← return
  vis = [1, 1, 1]

Return cnt = 2 ✓
```

### Visual Animation

```
Initial state:
Cities: 0   1   2
vis:   [0,  0,  0]   cnt = 0

i=0: Unvisited! → cnt = 1, launch DFS(0)
  DFS floods: marks 0 ✓, finds 1 connected → marks 1 ✓

vis:   [1,  1,  0]   cnt = 1
         ↑   ↑
     Province 1 fully colored!

i=1: Already visited → skip

i=2: Unvisited! → cnt = 2, launch DFS(2)
  DFS floods: marks 2 ✓, no connections

vis:   [1,  1,  1]   cnt = 2
                 ↑
     Province 2 fully colored!

Loop ends → return 2 ✓
```

---

## Code Full Solution

```cpp
class Solution {
public:
    void dfs(int node, vector<int> &vis, vector<vector<int>>& isConnected, int n) {
        vis[node] = 1;
        for (int i = 0; i < n; i++) {
            if (!vis[i] && isConnected[node][i] == 1) {
                dfs(i, vis, isConnected, n);
            }
        }
    }

    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<int> vis(n, 0);
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(i, vis, isConnected, n);
                cnt++;
            }
        }
        return cnt;
    }
};
```

---

## Code Explanation

### The Driver Function

```cpp
int n = isConnected.size();
vector<int> vis(n, 0);
int cnt = 0;
```

- **`n`:** Number of cities (matrix is n×n)
- **`vis`:** Size-n array, all 0 — tracks which cities have been visited
- **`cnt`:** Province counter, starts at 0

```cpp
for (int i = 0; i < n; i++) {
    if (!vis[i]) {
        dfs(i, vis, isConnected, n);
        cnt++;
    }
}
return cnt;
```

**The outer loop is the province detector:**
```
Think of it as scanning cities one by one.
When you find an unvisited city, you know two things:
  1. It belongs to a brand new province (never seen before)
  2. DFS will find and mark ALL cities in that same province

After DFS returns, every city reachable from i is marked.
So the next time the loop finds an unvisited city,
it is GUARANTEED to be in a different province.
```

---

### The DFS Function

```cpp
void dfs(int node, vector<int> &vis, vector<vector<int>>& isConnected, int n) {
    vis[node] = 1;
    for (int i = 0; i < n; i++) {
        if (!vis[i] && isConnected[node][i] == 1) {
            dfs(i, vis, isConnected, n);
        }
    }
}
```

**Mark first, then explore:**

```cpp
vis[node] = 1;
```
- Mark the current city visited immediately
- Prevents infinite recursion on cycles (A→B→A→B...)

**Scan the full row of the matrix:**

```cpp
for (int i = 0; i < n; i++) {
    if (!vis[i] && isConnected[node][i] == 1) { ... }
}
```

- **Why loop from 0 to n?** Because the input is an **adjacency matrix**, not an adjacency list. Every row has n entries — we scan all of them.
- **Two conditions must both be true:**
  - `isConnected[node][i] == 1` → there's an edge between node and i
  - `!vis[i]` → i hasn't been visited yet

```
isConnected[node] = [0, 1, 0, 1]
                      ↑  ↑  ↑  ↑
                      i=0 i=1 i=2 i=3

i=0: isConnected=0 → skip (no edge)
i=1: isConnected=1, vis[1]=0 → DFS(1) ✓
i=2: isConnected=0 → skip (no edge)
i=3: isConnected=1, vis[3]=0 → DFS(3) ✓
```

**Why adjacency matrix and not list?**
```
Adjacency list: adj[node] = [1, 3]  → loop over neighbors directly
Adjacency matrix: isConnected[node] = [0,1,0,1] → must scan entire row

This problem gives a matrix, so we loop i from 0 to n-1
and check isConnected[node][i] == 1 to find neighbors.
```

---

## Complete Example Traces

### Trace 1: Two Provinces

```
n=3, isConnected:
[[1,1,0],
 [1,1,0],
 [0,0,1]]

vis=[0,0,0], cnt=0

i=0: not visited → cnt=1, DFS(0)
  vis[0]=1
  i=0: isConnected[0][0]=1, but vis[0]=1 → skip
  i=1: isConnected[0][1]=1, vis[1]=0 → DFS(1)
    vis[1]=1
    i=0: isConnected[1][0]=1, vis[0]=1 → skip
    i=1: isConnected[1][1]=1, vis[1]=1 → skip
    i=2: isConnected[1][2]=0 → skip
  ← return
  i=2: isConnected[0][2]=0 → skip
← return

vis=[1,1,0], cnt=1

i=1: vis[1]=1 → skip

i=2: not visited → cnt=2, DFS(2)
  vis[2]=1
  i=0: isConnected[2][0]=0 → skip
  i=1: isConnected[2][1]=0 → skip
  i=2: isConnected[2][2]=1, vis[2]=1 → skip
← return

vis=[1,1,1], cnt=2

Return 2 ✓
```

### Trace 2: All Cities in One Province

```
n=3, isConnected:
[[1,1,1],
 [1,1,1],
 [1,1,1]]

vis=[0,0,0], cnt=0

i=0: not visited → cnt=1, DFS(0)
  vis[0]=1
  i=1: connected, not visited → DFS(1)
    vis[1]=1
    i=0: visited → skip
    i=2: connected, not visited → DFS(2)
      vis[2]=1
      i=0: visited → skip
      i=1: visited → skip
    ← return
  ← return
  i=2: visited → skip
← return

vis=[1,1,1], cnt=1

i=1: visited → skip
i=2: visited → skip

Return 1 ✓
(All cities in one giant province)
```

### Trace 3: All Cities Isolated

```
n=3, isConnected:
[[1,0,0],
 [0,1,0],
 [0,0,1]]

vis=[0,0,0], cnt=0

i=0: not visited → cnt=1, DFS(0)
  vis[0]=1, no connected unvisited neighbors
← return

i=1: not visited → cnt=2, DFS(1)
  vis[1]=1, no connected unvisited neighbors
← return

i=2: not visited → cnt=3, DFS(2)
  vis[2]=1, no connected unvisited neighbors
← return

Return 3 ✓
(Every city is its own province)
```

### Trace 4: Chain of Cities (Indirect Connection)

```
n=4, isConnected:
[[1,1,0,0],   0-1
 [1,1,1,0],   1-2
 [0,1,1,1],   2-3
 [0,0,1,1]]

vis=[0,0,0,0], cnt=0

i=0: not visited → cnt=1, DFS(0)
  vis[0]=1
  i=1: connected → DFS(1)
    vis[1]=1
    i=0: visited → skip
    i=2: connected → DFS(2)
      vis[2]=1
      i=1: visited → skip
      i=3: connected → DFS(3)
        vis[3]=1, no new neighbors
      ← return
    ← return
  ← return

vis=[1,1,1,1], cnt=1

i=1,2,3: all visited → skip

Return 1 ✓
(0→1→2→3 all connected indirectly → 1 province!)
```

### Trace 5: Two Separate Pairs

```
n=4, isConnected:
[[1,1,0,0],   0-1 connected
 [1,1,0,0],   2-3 connected
 [0,0,1,1],   no cross-connections
 [0,0,1,1]]

vis=[0,0,0,0], cnt=0

i=0: not visited → cnt=1, DFS(0)
  vis[0]=1
  i=1: connected → DFS(1) → vis[1]=1, neighbors 0 visited
← return
vis=[1,1,0,0]

i=1: visited → skip

i=2: not visited → cnt=2, DFS(2)
  vis[2]=1
  i=3: connected → DFS(3) → vis[3]=1, neighbors 2 visited
← return
vis=[1,1,1,1]

i=3: visited → skip

Return 2 ✓
```

### Trace 6: Single City

```
n=1, isConnected: [[1]]

vis=[0], cnt=0

i=0: not visited → cnt=1, DFS(0)
  vis[0]=1
  i=0: isConnected[0][0]=1 but vis[0]=1 → skip
← return

Return 1 ✓
(One city = one province, always)
```

---

## Edge Cases

### Case 1: Single City

```
Input: isConnected=[[1]]
- Only one city, one province.
Output: 1 ✓
```

### Case 2: All Isolated Cities

```
Input: Identity matrix (1s on diagonal only)
- Every city is its own province.
- DFS from each city visits only itself.
Output: n ✓
```

### Case 3: All Cities Fully Connected

```
Input: Matrix of all 1s
- One DFS from city 0 visits every city.
- Loop sees all remaining as visited.
Output: 1 ✓
```

### Case 4: Diagonal is Always 1

```
isConnected[i][i] = 1 always (a city is connected to itself)
- In the DFS loop: when i==node, vis[node] is already 1 → skip
- The self-loop never causes a re-visit or infinite recursion ✓
```

### Case 5: Large n, One Massive Province

```
Input: n=1000, all cities connected in a chain
- DFS from 0 goes 1000 calls deep
- All marked in one shot
- Recursion depth = n → risk of stack overflow for very large n
Output: 1 ✓ (but use iterative DFS for n > 10^4)
```

---

## Time Complexity

- **O(n²)** where n = number of cities
- The outer loop runs n times
- Each DFS call scans a full row of the matrix → O(n) per call
- Each city is visited exactly once → total DFS work = O(n²)
- The matrix itself is n×n, so O(n²) is optimal for this input format

---

## Space Complexity

- **O(n)** extra space
- `vis` array of size n → O(n)
- Recursion call stack: depth up to n in worst case (all cities in one chain) → O(n)
- Total extra space: **O(n)**

---

## Key Insights

### Why cnt++ is AFTER the DFS call

```cpp
if (!vis[i]) {
    dfs(i, vis, isConnected, n);
    cnt++;          ← after DFS, not before
}
```

```
When we reach an unvisited node i, we don't yet know
how many nodes are in its province — we just know it's a new one.

DFS runs and marks every city in that province as visited.
THEN we count it: "that entire flood fill = 1 province."

If we incremented before DFS:
  Still works here, but after DFS is the natural read:
  "Launch DFS → it finishes → province found → count it."
```

### The Diagonal (isConnected[i][i] = 1)

```
Every city is connected to itself by definition.
The matrix always has 1s on the diagonal.

In our DFS inner loop:
  when i == node: vis[node] is already 1 → !vis[i] is false → skip ✓

The diagonal never causes a recursive self-call.
It's harmlessly skipped by the visited check.
```

### Adjacency Matrix vs Adjacency List DFS

```
This problem (adjacency matrix):
  for (int i = 0; i < n; i++) {
      if (!vis[i] && isConnected[node][i] == 1)
  }
  → Must scan entire row → O(n) per node → O(n²) total

Standard graph DFS (adjacency list):
  for (int neighbor : adj[node])
  → Only actual neighbors → O(degree) per node → O(V+E) total

Same logic, different input format!
```

### Why This Is "Connected Components"

```
This problem is exactly:
  "Count the number of connected components in an undirected graph"

Province = Connected Component

The pattern is universal:
  cnt = 0
  for each node:
      if not visited:
          DFS/BFS from node   ← flood fills one component
          cnt++

Works for any graph representation (matrix or list).
Memorize this pattern — it appears in dozens of problems!
```

### Visualizing the "Flood Fill" Mental Model

```
isConnected matrix as a map. Cities = islands.
Connections = bridges between islands.

Province 1:        Province 2:
  [0]--[1]            [2]

DFS from 0 is like pouring water on island 0.
Water flows across all bridges it can reach.
Every island that gets wet = same province.

When water stops spreading, count it as 1 province.
Find the next dry island → new province!
```

## References
https://www.youtube.com/watch?v=ACzkVtewUYA

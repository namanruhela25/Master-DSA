# BFS Traversal of a Graph

**Problem Link:** https://naukri.com/code360/problems/bfs-in-graph_973002

## What is this Problem?

You have a **graph of nodes** connected by edges and you need to **visit every node level by level**, starting from node 0.

BFS (Breadth-First Search) visits:
- All **immediate neighbors first**, then their neighbors, and so on
- Every node is visited **exactly once**

**Examples:**
```
Graph (0-indexed, 4 nodes):
0 -- 1
|    |
2 -- 3

BFS from node 0:
Output: [0, 1, 2, 3]
(0 visited first, then its neighbors 1 and 2, then their unvisited neighbor 3)

Another Graph:
0 -- 1 -- 3
|
2

BFS from node 0:
Output: [0, 1, 2, 3]
(0 first, then neighbors 1 and 2, then 1's unvisited neighbor 3)
```

---

## The Problem Explained

Think of it like **ripples spreading in a pond**:

```
Drop stone at node 0:

Wave 1 (Level 0):
    [0]
    ↓ spreads to neighbors

Wave 2 (Level 1):
    [1, 2]
    ↓ spreads to their unvisited neighbors

Wave 3 (Level 2):
    [3]
    ↓ no more new nodes

BFS order: 0 → 1 → 2 → 3
```

**Key idea:** Process nodes in the order you discover them — use a **queue** (First In, First Out)!


Example :
Facebook is using to find possible account you are searching , by searching it one level 

You —> friend —> friend —> (friend you are searching)

---

## HOOK TO REMEMBER FOREVER

**"PUSH START, MARK VISITED, POP AND EXPLORE"**

Every time you see "BFS traversal of a graph":
- ✅ Push the starting node into the queue and mark it visited
- ✅ Pop a node, add it to your answer
- ✅ Push all its **unvisited** neighbors into the queue and mark them visited
- ✅ Repeat until the queue is empty
- ✅ O(V + E) time — every node and edge visited once
- ✅ O(V) extra space for the visited array and queue

**Remember: Queue gives you level-by-level order. Mark visited BEFORE pushing, not after!** 🌊

---

## How It Works Step By Step

### The Strategy

```
Graph adjacency list:
0 → [1, 2]
1 → [0, 3]
2 → [0, 3]
3 → [1, 2]

Step 1: Push node 0 into queue, mark visited[0] = 1
  Queue: [0]   Visited: [1, 0, 0, 0]

Step 2: Pop 0, add to ans. Push unvisited neighbors 1, 2
  ans: [0]   Queue: [1, 2]   Visited: [1, 1, 1, 0]

Step 3: Pop 1, add to ans. Push unvisited neighbors (0 visited, 3 unvisited → push 3)
  ans: [0, 1]   Queue: [2, 3]   Visited: [1, 1, 1, 1]

Step 4: Pop 2, add to ans. Neighbors 0 and 3 are already visited
  ans: [0, 1, 2]   Queue: [3]   Visited: [1, 1, 1, 1]

Step 5: Pop 3, add to ans. All neighbors visited
  ans: [0, 1, 2, 3]   Queue: []

Queue empty → Done!
Result: [0, 1, 2, 3]
```

### Visual Animation: Graph with 4 nodes

```
Initial State:
Queue: [0]
Visited: [1, 0, 0, 0]
ans: []

After popping 0:
Queue: [1, 2]       ← 0's neighbors added
Visited: [1, 1, 1, 0]
ans: [0]

After popping 1:
Queue: [2, 3]       ← 3 added (0 already visited)
Visited: [1, 1, 1, 1]
ans: [0, 1]

After popping 2:
Queue: [3]          ← 0, 3 both visited, nothing new
Visited: [1, 1, 1, 1]
ans: [0, 1, 2]

After popping 3:
Queue: []           ← 1, 2 both visited, nothing new
Visited: [1, 1, 1, 1]
ans: [0, 1, 2, 3]

Queue empty → return ans!
```

---

## Code Full Solution

```cpp
vector<int> bfsTraversal(int n, vector<vector<int>> &adj) {
    vector<int> ans;
    queue<int> q;
    vector<int> visited(n, 0);

    q.push(0);
    visited[0] = 1;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        ans.push_back(node);

        for (int i = 0; i < adj[node].size(); i++) {
            if (!visited[adj[node][i]]) {
                q.push(adj[node][i]);
                visited[adj[node][i]] = 1;
            }
        }
    }

    return ans;
}
```

---

## Code Explanation

### Initialize Data Structures

```cpp
vector<int> ans;
queue<int> q;
vector<int> visited(n, 0);
```

- **`ans`:** Stores BFS order result to return at the end
- **`q`:** Queue drives the level-by-level traversal (FIFO order)
- **`visited`:** Size-n array initialized to 0; marks which nodes have been seen

**Why a queue?**
```
Stack (DFS): processes deepest node first → goes far away fast
Queue (BFS): processes earliest-seen node first → stays close, level by level
```

---

### Seed the Starting Node

```cpp
q.push(0);
visited[0] = 1;
```

- Push node 0 as the starting point
- Mark it visited immediately — **before** processing, not after!

**Why mark visited on push, not on pop?**
```
If we mark visited on pop:
  Node 3 could be pushed twice (once from node 1, once from node 2)
  → Duplicate entries in ans!

Marking on push:
  First time we see node 3 (from node 1), we push and mark
  Second time (from node 2), visited[3] is already 1 → skip ✓
```

---

### Main BFS Loop

```cpp
while (!q.empty()) {
    int node = q.front();
    q.pop();
    ans.push_back(node);
    ...
}
```

- **`q.front()`:** Peek at the oldest node in the queue (the one added earliest)
- **`q.pop()`:** Remove it from the front
- **`ans.push_back(node)`:** Record this node in the traversal order

This continues until the queue is empty — meaning all reachable nodes are processed.

---

### Explore Neighbors

```cpp
for (int i = 0; i < adj[node].size(); i++) {
    if (!visited[adj[node][i]]) {
        q.push(adj[node][i]);
        visited[adj[node][i]] = 1;
    }
}
```

**Loop:** Iterates over every neighbor of the current node

**Key operation:** `adj[node][i]` gives the i-th neighbor of `node`

**Why the visited check?**
```
Without check:
  Graph: 0--1--0 (0 and 1 connected)
  Pop 0 → push 1
  Pop 1 → push 0 again!
  Pop 0 → push 1 again!
  → Infinite loop! ❌

With check:
  Pop 0 → push 1 (mark visited)
  Pop 1 → 0 is visited, skip → done ✓
```

---

## Complete Example Traces

### Trace 1: Standard 4-Node Graph

```
adj = { {1,2}, {0,3}, {0,3}, {1,2} }

Initial:
  q=[0], visited=[1,0,0,0], ans=[]

Iteration 1: node=0
  Pop 0, ans=[0]
  Neighbor 1: not visited → push, mark
  Neighbor 2: not visited → push, mark
  q=[1,2], visited=[1,1,1,0]

Iteration 2: node=1
  Pop 1, ans=[0,1]
  Neighbor 0: visited → skip
  Neighbor 3: not visited → push, mark
  q=[2,3], visited=[1,1,1,1]

Iteration 3: node=2
  Pop 2, ans=[0,1,2]
  Neighbor 0: visited → skip
  Neighbor 3: visited → skip
  q=[3], visited=[1,1,1,1]

Iteration 4: node=3
  Pop 3, ans=[0,1,2,3]
  Neighbor 1: visited → skip
  Neighbor 2: visited → skip
  q=[]

Queue empty → return [0,1,2,3] ✓
```

### Trace 2: Linear Graph (Chain)

```
adj = { {1}, {0,2}, {1,3}, {2} }
0 -- 1 -- 2 -- 3

Initial:
  q=[0], visited=[1,0,0,0], ans=[]

Iteration 1: node=0
  Pop 0, ans=[0]
  Push 1, mark
  q=[1], visited=[1,1,0,0]

Iteration 2: node=1
  Pop 1, ans=[0,1]
  0 visited → skip
  Push 2, mark
  q=[2], visited=[1,1,1,0]

Iteration 3: node=2
  Pop 2, ans=[0,1,2]
  1 visited → skip
  Push 3, mark
  q=[3], visited=[1,1,1,1]

Iteration 4: node=3
  Pop 3, ans=[0,1,2,3]
  2 visited → skip
  q=[]

Return: [0,1,2,3] ✓
(Visits in chain order — same as DFS here, because graph is linear!)
```

### Trace 3: Star Graph

```
adj = { {1,2,3,4}, {0}, {0}, {0}, {0} }
      1
      |
4 -- 0 -- 2
      |
      3

Initial:
  q=[0], visited=[1,0,0,0,0], ans=[]

Iteration 1: node=0
  Pop 0, ans=[0]
  Push 1,2,3,4 (all unvisited), mark all
  q=[1,2,3,4], visited=[1,1,1,1,1]

Iterations 2-5:
  Pop 1 → ans=[0,1], no new neighbors
  Pop 2 → ans=[0,1,2], no new neighbors
  Pop 3 → ans=[0,1,2,3], no new neighbors
  Pop 4 → ans=[0,1,2,3,4], no new neighbors
  q=[]

Return: [0,1,2,3,4] ✓
(Center visited first, all spokes in order of adjacency list)
```

### Trace 4: Disconnected-looking but Connected Graph

```
adj = { {2}, {3}, {0,3}, {1,2} }
0 -- 2
     |  \
     3 -- 1

Initial:
  q=[0], visited=[1,0,0,0], ans=[]

Iteration 1: node=0
  Pop 0, ans=[0]
  Push 2, mark
  q=[2], visited=[1,0,1,0]

Iteration 2: node=2
  Pop 2, ans=[0,2]
  0 visited → skip
  Push 3, mark
  q=[3], visited=[1,0,1,1]

Iteration 3: node=3
  Pop 3, ans=[0,2,3]
  Push 1, mark
  2 visited → skip
  q=[1], visited=[1,1,1,1]

Iteration 4: node=1
  Pop 1, ans=[0,2,3,1]
  3 visited → skip
  q=[]

Return: [0,2,3,1] ✓
(Visits via the path it discovers, not by node number order!)
```

### Trace 5: Single Node

```
adj = { {} }  (n=1, no edges)

Initial:
  q=[0], visited=[1], ans=[]

Iteration 1: node=0
  Pop 0, ans=[0]
  No neighbors to iterate
  q=[]

Return: [0] ✓
(Single node — just returns itself)
```

### Trace 6: Two Nodes

```
adj = { {1}, {0} }  (n=2, one edge)
0 -- 1

Initial:
  q=[0], visited=[1,0], ans=[]

Iteration 1: node=0
  Pop 0, ans=[0]
  Push 1, mark
  q=[1], visited=[1,1]

Iteration 2: node=1
  Pop 1, ans=[0,1]
  0 visited → skip
  q=[]

Return: [0,1] ✓
```

---

## Edge Cases

### Case 1: Single Node, No Edges

```
Input: n=1, adj={{}}
- Push 0, mark visited
- Pop 0, add to ans. No neighbors.
- Queue empty.
Output: [0] ✓
```

### Case 2: All Nodes Connected to Each Other (Complete Graph)

```
Input: n=3, adj={{1,2},{0,2},{0,1}}
- Pop 0 → push 1, 2
- Pop 1 → 0 visited, 2 visited (already pushed)
- Pop 2 → all visited
Output: [0,1,2] ✓
(No duplicates because we mark on push!)
```

### Case 3: Long Chain

```
Input: 0-1-2-3-...-999
- Queue always has at most 1-2 elements
- Each node pushed and popped exactly once
Output: [0,1,2,...,999] ✓
(Still O(V+E) time!)
```

### Case 4: Node with Many Neighbors

```
Input: n=5, adj = {{1,2,3,4},{0},{0},{0},{0}}
- All neighbors of 0 get pushed in one shot
- Queue size peaks at 4
Output: [0,1,2,3,4] ✓
```

### Case 5: Graph with Cycles

```
Input: 0-1-2-0 (triangle)
adj = {{1,2},{0,2},{0,1}}
- Pop 0 → push 1,2
- Pop 1 → 0 visited, push nothing new (2 already pushed)
- Pop 2 → 0,1 both visited
Output: [0,1,2] ✓
(visited array prevents infinite loops in cycles)
```

---

## Time Complexity

- **O(V + E)** where V = number of vertices, E = number of edges
- Every node is pushed and popped from the queue exactly once → O(V)
- Every edge is examined once per endpoint → O(E)
- Total: O(V) + O(E) = **O(V + E)**

---

## Space Complexity

- **O(V)** — Linear extra space
- `visited` array of size V → O(V)
- Queue holds at most V nodes at a time → O(V)
- `ans` array stores all V nodes → O(V)
- Total extra space: **O(V)**

---

## Key Insights

### Why Queue and Not Stack?

```
With a Stack (gives DFS, not BFS):
  Graph: 0 connected to 1, 2; 1 connected to 3

  Push 0 → pop 0, push 2, 1
  Pop 1 (top) → push 3
  Pop 3 → done
  Pop 2 → done
  Order: 0, 1, 3, 2  ← depth-first (goes deep before wide)

With a Queue (gives BFS):
  Push 0 → pop 0, push 1, 2
  Pop 1 (front) → push 3
  Pop 2 → nothing new
  Pop 3 → done
  Order: 0, 1, 2, 3  ← breadth-first (level by level)
```

### Why Mark Visited on PUSH, Not Pop?

```
Graph: 0 connected to 1 and 2; both 1 and 2 connected to 3

If we mark visited on POP:
  Pop 0 → push 1, push 2
  Pop 1 → push 3 (mark 1 visited)
  Pop 2 → push 3 AGAIN! (3 not yet popped/marked)
  Pop 3 → mark visited
  Pop 3 → mark visited (duplicate!)
  ans = [0,1,2,3,3] ✗

If we mark visited on PUSH:
  Pop 0 → push 1 (mark), push 2 (mark)
  Pop 1 → push 3 (mark)
  Pop 2 → 3 already marked → skip
  Pop 3 → done
  ans = [0,1,2,3] ✓
```

### The Adjacency List Structure

```
adj[node] = list of all neighbors of node

For edge 0-1:
  adj[0] contains 1
  adj[1] contains 0  (undirected graph → both directions)

For directed graph (0→1):
  adj[0] contains 1
  adj[1] does NOT contain 0
```

### BFS vs DFS: When to Use BFS

```
Use BFS when you need:
✅ Shortest path in unweighted graph
✅ Level-by-level traversal
✅ Closest nodes first
✅ "Minimum steps to reach" problems

Use DFS when you need:
✅ Detect cycles
✅ Topological sort
✅ Path existence (any path, not shortest)
✅ Exhaustive exploration
```

---

## Visualization of BFS Levels

```
Graph:
    0
   / \
  1   2
 / \   \
3   4   5

Level 0: [0]           ← Start here
Level 1: [1, 2]        ← 0's neighbors
Level 2: [3, 4, 5]     ← 1's and 2's unvisited neighbors

BFS Output: [0, 1, 2, 3, 4, 5]

Queue state over time:
[0]          ← Initial
[1,2]        ← After processing 0
[2,3,4]      ← After processing 1
[3,4,5]      ← After processing 2
[4,5]        ← After processing 3
[5]          ← After processing 4
[]           ← After processing 5 → Done!
```

## Reference
- https://www.youtube.com/watch?v=Vtu7qgF0ksw&list=PLQEaRBV9gAFte7vWOl3AWFABndCRCsIRQ&index=3
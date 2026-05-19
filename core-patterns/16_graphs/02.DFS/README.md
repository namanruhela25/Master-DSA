# DFS Traversal of a Graph

**Problem Link:** https://www.geeksforgeeks.org/problems/depth-first-traversal-for-a-graph/1

## What is this Problem?

You have a **graph of nodes** connected by edges and you need to **visit every node by going as deep as possible** before backtracking, starting from node 0.

DFS (Depth-First Search) visits:
- Go **as far down one path as possible** before turning back
- Every node is visited **exactly once**

**Examples:**
```
Graph (0-indexed, 4 nodes):
0 -- 1
|    |
2 -- 3

DFS from node 0:
Output: [0, 1, 3, 2]
(0 → goes deep to 1 → goes deep to 3 → backtracks → 2)

Another Graph:
0 -- 1 -- 3
|
2

DFS from node 0:
Output: [0, 1, 3, 2]
(0 → 1 → 3 → dead end → backtrack → backtrack → 2)
```

---

## The Problem Explained

Think of it like **exploring a maze**:

```
You are at node 0. You pick a corridor and walk as far as you can.
When you hit a dead end, you backtrack to the last junction
and try the next unexplored corridor.

Maze exploration from node 0:
    0
   / \
  1   2
 / \
3   4

Step 1: At 0, go to 1 (first neighbor)
Step 2: At 1, go to 3 (first neighbor)
Step 3: At 3, dead end → backtrack to 1
Step 4: At 1, go to 4 (next neighbor)
Step 5: At 4, dead end → backtrack to 1 → backtrack to 0
Step 6: At 0, go to 2 (next neighbor)
Step 7: At 2, dead end → done!

DFS order: 0 → 1 → 3 → 4 → 2
```

**Key idea:** Go deep first, use a **call stack (recursion)** or an **explicit stack** to remember where to backtrack!

---

## HOOK TO REMEMBER FOREVER

**"GO DEEP, MARK VISITED, BACKTRACK WHEN STUCK"**

Every time you see "DFS traversal of a graph":
- ✅ Mark the current node visited before going anywhere
- ✅ Recurse (or push to stack) into each **unvisited** neighbor
- ✅ Backtrack automatically when no unvisited neighbors remain
- ✅ O(V + E) time — every node and edge touched once
- ✅ O(V) extra space for visited array + recursion/stack depth

**Remember: DFS goes as deep as possible before coming back. Recursion IS the stack!** 🔍

---

## Two Approaches

There are **two valid ways** to implement DFS:

| | Recursive | Iterative (Stack) |
|---|---|---|
| Stack used | Call stack (implicit) | Explicit `stack<int>` |
| Code length | Shorter, elegant | Slightly longer |
| visited mark | On entry to function | On pop from stack |
| Stack overflow risk | Yes, for huge graphs | No |
| Order matches recursion | ✅ Yes | ✅ Yes (if push in reverse) |

---

## How It Works Step By Step

### Recursive Strategy

```
Graph adj:
0 → [1, 2]
1 → [0, 3]
2 → [0, 3]
3 → [1, 2]

Call helper(0):
  Mark visited[0]=true, res=[0]
  Neighbor 1: not visited → call helper(1)
    Mark visited[1]=true, res=[0,1]
    Neighbor 0: visited → skip
    Neighbor 3: not visited → call helper(3)
      Mark visited[3]=true, res=[0,1,3]
      Neighbor 1: visited → skip
      Neighbor 2: not visited → call helper(2)
        Mark visited[2]=true, res=[0,1,3,2]
        Neighbor 0: visited → skip
        Neighbor 3: visited → skip
      ← return from helper(2)
    ← return from helper(3)
  ← return from helper(1)
  Neighbor 2: visited → skip
← return from helper(0)

Result: [0, 1, 3, 2]
```

### Iterative (Stack) Strategy

```
Step 1: Push 0 into stack
  Stack: [0]   Visited: [0,0,0,0]   ans: []

Step 2: Pop 0. Not visited → mark, add to ans. Push neighbors in REVERSE order (2 first, then 1)
  Stack: [2,1]   Visited: [1,0,0,0]   ans: [0]

Step 3: Pop 1 (top). Not visited → mark, add to ans. Push 3 (0 already visited; reverse order)
  Stack: [2,3]   Visited: [1,1,0,0]   ans: [0,1]

Step 4: Pop 3. Not visited → mark, add to ans. 1 visited, push 2
  Stack: [2,2]   Visited: [1,1,0,1]   ans: [0,1,3]

Step 5: Pop 2. Not visited → mark, add to ans. 0,3 visited → nothing to push
  Stack: [2]   Visited: [1,1,1,1]   ans: [0,1,3,2]

Step 6: Pop 2. Already visited → continue (🔑 critical check!)
  Stack: []   Visited: [1,1,1,1]   ans: [0,1,3,2]

Stack empty → Done!
Result: [0, 1, 3, 2]
```

---

## Code — Recursive Solution

```cpp
class Solution {
  public:
    void helper(int idx, vector<vector<int>> &adj, vector<bool> &visited, vector<int> &res) {
        visited[idx] = true;
        res.push_back(idx);
        for (int neighbor : adj[idx]) {
            if (visited[neighbor] == false) helper(neighbor, adj, visited, res);
        }
    }

    vector<int> dfs(vector<vector<int>>& adj) {
        vector<bool> visited(adj.size(), false);
        vector<int> res;
        helper(0, adj, visited, res);
        return res;
    }
};
```

---

## Recursive Code Explanation

### The Driver Function

```cpp
vector<bool> visited(adj.size(), false);
vector<int> res;
helper(0, adj, visited, res);
return res;
```

- **`visited`:** Boolean array of size n, all false initially
- **`res`:** Accumulates the traversal order
- **`helper(0, ...)`:** Kicks off DFS from node 0
- Both `visited` and `res` are passed **by reference** — all recursive calls share the same arrays

---

### The Recursive Helper

```cpp
void helper(int idx, ...) {
    visited[idx] = true;
    res.push_back(idx);
    for (int neighbor : adj[idx]) {
        if (visited[neighbor] == false) helper(neighbor, adj, visited, res);
    }
}
```

**Three things happen every time helper is called:**

```
1. Mark current node visited
   visited[idx] = true
   → Prevents any future call from revisiting this node

2. Record the node
   res.push_back(idx)
   → Adds to result in the order we first reach each node

3. Recurse into unvisited neighbors
   for each neighbor: if not visited → call helper(neighbor)
   → Goes as deep as possible before returning
```

**Why mark visited BEFORE the loop?**
```
Graph: 0 -- 1 -- 0 (0 and 1 connected to each other)

Without marking first:
  helper(0) → loop → helper(1) → loop → helper(0) → ...
  Infinite recursion! Stack overflow! ❌

With marking first:
  helper(0): mark 0, loop → neighbor 1 not visited
  helper(1): mark 1, loop → neighbor 0 IS visited → skip
  Return to helper(0): done ✓
```

---

## Code — Iterative Stack Solution

```cpp
class Solution {
public:
    vector<int> dfs(vector<vector<int>>& adj) {
        int n = adj.size();
        vector<int> visited(n, 0);
        vector<int> ans;
        stack<int> st;

        st.push(0);

        while (!st.empty()) {
            int node = st.top();
            st.pop();

            if (visited[node]) continue;   // 🔑 critical check

            visited[node] = 1;
            ans.push_back(node);

            for (int i = adj[node].size() - 1; i >= 0; i--) {
                int neigh = adj[node][i];
                if (!visited[neigh]) {
                    st.push(neigh);
                }
            }
        }

        return ans;
    }
};
```

---

## Iterative Code Explanation

### Initialize and Seed

```cpp
vector<int> visited(n, 0);
vector<int> ans;
stack<int> st;
st.push(0);
```

- **`visited`:** All zeros; marks processed nodes
- **`st`:** Explicit stack replaces the call stack from recursion
- **Push node 0** to start — but do NOT mark visited yet (unlike BFS!)

**Key difference from BFS:**
```
BFS → Mark visited on PUSH (queue, FIFO)
DFS iterative → Mark visited on POP (stack, LIFO)

Why? A node can be pushed multiple times by different neighbors
before it's ever popped. We check on pop whether it's already
been handled. The 🔑 continue guard handles this.
```

---

### The 🔑 Critical Check

```cpp
if (visited[node]) continue;
```

This single line is what makes iterative DFS correct.

**Why is it needed?**
```
Graph: 0 connected to 1 and 2; both 1 and 2 connected to 3

Stack after processing 0: [2, 1]  (pushed in reverse)
Pop 1 → push 3 (from 1)
Stack: [2, 3]

Pop 3 → mark visited, add to ans
Stack: [2]

Pop 2 → its neighbor 3 was already pushed before we marked it visited
  → we push 3 again!
Stack: [3]

Pop 3 → visited[3] is 1 → continue ← critical check saves us!
Stack: []

Without this check: 3 would be added to ans twice ❌
With this check:    3 is added to ans exactly once ✓
```

---

### Push Neighbors in Reverse Order

```cpp
for (int i = adj[node].size() - 1; i >= 0; i--) {
    int neigh = adj[node][i];
    if (!visited[neigh]) st.push(neigh);
}
```

**Why reverse?**
```
adj[0] = [1, 2]

Forward push (wrong order):
  Push 1 first, then 2
  Stack top: 2 → 2 gets processed first
  DFS order: 0, 2, ...  ← goes to 2 first!

Reverse push (correct):
  Push 2 first, then 1
  Stack top: 1 → 1 gets processed first
  DFS order: 0, 1, ...  ← matches recursive DFS ✓

Stack is LIFO: last pushed = first processed.
Reverse push makes the first neighbor get processed first.
```

---

## Complete Example Traces

### Trace 1: Standard 4-Node Graph (Recursive)

```
adj = { {1,2}, {0,3}, {0,3}, {1,2} }

helper(0):
  visited=[T,F,F,F], res=[0]
  neighbor 1 → not visited
    helper(1):
      visited=[T,T,F,F], res=[0,1]
      neighbor 0 → visited, skip
      neighbor 3 → not visited
        helper(3):
          visited=[T,T,F,T], res=[0,1,3]
          neighbor 1 → visited, skip
          neighbor 2 → not visited
            helper(2):
              visited=[T,T,T,T], res=[0,1,3,2]
              neighbor 0 → visited, skip
              neighbor 3 → visited, skip
            ← return
          ← return
        ← return
      ← return
  neighbor 2 → visited, skip
← return

Result: [0, 1, 3, 2] ✓
```

### Trace 2: Standard 4-Node Graph (Iterative Stack)

```
adj = { {1,2}, {0,3}, {0,3}, {1,2} }

Push 0. Stack: [0]

Pop 0. Not visited → mark, ans=[0]
  Push in reverse: push 2 then push 1
  Stack: [2,1]  visited=[1,0,0,0]

Pop 1. Not visited → mark, ans=[0,1]
  Push in reverse: 0 visited skip, push 3
  Stack: [2,3]  visited=[1,1,0,0]

Pop 3. Not visited → mark, ans=[0,1,3]
  Push in reverse: 2 not visited → push 2, 1 visited skip
  Stack: [2,2]  visited=[1,1,0,1]

Pop 2. Not visited → mark, ans=[0,1,3,2]
  0 visited skip, 3 visited skip. Push nothing.
  Stack: [2]  visited=[1,1,1,1]

Pop 2. visited[2]=1 → continue ← 🔑 critical check!
  Stack: []

Return: [0,1,3,2] ✓
```

### Trace 3: Linear Chain

```
adj = { {1}, {0,2}, {1,3}, {2} }
0 -- 1 -- 2 -- 3

Recursive:
helper(0) → helper(1) → helper(2) → helper(3)
  At 3: no unvisited neighbors, return
  At 2: 1 visited, return
  At 1: 0 visited, return
  At 0: done

Result: [0, 1, 2, 3] ✓
(Linear graph: DFS and BFS give same order!)
```

### Trace 4: Tree-shaped Graph

```
adj = { {1,2}, {0,3,4}, {0,5}, {1}, {1}, {2} }
      0
     / \
    1   2
   / \   \
  3   4   5

Recursive DFS from 0:
  Visit 0 → go to 1
  Visit 1 → go to 3
  Visit 3 → dead end, backtrack
  Visit 4 → dead end, backtrack to 1 → backtrack to 0
  Visit 2 → go to 5
  Visit 5 → dead end, backtrack

Result: [0, 1, 3, 4, 2, 5] ✓
(Goes all the way down left subtree before right subtree)
```

### Trace 5: Graph with Cycle

```
adj = { {1,2}, {0,2}, {0,1} }
Triangle: 0 -- 1 -- 2 -- 0

Recursive:
helper(0): visited[0]=T, res=[0]
  neighbor 1 → not visited
    helper(1): visited[1]=T, res=[0,1]
      neighbor 0 → visited, skip
      neighbor 2 → not visited
        helper(2): visited[2]=T, res=[0,1,2]
          neighbor 0 → visited, skip
          neighbor 1 → visited, skip
        ← return
      ← return
    ← return
  neighbor 2 → visited, skip
← return

Result: [0, 1, 2] ✓
(Cycle handled cleanly by visited check!)
```

### Trace 6: Single Node

```
adj = { {} }  (n=1, no edges)

Recursive:
helper(0): visited[0]=T, res=[0]
  No neighbors to iterate.

Result: [0] ✓

Iterative:
Push 0. Pop 0. Not visited → mark, ans=[0]. No neighbors. Stack empty.
Result: [0] ✓
```

---

## Edge Cases

### Case 1: Single Node, No Edges

```
Input: n=1, adj={{}}
Recursive: helper(0) → mark, record. No neighbors. Done.
Output: [0] ✓
```

### Case 2: Two Nodes, One Edge

```
Input: adj={{1},{0}}
helper(0) → mark 0, visit neighbor 1
  helper(1) → mark 1, neighbor 0 visited → skip
Output: [0, 1] ✓
```

### Case 3: Graph with All Nodes Connected to 0 (Star)

```
Input: adj={{1,2,3},{0},{0},{0}}
helper(0) → 0, neighbor 1 → helper(1) → dead end
back to 0, neighbor 2 → helper(2) → dead end
back to 0, neighbor 3 → helper(3) → dead end
Output: [0, 1, 2, 3] ✓
```

### Case 4: Dense Graph (Many Edges)

```
All nodes connected to all others.
DFS still visits each node exactly once.
visited array ensures no revisits regardless of edge count.
Output: depends on adjacency list order, but always all V nodes ✓
```

### Case 5: Long Chain (Stack Overflow Risk for Recursive)

```
Input: 0-1-2-3-...-100000 (linear chain)
Recursive: Call stack depth = 100000 → Stack Overflow! ❌
Iterative: Stack holds at most O(1) nodes at a time → Safe ✓

Use iterative DFS for very large or deep graphs!
```

---

## Time Complexity

- **O(V + E)** where V = number of vertices, E = number of edges
- Every node is visited exactly once → O(V)
- Every edge is checked once per endpoint → O(E)
- Total: O(V) + O(E) = **O(V + E)**

---

## Space Complexity

- **O(V)** — Linear extra space
- `visited` array → O(V)
- Recursive: call stack depth up to O(V) in worst case (linear chain)
- Iterative: explicit stack holds up to O(V) nodes
- `res`/`ans` stores all V nodes → O(V)
- Total extra space: **O(V)**

---

## Key Insights

### Recursive vs Iterative: Visited Marking Difference

```
Recursive DFS:
  Mark visited at the TOP of helper, before the loop
  → Node is marked the instant we "enter" it
  → Safe because a node is only entered if it wasn't visited

Iterative DFS:
  Mark visited AFTER popping, not after pushing
  → A node can be pushed multiple times (by different neighbors)
  → The 🔑 critical check (if visited → continue) deduplicates
  → Without this check: nodes appear multiple times in result
```

### Why DFS Visits in a Different Order Than BFS

```
Graph:
    0
   / \
  1   2
 / \
3   4

BFS (queue, level by level):
  Level 0: [0]
  Level 1: [1, 2]
  Level 2: [3, 4]
  Result: [0, 1, 2, 3, 4]

DFS (stack/recursion, depth first):
  Go deep: 0 → 1 → 3 → (backtrack) → 4 → (backtrack) → 2
  Result: [0, 1, 3, 4, 2]

BFS spreads wide. DFS dives deep.
```

### The Call Stack IS the Stack

```
In recursion, the function call stack stores:
  - Which node we're currently at
  - Which neighbor index we were about to try next
  - All the "return addresses" to backtrack to

helper(0) on stack
  └─ helper(1) on stack
       └─ helper(3) on stack  ← deepest point
       ↑ return to helper(1)
  ↑ return to helper(0)

The iterative version just makes this stack explicit:
stack<int> st;  ← same idea, manual control
```

### Reverse Push in Iterative = Same Order as Recursive

```
adj[0] = [1, 2]

Recursive visits neighbor 1 FIRST (left to right loop)
→ goes deep into 1 before ever touching 2

Iterative must mimic this:
  Push 2 first, then 1 (reverse)
  Stack top = 1 → pops 1 first ✓

  If we pushed 1 first then 2:
  Stack top = 2 → pops 2 first ✗ (different order than recursive)
```

### When to Use DFS Over BFS

```
✅ Use DFS for:
  - Detecting cycles in a graph
  - Topological sorting (DAGs)
  - Finding connected components
  - Path existence between two nodes
  - Solving mazes / puzzles
  - Tree traversals (pre/in/post-order)

✅ Use BFS for:
  - Shortest path in unweighted graph
  - Level-order traversal
  - "Minimum steps to reach" problems
  - Finding all nodes within distance k
```
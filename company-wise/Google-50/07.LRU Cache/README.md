# LRU Cache

## Problem Link
🔗 [LeetCode 146 — LRU Cache](https://leetcode.com/problems/lru-cache/)

---

## What is this Problem?

Design a cache of fixed capacity that evicts the **least recently used** entry when full. Both operations must run in **O(1)** average time.

```
get(key)      → value if present (and mark it most recently used), else -1
put(key, val) → insert or update; if size exceeds capacity, evict the LRU entry
```

```
LRUCache(2)
put(1,1)  put(2,2)      cache: 1→1, 2→2
get(1)    → 1           (1 is now most recent)
put(3,3)                evicts 2 → cache: 3→3, 1→1
get(2)    → -1
put(4,4)                evicts 1 → cache: 4→4, 3→3
get(1)    → -1
get(3)    → 3
get(4)    → 4
```

---

## The Idea

Two requirements fight each other:

```
"find a key fast"          → hash map
"move to front / drop the back fast" → ordered container
```

A hash map alone cannot answer "which key is least recently used?" without scanning. An array/list alone cannot look a key up in O(1). So use **both, and let each element know its position in the other**:

```
  unordered_map<key, {value, iterator}>          list<key>
  ┌──────────────────────────────┐               FRONT = most recent
  │ 1 → {1, ●──┐}                │                          │
  │ 3 → {3, ●──┼──┐}             │        dll:  3 ↔ 1 ↔ 2   │
  │ 4 → {4, ●──┼──┼──┐}          │                             BACK = least recent
  └────────────┼──┼──┘           │
               └──┴──────────────┴──► list nodes
```

- front of the list = most recently used; back = the eviction victim
- the map stores an **iterator into the list**, so `erase(it)` is O(1) — no search
- `get` and `put` both end with "move this key to the front"

```
get(key):
  miss → -1
  hit  → erase its node, push_front(key), update stored iterator, return value

put(key, value):
  exists → update value, move to front
  new    → push_front, insert map entry, one slot consumed
  over capacity → erase map entry for back(), pop_back()
```

---

## Code Full Solution

```cpp
class LRUCache {
public:
    list<int> dll;
    unordered_map<int,pair<int,list<int>::iterator>> mpp;
    int n;
    LRUCache(int capacity) {
        n = capacity;
    }
    void markRecentlyUsed(int &key) {
        dll.erase(mpp[key].second);
        dll.push_front(key);
        mpp[key].second = dll.begin();
    }
    int get(int key) {
        if(mpp.find(key) == mpp.end()) {
            return -1;
        }
        markRecentlyUsed(key);
        return mpp[key].first;
    }
    void put(int key, int value) {
        if(mpp.find(key)!=mpp.end()) {
            mpp[key].first = value;
            markRecentlyUsed(key);
        } else {
            dll.push_front(key);
            mpp[key] = {value,dll.begin()};
            n--;
        }
        if(n<0) {
            int key_to_del = dll.back();
            mpp.erase(key_to_del);
            dll.pop_back();
            n++;
        }
    }
};
```

---

## Code Explanation

### The Two Containers

```cpp
list<int> dll;
unordered_map<int,pair<int,list<int>::iterator>> mpp;
```

`dll` holds only **keys**, ordered by recency (front = newest). `mpp` maps each key to `{value, iterator into dll}`. The key appears in both, and that duplication is what makes O(1) possible: the map finds the value, the list finds the recency order, and the stored iterator lets each jump straight to the other.

`list` (not `vector`) because `erase` on a node is O(1) and iterators to other nodes stay valid. A `vector` would shift elements and invalidate everything.

### `markRecentlyUsed`

```cpp
dll.erase(mpp[key].second);   // O(1) — we already know the node
dll.push_front(key);
mpp[key].second = dll.begin(); // the iterator must be refreshed
```

The third line is the one that is easy to forget: after `erase` + `push_front`, the old iterator is dangling, and the map would keep pointing at freed memory.

As written the parameter is `int &key` — a non-const lvalue reference even though `key` is never modified. That blocks calls with an rvalue and implies mutation; `int key` (or `const int&`) would be honest. It compiles and behaves correctly here because both call sites pass a local `int` lvalue.

### `get`

```cpp
if(mpp.find(key) == mpp.end()) return -1;
markRecentlyUsed(key);
return mpp[key].first;
```

A *read* counts as a use, so a hit promotes the key. `mpp[key]` after the promotion still refers to the same entry (only its iterator changed), so returning `.first` is safe.

### `put` — Existing Key

```cpp
mpp[key].first = value;
markRecentlyUsed(key);
```

Only the value changes; `n` is untouched because no new slot was needed. Missing this branch is the classic LRU bug: the value update is silently dropped and the old value comes back from `get`.

### `put` — New Key

```cpp
dll.push_front(key);
mpp[key] = {value, dll.begin()};
n--;
```

`n` is used as **remaining capacity**, not size. It starts at `capacity`, decrements per insertion, and is restored on eviction — so `n < 0` means "one over capacity". That is a valid trick but the name is misleading (`slots` or `size`-plus-comparison would read better).

### Eviction

```cpp
int key_to_del = dll.back();
mpp.erase(key_to_del);
dll.pop_back();
n++;
```

Order matters: read the key **before** `pop_back` (the node is gone afterwards). Both erases happen, so no dangling iterator is left in the map and no orphan node in the list.

Because only one insertion can happen per `put`, a single `if` (not `while`) is sufficient — capacity never drops by more than one at a time.

---

## Full Trace: LeetCode example, capacity 2

```
dll = [ ]            (front → back)
n = 2

put(1,1)  not in map → push_front(1); map{1→(1,it)}; n=1
          dll = [1]
          n ≥ 0, no eviction

put(2,2)  not in map → push_front(2); map{1→(1,it), 2→(2,it)}; n=0
          dll = [2, 1]

get(1)    found → markRecentlyUsed(1)
          erase node(1) → dll=[2]; push_front(1) → dll=[1,2]; refresh iterator
          return 1 ✓

put(3,3)  not in map → push_front(3); map{...,3→(3,it)}; n=-1
          dll = [3, 1, 2]
          n < 0 → key_to_del = back() = 2
                  map.erase(2); dll.pop_back() → dll=[3,1]; n=0

get(2)    not in map → return -1 ✓

put(4,4)  not in map → push_front(4); n=-1
          dll = [4, 3, 1]
          evict back() = 1 → map.erase(1); dll=[4,3]; n=0

get(1)    not in map → -1 ✓
get(3)    found → mark: dll=[3,4]; return 3 ✓
get(4)    found → mark: dll=[4,3]; return 4 ✓
```

## Full Trace: capacity 1, with an update

```
n = 1, dll = [ ]

put(2,1)  new → dll=[2]; map{2→(1,it)}; n=0
get(2)    hit → dll=[2]; return 1 ✓

put(2,2)  EXISTS → value=2; mark → erase+push_front → dll=[2]; n stays 0
get(2)    hit → return 2 ✓          (update was applied)

put(1,1)  new → dll=[1,2]; n=-1
          evict back() = 2 → map.erase(2); dll=[1]; n=0
get(2)    → -1 ✓
get(1)    → 1 ✓
```

Note the eviction picks `2`, **not** the freshly inserted `1` — `push_front` guarantees the new key sits at the front and the victim is always at the back.

---

## Example Traces

### `put` on an Existing Key Does Not Evict

```
capacity 2: put(1,1), put(2,2) → full (n=0)
put(1,9): exists → n unchanged (0) → no eviction
cache: 1→9 (most recent), 2→2
get(2) → 2 ✓  (still present)
```

### `get` Refreshes Order

```
capacity 2: put(1,1), put(2,2) → dll=[2,1]
get(1) → dll=[1,2]
put(3,3) → evicts 2 (now LRU), dll=[3,1]
If get(1) had been skipped, put(3,3) would evict 1 instead.
```

### Repeated Access to One Key

```
capacity 2: put(1,1), put(2,2), get(1), get(1), get(1)
dll stays [1,2]; put(3,3) still evicts 2 ✓
Repeated hits do not accumulate state — each is erase + push_front.
```

---

## Edge Cases

### Capacity 1

Works: after each new insertion one eviction brings `n` back to 0, and the survivor is always the newest key ✓

### `get` on a Missing Key

Returns `-1` **without** touching `dll` — a miss must not change recency ✓

### Updating the Value of the Least Recently Used Key

`put` on an existing key promotes it, so the update also rescues it from eviction ✓ (see the capacity-1 trace: `put(2,2)` re-freshens `2`)

### No Duplicate Keys in `dll`

`markRecentlyUsed` always removes before inserting, and the new-key branch is only reached when the key is absent — so each key appears exactly once ✓

### Missing Includes

LeetCode provides `<list>` and `<unordered_map>`. Running this standalone needs both, plus `using namespace std;`.

---

## Time and Space Complexity

| Operation | Time |
|---|---|
| `get` | O(1) average |
| `put` | O(1) average |
| Constructor | O(1) |

| | Value |
|---|---|
| Space | O(capacity) |

```
Every operation does a constant number of hash lookups and list splices.
The O(1) rests entirely on the two links:
  map → list iterator  (so erase never searches)
  list node → key      (so eviction can erase the map entry)

Naive alternatives: vector + linear scan for recency → O(n) per op;
std::map keyed by timestamp → O(log n) per op, still correct but slower.
```

---

## Key Insight

```
"Fast lookup" and "fast reordering" are different data-structure jobs.
Do not try to make one structure do both — store a HANDLE instead.

The map holds {value, iterator into the list}. That iterator is the bridge:
it turns "remove this key from the middle of the list" from O(n) into O(1),
which is the only reason the whole design hits O(1).

Corollary, and the usual interview failure: when you erase a list node you
MUST also erase the map entry (and refresh the iterator on every move),
otherwise the two structures drift apart and you get dangling iterators or
zombie keys.
```

---

## References

- 🔗 [LeetCode 146 — LRU Cache](https://leetcode.com/problems/lru-cache/)
- 🔗 [cppreference — `std::list::erase`](https://en.cppreference.com/w/cpp/container/list/erase) (iterator validity guarantees)
- 🔗 [LeetCode 460 — LFU Cache](https://leetcode.com/problems/lfu-cache/) (harder sibling: frequency + recency)

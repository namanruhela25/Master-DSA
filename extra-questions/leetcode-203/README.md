# Remove Linked List Elements 

**Problem Link:** https://leetcode.com/problems/remove-linked-list-elements/

## What is this Problem?

We have a **linked list** (like a chain of train cars with numbers). We need to **remove all nodes that have a specific value** from the list.

**Linked List Example:**
```
1 → 2 → 6 → 3 → 4 → 5 → 6 → NULL
val = 6

After removing all 6s:
1 → 2 → 3 → 4 → 5 → NULL
```

---

## The Problem Explained 

### Tricky Part: What if head itself has the value?

```
Input: 6 → 6 → 6 → 1 → NULL
val = 6

The first nodes to remove are at the head!
After removing all 6s:
1 → NULL
```

We need to **handle head removal specially**!

---

## 🎯 HOOK TO REMEMBER FOREVER

### **"DUMMY NODE SAVES THE HEAD! SKIP MATCHING, KEEP MOVING"**

Every time you see a linked list problem with potential head removal:
- ✅ Create a **dummy node pointing to head** (safety net!)
- ✅ Use pointers to skip nodes that match
- ✅ Keep moving forward and fixing connections
- ✅ Return `dummy.next` as the new head!

**Remember: Dummy node = Freedom to remove head without special cases!** 🛡️

---

## How It Works Step By Step

### Example: Remove value 6 from `1 → 2 → 6 → 3 → 4 → 5 → 6 → NULL`

**Setup with Dummy Node:**
```
dummy(-1) → 1 → 2 → 6 → 3 → 4 → 5 → 6 → NULL
   ↑
 temp (points to dummy)
```

Note: dummy has value -1 (won't match anything)

**Step 1: temp at dummy**
```
Check temp->next = 1, 1 != 6? 
YES, move to next node

temp → 1
```

**Step 2: temp at node 1**
```
Check temp->next = 2, 2 != 6?
YES, move to next node

temp → 2
```

**Step 3: temp at node 2**
```
Check temp->next = 6, 6 == 6?
YES!! Skip this node!
temp->next = temp->next->next
temp->next now points to 3

dummy(-1) → 1 → 2 → 3 → ...
        temp→2
        (2's next is now 3, 6 is removed!)
```

**Step 4: temp still at node 2**
```
Check again: temp->next = 3, 3 != 6?
YES, move to next node

temp → 3
```

**Step 5: temp at node 3**
```
Check temp->next = 4, 4 != 6?
YES, move to next node

temp → 4
```

**Step 6: temp at node 4**
```
Check temp->next = 5, 5 != 6?
YES, move to next node

temp → 5
```

**Step 7: temp at node 5**
```
Check temp->next = 6, 6 == 6?
YES!! Skip this node!
temp->next = temp->next->next
temp->next now points to NULL

temp → 5 → NULL
```

**Step 8: temp at node 5**
```
Check temp->next again: is it NULL?
YES, inner while stops
Move to next

temp = temp->next = NULL
Outer while stops!
```

**Final Result:**
```
Return dummy.next:
1 → 2 → 3 → 4 → 5 → NULL ✓
```

---

## Code Full Solution

```cpp
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode dummy(-1, head);        // Create dummy node
        ListNode *temp = &dummy;         // Start at dummy
        
        while(temp != NULL) {            // While we have nodes
            // Remove all consecutive matching nodes
            while(temp->next != NULL && temp->next->val == val) {
                temp->next = temp->next->next;  // Skip the matching node
            }
            temp = temp->next;            // Move to next
        }
        
        return dummy.next;                // Return head (skip dummy)
    }
};
```

---

## Code Explanation 

### Step 1: Create Dummy Node

```cpp
ListNode dummy(-1, head);
ListNode *temp = &dummy;
```

- **`ListNode dummy(-1, head)`:** Create a new node
  - Value: -1 (will never match anything)
  - Next pointer: points to head
- **Why?** If head itself needs to be removed, dummy lets us handle it!

**Visual:**
```
Before: head → (rest of list)
After:  dummy → head → (rest of list)
```

- **`ListNode *temp = &dummy`:** temp pointer points to the dummy node
- We start from dummy, not from head!

### Step 2: Outer While Loop

```cpp
while(temp != NULL) {
```

- **Condition:** Keep going while temp is not NULL
- **Purpose:** Traverse the entire list from dummy to the end

### Step 3: Inner While Loop (Skip All Matching)

```cpp
    while(temp->next != NULL && temp->next->val == val) {
        temp->next = temp->next->next;
    }
```

- **`temp->next != NULL`:** Don't go beyond the list
- **`temp->next->val == val`:** Is the next node's value what we're removing?
  - YES → Skip it!
  - NO → Stop the inner loop

- **`temp->next = temp->next->next`:** Make current node skip the matching node
  - Connect current node directly to the node after the matching node

**Example:**
```
temp → A → 6 → B → ...
If 6 == val:
  temp->next becomes B
temp → A → B → ... (6 is removed!)
```

**Why inner while vs inner if?**
```
For: 1 → 6 → 6 → 6 → 2 → NULL, val = 6
If we use if: We only remove one 6 per node
If we use while: We remove ALL consecutive 6s!

With while:
temp at 1: Remove 6, then remove 6, then remove 6
temp->next becomes 2 ✓

With if:
temp at 1: Remove only one 6
Next iteration: Remove another 6
Slower, but same result
```

### Step 4: Move Forward

```cpp
    temp = temp->next;
}
```

- **After removing all matching from current node, move to next**
- If we just removed all trailing nodes, temp becomes NULL
- Outer while stops!

### Step 5: Return New Head

```cpp
return dummy.next;
```

- Return what dummy points to
- If head was removed, dummy now points to the new head
- If head wasn't removed, dummy still points to original head ✓

---

## Complete Example Trace

```
Input: head = 1→2→6→3→4→5→6→NULL, val = 6

dummy(-1) → 1 → 2 → 6 → 3 → 4 → 5 → 6 → NULL
  ↑
temp

Step 1: temp = dummy
  temp->next = 1, 1 != 6? Skip inner while
  temp = 1

Step 2: temp = 1
  temp->next = 2, 2 != 6? Skip inner while
  temp = 2

Step 3: temp = 2
  temp->next = 6, 6 == 6? Enter inner while!
    Remove: 2->next = 3
    (2→6 becomes 2→3)
    2->next = 3, 3 != 6? Skip
  temp = 3

Step 4: temp = 3
  temp->next = 4, 4 != 6? Skip inner while
  temp = 4

Step 5: temp = 4
  temp->next = 5, 5 != 6? Skip inner while
  temp = 5

Step 6: temp = 5
  temp->next = 6, 6 == 6? Enter inner while!
    Remove: 5->next = NULL
    (5→6 becomes 5→NULL)
    5->next = NULL, break
  temp = NULL

Step 7: temp = NULL, outer while stops

Final list: 1 → 2 → 3 → 4 → 5 → NULL
Return dummy.next = 1 → 2 → 3 → 4 → 5 → NULL ✓
```

---

## Edge Cases 

### Case 1: All elements are val
```
Input: 6 → 6 → 6 → NULL, val = 6

dummy → 6 → 6 → 6 → NULL
Remove all:
dummy → NULL

Return dummy.next = NULL ✓
```

### Case 2: Head is val
```
Input: 6 → 1 → 2 → NULL, val = 6

dummy → 6 → 1 → 2 → NULL
Remove head:
dummy → 1 → 2 → NULL

Return dummy.next = 1 → 2 → NULL ✓
(Without dummy, we'd need special handling!)
```

### Case 3: No elements to remove
```
Input: 1 → 2 → 3 → NULL, val = 6

dummy → 1 → 2 → 3 → NULL
No matches:
dummy → 1 → 2 → 3 → NULL

Return dummy.next = 1 → 2 → 3 → NULL ✓
```

---

## Time Complexity 

- **O(n)** where n = number of nodes
- We visit each node exactly once
- No nested loops that go beyond the list

---

## Space Complexity 

- **O(1)** - Only using a dummy node and temp pointer
- No extra data structures needed!

---

## Why Dummy Node is Genius 💡

**Without dummy node, we need special handling:**
```cpp
// Without dummy
if(head->val == val) {
    head = head->next;
}
// Then handle rest...
```

**With dummy node, we don't:**
```cpp
// With dummy
dummy.next = head;
// Handle all nodes uniformly!
// If head was removed, dummy.next points to new head automatically!
```

**Result:** Cleaner, simpler, fewer bugs! ✨

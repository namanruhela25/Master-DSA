# Baseball Game

**Problem Link:** https://leetcode.com/problems/baseball-game/

## What is this Problem?

We're tracking **scores in a baseball game**. We have a list of operations:

1. **Number (like "5")** → Add that score to records
2. **"+"** → Score = last 2 scores added together, add this new score
3. **"D"** → Score = last score × 2, add this new score
4. **"C"** → Cancel the last score (remove it from records)

We need to return the **total sum of all valid scores**.

**Example:**
```
Operations: ["5", "2", "C", "D", "+"]

"5"   →  Record: [5]      Sum: 5
"2"   →  Record: [5, 2]   Sum: 7
"C"   →  Record: [5]      Sum: 5      (cancel the 2!)
"D"   →  Record: [5, 10]  Sum: 15     (double 5 → 10)
"+"   →  Record: [5, 10, 15] Sum: 30  (5 + 10 = 15)

Final Sum: 30
```

---

## The Problem Explained

Think of it like a **scoreboard that can be edited**:
- Write a number
- Add last two numbers
- Double last number
- Erase last entry

Play continues, and we report the final score!

---

## HOOK TO REMEMBER FOREVER

### **"STACK FOR ORDER, SUM FOR TOTAL, OPS FOR RULES"**

Every time you see this problem:
- ✅ Use a **stack to remember scores in order**
- ✅ Keep **running sum** for efficiency
- ✅ Operations modify stack and sum together
- ✅ "C" is the only one that reduces sum

**Remember: Operations tell the game rules - follow them in order!** 🎮

---

## How It Works Step By Step

### Example: Process `["5", "2", "C", "D", "+"]`

**Start:**
```
Stack: (empty)
Sum: 0
```

**Step 1: Operation "5" (number)**
```
Add to stack and sum
Stack: [5]
Sum: 0 + 5 = 5
```

**Step 2: Operation "2" (number)**
```
Add to stack and sum
Stack: [5, 2]
Sum: 5 + 2 = 7
```

**Step 3: Operation "C" (cancel)**
```
Remove last score from stack and subtract from sum
Last score: 2
Stack: [5]
Sum: 7 - 2 = 5
```

**Step 4: Operation "D" (double)**
```
Get last score (5), double it (10), add to stack and sum
Last score: 5
New score: 5 × 2 = 10
Stack: [5, 10]
Sum: 5 + 10 = 15
```

**Step 5: Operation "+" (sum last two)**
```
Get last two scores: 10 and 5
Add them: 10 + 5 = 15
Add to stack and sum
Stack: [5, 10, 15]
Sum: 15 + 15 = 30
```

**Final Result:**
```
Stack: [5, 10, 15]
Total Sum: 30 ✓
```

---

## Code Full Solution

```cpp
class Solution {
public:
    int calPoints(vector<string>& operations) {
        int sum = 0;                           // Track total score
        stack<int> st;                         // Track individual scores in order
        
        for(auto &el : operations) {           // Process each operation
            
            if(el == "+") {                    // Add last two scores
                int top1 = st.top();           // Get last score
                st.pop();
                int top2 = st.top();           // Get second-to-last score
                st.push(top1);                 // Put first back
                int newscore = top1 + top2;    // Add them
                st.push(newscore);             // Push new score
                sum += newscore;               // Add to total
                
            } else if(el == "D") {             // Double last score
                int top1 = st.top();           // Get last score
                int doubleval = top1 * 2;      // Double it
                st.push(doubleval);            // Push to stack
                sum += doubleval;              // Add to total
                
            } else if(el == "C") {             // Cancel last score
                sum -= st.top();               // Reduce total
                st.pop();                      // Remove from stack
                
            } else {                           // It's a number
                int num = stoi(el);            // Convert string to integer
                sum += num;                    // Add to total
                st.push(num);                  // Add to stack
            }
        }
        
        return sum;                            // Return final total
    }
};
```

---

## Code Explanation 

### Setup

```cpp
int sum = 0;
stack<int> st;
```

- **`sum`:** Running total of all scores (for efficiency!)
- **`stack<int> st`:** Stack to remember scores in order

**Why use a stack?**
- Stack preserves order of scores
- Easy to get "last" score (top)
- Easy to remove last score (pop)

### Main Loop

```cpp
for(auto &el : operations) {
```

- Go through each operation string one by one
- **`el`:** Current operation string ("5", "+", "D", or "C")

---

## Operation 1: "+" (Add Last Two)

```cpp
if(el == "+") {
    int top1 = st.top();      // Get the topmost score (most recent)
    st.pop();                 // Remove it from stack temporarily
    int top2 = st.top();      // Now get the second-most recent
    st.push(top1);            // Put the first one back
    int newscore = top1 + top2;
    st.push(newscore);        // Add new score to stack
    sum += newscore;          // Add to total
}
```

**Why the pop and push dance?**
```
Stack has: [a, b, c]
                ↑ top

We need b and c (last two), but top is c

Step 1: top1 = c, pop()
       Stack: [a, b]
       
Step 2: top2 = b (now we can see it!)

Step 3: push(top1) = push(c)
       Stack: [a, b, c]
       
Step 4: newscore = c + b
       Stack: [a, b, c, (c+b)]
```

---

## Operation 2: "D" (Double)

```cpp
} else if(el == "D") {
    int top1 = st.top();        // Get last score
    int doubleval = top1 * 2;   // Double it
    st.push(doubleval);         // Add doubled score
    sum += doubleval;           // Add to total
}
```

**Simple! Just take top, double it, push it.**

**Example:**
```
Stack: [5, 10]
Last: 10
Doubled: 10 × 2 = 20
Stack: [5, 10, 20]
```

---

## Operation 3: "C" (Cancel)

```cpp
} else if(el == "C") {
    sum -= st.top();  // Subtract the last score from total
    st.pop();         // Remove it from stack
}
```

**This is the only operation that REDUCES the sum!**

**Example:**
```
Stack: [5, 10, 15]
Sum: 30
Last score: 15
After C:
  Sum: 30 - 15 = 15
  Stack: [5, 10]
```

---

## Operation 4: Number (like "5")

```cpp
} else {
    int num = stoi(el);  // Convert string "5" to integer 5
    sum += num;          // Add to total
    st.push(num);        // Add to stack
}
```

- **`stoi(el)`:** String to integer conversion
  - Example: stoi("42") = 42

**Example:**
```
el = "5"
num = stoi("5") = 5
Stack: [5]
Sum: 5
```

---

## Complete Example Trace

```
Operations: ["5", "2", "C", "D", "+"]

Initial: sum = 0, st = []

i=0: el = "5" (number)
     num = 5
     sum = 0 + 5 = 5
     st = [5]

i=1: el = "2" (number)
     num = 2
     sum = 5 + 2 = 7
     st = [5, 2]

i=2: el = "C" (cancel)
     sum = 7 - 2 = 5
     st = [5]

i=3: el = "D" (double)
     top1 = 5
     doubleval = 10
     sum = 5 + 10 = 15
     st = [5, 10]

i=4: el = "+" (add last two)
     top1 = 10
     pop() → st = [5]
     top2 = 5
     push(10) → st = [5, 10]
     newscore = 10 + 5 = 15
     sum = 15 + 15 = 30
     st = [5, 10, 15]

Return: 30 ✓
```

---

## Edge Cases

### Case 1: All Numbers
```
Input: ["10", "20", "30"]
sum = 10, st = [10]
sum = 30, st = [10, 20]
sum = 60, st = [10, 20, 30]
Output: 60
```

### Case 2: Cancel Everything
```
Input: ["5", "C"]
sum = 5, st = [5]
sum = 0, st = []
Output: 0
```

### Case 3: Complex Operations
```
Input: ["1", "+", "C", "D", "+"]
sum = 1, st = [1]
"+" → Can't add (need 2 items, only have 1)... Actually this would be invalid input
(Valid input guaranteed by problem)
```

### Case 4: Double Then Add
```
Input: ["2", "D", "+"]
num = 2: sum = 2, st = [2]
"D": sum = 6, st = [2, 4]
"+": sum = 6 + (4+2) = 12, st = [2, 4, 6]
Output: 12
```

---

## Why Stack?

**Stack properties we need:**
- Remember order of scores ✓
- Get most recent score easily ✓
- Remove most recent score easily ✓
- No random access needed

**Stack provides all of these optimally!**

---

## Time Complexity 

- **O(n)** where n = number of operations
- Each operation (push, pop, top) is O(1)
- Loop runs n times

---

## Space Complexity

- **O(n)** for the stack
- In worst case (all numbers, no cancels), stack has n elements

---

## Key Insights

### Two Variables Working Together
```
sum:    Tracks the total (for answer at end)
stack:  Tracks individual scores (for operations that need history)

Without sum: 
  Would need to recalculate total each time
  
Without stack:
  Couldn't implement "+", "D", "C" operations properly
```

### Why "C" Needs Only Sum (Not Stack)
```
When canceling, we only need:
1. Know how much to remove from sum → st.top()
2. Remove from stack → st.pop()

We DON'T recalculate entire sum!
```

This is efficient! ✨

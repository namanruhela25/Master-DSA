# Largest Number Problem 🔢

**Problem Link:** https://leetcode.com/problems/largest-number/

## What is this problem?

We are given a list of numbers. We need to **arrange them in a special order** so that when we put them together, we get the **biggest number possible**.

### Example:
If we have numbers: **3, 30, 34, 5, 9**

A normal way would give: 9, 5, 34, 30, 3 → **953430**

But the smart way gives: 9, 5, 34, 3, 30 → **9534330**

The second one is bigger! That's what we want. ✨

---

## The Main Idea (Intuition)

### How do we decide which number should come first?

Imagine you have two numbers: **3** and **30**

You can arrange them in two ways:
1. **3 then 30** → Makes **330**
2. **30 then 3** → Makes **303**

**330 > 303** ✓

So **3 should come before 30**.

That's the secret! 

### The Rule:
When comparing two numbers **A** and **B**:
- If **AB > BA**, then **A comes first**
- If **BA > AB**, then **B comes first**

---

## Step-by-Step Solution

### Step 1: Convert numbers to text
```
3, 30, 34, 5, 9  →  "3", "30", "34", "5", "9"
```
(We convert them to text/strings so we can combine them easily)

### Step 2: Sort using our special rule
Compare each pair using **AB vs BA** rule:
- "3" + "30" = "330" vs "30" + "3" = "303" → 330 > 303 ✓ So "3" comes first
- "5" + "34" = "534" vs "34" + "5" = "345" → 534 > 345 ✓ So "5" comes first
- "9" + "5" = "95" vs "5" + "9" = "59" → 95 > 59 ✓ So "9" comes first

After sorting: **9, 5, 34, 3, 30**

### Step 3: Combine them
Stick them all together:
```
"9" + "5" + "34" + "3" + "30" = "9534330"
```

### Step 4: Handle special case
If all numbers are 0 like [0, 0, 0], the answer should be "0" (not "000")

---

## Real-Life Example 

Imagine you have cards with numbers: **3, 30, 34, 5, 9**

You need to arrange these cards to make the biggest number when you put them side by side.

- Put **9** first (biggest single digit!)
- Then **5**
- Then **34** (bigger than 3 when put together)
- Then **3** 
- Then **30**

Result: **9534330** - That's the biggest! 🎉

---

## Time Complexity

- Converting to strings: **O(n)**
- Sorting: **O(n log n)**
- Combining strings: **O(n)**

**Total: O(n log n)** where n is the number of integers


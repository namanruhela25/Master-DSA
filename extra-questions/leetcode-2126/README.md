# Destroy the Asteroids

**Problem Link:** https://leetcode.com/problems/destroy-the-asteroids/

## What is this Problem?

You are in a spaceship with initial `mass`. You encounter asteroids with different masses. When you collide with an asteroid:
- **If your mass ≥ asteroid mass:** You destroy it and gain its mass
- **If your mass < asteroid mass:** You are destroyed

We need to determine if you can **destroy ALL asteroids** (return `true`) or if an asteroid will destroy you (return `false`).

**Key Points:**
- You can choose the order to encounter asteroids
- Goal: Find if there's ANY order that allows destruction of all
- Return true if possible, false otherwise
- Your mass increases after destroying each asteroid

**Examples:**
```
Input: mass = 10, asteroids = [3, 9, 19, 5, 21]
Output: true
Explanation:
- Order: [3, 5, 9, 19, 21]
- Start: mass = 10
- Meet 3: 10 >= 3 → destroy, mass = 10 + 3 = 13
- Meet 5: 13 >= 5 → destroy, mass = 13 + 5 = 18
- Meet 9: 18 >= 9 → destroy, mass = 18 + 9 = 27
- Meet 19: 27 >= 19 → destroy, mass = 27 + 19 = 46
- Meet 21: 46 >= 21 → destroy, mass = 46 + 21 = 67
- All destroyed! Return true

Input: mass = 5, asteroids = [4, 9, 23, 4]
Output: false
Explanation:
- Best order: [4, 4, 9, 23]
- Start: mass = 5
- Meet 4: 5 >= 4 → destroy, mass = 5 + 4 = 9
- Meet 4: 9 >= 4 → destroy, mass = 9 + 4 = 13
- Meet 9: 13 >= 9 → destroy, mass = 13 + 9 = 22
- Meet 23: 22 >= 23? NO! → destroyed
- Can't destroy all. Return false
```

---

## The Problem Explained

Imagine you're a spaceship with power level `mass`. You encounter asteroids and must decide the order to fight them.

**Strategy:** 
- Smaller asteroids = easier to defeat
- Defeating them increases your power
- Larger asteroids = harder, need more power first
- **Greedy approach:** Fight smaller asteroids first!

**Key insight:** 
If you can destroy asteroids in **increasing order of mass**, you have the best chance. This way, you keep gaining power before facing larger ones.

---

## HOOK TO REMEMBER FOREVER

### **"SORT SMALL-TO-LARGE, ACCUMULATE, THEN CHECK"**

Every time you see this problem:
- ✅ **Greedy strategy:** Destroy asteroids in **increasing order**
- ✅ **Count frequencies:** Multiple asteroids of same mass
- ✅ **Accumulate mass:** Add defeated asteroid mass to current mass
- ✅ **Check at each step:** Can you destroy the next asteroid?
- ✅ If yes at all steps, return **true**
- ✅ If blocked at any step, return **false**

**Remember: Gain power systematically before facing giants!** 🚀

---

## How It Works Step By Step

### Greedy Approach: Process Asteroids by Increasing Mass

**Why greedy works:**
- If you can't destroy a smaller asteroid now, defeating larger ones first won't help (your mass only increases by defeating asteroids)
- Defeating smaller asteroids first maximizes your mass for larger ones
- **Proof:** If you can defeat asteroids in some order, you can also defeat them in sorted order

### Example: mass = 10, asteroids = [3, 9, 19, 5, 21]

**Step 1: Count Asteroid Frequencies**
```
Original: [3, 9, 19, 5, 21]
Frequencies:
  3 → appears 1 time
  5 → appears 1 time
  9 → appears 1 time
  19 → appears 1 time
  21 → appears 1 time
```

**Step 2: Initialize**
```
max_asteroid = 21
freq array = [0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1]
                                        3  5        9                    19    21
curr_mass = 10
```

**Step 3: Process Asteroids in Order (1 to 21)**
```
i=1: freq[1]=0, skip
i=2: freq[2]=0, skip
i=3: freq[3]=1 (one asteroid of mass 3)
     curr_mass (10) >= 3? YES ✓
     curr_mass = 10 + 1*3 = 13
     
i=4: freq[4]=0, skip
i=5: freq[5]=1
     curr_mass (13) >= 5? YES ✓
     curr_mass = 13 + 1*5 = 18
     
i=6 to i=8: freq=0, skip

i=9: freq[9]=1
     curr_mass (18) >= 9? YES ✓
     curr_mass = 18 + 1*9 = 27
     
i=10 to i=18: freq=0, skip

i=19: freq[19]=1
      curr_mass (27) >= 19? YES ✓
      curr_mass = 27 + 1*19 = 46

i=20: freq[20]=0, skip

i=21: freq[21]=1
      curr_mass (46) >= 21? YES ✓
      curr_mass = 46 + 1*21 = 67

Loop completes without blocking
Return: true ✓
```

---

### Example: mass = 5, asteroids = [4, 9, 23, 4]

**Step 1: Count Frequencies**
```
Frequencies:
  4 → appears 2 times
  9 → appears 1 time
  23 → appears 1 time
```

**Step 2: Initialize**
```
max_asteroid = 23
freq array = [0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1]
                            4              9                                      23
curr_mass = 5
```

**Step 3: Process Asteroids in Order**
```
i=1 to i=3: freq=0, skip

i=4: freq[4]=2 (two asteroids of mass 4)
     curr_mass (5) >= 4? YES ✓
     curr_mass = 5 + 2*4 = 13

i=5 to i=8: freq=0, skip

i=9: freq[9]=1
     curr_mass (13) >= 9? YES ✓
     curr_mass = 13 + 1*9 = 22

i=10 to i=22: freq=0, skip

i=23: freq[23]=1
      curr_mass (22) >= 23? NO! ✗
      return false

Return: false ✓
```

---

## Code Full Solution

```cpp
class Solution {
public:
    bool asteroidsDestroyed(int mass, vector<int>& a) {
        int n = a.size();
        
        // Step 1: Find maximum asteroid mass
        int maxi = *max_element(a.begin(), a.end());
        
        // Step 2: Build frequency array
        vector<int> freq(maxi + 1, 0);
        for(int &el : a) {
            freq[el]++;
        }
        
        // Step 3: Process asteroids in increasing order
        long long curr = mass;
        for(int i = 1; i <= maxi; i++) {
            if(freq[i] > 0) {
                if(curr >= i) {
                    // Destroy all asteroids of mass i
                    curr += (long long)i * freq[i];
                } else {
                    // Can't destroy, blocked!
                    return false;
                }
            }
        }
        
        // Destroyed all asteroids
        return true;
    }
};
```

---

## Code Explanation

### Step 1: Find Maximum Asteroid

```cpp
int maxi = *max_element(a.begin(), a.end());
```

- **`max_element()`:** Returns iterator to largest element
- **`*`:** Dereference to get the value
- **`maxi`:** Upper bound for frequency array

**Why needed?**
```cpp
// If asteroids = [3, 5, 9]
// maxi = 9
// We only need freq array up to index 9
// Wasteful to allocate up to INT_MAX

// Creates array: freq[0..9]
// Instead of freq[0..INT_MAX]
```

---

### Step 2: Build Frequency Array

```cpp
vector<int> freq(maxi + 1, 0);
for(int &el : a) {
    freq[el]++;
}
```

- **`freq[i]`:** Count of asteroids with mass i
- **`maxi + 1`:** Array size (0 to maxi inclusive)
- **Loop:** Count each asteroid

**Example:**
```cpp
a = [3, 9, 3, 5]
maxi = 9

After loop:
freq[3] = 2 (two 3's)
freq[5] = 1
freq[9] = 1
freq[1] = 0, freq[2] = 0, etc.
```

**Why frequency array instead of sorting?**
```
Sorting approach: O(n log n) sorting time
Frequency approach: O(n + maxi) time
                   Faster when maxi is small relative to n

Frequency also reveals repeated asteroids naturally!
```

---

### Step 3: Process Asteroids in Order

```cpp
long long curr = mass;
for(int i = 1; i <= maxi; i++) {
    if(freq[i] > 0) {
        if(curr >= i) {
            curr += (long long)i * freq[i];
        } else {
            return false;
        }
    }
}
```

**Variable types:**
- **`long long curr`:** Current mass (can grow very large)
  - Start with `mass` (int)
  - Add `i * freq[i]` potentially many times
  - Can overflow if stored as int
  - Example: mass=1, asteroids=[1000000]*1000 → exceeds int

**Loop logic:**
- **`i = 1 to maxi`:** Iterate through all possible asteroid masses
- **`if(freq[i] > 0)`:** Only process if asteroids of this mass exist
- **`if(curr >= i)`:** Can we destroy asteroids of mass i?
  - YES: Add to current mass: `curr += i * freq[i]`
  - NO: Return false immediately

**Why `(long long)i * freq[i]`?**
```cpp
int i, freq[i];
i * freq[i]              // Result might overflow int
(long long)i * freq[i]   // Convert i to long long first, then multiply
                         // Result is long long (safe)

Example:
i = 1000000
freq[i] = 1000
i * freq[i] = 1000000 * 1000 = 1000000000 (fits in int: 2^31 ≈ 2.1B)

But if:
i = 1000000
freq[i] = 100000
i * freq[i] = 1000000 * 100000 = 100000000000 (overflows int!)
(long long)i * freq[i] = 100000000000LL (safe)
```

---

## Complete Example Trace

### Input: mass = 10, asteroids = [3, 9, 19, 5, 21]

```
Call asteroidsDestroyed(10, [3, 9, 19, 5, 21]):

Step 1: Find max
maxi = max(3, 9, 19, 5, 21) = 21

Step 2: Build frequency array
freq[0..21] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
               
Process 3: freq[3]++ → freq[3] = 1
Process 9: freq[9]++ → freq[9] = 1
Process 19: freq[19]++ → freq[19] = 1
Process 5: freq[5]++ → freq[5] = 1
Process 21: freq[21]++ → freq[21] = 1

freq = [0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1]

Step 3: Process in order
curr = 10

i=1: freq[1]=0, skip
i=2: freq[2]=0, skip
i=3: freq[3]=1
     10 >= 3? YES
     curr = 10 + 3*1 = 13

i=4: freq[4]=0, skip
i=5: freq[5]=1
     13 >= 5? YES
     curr = 13 + 5*1 = 18

i=6-8: freq=0, skip
i=9: freq[9]=1
     18 >= 9? YES
     curr = 18 + 9*1 = 27

i=10-18: freq=0, skip
i=19: freq[19]=1
      27 >= 19? YES
      curr = 27 + 19*1 = 46

i=20: freq[20]=0, skip
i=21: freq[21]=1
      46 >= 21? YES
      curr = 46 + 21*1 = 67

Loop completes normally
Return: true ✓
```

---

## Edge Cases

### Case 1: Single Asteroid (Destroyable)
```
Input: mass = 5, asteroids = [3]
5 >= 3? YES
Output: true ✓
```

### Case 2: Single Asteroid (Not Destroyable)
```
Input: mass = 5, asteroids = [10]
5 >= 10? NO
Output: false ✓
```

### Case 3: All Asteroids Same Mass
```
Input: mass = 5, asteroids = [2, 2, 2, 2, 2]
freq[2] = 5
5 >= 2? YES
curr = 5 + 2*5 = 15
Output: true ✓
```

### Case 4: Asteroids in Random Order
```
Input: mass = 10, asteroids = [21, 3, 5, 9, 19]
Processed in order: 3, 5, 9, 19, 21 (not input order)
Output: true (same as sorted example) ✓
```

### Case 5: Blocked by Medium Asteroid
```
Input: mass = 5, asteroids = [3, 10]
3: 5 >= 3? YES, curr = 8
10: 8 >= 10? NO
Output: false ✓
```

### Case 6: Large Numbers
```
Input: mass = 1, asteroids = [1000000000]
1 >= 1000000000? NO
Output: false ✓
```

---

## Why Greedy Works

**Theorem:** If you can destroy all asteroids in some order, you can also destroy them in **sorted (increasing) order**.

**Proof:**
- Suppose you can destroy in order: [a₁, a₂, ..., aₙ]
- Let's say this order is NOT sorted (e.g., aᵢ > aᵢ₊₁ somewhere)
- Your mass grows: mass → mass+a₁ → mass+a₁+a₂ → ... → mass+a₁+...+aₙ
- At step i: you have met a₁, a₂, ..., aᵢ (total added)
- At step i+1: you have met a₁, a₂, ..., aᵢ, aᵢ₊₁
- If you swap aᵢ and aᵢ₊₁:
  - Before swap: mass+a₁+...+aᵢ₋₁ >= aᵢ
  - You need: mass+a₁+...+aᵢ₋₁ >= aᵢ₊₁
  - But aᵢ₊₁ <= aᵢ (if we swap)
  - So: mass+a₁+...+aᵢ₋₁ >= aᵢ₊₁ ✓ (still true!)
- After defeating aᵢ₊₁ (now in position i): mass += aᵢ₊₁
- Then defeat aᵢ (now in position i+1): need mass+aᵢ₊₁ >= aᵢ
- But we know we had mass+...+aᵢ before, and now we have more!
- ✓ Still works!

**Result:** Any working order can be rearranged to sorted order without breaking!

---

## Time Complexity

- **Find max:** O(n) where n = number of asteroids
- **Build frequency:** O(n)
- **Process asteroids:** O(maxi) where maxi = largest asteroid mass
- **Total: O(n + maxi)**

**Best case:** O(n) when maxi ≈ n
**Worst case:** O(n + maxi) when maxi >> n

**Comparison:**
```
Sorting approach: O(n log n)
Frequency approach: O(n + maxi)

If maxi ≤ n log n → Frequency is better
If maxi > n log n → Sorting might be better
```

---

## Space Complexity

- **Frequency array:** O(maxi)
  - Size = maxi + 1
  - Only stores counts

**Overall: O(maxi)** 

---

## Key Insights

### Why `long long` for curr?

```cpp
long long curr = mass;
curr += (long long)i * freq[i];
```

- **Integer overflow prevention**
- Example: mass = 1, 1M asteroids of mass 1M each
- Total: 1 + 1M*1M = 10¹² (exceeds int 2.1×10⁹)
- long long supports up to ~9×10¹⁸

### Why Frequency Instead of Sorting?

**Frequency approach:**
- O(n + maxi) time
- O(maxi) space
- **Advantage:** Reveals repeated masses naturally

**Sorting approach:**
- O(n log n) time
- O(1) space (if in-place sort)
- **Advantage:** Simpler conceptually, but sorting has overhead

**For this problem:** Frequency is better when maxi is reasonable

### The Greedy Insight

The key insight is: **fighting smaller asteroids first maximizes your chances**

```
Fighting order matters!
Bad order:   [21] → fail immediately
Good order:  [3, 5, 9, 19, 21] → succeed
```

Greedy always chooses the smallest remaining asteroid because:
- Easiest to defeat now
- Gain mass to face harder ones later
- If you can't defeat it now, defeating others won't help

---

## Key Takeaway

**Greedy with frequency counting is elegant and efficient!** Sort asteroids implicitly using frequency array, process from smallest to largest, accumulate mass greedily. This guarantees the best possible outcome if any order works at all! 🚀

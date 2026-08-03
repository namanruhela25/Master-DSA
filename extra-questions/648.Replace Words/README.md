# Replace Words

## Problem Link
🔗 [LeetCode 648 — Replace Words](https://leetcode.com/problems/replace-words/)

---

## What is this Problem?

Given a dictionary of **roots** and a sentence, replace every word in the sentence with its **shortest root** from the dictionary. If a word has no root, leave it unchanged.

```
dict = ["cat","bat","rat"]
sentence = "the cattle was rattled by the battery"

Output: "the cat was rat by the bat"

"cattle" → starts with "cat" → replaced with "cat"
"rattled" → starts with "rat" → replaced with "rat"
"battery" → starts with "bat" → replaced with "bat"
"the" → no root matches → stays "the"
```

---

## The Problem Explained

Think of it like **autocorrect shortening words to their prefix**:

```
For each word in the sentence:
  Try prefix of length 1, then 2, then 3...
  The FIRST prefix that exists in the dictionary wins.
  "Shortest root" = first match found when growing prefix.
```

---

## HOOK TO REMEMBER FOREVER

**"STORE ROOTS IN A HASHSET. FOR EACH WORD, TRY GROWING PREFIXES. FIRST HIT = REPLACEMENT."**

- ✅ Insert all dictionary roots into an `unordered_map` (or set) for O(1) lookup
- ✅ Split the sentence word by word using `istringstream`
- ✅ For each word, grow prefix from length 1 upward
- ✅ First prefix found in the dictionary → use it, skip the rest
- ✅ If no prefix found after the full word → keep the original word
- ✅ O(n × k²) time where n = words in sentence, k = max word length

---

## How It Works Step By Step

### Example: `dict=["cat","bat","rat"], sentence="the cattle was rattled by the battery"`

**Step 1 — Build the lookup set:**
```
mp = {cat:true, bat:true, rat:true}
```

**Step 2 — Parse each word and find shortest root:**

```
Word: "the"
  i=0: substr="t". In mp? NO
  i=1: substr="th". In mp? NO
  i=2: substr="the". In mp? NO. i==size-1 → res += "the "

Word: "cattle"
  i=0: substr="c". In mp? NO
  i=1: substr="ca". In mp? NO
  i=2: substr="cat". In mp? YES → res += "cat ". BREAK.

Word: "was"
  i=0: "w" NO, i=1: "wa" NO, i=2: "was" NO → res += "was "

Word: "rattled"
  i=0: "r" NO, i=1: "ra" NO, i=2: "rat" YES → res += "rat ". BREAK.

Word: "by"
  No root → res += "by "

Word: "the"
  No root → res += "the "

Word: "battery"
  i=0: "b" NO, i=1: "ba" NO, i=2: "bat" YES → res += "bat ". BREAK.
```

**Step 3 — Remove trailing space:**
```
res = "the cat was rat by the bat " → erase last char → "the cat was rat by the bat"
```

---

## Code Full Solution

```cpp
class Solution {
public:
    string replaceWords(vector<string>& dict, string sentence) {
        unordered_map<string, bool> mp;
        string word, res;

        for (auto &el : dict) mp[el] = true;

        istringstream ss(sentence);

        while (ss >> word) {
            int i = 0;
            while (i < word.size()) {
                string sbs = word.substr(0, i + 1);
                if (mp.find(sbs) != mp.end()) {
                    res += sbs + " ";
                    break;
                }
                if (i == word.size() - 1) res += sbs + " ";
                i++;
            }
        }

        res.erase(res.size() - 1);
        return res;
    }
};
```

---

## Code Explanation

### Store Roots for O(1) Lookup

```cpp
unordered_map<string, bool> mp;
for (auto &el : dict) mp[el] = true;
```

`unordered_map` (could also be `unordered_set`) lets us check if a prefix is a root in O(1) average time.

---

### Split Sentence Using `istringstream`

```cpp
istringstream ss(sentence);
while (ss >> word) { ... }
```

`istringstream` splits the sentence on whitespace automatically — no manual indexOf-space logic needed. Each iteration of the while loop gives us the next word.

---

### Inner Loop — Grow Prefix Until Match or End

```cpp
int i = 0;
while (i < word.size()) {
    string sbs = word.substr(0, i + 1);
    if (mp.find(sbs) != mp.end()) {
        res += sbs + " ";
        break;
    }
    if (i == word.size() - 1) res += sbs + " ";
    i++;
}
```

```
i=0: check length-1 prefix ("c")
i=1: check length-2 prefix ("ca")
i=2: check length-3 prefix ("cat") → FOUND! Append "cat " and break.

If we reach i == word.size()-1 and STILL haven't found a root:
  We're on the full word itself. Append it and move on.
```

**Two exit paths from the inner loop:**
```
1. Root found early → res += sbs + " ". break.
2. No root found → when i hits the last character,
   res += full_word + " ". Loop ends naturally.
```

---

### Remove Trailing Space

```cpp
res.erase(res.size() - 1);
```

Every word gets a trailing space added. The last word leaves an unwanted space at the end — erase it before returning.

---

## Edge Cases

### Case 1: No Root Matches Any Word

```
dict=["xyz"], sentence="the cat sat"
All words are kept unchanged.
Output: "the cat sat" ✓
```

### Case 2: Root IS the Word Itself

```
dict=["cat"], sentence="cat catches"
"cat" → prefix "cat" matches at i=2 → res += "cat"
"catches" → prefix "cat" found → replaced with "cat"
Output: "cat cat" ✓
```

### Case 3: Multiple Roots Match — Use the SHORTEST

```
dict=["ca","cat","c"], sentence="cattle"
i=0: "c" → FOUND! Use "c". BREAK.
Output: "c"  (not "ca" or "cat")

The growing-from-length-1 approach naturally picks the shortest. ✓
```

### Case 4: Single Word Sentence

```
dict=["the"], sentence="there"
"there" → i=2: "the" found → "the"
res = "the ". erase last → "the"
Output: "the" ✓
```

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(n × k²) — for each of n words, try up to k prefixes, each `substr` takes O(k) |
| Space | O(d × l) — dictionary stored in hashmap, d=dict size, l=avg root length |

> **Faster approach:** Use a **Trie**. Instead of trying all prefixes via `substr`, traverse the Trie character by character. Finding the shortest root becomes O(k) per word instead of O(k²). Recommended when dict is large or performance matters.

---

## Key Insights

### Why Growing from Length 1 Guarantees the SHORTEST Root

```
We try prefix of length 1 first, then 2, then 3...
The FIRST match we find is necessarily the shortest.

If both "ca" and "cat" are in the dictionary and our word
is "cattle", we'd find "ca" at i=1 and break immediately
— we never even check "cat". ✓
```

### Why `unordered_map<string,bool>` and Not `unordered_set<string>`?

```
Functionally identical here. unordered_set<string> is
actually the more idiomatic choice — we only need
"does this key exist?" not "what's the value?".

The bool value is unused — it's always just true.
In an interview, prefer unordered_set for clarity.
```

### The Better Approach: Trie

```
This solution generates O(k) substrings per word (each substr is O(k))
→ O(k²) per word.

A Trie stores each root as a path from root to a "end" node.
To find the shortest root of a word, just walk the Trie
character by character — stop at the first "end" marker.
That's O(k) per word, no substr allocations.

Trie = the production-grade solution for this problem class.
```

---

## References

- 🔗 [LeetCode 648 — Replace Words](https://leetcode.com/problems/replace-words/)
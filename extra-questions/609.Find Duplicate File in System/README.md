# Find Duplicate File in System

## Problem Link
🔗 [LeetCode 609 — Find Duplicate File in System](https://leetcode.com/problems/find-duplicate-file-in-system/)

---

## What is this Problem?

Given a list of directory info strings, find all groups of **duplicate files** — files that have the **same content**.

Each string in `paths` looks like:
```
"root/dir file1.txt(content1) file2.txt(content2) ..."
```
The first word is the **directory**, followed by space-separated `filename(content)` pairs.

**Example:**
```
paths = [
  "root/a 1.txt(abcd) 2.txt(efgh)",
  "root/c 3.txt(abcd)",
  "root/c/d 4.txt(efgh)",
  "root 4.txt(efgh)"
]

Output: [
  ["root/a/1.txt","root/c/3.txt"],       ← both have content "abcd"
  ["root/a/2.txt","root/c/d/4.txt","root/4.txt"]  ← all have content "efgh"
]
```

---

## The Problem Explained

Think of it like **Google Drive detecting duplicate files by their content hash**:

```
Two files are "duplicates" if they have IDENTICAL CONTENT,
regardless of their name or where they live.

Strategy:
  Build a map: content → [list of file paths with that content]
  Any content bucket with 2+ files = a duplicate group.
```

---

## HOOK TO REMEMBER FOREVER

**"PARSE DIR + FILES, EXTRACT CONTENT AS KEY, GROUP FILE PATHS BY CONTENT, RETURN GROUPS WITH SIZE > 1"**

- ✅ For each path string: first token = directory, rest = `file(content)` pairs
- ✅ Extract content from between `(` and `)`
- ✅ Build full path = `dir + "/" + filename`
- ✅ Group full paths by content: `mp[content].push_back(fullpath)`
- ✅ Any group with size ≥ 2 is a duplicate group → add to answer

---

## Parsing a Single Path String

```
Input: "root/a 1.txt(abcd) 2.txt(efgh)"

istringstream splits on spaces:
  Token 1: "root/a"         → this is the directory
  Token 2: "1.txt(abcd)"    → file with content
  Token 3: "2.txt(efgh)"    → another file

From "1.txt(abcd)":
  filename = substr before '(' → "1.txt"
  content  = substr between '(' and ')' → "abcd"
  fullpath = "root/a" + "/" + "1.txt" → "root/a/1.txt"
```

### Extracting Filename and Content

```cpp
string content = file.substr(file.find('(') + 1, 
                              file.find(')') - file.find('(') - 1);
string filename = file.substr(0, file.find('('));
```

```
file = "1.txt(abcd)"
          ↑    ↑   ↑
       fname  (  content  )

find('(') = 5   → filename = file.substr(0, 5)     = "1.txt"
find(')') = 10  → content  = file.substr(6, 10-5-1) = "abcd"

substr(start, length) — not start,end! Length = find(')')-find('(')-1
```

---

## How It Works Step By Step

```
paths = ["root/a 1.txt(abcd) 2.txt(efgh)", "root/c 3.txt(abcd)"]
```

**Iteration 1:** `"root/a 1.txt(abcd) 2.txt(efgh)"`
```
dir = "root/a"

file = "1.txt(abcd)":
  content = "abcd", filename = "1.txt"
  fullpath = "root/a/1.txt"
  mp["abcd"] = ["root/a/1.txt"]

file = "2.txt(efgh)":
  content = "efgh", filename = "2.txt"
  fullpath = "root/a/2.txt"
  mp["efgh"] = ["root/a/2.txt"]
```

**Iteration 2:** `"root/c 3.txt(abcd)"`
```
dir = "root/c"

file = "3.txt(abcd)":
  content = "abcd", filename = "3.txt"
  fullpath = "root/c/3.txt"
  mp["abcd"] = ["root/a/1.txt", "root/c/3.txt"]  ← duplicate!
```

**Final map:**
```
mp = {
  "abcd": ["root/a/1.txt", "root/c/3.txt"],    ← size=2 → duplicate group ✓
  "efgh": ["root/a/2.txt"]                      ← size=1 → not a duplicate
}

ans = [["root/a/1.txt","root/c/3.txt"]]
```

---

## Code Full Solution

```cpp
class Solution {
public:
    vector<vector<string>> findDuplicate(vector<string>& paths) {
        unordered_map<string, vector<string>> mp;
        vector<vector<string>> ans;

        for (auto &path : paths) {
            istringstream ss(path);
            string dir, file;
            ss >> dir;

            while (ss >> file) {
                string content = file.substr(file.find('(') + 1,
                                 file.find(')') - file.find('(') - 1);
                string filename = file.substr(0, file.find('('));
                string filedir = dir + "/" + filename;
                mp[content].push_back(filedir);
            }
        }

        for (auto &el : mp) {
            if (el.second.size() > 1) {
                ans.push_back(el.second);
            }
        }

        return ans;
    }
};
```

---

## Code Explanation

### Parse Directory and Files

```cpp
istringstream ss(path);
string dir, file;
ss >> dir;          // first token = directory
while (ss >> file)  // remaining tokens = file(content) pairs
```

`istringstream` splits on whitespace automatically. First `>>` grabs the directory, then the `while` loop grabs each `file(content)` pair one by one.

---

### Extract Content and Build Full Path

```cpp
string content = file.substr(file.find('(') + 1,
                 file.find(')') - file.find('(') - 1);
string filename = file.substr(0, file.find('('));
string filedir = dir + "/" + filename;
```

```
For "1.txt(abcd)":
  find('(') = 5, find(')') = 10
  content  = substr(6, 4)   = "abcd"   [start = 5+1, len = 10-5-1]
  filename = substr(0, 5)   = "1.txt"
  filedir  = "root/a/1.txt"
```

---

### Group and Filter

```cpp
mp[content].push_back(filedir);
// ...
if (el.second.size() > 1) ans.push_back(el.second);
```

Content is the key. All file paths with identical content land in the same bucket. We only care about buckets with 2+ files — those are the duplicates.

---

## Edge Cases

### Case 1: All Files Unique Content

```
No content bucket reaches size > 1.
Output: [] ✓
```

### Case 2: All Files Same Content

```
paths = ["root/a 1.txt(abc)","root/b 2.txt(abc)","root/c 3.txt(abc)"]

mp["abc"] = ["root/a/1.txt","root/b/2.txt","root/c/3.txt"]

Output: [["root/a/1.txt","root/b/2.txt","root/c/3.txt"]] ✓
```

### Case 3: File in Root Directory

```
"root 4.txt(efgh)"
dir = "root", filename = "4.txt"
filedir = "root/4.txt" ✓
```

### Case 4: Same Filename, Different Content

```
"root/a 1.txt(abc)" and "root/b 1.txt(xyz)"
Different content → different keys → NOT duplicates ✓
(duplicate = same content, NOT same name)
```

---

## Time and Space Complexity

| | Value |
|---|---|
| Time | O(N) where N = total characters across all path strings |
| Space | O(N) for the hashmap storing all full paths |

---

## Key Insights

### Content is the Key, Not the Filename

```
Common mistake: group by filename ("1.txt" = "1.txt" → duplicate?).
WRONG. Two files named "1.txt" in different directories
with DIFFERENT content are NOT duplicates.

Two files named completely differently but with IDENTICAL
content ARE duplicates.

Always group by CONTENT. ✓
```

### `substr(start, length)` — Not `substr(start, end)`

```
C++ substr takes (start_position, LENGTH), not end position.

content = file.substr(find('(')+1, find(')')-find('(')-1)
                       ↑ start     ↑ length (not end!)

This is a common gotcha. The length = end_pos - start_pos.
If you pass find(')') directly as the second argument,
you'd get a much longer (wrong) substring.
```

### Follow-up Interview Questions

The LeetCode editorial for this problem lists common follow-ups:

```
1. If files are too large to read fully — use file metadata
   (size, last-modified) to pre-filter before hashing content.

2. If many files map to the same content bucket — use a
   cryptographic hash (MD5/SHA256) as key instead of raw content
   to reduce memory (but handle rare hash collisions).

3. If re-queried frequently — cache the content→paths map
   and support incremental updates when files are added/deleted.
```

---

## References

- 🔗 [LeetCode 609 — Find Duplicate File in System](https://leetcode.com/problems/find-duplicate-file-in-system/)
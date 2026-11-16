# Master DSA

A structured DSA repository for **interview preparation and revision**.  
Every problem has clean C++ solutions with detailed READMEs — explained simply.

---

## What's inside

| Section | What it covers | Problems |
|---|---|---|
| [`core-patterns/`](core-patterns) | One folder per pattern — sorting, arrays, binary search, graphs, … | **87** |
| [`company-wise/`](company-wise) | Problems grouped by the company that asked them | **7** |
| [`extra-questions/`](extra-questions) | Assorted LeetCode / GFG questions that don't fit a pattern | **33** |


**127 solutions · 125 of them with a full README**

---

## Repository structure

```
Master DSA
│
├── core-patterns/                     learn the pattern, then the problems
│   ├── 01_sorting/                    5 problems + READMEs
│   ├── 02_arrays/                     40 problems + READMEs
│   ├── 03_binarySearch/               24 problems + READMEs
│   ├── 05_strings/                    1 problem + README
│   ├── 06_linkedList/                 (empty)
│   ├── 07_recursion/                  (empty)
│   ├── 08_BitManipulation/            (empty)
│   ├── 09_stack/                      (empty)
│   ├── 10_queues/                     (empty)
│   ├── 11_slidingWindow_twoPointer/   (empty)
│   ├── 12_heaps/                      (empty)
│   ├── 13_greedyAlgorithms/           (empty)
│   ├── 14_binaryTrees/                (empty)
│   ├── 15_binarySearchTrees/          (empty)
│   ├── 16_graphs/                     17 problems + READMEs
│   ├── 17_dynamicProgramming/         (empty)
│   ├── 18_tries/                      (empty)
│   └── 19_advanceStrings/             (empty)
│
├── company-wise/
│   └── Google-50/                     7 problems (01–07)
│
├── extra-questions/
│   └── <number>.<Title>/              one folder per question
│
└── neetcode-150/                      folders created, problems pending
```

Each problem lives in its own folder:

```
02_arrays/17.Majority element Moore voting/
├── main.cpp      ← the solution
└── README.md     ← the explanation
```

---

## Core patterns — progress

| # | Pattern | Problems | Status |
|---|---|---:|---|
| 01 | Sorting | 5 | ✅ |
| 02 | Arrays | 40 | ✅ |
| 03 | Binary Search | 24 | ✅ |
| 05 | Strings | 1 | ✅ |
| 06 | Linked List | 0 | ⬜ |
| 07 | Recursion | 0 | ⬜ |
| 08 | Bit Manipulation | 0 | ⬜ |
| 09 | Stack | 0 | ⬜ |
| 10 | Queues | 0 | ⬜ |
| 11 | Sliding Window / Two Pointer | 0 | ⬜ |
| 12 | Heaps | 0 | ⬜ |
| 13 | Greedy | 0 | ⬜ |
| 14 | Binary Trees | 0 | ⬜ |
| 15 | Binary Search Trees | 0 | ⬜ |
| 16 | Graphs | 17 | ✅ |
| 17 | Dynamic Programming | 0 | ⬜ |
| 18 | Tries | 0 | ⬜ |
| 19 | Advanced Strings | 0 | ⬜ |

---

## What a README looks like

Most problem READMEs share the same spine, so revision is predictable:

```
## Problem Link            → direct LeetCode / GFG link
## What is this Problem?   → statement + worked examples
## The Idea                → the intuition, usually as an ASCII diagram
## Code Full Solution      → the folder's main.cpp, verbatim
## Code Explanation        → what each block does and why
## Full Trace              → the algorithm run step by step on real input
## Example Traces          → extra inputs, including the tricky ones
## Edge Cases              → empty, single element, duplicates, overflow
## Time and Space Complexity
## Key Insight             → the one line worth remembering
## References
```

Section names shift slightly by pattern — `The Idea` may appear as `The Problem Explained` or `HOOK TO REMEMBER FOREVER` (arrays and graphs use that mnemonic), and complexity is sometimes split into `Time Complexity` + `Space Complexity`. The `01_sorting` READMEs are prose explainers with no problem link, since they cover algorithms rather than judge questions.

Where a solution has a real defect, the README says so with a `⚠️ **Bug:**` note that traces the failure and gives the fix — the code is left untouched so the mistake stays visible.


## Conventions

- **One problem, one folder** — `NN.Problem Title/` inside the pattern it belongs to.
- **`main.cpp` holds only the solution** — no driver code, no `using namespace std;` unless needed.
- **Folder order is the study order** — within a pattern, problems go from easy to hard.
- **Names mirror the source** — the folder title matches the LeetCode / GFG problem name as closely as possible.


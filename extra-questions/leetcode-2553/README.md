# Separate the Digits in an Array

**Problem Link:** https://leetcode.com/problems/separate-the-digits-in-an-array/

## What is this Problem?

You have an **array of multi-digit numbers** and you need to **break each number into individual digits**, then return a new array containing all digits in order.

**Examples:**
```
Input: [123, 45, 67]
Output: [1, 2, 3, 4, 5, 6, 7]
(123 becomes 1,2,3; 45 becomes 4,5; 67 becomes 6,7)

Input: [1, 100, 2]
Output: [1, 1, 0, 0, 2]
(1 stays 1; 100 becomes 1,0,0; 2 stays 2)

Input: [7]
Output: [7]
(Single digit stays single digit)
```

---

## The Problem Explained

Think of it like **opening a combination lock**:

```
Combination: 123

Lock dial shows: 123 (one number)

You need to read individual digits:
Look at first digit: 1
Look at second digit: 2
Look at third digit: 3

Write them out separately: [1, 2, 3]
```

**Key insight:** Numbers can be treated as strings! Convert to string, access each character, convert back to digit.

---

## HOOK TO REMEMBER FOREVER

**"TO STRING, EXTRACT, BACK TO INT"**

Every time you see "separate digits" or "break number into digits":
- ✅ Convert number to string using to_string()
- ✅ Loop through each character in the string
- ✅ Convert each character back to digit (char - '0')
- ✅ Add to result array
- ✅ O(n) where n = total number of digits
- ✅ Simple string manipulation power!

**Remember: String acts as a bridge to access individual digits!** 🌉

---

## How It Works Step By Step

### The String Bridge Strategy

```
Number: 123

Step 1: Convert to string
  string num = "123"
  (Now we can access individual characters!)

Step 2: Loop through each character
  '1', '2', '3'

Step 3: Convert each character to digit
  '1' - '0' = 1
  '2' - '0' = 2
  '3' - '0' = 3

Step 4: Add to result
  result = [1, 2, 3]
```

### Visual Example: [123, 45, 67]

```
Initial: nums = [123, 45, 67], ans = []

Process 123:
  Convert to string: "123"
  Extract '1': '1' - '0' = 1 → ans = [1]
  Extract '2': '2' - '0' = 2 → ans = [1, 2]
  Extract '3': '3' - '0' = 3 → ans = [1, 2, 3]

Process 45:
  Convert to string: "45"
  Extract '4': '4' - '0' = 4 → ans = [1, 2, 3, 4]
  Extract '5': '5' - '0' = 5 → ans = [1, 2, 3, 4, 5]

Process 67:
  Convert to string: "67"
  Extract '6': '6' - '0' = 6 → ans = [1, 2, 3, 4, 5, 6]
  Extract '7': '7' - '0' = 7 → ans = [1, 2, 3, 4, 5, 6, 7]

Final result: [1, 2, 3, 4, 5, 6, 7] ✓
```

---

## Code Full Solution

```cpp
class Solution {
public:
    vector<int> separateDigits(vector<int>& nums) {
        vector<int> ans;
        
        for(auto &el : nums) {
            // Convert number to string
            string num = to_string(el);
            
            // Extract each digit from the string
            for(auto &el : num) {
                // Convert character to digit and add to result
                ans.push_back(el - '0');
            }
        }
        
        return ans;
    }
};
```

---

## Code Explanation

### Initialize Result Array

```cpp
vector<int> ans;
```

- **`ans`:** Empty vector to store all digits
- We'll push digits into this as we process each number
- Return this at the end

---

### Outer Loop: Process Each Number

```cpp
for(auto &el : nums) {
    string num = to_string(el);
```

- **`for(auto &el : nums)`:** Iterate through each number in input array
- **`auto &el`:** Reference to each integer element
- **`to_string(el)`:** Convert integer to string
  - Example: `to_string(123)` → `"123"`
  - Now we can access individual characters!

**Why convert to string?**
```
Without string:
123 → can't easily get individual digits
Need math: 123 % 10 = 3, 123 / 10 = 12, etc.

With string:
123 → "123" → access '1', '2', '3' directly
Much simpler!
```

---

### Inner Loop: Extract Each Digit

```cpp
    for(auto &el : num) {
        ans.push_back(el - '0');
    }
```

- **`for(auto &el : num)`:** Iterate through each character in string
- **`el`:** This is a `char`, like `'1'`, `'2'`, `'3'`
- **`el - '0'`:** Convert character digit to integer digit!

**Why subtract '0'?**
```
Character '0' has ASCII value 48
Character '1' has ASCII value 49
Character '2' has ASCII value 50
...

So: '1' - '0' = 49 - 48 = 1 ✓
    '2' - '0' = 50 - 48 = 2 ✓
    '9' - '0' = 57 - 48 = 9 ✓

Subtracting '0' from any digit character gives the numeric value!
```

- **`ans.push_back(...)`:** Add the digit to result array

---

### Return Result

```cpp
return ans;
```

- Return the vector containing all separated digits in order

---

## Complete Example Traces

### Trace 1: Mixed Multi-Digit Numbers [123, 45, 67]

```
Initial: nums = [123, 45, 67], ans = []

Outer loop iteration 1: el = 123
  to_string(123) → num = "123"
  
  Inner loop iteration 1: el = '1'
    '1' - '0' = 1
    ans.push_back(1) → ans = [1]
  
  Inner loop iteration 2: el = '2'
    '2' - '0' = 2
    ans.push_back(2) → ans = [1, 2]
  
  Inner loop iteration 3: el = '3'
    '3' - '0' = 3
    ans.push_back(3) → ans = [1, 2, 3]

Outer loop iteration 2: el = 45
  to_string(45) → num = "45"
  
  Inner loop iteration 1: el = '4'
    '4' - '0' = 4
    ans.push_back(4) → ans = [1, 2, 3, 4]
  
  Inner loop iteration 2: el = '5'
    '5' - '0' = 5
    ans.push_back(5) → ans = [1, 2, 3, 4, 5]

Outer loop iteration 3: el = 67
  to_string(67) → num = "67"
  
  Inner loop iteration 1: el = '6'
    '6' - '0' = 6
    ans.push_back(6) → ans = [1, 2, 3, 4, 5, 6]
  
  Inner loop iteration 2: el = '7'
    '7' - '0' = 7
    ans.push_back(7) → ans = [1, 2, 3, 4, 5, 6, 7]

Return: [1, 2, 3, 4, 5, 6, 7] ✓
```

### Trace 2: Single and Multi-Digit [1, 100, 2]

```
Initial: nums = [1, 100, 2], ans = []

Outer iteration 1: el = 1
  to_string(1) → num = "1"
  
  Inner iteration 1: el = '1'
    '1' - '0' = 1
    ans = [1]

Outer iteration 2: el = 100
  to_string(100) → num = "100"
  
  Inner iteration 1: el = '1'
    '1' - '0' = 1
    ans = [1, 1]
  
  Inner iteration 2: el = '0'
    '0' - '0' = 0
    ans = [1, 1, 0]
  
  Inner iteration 3: el = '0'
    '0' - '0' = 0
    ans = [1, 1, 0, 0]

Outer iteration 3: el = 2
  to_string(2) → num = "2"
  
  Inner iteration 1: el = '2'
    '2' - '0' = 2
    ans = [1, 1, 0, 0, 2]

Return: [1, 1, 0, 0, 2] ✓
```

### Trace 3: Single Digit [7]

```
Initial: nums = [7], ans = []

Outer iteration 1: el = 7
  to_string(7) → num = "7"
  
  Inner iteration 1: el = '7'
    '7' - '0' = 7
    ans = [7]

Return: [7] ✓
```

### Trace 4: Zeros in Numbers [10, 20, 30]

```
Initial: nums = [10, 20, 30], ans = []

Outer iteration 1: el = 10
  to_string(10) → num = "10"
  
  Inner iteration 1: el = '1'
    '1' - '0' = 1
    ans = [1]
  
  Inner iteration 2: el = '0'
    '0' - '0' = 0
    ans = [1, 0]

Outer iteration 2: el = 20
  to_string(20) → num = "20"
  
  Inner iteration 1: el = '2'
    '2' - '0' = 2
    ans = [1, 0, 2]
  
  Inner iteration 2: el = '0'
    '0' - '0' = 0
    ans = [1, 0, 2, 0]

Outer iteration 3: el = 30
  to_string(30) → num = "30"
  
  Inner iteration 1: el = '3'
    '3' - '0' = 3
    ans = [1, 0, 2, 0, 3]
  
  Inner iteration 2: el = '0'
    '0' - '0' = 0
    ans = [1, 0, 2, 0, 3, 0]

Return: [1, 0, 2, 0, 3, 0] ✓
```

### Trace 5: Large Numbers [999, 1000]

```
Initial: nums = [999, 1000], ans = []

Outer iteration 1: el = 999
  to_string(999) → num = "999"
  
  Inner loop 3 times:
    '9' - '0' = 9
    '9' - '0' = 9
    '9' - '0' = 9
  ans = [9, 9, 9]

Outer iteration 2: el = 1000
  to_string(1000) → num = "1000"
  
  Inner loop 4 times:
    '1' - '0' = 1
    '0' - '0' = 0
    '0' - '0' = 0
    '0' - '0' = 0
  ans = [9, 9, 9, 1, 0, 0, 0]

Return: [9, 9, 9, 1, 0, 0, 0] ✓
```

### Trace 6: Sequential [11, 22, 33]

```
Initial: nums = [11, 22, 33], ans = []

Outer iteration 1: el = 11
  to_string(11) → num = "11"
  
  Inner iterations:
    '1' - '0' = 1
    '1' - '0' = 1
  ans = [1, 1]

Outer iteration 2: el = 22
  to_string(22) → num = "22"
  
  Inner iterations:
    '2' - '0' = 2
    '2' - '0' = 2
  ans = [1, 1, 2, 2]

Outer iteration 3: el = 33
  to_string(33) → num = "33"
  
  Inner iterations:
    '3' - '0' = 3
    '3' - '0' = 3
  ans = [1, 1, 2, 2, 3, 3]

Return: [1, 1, 2, 2, 3, 3] ✓
```

---

## Edge Cases

### Case 1: Single Element [5]

```
Input: [5]
- to_string(5) → "5"
- '5' - '0' = 5
Output: [5] ✓
```

### Case 2: All Single Digits [1, 2, 3]

```
Input: [1, 2, 3]
- Each number is already single digit
- No separation needed, just extract
Output: [1, 2, 3] ✓
```

### Case 3: Number with Zeros [102, 305]

```
Input: [102, 305]
- 102 → [1, 0, 2]
- 305 → [3, 0, 5]
Output: [1, 0, 2, 3, 0, 5] ✓
(Zeros are preserved as digits!)
```

### Case 4: Very Large Numbers [123456789]

```
Input: [123456789]
- Convert to string and extract each digit
- 9 characters → 9 digits
Output: [1, 2, 3, 4, 5, 6, 7, 8, 9] ✓
```

### Case 5: Repeated Numbers [777, 777, 777]

```
Input: [777, 777, 777]
- Each 777 becomes [7, 7, 7]
Output: [7, 7, 7, 7, 7, 7, 7, 7, 7] ✓
```

### Case 6: Mix of Small and Large [1, 1000000]

```
Input: [1, 1000000]
- 1 → [1]
- 1000000 → [1, 0, 0, 0, 0, 0, 0]
Output: [1, 1, 0, 0, 0, 0, 0, 0] ✓
```

---

## Time Complexity

- **O(n × d)** where n = number of elements, d = average digits per number
- Outer loop: O(n) - iterate through each number
- Inner loop: O(d) - iterate through digits of each number
- to_string() conversion: O(d) per number
- Total: n numbers × d digits average = O(n × d)

In practice, since d is usually small (1-10 digits), this is effectively **O(n)** for fixed digit ranges.

---

## Space Complexity

- **O(1)** - excluding output array
- Only using temporary variables: `num` (string), `el` (char)
- The result array is the output, not counted as extra space
- If we count result array: **O(n × d)** for output

---

## Key Insights

### Why Convert to String?

```
Alternative approach using math:
123 % 10 = 3 (last digit)
123 / 10 = 12
12 % 10 = 2 (second digit)
12 / 10 = 1
1 % 10 = 1 (first digit)
1 / 10 = 0 (stop)

Gets digits in reverse order! Need to reverse.

String approach:
"123" → access '0', '1', '2' directly
Already in correct order!
Cleaner code.
```

### Character to Digit Conversion

```
ASCII values:
'0' = 48
'1' = 49
'2' = 50
...
'9' = 57

So: '0' - '0' = 0
    '1' - '0' = 1
    ...
    '9' - '0' = 9

This is the standard trick in competitive programming!
```

### Why Nested Loops?

```
Can't just do:
vector<int> ans;
ans.push_back(num);  ❌ num is array, not single digit

Need to:
1. Iterate through each number in input array (outer loop)
2. Iterate through each character in that number's string (inner loop)
3. Convert and collect each digit
```

### Order Preservation

```
Input: [123, 45, 67]

Order: process 123 completely, then 45, then 67
Within 123: process '1', '2', '3' in order

Result maintains order naturally!
```

### Why Not Store as String?

```
Problem asks for: vector<int>
Output needs to be integers

If we stored as string:
ans = "1234567"

Need to loop again to convert to integers
Extra pass + complexity

Direct conversion during extraction is efficient!
```

### Space Efficiency

```
We must return all digits, so output size is fixed
We only use temporary variables, not arrays

The string 'num' is reused for each input number
- Get reference to input number
- Convert to string temporarily
- Extract digits
- Move to next number

No permanently stored strings or extra arrays!
```

class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    int max_len = 0;
    unordered_map<char, int> lastSeen;
    int l = 0;
    for (int r = 0; r < s.size(); r++) {
      char c = s[r];
      if (lastSeen.find(c) != lastSeen.end() && lastSeen[c] >= l) {
        l = lastSeen[c] + 1;
      }

      max_len = max(max_len, r - l + 1);
      lastSeen[c] = r;
    }
    return max_len;
  }
};
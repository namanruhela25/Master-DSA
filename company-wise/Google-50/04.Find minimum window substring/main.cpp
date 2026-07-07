class Solution {
public:
  string minWindow(string s, string t) {
    if (s.size() < t.size())
      return "";
    int l = 0, r = 0;
    unordered_map<char, int> hash;
    int cnt = 0;
    int min_len = 1e9;
    int startIndex = -1;
    int tlen = t.size();
    int slen = s.size();

    for (auto &el : t) {
      hash[el]++;
    }

    while (r < slen) {
      if (hash[s[r]] > 0)
        cnt++;
      hash[s[r]]--;

      while (cnt == tlen) {
        if (r - l + 1 < min_len) {
          min_len = r - l + 1;
          startIndex = l;
        }
        hash[s[l]]++;
        if (hash[s[l]] > 0)
          cnt--;
        l++;
      }
      r++;
    }

    return startIndex == -1 ? "" : s.substr(startIndex, min_len);
  }
};
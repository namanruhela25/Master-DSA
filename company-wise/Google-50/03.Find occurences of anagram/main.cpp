class Solution {
public:
  vector<int> findAnagrams(string s, string p) {
    int n = s.size();
    vector<int> ans;
    vector<int> freq(26, 0);

    // count tells how much required ?
    int count = p.size();
    int left = 0;

    for (auto &el : p) {
      freq[el - 'a']++;
    }

    int pl = p.size();

    for (int right = 0; right < n; right++) {
      if (freq[s[right] - 'a'] > 0)
        count--;

      freq[s[right] - 'a']--;

      if (right - left + 1 > pl) {

        if (freq[s[left] - 'a'] >= 0) {
          count++;
        }

        freq[s[left] - 'a']++;
        left++;
      }

      if (count == 0)
        ans.push_back(left);
    }
    return ans;
  }
};

/*
class Solution {
public:
    bool allzero(unordered_map<char,int> &mpp) {
        for(auto &el : mpp) {
            if(el.second != 0) return false;
        }
        return true;
    }

    vector<int> findAnagrams(string s, string p) {
        int n = s.size();
        unordered_map<char,int> mpp;
        vector<int> ans;
        int pl = p.size();
        int left = 0;

        for(char &c : p) mpp[c]++;

        for(int right = 0; right < n;right++) {
            mpp[s[right]]--;
            if(right - left + 1 == pl) {
                if(allzero(mpp)) {
                    ans.push_back(left);
                }
                mpp[s[left]]++;
                left++;
            }
        }

        return ans;
    }
};
*/

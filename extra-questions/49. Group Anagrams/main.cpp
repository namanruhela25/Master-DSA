class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        int n = strs.size();
        unordered_map<string,vector<string>> mpp;
        for(string &str : strs) {
            vector<int> count(26,0);

            for(char c : str) {
                count[c - 'a']++;
            }
            
            string key;
            for(int num : count) {
                key+=to_string(num) + "#";
            }

            mpp[key].push_back(str);
        }
        vector<vector<string>> ans;
        for(auto &el : mpp) {
            ans.push_back(el.second);
        }
        return ans;
    }
};
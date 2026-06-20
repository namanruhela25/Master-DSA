class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& a) {
        sort(a.begin(),a.end());
        vector<vector<int>> ans;
        for(auto &el : a) {
            if(ans.empty() || el[0] > ans.back()[1]) {
                ans.push_back(el);
            } else{
                ans.back()[1] = max(el[1],ans.back()[1]);
            }
        }
        return ans;
    }
};
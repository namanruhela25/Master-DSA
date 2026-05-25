class Solution {
public:
    int findLucky(vector<int>& arr) {
        unordered_map<int,int> mpp;
        for(auto &el : arr) {
            mpp[el]++;
        }
        int ans = -1;
        for(auto &el : mpp) {
            if(el.second == el.first) {
                ans = max(ans,el.first);
            }
        }
        return ans;
    }
};
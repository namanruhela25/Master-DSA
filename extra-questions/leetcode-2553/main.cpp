class Solution {
public:
    vector<int> separateDigits(vector<int>& nums) {
        vector<int> ans;
        for(auto &el : nums) {
            string num=to_string(el);
            for(auto &el : num) {
                ans.push_back(el - '0');
            }
        }
        return ans;
    }
};
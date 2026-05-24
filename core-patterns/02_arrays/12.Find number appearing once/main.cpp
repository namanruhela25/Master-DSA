class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans = 0;
        for(auto &el : nums){
            ans = ans ^ el;
        }
        return ans;
    }
};
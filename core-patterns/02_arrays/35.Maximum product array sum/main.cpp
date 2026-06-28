class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int prefix = 1;
        int suffix = 1;
        int n = nums.size();
        int ans = INT_MIN;
        for(int i=0;i<n;i++) {
            if (nums[i] == 0) prefix = 1;
            if (nums[n-i-1] == 0) suffix = 1;

            prefix*=nums[i];
            suffix*=nums[n-i-1];

            ans = max(ans,max(prefix,suffix));
        }
        return ans;
    }
};
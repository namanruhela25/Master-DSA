class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int sum = nums[0];
        int maxSum = nums[0];
        int n = nums.size();
        for(int i=1;i<n;i++) {
            sum+=nums[i];
            if(sum > maxSum) maxSum = sum;
            if(sum < 0) sum = 0;
            if(nums[i] > maxSum) {
                maxSum = nums[i];
                sum = nums[i];
            }
        }
        return maxSum;
    }
};
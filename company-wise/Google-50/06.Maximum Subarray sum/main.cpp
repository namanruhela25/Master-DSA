class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // [-2,1,-3,4,-1,2,1,-5,4]

        int sum = nums[0];
        int maxSum = nums[0];

        for(int i=1;i<n;i++) {
            sum+=nums[i];
            if(sum > maxSum) maxSum = sum;
            if(sum < 0)  sum = 0;
            if(sum > nums[i]) {
                maxSum = nums[i];
                sum = nums[i];
            }
        }
        return maxSum;
    }
};
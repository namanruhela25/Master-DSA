class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int start = 0;
        int end = 0;
        int maxSum = INT_MIN;
        int sum = 0;
        int tempStart = 0;

        for(int i=0;i<nums.size();i++) {
            sum += nums[i];

            if(sum > maxSum) {
                start = tempStart;
                end = i;
                maxSum = sum;
            }

            if(sum < 0) {
                tempStart = i+1;
                sum = 0;
            }
        }
        cout<<start<<" "<<end<<endl;
        return maxSum;
    }
};


int main() {
    Solution s;
    vector<int> nums = {-2,1,-3,-4,2,5,-1,-5,-4};
    cout << s.maxSubArray(nums) << endl;
    return 0;
}
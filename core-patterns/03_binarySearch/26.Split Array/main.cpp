class Solution {
public:
    int solve(vector<int> &nums,int mid,int n) {
        int sm=0;
        int partition = 1;
        for(int i=0;i<n;i++) {
            if(sm + nums[i] <= mid) {
                sm+=nums[i];
            } else{
                sm = nums[i];
                partition++;
            }
        }
        return partition;
    }

    int splitArray(vector<int>& nums, int k) {
        int n = nums.size();
        int low = *max_element(nums.begin(),nums.end());
        int high = accumulate(nums.begin(),nums.end(),0);
        while(low <= high) {
            int mid = low + (high - low) / 2;
            int noofpartition = solve(nums,mid,n);
            if(noofpartition <= k) {
                high = mid - 1;
            } else{
                low = mid + 1;
            }
        }
        return low;
    }
};
class Solution {
public:
    int findMin(vector<int>& nums) {
        int low=0;
        int high = nums.size() - 1;
        int ans = INT_MAX;
        while(low<=high) {
            int mid = low + (high - low) / 2;
            if(nums[low] <= nums[mid]) {
                ans = min(ans,nums[low]);
                low = mid + 1;
                // why low = mid + 1 ? because 
                // it is sorted array this low element is smallest why to check 
                // which are coming right to it they are already greater 
                // So Skip them all and shift to right part
            } else{
                ans = min(ans,nums[mid]);
                high = mid - 1;
            }
        }

        return ans;
    }
};
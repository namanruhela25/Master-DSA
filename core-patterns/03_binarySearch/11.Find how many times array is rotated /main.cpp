class Solution {
  public:
    int findKRotation(vector<int> &nums) {
        int low = 0;
        int high = nums.size() - 1;
        int ans = INT_MAX;
        int index = 0;
        while(low <= high) {
            int mid = low + (high - low) / 2;

            // This piece of code not needed but make algo faster
            if(nums[low] <= nums[high]) {
                if(nums[low] < ans) {
                    index = low;
                    ans = nums[low];
                }
            }
            // ---------------------------------------------------

            if(nums[low] <= nums[mid]) {
                if(nums[low] < ans) {
                    ans = nums[low];
                    index = low;
                }
                low = mid + 1;
            }else {
                if(nums[mid] < ans) {
                    ans = nums[mid];
                    index = mid;
                }
                high = mid - 1;
            }
        }
        return index;        
    }
};

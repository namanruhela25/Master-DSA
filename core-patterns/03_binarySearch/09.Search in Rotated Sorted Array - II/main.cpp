class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() - 1;

        while(low <= high) {
            int mid = low + (high - low) / 2;

            if(nums[mid] == target) return true;
            
            // At this stage we are not able to decide where to go so we simply increase and decrease steps by 1 and skip current iteration
            // example - 1 0 1 1 1 , target = 0
            if(nums[mid] == nums[low] && nums[mid] == nums[high]) {
                low = low + 1;
                high = high - 1;
                continue;
            }

            if(nums[low] <= nums[mid]) {
                if(target<=nums[mid] && target>=nums[low]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            } else{
                if(target>=nums[mid] && target<=nums[high]) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }
        return false;
    }
};
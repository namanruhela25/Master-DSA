class Solution1WithBinarySearch {
public:
    int binarySearch(vector<int>& nums, int target,int leftTraverse){
        int low = 0;
        int high = nums.size() - 1;
        int ans = -1;

        while(low<=high){
            int mid = (low + high)/2;
            if(nums[mid] > target){
                high = mid - 1;
            }else if(nums[mid] < target){
                low = mid + 1;
            }else{
                ans = mid;
                if(leftTraverse){
                    high = mid - 1;
                } else{
                    low = mid + 1;
                }
            }
        }
        return ans;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        int left = binarySearch(nums,target,true);
        int right = binarySearch(nums,target,false);
        return {left,right};
    }
};


class Solution2WithUpperBound {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        auto lower = lower_bound(nums.begin(),nums.end(), target);
        
        // lower bound can be equal to target value
        if(lower == nums.end() || *lower!=target) return {-1,-1};

        auto upper = upper_bound(nums.begin(),nums.end(),target);

        return {int(lower - nums.begin()), int((upper - nums.begin())-1)};

    }
};
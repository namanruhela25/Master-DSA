class Solution {
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
    
    int countFreq(vector<int>& nums, int target) {
        int left = binarySearch(nums,target,true);
        int right = binarySearch(nums,target,false);
        if(left == -1 || right == -1) return 0;
        return right - left + 1;
        
    }

    int countFreqStdFunctios(vector<int>& arr, int target) {
        // code here
        auto lower = lower_bound(arr.begin(),arr.end(),target);
        
        if(lower == arr.end() || *lower != target) return 0;
        
        auto upper = upper_bound(arr.begin(),arr.end(),target);

        int li = int(lower - arr.begin());
        int ui = int(upper - arr.begin());
        
        return ui - li;
    }
};

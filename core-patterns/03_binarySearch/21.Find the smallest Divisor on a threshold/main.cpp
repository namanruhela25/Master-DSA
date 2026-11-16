class Solution {
public:
    int possible(vector<int>& nums, int mid) {
        int sum = 0;
        for(auto &el : nums) {
            sum += (ceil(double(el)/mid));
        }
        return sum;
    }

    int smallestDivisor(vector<int>& nums, int threshold) {
        int low = 1;
        int high = *max_element(nums.begin(),nums.end());
        while(low <= high) {
            int mid = low + (high - low) / 2;
            if(possible(nums,mid) <= threshold) {
                high = mid - 1;
            }else {
                low = mid + 1;
            }
        }
        return low;
    }
};
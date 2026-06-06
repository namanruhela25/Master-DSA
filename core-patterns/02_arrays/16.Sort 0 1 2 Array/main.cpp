class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        // 2 2 1 0 0 2

        int zero = 0, one = 0, two = n-1;

        while(one<=two) {
            if(nums[one] == 0) {
                swap(nums[zero],nums[one]);
                one++;
                zero++;
            } else if(nums[one] == 1) {
                one++;
            }else {
                swap(nums[one],nums[two]);
                two--; // why not one++ ? because. might be possibility zero will come here
            }
        }
    }
};
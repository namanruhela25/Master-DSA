class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int index = 0;
        int prevelement = nums[0];

        for(auto &el : nums){
            if(el!=prevelement){
                index++;
                nums[index] = el;
                prevelement = el;
            }
        }
        return index+1;
    }
};
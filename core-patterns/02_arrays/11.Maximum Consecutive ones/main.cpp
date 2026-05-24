class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int cnt = 0;
        int maxi = 0;

        for (auto num : nums){
            if(num == 1){
                cnt++;
            }else{
                cnt = 0;
            }
            maxi = max(maxi,cnt);
        } 
        return maxi;
    }
};
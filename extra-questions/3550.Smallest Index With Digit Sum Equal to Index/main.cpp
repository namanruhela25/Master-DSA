class Solution {
public:
    int smallestIndex(vector<int>& nums) {
        int n = nums.size();
        for(int i=0;i<n;i++) {
            string number = to_string(nums[i]);
            int sum = 0;
            for(char ch : number) {
                sum+=(ch-'0');
            }
            if(sum == i) return i;
        }
        return -1;
    }
};
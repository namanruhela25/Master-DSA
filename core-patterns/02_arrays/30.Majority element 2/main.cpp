class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int maj1 ;
        int maj2 ;
        int cnt1 = 0;
        int cnt2 = 0;
        int n = nums.size();
        for(int &el : nums) {
            if(el == maj1) {
                cnt1++;
            } else if(el == maj2) {
                cnt2++;
            } else if(cnt1 == 0) {
                maj1 = el;
                cnt1++;
            } else if(cnt2 == 0) {
                maj2 = el;
                cnt2++;
            } else {
                cnt1--;
                cnt2--;
            }
        }

        int freq1 = 0;
        int freq2 = 0;
        vector<int> ans;

        for(int &num : nums) {
            if(num == maj1) freq1++;
            else if(num == maj2) freq2++;
        }

        if(freq1 > floor(n/3)) {
            ans.push_back(maj1);
        }
        
        if(freq2 > floor(n/3)) {
            ans.push_back(maj2);
        }
        return ans;
    }
};
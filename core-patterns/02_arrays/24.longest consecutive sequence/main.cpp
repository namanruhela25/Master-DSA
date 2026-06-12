class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> mpp(nums.begin(),nums.end());

        int ans = 0;
        for(int num : mpp) { // why loop on set -- to avoid duplicates in nums
            if(mpp.find(num-1)==mpp.end()) { 
                // if not exist then check it might be new sequence calculate new len,
                /*
                    example:
                    jaise 4 h toh 4 3 ke path se ayega hume sequence me mtlb hume 4 se nahi banana h vo already 3 se ayega toh agar exist ni kra toh bnao yaha se mtlb yhi starting point h 
                */
                int len = 1;
                while(mpp.find(num + len) != mpp.end()) {
                    len++;
                }
                ans = max(ans,len);
            }
        }
        return ans;
    }
};
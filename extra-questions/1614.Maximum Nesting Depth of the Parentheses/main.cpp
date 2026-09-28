class Solution {
public:
    int maxDepth(string s) {
        int cnt = 0;
        int ans = 0;

        for(auto &el : s) {
            if(el == '(') {
                cnt++;
            } else if(el == ')') {
                ans = max(ans,cnt);
                cnt--;
            }
        }
        return ans;
    }
};
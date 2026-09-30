class Solution {
public:
    vector<int> maxDepthAfterSplit(auto s) {
        int n = s.size(); 
        vector<int> res(n);
        int depth = 0;
        for(int i=0;i<n;i++) {
            if(s[i] == '(') {
                res[i] = depth%2;
                depth++;
            } else if(s[i] == ')') {
                depth--;
                res[i] = depth%2;
            }
        }
        return res;
    }
};
class Solution {
public:
    string clearDigits(string s) {
        string ans;
        for(auto &el : s) {
            if(isdigit(el)) {
                ans.pop_back();
            }else{
                ans.push_back(el);
            }
        }
        return ans;
    }
};
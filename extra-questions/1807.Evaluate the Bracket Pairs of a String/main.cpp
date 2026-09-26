class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        string ans;
        int n = s.size();
        int j=0;
        unordered_map<string,string> mpp;
        for(auto el : knowledge) {
            mpp[el[0]] = el[1];
        }
        for(int i=0;i<n;i++) {
            if(s[i] == '(') {
                int j = s.find(')', i+1);
                string subString = s.substr(i + 1, j - i - 1);
                string a = (mpp.count(subString) > 0) ? mpp[subString] : "?";
                ans+=a;
                i = j;
            } else{
                ans+=s[i];
            }
        }
        return ans;
    }
};
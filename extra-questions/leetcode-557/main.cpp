class Solution {
public:
    string reverseWords(string s) {
        istringstream iss(s);
        string ans;
        string word;
        while(iss >> word) {
            reverse(word.begin(),word.end());
            ans+=word + " ";
        }
        ans.pop_back();
        return  ans;
    }
};
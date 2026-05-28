class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        unordered_map<char,int> wordMap;
        vector<string> ans;

        for(auto &c : "qwertyuiop") wordMap[c] = 1;
        for(auto &c : "asdfghjkl") wordMap[c] = 2;
        for(auto &c : "zxcvbnm") wordMap[c] = 3;

        for(auto &word : words) {
            int val=wordMap[tolower(word[0])];
            bool add = true;
            for(int i=0;i<word.size();i++) {
                if(val != wordMap[tolower(word[i])]) {
                    add = false;
                    break;
                }
            }
            if(add) ans.push_back(word);
        }

        return ans;
    }
};
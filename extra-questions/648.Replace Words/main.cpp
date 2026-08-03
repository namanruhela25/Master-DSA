class Solution {
public:
    string replaceWords(vector<string>& dict, string sentence) {
        unordered_map<string,bool> mp;
        string word,res;

        for(auto &el : dict) {
            mp[el] = true;
        }

        istringstream ss(sentence);

        while(ss >> word) {
            int i=0;
            while(i<word.size()) {
                string sbs = word.substr(0,i+1);
                if(mp.find(sbs)!=mp.end()) {
                    res += sbs + " ";
                    break;
                }
                if(i == word.size()-1) res+=sbs + " ";
                i++;
            }
        }
        res.erase(res.size()-1);
        return res;
    }
};
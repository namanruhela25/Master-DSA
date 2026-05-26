class Solution {
public:
    int numberOfSpecialChars(string word) {
        /*
        unordered_map<char,bool> mpp;

        for(auto &el : word) {
            if(isupper(el))
                mpp[el] = true;
        }

        int cnt=0;
        for(auto &el : word) {
            if(islower(el) && mpp.find(toupper(el))!=mpp.end()){
                mpp.erase(toupper(el));
                cnt++;
            }

        }
        return cnt;
        */

        int lower = 0;
        int upper = 0;

        for(char ch : word) {
            if(islower(ch)) {
                lower |= (1 << (ch - 'a'));
            }
            else {
                upper |= (1 << (ch - 'A'));
            }
        }
        
        int common = lower & upper;

        return __builtin_popcount(common);

    }
};
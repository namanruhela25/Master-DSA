class Solution {
public:
    static bool cmp(string &a, string &b) {
        return a+b > b+a;
    }

    string largestNumber(vector<int>& nums) {
        // 3 30 34 5 9
        vector<string> strs;
        for(auto &el : nums){
            strs.push_back(to_string(el));
        }
        sort(strs.begin(), strs.end(), cmp);

        if(strs[0]=="0") return "0";

        string temp="";
        for(auto &el : strs){
            temp+=el;
        }
        return temp;

    }
};
class Solution {
public:
    static bool cmp(int a,int b) {
        int a_bitcount = __builtin_popcount(a);
        int b_bitcount = __builtin_popcount(b);
        if(a_bitcount == b_bitcount) return a<b;
        return a_bitcount < b_bitcount;
    } 

    vector<int> sortByBits(vector<int>& arr) {
        sort(arr.begin(),arr.end(),cmp);
        return arr;
    }
};
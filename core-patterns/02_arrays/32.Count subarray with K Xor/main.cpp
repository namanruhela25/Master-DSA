class Solution {
  public:
    long subarrayXor(vector<int> &arr, int k) {
        long cnt = 0;
        int n = arr.size();
        unordered_map<int,int> mpp;
        long xorr = 0;
        mpp[xorr]++;
        for(auto &el : arr) {
            xorr = xorr ^ el;
            int x = xorr ^ k;
            cnt+=mpp[x];
            mpp[xorr]++;
        }
        return cnt;
    }
};
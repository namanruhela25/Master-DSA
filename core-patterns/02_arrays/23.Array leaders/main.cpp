class Solution {
  public:
    vector<int> leaders(vector<int>& arr) {
        // code here
        int n = arr.size();
        
        int lastMaximum = INT_MIN;
        vector<int> ans;
        for(int i=n-1;i>=0;i--) {
            if(lastMaximum <= arr[i]) {
                lastMaximum = arr[i];
                ans.push_back(lastMaximum);
            }
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};
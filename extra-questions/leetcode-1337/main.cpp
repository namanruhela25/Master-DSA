class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        int n = mat.size();
        int m = mat[0].size();

        for(int i=0;i<n;i++) {
            mat[i].push_back(i);
        }

        sort(mat.begin(),mat.end());
        
        /*
        for(int i=0;i<mat.size();i++) {
            for(int j=0;j<mat[0].size();j++) {
                cout<<mat[i][j]<<" ";
            }
            cout<<endl;
        } */

        vector<int> ans;

        for(int i=0;i<k;i++) {
            ans.push_back(mat[i][m]);
        }

        return ans;
    }
};
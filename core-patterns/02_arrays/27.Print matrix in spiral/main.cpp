class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& m) {
        int n = m.size();
        int colmm = m[0].size();
        vector<int> ans;

        int top = 0,left=0,right=colmm-1,bottom=n-1;
        
        while(top<=bottom && left<=right) {

            for(int i=left;i<=right;i++) {
                ans.push_back(m[top][i]);
            }

            top++;

            for(int i=top;i<=bottom;i++) {
                ans.push_back(m[i][right]);
            }

            right--;


            if(top<=bottom) {
                for(int i=right;i>=left;i--) {
                    ans.push_back(m[bottom][i]);
                }
                bottom--;
            }

            if(left<=right) {
                for(int i=bottom;i>=top;i--) {
                    ans.push_back(m[i][left]);
                }
                left++;
            }

        }
        return ans;
    }
};
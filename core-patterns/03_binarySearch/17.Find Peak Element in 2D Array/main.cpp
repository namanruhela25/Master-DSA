class Solution {
public:
    int findMaxRowElement(vector<vector<int>>& mat, int mid, int n) {
        int target = INT_MIN;
        int ans = -1;
        for(int i=0;i<n;i++) {
            if(mat[i][mid] > target) {
                ans = i;
                target = mat[i][mid];
            }
        }
        return ans;
    }
    
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();

        int low = 0;
        int high = m - 1;

        while(low <= high) {
            int mid = low + (high - low) / 2;
            int row = findMaxRowElement(mat,mid,n);
            int left = (mid - 1 >= 0) ? mat[row][mid-1] : -1;
            int right = (mid + 1 < m) ? mat[row][mid+1] : -1;
            int maxelement = mat[row][mid];

            if(maxelement > left && maxelement > right) return {row,mid};

            if(maxelement < left) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        } 
        return {-1,-1};
    }
};
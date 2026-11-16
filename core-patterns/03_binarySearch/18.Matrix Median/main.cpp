class Solution {
  public:
    int checkMid(vector<vector<int>> &mat, int &mid, int n) {
        int cnt = 0;
        for(int i=0;i<n;i++) {
            // 1 3 5
            cnt+=upper_bound(mat[i].begin(),mat[i].end(),mid) - mat[i].begin();
        }
        // cout<<"cnt = "<<cnt<<endl;
        return cnt;
    }
    
    int median(vector<vector<int>> &mat) {
        int low = INT_MAX;
        int high = INT_MIN;
        int n = mat.size();
        int m = mat[0].size();
        
        for(int i=0;i<n;i++) {
            low = min(low,mat[i][0]);
            high = max(high,mat[i][m-1]);
        }
        
        int rqElements = ((n * m)) / 2;
        
        cout<<low<<high<<endl;
        
        // 5 * 5 + 1= 26 / 2 = 13th element is the ans 
        // upper bound return greater than or equal to that val
        
        // cout<<"rqElements = "<<rqElements;
        
        while(low<=high) {
            int mid = low + (high - low) / 2;
           
            int cal = checkMid(mat,mid,n);
            
            // cout<<"mid = "<<mid<<endl;
            // cout<<"cal = "<<cal<<endl;
            
            if(cal >= rqElements) {
                high = mid - 1;
            }else {
                low = mid + 1;
            }
        }
        
        return low;
    }
};

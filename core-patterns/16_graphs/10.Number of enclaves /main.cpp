class Solution {
public:

    void dfs(int row,int col, vector<vector<int>>& mat, vector<vector<int>>& vis, int drow[],int dcol[]) {
        vis[row][col] = 1;

        int n = mat.size();
        int m = mat[0].size();

        for(int i=0;i<4;i++) {
            int nrow = row + drow[i];
            int ncol = col + dcol[i];

            if(nrow>=0 && ncol>=0 && nrow<n && ncol < m && !vis[nrow][ncol] && mat[nrow][ncol] == 1) {
                dfs(nrow,ncol,mat,vis,drow,dcol);
            }

        }
    }

    int numEnclaves(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();

        int drow[] = {-1,0,1,0};
        int dcol[] = {0,1,0,-1};

        vector<vector<int>> vis(n,vector<int>(m,0));

        for(int j=0;j<m;j++) {
            if(!vis[0][j] && mat[0][j] == 1) {
                dfs(0,j,mat,vis,drow,dcol);
            }

            if(!vis[n-1][j] && mat[n-1][j] == 1) {
                dfs(n-1,j,mat,vis,drow,dcol);
            }
        }

        for(int i=0;i<n;i++) {
            if(!vis[i][0] && mat[i][0] == 1) {
                dfs(i,0,mat,vis,drow,dcol);
            }

            if(!vis[i][m-1] && mat[i][m-1] == 1) {
                dfs(i,m-1,mat,vis,drow,dcol);
            }
        }

        int cnt = 0;
        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                if(mat[i][j] == 1 && !vis[i][j]) {
                    cnt++;
                }
            }
        }

        return cnt;

    }
};
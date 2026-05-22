class Solution {
public:
   void dfs(vector<vector<int>>& image,vector<vector<int>>& ans,int delRow[],int delCol[] ,int row, int col, int iniColor,int newColor) {
       ans[row][col] = newColor;
       int n = image.size();
       int m = image[0].size();
       for(int i=0;i<4;i++) {
           int nrow = row + delRow[i];
           int ncol = col + delCol[i];


           if(nrow >=0 && nrow < n && ncol >=0 && ncol < m && image[nrow][ncol] == iniColor && ans[nrow][ncol] != newColor) {
               dfs(image,ans,delRow,delCol,nrow,ncol,iniColor,newColor);
           }
       }
   }

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
       int iniColor = image[sr][sc];
       int delRow[] = {-1,0,1,0};
       int delCol[] = {0,1,0,-1};
       vector<vector<int>> ans = image;
       dfs(image,ans,delRow,delCol,sr,sc,iniColor,color);
       return ans;
    }
};
class Solution {
public:
   void dfs(int node,vector<int> &vis,vector<vector<int>>& isConnected,int n) {
       vis[node] = 1;
       for(int i=0;i<n;i++) {
           if(!vis[i] && isConnected[node][i] == 1) {
               dfs(i,vis,isConnected,n);
           }
       }
   }


   int findCircleNum(vector<vector<int>>& isConnected) {
       int n = isConnected.size();
       vector<int> vis(n,0);
       int cnt = 0;
       for(int i = 0; i<n;i++) {
           if(!vis[i]) {
               dfs(i,vis,isConnected,n);
               cnt++;
           }
       }
       return cnt;
   }
};

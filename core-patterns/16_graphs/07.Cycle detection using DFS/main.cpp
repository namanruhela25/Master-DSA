class Solution {
private:
bool dfs(int node, int parent, vector<vector<int>> &adj, vector<int> &vis) {
       vis[node] = 1;
       for(auto &nei : adj[node]) {
           if(!vis[nei]) {
               if(dfs(nei,node,adj,vis)) return true;
           }
           else if(nei != parent) return true;
       }
       return false;
}

public:
   bool isCycle(int V, vector<vector<int>>& edges) {
       vector<vector<int>> adj(V);
      
       for(auto &edge : edges) {
           adj[edge[0]].push_back(edge[1]);
           adj[edge[1]].push_back(edge[0]);
       }
      
       vector<int> vis(V,0);
      
       for(int node=0; node<V; node++) {
           if(!vis[node]) {
               if(dfs(node,-1,adj,vis)) return true;
           }
       }
       return false;
   }
};

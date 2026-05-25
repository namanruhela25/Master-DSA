
class Solution {
 private:
   bool bfs(int node, vector<vector<int>> &adj, vector<int> &vis) {
       queue<pair<int,int>> q;
       vis[node] = 1;
       q.push({node,-1});
      
       while(!q.empty()) {
           auto [node,parent] = q.front();
           q.pop();
          
           for(auto &nei : adj[node]) {
               if(!vis[nei]) {
                   q.push({nei,node});
                   vis[nei] = 1;
               }
               else if(parent!=nei) return true;
           }
       }
       return false;
   }

 public:
   bool isCycle(int V, vector<vector<int>>& edges) {
       // Code here
       // create a adj list graph
       vector<vector<int>> adj(V);
      
       for(auto &edge : edges) {
           adj[edge[0]].push_back(edge[1]);
           adj[edge[1]].push_back(edge[0]);
       }
      
       vector<int> vis(V,0);
      
       for(int node=0; node<V; node++) {
           if(!vis[node]) {
               if(bfs(node,adj,vis)) {
                   return true;
               }
           }
       }
      
       return false;
      
   }
};

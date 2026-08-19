class Solution {

private:
   void dfs(int node,vector<int> &vis,vector<vector<int>> &graph,stack<int> &st) {
       vis[node] = 1;
      
       for(auto &el : graph[node]) {
           if(!vis[el]) {
               dfs(el,vis,graph,st);
           }
       }
      
       st.push(node);
   }

public:
   vector<int> topoSort(int V, vector<vector<int>>& edges) {
       // code here
       vector<vector<int>> graph(V);
       vector<int> vis(V,0);

       vector<int> ans;
       stack<int> st;
      
       // O(V)
       for(auto &el : edges) {
           graph[el[0]].push_back(el[1]);
       }

       // O(V + E)
       for(int i=0;i<V;i++) {
          if(!vis[i]) {
              dfs(i,vis,graph,st);
          }
       }

       // O(V)
       while(!st.empty()) {
           ans.push_back(st.top());
           st.pop();
       }

       return ans;
   }
};

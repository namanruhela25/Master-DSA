class Solution {
public:
    vector<int> findOrder(int V, vector<vector<int>>& edges) {
       vector<vector<int>> graph(V);
       queue<int> q;
       vector<int> indegree(V,0);
      
       vector<int> ans;
      
       for(auto &el : edges) {
           graph[el[1]].push_back(el[0]);
       }
      
       for(int i=0;i<V;i++) {
           for(auto &el : graph[i]) {
               indegree[el]++;
           }
       }
      
       for(int i = 0 ; i < V; i++) {
           if(indegree[i] == 0) {
               q.push(i);
           }
       }
      
       while(!q.empty()) {
           auto node = q.front();
           q.pop();
          
           ans.push_back(node);
          
           for(auto &nei : graph[node]) {
               indegree[nei]--;
               if(indegree[nei] == 0) q.push(nei);
           }
       }
      
       if(ans.size() == V) return ans;
        return {};
    }
};
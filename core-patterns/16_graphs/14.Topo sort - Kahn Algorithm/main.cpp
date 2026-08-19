class Solution {
public:
   vector<int> topoSort(int V, vector<vector<int>>& edges) {    
      vector<vector<int>> graph(V);
      queue<int> q;
      vector<int> inDegree(V,0);

      for(auto &el : edges) {
        graph[el[0]].push_back(el[1]);
      }

      for(int i=0;i<V;i++) {
        for(auto &el : graph[i]) {
            inDegree[el]++;
        }
      }

      for(int i=0;i<V;i++) {
        if(inDegree[i] == 0) {
            q.push(i);
        }
      }

      while(!q.empty()) {
        auto node = q.front();
        q.pop();

        ans.push_back(node);

        for(auto &nei : graph[node]) {
            inDegree[nei]--;
            if(inDegree[nei] == 0) {
                q.push(nei);
            }
        }
      }

      return ans;
   }
};

class Solution {
 public:
    bool dfs(int node, vector<int> &vis,vector<vector<int>> &graph) {
        vis[node] = 2;

        for(auto &nei : graph[node]) {
            if(vis[nei] == 0) {
                if(dfs(nei,vis,graph) == true) return true;
            } else if(vis[nei] == 2) {
                return true;
            }
        }

        vis[node] = 1;
        return false;
    }

    bool isCyclic(int V, vector<vector<int>> &edges) {
        vector<vector<int>> graph(V);

        vector<int> vis(V,0);

        for(auto &el : edges) {
            graph[el[0]].push_back(el[1]);
        }

        for(int i=0;i<V;i++) {
            if(!vis[i]) {
                if(dfs(i,vis,graph) == true) return true;
            }
        }

        return false;
    }
};

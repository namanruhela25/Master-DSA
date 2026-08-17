class Solution {
public:
    bool dfs(int node, int cl, vector<int> &color, vector<vector<int>>& graph) {
        color[node] = cl;
        for(auto &nei : graph[node]) {
            if(color[nei] == -1) {
                if(dfs(nei,1-cl,color,graph) == false) return false;
            } else if(cl == color[nei]) {
                return false;
            }
        }
        return true;
    }
     
    bool isBipartite(vector<vector<int>>& graph) {
        int v = graph.size();
        vector<int> color(v,-1);
        for(int i=0;i<v;i++) {
            if(color[i] == -1) {
                // immediately return false if a component is returning false
                // because this graph can never be bi-partite
                if(dfs(i,0,color,graph) == false) return false;
            }
        }
        return true;
    }
};
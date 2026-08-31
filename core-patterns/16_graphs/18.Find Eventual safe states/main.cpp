class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        vector<int> ans;
        int V = graph.size();
        vector<vector<int>> adj(V);

        vector<int> indegree(V,0);

        queue<int> q;

        for(int i=0;i<V;i++) {
            for(auto &el : graph[i]) {
                adj[el].push_back(i);
                indegree[i]++;
            }
        }

        for(int i=0;i<V;i++) {
            if(indegree[i] == 0) q.push(i);
        }

        while(!q.empty()) {
            int node = q.front();
            q.pop();
            ans.push_back(node);

            for(int &nei : adj[node]) {
                indegree[nei]--;
                if(indegree[nei] == 0) {
                    q.push(nei);
                }
            }
        }

        sort(ans.begin(),ans.end());

        return ans;

    }
};
class Solution {
public:
    bool bfs(int start, vector<int>& color, vector<vector<int>>& graph) {

        queue<int> q;
        q.push(start);
        color[start] = 0;

        while (!q.empty()) {

            int node = q.front();
            q.pop();

            for (auto nei : graph[node]) {

                // Not colored yet
                if (color[nei] == -1) {
                    color[nei] = 1 - color[node];
                    q.push(nei);
                }

                // Same color => not bipartite
                else if (color[nei] == color[node]) {
                    return false;
                }
            }
        }

        return true;
    }

    bool isBipartite(vector<vector<int>>& graph) {

        int n = graph.size();
        vector<int> color(n, -1);

        // Handle disconnected components
        for (int i = 0; i < n; i++) {

            if (color[i] == -1) {
                if (!bfs(i, color, graph))
                    return false;
            }
        }

        return true;
    }
};
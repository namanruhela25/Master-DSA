// Recursive solution
class Solution {
  public:
   void helper(int idx, vector<vector<int>> &adj, vector<bool> &visited, vector<int> &res) {
       visited[idx] = true;
       res.push_back(idx);
       for (int neighbor : adj[idx]) {
           if (visited[neighbor] == false) helper(neighbor, adj, visited, res);
       }
   }
    vector<int> dfs(vector<vector<int>>& adj) {
        // Code here
        vector<bool> visited(adj.size(), false);
        vector<int> res;
        helper(0, adj, visited, res);
        return res;
    }
};

// Stack solution
class Solution {
public:
    vector<int> dfs(vector<vector<int>>& adj) {
        int n = adj.size();
        vector<int> visited(n, 0);
        vector<int> ans;
        stack<int> st;

        st.push(0);

        while(!st.empty()) {
            int node = st.top();
            st.pop();

            if(visited[node]) continue;   // 🔑 critical check

            visited[node] = 1;
            ans.push_back(node);

            // push neighbors in reverse order
            for(int i = adj[node].size() - 1; i >= 0; i--) {
                int neigh = adj[node][i];
                if(!visited[neigh]) {
                    st.push(neigh);
                }
            }
        }

        return ans;
    }
};

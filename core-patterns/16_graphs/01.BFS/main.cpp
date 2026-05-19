vector<int> bfsTraversal(int n, vector<vector<int>> &adj){
   vector<int> ans;
   queue<int> q;
   vector<int> visited(n,0);


   q.push(0);
   visited[0] = 1;


   while(!q.empty()) {
       int node = q.front();
       q.pop();
       ans.push_back(node);


       for(int i=0;i < adj[node].size(); i++) {
           if(!visited[adj[node][i]]) {
               q.push(adj[node][i]);
               visited[adj[node][i]] = 1;
           }
       }
   }


   return ans;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);

    adj = {
        {1, 2},    // Neighbors of node 0
        {0, 3},    // Neighbors of node 1
        {0, 3},    // Neighbors of node 2
        {1, 2}     // Neighbors of node 3
    };

    vector<int> bfsResult = bfsTraversal(n, adj);
    for (int node : bfsResult) {
        cout << node << " ";
    }
    cout << endl;
    return 0;
}
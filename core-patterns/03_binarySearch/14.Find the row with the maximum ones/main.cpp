int findIndex(vector<int> &row,int m) {
    int low = 0;
    int high = m - 1;

    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(row[mid] == 1) {
            high = mid - 1;
        } else{
            low = mid + 1;
        }
    }
    return low;
}

int rowWithMax1s(vector<vector<int>> &mat, int n, int m) {
    int ansRow = -1;
    int ones = 0;
    for(int i=0;i<n;i++) {
        int index = findIndex(mat[i],m);
        int onecounts = m - index;
        if(onecounts > ones) {
            ones = onecounts;
            ansRow = i;
        }
    }
    return ansRow;
}

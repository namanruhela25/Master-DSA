int possible(vector<int>& arr, int m, int mid) {
    int std = 1;
    int allocatedPages = 0;
    for(auto &p : arr) {
        if(p + allocatedPages <= mid) {
            allocatedPages+=p;
        }else{
            allocatedPages = p;
            std++;
        }   
    }
    return std;
}

int findPages(vector<int>& arr, int n, int m) {
    if(m > arr.size()) return -1;
    int low = *max_element(arr.begin(),arr.end());
    int high = accumulate(arr.begin(),arr.end(),0);

    while(low <= high) {
        int mid = low + (high - low) / 2;
        int stduents = possible(arr,m,mid);
        if(stduents <= m) {
            high = mid - 1;
        } else{
            low = mid + 1;
        }
    }
    return low;
}
class Solution {
  public:
    
    bool canWePlace(vector<int> &arr,int mid, int k) {
        int cows = 1;
        int last = arr[0];
        int n = arr.size();
        
        for(int i=1;i<n;i++) {
            if(arr[i] - last >= mid) {
                last = arr[i];
                cows++;
            }
            if(cows == k) return true;
        }
        
        return false;
        
    }
    
    
    int aggressiveCows(vector<int> &arr, int k) {
        std::sort(arr.begin(),arr.end());
        int n = arr.size();
        int low = 1;
        int high = arr[n-1] - arr[0];
        
        while(low<=high) {
            int mid = low + (high - low) / 2;
            
            if(canWePlace(arr,mid,k)) {
                low = mid + 1;
            }else {
                high = mid - 1;
            }
        }
        return high;
    }
};
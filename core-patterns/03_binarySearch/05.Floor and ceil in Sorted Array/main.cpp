class Solution {
  public:
    vector<int> getFloorAndCeil(int x, vector<int> &arr) {
        int low = 0;
        int high = arr.size() - 1;
        
        int floorval = -1;
        int ceilval = -1;
        
        sort(arr.begin(),arr.end());
        
        while(low <= high) {
            int mid = low + (high - low) / 2;
            
            if(arr[mid] == x) return {x,x};
            
            if(arr[mid] < x) {
                floorval = arr[mid];
                low = mid + 1;
            } else{
                ceilval = arr[mid];
                high = mid - 1;
            }
        }
        
        return {floorval,ceilval};
    }
};
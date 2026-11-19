class Solution {
  public:
    int kthElement(vector<int> &a, vector<int> &b, int k) {
        int n = a.size();
        int m = b.size();
        
        if(n > m) return kthElement(b,a,k);
        
        // a--> 2 , k = 6
        // b--> 5
        // I have to consider 1 from a at least 
        // because if I take 0 from a the b can never fullfill the demand of 
        // 6 elements from its array
        int low = max(0, k - m);
        
        // a --> 5 , k = 2, max i can pick only 2, 
        int high = min(k,n); 
        
        
        while(low <= high) {
            int Px = low + (high - low) / 2;
            int Py = k - Px;
            
            // 2 3 | 6 7 9 
        
            // 1 4 8 | 10 
            
            int x1 = (Px == 0) ? INT_MIN : a[Px-1];
            int x2 = (Py == 0) ? INT_MIN : b[Py-1];
            
            int x3 = (Px == n) ? INT_MAX : a[Px];
            int x4 = (Py == m) ? INT_MAX : b[Py];
            
            if(x1 <= x4 && x2 <= x3) {
                return max(x1,x2);
            }
            
            if(x1 > x4) {
                high = Px-1;
            } else{
                low = Px + 1;
            }
        }
        return -1;
        
    }
};
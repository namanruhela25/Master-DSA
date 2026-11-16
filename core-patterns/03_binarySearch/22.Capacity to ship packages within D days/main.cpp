class Solution {
public:
    int find(vector<int>& w, int mid) {
        int days = 1; // Day 1 , should be counted
        int currW = 0;
        for(auto &el : w) {
            if(currW + el <= mid) {
                currW+=el;
            }else{
                currW = el;
                days++;
            }
        } 
        return days;
    }

    int shipWithinDays(vector<int>& w, int days) {
        int low = *max_element(w.begin(),w.end()); // Find weight with maximum that should be minimum capacity we should consider
        int high = accumulate(w.begin(),w.end(),0);

        while(low <= high) {
            int mid = low + (high - low) / 2;
            int noofdays = find(w,mid);

            if(noofdays <= days) {
                high = mid - 1;
            }else{
                low = mid + 1;
            }
        }
        return low;
    }
};
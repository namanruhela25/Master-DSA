class Solution {
public:
    long long calculateHrs(int k, vector<int>& piles) {
        long long totalhrs = 0;
        for(auto &el : piles) {
            totalhrs=totalhrs + (el / k);
            if(el % k !=0) totalhrs++;
        }
        return totalhrs;
    }

    int minEatingSpeed(vector<int>& piles, int h) {
        int low = 1;
        int high = *max_element(piles.begin(),piles.end());

        cout<<low<<high;

        while(low<=high) {
            int mid = low + (high - low) / 2;
            long long hrs = calculateHrs(mid,piles);

            if(hrs<=h) {
                high = mid - 1;
            } else{
                low = mid + 1;
            }
        }

        return low;
    }
};
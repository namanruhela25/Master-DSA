class Solution {
public:
    int calculateBouquet(vector<int>& bloomDay, int k, int mid) {
        int consecutive_cnt = 0;
        int bouque_cnt = 0;
        for(auto &el : bloomDay) {
            if(el <= mid) {
                consecutive_cnt++;
            }else {
                consecutive_cnt = 0;
            }
            if(consecutive_cnt == k) {
                bouque_cnt++;
                consecutive_cnt = 0;
            }
        }
        return bouque_cnt;
    }

    int minDays(vector<int>& bloomDay, int m, int k) {
        int low = *min_element(bloomDay.begin(),bloomDay.end());
        int high = *max_element(bloomDay.begin(),bloomDay.end());

        int minDays = -1;
        while(low <= high) {
            int mid = low + (high - low) / 2;
            int bouquetMade = calculateBouquet(bloomDay, k, mid);

            if(bouquetMade >= m) {
                minDays = mid;
                high = mid - 1;
            } else{
                low = mid + 1;
            }
        }
        return minDays;
    }
};
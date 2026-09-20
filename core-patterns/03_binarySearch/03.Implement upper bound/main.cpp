#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int getUpperBound(int k, vector<int> &arr) {
        int n = arr.size();
        int low = 0;
        int high = n - 1;

        sort(arr.begin(), arr.end());

        while (low <= high) {
            cout<<low<<" "<<high<<endl;
            int mid = low + (high - low) / 2;

            if (arr[mid] <= k) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return arr[low];
    }
};

int main() {
    Solution sol;

    vector<int> arr = {3, 5, 5, 6, 6, 6, 8, 9};
    int k = 7;

    int ans = sol.getUpperBound(k, arr);

    cout << "Upper bound of " << k << " = " << ans << endl;

    return 0;
}
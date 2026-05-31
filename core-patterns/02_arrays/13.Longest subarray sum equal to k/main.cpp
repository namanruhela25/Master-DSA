#include <bits/stdc++.h>
using namespace std;

class Solution{
public:
int longestSubarray(vector<int> &nums, int k) {
    int n = nums.size();
    int left = 0, right = 0;
    int curr = 0;       
    int maxlen = 0;

    while (right < n) {
        curr += nums[right];  

        while (left < right && curr > k) {
            curr -= nums[left];
            left++;
        }

        if (curr == k) {
            maxlen = max(maxlen, right - left + 1);
        }

        right++;
    }
    return maxlen;
}
};

int main() {
	vector<int> nums = {10, 5, 2, 7, 1, 9};
    int k = 15;
    
	Solution sol;

	int ans = sol.longestSubarray(nums, k);

	cout << "The length of longest subarray having sum k is: " << ans;

	return 0;
}

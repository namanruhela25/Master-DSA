class Solution {
public:
  vector<int> findOriginalArray(vector<int> &nums) {
    int n = nums.size();
    vector<int> ans;
    sort(nums.begin(), nums.end());
    // 0 1 3 6
    for (int i = 0; i < n; i++) {
      int num = nums[i];
      if (num < 0)
        continue;

      // Binary search logic
      auto idx = lower_bound(nums.begin() + i + 1, nums.end(), 2 * num);

      // kyuki current is greater number hamesha aage hi milega

      if (idx != nums.end() && *idx == 2 * num) {
        *idx = -1;
        ans.push_back(num);
      } else {
        return {};
      }
    }
    return ans;
  }
};
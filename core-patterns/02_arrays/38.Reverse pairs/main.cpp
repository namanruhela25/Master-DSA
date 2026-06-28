#include <bits/stdc++.h>

using namespace std;

void merge(vector<int> &nums, int low, int high, int mid) {
  int i = low;
  int j = mid + 1;
  vector<int> temp;

  while (i <= mid && j <= high) {
    if (nums[i] <= nums[j]) {
      temp.push_back(nums[i]);
      i++;
    } else {

      temp.push_back(nums[j]);
      j++;
    }
  }

  while (i <= mid) {
    temp.push_back(nums[i]);
    i++;
  }

  while (j <= high) {
    temp.push_back(nums[j]);
    j++;
  }

  for (int i = low; i <= high; i++) {
    nums[i] = temp[i - low];
  }
}

int countPairs(vector<int> &nums, int low, int mid, int high) {
  int left = low;
  int cnt = 0;
  int right = mid + 1;
  for (int i = low; i <= mid; i++) {
    while (right <= high && (nums[i] > 2 * nums[right]))
      right++;
    cnt = cnt + right - (mid + 1);
  }
  return cnt;
}

int mergSort(vector<int> &nums, int low, int high) {
  int mid = (low + high) / 2;
  int cnt = 0;
  if (low < high) {
    cnt += mergSort(nums, low, mid);
    cnt += mergSort(nums, mid + 1, high);
    cnt += countPairs(nums, low, mid, high);
    merge(nums, low, high, mid);
  }
  return cnt;
}

int main() {
  vector<int> nums = {2, 4, 3, 5, 1};
  int n = nums.size();
  int inversions = mergSort(nums, 0, n - 1);
  cout << "Count of inversions: " << inversions << endl;
  return 0;
}
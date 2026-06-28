class Solution {
public:
  vector<int> findTwoElement(vector<int> &arr) {
    long long n = arr.size();
    long long S = (n * (n + 1)) / 2;
    long long S2n = (n * (n + 1) * (2 * n + 1)) / 6;

    long long sum1 = 0;
    long long sum2 = 0;

    for (int &el : arr) {
      sum1 += el;
      sum2 += 1LL * el * el;
    }

    long long val1 = sum1 - S;
    long long val2 = sum2 - S2n;

    val2 = val2 / val1;

    long long x = (val1 + val2) / 2;

    long long y = val2 - x;

    return {(int)x, (int)y};
  }
};
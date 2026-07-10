class Solution {
public:
  int compareVersion(string version1, string version2) {
    int n = version1.size();
    int m = version2.size();
    int i = 0, j = 0;

    while (i < n || j < m) {

      string temp1;
      while (i < n && version1[i] != '.') {
        temp1.push_back(version1[i]);
        i++;
      }

      int num1 = temp1.empty() ? 0 : stoi(temp1);

      string temp2;
      while (j < m && version2[j] != '.') {
        temp2.push_back(version2[j]);
        j++;
      }

      int num2 = temp2.empty() ? 0 : stoi(temp2);

      if (num1 > num2)
        return 1;

      if (num1 < num2)
        return -1;

      i++;
      j++;
    }
    return 0;
  }
};
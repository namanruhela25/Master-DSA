class Solution {
public:
    string reverseOnlyLetters(string s) {
        int n = s.size();
        int i=0;
        int j=n-1;

        while(i<j) {
            while(i<n && !isalpha(s[i])) i++;
            while(j>=0 && !isalpha(s[j])) j--;
            if(i<j) {
                swap(s[i],s[j]);
                i++;
                j--;
            }
        }
        return s;
    }
};
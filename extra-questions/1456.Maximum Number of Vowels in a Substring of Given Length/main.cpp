class Solution {
public:
    bool isVowel(char ch) {
        if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') 
            return true;
        return false;
    }

    int maxVowels(string s, int k) {
        int i=0;
        int j=0;
        int maxVal=0;
        int count=0;
        int n = s.size();
        while(j < n) {
            if(isVowel(s[j])) {
                count++;
            }
            if(j - i + 1 == k) {
                maxVal = max(maxVal, count);
                if(isVowel(s[i])) count--;
                i++; 
            }
            j++;
        }
        return maxVal;
    }
};
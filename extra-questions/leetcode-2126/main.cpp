class Solution {
public:
    bool asteroidsDestroyed(int mass, vector<int>& a) {
        
        /*
        0 1 2 3 4 5 6 7 8 9 ,,,,, 20 21 22 23 24
                2         1                 1
        */

        int n = a.size();

        int maxi = *max_element(a.begin(),a.end());

        vector<int> freq(maxi+1,0);

        for(int &el : a) {
            freq[el]++;
        }

        long long curr = mass;

        for(int i=1;i<=maxi;i++) {
            if(freq[i] > 0) {
                if(curr >= i) {
                    curr+=(long long)i*freq[i];
                }else{
                    return false;
                }
            }
        }
        return true;
    }
};
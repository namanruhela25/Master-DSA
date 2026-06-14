class Solution {
public:
    void setZeroes(vector<vector<int>>& m) {
        int rown = m.size();
        int colm = m[0].size();
        int col0 = 1;

        for(int i=0;i<rown;i++) {
            for(int j=0;j<colm;j++) {
                if(m[i][j] == 0) {
                    m[i][0] = 0;
                    if(j==0) { 
                        col0=0;
                    } else{
                        m[0][j] = 0;
                    }            
                }
            }
        }

        for(int i=1;i<rown;i++) {
            for(int j=1;j<colm;j++) {
                if(m[i][j]!=0) {
                    if(m[0][j] == 0 || m[i][0] == 0) {
                        m[i][j] = 0;
                    }
                }
            }
        }

        if(m[0][0] == 0) {
            for(int j=0;j<colm;j++) {
                m[0][j] = 0;
            }
        }

        if(col0 == 0) {
            for(int i=0;i<rown;i++) {
                m[i][0] = 0;
            }
        }
        
    }
};
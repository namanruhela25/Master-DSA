class Solution {
public:
    static bool comp(vector<int> &v1,vector<int> &v2) {
        return v1[1] < v2[1];
    }

    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(),points.end(),comp);

        int n = points.size();
        int count = 1;
        int prevlast = points[0][1];

        for(int i=1;i<n;i++) {
            int currstart = points[i][0];
            if(prevlast < currstart) {
                count++;
                prevlast = points[i][1];
            }
        }

        return count;
    }
};
class Solution {
public:
    int calPoints(vector<string>& operations) {
        int sum = 0;
        stack<int> st;

        for(auto &el : operations) {
            if(el == "+"){
                int top1 = st.top();
                st.pop();
                int top2 = st.top();
                st.push(top1);
                int newscore = top1 + top2;
                st.push(newscore);
                sum+=newscore;
            } else if(el == "D") {
                int top1 = st.top();
                int doubleval = top1 * 2;
                st.push(doubleval);
                sum+=doubleval;
            } else if(el == "C") {
                sum-=st.top();
                st.pop();
            } else {
                int num = stoi(el);
                sum+=num;
                st.push(num);
            } 
        }
        return sum;
    }
};
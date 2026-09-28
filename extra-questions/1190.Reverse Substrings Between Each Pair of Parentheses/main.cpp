class Solution {
public:
    string reverseParentheses(string s) {
        int n = s.size();
        stack<int> st;
        vector<int> link(n);
        string res;

        for(int i=0;i<n;i++) {
            if(s[i] == '('){
                st.push(i);
            } else if(s[i] == ')') {
                link[i] = st.top();
                link[st.top()] = i;
                st.pop();
            }
        }

        for(int i=0,dir = 1;i<n;i+=dir) {
            if(s[i] >= 'a') {
                res+=s[i];
            } else{
                i = link[i];
                dir = -dir;
            }
        }

        return res;
        
    }
};
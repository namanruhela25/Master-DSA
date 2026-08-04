class Solution {
public:
    vector<vector<string>> findDuplicate(vector<string>& paths) {
        unordered_map<string,vector<string>> mp;
        vector<vector<string>> ans;
        for(auto &path : paths) {
            istringstream ss(path);
            string dir;
            ss >> dir;
            string file;

            while(ss >> file) {
                string content =  file.substr(file.find('(') + 1, file.find(')') - file.find('(') - 1); 
                // cout<<"content : "<<content<<endl;
                string filename = file.substr(0,file.find('('));
                string filedir = dir + "/" + filename;
                // cout<<"filedir : "<<filedir<<endl;
                mp[content].push_back(filedir);
            }
        }
        for(auto &el : mp) {
            if(el.second.size() > 1) {
                ans.push_back(el.second);
            }
        }
        return ans;
    }
};
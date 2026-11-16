class LRUCache {
public:
    list<int> dll;
    unordered_map<int,pair<int,list<int>::iterator>> mpp;
    int n;
    LRUCache(int capacity) {
        n = capacity;
    }
    void markRecentlyUsed(int &key) {
        dll.erase(mpp[key].second);
        dll.push_front(key);
        mpp[key].second = dll.begin();
    }
    int get(int key) {
        if(mpp.find(key) == mpp.end()) {
            return -1;
        }
        markRecentlyUsed(key);
        return mpp[key].first;
    }
    void put(int key, int value) {
        if(mpp.find(key)!=mpp.end()) {
            mpp[key].first = value;
            markRecentlyUsed(key);
        } else {
            dll.push_front(key);
            mpp[key] = {value,dll.begin()};
            n--;
        }
        if(n<0) {
            int key_to_del = dll.back();
            mpp.erase(key_to_del);
            dll.pop_back();
            n++;
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
#include <bits/stdc++.h>

using namespace std;

int merge(vector<int> &nums,int low, int high, int mid) {
    int i = low;
    int j = mid+1;
    vector<int> temp;
    int cnt = 0;

    while(i<=mid && j<=high) {
        if(nums[i] <= nums[j]) {
            temp.push_back(nums[i]);
            i++;
        } else{
            cnt+=(mid-i+1);
            temp.push_back(nums[j]);
            j++;
        }
    }

    while(i<=mid) {
        temp.push_back(nums[i]);
        i++;
    }

    while(j<=high) {
        temp.push_back(nums[j]);
        j++;
    }

    for(int i=low; i <= high; i++) {
        nums[i] = temp[i - low];
    }

    return cnt;
}


int mergSort(vector<int> &nums,int low, int high) {
    int mid = (low + high) / 2;
    int cnt = 0;
    if(low < high) {
        cnt += mergSort(nums,low,mid);
        cnt += mergSort(nums,mid + 1,high);
        cnt += merge(nums,low,high,mid);
    }
    return cnt;
}


int main() {
    vector<int> nums = {1, 20, 6, 4, 5};
    int n = nums.size();
    int inversions = mergSort(nums,0,n-1);
    cout << "Count of inversions: " << inversions << endl;
    return 0;
}
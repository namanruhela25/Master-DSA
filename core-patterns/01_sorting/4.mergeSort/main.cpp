#include<bits/stdc++.h>

using namespace std;

void merge(vector<int> &nums,int low, int high, int mid) {
    int i = low;
    int j = mid+1;
    vector<int> temp;

    while(i<=mid && j<=high) {
        if(nums[i] <= nums[j]) {
            temp.push_back(nums[i]);
            i++;
        } else{
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
        /*
            why written i - low ?
            because temp array is starting from index 0 but we want to copy the elements in the original array from index low to high. so we need to subtract low from i to get the correct index in temp array.
            
            for this consider right subarray where lets suppose

            temp = {4,5,6}
                    0,1,2 -- index

            nums[] = {6,5,4}
                      3,4,5 -- index

            low = 3, high = 5

            we want temp index=0 for low=3 (3-3=0)
                         index=1 for low=4 (4-3=1)
                         index=2 for low=5 (5-3=2)
        */ 
        

        // 
    }

}


void mergSort(vector<int> &nums,int low, int high) {
    int mid = (low + high) / 2;
    if(low < high) {
        mergSort(nums,low,mid);
        mergSort(nums,mid + 1,high);
        merge(nums,low,high,mid);
    }
}


int main() {
    vector<int> nums = {38, 27, 43, 3, 9, 82, 10};
    int n = nums.size();
    
    // pass first and last index
    mergSort(nums,0,n-1);

    for(int i=0; i<n; i++) {
        cout << nums[i] << " ";
    }
    return 0;
}
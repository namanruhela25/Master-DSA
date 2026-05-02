int partition(vector<int> &nums,int start,int end) {
    int pivot = nums[start];
    int i=start+1;
    int j=end;

    while(i<j) {
        while(i<=end-1 && nums[i]<=pivot) { // already in its place if smaller than nums[i] move i
            i++;
        }
        while(j>=start+1 && nums[j]>pivot) { // already in its place if greater than nums[j] move j
            j--;
        }

        if(i<j) swap(nums[i],nums[j]);
    }
    
    swap(nums[start],nums[j]);
    /*
        why j ?
        because it is shifting to more minimum value so with that we have to replace starting pivot index
    */ 
    
    return j;

}

void quickSort(int start,int end,vector<int> &nums) {
    if(start < end) {
        int pivotIndex=partition(nums,start,end);
        quickSort(start,pivotIndex-1,nums);
        quickSort(pivotIndex+1,end,nums);
    }
}


int main() {
    vector<int> nums = {5,4,3,2,1};
    int n = nums.size();
    quickSort(0,n-1,nums);
    for(int i=0; i<n; i++) {
        cout<<nums[i]<<" ";
    }
}
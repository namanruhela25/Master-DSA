int solve(vector<int> &nums,int mid ,int n) {
    int hrs = 0;
    int painters = 1;

    for(int i=0;i<n;i++) {
        if(nums[i] + hrs <= mid) {
            hrs+=nums[i];
        } else{
            hrs = nums[i];
            painters++;
        }
    }
    return painters;
}

int findLargestMinDistance(vector<int> &nums, int k)
{   
    int n = nums.size();
    int low = *max_element(nums.begin(),nums.end());
    int high = accumulate(nums.begin(),nums.end(),0);
    while(low<=high) {
        int mid = low + (high - low) / 2;
        int painters = solve(nums,mid,n);
        if(painters <= k) {
            high = mid - 1;
        } else{
            low = mid + 1;
        }
    }
    return low;
}
#include<vector>

void swapifgreater(vector<long long>& nums1, vector<long long>& nums2, int ind1, int ind2) {
	if(nums1[ind1] > nums2[ind2]) {
		swap(nums1[ind1],nums2[ind2]);
	}
}

int nextGap(int len) {
    /*
        why 1 ?
        because when length become 1 ceil value always return 1
        So our loop went to infinite loop and never exit
    */
	if(len<=1) return 0;
	return (len/2) + (len%2);
}

void mergeTwoSortedArraysWithoutExtraSpace(vector<long long> &nums1, vector<long long> &nums2){
	int m = nums1.size();
	int n = nums2.size();

	int len = (m+n);
	int gap = nextGap(len);

	while(gap > 0) {
		int left = 0;
		int right = gap + left;
		while(right < len) {
			// nums1,nums2
			if(left < m && right>=m) {
				swapifgreater(nums1,nums2,left,right - m);
			} 
			// nums2,nums2
			else if(left>=m) {
				swapifgreater(nums2,nums2,left-m,right-m);
			}
			// nums1,nums1
			else if(right<m) {
				swapifgreater(nums1,nums1,left,right);
			}
			left++;
			right++;
		}

		gap = nextGap(gap);
	}	
}
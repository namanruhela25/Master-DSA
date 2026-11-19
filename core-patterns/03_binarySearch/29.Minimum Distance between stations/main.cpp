#include<bits/stdc++.h>
double minimiseMaxDistance(vector<int> &arr, int k){
	int n = arr.size();
	vector<int> howMany(n-1,0);
	priority_queue<pair<long double,int>> pq;
	for(int i=0;i<n-1;i++) {
		pq.push({arr[i+1] - arr[i],i});
	}
	for(int station = 1; station <= k; station++) {
		auto tp = pq.top();
		pq.pop();
		int secInd = tp.second;
		howMany[secInd]++;
		long double iniDiff = arr[secInd + 1] - arr[secInd];
		long double secLength = (long double) (iniDiff) / (howMany[secInd] + 1);
		pq.push({secLength,secInd});
	}
	return pq.top().first;
}

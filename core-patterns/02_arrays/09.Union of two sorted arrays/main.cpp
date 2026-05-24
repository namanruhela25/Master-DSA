
vector<int> unionOfSortedArrays(vector<int>& arr1, vector<int>& arr2) {
    int m = arr1.size(), n = arr2.size();
    int i = 0, j = 0;
    vector<int> result;

    while (i < m && j < n) {
        // Skip duplicates in arr1
        while (i > 0 && i < m && arr1[i] == arr1[i - 1]) i++;
        // Skip duplicates in arr2
        while (j > 0 && j < n && arr2[j] == arr2[j - 1]) j++;

        if (i >= m || j >= n) break;

        if (arr1[i] == arr2[j]) {
            if (result.empty() || result.back() != arr1[i])
                result.push_back(arr1[i]);
            i++;
            j++;
        } else if (arr1[i] < arr2[j]) {
            if (result.empty() || result.back() != arr1[i])
                result.push_back(arr1[i]);
            i++;
        } else {
            if (result.empty() || result.back() != arr2[j])
                result.push_back(arr2[j]);
            j++;
        }
    }

    // Drain remaining elements of arr1
    while (i < m) {
        if (result.empty() || result.back() != arr1[i])
            result.push_back(arr1[i]);
        i++;
    }

    // Drain remaining elements of arr2
    while (j < n) {
        if (result.empty() || result.back() != arr2[j])
            result.push_back(arr2[j]);
        j++;
    }

    return result;
}
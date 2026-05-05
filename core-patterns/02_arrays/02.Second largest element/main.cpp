int secondLargest(int arr[], int n) {
    if (n < 2)
        return -1;

    int large = INT_MIN, second_large = INT_MIN;

    for (int i = 0; i < n; i++) {
        if (arr[i] > large) {
            second_large = large;
            large = arr[i];
        } 
        else if (arr[i] > second_large && arr[i] != large) {
            second_large = arr[i];
        }
    }
    return second_large;
}


int secondSmallest(int arr[], int n) {
    if (n < 2)
        return -1;

    int small = INT_MAX;
    int second_small = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (arr[i] < small) {
            second_small = small;
            small = arr[i];
        } 
        else if (arr[i] < second_small && arr[i] != small) {
            second_small = arr[i];
        }
    }
    return second_small; 
}

int main() {
    int arr[] = {3, 5, 7, 2, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int second_largest = secondLargest(arr, n);
    std::cout << "The second largest element in the array is: " << second_largest << std::endl;

    int second_smallest = secondSmallest(arr, n);
    std::cout << "The second smallest element in the array is: " << second_smallest << std::endl;

    return 0;
}
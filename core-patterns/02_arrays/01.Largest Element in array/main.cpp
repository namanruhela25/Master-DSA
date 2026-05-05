int findLargestElement(int arr[], int n) {
    int max = arr[0];  
    
    for (int i = 1; i < n; i++) {
        if (max < arr[i]) { 
            max = arr[i];
        }
    }

    return max;  
}

int main() {
    int arr[] = {3, 5, 7, 2, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int largest = findLargestElement(arr, n);
    std::cout << "The largest element in the array is: " << largest << std::endl;

    return 0;
}
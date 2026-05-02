class BubbleSort {
public:
    void bubble_sort(vector<int>& arr) {
        int n = arr.size();
        for (int i = n - 1; i >= 0; i--) { // Start setting last element
            for (int j = 0; j <= i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]); 
                }
            }
        }
        cout << "After Using Bubble Sort:\n";
        for (int num : arr) {
            cout << num << " ";
        }
        cout << endl;
    }
};


int main() {
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    BubbleSort bs;
    bs.bubble_sort(arr);
    return 0;
}
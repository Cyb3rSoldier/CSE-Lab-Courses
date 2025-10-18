
#include <bits/stdc++.h>
using namespace std;

void countingSort(vector<int>& arr) {
    // Step 1: Find the maximum element
    int maxVal = *max_element(arr.begin(), arr.end());

    // Step 2: Create count vector and initialize with 0
    vector<int> count(maxVal + 1, 0);

    // Step 3: Count the occurrences of each element
    for (int num : arr) {
        count[num]++;
    }

    // Step 4: Reconstruct the sorted array
    int index = 0;
    for (int i = 0; i <= maxVal; i++) {
        while (count[i] > 0) {
            arr[index++] = i;
            count[i]--;
        }
    }
}

int main() {
    vector<int> arr = {4, 2, 2, 8, 3, 3, 1};

    cout << "Original array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    countingSort(arr);

    cout << "Sorted array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
    void merge(vector<int>& nums, vector<int>& indices, vector<int>& tempIndices, 
               vector<int>& count, int left, int mid, int right) {
        int i = left;      // Pointer for left half
        int j = mid + 1;   // Pointer for right half
        int k = left;      // Pointer for temp array
        int rightCounter = 0; // Count of elements from the right half smaller than left[i]

        while (i <= mid && j <= right) {
            // If the element in right half is strictly smaller
            if (nums[indices[j]] < nums[indices[i]]) {
                rightCounter++;
                tempIndices[k++] = indices[j++];
            } else {
                count[indices[i]] += rightCounter;
                tempIndices[k++] = indices[i++];
            }
        }

        while (i <= mid) {
            count[indices[i]] += rightCounter;
            tempIndices[k++] = indices[i++];
        }

        while (j <= right) {
            tempIndices[k++] = indices[j++];
        }

        for (int p = left; p <= right; p++) {
            indices[p] = tempIndices[p];
        }
    }

    void mergeSort(vector<int>& nums, vector<int>& indices, vector<int>& tempIndices, 
                   vector<int>& count, int left, int right) {
        if (left >= right) return;

        int mid = left + (right - left) / 2;
        mergeSort(nums, indices, tempIndices, count, left, mid);
        mergeSort(nums, indices, tempIndices, count, mid + 1, right);
        merge(nums, indices, tempIndices, count, left, mid, right);
    }

    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> count(n, 0);
        vector<int> indices(n);
        vector<int> tempIndices(n);

        // Track original positions
        iota(indices.begin(), indices.end(), 0);

        mergeSort(nums, indices, tempIndices, count, 0, n - 1);
        return count;
    }
};

void printVector(const vector<int>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i] << (i + 1 < vec.size() ? ", " : "");
    }
    cout << "]\n";
}

int main() {
    Solution solver;

    // Test Case 1: [5, 2, 6, 1] -> [2, 1, 1, 0]
    vector<int> nums1 = {5, 2, 6, 1};
    cout << "Input:  ";
    printVector(nums1);
    cout << "Output: ";
    printVector(solver.countSmaller(nums1));
    cout << "\n";

    // Test Case 2: [-1] -> [0]
    vector<int> nums2 = {-1};
    cout << "Input:  ";
    printVector(nums2);
    cout << "Output: ";
    printVector(solver.countSmaller(nums2));
    cout << "\n";

    // Test Case 3: [-1, -1] -> [0, 0]
    vector<int> nums3 = {-1, -1};
    cout << "Input:  ";
    printVector(nums3);
    cout << "Output: ";
    printVector(solver.countSmaller(nums3));

    return 0;
}
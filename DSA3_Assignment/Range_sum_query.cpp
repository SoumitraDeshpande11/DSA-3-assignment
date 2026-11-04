#include <iostream>
#include <vector>

using namespace std;

class NumArray {
public:
    vector<int> tree;
    int n;

    NumArray(vector<int>& nums) {
        n = nums.size();
        tree.resize(2 * n, 0);

        // Insert leaf nodes into the second half of the tree
        for (int i = 0; i < n; i++) {
            tree[n + i] = nums[i];
        }

        // Build parents by summing child nodes bottom-up
        for (int i = n - 1; i > 0; i--) {
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
    }

    void update(int index, int val) {
        index += n;
        tree[index] = val;

        // Propagate updates up to the root
        while (index > 1) {
            index /= 2;
            tree[index] = tree[2 * index] + tree[2 * index + 1];
        }
    }

    int sumRange(int left, int right) {
        left += n;
        right += n;

        int sum = 0;

        while (left <= right) {
            // If left is a right child, include it and shift to next right subtree
            if (left % 2 == 1) {
                sum += tree[left];
                left++;
            }

            // If right is a left child, include it and shift to next left subtree
            if (right % 2 == 0) {
                sum += tree[right];
                right--;
            }

            left /= 2;
            right /= 2;
        }

        return sum;
    }
};

int main() {
    vector<int> nums = {1, 3, 5};
    NumArray numArray(nums);

    cout << "Initial array: [1, 3, 5]\n\n";

    // Query sum of range [0, 2] -> 1 + 3 + 5 = 9
    cout << "sumRange(0, 2): " << numArray.sumRange(0, 2) << " (Expected: 9)\n";

    // Update index 1 to value 2 -> array becomes [1, 2, 5]
    numArray.update(1, 2);
    cout << "update(1, 2) -> array is now [1, 2, 5]\n";

    // Query sum of range [0, 2] -> 1 + 2 + 5 = 8
    cout << "sumRange(0, 2): " << numArray.sumRange(0, 2) << " (Expected: 8)\n";

    // Query sum of single element at index 1 -> 2
    cout << "sumRange(1, 1): " << numArray.sumRange(1, 1) << " (Expected: 2)\n";

    return 0;
}
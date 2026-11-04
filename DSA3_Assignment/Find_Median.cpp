#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

class MedianFinder {
public:
    priority_queue<int> maxHeap;                             // Smaller half
    priority_queue<int, vector<int>, greater<int>> minHeap;  // Larger half

    MedianFinder() {
    }

    void addNum(int num) {
        maxHeap.push(num);

        // Move largest element of maxHeap to minHeap
        minHeap.push(maxHeap.top());
        maxHeap.pop();

        // Maintain maxHeap size >= minHeap size (maxHeap can hold at most 1 more element)
        if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    double findMedian() {
        if (maxHeap.size() > minHeap.size()) {
            return maxHeap.top();
        }

        return (maxHeap.top() + minHeap.top()) / 2.0;
    }
};

int main() {
    MedianFinder medianFinder;

    cout << fixed << setprecision(1);

    cout << "Adding 1:\n";
    medianFinder.addNum(1);
    cout << "Current Median: " << medianFinder.findMedian() << "\n\n"; // 1.0

    cout << "Adding 2:\n";
    medianFinder.addNum(2);
    cout << "Current Median: " << medianFinder.findMedian() << "\n\n"; // (1 + 2) / 2 = 1.5

    cout << "Adding 3:\n";
    medianFinder.addNum(3);
    cout << "Current Median: " << medianFinder.findMedian() << "\n\n"; // 2.0

    cout << "Adding 5:\n";
    medianFinder.addNum(5);
    cout << "Current Median: " << medianFinder.findMedian() << "\n\n"; // (2 + 3) / 2 = 2.5

    cout << "Adding 4:\n";
    medianFinder.addNum(4);
    cout << "Current Median: " << medianFinder.findMedian() << "\n";   // 3.0

    return 0;
}
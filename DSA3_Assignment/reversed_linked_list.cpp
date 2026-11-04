#include <iostream>
#include <vector>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while (curr) {
            ListNode* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }
        return prev;
    }
};

// Helper: build a linked list from an array/vector
ListNode* createList(const vector<int>& values) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    for (int val : values) {
        tail->next = new ListNode(val);
        tail = tail->next;
    }
    return dummy.next;
}

// Helper: print the linked list
void printList(ListNode* head) {
    ListNode* curr = head;
    while (curr) {
        cout << curr->val;
        if (curr->next) cout << " -> ";
        curr = curr->next;
    }
    cout << " -> nullptr\n";
}

// Helper: free allocated memory
void freeList(ListNode* head) {
    while (head) {
        ListNode* next = head->next;
        delete head;
        head = next;
    }
}

int main() {
    Solution solver;

    // Test Case 1: 1 -> 2 -> 3 -> 4 -> 5
    ListNode* head1 = createList({1, 2, 3, 4, 5});
    cout << "Original 1: ";
    printList(head1);
    head1 = solver.reverseList(head1);
    cout << "Reversed 1: ";
    printList(head1);
    freeList(head1);

    cout << "\n";

    // Test Case 2: 1 -> 2
    ListNode* head2 = createList({1, 2});
    cout << "Original 2: ";
    printList(head2);
    head2 = solver.reverseList(head2);
    cout << "Reversed 2: ";
    printList(head2);
    freeList(head2);

    cout << "\n";

    // Test Case 3: Empty list
    ListNode* head3 = nullptr;
    cout << "Original 3: ";
    printList(head3);
    head3 = solver.reverseList(head3);
    cout << "Reversed 3: ";
    printList(head3);
    freeList(head3);

    return 0;
}
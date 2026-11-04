#include <iostream>
#include <unordered_map>

using namespace std;

class LRUCache {
public:
    class Node {
    public:
        Node* next;
        Node* prev;
        int key, val;

        Node(int k, int v) {
            key = k;
            val = v;
            prev = next = nullptr;
        }
    };

    Node* head;
    Node* tail;
    unordered_map<int, Node*> m;
    int limit;

    LRUCache(int capacity) {
        limit = capacity;
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    ~LRUCache() {
        Node* curr = head;
        while (curr != nullptr) {
            Node* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
    }

    void addNode(Node* newNode) {
        Node* temp = head->next;
        head->next = newNode;
        newNode->prev = head;
        newNode->next = temp;
        temp->prev = newNode;
    }

    void delNode(Node* delnode) {
        Node* prevv = delnode->prev;
        Node* nextt = delnode->next;
        prevv->next = nextt;
        nextt->prev = prevv;
    }

    int get(int key) {
        if (m.find(key) == m.end()) {
            return -1;
        }

        Node* resNode = m[key];
        int res = resNode->val;

        // Move node to front (most recently used)
        delNode(resNode);
        addNode(resNode);

        return res;
    }

    void put(int key, int value) {
        if (m.find(key) != m.end()) {
            Node* oldNode = m[key];
            m.erase(key);
            delNode(oldNode);
            delete oldNode; // Prevent memory leak on replacement
        }

        if (m.size() == static_cast<size_t>(limit)) {
            // LRU eviction (node right before dummy tail)
            Node* lruNode = tail->prev;
            m.erase(lruNode->key);
            delNode(lruNode);
            delete lruNode; // Free evicted node
        }

        Node* newNode = new Node(key, value);
        addNode(newNode);
        m[key] = newNode;
    }
};

int main() {
    LRUCache lRUCache(2);

    cout << boolalpha;

    lRUCache.put(1, 1); // cache is {1=1}
    cout << "put(1, 1)\n";

    lRUCache.put(2, 2); // cache is {1=1, 2=2}
    cout << "put(2, 2)\n";

    cout << "get(1): " << lRUCache.get(1) << "\n"; // returns 1, makes 1 MRU

    lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    cout << "put(3, 3) (evicts key 2)\n";

    cout << "get(2): " << lRUCache.get(2) << "\n"; // returns -1 (not found)

    lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    cout << "put(4, 4) (evicts key 1)\n";

    cout << "get(1): " << lRUCache.get(1) << "\n"; // returns -1 (not found)
    cout << "get(3): " << lRUCache.get(3) << "\n"; // returns 3
    cout << "get(4): " << lRUCache.get(4) << "\n"; // returns 4

    return 0;
}
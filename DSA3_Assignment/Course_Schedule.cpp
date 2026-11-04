#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool cycleDFS(int src, vector<bool>& vis, vector<bool>& recPath, vector<vector<int>>& edges) {
        vis[src] = true;
        recPath[src] = true;

        for (size_t i = 0; i < edges.size(); i++) {
            int v = edges[i][0];
            int u = edges[i][1];

            // Finding directed edges originating from src: u -> v
            if (u == src) {
                if (!vis[v]) {
                    if (cycleDFS(v, vis, recPath, edges)) {
                        return true;
                    }
                } else if (recPath[v]) {
                    return true;
                }
            }
        }

        recPath[src] = false;
        return false;
    }

    bool canFinish(int n, vector<vector<int>>& edges) {
        vector<bool> vis(n, false);
        vector<bool> recPath(n, false);

        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                if (cycleDFS(i, vis, recPath, edges)) {
                    return false; // Cycle detected: cannot complete all courses
                }
            }
        }

        return true;
    }
};

int main() {
    Solution solver;
    cout << boolalpha;

    // Test Case 1: 2 courses, prerequisite [1, 0] (0 -> 1). No cycle.
    int n1 = 2;
    vector<vector<int>> edges1 = {{1, 0}};
    cout << "Test 1 (2 courses, [[1, 0]]): " 
         << solver.canFinish(n1, edges1) << " (Expected: true)\n";

    // Test Case 2: 2 courses, prerequisites [1, 0] and [0, 1] (0 <-> 1). Cycle present.
    int n2 = 2;
    vector<vector<int>> edges2 = {{1, 0}, {0, 1}};
    cout << "Test 2 (2 courses, [[1, 0], [0, 1]]): " 
         << solver.canFinish(n2, edges2) << " (Expected: false)\n";

    // Test Case 3: 4 courses with cycle (1 -> 2 -> 3 -> 1)
    // Edges format: [course, prerequisite]
    int n3 = 4;
    vector<vector<int>> edges3 = {{1, 0}, {2, 1}, {3, 2}, {1, 3}};
    cout << "Test 3 (4 courses with cycle): " 
         << solver.canFinish(n3, edges3) << " (Expected: false)\n";

    // Test Case 4: Independent courses with no prerequisites
    int n4 = 3;
    vector<vector<int>> edges4 = {};
    cout << "Test 4 (3 independent courses): " 
         << solver.canFinish(n4, edges4) << " (Expected: true)\n";

    return 0;
}
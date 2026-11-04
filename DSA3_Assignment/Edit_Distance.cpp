#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        // Base cases: converting word1 prefixes to empty string (all deletions)
        for (int i = 0; i <= m; i++)
            dp[i][0] = i;

        // Base cases: converting empty string to word2 prefixes (all insertions)
        for (int j = 0; j <= n; j++)
            dp[0][j] = j;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + min({
                        dp[i - 1][j],      // Delete
                        dp[i][j - 1],      // Insert
                        dp[i - 1][j - 1]   // Replace
                    });
                }
            }
        }

        return dp[m][n];
    }
};

int main() {
    Solution solver;

    // Test Case 1: "horse" -> "ros"
    // horse -> rorse (replace 'h' with 'r')
    // rorse -> rose (remove 'r')
    // rose -> ros (remove 'e')
    string w1_a = "horse", w2_a = "ros";
    cout << "Input: word1 = \"" << w1_a << "\", word2 = \"" << w2_a << "\"\n";
    cout << "Min Distance: " << solver.minDistance(w1_a, w2_a) << " (Expected: 3)\n\n";

    // Test Case 2: "intention" -> "execution"
    string w1_b = "intention", w2_b = "execution";
    cout << "Input: word1 = \"" << w1_b << "\", word2 = \"" << w2_b << "\"\n";
    cout << "Min Distance: " << solver.minDistance(w1_b, w2_b) << " (Expected: 5)\n\n";

    // Test Case 3: Empty string to non-empty
    string w1_c = "", w2_c = "a";
    cout << "Input: word1 = \"" << w1_c << "\", word2 = \"" << w2_c << "\"\n";
    cout << "Min Distance: " << solver.minDistance(w1_c, w2_c) << " (Expected: 1)\n";

    return 0;
}
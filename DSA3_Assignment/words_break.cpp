#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        vector<bool> dp(n + 1, false);

        // Base case: an empty string can always be segmented
        dp[0] = true;

        for (int i = 1; i <= n; i++) {
            for (const string &word : wordDict) {
                int len = word.size();

                // If the word fits, the preceding substring is valid, and the slice matches
                if (i >= len && dp[i - len] && s.compare(i - len, len, word) == 0) {
                    dp[i] = true;
                    break; // Move to the next index once dp[i] is proven true
                }
            }
        }
        return dp[n];
    }
};

int main() {
    Solution solver;

    // Test Case 1
    string s1 = "leetcode";
    vector<string> dict1 = {"leet", "code"};
    cout << "Test 1 (\"" << s1 << "\"): " 
         << (solver.wordBreak(s1, dict1) ? "true" : "false") << "\n";

    // Test Case 2
    string s2 = "applepenapple";
    vector<string> dict2 = {"apple", "pen"};
    cout << "Test 2 (\"" << s2 << "\"): " 
         << (solver.wordBreak(s2, dict2) ? "true" : "false") << "\n";

    // Test Case 3
    string s3 = "catsandog";
    vector<string> dict3 = {"cats", "dog", "sand", "and", "cat"};
    cout << "Test 3 (\"" << s3 << "\"): " 
         << (solver.wordBreak(s3, dict3) ? "true" : "false") << "\n";

    return 0;
}
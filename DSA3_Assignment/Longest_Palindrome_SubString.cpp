#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        if (n <= 1) return s;

        int start = 0, maxLen = 1;

        for (int i = 0; i < n; i++) {
            // Odd length palindrome (center is s[i])
            int l = i, r = i;
            while (l >= 0 && r < n && s[l] == s[r]) {
                if (r - l + 1 > maxLen) {
                    start = l;
                    maxLen = r - l + 1;
                }
                l--;
                r++;
            }

            // Even length palindrome (center is between s[i] and s[i + 1])
            l = i;
            r = i + 1;
            while (l >= 0 && r < n && s[l] == s[r]) {
                if (r - l + 1 > maxLen) {
                    start = l;
                    maxLen = r - l + 1;
                }
                l--;
                r++;
            }
        }

        return s.substr(start, maxLen);
    }
};

int main() {
    Solution solver;

    // Test Case 1: Odd length palindrome
    string s1 = "babad";
    cout << "Input: \"" << s1 << "\"\n";
    cout << "Output: \"" << solver.longestPalindrome(s1) << "\" (Valid: \"bab\" or \"aba\")\n\n";

    // Test Case 2: Even length palindrome
    string s2 = "cbbd";
    cout << "Input: \"" << s2 << "\"\n";
    cout << "Output: \"" << solver.longestPalindrome(s2) << "\" (Expected: \"bb\")\n\n";

    // Test Case 3: Entire string is a palindrome
    string s3 = "racecar";
    cout << "Input: \"" << s3 << "\"\n";
    cout << "Output: \"" << solver.longestPalindrome(s3) << "\" (Expected: \"racecar\")\n\n";

    // Test Case 4: Single character string
    string s4 = "a";
    cout << "Input: \"" << s4 << "\"\n";
    cout << "Output: \"" << solver.longestPalindrome(s4) << "\" (Expected: \"a\")\n";

    return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Suggestion {
    string word;
    int freq;
    int dist;
};

bool byFreq(Suggestion a, Suggestion b) {
    return a.freq > b.freq;
}

bool byDistThenFreq(Suggestion a, Suggestion b) {
    if (a.dist != b.dist) return a.dist < b.dist;
    return a.freq > b.freq;
}

struct Node {
    Node* child[26] = {};
    bool isWord = false;
    int freq = 0;
};

class Trie {
public:
    Node* root = new Node();
    int steps = 0;

    void insert(string word, int freq) {
        Node* cur = root;
        for (char c : word) {
            int i = c - 'a';
            if (cur->child[i] == nullptr) cur->child[i] = new Node();
            cur = cur->child[i];
        }
        cur->isWord = true;
        cur->freq = freq;
    }

    bool contains(string word) {
        Node* cur = root;
        for (char c : word) {
            cur = cur->child[c - 'a'];
            if (cur == nullptr) return false;
        }
        return cur->isWord;
    }

    void collect(Node* node, string word, vector<Suggestion>& out) {
        steps++;
        if (node->isWord) out.push_back({word, node->freq, 0});
        for (int i = 0; i < 26; i++)
            if (node->child[i] != nullptr) collect(node->child[i], word + char('a' + i), out);
    }

    vector<Suggestion> autocomplete(string prefix) {
        steps = 0;
        vector<Suggestion> out;
        Node* cur = root;
        for (char c : prefix) {
            steps++;
            cur = cur->child[c - 'a'];
            if (cur == nullptr) return out;
        }
        collect(cur, prefix, out);
        sort(out.begin(), out.end(), byFreq);
        return out;
    }

    void walk(Node* node, string word, string& target, vector<int>& prevRow, int maxDist, vector<Suggestion>& out) {
        steps++;
        int n = target.size();
        char letter = word.back();
        vector<int> row(n + 1);
        row[0] = prevRow[0] + 1;
        for (int j = 1; j <= n; j++) {
            if (target[j - 1] == letter) row[j] = prevRow[j - 1];
            else row[j] = 1 + min({prevRow[j], row[j - 1], prevRow[j - 1]});
        }

        if (node->isWord && row[n] <= maxDist) out.push_back({word, node->freq, row[n]});
        if (*min_element(row.begin(), row.end()) > maxDist) return;

        for (int i = 0; i < 26; i++)
            if (node->child[i] != nullptr) walk(node->child[i], word + char('a' + i), target, row, maxDist, out);
    }

    vector<Suggestion> correct(string target, int maxDist) {
        steps = 0;
        vector<Suggestion> out;
        vector<int> firstRow(target.size() + 1);
        for (int j = 0; j <= target.size(); j++) firstRow[j] = j;
        for (int i = 0; i < 26; i++)
            if (root->child[i] != nullptr) walk(root->child[i], string(1, 'a' + i), target, firstRow, maxDist, out);
        sort(out.begin(), out.end(), byDistThenFreq);
        return out;
    }
};

class FullScan {
public:
    vector<Suggestion> words;
    int steps = 0;

    void insert(string word, int freq) {
        words.push_back({word, freq, 0});
    }

    int editDistance(string a, string b) {
        int m = a.size(), n = b.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int i = 0; i <= m; i++) dp[i][0] = i;
        for (int j = 0; j <= n; j++) dp[0][j] = j;
        for (int i = 1; i <= m; i++) {
            steps++;
            for (int j = 1; j <= n; j++) {
                if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1];
                else dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
        return dp[m][n];
    }

    vector<Suggestion> autocomplete(string prefix) {
        steps = 0;
        vector<Suggestion> out;
        for (Suggestion s : words) {
            steps++;
            if (s.word.compare(0, prefix.size(), prefix) == 0) out.push_back(s);
        }
        sort(out.begin(), out.end(), byFreq);
        return out;
    }

    vector<Suggestion> correct(string target, int maxDist) {
        steps = 0;
        vector<Suggestion> out;
        for (Suggestion s : words) {
            int d = editDistance(s.word, target);
            if (d <= maxDist) out.push_back({s.word, s.freq, d});
        }
        sort(out.begin(), out.end(), byDistThenFreq);
        return out;
    }
};

void show(string title, vector<Suggestion> list) {
    cout << title;
    if (list.empty()) cout << " none";
    for (int i = 0; i < list.size() && i < 5; i++) {
        cout << "  " << list[i].word;
        if (list[i].dist > 0) cout << " (" << list[i].dist << ")";
    }
    cout << "\n";
}

int main() {
    Trie trie;
    FullScan scan;

    ifstream file("words.txt");
    string word;
    int freq;
    while (file >> word >> freq) {
        trie.insert(word, freq);
        scan.insert(word, freq);
    }

    if (scan.words.empty()) {
        cout << "Could not read words.txt\n";
        return 1;
    }
    cout << "Loaded " << scan.words.size() << " words\n";

    int maxDist = 2;
    string input;
    while (true) {
        cout << "\nType a word (or exit): ";
        if (!(cin >> input) || input == "exit") break;

        string text = "";
        for (char c : input)
            if (isalpha(c)) text += tolower(c);
        if (text.empty()) continue;

        vector<Suggestion> completions = trie.autocomplete(text);
        int trieAutoSteps = trie.steps;
        vector<Suggestion> fixes = trie.correct(text, maxDist);
        int trieFixSteps = trie.steps;

        scan.autocomplete(text);
        int scanAutoSteps = scan.steps;
        scan.correct(text, maxDist);
        int scanFixSteps = scan.steps;

        cout << "\n";
        show("Autocomplete :", completions);
        if (trie.contains(text)) cout << "Spelling     :  correct\n";
        else show("Did you mean :", fixes);

        cout << "\n" << left << setw(15) << "Steps" << setw(8) << "Trie" << "Full scan\n";
        cout << setw(15) << "Autocomplete" << setw(8) << trieAutoSteps << scanAutoSteps << "\n";
        cout << setw(15) << "Typo check" << setw(8) << trieFixSteps << scanFixSteps << "\n";
    }

    return 0;
}

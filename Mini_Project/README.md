# Smart Autocomplete and Typo Correction

Type a word and the program shows:

- **Autocomplete**: words that start with what you typed, most common first (trie prefix search)
- **Did you mean**: closest words within 2 edits, ranked by edit distance and then frequency (edit-distance DP while walking the trie)
- **Steps**: how much work the trie did compared with scanning the whole dictionary

## Run

```
g++ -std=c++17 autocomplete.cpp -o autocomplete
./autocomplete
```

Run it from this folder so it can find `words.txt`.

## Example

```
Type a word (or exit): helo

Autocomplete : none
Did you mean :  help (1)  hello (1)  held (1)  hell (1)  he (2)

Steps          Trie    Full scan
Autocomplete   4       541
Typo check     738     2522
```

## How it works

- `words.txt` has one word per line with its frequency.
- **Trie**: each node has 26 children. Autocomplete walks down the prefix, then collects every word under that node.
- **Typo correction**: while walking the trie, each node adds one row of the edit-distance table. Words that share a prefix share those rows. If every value in a row is above 2, that whole branch is skipped.
- **Full scan**: checks every word and builds a full edit-distance table for each one. It gives the same answers but does more work.

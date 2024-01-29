#include <iostream>
#include <vector>
using namespace std;

void write_solution(const vector<string>& words, vector<int>& subset_word, int subsets) {
    for (int i = 0; i < subsets; ++i) {
        bool is_first = true;

        cout << "subset " << i+1 << ": {";
        for (int j = 0; j < words.size(); ++j) {
            if (subset_word[j] == i) {
                if (not is_first) cout << ',';
                cout << words[j];
                is_first = false;
            }
        }
        cout << '}' << endl;
    }
    cout << endl;
}

void exhaustive_search(int i, const vector<string>& words, vector<int>& subset_word, int subsets) {
    if (i == words.size()) {
        write_solution(words, subset_word, subsets);
        return;
    }
    for (int j = 0; j < subsets; ++j) {
        subset_word[i] = j;
        exhaustive_search(i+1, words, subset_word, subsets);
    }
    
}

int main() {
    int n; cin >> n;
    vector<string> words(n);
    for (int i = 0; i < n; ++i) cin >> words[i];
    int subsets; cin >> subsets;
    vector<int> subset_word(n);
    exhaustive_search(0, words, subset_word, subsets);
}

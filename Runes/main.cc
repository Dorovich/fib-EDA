#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool esvocal (const char c) {
    return c == 'a' or c == 'e' or c == 'i' or c == 'o' or c == 'u';
}

void combi (const vector<char>& letras, vector<char>& palabra, int i, const bool antvoc) {
    if (i == palabra.size()) {
        for (int j = 0; j < i; ++j) cout << palabra[j];
        cout << endl;
        return;
    }
    for (int j = 0; j < letras.size(); ++j) {
        if (not esvocal(letras[j])) {
            palabra[i] = letras[j];
            combi(letras, palabra, i+1, false);
        }
        else {
            if (not antvoc) {
                palabra[i] = letras[j];
                combi(letras, palabra, i+1, true);
            }
        }
    }
}

int main () {
    int n, m;
    vector<char> palabra;
    vector<char> letras;
    
    while (cin >> n >> m) {
        palabra = vector<char> (n);
        letras = vector<char> (m);
        for (int i = 0; i < m; ++i) cin >> letras[i];
        sort(letras.begin(), letras.end(), [](char a, char b) {
            return a < b;
        });
        combi(letras, palabra, 0, false);
        cout << "----------" << endl;
    }
    
    return 0;
}

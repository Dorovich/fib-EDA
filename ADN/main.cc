#include <iostream>
#include <vector>
using namespace std;

void send (vector<char>& combi) {
    for (int i = 0; i < combi.size(); ++i) cout << combi[i];
    cout << endl;
}

void combinate (const vector<char>& letras, vector<char>& combi, int n, int act) {
    if (act == n) {
        send(combi);
        return;
    }
    for (int i = 0; i < 4; ++i) {
        combi[act] = letras[i];
        combinate(letras, combi, n, act+1);
    }
}

int main () {
    const vector<char> letras = { 'A', 'C', 'G', 'T' };
    int n;
    cin >> n;
    vector<char> combi (n);
    combinate(letras, combi, n, 0);
    return 0;
}

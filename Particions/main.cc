#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct par {
    string palabra;
    int conj;
};

void send (vector<par>& pares, int p) {
    for (int j = 0; j < p; ++j) {
        bool primero = false;
        cout << "subconjunt " << j+1 << ": {";
        for (int k = 0; k < pares.size(); ++k) {
            if (pares[k].conj == j) {
                if (primero) cout << ',';
                cout << pares[k].palabra;
                primero = true;
            }
        }
        cout << "}\n";
    }
    cout << endl;
}

void combi (vector<par>& pares, int i, int p) {
    if (i == pares.size()) {
        send(pares, p);
        return;
    }
    for (int j = 0; j < p; ++j) {
        pares[i].conj = j;
        combi(pares, i+1, p);
    }
}

int main () {
    int n, p;
    cin >> n;
    vector<par> pares (n);
    for (int i = 0; i < n; ++i) cin >> pares[i].palabra;
    cin >> p;
    combi(pares, 0, p);
    return 0;
}

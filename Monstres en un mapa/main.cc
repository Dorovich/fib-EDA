#include <iostream>
#include <vector>
using namespace std;

typedef vector<char> chvec;
typedef vector<chvec> chmat;
struct position { int row, col; };

bool checkpath (const chmat& mat) {

}

int main () {
    int nrows, ncols;
    cin >> nrows >> ncols;
    chmat mat (nrows, chvec (ncols));
    position start;
    for (int i = 0; i < nrows; ++i) 
        for (int j = 0; j < ncols; ++j) {
            cin >> mat[i][j];
            if (mat[i][j] == 'I') start = { i, j };
        }
    if (checkpath(mat)) cout << "SI" << endl;
    else cout << "NO" << endl;
    return 0;
}

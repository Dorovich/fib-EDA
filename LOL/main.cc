#include <iostream>
#include <vector>
using namespace std;

typedef vector<char> chvec;
typedef vector<chvec> chmat;
struct Pos { int row, col; };

bool invalidpos (const chmat& mat, const Pos& p) {/*{{{*/
    int nrows = mat.size();
    int ncols = mat[0].size();
    if (p.row >= nrows or p.row < 0) return false;
    if (p.col >= ncols or p.col < 0) return false;
    return true;
}/*}}}*/

Pos nextpos (const chmat& mat, const Pos& p) {/*{{{*/
    return (invalidpos(mat, {p.row, p.col+1}) ?
            Pos {p.row+1, 0} : Pos {p.row, p.col+1});
}/*}}}*/

int count_dirs (const chmat& mat, const Pos& p, chmat& checked) {/*{{{*/
    if (mat[p.row][p.col] == 'O') return 0;
    int count = 0;
    
    // Left
    if (not invalidpos(mat, {p.row, p.col-1}) and mat[p.row][p.col-1] == 'O'
    and not invalidpos(mat, {p.row, p.col-2}) and mat[p.row][p.col-2] == 'L'
    and checked[p.row][p.col-2] == 'n') count++;
    // Right
    if (not invalidpos(mat, {p.row, p.col+1}) and mat[p.row][p.col+1] == 'O'
    and not invalidpos(mat, {p.row, p.col+2}) and mat[p.row][p.col+2] == 'L'
    and checked[p.row][p.col+2] == 'n') count++;
    // Up
    if (not invalidpos(mat, {p.row-1, p.col}) and mat[p.row-1][p.col] == 'O'
    and not invalidpos(mat, {p.row-2, p.col}) and mat[p.row-2][p.col] == 'L'
    and checked[p.row-2][p.col] == 'n') count++;
    // Down
    if (not invalidpos(mat, {p.row+1, p.col}) and mat[p.row+1][p.col] == 'O'
    and not invalidpos(mat, {p.row+2, p.col}) and mat[p.row+2][p.col] == 'L'
    and checked[p.row+2][p.col] == 'n') count++;
    // UL
    if (not invalidpos(mat, {p.row-1, p.col-1}) and mat[p.row-1][p.col-1] == 'O'
    and not invalidpos(mat, {p.row-2, p.col-2}) and mat[p.row-2][p.col-2] == 'L'
    and checked[p.row-2][p.col-2] == 'n') count++;
    // UR
    if (not invalidpos(mat, {p.row-1, p.col+1}) and mat[p.row-1][p.col+1] == 'O'
    and not invalidpos(mat, {p.row-2, p.col+2}) and mat[p.row-2][p.col+2] == 'L'
    and checked[p.row-2][p.col+2] == 'n') count++;
    // DL
    if (not invalidpos(mat, {p.row+1, p.col-1}) and mat[p.row+1][p.col-1] == 'O'
    and not invalidpos(mat, {p.row+2, p.col-2}) and mat[p.row+2][p.col-2] == 'L'
    and checked[p.row+2][p.col-2] == 'n') count++;
    // DR
    if (not invalidpos(mat, {p.row+1, p.col+1}) and mat[p.row+1][p.col+1] == 'O'
    and not invalidpos(mat, {p.row+2, p.col+2}) and mat[p.row+2][p.col+2] == 'L'
    and checked[p.row+2][p.col+2] == 'n') count++;

    checked[p.row][p.col] = 'y';
    return count;
}/*}}}*/

int countlols (const chmat& mat, const Pos& p, chmat& checked) {
    if (invalidpos(mat, p)) return 0;
    int count = 0;
    count += count_dirs(mat, p, checked);
    count += countlols(mat, nextpos(mat, p), checked);
    return count;
}

int fill_and_check (chmat& mat, const Pos& p, chmat& checked) {
    if (invalidpos(mat, p)) {
        for (int i = 0; i < checked.size(); ++i) {
            for (int j = 0; j < checked[0].size(); ++j) checked[i][j] = 'n';
        }
        return countlols(mat, {0,0}, checked);
    }

    Pos np = nextpos(mat, p);
    
    mat[p.row][p.col] = 'L';
    int lols = fill_and_check(mat, np, checked);

    mat[p.row][p.col] = 'O';
    int auxc = fill_and_check(mat, np, checked);
    if (auxc > lols) lols = auxc;
    
    return lols;
}

int main () {/*{{{*/
    int n, m; 
    while (cin >> n >> m) {
        chmat mat (n, chvec (m, 'x'));
        chmat checked (n, chvec (m, 'n'));
        cout << fill_and_check(mat, {0,0}, checked) << endl;
    }
    return 0;
}/*}}}*/

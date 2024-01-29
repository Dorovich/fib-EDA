#include <iostream>
#include <vector>
using namespace std;

typedef vector<char> chvec;
typedef vector<chvec> chmat;
typedef vector<bool> blvec;
struct pos { int row, col; };

void read_sudoku (chmat& sudoku) {/*{{{*/
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j)
            cin >> sudoku[i][j];
    }
}/*}}}*/

void send_solution (const chmat& solution) {/*{{{*/
    cout << endl;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (j != 0) cout << ' ';
            cout << solution[i][j];
        }
        cout << endl;
    }
}/*}}}*/

bool check_rows (const chmat& solution) {/*{{{*/
    blvec appears (9, false);
    for (int i = 0; i < 9; ++i) {
        appears = blvec (9, false);
        for (int j = 0; j < 9; ++j) {
            if (appears[solution[i][j]-'1']) return false;
            appears[solution[i][j]-'1'] = true;
        }
    }
    return true;
}/*}}}*/

bool check_cols (const chmat& solution) {/*{{{*/
    blvec appears (9, false);
    for (int i = 0; i < 9; ++i) {
        appears = blvec (9, false);
        for (int j = 0; j < 9; ++j) {
            if (appears[solution[j][i]-'1']) return false;
            appears[solution[j][i]-'1'] = true;
        }
    }
    return true;
}/*}}}*/

bool check_blocks (const chmat& solution) {/*{{{*/
    blvec appears (9, false);
    for (int rowb = 0; rowb < 3; ++rowb)
        for (int colb = 0; colb < 3; ++colb) {
            appears = blvec (9, false);
            
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) {
                    if (appears[solution[rowb*3+i][colb*3+j]-'1']) return false;
                    appears[solution[rowb*3+i][colb*3+j]-'1'] = true;
                }
            
            for (int i = 0; i < 9; ++i)
                if (!appears[i]) return false;
        }
    return true;
}/*}}}*/

pos nextpos (const pos& p) {/*{{{*/
    if (p.col+1 == 9) return pos {p.row+1, 0};
    return pos {p.row, p.col+1};
}/*}}}*/

bool solve_sudoku (const chmat& sudoku, chmat& solution, const pos& p) {/*{{{*/
    if (p.row == 9) {
        send_solution(solution);
        return true;
    }
    
    bool solved = false;
    if (sudoku[p.row][p.col] != '.') {
        solution[p.row][p.col] = sudoku[p.row][p.col];
        solved = solve_sudoku(sudoku, solution, nextpos(p));
    }
    else {
        blvec can_use (9, true);
        char content;
        
        // check row and column for numbers that can be used
        for (int i = 0; i < 9; ++i) {
            content = solution[p.row][i];
            if (content != '.') can_use[content-'1'] = false;
            content = solution[i][p.col];
            if (content != '.') can_use[content-'1'] = false;
        }

        // check block for numbers that can be used
        int rowb = p.row/3, colb = p.col/3;
        for (int i = 0; i < 3; ++i) 
            for (int j = 0; j < 3; ++j) {
                content = solution[rowb*3+i][colb*3+j];
                if (content != '.') can_use[content-'1'] = false;
            }

        // fill with possible solutions
        for (int i = 0; i < 9; ++i) {
            if (can_use[i]) {
                solution[p.row][p.col] = (char)(i+'1');
                solved = solve_sudoku(sudoku, solution, nextpos(p));
                if (solved) return true;
                solution[p.row][p.col] = '.';
            }
        }
    }
    return solved;
}/*}}}*/

int main () {/*{{{*/
    chmat sudoku (9, chvec (9));
    int cases;
    cin >> cases;
    cout << cases << endl;
    for (int c = 0; c < cases; c++) {
        read_sudoku(sudoku);
        chmat solution = sudoku;
        solve_sudoku(sudoku, solution, {0,0});
    }
}/*}}}*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
using namespace std;

struct element {
    int index;
    int indeg = 0;
    char (*func)(char,char);
    vector<int> param_indexes;
    list<int> next_indexes;
};

char and_func (char a, char b) { return (a == b) ? 'T' : 'F'; }
char or_func (char a, char b) { return (a == 'T' or b == 'T') ? 'T' : 'F'; }
char not_func (char a, char b) { return (a == 'T') ? 'F' : 'T'; }

void add_var (map<string,element>& elements, const string& s, const string& p1, const string& p2, char (*func)(char,char), int& total_vars) {/*{{{*/
    bool is_p1 = (p1 != "");
    bool is_p2 = (p2 != "");
    int idx_p1 = (is_p1 ? elements[p1].index : -1);
    int idx_p2 = (is_p2 ? elements[p2].index : -1);
    
    int idx_s = elements[s].index;
    if (is_p1) elements[p1].next_indexes.push_back(idx_s);
    if (is_p2) elements[p2].next_indexes.push_back(idx_s);
    
    element new_var;
    new_var.index = total_vars-1;
    total_vars++;
    new_var.indeg = is_p1+is_p2;
    new_var.func = func;
    new_var.param_indexes = { idx_p1, idx_p2 };
    elements[s] = new_var;
}/*}}}*/

void topol_sort (map<string,element>& elements, const vector<string>& vars, vector<char>& var_values, const int out_vars) {/*{{{*/
    int nvars = var_values.size();
    set<string> zeros;
    
    for (int i = 0; i < nvars; ++i)
        if (elements[vars[i]].indeg == 0) {
            elements[vars[i]].indeg = -1;
            for (auto it = elements[vars[i]].next_indexes.begin(); it != elements[vars[i]].next_indexes.end(); ++it) {
                string var_to_decrement = vars[*it];
                --elements[var_to_decrement].indeg;
                if (elements[var_to_decrement].indeg == 0) zeros.insert(var_to_decrement);
            }
        }

    while (not zeros.empty()) {
        string current_var = *zeros.begin();
        zeros.erase(*zeros.begin());

        // Calcular resultado
        int idx_p1 = elements[current_var].param_indexes[0];
        int idx_p2 = elements[current_var].param_indexes[1];
        char param1 = (idx_p1 >= 0) ? var_values[idx_p1] : 'N';
        char param2 = (idx_p2 >= 0) ? var_values[idx_p2] : 'N';
        char result = elements[current_var].func(param1, param2);
        var_values[elements[current_var].index] = result;

        // Decrementar los siguientes
        for (auto it = elements[current_var].next_indexes.begin(); it != elements[current_var].next_indexes.end(); ++it) {
            string var_to_decrement = vars[*it];
            --elements[var_to_decrement].indeg;
            if (elements[var_to_decrement].indeg == 0) zeros.insert(var_to_decrement);
        }
    }

    for (int i = 0; i < out_vars; ++i) {
        if (i != 0) cout << ' ';
        cout << var_values[i];
    }
    cout << endl;
}/*}}}*/

int main () {/*{{{*/
    int out_vars = 0, inp_vars = 0;
    int total_vars = 0;
    string s, param1, param2;
    
    vector<string> vars;
    map<string,element> elements;
    
    /* OUTPUT VARIABLES */
    while (cin >> s and s != "END") {/*{{{*/
        if (s == "OUTPUT") cin >> s;
        vars.push_back(s);
        add_var(elements, s, "", "", NULL, total_vars);
        out_vars++;
        cout << "read output var " << s << endl;
    }/*}}}*/

    /* INPUT VARIABLES */
    while (cin >> s and s != "END") {/*{{{*/
        if (s == "INPUT") cin >> s;
        vars.push_back(s);
        add_var(elements, s, "", "", NULL, total_vars);
        inp_vars++;
        cout << "read input var " << s << endl;
    }/*}}}*/

    /* PRECEDENCE FUNCTIONS */
    while (cin >> s and s != "END") {/*{{{*/
        if (s == "NOT") {
            cin >> s >> param1;
            
            if (elements.find(s) == elements.end()) vars.push_back(s);
            if (elements.find(param1) == elements.end()) vars.push_back(param1);
            
            add_var(elements, s, param1, "", not_func, total_vars);
            cout << "read var " << s << endl;
        }
        else if (s == "AND") {
            cin >> s >> param1 >> param2;
            
            if (elements.find(s) == elements.end()) vars.push_back(s);
            if (elements.find(param1) == elements.end()) vars.push_back(param1);
            if (elements.find(param2) == elements.end()) vars.push_back(param2);
            
            add_var(elements, s, param1, param2, and_func, total_vars);
            cout << "read var " << s << endl;
        }
        else if (s == "OR") {
            cin >> s >> param1 >> param2;
            
            if (elements.find(s) == elements.end()) vars.push_back(s);
            if (elements.find(param1) == elements.end()) vars.push_back(param1);
            if (elements.find(param2) == elements.end()) vars.push_back(param2);
            
            add_var(elements, s, param1, param2, or_func, total_vars);
            cout << "read var " << s << endl;
        }
    }/*}}}*/
    
    vector<char> var_values (total_vars, 'N');
    while (cin >> var_values[inp_vars-1]) {
        for (int i = inp_vars-1; i < inp_vars; ++i) cin >> var_values[i];
        topol_sort(elements, vars, var_values, out_vars);
    }
}/*}}}*/

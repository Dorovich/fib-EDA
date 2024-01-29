#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
using namespace std;

string topol_sort (vector<set<int>>& G, vector<int>& indeg, const vector<string>& task, string& solution) {
    int n = G.size();
    
    set<int> S;
    for (int u = 0; u < n; ++u) {
        if (indeg[u] == 0) S.insert(u);
    }

    while (not S.empty()) {
        int u = *S.begin(); 
        S.erase(S.begin());

        solution += task[u];

        for (auto it = G[u].begin(); it != G[u].end(); it++) {
            --indeg[*it];
            if (indeg[*it] == 0) S.insert(*it);
        }
    }

    for (int i = 0; i < (int)indeg.size(); ++i)
        if (indeg[i] != 0) return "NO VALID ORDERING";
    
    return solution;
}

int main ()
{
    int n, m, id_x, id_y;
    string aux;
    
    vector<string> task;
    map<string,int> index_catcher;
    vector<int> indeg;
    vector<set<int>> G;
    
    while (cin >> n) {
        task = vector<string> (n);
        indeg = vector<int> (n, 0);
        G = vector<set<int>> (n);
        
        for (int i = 0;  i < n; ++i) cin >> task[i];
        sort(task.begin(), task.end());
        
        for (int i = 0;  i < n; ++i)
            index_catcher[task[i]] = i;
        
        cin >> m;
        for (int i = 0;  i < m; ++i) {
            cin >> aux;
            id_x = index_catcher[aux];
            cin >> aux;
            id_y = index_catcher[aux];
            
            G[id_x].insert(id_y);
            indeg[id_y]++;
        }
        
        string solution = "";
        cout << topol_sort(G, indeg, task, solution) << endl;
    }
}


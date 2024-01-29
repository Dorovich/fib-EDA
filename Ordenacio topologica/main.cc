#include <iostream>
#include <vector>
#include <set>
using namespace std;

void topol_sort (vector<set<int>>& G, vector<int>& indeg)
{
    int n = G.size();
    
    set<int> S;
    for (int u = 0; u < n; ++u) {
        if (indeg[u] == 0) S.insert(u);
    }

    bool firstit = true;
    while (not S.empty()) {
        int u = *S.begin(); 
        S.erase(S.begin());

        if (firstit) firstit = false;
        else cout << ' ';
        cout << u;

        for (auto it = G[u].begin(); it != G[u].end(); it++) {
            --indeg[*it];
            if (indeg[*it] == 0) S.insert(*it);
        }
    }
    cout << endl;
}

int main ()
{
    int n, m;
    while (cin >> n >> m) {
        vector<set<int>> G(n);
        vector<int> indeg(n, 0);
        int x, y;
        for (int i = 0; i < m; ++i) {
            cin >> x >> y;
            G[x].insert(y);
            indeg[y]++;
        }
        topol_sort(G, indeg);
    }
}


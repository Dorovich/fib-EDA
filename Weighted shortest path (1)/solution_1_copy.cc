#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int,int> Pares;
typedef vector<Pares> VPares;
typedef vector<int> VInt;
typedef vector<VPares> Graf;
typedef priority_queue<Pares> CuaPares;

int n, m;
VInt D;
Graf G;
const int INF = 1e9;

void dijsktra (const int origin, const int desti) {
    D = VInt(n,INF);
    D[origin] = 0;
    
    CuaPares Q;
    Q.push(Pares(0,origin));

    while (not Q.empty()) {
        int vtx     = Q.top().second;
        int pes_vtx = -Q.top().first;
        Q.pop();
        
        if (pes_vtx == D[vtx]) {
            if (vtx == desti) return;
            for (int i = 0; i < (int)G[vtx].size(); ++i) {
                int adj     = G[vtx][i].first;
                int pes_adj = G[vtx][i].second;
                if (pes_vtx + pes_adj < D[adj]) {
                    D[adj] = pes_vtx + pes_adj;
                    Q.push(Pares(-D[adj],adj));
                }
            }
        }
    }
}

int main () {/*{{{*/
    while (cin >> n >> m) {
        G = Graf(n);
        for (int i = 0; i < m; ++i) {
            int v1, v2, w;
            cin >> v1 >> v2 >> w;
            G[v1].push_back(Pares(v2,w));
        }
        int origin, desti;
        cin >> origin >> desti;
        dijsktra(origin, desti);
        if (D[desti] < INF) cout << D[desti];
        else cout << "no path from " << origin << " to " << desti;
        cout << endl;
    }
    return 0;
}/*}}}*/

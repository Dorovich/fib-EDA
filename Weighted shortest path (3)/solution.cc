#include<iostream>
#include<vector>
#include<queue>
using namespace std;

typedef pair<int,int> Pars;
typedef vector<Pars> VPars;
typedef vector<VPars> Graf;
typedef vector<int> VInt;

// VARIABLES

int n;      // vertexs
int m;      // arestes
int origen, desti;
Graf G;
VInt D, steps;
queue<int> res;
const int INF = 1e9;

void dijkstra() {
    D = steps = VInt(n,INF);    // inicialitza el vector de distancies
    D[origen] = steps[origen] = 0;      // fica distancia 0 el origen
    priority_queue<Pars> Q;
    Q.push(Pars(0,origen));    // Pars: <dist,vertex>

    while(not Q.empty()) {
        int p = -Q.top().first;      // extreiem el pes
        int v = Q.top().second;     // extreiem el vertex
        Q.pop();

        if (p == D[v]) {
            if (v == desti) return;     // quan trobo el desti acaba
            for (int i = 0; i < (int)G[v].size(); ++i) {
                int adj = G[v][i].first;       // extreiem el vertex adjacent a v
                int pes = G[v][i].second;      // extreiem el pes de v a adj
                if (p + pes < D[adj]) {
                    steps[adj] = steps[v]+1;
                    D[adj] = p+pes;
                    Q.push(Pars(-D[adj],adj));
                }
                else if (p+pes == D[adj] and steps[v]+1 < steps[adj])
                    steps[adj] = steps[v] + 1;
            }
        }
    }
}

int main() {
    while (cin >> n >> m) {
        G = Graf(n);            // li fiques tamany n a un vector de vector de pairs.
        for (int i = 0; i < m; i++) {
            int a,b,c;
            cin >> a >> b >> c;
            G[a].push_back(Pars(b,c));
        }
        cin >> origen >> desti;
        dijkstra();

        if (D[desti] < INF) cout << "cost " << D[desti] << ", " << steps[desti] << " step(s)";
        else cout << "no path from " << origen << " to " << desti;
        cout << endl;
    }
}

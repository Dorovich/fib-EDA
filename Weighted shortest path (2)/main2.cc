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
Graf G;
VInt D, P;  // distancies, previs
const int INF = 1e9;

int prevchain (const int v, const int origen) {
    if (v == origen) return 0;
    return 1+prevchain(P[v], origen);
}

void dijkstra (const int origen, const int desti) {
    D = VInt(n,INF);    // inicialitza el vector de distancies
    P = VInt(n);
    D[origen] = 0;      // fica distancia 0 el origen
    priority_queue<Pars> Q;
    Q.push(Pars(0,origen));    // Pars: <vertex,dist>

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
                    D[adj] = p + pes;
                    P[adj] = v; // previ
                    Q.push(Pars(-D[adj],adj));
                }
            }
        }
    }
}

int main () {
    while (cin >> n >> m) {
        G = Graf(n);
        for (int i = 0; i < m; i++) {
            int a,b,c;
            cin >> a >> b >> c;
            G[a].push_back(Pars(b,c));
        }
        
        int origen, desti;
        cin >> origen >> desti;
        dijkstra(origen, desti);

        if (D[desti] < INF) cout << "cost " << D[desti] << ", " << prevchain(desti, origen) << " step(s)";
        else cout << "no path from " << origen << " to " << desti;
        cout << endl;
    }
}

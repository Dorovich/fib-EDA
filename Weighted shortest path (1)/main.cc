#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <limits>
using namespace std;

#define infinity numeric_limits<double>::infinity()
#define nil -1
typedef vector<vector<double>> wgraph;

int dijkstra (const wgraph& G, int from_idx, int to_idx) {/*{{{*/
    int n = (int)G.size();
    
    vector<bool> seen (n, false);
    vector<double> dist (n, infinity);
    queue<int> q;
    
    dist[from_idx] = 0;
    q.push(from_idx);
    
    while (not q.empty()) {
        int current_idx = q.front();
        q.pop();
        
        if (seen[current_idx]) continue;
        else seen[current_idx] = true;
        
        for (int i = 0; i < n; ++i) {
            if (dist[i] <= dist[current_idx] + G[current_idx][i]) continue;
            dist[i] = dist[current_idx] + G[current_idx][i];
            cout << "revisado " << current_idx << ", distancia a " << i << ": " << dist[i] << endl;
            q.push(i);
            cout << i << " añadido al stack" << endl;
        }
    }

    return dist[to_idx];
}/*}}}*/

int main () {/*{{{*/
    int n, m, v1, v2;
    double w;
    wgraph G;
    
    while (cin >> n >> m) {
        G = wgraph (n, vector<double> (n, infinity));
        for (int i = 0; i < m; ++i) {
            cin >> v1 >> v2 >> w;
            G[v1][v2] = w;
        }
        
        cin >> v1 >> v2;
        int dist = dijkstra(G, v1, v2);
        if (dist > 0) cout << dist << endl;
        else cout << "no path from " << v1 << " to " << v2 << endl;
    }
}/*}}}*/

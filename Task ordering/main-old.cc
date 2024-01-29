#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;

struct taskdata {
    set<string> precs;
    int indeg = 0;
};

#define taskmap map<string,taskdata>
#define taskit map<string,taskdata>::iterator
#define tsetit set<taskit>::iterator
#define precit set<string>::iterator

void topol_sort (taskmap& tasks) {
    set<taskit> tset;
    
    for (taskit it = tasks.begin(); it != tasks.end(); it++) {
        if (it->second.indeg == 0) tset.insert(it);
    }
    
    while (not tset.empty()) {
        tsetit starter = tset.begin();
        cout << (*starter)->first;
        
        for (precit it = (*starter)->second.precs.begin(); it != (*starter)->second.precs.end(); it++) {
            --tasks[*it].indeg;
            if (tasks[*it].indeg == 0) tset.insert(tasks.find(*it));
        }
        
        tset.erase(starter);
    }
}

int main () {
    int n; cin >> n;
    vector<string> names (n);
    taskmap tasks;
    for (int i = 0; i < n; ++i) cin >> names[i];
    int m; cin >> m;
    for (int i = 0; i < m; ++i) {
        string x; cin >> x;
        string y; cin >> y;
        tasks[x].precs.insert(y);
        tasks[x].indeg++;
    }
}

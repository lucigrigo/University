#include<bits/stdc++.h>

using namespace std;

const int mxN = 1e4;
const int mxX = 10;
const int start = 1;

int n, m, x, finish, n_collected, cost1, cost2;
unordered_set<int> substs[mxN];
map<int, int> to[mxN];
int collected[mxX];
unordered_set<int> vis1;
unordered_set<int> vis2;

// functie care realizeaza parcurgerea in adancime pentru RELU
void DFS1(int u) {
    for(auto itr = substs[u].begin(); itr != substs[u].end(); ++itr) {
		if(collected[*itr] == 0) {
			n_collected++;
			collected[*itr] = 1;
		}
    }
    if(u == finish) {
		return;
    }
    vis1.insert(u);
    map<int, int> adj = to[u];
    if(n_collected < x) {
    	int min_dist = to[u].begin()->first;
    	for(map<int, int>::iterator it = adj.begin(); it != adj.end() && it->first == min_dist; it++) {
			if(!substs[it->second].empty() && vis1.find(it->second) == vis1.end()) {
				for(auto itr = substs[it->second].begin(); itr != substs[it->second].end(); ++itr) {
					if(collected[*itr] == 0) {
				   		cost1 += it->first;
			    	    DFS1(it->second); 	    
				    	return;
					}
				}
			}
			if(it->second == finish) {
				cost1 += it->first;
				DFS1(it->second);
				return;
			}
	    }
        for(auto it = adj.begin(); it != adj.end(); ++it) {
            if(vis1.find(it->second) == vis1.end()) {
                cost1 += it->first;
    			DFS1(it->second);
                return;
            }
        }
	    
    } else {
    	for(auto it = adj.begin(); it != adj.end(); ++it) {
    		if(it->second == finish) {
    			cost1 += it->first;
    			DFS1(it->second);
    			return;
    		}
    	}
    	for(auto it = adj.begin(); it != adj.end(); ++it) {
            if(vis1.find(it->second) == vis1.end()) {
                cost1 += it->first;
                DFS1(it->second);
                return;
            }
        }
    }
}

// functie care realizeaza parcurgerea in adancime pentru SABIN
void DFS2(int u) {
    for(auto itr = substs[u].begin(); itr != substs[u].end(); ++itr) {
		if(collected[*itr] == 0) {
			n_collected++;
			collected[*itr] = 1;
		}
    }
    if(u == finish) {
		return;
    }
    map<int, int> adj = to[u];
    vis2.insert(u);
    if(n_collected < x) {
		for(auto it = adj.begin(); it != adj.end(); ++it) {
			if(!substs[it->second].empty() && vis2.find(it->second) == vis2.end()) {
				for(auto itr = substs[it->second].begin(); itr != substs[it->second].end(); ++itr) {
					if(collected[*itr] == 0) {
					    cost2 += it->first;
			    	    DFS2(it->second); 	    
					    return;
					}
				}
			}
		}
        for(auto it = adj.begin(); it != adj.end(); ++it) {
            if(vis2.find(it->second) == vis2.end()) {
                cost2 += it->first;
                DFS2(it->second);
                return;
            }
        }
	} else {
		for(auto it = adj.begin(); it != adj.end(); ++it) {
			if(it->second == finish) {
				cost2 += it->first;
				DFS2(it->second);
				return;
			}
		}
		for(auto it = adj.begin(); it != adj.end(); ++it) {
            if(vis2.find(it->second) == vis2.end()) {
                cost2 += it->first;
                DFS2(it->second);
                return;
            }
        }
	}	
}

int main() {
    // citire date de intrare
    ifstream in;
    in.open("umbre.in");
    in >> n >> m >> x;
    finish = n;

    // citire substante
    for(int i = 0; i < n; ++i) {
        int nr;
        in >> nr;
        for(int j = 0; j < nr; ++j) {
            int s;
            in >> s;
            substs[i].insert(s);
        }
    }

    // citire muchii
    for(int i = 0; i < m; ++i) {
        int u, v, c;
        in >> u >> v >> c;
        to[u].insert(pair<int, int>(c, v));
	    to[v].insert(pair<int, int>(c, u));
    }
    in.close();

    // realizarea a doua parcurgeri in adancime 
    // primul drum
    DFS1(1);

    // al doilea drum
    DFS2(1);

    // scriere date de iesire
    ofstream out;
    out.open("umbre.out");
    out << max(cost1, cost2);
    out.close();

    return 0;
}
#include<bits/stdc++.h>

using namespace std;

const int maxn = 1e5; // nr maxim de noduri
int n, m, a, b, n_edges, parents[maxn]; // variabile folosite
vector<int> to[maxn]; // vectorul de liste de adiacenta
bool ancestor[maxn], visited[maxn];
unordered_set<int> path; // drumul creat la un moment de algoritm

// functia care intoarce stramosul unui nod din CTC
int find_parent(int u) {
	return parents[u] == u ? u : parents[u] = find_parent(parents[u]);
}

// functia care realizeaza parcurgerea in adancime
void DFS(int u) {
	visited[u] = 1; // marcam nodul ca vizitat
	path.insert(u); // il adaugam la drumul creat
	for(int i = 0; i < (int) to[u].size(); i++) { // parcurgem vecinii lui
		int v = to[u][i];
		if(find_parent(u) != find_parent(v)) { 
			// daca nu fac parte din aceeasi CTC
			continue;
		}
		if(visited[v] && path.find(v) != path.end()) { 
			// daca nodul a fost vizitat de drumul curent
			ancestor[find_parent(v)] = 1; // am gasit un ciclu
		}
		if(!visited[v]) { // daca nodul nu a fost vizitat
			DFS(v);
		}
	}
	path.erase(u); // stergem nodul curent in drum
}

// functia care adauga o noua muchie in graf
void addEdge(int u, int v) {
	to[u].push_back(v);
	parents[find_parent(u)] = find_parent(v); // muchie unidirectionala
}

int main() {
	// citire date de intrare
    ifstream in;
    in.open("holograme.in");

    in >> n >> m;

	// initializari parinti
	n_edges = n;
	for(int i = 0; i < n; i++) {
		parents[i] = i;
	}

	// citirea muchiilor
	for(int i = 0; i < m; i++) {
        in >> a >> b;
		addEdge(a, b);
	}
    in.close();

	// parcurgere noduri
	for(int i = 0; i < n; i++) {
		int r = find_parent(i);
		if(ancestor[r]) { // daca exista un drum pana la nodul curent
			visited[i] = 1;
		}
		if(!visited[i]) { // daca nodul nu a fost vizitat
			DFS(i);
		}
	}

	// parcurgere noduri
	for(int i = 0; i < n; i++) {
		int r = find_parent(i);
		if(visited[i] && !ancestor[r]) { // daca gasim o componenta conexa cu ciclu in ea
			ancestor[r] = 1;
			n_edges--; // scadem o muchie din numarul total
		}
	}

	// scriere rezultat
    ofstream out;
    out.open("holograme.out");
    out << n_edges;
    out.close();

    return 0;
}
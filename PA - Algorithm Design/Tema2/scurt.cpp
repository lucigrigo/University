#include<bits/stdc++.h>

using namespace std;

// constante folosite
const int mxN = 1e4;
const int mxC = 1e4 + 1;

// variabile folosite
int n, m, a, b, c, no_final_edges;
bool visited[mxN + 1];

// structura folosita pentru a memora o muchie
typedef struct edge { 
    int cost;
    int status;
    int start;
    int finish;
    int index;
    bool reversed;
    struct edge *next;
    struct edge *sibling;
} TEdge;

// structura folosite pentru memorarea unei paduri de muchii
typedef struct forest {
    int index;
    int n_size;
    int *nodes;
} TForest;

// lista de distante maxime pentru toate adiacentele
int max_list[mxN + 1][mxN + 1];

// functie care creeaza o noua muchie
TEdge *newEdge(int c, int u, int v, bool r, int i) {
    TEdge *e = (TEdge *) malloc(sizeof(TEdge));
    e->cost = c;
    e->start = u;
    e->finish = v;
    e->reversed = r;
    e->status = -1;
    e->index = i;
    e->next = NULL;
    e->sibling = NULL;
    return e;
}

// structuri de memorare folosite
TEdge **edges = NULL;
vector<TEdge *> in_edges[mxC];
vector<TEdge *> to[mxN + 1];
TEdge **final_edges;

// functie care adauga o noua muchie
void addEdge(int u, int v, int c, int i) {
    TEdge *de = newEdge(c, u, v, false, i);
    TEdge *re = newEdge(c, v, u, true, i);
    de->sibling = re;
    re->sibling = de;
    
    in_edges[c].push_back(de);
}

// functie care initializeaza padurile de muchii
TForest **init_forests() {
    TForest **forests = (TForest **) malloc((n + 1) * sizeof(TForest *));
    for(int i = 1; i <= n; ++i) {
        TForest *f = (TForest *) malloc(sizeof(TForest));
        f->nodes = (int *) malloc((n + 1) * sizeof(int));
        f->nodes[0] = i;
        f->n_size = 1;
        forests[i] = f;
    }
    return forests;
}

// functie care realizeaza un drum de la sursa la destinatie
int DFS(int start, int finish, int u, int c) {
    if(u == finish) { // daca am ajuns la destinatie
        return 1;
    }
    visited[u] = true; // il marcam ca vizitat
    vector<TEdge *> adj = to[u];

    for(auto it = adj.begin(); it != adj.end(); ++it) { // parcurgerea vecinilor
        if(!visited[(*it)->finish]) { // daca vecinul a fost vizitat
            int ret = DFS(start, finish, (*it)->finish, c);
            if(ret == 1) { // daca s-a ajuns la destinatie la un moment dat
                if((*it)->cost == c) { // eliminam muchiile de cost maxim
                    (*it)->status = 1;
                    (*it)->sibling->status = 1;
                }
                return 1;
            }
        }
    }
    return 0;
}

// functie care verifica pentru o muchie care ar crea un ciclu daca poate
// fi inclusa sau nu in padure
TForest **check_cycle(TForest **forests, TEdge **e, int u, int v) {
    TForest *f = forests[u];

    // se obtine costul maxim
    int max_c = max(max_list[u][v], max_list[v][u]);
    
    if(max_c < (*e)->cost) { // daca muchia curenta este de cost mai mare
        return forests;
    }

    for(int i = 1; i <= n; ++i) { // se realizeaza drumul de la u la v
        visited[i] = false;
    }
    int ret = DFS(u, v, u, (*e)->cost);

    // se adauga muchia curenta ca fiind din grupul 2 de muchii la arborele final
    (*e)->status = 1;
    to[u].push_back((*e));
    to[v].push_back((*e)->sibling);
    final_edges[no_final_edges] = (*e);
    no_final_edges++;

    return forests;
}

// functie care realizeaza reuniunea dintre doua paduri de muchii
TForest **forest_reunion(TForest **forests, TEdge **e, int u, int v, int c) {
    TForest *f1 = forests[u];
    TForest *f2 = forests[v];

    // adaugarea muchiei curente
    (*e)->status = 0;
    to[u].push_back((*e));
    to[v].push_back((*e)->sibling);
    final_edges[no_final_edges] = (*e);
    no_final_edges++;

    // actualizare distante
    for(int i = 0; i < f1->n_size; ++i) {
        for(int j = 0; j < f2->n_size; ++j) {
            max_list[f1->nodes[i]][f2->nodes[j]] = (*e)->cost;
            max_list[f2->nodes[j]][f1->nodes[i]] = (*e)->cost;
        }
    }

    // mutare noduri
    for(int i = 0; i < f2->n_size; ++i) {
        f1->nodes[f1->n_size] = f2->nodes[i];
        f1->n_size = f1->n_size + 1;
    }

    // atribuire pointer la paduri
    for(int i = 0; i < f1->n_size; ++i) {
        forests[f1->nodes[i]] = f1;
    }

    return forests;
}

// functie care compara dupa index muchiile
int ecomp(const void *p, const void *q) {
    return (*(TEdge **)p)->index - (*(TEdge **)q)->index;
}

int main() {
    // citire date de intrare
    ifstream in;
    in.open("scurt.in");

    in >> n >> m;
    int cc = 0;
    for(int i = 0; i < m; ++i) {
        in >> a >> b >> c;
        addEdge(a, b, c, i);
        cc = max(cc, c);
    }
    in.close();

    // initializare structuri pentru paduri
    final_edges = (TEdge **) malloc(4 * mxN * sizeof(TEdge *));
    TForest **forests = init_forests();

    // parcurgere muchii dupa cost
    int index_cost = 1;
    for(auto itr = in_edges[index_cost].begin(); index_cost <= cc; ++itr) {
        if(itr == in_edges[index_cost].end()) { // daca am terminat muchiile de un cost
            if(forests[1]->n_size == n) { // daca am inclus toate nodurile in MST
                break;
            }
            index_cost++;
            // gasirea urmatoarelor muchii
            while(in_edges[index_cost].empty() && index_cost < mxC) {
                ++index_cost;
            }
            if(index_cost == mxC) // daca am terminat muchiile
                break;
            itr = in_edges[index_cost].begin();
        }
        // valori curente
        TEdge *current_edge = *itr;
        int u = current_edge->start;
        int v = current_edge->finish;
        int c = current_edge->cost;

        if(forests[u] == forests[v]) { // daca cele doua noduri fac parte din aceeasi padure
            forests = check_cycle(forests, &current_edge, u, v);
        } else { // daca fac parte din paduri diferite
            forests = forest_reunion(forests, &current_edge, u, v, c);
        }
    }

    // scriere date de iesire
    ofstream out;
    out.open("scurt.out");

    // sortare muchii finale dupa index
    qsort(final_edges, no_final_edges, sizeof(TEdge*), ecomp);

    // calculare numar de muchii din fiecare tip
    int n_vital = 0;
    int n_intr = 0;
    for(int it = 0; it < no_final_edges; ++it) {
        if(final_edges[it]->status == 0) {
            ++n_vital;
        } else if(final_edges[it]->status == 1) {
            ++n_intr;
        }
    }

    // afisare muchii din grupul 1
    out << n_vital << " " << n_intr << '\n';
    for(int it = 0; it < no_final_edges; ++it) {
        if(final_edges[it]->status == 0) {
            out << final_edges[it]->start << " " << final_edges[it]->finish << "\n";
        }
    }

    // afisare muchii din grupul 2
    for(int it = 0; it < no_final_edges; ++it) {
        if(final_edges[it]->status == 1) {
            out << final_edges[it]->start << " " << final_edges[it]->finish << "\n";
        }
    }

    out.close();
    return 0;
}
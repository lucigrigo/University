// Proiectarea Algoritmilor
// Laborator 11
// Grigore Lucian-Florin 324CDb
#include <stdlib.h>
#include <stdio.h>

int G[12][12]; // graful folosit
int n = 12; // numarul de noduri din graf

int dist_prim[12]; // vectorul de distante pentru alg. Prim
int p_prim[12]; // vectorul de parinti pentru alg. Prim
int inclus_prim[12]; // vector care indica daca un nod face parte din AMA

int *constrQ(int *q, int *size, int sursa) {
	int i;
	for(i = 0; i < n; ++i) {
		if(G[sursa][i] != 0 || G[i][sursa] != 0) {
			dist_prim[i] = G[sursa][i] + G[i][sursa];
			p_prim[i] = sursa;
			q[*size] = i;
			(*size)++;
		}
	}
	return q;
}

int *extrageMin(int *q, int *e, int *size) {
	int min = 1000000000;
	int index = -1;
	for(i = 0; i < *size; ++i) {
		if(dist_prim[q[i]] < min) {
			index = i;
			min = dist_prim[q[i]];
		}
	}
	*e = q[index];
	q[index] = q[*size];
	(*size)--;
	return q;
}

void prim() {
	int *q = (int *) malloc(n * sizeof(int)); // alocare coada
	int q_size = 0; // dimensiunea cozii
	int ama_size = 0; // dimensiunea arborelui minim de acoperire
	int AMA[24][2]; // aici vor fi memorate muchiile din AMA
	int i;
	int elem;
	for(i = 0; i < n; ++i) {
		dist_prim[i] = 1000000000; // initializare distante
		p_prim = -1; // initializare parinti
	}
	dist_prim[8] = 0; // nod sursa
	q = constrQ(q, &q_size);
	while(q_size > 0) {
		q = extrageMin(q, &elem, &q_size);
		AMA[ama_size][0] = elem;
		AMA[ama_size][1] = p_prim[elem];
		int j;
		for(j = 0; j < n; ++j) {
			if(G[elem][])
		}
	}
	free(q);
}

void kruskal() {

}

int main() {
	// muchiile din graful folosit
	G[0][8] = 3;
	G[0][1] = 9;
	G[0][6] = 10;
	G[0][7] = 6;
	G[1][6] = 11;
	G[1][2] = 5;
	G[2][3] = 8;
	G[2][4] = 12;
	G[3][5] = 0;
	G[4][5] = 2;
	G[6][7] = 4;
	G[8][9] = 5;
	G[9][10] = 14;
	G[10][11] = 7;
	G[8][11] = 8;
	prim();
	kruskal();
	return 0;
}
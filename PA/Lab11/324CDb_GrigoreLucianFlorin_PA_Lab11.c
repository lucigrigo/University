// Proiectarea Algoritmilor
// Laborator 11
// Grigore Lucian-Florin 324CDb
#include <stdlib.h>
#include <stdio.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

int G[12][12]; // graful folosit
int n = 12; // numarul de noduri din graf

int dist_prim[12]; // vectorul de distante pentru alg. Prim
int p_prim[12]; // vectorul de parinti pentru alg. Prim
int inclus_prim[12]; // vector care indica daca un nod face parte din AMA

// functie care construieste coada cu noduri pentru alg. PRIM
int *constrQ(int *q, int *size, int sursa) {
	int i;
	for(i = 0; i < n; ++i) { // se adauga toate nodurile din graf
		q[*size] = i;
		(*size)++;
	}
	return q;
}

// functie care extrage nodul cu distanta minima din coada
int *extrageMin(int *q, int *e, int *size) {
	// initializari
	int min = 1000000000;
	int index = -1;
	int i;
	for(i = 0; i < *size; ++i) { // se cauta minimul
		if(dist_prim[q[i]] < min) { // daca s-a gasit un nou minim
			index = i;
			min = dist_prim[q[i]];
		}
	}
	// se atribuie valoarea de intoarcere
	*e = q[index];
	// se actualizeaza coada
	q[index] = q[*size - 1];
	(*size)--;
	return q;
}

// functie care implementeaza algoritmul lui PRIM
void prim() {
	printf("---------------------------------------\n");
	printf("--- ALGORITMUL LUI PRIM ---\n\n");
	int *q = (int *) malloc(n * sizeof(int)); // alocare coada
	int q_size = 0; // dimensiunea cozii
	int ama_size = 0; // dimensiunea arborelui minim de acoperire
	int AMA[50][2]; // aici vor fi memorate muchiile din AMA
	int i; // iterator
	int elem; // elementul care va fi scos din caoda
	for(i = 0; i < n; ++i) {
		dist_prim[i] = 1000000000; // initializare distante
		p_prim[i] = -1; // initializare parinti
	}
	dist_prim[8] = 0; // nod sursa
	q = constrQ(q, &q_size, 8); // se construieste coada
	int pas = 0; // numarul pasii algoritmului
	while(q_size > 0) { // cat timp coada nu e vida
		int k;
		q = extrageMin(q, &elem, &q_size); // se extrage nodul cel mai apropiat
		printf("pasul %d - se extrage nodul (%c) p=%c\n", pas++,
			(char) elem + 65, (char) p_prim[elem] + 65);
		AMA[ama_size][0] = elem; // se adauga muchia in AMA
		AMA[ama_size][1] = p_prim[elem]; // dintre el si parintele lui
		ama_size++; // creste dimensiunea AMA-ului
		int j;
		for(j = 0; j < n; ++j) { // se parcurg succesorii acestuia
			if(G[elem][j] != 0 || G[j][elem] != 0) { 
				int d = G[elem][j] + G[j][elem];
				if(d < dist_prim[j]) {
					// daca se poate actualiza o distanta
					p_prim[j] = elem;
					dist_prim[j] = d;
				}
			}
		}
	}
	// printare rezultat algoritm
	printf("\n\n--- REZULTATE ALGORITMUL LUI PRIM ---\n");
	printf("\n--- muchiile din AMA sunt ---\n");
	for(i = 1; i < ama_size; ++i) {
		printf("\t%c - %c\n", (char)AMA[i][0] + 65, (char)AMA[i][1] + 65);
	}
	printf("\n---------------------------------------\n");
	free(q);
}

// functie care actualizeaza vectorul arb pentru alg. KRUSKAL
// atunci cand se adauga o noua muchie
int *alegeArb(int index1, int index2, int *v) {
	int v1 = v[index1];
	int v2 = v[index2];
	int m = min(v1, v2);
	int i;
	for(i = 0; i < n; ++i) {
		if(v[i] == v1 || v[i] == v2) {
			v[i] = m;
		}
	}
	return v;
}

// functie care implementeaza algoritmul lui KRUSKAL
void kruskal() {
	printf("--- ALGORITMUL LUI KRUSKAL ---\n\n");
	int *arb_kruskal = (int *) malloc(n * sizeof(int)); // vectorul arb
	int muchii_kruskal[50][3]; // muchiile din graful initial
	int muchii_AMA[50][2]; // muchiile din arborele minim de acoperire
	int nr_muchii = 0; // numarul de muchii din graf
	int i; // iterator
	int ama_size = 0; // numarul de muchii din AMA
	for(i = 0; i < n; ++i) { // initializari
		arb_kruskal[i] = i; // impartire noduri in n subarbori
		int j;
		for(j = 0; j < n; ++j) { // adaugare muchii in vectorul de muchii
			if(G[i][j] != 0) {
				muchii_kruskal[nr_muchii][0] = i;
				muchii_kruskal[nr_muchii][1] = j;
				muchii_kruskal[nr_muchii][2] = G[i][j];
				nr_muchii++;
			}
		}
	}
	for(i = 0; i < nr_muchii; ++i) {
		int muchia_curenta[2];
		int min = 1000000000;
		int index_min = -1;
		int j;
		// cautare muchia de cost minim
		for(j = 0; j < nr_muchii; ++j) {
			if(muchii_kruskal[j][2] < min) {
				min = muchii_kruskal[j][2];
				index_min = j;
			}
		}
		int u = muchii_kruskal[index_min][0];
		int v = muchii_kruskal[index_min][1];
		printf("pas %d - muchia %c-%c de cost=%d\n", i, (char)u + 65,
			(char)v + 65, muchii_kruskal[index_min][2]);
		// suprascrierea costului muchiei gasite
		// pentru a nu fi considerata din nou in viitor de catre algoritm
		muchii_kruskal[index_min][2] = 1000000000;
		if(arb_kruskal[u] != arb_kruskal[v]) {
			// daca nodurile care formeaza acea muchie sunt in subarbori diferiti
			printf("\t se adauga in AMA\n");
			arb_kruskal = alegeArb(u, v, arb_kruskal); // actualizare vector arb
			// adaugare muchie gasita in vector
			muchii_AMA[ama_size][0] = u; 
			muchii_AMA[ama_size][1] = v;
			ama_size++;
		} else {
			printf("\t NU se adauga in AMA\n");
		}
	}
	// printare rezultat algoritm
	printf("\n\n--- REZULTATE ALGORITMUL LUI KRUSKAL ---\n"
			"muchiile din graf sunt:\n");
	for(i = 0; i < ama_size; ++i) {
		printf("\t%c - %c\n", (char)muchii_AMA[i][0] + 65,
					(char)muchii_AMA[i][1] + 65);
	}
	printf("---------------------------------------\n");
	free(arb_kruskal);
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
	G[3][5] = 9;
	G[4][5] = 2;
	G[6][7] = 4;
	G[8][9] = 5;
	G[9][10] = 14;
	G[10][11] = 7;
	G[8][11] = 8;
	// aplicam algoritmii Prim si Kruskal pe graful de mai sus
	prim();
	kruskal();
	return 0;
}
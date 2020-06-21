/*
                        Proiectarea Algoritmilor
                        Laborator 7
                        Grigore Lucian-Florin
                        324CD
*/
#include <stdio.h>
#include <stdlib.h>
#define min(a, b) ((a) < (b) ? (a) : (b))

// variabile globale (automat initializate cu valoarea default - 0)
int n = 10;          // numar de noduri din graf
int M[10][10];       // matricea de adiacenta
int d_bfs[10][10];   // vectorul de distante pentru BFS
int vizitat_bfs[10]; // vectorul de culori pentru BFS
int p_bfs[10];       // vectorul de parinti pentru BFS
int vizitat_dfs[10]; // vectorul de culori pentru DFS
int d_dfs[10];       // vectorul care memoreaza timpul de inceput pentru DFS
int f_dfs[10];       // vectorul care memoreaza timpul de finalizare pentru DFS
int p_dfs[10];       // vectorul de parinti pentru DFS
int timp_dfs;        // timp pentru parcurgerea in adancime

// structura pentru coada
struct queue {
  int start; // indexul de inceput al cozii
  int size;  // numarul de elemente din coada (si indexul de final din coada)
  int arr[]; // vectorul de elemente
};

// functia care initializeaza o coada goala
struct queue *create_queue() {
  struct queue *q = (struct queue *)malloc(sizeof(struct queue));
  q->size = 0;  // dimensiunea initiala
  q->start = 0; // indexul initial de start (nu are niciun element coada)
  return q;
}

// functia care adauga un element in coada
struct queue *enqueue(struct queue *q, int elem) {
  q->arr[q->size] = elem; // adauga elementul pe ultima pozitie
  q->size = q->size + 1;  // incrementeaza dimensiunea
  return q;
}

// functia care returneaza primul element din coada
struct queue *top(struct queue *q, int *x) {
  *x = q->arr[q->start]; // returneaza elementul de pe pozitia indexului 'start'
  return q;
}

// functia care elimina un element din coada
struct queue *dequeue(struct queue *q) {
  q->start = q->start + 1; // incrementeaza indexul de start
  return q;
}

// functia care verifica daca o coada este goala
int is_empty(struct queue *q) {
  // verifica daca indexul de start este egal cu cel de final
  if (q->size == q->start) {
    return 1; // coada este goala
  }
  return 0; // coada inca mai are elemente in ea
}

// functia care printeaza o coada (folosita pentru parcurgerea in latime)
void printare_coada(struct queue *q) {
  int i;
  printf("Q: "); // inceputul cozii la momentul curent

  // se printeaza informatii despre fiecare nod din coada astfel:
  // nodul curent
  // parintele nodului curent
  // distanta de la nodul radacina al subarborelui generat de algoritm la nodul
  // curent culoarea nodului curent
  for (i = q->start; i < q->size; ++i) {
    printf("   \tNod (%c) p(%c)=%c d(%c)=%d c(%c)=%s\n", (char)q->arr[i] + 65,
           (char)q->arr[i] + 65, (char)p_bfs[q->arr[i]] + 65,
           (char)q->arr[i] + 65, (*d_bfs)[q->arr[i]], (char)q->arr[i] + 65,
           vizitat_bfs[q->arr[i]] == 1 ? "gri" : "alb");
  }
  // printf("\n");
}

// functie care printeaza informatiile finale ale algoritmului BFS
void printare_rezultate_BFS() {
  int i;
  printf("\nRezultate finale BFS:\n");

  // se printeaza urmatoarele informatii pentru fiecare nod al grafului
  // numele nodului
  // parintele nodului
  // distanta de la nodul radacina al subarborelui generat de algoritm in
  //           care intra nodul pana la nodul curent
  // culoarea nodului
  for (i = 0; i < n; ++i) {
    printf("\tNod (%c): p(%c)=%c d(%c)=%d c(%c)=%s\n", (char)i + 65,
           (char)i + 65, p_bfs[i] == i ? '-' : (char)p_bfs[i] + 65,
           (char)i + 65, (*d_bfs)[i], (char)i + 65,
           vizitat_bfs[i] == 1 ? "negru" : "alb");
  }
}

// functia care realizeaza parcurgerea in latime
void BFS() {
  int i; // iterator printre noduri
  int t; // variabila timp
  int prev_elem = -1;

  for (i = 0, t = 1; i < n; ++i) {
    if (vizitat_bfs[i] == 0) {          // daca nu am vizitat nodul curent
      struct queue *q = create_queue(); // creaza o coada goala
      q = enqueue(q, i);                // baga in coada elementul curent
      d_bfs[i][i] = 0;    // actualizez distanta pentru primul element (0)
      vizitat_bfs[i] = 1; // il marchez ca vizitat
      printf("\nNod sursa curent: %c\n", (char)i + 65);

      while (is_empty(q) == 0) { // cat timp coada nu este goala
        printf("Pasul %d: \n", t++);
        printare_coada(q);     // printeaza coada la momentul curent
        if (prev_elem != -1) { // ultimul element scos din coada
          printf("  \tc(%c)=negru\n\n", (char)prev_elem + 65);
        } else {
          printf("\n");
        }
        int current_elem;          // declar elementul curent din coada
        q = top(q, &current_elem); // ii atribui valoarea din coada
        int j;                     // iterator printre noduri

        for (j = 0; j < n; ++j) {
          // daca exista muchie de la nodul din coada la cel curent in iterare
          // din graf si acesta nu a fost vizitat
          if ((M[current_elem][j] == 1) && (vizitat_bfs[j] == 0)) {
            q = enqueue(q, j);                        // bag elementul in coada
            d_bfs[i][j] = d_bfs[i][current_elem] + 1; // actualizez distanta lui
            p_bfs[j] = current_elem; // atribui parintele nodului curent
            vizitat_bfs[j] = 1;      // il marchez ca vizitat
          }
        }

        vizitat_bfs[current_elem] = 1; // marchez elementul curent ca vizitat
        q = dequeue(q);                // il scot din coada
        prev_elem = current_elem;      // ultimul element scos din coada
      }
    }
  }
  printf("Pasul %d:\nQ:\tc(%c)=negru\n  \tempty\n", t, (char)prev_elem + 65);
  printare_rezultate_BFS(); // printez rezultatele finale
}

// functia recursiva care exploreaza conform algoritmului DFS
void explorare(int u, int p) {
  d_dfs[u] = ++timp_dfs; // atribui timpul de inceput al nodului curent
  int j;                 // declar iteratorul
  vizitat_dfs[u] = 1;    // marchez nodul curent ca "gri"
  // afisez nodul curent inainte de apelul recursiv
  // printez caracterul din nod si distanta pana la acesta de la
  //    nodul curent al functiei initiale a algoritmului
  printf("\nNod %c c(%c)=gri d(%c)=%d p(%c)=%c", (char)u + 65, (char)u + 65,
         (char)u + 65, d_dfs[u], (char)u + 65, (char)p + 65);

  // parcurg toate nodurile
  for (j = 0; j < n; ++j) {
    // daca exista muchie de la nodul curent la acesta si cel din urma este inca
    // "alb"
    if (M[u][j] == 1 && vizitat_dfs[j] == 0) {
      p_dfs[j] = u; // ii marchez parintele
      // apelez functia de explorare pentru nodurile adiacente celui curent
      explorare(j, u);
    }
  }
  f_dfs[u] = ++timp_dfs; // atribui timpul de finalizare al nodului curent
  printf("\nNod %c c(%c)=negru f(%c)=%d", (char)u + 65, (char)u + 65,
         (char)u + 65, f_dfs[u]);
  vizitat_dfs[u] = 2; // marchez nodul curent ca "negru"
}

// functia principala care realizeaza parcurgerea in adancime
void DFS() {
  int i; // iteratorul

  // parcurg toate nodurile grafului
  for (i = 0; i < n; ++i) {
    if (vizitat_dfs[i] == 0) { // daca nodul nu a fost vizitat inca
      printf("\n\t\t---\nNod radacina curent: %c", (char)i + 65);
      explorare(i, -20); // apelez functia de explorare pentru acesta
      // reinitializez vectorul de culori pentru urmatoarea iteratie
      // pentru ca folosesc o variabila globala
      // daca nu as reinitializa acest vector dupa fiecare parcurgere a
      // unui nod, algoritmul s-ar opri dupa primele cateva noduri care
      // trec maxim o data prin toate nodurile grafului
      int j;
      timp_dfs = 0;
      for (j = 0; j < n; j++) {
        if (j != i) {
          // resetez vectorii distantelor
          d_dfs[j] = 0;
          f_dfs[j] = 0;
          // resetez culoarea nodurilor
          vizitat_dfs[j] = 0;
        }
      }
    }
  }
}

// functia main
int main() {
  // muchiile grafului
  M[0][1] = 1; // (A,B)
  M[0][2] = 1; // (A,C)
  M[0][7] = 1; // (A,H)
  M[1][3] = 1; // (B,D)
  M[1][4] = 1; // (B,E)
  M[1][7] = 1; // (B,H)
  M[1][8] = 1; // (B,I)
  M[2][3] = 1; // (C,D)
  M[3][4] = 1; // (D,E)
  M[3][9] = 1; // (D,J)
  M[4][5] = 1; // (E,F)
  M[4][6] = 1; // (E,G)
  M[5][6] = 1; // (F,G)
  M[7][8] = 1; // (H,I)
  M[8][0] = 1; // (I,A)
  printf("\n------------------------------\n");
  printf("\n--- Parcurgere pe latime --- \n");
  BFS(); // parcurgerea in latime
  printf("\n------------------------------\n--- Parcurgere pe adancime ---\n");
  DFS(); // parcurgerea in adancime
  printf("\n------------------------------\n");
  return 0;
}

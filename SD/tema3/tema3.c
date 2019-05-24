//                Tema 3 - Structuri de date
//                Grigore Lucian - Florin 314CD
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INT 2147483647

// prototipuri ale functiilor folosite
void readData(FILE *, char *);
void kuhnAlgorithm(int **, int **, int, int, char *);
int computeCost(int *, int *);
void removeMins(int **, int, int);
int **updateMatrix(int **, int, int, int *, int *);
void makeZero(int *, int, int *, int);
void writeSolution(int **, int, int, int *, char *);
int match(int index, int *markedLin, int *rowsLeft, int *columnsRight, int **A,
          int M, int N, int *visited, int *count);
void checkOrientation(int *markedLin, int *markedCol, int M, int N, int **A,
                      int index, int *columnsRight, int *rowsLeft);

int main(int argc, char *argv[]) {
  FILE *ffile = fopen(argv[1], "r"); // deschiderea fisierului de input
  if (ffile == NULL) {
    printf("error openning input file\nexiting\n");
    exit(1);
  }
  readData(ffile, argv[2]); // citirea datelor de input
  return 0;
}

void writeSolution(int **A, int M, int N, int *columns, char *outputFileName) {
  FILE *ffile = fopen(outputFileName, "w");
  int i;
  for (i = 0; i < N; i++) // scrierea indicilor de output
    fprintf(ffile, "%d\n", columns[i]);
  fclose(ffile);
}

void readData(FILE *inputFile, char *outputFileName) {
  int N, M;
  // citirea nr de orase si nr de centrale
  fscanf(inputFile, "%d %d\n", &N, &M);
  // citirea pozitiilor oraselor
  int **cities = (int **)malloc(N * sizeof(int *)), i;
  for (i = 0; i < N; i++) {
    cities[i] = (int *)malloc(2 * sizeof(int));
    fscanf(inputFile, "%d %d\n", &cities[i][0], &cities[i][1]);
  }
  // citirea pozitiilor centralelor
  int **plants = (int **)malloc(M * sizeof(int *));
  for (i = 0; i < M; i++) {
    plants[i] = (int *)malloc(2 * sizeof(int));
    fscanf(inputFile, "%d %d\n", &plants[i][0], &plants[i][1]);
  }
  fclose(inputFile);
  // apelarea functiei de rezolvare a algoritmului
  kuhnAlgorithm(cities, plants, N, M, outputFileName);
  // eliberarea memoriei folosite
  for (i = 0; i < M; i++)
    free(plants[i]);
  free(plants);
  for (i = 0; i < N; i++)
    free(cities[i]);
  free(cities);
}

// calculeaza costul pentru o coordonata anume din matrice
int computeCost(int *cityCoord, int *plantCoord) {
  return (abs(cityCoord[0] - plantCoord[0]) +
          abs(cityCoord[1] - plantCoord[1]));
}

// scade minimul de pe fiecare linie/coloana de pe linia/coloana respectiva
void removeMins(int **A, int M, int N) {
  int i, j;
  // minimul pe linii
  for (i = 0; i < M; i++) {
    int min = MAX_INT;
    for (j = 0; j < N; j++) {
      if (A[i][j] < min)
        min = A[i][j];
    }
    for (j = 0; j < N; j++) {
      A[i][j] = A[i][j] - min;
    }
  }
  // minimul pe coloane
  for (i = 0; i < N; i++) {
    int min = MAX_INT;
    for (j = 0; j < M; j++) {
      if (A[j][i] < min)
        min = A[j][i];
    }
    for (j = 0; j < M; j++) {
      A[j][i] = A[j][i] - min;
    }
  }
}

/* Calculeaza minimul dintre valorile neacoperite de nicio linie si o scade
din aceste valori; aduna aceeasi valoare la toate casutele acoperite de
doua linii. */
int **updateMatrix(int **A, int M, int N, int *markedLin, int *markedCol) {
  int min = MAX_INT, i, j;
  // calculeaza minimul
  for (i = 0; i < M; i++) {
    if (!markedLin[i]) {
      for (j = 0; j < N; j++) {
        if (!markedCol[j]) {
          if (A[i][j] < min && A[i][j] >= 0)
            min = A[i][j];
        }
      }
    }
  }
  // scade minimul de pe liniile neacoperite
  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++) {
      if (!markedCol[j] && !markedLin[i])
        A[i][j] = A[i][j] - min;
    }
  }
  // il adauga la cele acoperite de 2 ori
  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++) {
      if (markedCol[j] && markedLin[i])
        A[i][j] = A[i][j] + min;
    }
  }
  return A;
}

// Functie creata doar pentru a initializa doi vectori cu valori 0
void makeZero(int *v1, int n1, int *v2, int n2) {
  int i;
  for (i = 0; i < n1; i++)
    v1[i] = 0;
  for (i = 0; i < n2; i++)
    v2[i] = 0;
}

/* Functie care realizeaza "cuplarea" dintre linii si coloane, adica gasirea
numarului minim de linii care sa acopere un numar maxim de 0-uri din matricea
de costuri. */
int match(int index, int *markedLin, int *rowsLeft, int *columnsRight, int **A,
          int M, int N, int *visited, int *count) {
  if (visited[index])
    return 0;
  visited[index] = 1;
  int i;
  /* cazul in care pe linia curenta se cauta un 0 necuplat cu alta coloana,
  se cupleaza cu linia curenta, si se marcheaza linia curenta */
  for (i = 0; i < N; i++) {
    if (A[index][i] == 0 && columnsRight[i] == -1) {
      markedLin[index] = 1;
      rowsLeft[index] = i;
      columnsRight[i] = index;
      (*count)++;
      return 1;
    }
  }
  /* cazul in care se incearca decuplarea unui 0 deja marcat de pe linia
   curenta si cuplarea lui cu linia curenta.
   Adica linia corespunzatoare cuplajului linie-coloana al coloanei pe care se
   afla 0-ul curent se vrea cuplata cu alt 0 de pe ea, diferit de cel actual.*/
  for (i = 0; i < N; i++) {
    if (A[index][i] == 0 && match(columnsRight[i], markedLin, rowsLeft,
                                  columnsRight, A, M, N, visited, count)) {
      markedLin[index] = 1;
      rowsLeft[index] = i;
      columnsRight[i] = index;
      return 1;
    }
  }
  return 0;
}

/* Functia care verifica ca pentru un numar minim de cuplaje, adica linii
trase prin matricea de costuri, sunt acoperite toate valorile de 0.
Daca se gaseste un 0 neacoperit de nicio linie, se marcheaza coloana respecti-
va, se demarcheaza linia cuplata cu coloana in speta si se realizeaza aceeasi
cautare pentru noua linie nemarcata. */
void checkOrientation(int *markedLin, int *markedCol, int M, int N, int **A,
                      int index, int *columnsRight, int *rowsLeft) {
  int i;
  for (i = 0; i < N; i++) {
    if (!markedCol[i] && A[index][i] == 0) {
      markedCol[i] = 1;
      markedLin[columnsRight[i]] = 0;
      checkOrientation(markedLin, markedCol, M, N, A, columnsRight[i],
                       columnsRight, rowsLeft);
    }
  }
}

// Functia principala pentru rezolvarea algoritmului
void kuhnAlgorithm(int **cities, int **plants, int N, int M,
                   char *outputFileName) {
  // alocarea matricei
  int **A = (int **)calloc(M, sizeof(int *)), i, j;
  for (i = 0; i < M; i++)
    A[i] = (int *)calloc(M, sizeof(int));
  // calcularea costurilor
  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++)
      A[i][j] = computeCost(cities[j], plants[i]);
  }
  // scaderea minimurilor de pe fiecare linie si coloana
  removeMins(A, M, M);
  int *rowsLeft = (int *)calloc(M, sizeof(int)),
      *columnsRight = (int *)calloc(N, sizeof(int));
  while (1) {
    // variabile care trebuie reinitializate cu 0 la fiecare noua iteratie
    int *markedLin = (int *)calloc(M, sizeof(int)),
        *markedCol = (int *)calloc(M, sizeof(int)),
        *visitedLins = (int *)calloc(M, sizeof(int));
    if (markedLin == NULL || markedCol == NULL) {
      printf("eroare la alocarea memoriei\n");
      exit(1);
    }
    int count = 0;
    for (i = 0; i < M; i++) { // valori care sa indice "unmatched"
      rowsLeft[i] = -1;
      columnsRight[i] = -1;
    }
    while (1) {
      int found = 0;
      for (i = 0; i < M; i++) // marcam ca nevizitate toate liniile
        visitedLins[i] = 0;
      for (i = 0; i < M; i++) {
        if (rowsLeft[i] == -1) // cautam sa cuplam o linie necuplata
          found = found | match(i, markedLin, rowsLeft, columnsRight, A, M, M,
                                visitedLins, &count);
      }
      if (!found) // daca nu cuplam vreo linie in iteratia curenta
        break;
    }
    // cautam sa imbunatatim la maxim acoperirea 0-urilor cu cele (count)-linii
    for (i = 0; i < M; i++) {
      if (!markedLin[i])
        checkOrientation(markedLin, markedCol, M, N, A, i, columnsRight,
                         rowsLeft);
    }
    if (count == M) { // daca s-a gasit solutia finala
      free(markedLin);
      free(markedCol);
      free(visitedLins);
      break;
    }
    makeZero(rowsLeft, M, columnsRight, N); // reinitializarea unor valori cu 0
    updateMatrix(A, M, N, markedLin, markedCol); // crearea de noi 0
  }
  writeSolution(A, M, N, columnsRight, outputFileName); // scrierea solutiei
  // eliberarea memoriei folosite
  free(columnsRight);
  free(rowsLeft);
  for (i = 0; i < M; i++) {
    free(A[i]);
  }
  free(A);
}

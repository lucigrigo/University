/*
  Proiectarea Algoritmilor - Tema 1
  Problema 1 - Temele buclucase
  Grigore Lucian-Florin 324CD
*/
#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define INPUT_FILENAME "teme.in"
#define OUTPUT_FILENAME "teme.out"

// structura care memoreaza informatiile despre o tema
struct tema {
  short punctaj;
  short timp_rezolvare;
  short deadline;
  short index;
};

// structura care memoreaza informatiile legate de o solutie
struct solutie {
  int punctaj;
  int no_teme;
  int index_i;
  int index_j;
  int rezolvata;
  struct solutie *prev;
};

// functie care creeaza o noua tema
struct tema *tema_noua(short p, short tr, short d, short i) {
  struct tema *t = (struct tema *)malloc(sizeof(struct tema));
  t->deadline = d;
  t->punctaj = p;
  t->index = i;
  t->timp_rezolvare = tr;
  return t;
}

// functie care creeaza un nou element care memoreaza o solutie
struct solutie *new_sol(int add, const int max_size) {
  struct solutie *s = (struct solutie *)malloc(sizeof(struct solutie));
  s->punctaj = 0;
  s->no_teme = 0;
  s->index_i = -1;
  s->index_j = -1;
  s->rezolvata = 0;
  s->prev = NULL;
  return s;
}

// functie de comparare intre teme folosita pentru qsort
int tcomp(const void *p, const void *q) {
  // temele sunt comparate dupa deadline
  return (*(struct tema **)p)->deadline - (*(struct tema **)q)->deadline;
}

struct solutie *alegere(struct solutie *s1, struct solutie *s2,
                        struct tema *tema_curenta, int ii, int j) {
  // initializare solutie
  struct solutie *sol = new_sol(0, 0);
  // linia curenta
  sol->index_i = ii;
  // coloana curenta
  sol->index_j = j;

  // daca nu exista o tema ce poate fi rezolvata, alegem maximul dintre solutii
  if (tema_curenta == NULL) {
    if (s1->punctaj > s2->punctaj) {
      sol->punctaj = s1->punctaj;
      sol->no_teme = s1->no_teme;
      sol->prev = s1;
    } else {
      sol->punctaj = s2->punctaj;
      sol->no_teme = s2->no_teme;
      sol->prev = s2;
    }
  } else {
    // daca putem face o tema, alegem maximul dintre D[i-1][j] si D[i-1][j-t_f]
    if (s2->punctaj + tema_curenta->punctaj > s1->punctaj) {
      // daca este mai profitabil sa facem tema curenta in loc de oricare alta
      sol->punctaj = s2->punctaj + tema_curenta->punctaj;
      sol->no_teme = s2->no_teme + 1;
      sol->prev = s2;
      sol->rezolvata = 1;
    } else {
      // este mai profitabil sa nu facem tema curenta
      sol->punctaj = s1->punctaj;
      sol->no_teme = s1->no_teme;
      sol->prev = s1;
    }
  }

  // intoarcem solutie obtinuta
  return sol;
}

int main() {
  int i;

  // valoare de input
  short nr_teme_total;
  short final_deadline = 0;

  // citire date de intrare
  FILE *file_in = fopen(INPUT_FILENAME, "r");
  fscanf(file_in, "%hi\n", &nr_teme_total);
  struct tema **teme =
      (struct tema **)malloc(nr_teme_total * sizeof(struct tema *));
  for (i = 0; i < nr_teme_total; ++i) {
    short timp_rezolvare;
    short punctaj;
    short deadline;
    fscanf(file_in, "%hi %hi %hi\n", &timp_rezolvare, &punctaj, &deadline);
    teme[i] = tema_noua(punctaj, timp_rezolvare, deadline, i + 1);
    final_deadline = max(final_deadline, deadline);
  }
  fclose(file_in);

  // sortarea temelor crescator dupa deadline
  qsort(teme, nr_teme_total, sizeof(struct tema *), tcomp);

  // alocare memorie pentru matricea de solutii
  struct solutie ***D = (struct solutie ***)malloc((nr_teme_total + 2) *
                                                   sizeof(struct solutie **));
  for (i = 0; i <= nr_teme_total; ++i) {
    D[i] = (struct solutie **)malloc((final_deadline + 2) *
                                     sizeof(struct solutie *));
  }

  // initializare valori default pentru cazul de baza
  for (i = 0; i <= final_deadline; ++i) {
    D[0][i] = new_sol(1, nr_teme_total);
  }

  // construirea solutiei optime la fiecare pas
  for (i = 1; i <= (nr_teme_total); ++i) {
    int j;
    // indexul temei curente
    int index_tema = i - 1;
    // tema curenta
    struct tema *tema_curenta = teme[index_tema];
    // deadline temei curente
    int ddl = tema_curenta->deadline;
    // timpul de finalizare al temei curente
    int t_f = tema_curenta->timp_rezolvare;

    // parcurgere pe parcursul saptamanilor
    for (j = 0; j <= final_deadline; j++) {
      if (j < t_f) {
        // daca nu putem face tema curenta (dpdv al timpului)
        // copiem solutia de mai sus (aceeasi saptamana, tema precedenta)
        D[i][j] = new_sol(0, 0);
        D[i][j]->no_teme = D[i - 1][j]->no_teme;
        D[i][j]->prev = D[i - 1][j];
        D[i][j]->punctaj = D[i - 1][j]->punctaj;
        D[i][j]->index_i = i;
        D[i][j]->index_j = j;
      } else {
        if (j <= ddl) {
          // daca inca putem face tema curenta
          // alegem maximul dintre D[i-1][j] si D[i-1][j-t_r]
          D[i][j] = alegere(D[i - 1][j], D[i - 1][j - t_f], tema_curenta, i, j);
        } else {
          // daca am trecut de deadline-ul temei curente
          // alegem maximul dintre D[i-1][j] si D[i][j-1]
          D[i][j] = alegere(D[i - 1][j], D[i][j - 1], NULL, i, j);
        }
      }
    }
  }

  // rezultatele finale
  int punctaj_acumulat = D[nr_teme_total][final_deadline]->punctaj;
  int teme_rezolvate = D[nr_teme_total][final_deadline]->no_teme;

  // scriere date de iesire
  FILE *file_out = fopen(OUTPUT_FILENAME, "w");
  fprintf(file_out, "%d %d\n", punctaj_acumulat, teme_rezolvate);

  // construirea solutiei in ordinea rezolvarii temelor
  struct solutie *sol_curenta = D[nr_teme_total][final_deadline];
  int *sol = (int *)malloc(nr_teme_total * sizeof(int));
  i = 0;
  while (sol_curenta != NULL) {
    if (sol_curenta->rezolvata == 1) {
      sol[i++] = teme[sol_curenta->index_i - 1]->index;
    }
    sol_curenta = sol_curenta->prev;
  }
  i--;

  // printarea solutiei
  while (i >= 0) {
    fprintf(file_out, "%d ", sol[i--]);
  }
  fclose(file_out);

  // eliberarea memoriei folosite
  free(sol);
  for (i = 0; i <= nr_teme_total; ++i) {
    int j = 0;
    if (D[i] != NULL) {
      for (j = 0; j <= final_deadline; ++j) {
        if (D[i][j] != NULL) {
          free(D[i][j]);
        }
      }
      free(D[i]);
    }
  }
  free(D);

  return 0;
}

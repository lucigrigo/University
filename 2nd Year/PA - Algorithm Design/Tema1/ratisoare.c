/*
Proiectarea Algoritmilor - Tema 1
Problema 3 - Ratustele
Grigore Lucian-Florin 324CD
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILENAME "ratisoare.in"
#define OUTPUT_FILENAME "ratisoare.out"
// valoarea default (de initializare) pentru timpul de iesire
#define DEFAULT_TIME 2147483647

// structura ce memoreaza informatiile despre o rata
struct rata {
  int linie;
  int coloana;
  int index_initial;
  int timp_iesire;
  char *orientare;
};

// functia care creeaza o rata noua
struct rata *rata_noua(int l, int c, int i, char *o) {
  struct rata *r = (struct rata *)malloc(sizeof(struct rata));
  r->orientare = (char *)malloc(2 * sizeof(char));
  strncpy(r->orientare, o, 2);
  r->index_initial = i;
  r->linie = l;
  r->coloana = c;
  r->timp_iesire = DEFAULT_TIME;
  return r;
}

// functie de comparare folosita la sortarea initiala
int init_comp(const void *p, const void *q) {
  // sortare rate dupa linie si coloana crescator
  if (((*(struct rata **)p)->linie != (*(struct rata **)q)->linie)) {
    return ((*(struct rata **)p)->linie - (*(struct rata **)q)->linie);
  }
  return ((*(struct rata **)p)->coloana - (*(struct rata **)q)->coloana);
}

// functie de comparare folosita la sortarea finala
int final_comp(const void *p, const void *q) {
  // sortare rate dupa timpul de iesire
  if ((*(struct rata **)p)->timp_iesire != (*(struct rata **)q)->timp_iesire) {
    return (*(struct rata **)p)->timp_iesire -
           (*(struct rata **)q)->timp_iesire;
  }
  return (*(struct rata **)p)->index_initial -
         (*(struct rata **)q)->index_initial;
}

// functie care calculeaza timpii de iesire pentru o anumita linie
struct rata **calcul_linie(struct rata **rate, int start_index,
                           int linie_curenta, int nr_rate, int nr_coloane) {
  int i = start_index, index_max = -1;

  // scoatem ratele care sunt orientate inspre stanga si pot fi scoase
  while (i < nr_rate && strcmp(rate[i]->orientare, "S") == 0 &&
         rate[i]->linie == linie_curenta) {
    rate[i]->timp_iesire = rate[i]->coloana + 1;
    i++;
  }

  // cautam indicele ultimei rate de pe linia curenta
  while (i < nr_rate && rate[i]->linie == linie_curenta) {
    i++;
  }
  i--;
  index_max = i;

  // scoatem ratele care sunt orientate inspre dreapta si pot fi scoase
  while (i >= start_index && strcmp(rate[i]->orientare, "D") == 0 &&
         rate[i]->linie == linie_curenta) {
    rate[i]->timp_iesire = nr_coloane - rate[i]->coloana;
    i--;
  }
  // numarul maxim posibil de rate de pe linie
  int max_dim = index_max - start_index + 1;

  // alocare memorie pentru vectorii de pointeri
  struct rata **orientate_stanga =
      (struct rata **)malloc(max_dim * sizeof(struct rata *));
  struct rata **orientate_dreapta =
      (struct rata **)malloc(max_dim * sizeof(struct rata *));
  int max_stanga = 0, max_dreapta = 0;

  // construirea vectorilor de pointeri cu cele doua tipuri de orientari
  for (i = start_index; i <= index_max; ++i) {
    if (rate[i]->timp_iesire == DEFAULT_TIME) {
      if (strcmp(rate[i]->orientare, "D") == 0) {
        // daca rata este ->
        orientate_dreapta[max_dreapta] = rate[i];
        max_dreapta++;
      } else {
        // daca rata este <-
        orientate_stanga[max_stanga] = rate[i];
        max_stanga++;
      }
    }
  }

  // atribuirea primelor max_stanga rate care nu au timpul de iesire calculat
  // timpul de iesire al primul max_stanga rate orientate la stanga
  int st = 0, dr = 0;
  for (i = start_index; i <= index_max && st < max_stanga; ++i) {
    struct rata *r = rate[i];
    if (r->timp_iesire == DEFAULT_TIME) {
      r->timp_iesire = orientate_stanga[st]->coloana + 1;
      st++;
    }
  }

  // atribuirea ratelor ramase cu timpul necalculat timpul de iesire al ratelor
  // orientate la dreapta
  for (; i <= index_max && dr < max_dreapta; ++i) {
    struct rata *r = rate[i];
    if (r->timp_iesire == DEFAULT_TIME) {
      r->timp_iesire = nr_coloane - orientate_dreapta[dr]->coloana;
      dr++;
    }
  }

  // eliberarea vectorilor
  free(orientate_dreapta);
  free(orientate_stanga);
  return rate;
}

int main() {
  int i;

  // valori de input
  int nr_linii;
  int nr_coloane;
  int k;
  int nr_ratisoare;

  // citire date de intrare
  FILE *file_in = fopen(INPUT_FILENAME, "r");
  fscanf(file_in, "%d %d %d %d\n", &nr_linii, &nr_coloane, &k, &nr_ratisoare);
  struct rata **rate =
      (struct rata **)malloc(nr_ratisoare * sizeof(struct rata *));
  char *orientare = (char *)malloc(2 * sizeof(char));
  for (i = 0; i < nr_ratisoare; ++i) {
    int identificator;
    int index_linie;
    int index_coloana;
    fscanf(file_in, "%d %d %d %c\n", &identificator, &index_linie,
           &index_coloana, orientare);
    rate[i] =
        rata_noua(index_linie - 1, index_coloana - 1, identificator, orientare);
  }
  fclose(file_in);

  // sortare rate dupa linii si coloane
  qsort(rate, nr_ratisoare, sizeof(struct rata *), init_comp);

  // parcurgerea pe linii si calculul pe fiecare linie la fiecare rata
  int index;
  for (i = 0, index = 0; i < nr_linii && index < nr_ratisoare; i++) {
    // daca pe linia curenta nu avem nicio rata
    while (rate[index]->linie != i) {
      i++;
    }
    rate = calcul_linie(rate, index, i, nr_ratisoare, nr_coloane);

    // gasim prima rata care nu este de pe linia curenta
    while (index < nr_ratisoare && rate[index]->linie == i) {
      index++;
    }
  }

  // sortare rate crescator dupa timpul de iesire si index
  qsort(rate, nr_ratisoare, sizeof(struct rata *), final_comp);

  // scriere date de iesire
  FILE *file_out = fopen(OUTPUT_FILENAME, "w");
  fprintf(file_out, "%d", rate[k - 1]->index_initial);
  fclose(file_out);

  // eliberarea memoriei
  for (i = 0; i < nr_ratisoare; ++i) {
    free(rate[i]->orientare);
    free(rate[i]);
  }
  free(rate);

  return 0;
}

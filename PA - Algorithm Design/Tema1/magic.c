/*
Proiectarea Algoritmilor - Tema 1
Problema 2 - Numarul magic
Grigore Lucian-Florin 324CD
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILENAME "magic.in"
#define OUTPUT_FILENAME "magic.out"
#define MAX_NUM 100000
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

// structura care reprezinta un numar din sirul de input
struct numar {
  int index_initial;
  int suma;
};

// structura care reprezinta rezultatul algoritmului
struct rezultat {
  int nr_magic;
  int stg;
  int drp;
  int n_pct;
  struct numar **Y;
};

// functie care creeaza un element nou de tip numar din input
struct numar *numar_nou(int s, int i) {
  struct numar *n = (struct numar *)malloc(sizeof(struct numar));
  n->index_initial = i;
  n->suma = s;
  return n;
}

// functie folosita la qsort dupa suma
int ncomp(const void *p, const void *q) {
  return (*(struct numar **)p)->suma - (*(struct numar **)q)->suma;
}

// functie care realizeaza interclasarea dintre doua siruri dupa suma
struct numar **interclasare(struct numar **v1, struct numar **v2, int n1,
                            int n2) {
  int i;
  int j;
  int k;
  struct numar **new_Y =
      (struct numar **)malloc((n1 + n2) * sizeof(struct numar *));

  for (i = 0, j = 0, k = 0; i < n1 && j < n2;) {
    if (v1[i]->suma < v2[j]->suma) {
      new_Y[k++] = v1[i++];
    } else {
      new_Y[k++] = v2[j++];
    }
  }
  while (i < n1) {
    new_Y[k++] = v1[i++];
  }
  while (j < n2) {
    new_Y[k++] = v2[j++];
  }
  return new_Y;
}

// functie care calculeaza minimul dintre 3 numere (brute force)
struct rezultat *gaseste_min(int d1, int d2, int d3, int i_stg, int i_drp,
                             struct rezultat *rez, struct numar **v) {
  // se gaseste ordinea elementelor, se memoreaza nr magic local si indicii
  if (d1 < d2) {
    if (d3 < d1) {
      rez->nr_magic = d3;
      rez->stg = v[i_stg + 1]->index_initial;
      rez->drp = v[i_drp]->index_initial;
    } else {
      rez->nr_magic = d1;
      rez->stg = v[i_stg]->index_initial;
      rez->drp = v[i_drp]->index_initial;
    }
  } else {
    if (d3 < d2) {
      rez->nr_magic = d3;
      rez->stg = v[i_stg + 1]->index_initial;
      rez->drp = v[i_drp]->index_initial;
    } else {
      rez->nr_magic = d2;
      rez->stg = v[i_stg]->index_initial;
      rez->drp = v[i_drp - 1]->index_initial;
    }
  }
  rez->n_pct = 3;
  // se construieste vectorul suplimentar Y, ordonat dupa suma
  if (v[i_stg]->suma < v[i_drp]->suma) {
    if (v[i_stg]->suma < v[i_drp - 1]->suma) {
      rez->Y[0] = v[i_stg];
      if (v[i_drp]->suma < v[i_drp - 1]->suma) {
        rez->Y[1] = v[i_drp];
        rez->Y[2] = v[i_drp - 1];
      } else {
        rez->Y[1] = v[i_drp - 1];
        rez->Y[2] = v[i_drp];
      }
    } else {
      rez->Y[0] = v[i_drp - 1];
      rez->Y[1] = v[i_stg];
      rez->Y[2] = v[i_drp];
    }
  } else {
    if (v[i_drp]->suma < v[i_drp - 1]->suma) {
      rez->Y[0] = v[i_drp];
      if (v[i_drp - 1]->suma < v[i_stg]->suma) {
        rez->Y[1] = v[i_drp - 1];
        rez->Y[2] = v[i_stg];
      } else {
        rez->Y[1] = v[i_stg];
        rez->Y[2] = v[i_drp - 1];
      }
    } else {
      rez->Y[0] = v[i_drp - 1];
      rez->Y[1] = v[i_drp];
      rez->Y[2] = v[i_stg];
    }
  }
  return rez;
}

// functia principala de calcul al numarului magic
struct rezultat *calc_min(struct numar **vect, int lim_stg, int lim_drp) {
  if (lim_drp - lim_stg <= 2) {
    // daca avem 3 sau mai putine puncte in apelul curent
    // calculez minimul dintre numerele de la pasul curent
    struct rezultat *rez = (struct rezultat *)malloc(sizeof(struct rezultat));
    rez->n_pct = 0;
    rez->Y = (struct numar **)malloc(MAX_NUM * sizeof(struct numar *));
    int d1 = pow(lim_stg - lim_drp, 2) +
             pow(vect[lim_stg]->suma - vect[lim_drp]->suma, 2);
    if (lim_drp - lim_stg == 2) {
      // daca sunt 3 puncte
      int d2 = pow(lim_stg - lim_drp + 1, 2) +
               pow(vect[lim_stg]->suma - vect[lim_drp - 1]->suma, 2);
      int d3 = pow(lim_stg + 1 - lim_drp, 2) +
               pow(vect[lim_stg + 1]->suma - vect[lim_drp]->suma, 2);
      // apelez functia construita mai sus
      rez = gaseste_min(d1, d2, d3, lim_stg, lim_drp, rez, vect);
    } else {
      // daca sunt doar 2 puncte
      rez->nr_magic = d1;
      rez->stg = vect[lim_stg]->index_initial;
      rez->drp = vect[lim_drp]->index_initial;
      rez->n_pct = 2;
      if (lim_stg < lim_drp) {
        rez->Y[0] = vect[lim_stg];
        rez->Y[1] = vect[lim_drp];
      } else {
        rez->Y[1] = vect[lim_stg];
        rez->Y[0] = vect[lim_drp];
      }
    }
    return rez;
  }
  // impartirea zonei in jumatate
  int m = (lim_drp + lim_stg) / 2;

  // calcularea in zonele obtinute
  struct rezultat *min_stg = calc_min(vect, lim_stg, m);
  struct rezultat *min_drp = calc_min(vect, m + 1, lim_drp);

  // initializari
  struct rezultat *min = NULL;
  struct numar **new_Y =
      interclasare(min_stg->Y, min_drp->Y, min_stg->n_pct, min_drp->n_pct);
  int new_n_pct = min_stg->n_pct + min_drp->n_pct;
  int k;

  // daca minimul de pe stanga este mai mare decat celelalt
  if (min_stg->nr_magic < min_drp->nr_magic) {
    min = min_stg;
    free(min_drp);
  } else if (min_stg->nr_magic > min_drp->nr_magic) {
    // daca minimul de pe dreapta este mai mic decat celalalt
    min = min_drp;
    free(min_stg);
  } else if (min_stg->nr_magic == min_drp->nr_magic) {
    // daca minimurile sunt egale, caut solutie mai mica dpdv lexicografic
    if (min_stg->stg < min_drp->stg) {
      min = min_stg;
      free(min_drp);
    } else {
      min = min_drp;
      free(min_stg);
    }
  }
  min->Y = new_Y;
  min->n_pct = new_n_pct;

  int i, j;
  // cautare minimul in zona de minim din jurul dreptei care desparte zonele
  for (i = 0; i < new_n_pct; i++) {
    j = i + 1;
    int c = 0;
    if (new_n_pct == 1) {
      // daca avem doar un punct
      break;
    }
    if (abs(new_Y[i]->index_initial - vect[m]->index_initial) < min->nr_magic) {
      // daca punctul curent este la distanta minima necesara
      for (; c < 7 && j < new_n_pct; c++, j++) {
        // comparam cu urmatoarele elemente pentru gasirea minimului
        if (abs(new_Y[j]->suma - vect[m]->suma) > min->nr_magic) {
          // daca gasim un punct care este la o distanta mai mare decat numarul
          // magic curent, oprim compararea
          break;
        }
        if (pow(new_Y[i]->index_initial - new_Y[j]->index_initial, 2) +
                pow(new_Y[i]->suma - new_Y[j]->suma, 2) <
            min->nr_magic) {
          // daca gasim o distanta mai mica numarul magic precedent
          min->nr_magic =
              (pow(new_Y[i]->index_initial - new_Y[j]->index_initial, 2) +
               pow(new_Y[i]->suma - new_Y[j]->suma, 2));
          min->stg = min(new_Y[i]->index_initial, new_Y[j]->index_initial);
          min->drp = max(new_Y[i]->index_initial, new_Y[j]->index_initial);
        }
      }
    }
  }

  // intoarcem minimul
  return min;
}

int main() {
  int i;

  // valori de intrare
  int nr_biletele;

  // valori de iesire
  short nr_magic;
  short stanga;
  short dreapta;

  // citire date de intrare
  FILE *file_in = fopen(INPUT_FILENAME, "r");
  fscanf(file_in, "%d\n", &nr_biletele);
  struct numar **numere =
      (struct numar **)malloc(nr_biletele * sizeof(struct numar *));
  int suma = 0;
  for (i = 0; i < nr_biletele; ++i) {
    int nr_curent;
    fscanf(file_in, "%d ", &nr_curent);
    // printf("INPUT %d s=%d\n", nr_curent, suma);
    numere[i] = numar_nou(suma, i + 1);
    suma += nr_curent;
  }
  fclose(file_in);

  // calcularea recursiva a minimului
  struct rezultat *rezultat_final =
      (struct rezultat *)malloc(sizeof(struct rezultat));
  rezultat_final->drp = nr_biletele;
  rezultat_final->stg = 0;
  rezultat_final->nr_magic = 0;
  rezultat_final = calc_min(numere, 0, nr_biletele - 1);

  // scrierea datelor de iesire
  FILE *file_out = fopen(OUTPUT_FILENAME, "w");
  fprintf(file_out, "%d\n%d %d\n", rezultat_final->nr_magic,
          min(rezultat_final->stg, rezultat_final->drp),
          max(rezultat_final->stg, rezultat_final->drp));
  fclose(file_out);

  // eliberarea memoriei
  free(rezultat_final);
  return 0;
}

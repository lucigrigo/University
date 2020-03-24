/*
  Proiectarea Algoritmilor
  Laboratorul 5
  Grigore Lucian-Florin
  324CD semigrupa b
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// functie care interschimba 2 valori
void schimba(char *x, char *y)
{
  char temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

// functie care verifica daca am printat in trecut permutarea curenta
int alreadyHere(char *current_str, char **printed_str, int len)
{
  int i;
  for (i = 0; i < len; i++) // parcurg vectorul de stringuri
  {
    if (strcmp(current_str, printed_str[i]) == 0) // daca gasesc permutarea curenta
    {
      return 1;
    }
  }
  return 0;
}

// functie care foloseste backtracking pentru afisarea unei permutari
void permutare(char *a, int l, int n, char **already_printed, int len)
{
  if (l >= n) // daca am ajuns la lungimea unei afisari
  {
    printf("\t%s\n", a); // printam permutarea generata
    return;
  }
  // declarare iterator
  int i;
  // o sa interschimb litera cu litera cea de pe un index local
  // cu cea de pe indexul functiei
  for (i = 0; i < n; i++)
  {
    // verific daca am mai generat permutarea curenta
    if (alreadyHere(a, already_printed, len))
    {
      // daca da, merg la pozitia urmatoare
      continue;
    }
    // interschimbare litera pozitie curenta din functie
    // cu pozitia din apelul recursiv
    schimba((a + l), (a + i));
    // apelam recursiv functia curenta cu literele interschimbate
    permutare(a, l + 1, n, already_printed, len);
    // punem permutarea curenta in vectorul care le memoreaza
    strcpy(already_printed[len++], a);
    // interschimbam inapoi literele
    schimba((a + l), (a + i));
  }
}

// functie care printeaza toate solutiile de aranjare a scandurilor
// pentru lungimea de la un moment dat
void printare_solutie_garduri(int k, int L)
{
  // declarare iterator
  int j;
  // aloc memorie pentru string-ul intial
  char *a = (char *)malloc(L * sizeof(char));
  for (j = 0; j < L; j++)
  {
    // il populez cu scanduri verticale
    strcpy((a + j), "|");
  }

  // aloc memorie pentru vectorul care va memora toate
  // permutarile generate
  // aloc initial 50 de elemente
  char **str = (char **)malloc(50 * sizeof(char *));
  for (j = 0; j < 50; j++)
  {
    // alocare memorie pentru un singur string al vectorului
    str[j] = (char *)malloc(L * sizeof(char));
  }

  // apelul functiei care generaza permutarile
  permutare(a, 0, L - 1, str, 0);

  // eliberez memoria ocupata de fiecare element al vectorului
  for (j = 0; j < 10; j++)
  {
    free(str[j]);
  }
  // eliberez memoria ocupata de pointerul vector
  free(str);

  // codul care urmeaza cauta sa adauge scanduri orizontale (=)
  // memorez lungimea initiala a stringului
  int init_len = L;
  // initialez numarul de egaluri
  int nr_egaluri = 0;
  // pun egaluri cat timp l - k nu e mai mic ca 0
  while ((L - k) >= 0)
  {
    // aloc memorie pentru vectorul care va memora solutiile generate
    char **str_egal = (char **)malloc(50 * sizeof(char *));
    for (j = 0; j < 50; j++)
    {
      // aloc memorie pentru un element al vectorului
      str_egal[j] = (char *)malloc(10 * sizeof(char));
    }

    // incrementez numarul de egaluri
    nr_egaluri++;
    // scad din l k-ul corespunzator
    L -= k;

    // aloc memorie pentru stringul initial
    char *single_str_egal = (char *)malloc(50 * sizeof(char));
    // in index memorez indexul pana la care pun caracterul egal (=)
    // in stringul initial
    int index = 0;
    // pun cate egaluri e nevoie pentru pasul curent
    for (j = 0; j < nr_egaluri; j++)
    {
      strcpy((single_str_egal + j), "=");
      index++;
    }
    // de la indexul salvat la pasul precedent, pun cate scanduri verticale
    // sunt necesare pentru a ajunge la lungimea maxima
    for (j = 0; j < L; j++, index++)
    {
      strcpy((single_str_egal + index), "|");
    }

    // apelul funtiei de permutare pentru stringul generat
    permutare(single_str_egal, 0, init_len - nr_egaluri, str_egal, 0);

    // eliberez memoria ocupata de fiecare element al vectorului de stringuri
    for (j = 0; j < 50; j++)
    {
      free(str_egal[j]);
    }
    // eliberez memoria ocupata de vector ca pointer
    free(str_egal);
  }
}

// functia care rezolva problema k-garduri
void k_garduri(int n, int k)
{
  // initializare vector care memoreaza nr de solutii
  int D[n];
  // declarare
  int i = 3;

  // cazurile de baza (in cazul nostru cu k = 2)
  D[1] = 1;
  D[2] = 2;

  // desfasurarea recurentei pt nr de solutii
  for (; i <= n; i++)
  {
    // nr de solutii pentru gardul de lungime i
    D[i] = D[i - 1] + D[i - k];
  }

  // printare rezultat
  printf("solutii obtinute:\n");
  for (i = 1; i <= n; i++)
  {
    printf("\nD[%d] = %d\n", i, D[i]); // printare optim
    printare_solutie_garduri(k, i);    // printare solutie optima
  }
  printf("-----\n");
}

// functie care se ocupa de printare solutiilor pentru un singur pas al problemei
// sume modulo 3
void print_sume(int v[], int index, int sum, int rest, int sol[], int index_sol,
                int n)
{
  // daca am terminat de parcurs vectorul
  if (index == -1)
  {
    return;
  }
  // apel recursiv pentru aceeasi functie de afisare
  print_sume(v, index - 1, sum, rest, sol, index_sol, n);
  // daca adaugam elementul curent la suma pana la pasul curent
  // si ne da restul care trebuie pentru pasul din algoritm
  if (((sum + v[index]) % 3) == rest)
  {
    // adaugam elementul curent la vectorul solutie construit
    sol[index_sol++] = v[index];
    // printez suma de pana acum + elementul curent
    printf("%d + %d = %d { ", sum, v[index], sum + v[index]);
    int j;
    // printez elementele din vectorul solutie
    for (j = 0; j < index_sol; j++)
    {
      printf("%d ", sol[j]);
    }
    printf("}\n\t\t");
  }
  // apeluri recursive catre aceeasi functie
  if (((sum + v[index]) % 3) != rest)
  {
    // cazul in care elementul curent trebuie introdus in vector
    sol[index_sol++] = v[index];
    print_sume(v, index - 1, sum + v[index], rest, sol, index_sol, n);
  }
  else // cazul in care elementul curent nu e bagat in vector
  {
    print_sume(v, index - 1, sum + v[index], rest, sol, index_sol, n);
  }
}

// functie care rezolva problema sume modulo 3
void sume(int v[], int n)
{
  // initializare matricea care va contine nr de sume pentru fiecare
  // pas al algoritmului
  int D[n + 1][3];
  // cazurile de baza aflate la indexul 0 din matrice
  D[0][0] = 0;
  D[0][1] = 0;
  D[0][2] = 0;

  /*
      OBSERVATIE
      Pentru a putea include si cazurile de baza in matricea
  cu numarul de sume, am inceput algoritmul de la indexul 1. Vectorul de
  numere este indexat de la 0.
      Astfel, valoarea de la pasul curent (INDEX) din matrice este valoarea
  din vector de la (INDEX - 1).
      De aceea apare peste tot v[i - 1];
  */
  int i;
  for (i = 1; i <= n; i++)
  {
    if (v[i - 1] % 3 == 0) // cazul in care v[i] % 3 da rest 0
    {
      D[i][0] = 1 + 2 * D[i - 1][0]; // D[i][0] = 1 + 2 * D[i-1][0]
      D[i][1] = 2 * D[i - 1][1];     // D[i][1] = 2 * D[i-1][1]
      D[i][2] = 2 * D[i - 1][2];     // D[i][2] = 2 * D[i-1][2]
    }
    else if (v[i - 1] % 3 == 1) // cazul in care v[i] % 3 da rest 1
    {
      D[i][0] = D[i - 1][0] + D[i - 1][1]; // D[i][0] = D[i-1][0] + D[i-1][1]
      D[i][1] =
          1 + D[i - 1][0] + D[i - 1][1];   // D[i][1] = 1 + D[i-1][0] + D[i-1][1]
      D[i][2] = D[i - 1][2] + D[i - 1][1]; // D[i][2] = D[i-1][2] + D[i-1][1]
    }
    else // cazul in care v[i] % 3 da rest 2
    {
      D[i][0] = D[i - 1][0] + D[i - 1][1]; // D[i][0] = D[i-1][0] + D[i-1][1]
      D[i][1] = D[i - 1][2] + D[i - 1][1]; // D[i][1] = D[i-1][2] + D[i-1][1]
      D[i][2] =
          1 + D[i - 1][2] + D[i - 1][0]; // D[i][2] = 1 + D[i-1][2] + D[i-1][0]
    }
    /*
        OBSERVATIE AFISARE
      1. am printat toate cele 3 recurente rezultate la fiecare pas: D[i][0], D[i][1] si D[i][2]
      2. sub fiecare recurenta am printat construirea sumei pana la pasul unde se gaseste o solutie
      valida.
      3. pe acelasi rand cu afisarea fiecarei sume mentionate mai sus am printat solutia construita 
      intre acolade
      4. pentru (2) si (3) am folosit functia print_sume, implementata mai sus
      5. la fiecare printare a vectorului-solutie, elementele sunt in ordinea inversa fata de vectorul
      initial, datorita recurentei folosite
    */
    printf("La pasul %d valoarea din vector este %d si are restul impartirii "
           "la 3 egal cu %d.\nCele 3 recurente rezultate sunt:\n",
           i - 1, v[i - 1], v[i - 1] % 3);
    int empty_sol[n]; // vector care va memora solutia construita
    int len = 0;      // lungimea acestuia
    // pentru rest 0
    printf("\n\tD[%d][0] = %d\n\t\t", i, D[i][0]);
    print_sume(v, i - 1, 0, 0, empty_sol, len, n);
    len = 0;
    // pentru rest 1
    printf("\n\tD[%d][1] = %d\n\t\t", i, D[i][1]);
    print_sume(v, i - 1, 0, 1, empty_sol, len, n);
    len = 0;
    // pentru rest 2
    printf("\n\tD[%d][2] = %d\n\t\t", i, D[i][2]);
    print_sume(v, i - 1, 0, 2, empty_sol, len, n);
    printf("\n\n");
  }
  // afisare rezultat final, care ne interesa
  printf("\nNumarul de sume care dau restul 0 la impartirea cu 3 este egal cu "
         "%d.\n",
         D[n][0]);
  printf("-----\n");
}

// functia main a programului
int main()
{
  // 1. k-garduri
  printf("\n--- K-GARDURI ---\n");
  int n = 6;       // lungime maxima a gardului
  int k = 2;       // lungimea unei singure scanduri (kx1)
  k_garduri(n, k); // apelarea functiei de rezolvare

  // 2. sume de rest 0 la impartirea cu 3
  printf("\n--- SUME MODULO 3 ---\n\n");
  int v[] = {3, 1, 2, 4}; // sirul de numere dat
  int len = 4;            // lungimea sirului dat
  sume(v, len);           // apelarea functiei de rezolvare
  return 0;
}

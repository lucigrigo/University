//  Curs : Programarea Calculatoarelor
//  Tema 1 : TetriBit
//  Grupa : 314CD
//  Nume si Prenume : Grigore Lucian-Florin

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void afisareHarta(unsigned long long);
void endGame(unsigned long long,
             int,
             int);
int margineDreapta(unsigned long long);
int margineStanga(unsigned long long);
unsigned long long miscareDreapta(unsigned long long,
                                  unsigned long long,
                                  int,
                                  unsigned long long *);
unsigned long long miscareStanga(unsigned long long,
                                 unsigned long long,
                                 int,
                                 unsigned long long *);
unsigned long long miscareStangaSimpla(unsigned long long,
                                       unsigned long long,
                                       int);
unsigned long long miscareDreaptaSimpla(unsigned long long,
                                        unsigned long long,
                                        int);
unsigned long long stergereLinie(unsigned long long,
                                 int);
unsigned long long cautareLinie(unsigned long long,
                                int *);
int miscareJos(unsigned long long,
               unsigned long long);
void initializareJoc(unsigned long long,
                     int);

int main() {
  unsigned long long n;
  int M;
  scanf("%llu %d", &n, &M);
  initializareJoc(n, M);
  return 0;
}

/*  Afiseaza harta , punand "#" in loc de 1
  si "." in loc de 0 */
void afisareHarta(unsigned long long a) {
  int i;
  for (i = 63; i >= 0; i--) {
    if (((a >> i) & 1) == 1) {
      printf("#");
    }
    if (((a >> i) & 1) == 0) {
      printf(".");
    }
    if ((i % 8) == 0) {
      printf("\n");
    }
  }
  printf("\n");
}

/*  Functia de sfarsit de joc poate
  afisa harta cu piesele de pe ea,
  afiseaza un mesaj de final de joc,
  calculeaza scorul obtinut si
  il afiseaza pe ecran */
void endGame(unsigned long long a,
             int completedLines,
             int OK) {
  if (OK) {
    afisareHarta(a);
  }
  int zeros = 0;
  int i;
  for (i = 63; i >= 0; i--) {
    if (((a >> i) & 1) == 0) {
      zeros++;
    }
  }
  float scor = sqrt(zeros) + pow(1.25, completedLines);
  printf("GAME OVER!\nScore:%.2f", scor);
}

/* Cauta daca exista o linie completa pe harta
 si o sterge, apeland functia stergereLinie */
unsigned long long cautareLinie(unsigned long long harta,
                                int *completedLines) {
  int i = 63;
  while (i >= 7) {
    int j = i;
    int linie = 1;
    while (j >= (i - 7)) {
      if (((harta >> j) & 1) == 0) {
        linie = 0;
      }
      j--;
    }
    if (linie == 1) {
      harta = stergereLinie(harta, i);
      *completedLines = *completedLines + 1;
    }
    i -= 8;
  }
  return harta;
}

//  Functia sterge o linie din harta
unsigned long long stergereLinie(unsigned long long harta,
                                 int linie) {
  unsigned long long maskSus = 0, maskJos = 0;
  if (linie != 63) {
    maskSus = harta >> (linie + 1);
    maskSus <<= (linie + 1);
    maskSus >>= 8;
  }
  if (linie != 7) {
    linie = (71 - linie);
    maskJos = harta << (linie);
    maskJos >>= (linie);
  }
  /* maskJos memoreaza ce se afla sub linia ce trebuie stearsa
     maskSus memoreaza ce se afla deasupra liniei ce trebuie stearsa
     in cazul particular in care trebuie stearsa ultima linie de jos,
     sau prima de sus , maskJos nu exista sau, respectiv, maskSus
     nu exista ( sunt egale cu 0 ) */
  return (maskJos | maskSus);
}

/*  Verifica daca piesa se loveste
  de marginea din dreapta a tablei */
int margineDreapta(unsigned long long b) {
  int OK = 1, dif = 8, i;
  for (i = 0; i <= 56; i += 8) {
    int j = i;
    while (j <= (i + 7)) {
      if ((((b >> j) & 1) == 1)
          && dif > (j - i)) {
        dif = (j - i);
      }
      j++;
    }
  }
  if (dif == 0) {
    OK = 0;
  }
  return OK;
}

/*  Verifica daca piesa se loveste
  de marginea din stanga a tablei */
int margineStanga(unsigned long long b) {
  int OK = 1, dif = 8, i;
  for (i = 63; i >= 7; i -= 8) {
    int j = i;
    while (j >= (i - 7)) {
      if ((((b >> j) & 1) == 1)
          && dif > (i - j)) {
        dif = (i - j);
      }
      j--;
    }
  }
  if (dif == 0) {
    OK = 0;
  }
  return OK;
}

/*  Misca piesa (jumatatea de jos a piesei) la stanga
  respectand restrictionarile cerute
  - misca si copia piesei (piesa in intregime),
  exact cat se poate misca si jumatatea de jos
  - aceasta functie este folosita doar atunci cand piesa
  ocupa mai mult de un rand , la inceputul realizarii
  miscarilor sale */
unsigned long long miscareStanga(unsigned long long a,
                                 unsigned long long b,
                                 int miscareData,
                                 unsigned long long *copie) {
  while (miscareData != 0
         && (a & (b << 1)) == 0
         && margineStanga(b)) {
    b <<= 1;
    *copie = *copie << 1;
    miscareData++;
  }
  return b;
}

/*  Misca piesa (jumatatea de jos a piesei) la dreapta
  respectand restrictionarile cerute
  - misca si copia piesei (piesa in intregime),
  exact cat se poate misca si jumatatea de jos
  - aceasta functie este folosita doar in cazul in care piesa
  ocupa mai mult de un rand , la inceputul realizarii
  miscarilor sale */
unsigned long long miscareDreapta(unsigned long long a,
                                  unsigned long long b,
                                  int miscareData,
                                  unsigned long long *copie) {
  while (miscareData != 0
         && (a & (b >> 1)) == 0
         && margineDreapta(b)) {
    miscareData--;
    *copie = *copie >> 1;
    b >>= 1;
  }
  return b;
}

/* Misca piesa in dreapta,
   respectand restrictionarile din enunt,
   - aceasta functie este folosita pentru cazul in care piesa
   ocupa un singur rand, sau dupa primele miscari ale unei piese
   mai mari de un rand */
unsigned long long miscareDreaptaSimpla(unsigned long long a,
                                        unsigned long long b,
                                        int miscareData) {
  while (miscareData != 0
         && (a & (b >> 1)) == 0
         && margineDreapta(b)) {
    miscareData--;
    b >>= 1;
  }
  return b;
}

/* Misca piesa in stanga,
   respectand restrictionarile din enunt,
   - aceasta functie este folosita pentru cazul in care piesa
   ocupa un singur rand, sau dupa primele miscari ale unei piese
   mai mari de un rand */
unsigned long long miscareStangaSimpla(unsigned long long a,
                                       unsigned long long b,
                                       int miscareData) {
  while (miscareData != 0
         && (a & (b << 1)) == 0
         && margineStanga(b)) {
    b <<= 1;
    miscareData++;
  }
  return b;
}

/*  Misca piesa in jos ,
    daca nu se loveste de un obstacol
    sau daca nu iese de pe harta */
int miscareJos(unsigned long long a,
               unsigned long long b) {
  int OK = 1;
  if (((b >> 8) & a)
      || ((b >> 8) == 0)) {
    OK = 0;
  }
  return OK;
}

/*  Functia de rulare a jocului contine
    - citirea fiecarei piese
    - citirea fiecarei miscari
    - realizarea miscarilor posibile ( apelarea altor functii )
    - cautarea unei linii complete ( apelarea cautareLinie )
    - afisarea hartii, daca este necesar ( apelarea afisareHarta )
    - terminarea jocului ( apelarea endGame ) */
void initializareJoc(unsigned long long a,
                     int M) {
  int completedLines = 0;
  //  Afisarea hartii primite ca input
  afisareHarta(a);

  int i;
  for (i = 0; i < M; i++) {
    // Piesa este b
    unsigned long long b;
    int miscare;
    int j = 0;
    scanf("%llu", &b);
    //  Cazul in care piesa nu ocupa mai mult de un rand
    if (b < 256) {
      if (((b << 56) & a) == 0) {
        b <<= 56;
      } else {
        /*  Daca piesa nu mai are loc pe harta,
          jocul se termina */
        endGame(a | b, completedLines, 1);
        return;
      }
    }

    //  Cazul in care piesa este mai mare de un singur rand
    //  este tratat separat
    else {
      unsigned long long copiePiesa = b;
      scanf("%d", &miscare);
      if (((b << 56) & a) == 0) {
        // b memoreaza doar jumatatea de jos a piesei
        b <<= 56;
        // copiePiesa memoreaza piesa in intregime
        copiePiesa <<= 48;
        // b si copiePiesa realizeaza aceleasi miscari in prima faza
        if (miscare < 0) {
          b = miscareStanga(a, b, miscare, &copiePiesa);
        }
        if (miscare > 0) {
          b = miscareDreapta(a, b, miscare, &copiePiesa);
        }
        if (!miscareJos(a, b) && !(miscareJos(a, copiePiesa))) {
          /* Jocul se intrerupe daca piesa nu incape
           in intregime pe harta */
          afisareHarta(a | b);
          endGame(a | copiePiesa, completedLines, 1);
          return;
        }
        if (miscareJos(a, b) == 1) {
          afisareHarta(a | b);
          b = b >> 8;
          // b devine piesa completa
          b = b | copiePiesa;
        }
        j++;
      } else {
        /*  Jocul se intrerupe daca piesa nu incape
          pe harta */
        b <<= 56;
        a = a | b;
        endGame(a, completedLines, 1);
        return;
      }
    }

    // Acest OK ramane 1 atat timp cat miscarile se pot realiza
    int OK = 1;

    //  Citeste fiecare miscare si o realizeaza
    while (j < 8) {
      scanf("%d", &miscare);
      if (OK == 1) {
        if (miscare < 0) {
          b = miscareStangaSimpla(a, b, miscare);
        }
        if (miscare > 0) {
          b = miscareDreaptaSimpla(a, b, miscare);
        }
        afisareHarta(a | b);
        if ((miscareJos(a, b) == 1) && (j != 7)) {
          b = b >> 8;
        } else {
          /* Miscarile nu se mai realizeaza daca piesa
           nu se mai poate misca in jos */
          OK = 0;
        }
      }
      j++;
    }
    a = a | b;
    unsigned long long copieA = a;
    a = cautareLinie(a, &completedLines);
    // Afiseaza harta daca au fost sterse una sau mai multe linii
    if (copieA != a) {
      afisareHarta(a);
    }
  }

  /*  Dupa mutarea tuturor pieselor,
      jocul se termina */
  endGame(a, completedLines, 0);
  return;
}

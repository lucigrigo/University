//  Curs Programarea Calculatoarelor
//  Tema 1 : TetriBit
//  Grupa : 314CD
//  Student : Grigore Lucian-Florin


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void afisareHarta(unsigned long long );
void endGame(unsigned long long,
             int ,
             int );
int margineDreapta(unsigned long long );
int margineStanga(unsigned long long );
unsigned long long miscareDreapta(unsigned long long,
                                  unsigned long long,
                                  int );
unsigned long long miscareStanga(unsigned long long,
                                 unsigned long long,
                                 int );
int miscareJos(unsigned long long,
               unsigned long long );
void initializareJoc(unsigned long long ,
                     int );


int main()
{
    unsigned long long n;
    int M;
    printf("Dati datele hartii:\n");
    scanf("%llu %d", &n ,&M);
    initializareJoc(n, M);
    return 0;
}


//Afiseaza harta
void afisareHarta(unsigned long long a)
{
    int i;
    for( i = 63 ; i >= 0 ; i-- ){
        if( ( (a>>i) & 1) == 1){
            printf("#");
        }
        if( ( (a>>i) &1) == 0){
            printf(".");
        }
        if( (i%8) == 0 ){
            printf("\n");
        }
    }
    printf("\n");
}


//Functia de sfarsit de joc poate
//afisa harta cu piesele de pe ea,
//afiseaza un mesaj de final de joc,
//calculeaza scorul obtinut si
//il afiseaza pe ecran
void endGame(unsigned long long a,
             int completedLines,
             int OK)
{
    if(OK){
        afisareHarta(a);
    }
    int zeros = 0;
    int i;
    for( i = 63 ; i >= 0 ; i-- )
    {
        if( ( (a>>i) &1) == 0 ){
            zeros++;
        }
    }
    float scor = sqrt(zeros)
    + pow( 1.25 , completedLines);
    printf("GAME OVER!\nScore:%.2f",scor);
}


//Calculeaza daca piesa se loveste
//de marginea din dreapta a tablei
int margineDreapta(unsigned long long b)
{
    int OK = 1 , dif = 8,i;
    for( i = 0 ; i <= 56 ; i += 8 ){
        int j = i;
        while( j <= (i+7) ){
            if( (((b>>j) &1) == 1)
               && dif > ( j-i )){
                dif = ( j-i );
            }
            j++;
        }
    }
    if(dif == 0){
        OK = 0;
    }
    return OK;
}


//Calculeaza daca piesa se loveste
//de marginea din stanga a tablei
int margineStanga(unsigned long long b)
{
    int OK = 1 , dif = 8 , i;
    for( i = 63 ; i >= 7 ; i -= 8 ){
        int j = i;
        while(j>=(i-7)){
            if( (((b>>j)&1) == 1)
               && dif > (i-j)){
                dif = (i-j);
            }
            j--;
        }
    }
    if( dif == 0 ){
        OK = 0;
    }
    return OK;
}


//Misca piesa la stanga
//respectand restrictionarile cerute
unsigned long long miscareStanga(unsigned long long a,
                                 unsigned long long b,
                                 int miscareData)
{
    while(miscareData != 0
          && (a&(b<<1)) == 0
          && margineStanga(b)){
        b <<= 1;
        miscareData++;
    }
    return b;
}


//Misca piesa la dreapta
//respectand restrictionarile cerute
unsigned long long miscareDreapta(unsigned long long a,
                                  unsigned long long b,
                                  int miscareData)
{
    while(miscareData != 0
          && (a&(b>>1)) == 0
          && margineDreapta(b)){
        miscareData--;
        b >>= 1;
    }
    return b;
}


//Misca piesa in jos , daca nu se loveste de un obstacol
//sau daca nu iese de pe harta
int miscareJos(unsigned long long a,
               unsigned long long b)
{
    int OK = 1;
    if(( (b>>8) &a )
       || ( (b>>8) ==0 )){
        OK = 0;
    }
    return OK;
}


//Functia de rulare a jocului
//contine : citirea fiecarei piese,
//citirea fiecarei miscari,
//executarea miscarii citite,
//prin apelarea altor functii si
//stergerea unei linii daca este completa
void initializareJoc(unsigned long long a,
                     int M)
{
    int completedLines = 0;
    //Afisarea hartii primite ca input,
    afisareHarta(a);
    
    int i;
    for(i=0;i<M;i++){
        unsigned long long b;
        int miscare;
        int j = 0;
        scanf("%llu",&b);
        //Cazul in care piesa nu ocupa mai mult de un rand
        if(b<256){
            if(((b<<56)&a) == 0){
                b <<= 56;
            }
            else{
                //Daca piesa nu mai are loc pe harta,
                //jocul se termina
                endGame(a|b, completedLines, 1);
                return ;
            }
        }
        
        //Cazul in care piesa este mai mare de un singur rand
        //este tratat separat
        
        else{
            unsigned long long copiePiesa = b;
            scanf("%d",&miscare);
            if(((b<<56)&a) == 0){
                b <<= 56;
                copiePiesa <<= 48;
                if(miscare < 0){
                    b = miscareStanga(a, b, miscare);
                    copiePiesa = miscareStanga(0, copiePiesa, miscare);
                }
                if(miscare > 0){
                    b = miscareDreapta(a, b, miscare);
                    copiePiesa = miscareDreapta(0, copiePiesa, miscare);
                }
                afisareHarta(a|b);
                if(!miscareJos(a, copiePiesa)){
                    //Jocul se intrerupe daca piesa nu incape
                    //in intregime pe harta
                    endGame(a|copiePiesa, completedLines, 1);
                    return ;
                }
                if(miscareJos(a,b) == 1){
                    b = b>>8;
                    b = b | copiePiesa;
                }
                j++;
            }
            else{
                //Jocul se intrerupe daca piesa nu incape
                //pe harta
                a=a|b;
                endGame(a, completedLines, 1);
                return ;
            }
        }
        
        int OK=1;
        
        while(j<8 && OK == 1){
            scanf("%d",&miscare);
            if(miscare<0){
                b = miscareStanga(a, b, miscare);
            }
            if(miscare>0){
                b = miscareDreapta(a, b, miscare);
            }
            afisareHarta(a|b);
            if((miscareJos(a,b) == 1) && j != 7){
                b = b>>8;
            }
            else{
                OK = 0;
            }
            j++;
        }
        
        a = a|b;
        
        //Cautarea liniei/liniilor complete,
        int k;
        for(k=63;k>=7;k=(k-8)){
            int linie = 1;
            int p;
            for(p=k;p>=(k-7);p--){
                if(((a>>p)&1) == 0){
                    linie = 0;
                }
            }
            if(linie == 1){
                //Stergerea unei linii complete
                unsigned long long mask = 0;
                p = (k-8);
                while(p >= 0){
                    mask=((a>>p) & 1);
                    p--;
                }
                a = a>>8;
                a = a | mask;
                completedLines++;
            }
        }
        afisareHarta(a);
    }
    
    //Dupa mutarea tuturor pieselor,
    //jocul se termina
    endGame(a, completedLines, 0);
    return ;
}

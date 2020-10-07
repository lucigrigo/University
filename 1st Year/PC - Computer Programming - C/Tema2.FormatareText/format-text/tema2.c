#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 1000


//  Am definit un tip boolean
typedef enum {false , true} bool;


int getMaxWordLength(char [*][*],int );
int endSearch(char [*][*],int );
int getMaxLineLength(char[*][*], int);
void applyParagraph(int, char[*][*], int, int);
void allignLeft(int, int, int, char [*][*]);
void allignRight(int, int, int, char[*][*]);
void center(int, int, int, char[*][*]);
void justify(int, int, int, char[*][*]);
void wrapText(int, int *, char[*][*]);
void paragraph(int, int, int, int, char[*][*]);
void list(int ,int ,char [*],char [*],char [*][*],int );
void applyNumberedList(char [*][*],int ,int ,int ,char [*]);
void applyBulletList(char [*][*],char [*],int );
void applyAlphabeticalList(char [*][*],bool ,int ,int ,int ,char [*]);
void orderedList(int ,int ,int ,char [*][*],char [*],char [*],char [*]);
void lexSort(char [*][*],int ,int ,int );
void lexInvertedSort(char [*][*],int ,int ,int );
bool linieGoala(int ,char [*][*]);
void citireComenzi(char [*][*],char [*][*] ,int *,char *[],int );
void invalidOperation(char [*][*],int ,char *[]);
void wrapError(char [*][*],int ,char *[]);
void trimTrailing(char *);
void formatareInput(char *);


int main(int argc, char *argv[]) {

  FILE *ffile;
  char buf[MAX], A[MAX][MAX];
  int linesNumber = 0, i;

  /*	Citirea argumentelor transmise si verificarea acestora
  ( folosind scheletul de cod ) */
  if (argc != 4) {
    fprintf(stderr,
            "Usage : %s operations_string "
            "input_file output_file\n",
            argv[0]);
    return -1;
  }
  ffile = fopen(argv[2], "r");
  if (ffile == NULL) {
    fprintf(stderr, "File \"%s\" not found \n", argv[2]);
    return -2;
  }
  while (fgets(buf, MAX, ffile)) {
    strcpy(A[linesNumber], buf);
    linesNumber++;
  }
  char I[MAX][MAX];
  i = 0;
  while(i<linesNumber){
    strcpy(I[i],A[i]);
    i++;
  }
  i = 0;
  while(i < linesNumber){
    trimTrailing(A[i]);
    i++;
  }

  citireComenzi(I,A,&linesNumber,argv,argc);

  ffile = fopen(argv[3], "w");
  i = 0;
  while(i < linesNumber){
    trimTrailing(A[i]);
    i++;
  }
  i = 0;
  while (i < linesNumber) {
    fputs(A[i], ffile);
    i++;
  }
  //	Inchiderea fisierului de input
  fclose(ffile);
  return 0;
}


//  Functia elimina trailing whitespaces de la sfarsitul unei linii
void trimTrailing(char *linie){

    int index = -1, i = 0;
    while(linie[i] != '\0'){
        if(linie[i] != ' ' && linie[i] != '\t' && linie[i] != '\n'){
            index= i;
        }

        i++;
    }
    linie[index + 2] = '\0';
    linie[index + 1] = '\n';
}

void formatareInput(char arg[MAX]){

  while((arg[0] == ' ') || (arg[0] == '\t')
        || (arg[0] == '\n') || (arg[0] == '\0')){
          int len = (strlen(arg) - 1);
          int j=0;
          while(j<len){
            arg[j] = arg[j+1];
            j++;
          }
          arg[len]='\0';
  }
  int j=0,len=strlen(arg);
  while(j<len){
    if(arg[j] == ','){
      while(arg[j+1] == ' '){
        int k = (j+1);
        len--;
        while(k<len){
          arg[k] = arg[k+1];
          k++;
        }
        arg[len] = '\0';
      }
    }
    if(arg[j] == ' '){
      while(arg[j+1] == ' '){
        int k = (j+1);
        len--;
        while(k<len){
          arg[k] = arg[k+1];
          k++;
        }
        arg[len] = '\0';
      }
    }
    j++;
  }
}


void citireComenzi(char F[MAX][MAX],
                   char A[MAX][MAX],
                   int *linesNumber,
                   char *argv[],
                   int argc){

	int nrComenzi=0,startLine=-1,endLine=-1;
  char s[10];
	char d[10];
  char listType,specialCharacter,ordering;
  strcpy(d," ");
  strcpy(s,",");
  formatareInput(argv[1]);
  char *comandaToken = strtok(argv[1],s);

	while(nrComenzi<10 && (comandaToken != NULL)){
		char *arg = strtok(comandaToken,d);
    bool used=false;
    nrComenzi++;

    if(arg!=NULL){
		if((strcmp(arg,"W")==0) || (strcmp(arg,"w")==0)){
			arg = strtok(NULL,d);
      if(arg == NULL){
        invalidOperation(F,*linesNumber,argv);
      }
      used=true;
			int maxLineLength = (int) strtol(arg,(char**)NULL,10);
      arg=strtok(NULL,d);
      if(arg != NULL){
        invalidOperation(F,*linesNumber,argv);
      }
			int maxWordLength = getMaxWordLength(A,*linesNumber);
			if(maxLineLength < maxWordLength){
				wrapError(F,*linesNumber,argv);
			} else {
				wrapText(maxLineLength,linesNumber,A);
			}
    }
  }

    if(arg!=NULL){
		if((strcmp(arg,"L")==0) || (strcmp(arg,"l")==0)){
			arg = strtok(NULL,d);
      used = true;
			startLine = 0;
      endLine = MAX;
			if(arg != NULL){
				startLine = (int) strtol(arg,(char**)NULL,10);
        arg = strtok(NULL,d);
  			if(arg != NULL){
  				endLine = (int) strtol(arg,(char**)NULL,10);
          if(startLine > endLine){
    				invalidOperation(F,*linesNumber,argv);
    			} else {
    				allignLeft(startLine,endLine,*linesNumber,A);
    			}
  			} else {
  				allignLeft(startLine,*linesNumber-1,*linesNumber,A);
  			}
			}
      if(arg == NULL) {
				allignLeft(startLine,endLine,*linesNumber,A);
			}
    }
  }

    if(arg!=NULL){
		if((strcmp(arg,"R")==0) || (strcmp(arg,"r")==0)){
			arg = strtok(NULL,d);
      used = true;
			startLine = -1;
      endLine = MAX;
			if(arg != NULL){
				startLine = (int) strtol(arg,(char**)NULL,10);
        arg = strtok(NULL,d);
  			if(arg != NULL){
  				endLine = (int) strtol(arg,(char**)NULL,10);
          if(startLine > endLine){
    				invalidOperation(F,*linesNumber,argv);
    			} else {
    				allignRight(startLine,endLine,*linesNumber,A);
    			}
  			} else {
  				allignRight(startLine,*linesNumber-1,*linesNumber,A);
  			}
			} else {
				allignRight(0,*linesNumber-1,*linesNumber,A);
			}
    }
  }

    if(arg!=NULL){
		if((strcmp(arg,"J")==0) || (strcmp(arg,"j")==0)){
			arg = strtok(NULL,d);
      used = true;
			startLine = -1;
      endLine = MAX;
			if( arg != NULL ){
				startLine = (int) strtol(arg,(char**)NULL,10);
        arg = strtok(NULL,d);
  			if(arg != NULL){
  				endLine = (int) strtol(arg,(char**)NULL,10);
          if(startLine > endLine){
    			invalidOperation(F,*linesNumber,argv);
    			} else {
    				justify(startLine,endLine,*linesNumber,A);
    			}
  			} else {
  				justify(startLine,*linesNumber-1,*linesNumber,A);
  			}
			} else {
				justify(0,MAX,*linesNumber,A);
			}
    }
  }

    if(arg!=NULL){
		if((strcmp(arg,"C")==0) || (strcmp(arg,"c")==0)){
			arg = strtok(NULL,d);
      used = true;
			startLine = -1;
      endLine = MAX;
			if(arg != NULL){
				startLine = (int) strtol(arg,(char**)NULL,10);
        arg = strtok(NULL,d);
  			if(arg != NULL){
  				endLine = (int) strtol(arg,(char**)NULL,10);
          if(startLine > endLine){
    				invalidOperation(F,*linesNumber,argv);
    			} else {
    				center(startLine,endLine,*linesNumber,A);
    			}
  			} else {
  				center(startLine,*linesNumber-1,*linesNumber,A);
  			}
			} else {
				center(0,*linesNumber-1,*linesNumber,A);
			}
    }
  }

    if(arg!=NULL){
		if((strcmp(arg,"P")==0) || (strcmp(arg,"p")==0)){
			arg = strtok(NULL,d);
      used = true;
      if(arg == NULL){
        invalidOperation(F,*linesNumber,argv);
      }
			int indentLength = (int)arg;
			arg = strtok(NULL,d);
			startLine = -1;
      endLine = MAX;
			if(arg != NULL){
				startLine = (int) strtol(arg,(char**)NULL,10);
        arg = strtok(NULL,d);
  			if(arg != NULL){
  				endLine = (int) strtol(arg,(char**)NULL,10);
          if(startLine > endLine){
    				invalidOperation(F,*linesNumber,argv);
    			} else {
    				paragraph(indentLength,startLine,endLine,*linesNumber,A);
    			}
  			} else {
  				paragraph(indentLength,startLine,*linesNumber-1,*linesNumber,A);
  			}
			} else {
				paragraph(indentLength,0,*linesNumber-1,*linesNumber,A);
			}
    }
  }

    if(arg!=NULL){
		if((strcmp(arg,"I")==0) || (strcmp(arg,"i")==0)){
			arg = strtok(NULL,d);
      used = true;
			listType = *arg;
			arg = strtok(NULL,d);
			specialCharacter = *arg;
			arg = strtok(NULL,d);
			startLine = -1;
      endLine = MAX;
			if(arg != NULL){
				startLine = (int) strtol(arg,(char**)NULL,10);
        arg = strtok(NULL,d);
  			if(arg != NULL){
  				endLine = (int) strtol(arg,(char**)NULL,10);
          if(startLine > endLine){
    				invalidOperation(F,*linesNumber,argv);
    			} else {
    				list(startLine,endLine,&listType,&specialCharacter,A,*linesNumber);
    			}
  			} else {
  				list(startLine,*linesNumber-1,&listType,&specialCharacter,A,*linesNumber);
  			}
			} else {
				list(0,*linesNumber-1,&listType,&specialCharacter,A,*linesNumber);
			}
    }
  }

    if(arg!=NULL){
		if((strcmp(arg,"O")==0) || (strcmp(arg,"o")==0)){
			arg = strtok(NULL,d);
      used = true;
			listType = *arg;
			arg = strtok(NULL,d);
			specialCharacter = *arg;
			arg = strtok(NULL,d);
			ordering = *arg;
			arg=strtok(NULL,d);
			startLine = -1;
      endLine = MAX;
			if(arg != NULL){
				startLine = (int) strtol(arg,(char**)NULL,10);
        arg = strtok(NULL,d);
  			if(arg != NULL){
  				endLine = (int) strtol(arg,(char**)NULL,10);
          if(startLine > endLine){
    				invalidOperation(F,*linesNumber,argv);
    			} else {
    				orderedList(startLine,endLine,*linesNumber,A,&listType,&specialCharacter,&ordering);
    			}
  			} else {
  				orderedList(startLine,*linesNumber-1,*linesNumber,A,&listType,&specialCharacter,&ordering);
  			}
			} else {
				orderedList(0,*linesNumber-1,*linesNumber,A,&listType,&specialCharacter,&ordering);
			}
    }
  }
    arg = strtok(NULL,d);
    if(arg != NULL){
      invalidOperation(F,*linesNumber,argv);
    }
    //  Testeaza daca a fost realizata vreo operatie
    if(used==false){
      invalidOperation(A,*linesNumber,argv);
    }
		comandaToken=strtok(NULL,s);
	}

  // Se testeaza daca au fost introduse mai mult de 10 operatii in comanda
	if(nrComenzi>=10){
		printf("Too many operations! Only the first 10 will be applied.\n");
	}
}


//  Functia returneaza ultimul indice de pe linia curenta
int endSearch(char A[MAX][MAX],int position){

	int j=0;
  while(A[position][j] != '\0'){
    if(A[position][j]=='\n'){
      return j;
    }
    j++;
	}
	return 0;
}


//  Functia returneaza lungimea celui mai lung cuvant din text
int getMaxWordLength(char B[MAX][MAX],int linesNumber){

	int i=0,max=-1;
	const char s[10]=" \n\t\0,.";
  char A[MAX][MAX];
  while(i<linesNumber){
    strcpy(A[i],B[i]);
    i++;
  }
  i=0;
	while(i<linesNumber){
		char* word = strtok(A[i],s);
		while(word != NULL){
			int len = strlen(word);
			if(len > max){
				max = strlen(word);
			}
			word = strtok(NULL,s);
		}
		i++;
	}
	return max;
}


//  Functia aplica in paragraph la linia indicata
void applyParagraph(int indentLength,
					          char A[MAX][MAX],
					          int linesNumber,
                    int position) {

  int j, len = endSearch(A,position), init = indentLength, dif;

  while (indentLength > 0) {
        j = len;
        indentLength--;
        dif = (init - indentLength);
        len++;
        while (j > 0) {
            A[position][j] = A[position][j - 1];
            j--;
        }
        A[position][len] = '\0';
        j = 0;
        while (j < dif) {
            A[position][j] = ' ';
            j++;
        }
  }
}


//  Functia returneaza lungimea celei mai lungi linii din text
int getMaxLineLength(char A[MAX][MAX],
					           int linesNumber) {

  int i = 0, max = 0;

  while (i < linesNumber) {
    if ((strlen(A[i])) > max) {
      max = strlen(A[i]);
    }
    i++;
  }

  return max;
}


//  Testeaza daca o linie este goala ( nu contine niciun caracter )
bool linieGoala(int position,
                char A[MAX][MAX]){

	int j=0,len=strlen(A[position]);
	bool noChar=true;

  /* Este testat daca sunt prezente litere, cifre sau alte
  caractere in linia curenta */
	while(j<len){
		if((A[position][j] <= (char)126) && (A[position][j] >= (char)33)){
			noChar=false;
		}
		j++;
	}

	return noChar;
}


//  Functia se ocupa de cazul in care se introduce o operatie invalida
void invalidOperation(char A[MAX][MAX],
                      int linesNumber,
                      char *argv[]){

	printf("Invalid operation!\n");
	int i;
	FILE *ffile;
	ffile = fopen(argv[3], "w");
	  i = 0;
    //  Fisierul de output este identic cu cel initial
	  while (i < linesNumber) {
	    fputs(A[i], ffile);
	    i++;
	  }
	  //	Inchiderea fisierului de input/output
	  fclose(ffile);
	exit(0);
}

/* Functia se ocupa de cazul in care wrapLength este mai mica decat lungimea
celui mai lung cuvant din text */
void wrapError(char A[MAX][MAX],
               int linesNumber,
               char *argv[]){

	printf("Cannot wrap!\n");
	int i;
	FILE *ffile;
	ffile = fopen(argv[3], "w");
	  i = 0;
    //  Fisierul de output este identic cu cel primit la input
	  while (i < linesNumber) {
	    fputs(A[i], ffile);
	    i++;
	  }
	  //	Inchiderea fisierului de input
	  fclose(ffile);
	exit(0);
}


//  Functia alineaza la stanga liniile intre limitele indicate
void allignLeft(int startLine,
				int endLine,
				int linesNumber,
				char A[MAX][MAX]) {

  int i = startLine,initLen,finalLen,dif;

  while ((i < linesNumber) && (i <= endLine)) {
	initLen=strlen(A[i]);
	dif=0;
    while ((A[i][0] == ' ') || (A[i][0] == '\t')){
      int j = 0;
      while (A[i][j + 1] != '\n') {
        A[i][j] = A[i][j + 1];
        j++;
      }
      dif++;
    }
    if(dif!=0){
		finalLen=(initLen - dif);
		int j=(finalLen-1);
		while(j<=initLen){
			A[i][j]= (char)0;
			j++;
		}
		A[i][finalLen-1]='\n';
    }
    i++;
  }
}


//  Functia alineaza la dreapta liniile indicate
void allignRight(int startLine,
				 int endLine,
				 int linesNumber,
         char A[MAX][MAX]) {

  int i, j, max, len, dif;
  // max memoreaza lungimea celei mai lungi linii
  max = getMaxLineLength(A, linesNumber);
  i = (startLine);

  while ((i < linesNumber) && (i <= endLine)) {
    len = strlen(A[i]);
    // dif este numarul de spatii care trebuie introdus
    dif = (max - len);
    //  se muta caracterele la dreapta de dif ori
    while (len < max) {
      j = len;
      len++;
      while (j > 0) {
        A[i][j] = A[i][j - 1];
        j--;
      }
    }
    A[i][len] = '\0';
    j = 0;
    // se introduc dif spatii libere inaintea caracterelor initiale
    while (j < dif) {
      A[i][j] = ' ';
      j++;
    }
    i++;
  }
}


//  Functia centreaza textul intre startLine si endLine
void center(int startLine,
			int endLine,
			int linesNumber,
			char A[MAX][MAX]) {

  int i, max, len, j, dif, memo;
  //  max memoreaza lungimea celei mai lungi linii din fisier
  max = getMaxLineLength(A, linesNumber);
  i = (startLine);

  while ((i < linesNumber) && (i <= endLine)) {
    len = (endSearch(A,i));
    /* dif memoreaza diferenta de caractere intre liniea curenta si
    cea mai lunga */
    dif = (max - len);
    // pentru a centra o linie , adaugam la inceput dif/2 spatii
    dif =(dif/2);
    memo = dif;
    // se muta elementele la dreapta de dif ori
    while (dif > 0) {
      j = len;
      len++;
      while (j > 0) {
        A[i][j] = A[i][j - 1];
        j--;
      }
      dif--;
    }
    A[i][len] = '\0';
    j = 0;
    // introducerea efectiva a spatiilor
    while (j < memo) {
      A[i][j] = ' ';
      j++;
    }
    i++;
  }
}


// Functia se ocupa de operatia de wrap a textului
void wrapText(int maxLineLength,
			        int *linesNumber,
			        char A[MAX][MAX]) {

  int i=0;
   char B[MAX][MAX];
   while(i<*linesNumber){
     strcpy(B[i],A[i]);
     i++;
   }
   char d[10];
   strcpy(d," \n\0\r");
   int len=0,j=0;
   char C[MAX][MAX];
   i=0;
   char *token = NULL;

   while(i<=*linesNumber){
     token = strtok(B[i],d);
     if(token == NULL){

       len = strlen(C[j]);
       C[j][len-1] = '\n';
       C[j][len] = '\0';
       C[j+1][0] = '\n';
       j+=2;
     }
     while(token != NULL){
       len = strlen(C[j]);
       if( (len + strlen(token) - 1) >= maxLineLength ){
         C[j][len-1] = '\n';
         j++;
         len = strlen(C[j]);
       } else {
        strcat(C[j],token);
        len = strlen(C[j]);
        C[j][len] = ' ';
        token = strtok(NULL,d);
       }
     }
     i++;
   }
   *linesNumber=(j-1);
   i=0;
   while(i<*linesNumber){
     strcpy(A[i],C[i]);
     i++;
   }
}


//  Realizeaza functia JUSTIFY din cerinta
void justify(int startLine,
			       int endLine,
			       int linesNumber,
			       char A[MAX][MAX]) {

  int i = (startLine), max = (getMaxLineLength(A, linesNumber));
  allignLeft(startLine,endLine,linesNumber,A);

  i = (startLine);
  while ((i < linesNumber) && (i <= endLine)){
	  int OK=1;
    //  Pentru ultima linie din fisier nu are loc justify
	  if(i==(linesNumber-1)){
        return;
    }
    //  Se verifica daca urmatoarea linie din fisier e goala
  	 while(strlen(A[i+1]) == 1){
       // Daca e goala, nu se realizeaza operatia justify asupra acesteia
  		  OK=0;
        i++;
  	  }
  	  if(OK==1){
  		  int len = (strlen(A[i]));
  		  int dif = (max - len);
  		  while(dif>0){
  			  int j=0;
  			  while(j<len && dif>0){
            //  Acolo unde gaseste un spatiu, mai insereaza unul
  				  if(A[i][j] == ' '){
  					  len++;
  					  int k=len;
  					  dif--;
              //  Se creeaza spatiu prin mutarea la dreapta a caracterelor
  					  while(k>j){
  						  A[i][k]=A[i][k-1];
  						  k--;
  					  }
              while(A[i][++j] == ' ');
  				  }
  				  j++;
  			  }
  		  }
  	  }
      i++;
  }
}


//  Realizeaza indentarea paragrafelor
void paragraph(int indentLength,
			         int startLine,
			         int endLine,
			         int linesNumber,
               char A[MAX][MAX]) {

	int i=(startLine);

	while ((i < linesNumber) && (i <= endLine)){
		if(A[i][0] == '\n' || i==0){
			if(i==0){
				applyParagraph(indentLength,A,linesNumber,0);
			} else {
				applyParagraph(indentLength,A,linesNumber,(i+1));
			}
		}
		i++;
	}
}


/*  Functia creeaza listele simple (care nu sunt ordonate)
    si apeleaza functii care sa aplice diferitele tipuri de liste */
void list(int startLine,
		int endLine,
		char listType[1],
		char specialCharacter[1],
		char A[MAX][MAX],
		int linesNumber){

	if(listType[0] == 'b'){
		int i = (startLine);

		while ((i < linesNumber) && (i <= endLine)){
			applyBulletList(A,specialCharacter,i);
			i++;
		}
	} else if(listType[0] == 'n'){
		applyNumberedList(A,startLine,endLine,linesNumber,specialCharacter);
	} else if(listType[0] == 'a'){
		applyAlphabeticalList(A,false,startLine,endLine,linesNumber,specialCharacter);
	} else if(listType[0] == 'A'){
		applyAlphabeticalList(A,true,startLine,endLine,linesNumber,specialCharacter);
	}
}


// Functia creeaza listele de tip bullet list
void applyBulletList(char A[MAX][MAX],
					 char specialCharacter[1],
					 int position){

	int k=2,len=strlen(A[position]),j;

	while (k > 0) {
    //  Se creeaza spatiu la inceputul randului
	    j = len;
	    k--;
	    len++;
	    while (j > 0) {
	      A[position][j] = A[position][j - 1];
	      j--;
	    }
	    A[position][len] = '\0';
	}
  //  Se insereaza la inceputul sirului caracterele speciale cerute
	A[position][0]=specialCharacter[0];
	A[position][1]=' ';
}


// Creeaza listele numerotate intre limitele specificate (startLine si endLine)
void applyNumberedList(char A[MAX][MAX],
					 int startLine,
					 int endLine,
					 int linesNumber,
					 char specialCharacter[1]){

	int i = (startLine),nr=1;
	char numberString[3];

	while ((i < linesNumber) && (i <= endLine)){
    // Cu sprintf transform numarul intr-un sir de caractere
		sprintf(numberString,"%d",nr);
    // indentLength se refera la spatiul care trebuie creat pentru fiecare rand
		int indentLength=3;
		if(nr>=10 && nr<100){
      //  indentLength devine 4 daca numarul de ordine este de 2 cifre
			indentLength=4;
		}
		nr++;
		applyParagraph(indentLength,A,linesNumber,i);
		A[i][0]=numberString[0];
		if(numberString[1] != '\0'){
			A[i][1]=numberString[1];
			A[i][2]=specialCharacter[0];
		} else {
			A[i][1]=specialCharacter[0];
		}
		i++;
	}
}


// Creeaza listele alfabetice intre limitele indicate ( startLine si endLine )
void applyAlphabeticalList(char A[MAX][MAX],
						   bool isCapsLockOn,
						   int startLine,
						   int endLine,
						   int linesNumber,
						   char specialCharacter[1]){
  //  Verifica daca lista trebuie sa contina litere de tipar sau litere mici
	int i = (startLine),index,len;
	if(isCapsLockOn == true){
    //  Indicele din codul ASCII pentru caracterul 'A'
		index=65;
	} else {
    //  Indicele din codul ASCII pentru caracterul 'a'
		index=97;
	}

	while((i<=endLine) && (i<linesNumber)){
		int k=3;
		len=strlen(A[i]);
		while (k > 0) {
			    int j = len;
			    k--;
			    len++;
			    while (j > 0) {
			      A[i][j] = A[i][j - 1];
			      j--;
			    }
			    A[i][len] = '\0';
			}
			A[i][0]=(char)index++;
			A[i][1]=specialCharacter[0];
			A[i][2]=' ';
		i++;
	}
}


/* Functia orderedList se ocupa de crearea listelor ordonate
   - decide daca ordonarea trebuie sa fie lexicografica sau invers lexico-
   grafica si apeleaza functiile de sortare corespunzatoare
   - apeleaza funtiile de aplicare a bullet list, numbered list sau
   alphabetical list */
void orderedList(int startLine,
				 int endLine,
				 int linesNumber,
				 char A[MAX][MAX],
				 char listType[1],
				 char specialCharacter[1],
				 char ordering[1]){

	if(ordering[0] == 'a'){
    //  Apeleaza functia de ordonare lexicografica
		lexSort(A,linesNumber,startLine,endLine);
	} else if(ordering[0] == 'z'){
    //  Apeleaza functia de ordonare invers lexicografica
		lexInvertedSort(A,linesNumber,startLine,endLine);
	}
  // Dupa ordonare, apeleaza aceleasi functii ca functia de creare a listelor
	if(listType[0] == 'b'){
			int i = (startLine);
			while ((i < linesNumber) && (i <= endLine)){
				applyBulletList(A,specialCharacter,i);
				i++;
			}
		} else if(listType[0] == 'n'){
			applyNumberedList(A,startLine,endLine,linesNumber,specialCharacter);
		} else if(listType[0] == 'a'){
			applyAlphabeticalList(A,false,startLine,endLine,linesNumber,specialCharacter);
		} else if(listType[0] == 'A'){
			applyAlphabeticalList(A,true,startLine,endLine,linesNumber,specialCharacter);
		}
}


/* Functia lexSort sorteaza lexicografic (A-Z)/(a-z) liniile cuprinse intre
   startLine si endLine */
void lexSort(char A[MAX][MAX],
			 int linesNumber,
			 int startLine,
			 int endLine){

	int i = (startLine);
  //  Se foloseste bubble sort pentru sortarea lexicografica
	while((i<=(endLine-1)) && (i<(linesNumber-1))){
	   int j=(i+1);
	   while((j<=endLine) && (j<linesNumber)){
       // Se foloseste functia strcmp pentru comparare
		    if((strcmp(A[i],A[j])) > 0){
			       char temp[MAX];
			       strcpy(temp,A[i]);
			       strcpy(A[i],A[j]);
			       strcpy(A[j],temp);
		    }
		    j++;
	     }
	i++;
	}
}


/* Functia lexInvertedSort sorteaza invers lexicografic (Z-A)/(z-a) liniile
   cuprinse intre startLine si endLine */
void lexInvertedSort(char A[MAX][MAX],
					 int linesNumber,
					 int startLine,
					 int endLine){

	int i = (startLine);
  //  Se foloseste bubble sort pentru sortarea invers lexicografica
	while((i<=(endLine-1)) && (i<(linesNumber-1))){
		int j=(i+1);
		while((j<=endLine) && (j<linesNumber)){
      //  Se foloseste functia strcmp pentru comparare
			if((strcmp(A[i],A[j])) < 0){
				char temp[MAX];
				strcpy(temp,A[i]);
				strcpy(A[i],A[j]);
				strcpy(A[j],temp);
			}
			j++;
		}
		i++;
	}
}

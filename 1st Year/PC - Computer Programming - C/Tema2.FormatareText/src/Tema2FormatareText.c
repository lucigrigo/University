#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000



typedef enum {false , true} bool;


int getMaxWordLength(char [*][*],int );
int endSearch(char [*][*],int );
int getMaxLineLength(char[*][*], int);
void applyParagraph(int, char[*][*], int, int);
void allignLeft(int, int, int, char[*][*]);
void allignRight(int, int, int, char[*][*]);
void center(int, int, int, char[*][*]);
void justify(int, int, int, char[*][*]);
void wrapText(int, int, char[*][*]);
void paragraph(int, int, int, int, char[*][*]);
void list(int ,int ,char [*],char [*],char [*][*],int );
void applyNumberedList(char [*][*],int ,int ,int ,char [*]);
void applyBulletList(char [*][*],char [*],int );
void applyAlphabeticalList(char [*][*],bool ,int ,int ,int ,char [*]);
void orderedList(int ,int ,int ,char [*][*],char [*],char [*],char [*]);
void lexSort(char [*][*],int ,int ,int );
void lexInvertedSort(char [*][*],int ,int ,int );
bool linieGoala(int ,char [*][*]);
void citireComenzi(char [*][*],char [*][*],int ,char *[],int );
void invalidOperation(char [*][*],int ,char *[]);
void wrapError(char [*][*],int ,char *[]);



int main(int argc, char *argv[]) {

  FILE *ffile;
  char buf[MAX], A[MAX][MAX], F[MAX][MAX];
  int linesNumber = 0, finalLinesNumber = 0, i;

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


  citireComenzi(A,A,linesNumber,argv,argc);

  //    allignLeft(1,9,linesNumber,A);
  //    allignRight(4,50,linesNumber,A);
  //    center(1,3,linesNumber,A);
  //    paragraph(4,1,10,linesNumber,A);
  // 	list(1,3,"A",")",A,linesNumber);
  //	list(1,3,"a",".",A,linesNumber);
  //	list(1,3,"b","*",A,linesNumber);
  //  	list(1,1000,"n",".",A,linesNumber);
  //  	orderedList(1,7,linesNumber,A,"b","-","z");
  //    orderedList(1,7,linesNumber,A,"n",".","a");
  //	justify(1, 100000, linesNumber, A);
  //    wrapText(60,linesNumber,A); !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


  ffile = fopen(argv[3], "w");
  i = 0;
  while (i < linesNumber) {
    fputs(A[i], ffile);
    i++;
  }
  //	Inchiderea fisierului de input
  fclose(ffile);
  return 0;
}



void citireComenzi(char F[MAX][MAX],char A[MAX][MAX],int linesNumber,char *argv[],int argc){

	int nrComenzi=0;
	const char s[2]=",";
	const char d[2]=" ";
	char *comandaToken;
	comandaToken=strtok(argv[1],s);

	while(nrComenzi<10 && comandaToken != NULL){
		char *arg = strtok(comandaToken,d);
		switch(*arg){

		case *"W":case *"w":
			arg = strtok(NULL,d);
			int maxLineLength = (int)arg;
			int maxWordLength = getMaxWordLength(A,linesNumber);
			if(maxLineLength < maxWordLength){
				wrapError(F,linesNumber,argv);
			} else {
				wrapText(maxLineLength,linesNumber,A);
				break;
			}
			break;

		case *"L":case *"l":
			arg = strtok(NULL,d);
			int startLine = -1,endLine = -1;
			if(arg != NULL){
				startLine = (int)arg;
			} else {
				allignLeft(1,linesNumber,linesNumber,A);
				break;
			}
			arg = strtok(NULL,d);
			if(arg != NULL){
				endLine = (int)arg;
			} else {
				allignLeft(startLine,linesNumber,linesNumber,A);
				break;
			}
			if(startLine > endLine){
				invalidOperation(F,linesNumber,argv);
			} else {
				allignLeft(startLine,endLine,linesNumber,A);
			}
			break;

		case *"R":case *"r":
			arg = strtok(NULL,d);
			startLine = -1,endLine = -1;
			if(arg != NULL){
				startLine = (int)arg;
			} else {
				allignRight(1,linesNumber,linesNumber,A);
				break;
			}
			arg = strtok(NULL,d);
			if(arg != NULL){
				endLine = (int)arg;
			} else {
				allignRight(startLine,linesNumber,linesNumber,A);
				break;
			}
			if(startLine > endLine){
				invalidOperation(F,linesNumber,argv);
			} else {
				allignRight(startLine,endLine,linesNumber,A);
			}
			break;

		case *"j":case *"J":
			arg = strtok(NULL,d);
			startLine = -1,endLine = -1;
			if(arg != NULL){
				startLine = (int)arg;
			} else {
				justify(1,linesNumber,linesNumber,A);
				break;
			}
			arg = strtok(NULL,d);
			if(arg != NULL){
				endLine = (int)arg;
			} else {
				justify(startLine,linesNumber,linesNumber,A);
				break;
			}
			if(startLine > endLine){
			invalidOperation(F,linesNumber,argv);
			} else {
				justify(startLine,endLine,linesNumber,A);
			}
			break;

		case *"c":case *"C":
			arg = strtok(NULL,d);
			startLine = -1,endLine = -1;
			if(arg != NULL){
				startLine = (int)arg;
			} else {
				center(1,linesNumber,linesNumber,A);
				break;
			}
			arg = strtok(NULL,d);
			if(arg != NULL){
				endLine = (int)arg;
			} else {
				center(startLine,linesNumber,linesNumber,A);
				break;
			}
			if(startLine > endLine){
				invalidOperation(F,linesNumber,argv);
			} else {
				center(startLine,endLine,linesNumber,A);
			}
			break;

		case *"p":case *"P":
			arg = strtok(NULL,d);
			int indentLength = (int)arg;
			arg = strtok(NULL,d);
			startLine = -1,endLine = -1;
			if(arg != NULL){
				startLine = (int)arg;
			} else {
				paragraph(indentLength,1,linesNumber,linesNumber,A);
				break;
			}
			arg = strtok(NULL,d);
			if(arg != NULL){
				endLine = (int)arg;
			} else {
				paragraph(indentLength,startLine,linesNumber,linesNumber,A);
				break;
			}
			if(startLine > endLine){
				invalidOperation(F,linesNumber,argv);
			} else {
				paragraph(indentLength,startLine,endLine,linesNumber,A);
			}
			break;

		case *"I":case *"i":
			arg = strtok(NULL,d);
			char listType = *arg;
			arg = strtok(NULL,d);
			char specialCharacter = *arg;
			arg = strtok(NULL,d);
			startLine = -1,endLine = -1;
			if(arg != NULL){
				startLine = (int)arg;
			} else {
				list(1,linesNumber,listType,specialCharacter,A,linesNumber);
				break;
			}
			arg = strtok(NULL,d);
			if(arg != NULL){
				endLine = (int)arg;
			} else {
				list(startLine,linesNumber,listType,specialCharacter,A,linesNumber);
				break;
			}
			if(startLine > endLine){
				invalidOperation(F,linesNumber,argv);
			} else {
				list(startLine,endLine,listType,specialCharacter,A,linesNumber);
			}
			break;

		case *"o":case *"O":
			arg = strtok(NULL,d);
			listType = *arg;
			arg = strtok(NULL,d);
			specialCharacter = *arg;
			arg = strtok(NULL,d);
			char ordering = *arg;
			arg=strtok(NULL,d);
			startLine = -1,endLine = -1;
			if(arg != NULL){
				startLine = (int)arg;
			} else {
				orderedList(1,linesNumber,linesNumber,A,listType,specialCharacter,ordering);
				break;
			}
			arg = strtok(NULL,d);
			if(arg != NULL){
				endLine = (int)arg;
			} else {
				orderedList(startLine,linesNumber,linesNumber,A,listType,specialCharacter,ordering);
				break;
			}
			if(startLine > endLine){
				invalidOperation(F,linesNumber,argv);
			} else {
				orderedList(startLine,endLine,linesNumber,A,listType,specialCharacter,ordering);
			}
			break;

		default:
			invalidOperation(F,linesNumber,argv);
			break;
		}
		comandaToken = strtok(NULL,s);
		nrComenzi++;
	}

	if(nrComenzi==10){
		printf("Too many operations! Only the first 10 will be applied.");
	}
}



int endSearch(char A[MAX][MAX],int position){

	int j=0,len=strlen(A[position]);
	while(j<len){
		if(A[position][j]=='\n'){
			return j;
		}
		j++;
	}
	return 0;
}



int getMaxWordLength(char A[MAX][MAX],int linesNumber){

	int i=0,max=-1;
	const char s[10]=" \n\t\0,.";
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



void applyParagraph(int indentLength,
					char A[MAX][MAX],
					int linesNumber,
                    int position) {

  int j, len = strlen(A[position]), init = indentLength, dif;

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



bool linieGoala(int position,char A[MAX][MAX]){

	int j=0,len=strlen(A[position]);
	bool noChar=true;

	while(j<len){
		if((A[position][j] <= (char)122) && (A[position][j] >= (char)97)){
			noChar=false;
		}
		j++;
	}

	return noChar;
}



void invalidOperation(char A[MAX][MAX],int linesNumber,char *argv[]){

	printf("Invalid operation!");
	int i;
	FILE *ffile;
	ffile = fopen(argv[3], "w");
	  i = 0;
	  while (i < linesNumber) {
	    fputs(A[i], ffile);
	    i++;
	  }
	  //	Inchiderea fisierului de input
	  fclose(ffile);
	exit(0);
}


void wrapError(char A[MAX][MAX],int linesNumber,char *argv[]){

	printf("Cannot wrap!");
	int i;
	FILE *ffile;
	ffile = fopen(argv[3], "w");
	  i = 0;
	  while (i < linesNumber) {
	    fputs(A[i], ffile);
	    i++;
	  }
	  //	Inchiderea fisierului de input
	  fclose(ffile);
	exit(0);
}



void allignLeft(int startLine,
				int endLine,
				int linesNumber,
				char A[MAX][MAX]) {

  int i = (startLine - 1),initLen,finalLen,dif;

  while ((i < linesNumber) && (i < endLine)) {
	initLen=strlen(A[i]);
	dif=0;
    while (A[i][0] == ' ') {
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



void allignRight(int startLine,
				 int endLine,
				 int linesNumber,
                 char A[MAX][MAX]) {

  int i, j, max, len, dif;
  max = getMaxLineLength(A, linesNumber);
  i = (startLine - 1);

  while ((i < linesNumber) && (i < endLine)) {
    len = strlen(A[i]);
    dif = (max - len);
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
    while (j < dif) {
      A[i][j] = ' ';
      j++;
    }
    i++;
  }
}



void center(int startLine,
			int endLine,
			int linesNumber,
			char A[MAX][MAX]) {

  int i, max, len, j, dif, memo;
  max = getMaxLineLength(A, linesNumber);
  i = (startLine - 1);

  while ((i < linesNumber) && (i < endLine)) {
    len = strlen(A[i]);
    dif = (max - strlen(A[i]));
    dif /= 2;
    memo = dif;
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
    while (j < memo) {
      A[i][j] = ' ';
      j++;
    }
    i++;
  }
}



void wrapText(int maxLineLength,
			  int linesNumber,
			  char A[MAX][MAX]) {

	int i=0;

	while(i < linesNumber){

		i++;
	}
}



void justify(int startLine,
			 int endLine,
			 int linesNumber,
			 char A[MAX][MAX]) {

  int i = (startLine - 1), max = (getMaxLineLength(A, linesNumber));
  allignLeft(startLine,endLine,linesNumber,A);

  while ((i < linesNumber) && (i < endLine)){
	  int OK=1;
	  if(i==(linesNumber-1)){
		  return;
	  }
	  if(linieGoala(i+1,A) == true){
		  OK=0;
		  i++;
	  }
	  if(OK==1){
		  int len = (strlen(A[i]));
		  int dif = (max - len);
		  while(dif>0){
			  int j=0;
			  while(j<len && dif>0){
				  if(A[i][j] == ' '){
					  len++;
					  int k=len;
					  dif--;
					  while(k>j){
						  A[i][k]=A[i][k-1];
						  k--;
					  }
					  j++;
				  }
				  j++;
			  }
		  }
	  }
	  i++;
  }
}



void paragraph(int indentLength,
			   int startLine,
			   int endLine,
			   int linesNumber,
               char A[MAX][MAX]) {

	int i=(startLine-1);

	while ((i < linesNumber) && (i < endLine)){
		if(A[i][0] == '\n' || i==0){
			if(i==0){
				applyParagraph(indentLength,A,linesNumber,0);
			} else {
				applyParagraph(indentLength,A,linesNumber,(i+1));
			}
			printf("%d",i);
		}
		i++;
	}
}



void list(int startLine,
		int endLine,
		char listType[1],
		char specialCharacter[1],
		char A[MAX][MAX],
		int linesNumber){

	if(listType[0] == 'b'){
		int i = (startLine - 1);

		while ((i < linesNumber) && (i < endLine)){
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



void applyBulletList(char A[MAX][MAX],
					 char specialCharacter[1],
					 int position){

	int k=2,len=strlen(A[position]),j;

	while (k > 0) {
	    j = len;
	    k--;
	    len++;
	    while (j > 0) {
	      A[position][j] = A[position][j - 1];
	      j--;
	    }
	    A[position][len] = '\0';
	}
	A[position][0]=specialCharacter[0];
	A[position][1]=' ';
}



void applyNumberedList(char A[MAX][MAX],
					 int startLine,
					 int endLine,
					 int linesNumber,
					 char specialCharacter[1]){

	int i = (startLine - 1),nr=1;
	char numberString[3];

	while ((i < linesNumber) && (i < endLine)){
		sprintf(numberString,"%d",nr);
		int indentLength=3;
		if(nr>=10 && nr<100){
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



void applyAlphabeticalList(char A[MAX][MAX],
						   bool isCapsLockOn,
						   int startLine,
						   int endLine,
						   int linesNumber,
						   char specialCharacter[1]){

	int i = (startLine - 1),index,len;
	if(isCapsLockOn == true){
		index=65;
	} else {
		index=97;
	}

	while((i<endLine) && (i<linesNumber)){
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



void orderedList(int startLine,
				 int endLine,
				 int linesNumber,
				 char A[MAX][MAX],
				 char listType[1],
				 char specialCharacter[1],
				 char ordering[1]){

	if(ordering[0] == 'a'){
		lexSort(A,linesNumber,startLine,endLine);
	} else if(ordering[0] == 'z'){
		lexInvertedSort(A,linesNumber,startLine,endLine);
	}

	if(listType[0] == 'b'){
			int i = (startLine - 1);

			while ((i < linesNumber) && (i < endLine)){
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



void lexSort(char A[MAX][MAX],
			 int linesNumber,
			 int startLine,
			 int endLine){

	int i = (startLine-1);

	while((i<(endLine-1)) && (i<(linesNumber-1))){
		int j=(i+1);
		while((j<endLine) && (j<linesNumber)){
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



void lexInvertedSort(char A[MAX][MAX],
					 int linesNumber,
					 int startLine,
					 int endLine){

	int i = (startLine-1);

		while((i<(endLine-1)) && (i<(linesNumber-1))){
			int j=(i+1);
			while((j<endLine) && (j<linesNumber)){
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

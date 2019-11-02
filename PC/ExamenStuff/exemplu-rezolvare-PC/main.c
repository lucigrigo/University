#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

typedef struct 
{
    int len;
    char* mesaj;
    char destinatar[256];
    unsigned long timestamp;
} TMesaj;

typedef struct 
{
    TMesaj* mesaje; 
    int nrMaxMesaje; 
    int nrCrtMesaje; 
    int dimSursa;
    char* sursa;
} TLog;

typedef struct {
    TMesaj* primMesaj;
    int nrMesaje;
} TMesajeAutor;

TLog* alocaLog(int nrMaxMesaje) 
{
    TLog* log = (TLog*) malloc(sizeof(TLog));
    if (log)
    {
        log->nrMaxMesaje = nrMaxMesaje;
        log->nrCrtMesaje = 0;
        log->mesaje = (TMesaj*) malloc(nrMaxMesaje * sizeof(TMesaj));
        log->dimSursa = 0;
        log->sursa = NULL;
    }
    
    return log;
}

void elibereazaLog(TLog* log)
{
    int i;
    
    if (log)
    {
        for (i = 0; i < log->nrCrtMesaje; i++)
        {
            //printf("%d\n", i);
            if (log->mesaje[i].mesaj)
            {
                free(log->mesaje[i].mesaj);
            }
        }
        free(log->mesaje);
        free(log->sursa);
        free(log);
        log = NULL;
    }
}

TLog* readLogFromFile(FILE* fin) 
{
    TLog* log;
    int nrMaximMesaje;
    
    fread(&nrMaximMesaje, sizeof(int), 1, fin);
    log = alocaLog(nrMaximMesaje);
    if (log)
    {
        int i;
        fread(&log->nrCrtMesaje, sizeof(int), 1, fin);
        if (log->nrCrtMesaje > log->nrMaxMesaje)
        {
            log->nrCrtMesaje = log->nrMaxMesaje; // just in case
        }
        fread(&log->dimSursa, sizeof(int), 1, fin);
        log->sursa = (char*) calloc(log->dimSursa + 1, sizeof(char));   // we have written one more char than log->dimSursa
        fread(log->sursa, sizeof(char), log->dimSursa + 1, fin);
        for (i = 0; i < log->nrCrtMesaje; i++)
        {
            printf("%d\n", i);
            // atentie aici, avem nevoie de pointer catre mesaj
            TMesaj* mesaj = &(log->mesaje[i]);
            fread(&mesaj->destinatar, sizeof(char), 256, fin);
            fread(&mesaj->timestamp, sizeof(unsigned long), 1, fin);
            fread(&mesaj->len, sizeof(int), 1, fin);
            mesaj->mesaj = (char*) malloc(mesaj->len * sizeof(char));
            fread(mesaj->mesaj, sizeof(char), mesaj->len, fin);
        }
    }
    
    return log;
}

void writeLogToFile(FILE* fout, TLog* log)
{
    int i;
    fwrite(&log->nrMaxMesaje, sizeof(int), 1, fout);
    fwrite(&log->nrCrtMesaje, sizeof(int), 1, fout);
    fwrite(&log->dimSursa, sizeof(int), 1, fout);
    fwrite(log->sursa, sizeof(char), log->dimSursa + 1, fout);  // also write '\0' to file
    
    for (i = 0; i < log->nrCrtMesaje; i++)
    {
        TMesaj mesaj = log->mesaje[i];
        fwrite(&mesaj.destinatar, sizeof(char), 256, fout);
        fwrite(&mesaj.timestamp, sizeof(unsigned long), 1, fout);
        fwrite(&mesaj.len, sizeof(int), 1, fout);
        fwrite(mesaj.mesaj, sizeof(char), mesaj.len, fout);
    }
}

void printLog(TLog* log)
{
    int i;
    printf("Nr maxim mesaje: %d\n", log->nrMaxMesaje);
    printf("Nr curent mesaje: %d\n", log->nrCrtMesaje);
    printf("Dimensiune sursa: %d\n", log->dimSursa);
    printf("Sursa: %s\n", log->sursa);
    
    for (i = 0; i < log->nrCrtMesaje; i++)
    {
        TMesaj mesaj = log->mesaje[i];
        printf ("Mesaj %d: lungime %d, text %s, autor %s\n", i, mesaj.len, mesaj.mesaj, mesaj.destinatar);
    }
}


char randomLetter(int numLetters)
{
    return 'a' + (rand() % numLetters);
}

char randomLetterEnglish()
{
    return randomLetter(26);
}

TLog* createRandomLog() 
{
    int nrMaximMesaje, nrCrtMesaje, i;
    char sursaTest[] = "sursaTestLog";
    TLog* log;
    
    srand(time(NULL));
    nrMaximMesaje = rand() % 15 + 1;            // no more than 15 messages in a log
    nrCrtMesaje = rand() % nrMaximMesaje + 1;   // at least one message
    
    log = alocaLog(nrMaximMesaje);
    log->nrCrtMesaje = nrCrtMesaje;
    log->dimSursa = strlen(sursaTest);
    // also write '\0' to file
    log->sursa = (char*)malloc((log->dimSursa + 1) * sizeof(char));
    strcpy(log->sursa, sursaTest);
    
    for (i = 0; i < nrCrtMesaje; i++)
    {
        //printf("%d\n", i);
        //getch();
        int j, length;
        log->mesaje[i].timestamp = time(NULL);
        //sprintf(log->mesaje[i].destinatar, "%c autor %d", randomLetter(2), i);    // lots of authors
        sprintf(log->mesaje[i].destinatar, "%c autor", randomLetter(2));            // only two authors
        length = (rand() % 30) + 1;
        log->mesaje[i].len = length;
        log->mesaje[i].mesaj = (char*) calloc(length, sizeof(char));
        for (j = 0; j < length - 1; j++)
        {
            log->mesaje[i].mesaj[j] = randomLetterEnglish();
        }
        log->mesaje[i].mesaj[length - 1] = '\0'; // just in case
    }
    
    return log;
}

int cmpMesaje(const void* a, const void* b)
{
   TMesaj* m1 = (TMesaj*) a;
   TMesaj* m2 = (TMesaj*) b;
   int cmpDestinatar = strcmp(m1->destinatar, m2->destinatar);
   if (cmpDestinatar)
   {
       return cmpDestinatar;
   }
   return m1->timestamp - m2->timestamp;
}

/*
 * Assertion: log is already sorted by author and timestamp
 */
TMesajeAutor intoarceMesajeAutor(TLog* log, const char* autor, unsigned long t1, unsigned long t2)
{
    int i;
    TMesajeAutor ma;
    ma.primMesaj = NULL;
    ma.nrMesaje = 0;
    for (i = 0; i < log->nrCrtMesaje; i++)
    {
        TMesaj mesaj = log->mesaje[i];
        if (!strcmp(autor, mesaj.destinatar) && mesaj.timestamp >= t1 && mesaj.timestamp <= t2)
        {
            if (!ma.primMesaj)
            {
                ma.primMesaj = &log->mesaje[i];
            }
            ma.nrMesaje++;
        }
    }
    
    return ma;
}

int main(int argc, char **argv)
{
    TLog *log, *log2;
    FILE *fin, *fout;
    fout = fopen("log.dat", "wb");
    if (fout)
    {
        log = createRandomLog();
        printf("Printing random generated data!\n");
        printLog(log);
        printf("Writing the generated data to file!\n");
        writeLogToFile(fout, log);
        fclose(fout);
        elibereazaLog(log);
    }    
    
    fin = fopen("log.dat", "rb");
    if (fin)
    {
        TMesajeAutor ma;
        printf("Reading data from file!\n");
        log2 = readLogFromFile(fin);
        printf("Printing read data from file (to verify what we read)!\n");
        printLog(log2);
        printf("Printing ordered messages from log!\n");
        qsort(log2->mesaje, log2->nrCrtMesaje, sizeof(TMesaj), cmpMesaje);
        printLog(log2);
        
        char* authorToFind = log2->mesaje[log2->nrCrtMesaje - 1].destinatar;
        printf("Finding messages by author %s!\n", authorToFind);
        ma = intoarceMesajeAutor(log2, authorToFind, 0, time(NULL));        // find all messages for author
        //ma = intoarceMesajeAutor(log2, authorToFind, 0, time(NULL));        // find no messages for author (interval is ill-defined)
        printf("Number of messages found: %d", ma.nrMesaje);
        
        fclose(fin);
        elibereazaLog(log2);
    }
     
	getch();
	return 0;
}

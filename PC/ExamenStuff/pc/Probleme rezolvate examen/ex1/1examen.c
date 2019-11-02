#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(1)

typedef struct
{
	char cnp[14];
	char numeElev[30];
	float medieElev;
} TElev;

typedef struct 
{
	short numeScoala;
	char numeDirector[30];
	float medieScoala;
	int nrElevi;
	float procent;
	// procentul de fete care au media peste 5 din numarul de fete total
	TElev *elevi;
} TScoala;

#pragma pack()

TScoala* alocaScoala(int nrElevi)
{
	TScoala *scoala = calloc(1, sizeof(TScoala));
	scoala->elevi = calloc(nrElevi, sizeof(TElev));
	return scoala;
}

TScoala** alocaScoli(int nrScoli) 
{
	TScoala **scoli = calloc(nrScoli, sizeof(TScoala *));
	return scoli;
}

TScoala** citireScoli(int *nrScoli)
{
	FILE *input = fopen("1examen.txt", "rt");
	fscanf(input, "%d", &*nrScoli);
	TScoala **scoli = alocaScoli(*nrScoli);

	short numeScoala;
	char numeDirector[30];
	float medieScoala;
	int nrElevi;

	int i, j;
	for(i = 0; i < *nrScoli; i++) {
		fscanf(input, "%hd", &numeScoala);
		fscanf(input, "%s", numeDirector);
		fscanf(input, "%f", &medieScoala);
		fscanf(input, "%d", &nrElevi);
		scoli[i] = alocaScoala(nrElevi);
		scoli[i]->numeScoala = numeScoala;
		strcpy(scoli[i]->numeDirector, numeDirector);
		scoli[i]->medieScoala = medieScoala;
		scoli[i]->nrElevi = nrElevi;
		for(j = 0; j < scoli[i]->nrElevi; j++) {
			fscanf(input, "%s", scoli[i]->elevi[j].cnp);
			fscanf(input, "%s", scoli[i]->elevi[j].numeElev);
			fscanf(input, "%f", &scoli[i]->elevi[j].medieElev);
		}
	}

	fclose(input);
	return scoli;
}

void afisare(TScoala **scoli, int nrScoli) 
{
	int i, j;
	printf("%d\n", nrScoli);
	for(i = 0; i < nrScoli; i++) {
		printf("%hd\n", scoli[i]->numeScoala);
		printf("%s\n", scoli[i]->numeDirector);
		printf("%f\n", scoli[i]->medieScoala);
		printf("%f%\n", scoli[i]->procent);
		printf("%d\n", scoli[i]->nrElevi);
		for(j = 0; j < scoli[i]->nrElevi; j++) {
			printf("%s\n", scoli[i]->elevi[j].cnp);
			printf("%s\n", scoli[i]->elevi[j].numeElev);
			printf("%f\n\n", scoli[i]->elevi[j].medieElev);
		}
		printf("\n");
	}
}

void calculeazaMediaScoala(TScoala** scoli, int nrScoli) 
{
	int i, j; float sum;
	for(i = 0; i < nrScoli; i++)
		if(scoli[i]->medieScoala == 0) {
			sum = 0;
			for(j = 0; j < scoli[i]->nrElevi; j++)
				sum += scoli[i]->elevi[j].medieElev;
			scoli[i]->medieScoala = sum / scoli[i]->nrElevi;
		}
}

void interschimbare(TScoala* aux, TScoala *scoala)
{
	aux->numeScoala = scoala->numeScoala;
	strcpy(aux->numeDirector, scoala->numeDirector);
	aux->medieScoala = scoala->medieScoala;
	aux->nrElevi = scoala->nrElevi;
	aux->elevi = calloc(scoala->nrElevi, sizeof(TElev));
	aux->procent = scoala->procent;
	for (int i = 0; i < scoala->nrElevi; i++) {
		strcpy(aux->elevi[i].cnp, scoala->elevi[i].cnp);
		strcpy(aux->elevi[i].numeElev, scoala->elevi[i].numeElev);
		aux->elevi[i].medieElev = scoala->elevi[i].medieElev;
	}
}

void sorteazaScoliFetePromovate(TScoala** scoli, int nrScoli)
{
	int i, j, nrf, nrfp;
	for(i = 0; i < nrScoli; i++) {
		nrf = nrfp = 0;
		for(j = 0; j < scoli[i]->nrElevi; j++)
			if(scoli[i]->elevi[j].cnp[0] % 2 == 0) {
				nrf++;
				if(scoli[i]->elevi[j].medieElev >= 5) {
					nrfp++;
				}
			}
		if(nrf != 0)
			scoli[i]->procent = 100 * nrfp / nrf;
	}

	TScoala *aux = calloc(1, sizeof(TScoala));
	for(i = 0; i < nrScoli - 1; i++)
		for(j = i + 1; j < nrScoli; j++)
			if(scoli[i]->procent > scoli[j]->procent) {
				interschimbare(aux, scoli[i]);
				interschimbare(scoli[i], scoli[j]);
				interschimbare(scoli[j], aux);
			}

	free(aux->elevi);
	free(aux);
}

void dezalocaScoli(TScoala** scoli, int nrScoli)
{
	int i, j;
	for(i = 0; i < nrScoli; i++) {
		free(scoli[i]->elevi);
		free(scoli[i]);
	}
	free(scoli);
}

int main()
{
	int nrScoli;
	TScoala **scoli = citireScoli(&nrScoli);

	afisare(scoli, nrScoli);

	calculeazaMediaScoala(scoli, nrScoli);

	afisare(scoli, nrScoli);

	sorteazaScoliFetePromovate(scoli, nrScoli);

	afisare(scoli, nrScoli);

	return 0;
}
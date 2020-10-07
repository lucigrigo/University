#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#pragma pack(1)

typedef struct 
{
	char numeVolum[30];
	short anPublicare;
	uint8_t stare;
	int idPersoana;
} TVolum;

typedef struct 
{
	char numeAutor[30];
	char codTara[3];
	int nrVolume;
	TVolum *volume;
} TAutor;

#pragma pack()

TAutor* alocaAutor(int nrVolume)
{
	TAutor *autor = calloc(1, sizeof(TAutor));
	autor->volume = calloc(nrVolume, sizeof(TVolum));
	return autor;
}

TAutor** alocaAutori(int nrAutori, int* nrVolumeAutor)
{
	TAutor **autori = calloc(nrAutori, sizeof(TAutor *));
	int i;
	for(i = 0; i < nrAutori; i++)
		autori[i] = alocaAutor(nrVolumeAutor[i]);
	return autori;
}

TAutor** citireAutori(int *nrAutori)
{
	FILE *input = fopen("2examen.txt", "rt");
	fscanf(input, "%d", &*nrAutori);

	int *nrVolumeAutor = calloc(*nrAutori, sizeof(int));
	int i;
	for(i = 0; i < *nrAutori; i++)
		fscanf(input, "%d", &nrVolumeAutor[i]);

	TAutor **autori = alocaAutori(*nrAutori, nrVolumeAutor);

	int j;
	for(i = 0; i < *nrAutori; i++) {
		fscanf(input, "%s", autori[i]->numeAutor);
		fscanf(input, "%s", autori[i]->codTara);
		autori[i]->nrVolume = nrVolumeAutor[i];
		for(j = 0; j < nrVolumeAutor[i]; j++) {
			fscanf(input, "%s", autori[i]->volume[j].numeVolum);
			fscanf(input, "%hd", &autori[i]->volume[j].anPublicare);
			fscanf(input, "%hhu", &autori[i]->volume[j].stare);
			fscanf(input, "%d", &autori[i]->volume[j].idPersoana);
		}
	}
	free(nrVolumeAutor);
	fclose(input);
	return autori;
}

void afisare(TAutor **autori, int nrAutori)
{
	printf("%d\n", nrAutori);
	int i, j;
	for(i = 0; i < nrAutori; i++) {
		printf("%s\n", autori[i]->numeAutor);
		printf("%s\n", autori[i]->codTara);
		printf("%d\n\n", autori[i]->nrVolume);
		for(j = 0; j < autori[i]->nrVolume; j++) {
			printf("%s\n", autori[i]->volume[j].numeVolum);
			printf("%hd\n", autori[i]->volume[j].anPublicare);
			printf("%hhu\n", autori[i]->volume[j].stare);
			printf("%d\n\n", autori[i]->volume[j].idPersoana);
		}
		printf("\n");
	}
}

void nrVolumeTara(TAutor** autori, int nrAutori, char codTari[])
{
	int i; int nr = 0;
	for(i = 0; i < nrAutori; i++)
		if(!strcmp(codTari, autori[i]->codTara)) nr += autori[i]->nrVolume;
	printf("%d\n", nr);
}

int maxVolume(TAutor** autori, int nrAutori)
{
	uint8_t s;
	int i, j;

	int *id = calloc(10001, sizeof(int));

	for(i = 0; i < nrAutori; i++) {

		for(j = 0; j < autori[i]->nrVolume; j++) {
			s = autori[i]->volume[j].stare;
			s <<= 1; // s = s << 1;
			s >>= 7;
			if(s == 1)
				id[autori[i]->volume[j].idPersoana]++;
			}
	}

	int max = id[1], ID = 1;
	for(i = 2; i < 10000; i++)
		if(id[i] > max) {
			max = id[i];
			ID = i;
		}
	free(id);

	return ID;
}

void dezalocaAutori(TAutor** autori, int nrAutori)
{
	int i;
	for(i = 0; i < nrAutori; i++) {
		free(autori[i]->volume);
		free(autori[i]);
	}
	free(autori);
}

int main()
{
	int nrAutori;
	TAutor **autori = citireAutori(&nrAutori);

	afisare(autori, nrAutori);

	nrVolumeTara(autori, nrAutori, "UK");

	printf("%d\n", maxVolume(autori, nrAutori));

	dezalocaAutori(autori, nrAutori);

	return 0;
}
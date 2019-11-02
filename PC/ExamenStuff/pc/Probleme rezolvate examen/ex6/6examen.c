#include <stdio.h>
#include <stdlib.h>

#pragma pack(1)

typedef struct
{
	unsigned int varsta;
	unsigned int nr_loc;
	char nume[30];
	unsigned int nrSurseVenit;
	double surseVenit[100];
	double (*calculeazaTaxa)(double *venit, unsigned int nrSurseVenit);
} TPersoana;

typedef struct
{
	int nrLocuitori;	
	TPersoana *persoane;
	double taxaMedie;
} TPopulatie;

#pragma pack()

double taxaMica(double *venit, unsigned int nrSurseVenit);
double taxaMedie(double *venit, unsigned int nrSurseVenit);
double taxaMare(double *venit, unsigned int nrSurseVenit);

TPopulatie *alocaPopulatie(int nrPersoane)
{
	TPopulatie *populatie = calloc(1, sizeof(TPopulatie));
	populatie->persoane = calloc(nrPersoane, sizeof(TPersoana));
	return populatie;
}

TPopulatie **alocaPopulatii(unsigned int nrPopulatii, int *nrPersoane) 
{
	TPopulatie **populatii = calloc(nrPopulatii, sizeof(TPopulatie *));
	int i;
	for(i = 0; i < nrPopulatii; i++)
		populatii[i] = alocaPopulatie(nrPersoane[i]);
	
	return populatii;
}

void dezalocaPopulatii(TPopulatie **populatii, unsigned int nrPopulatii)
{
	int i;
	for(i = 0; i < nrPopulatii; i++) {
		free(populatii[i]->persoane);
		free(populatii[i]);
	}
	free(populatii);
}

TPopulatie **citirePopulatii(FILE *f, unsigned int *nrPopulatii)
{
	fscanf(f, "%d", nrPopulatii);

	unsigned int varsta;
	unsigned int nr_loc;
	char nume[30];
	unsigned int nrSurseVenit;
	double surseVenit[100];


	TPopulatie **populatii = calloc(*nrPopulatii, sizeof(TPopulatie *));

	int i, j, k;
	for(i = 0; i < *nrPopulatii; i++) {
		fscanf(f, "%u", &nr_loc);
		populatii[i] = alocaPopulatie(nr_loc);
		for(j = 0; j < nr_loc; j++) {
			fscanf(f, "%d", &populatii[i]->persoane[j].varsta);
			fscanf(f, "%s", populatii[i]->persoane[j].nume);
			fscanf(f, "%d", &populatii[i]->persoane[j].nrSurseVenit);
			for(k = 0; k < populatii[i]->persoane[j].nrSurseVenit; k++)
				fscanf(f, "%lf", &populatii[i]->persoane[j].surseVenit[k]);
		}
	}

	return populatii;
}

void modificaTaxa(TPopulatie *populatie, unsigned int nrPersoane)
{
	int i, j;
	for(i = 0; i < populatie->nrLocuitori; i++) {
		TPersoana *pers = &populatie->persoane[i];
		if(pers->nrSurseVenit <= 2) {
			for(j = 0; j < pers->nrSurseVenit; j++)
				if(pers->surseVenit[j] > 1600)
					break;
			if(j == pers->nrSurseVenit) 
				pers->calculeazaTaxa = taxaMica;
		} 
		else if(pers->nrSurseVenit <= 5) {
			for(j = 0; j < pers->nrSurseVenit; j++)
				if(pers->surseVenit[j] > 3500)
					break;
			if(j != pers->nrSurseVenit) 
				pers->calculeazaTaxa = taxaMedie;
		}
		else 
			pers->calculeazaTaxa = taxaMare;
	}
}

int compare(const void *a, const void *b)
{
	TPopulatie **el1 = (TPopulatie **)a;
	TPopulatie **el2 = (TPopulatie **)b;
	
	return (*el1)->taxaMedie - (*el2)->taxaMedie;
}

void sortarePopulatii(TPopulatie **populatii, unsigned int nrPopulatii)
{
	int i, j;
	for(i = 0; i < nrPopulatii; i++) {
		double taxaTotala = 0;
		for(j = 0; j < populatii[i]->nrLocuitori; j++) {
			TPersoana *pers = &populatii[i]->persoane[j];
			taxaTotala += pers->calculeazaTaxa(pers->surseVenit, pers->nrSurseVenit);
		}
		populatii[i]->taxaMedie = taxaTotala / populatii[i]->nrLocuitori;
	}

	qsort(populatii, sizeof(TPopulatie *), nrPopulatii, compare);
}

int main()
{
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#pragma pack(1)

typedef struct 
{
	unsigned char id;
	double x, y;
} TPunct2D;

typedef struct 
{
	char nume[50];
	unsigned int nrPuncte;
	TPunct2D *puncte;
	double (*funArie)(TPunct2D *puncte, int nrPuncte);
} TFigura2D;

#pragma pack()

extern double funcArieTriEchi(TPunct2D *puncte, int nrPuncte);
extern double funcArieFiguraComplexa(TPunct2D *puncte, int nrPuncte);
extern double funcAriePatrat(TPunct2D *puncte, int nrPuncte);


TFigura2D *alocaFigura(unsigned int nrPuncte)
{
	TFigura2D *figura = calloc(1, sizeof(TFigura2D));

	figura->nrPuncte = nrPuncte;
	figura->puncte = calloc(nrPuncte, sizeof(TPunct2D));

	return figura;
}

TFigura2D **alocaPlansa(unsigned int nrFiguri, unsigned int *nrPuncte)
{
	TFigura2D **plansa = calloc(nrFiguri, sizeof(TFigura2D *));

	int i;
	for(i = 0; i < nrFiguri; i++)
		plansa[i] = alocaFigura(nrPuncte[i]);

	return plansa;
}

void dezalocaPlansa(TFigura2D **plansa, unsigned int nrFiguri)
{
	int i, j;
	for(i = 0; i < nrFiguri; i++) {
		for(j = 0; j < plansa[i]->nrPuncte; j++){
			free(plansa[i]->puncte);
			free(plansa[i]);
		}
		free(plansa[i]);
	}
	free(plansa);

}

TFigura2D **citirePlansa(unsigned int *nrFiguri, FILE *input)
{

	fread(nrFiguri, sizeof(unsigned int), 1, input);

	unsigned int *nrPuncte = calloc(*nrFiguri, sizeof(unsigned int));

	fread(nrPuncte, sizeof(unsigned int), *nrFiguri, input);

	TFigura2D **plansa = alocaPlansa(*nrFiguri, nrPuncte);

	int i, j;
	for(i = 0; i < *nrFiguri; i++) {
		fread(plansa[i]->nume, sizeof(char), 50, input);
		for(j = 0; j < nrPuncte[i]; j++) {
			fread(&plansa[i]->puncte[j].x, sizeof(double), 1, input);
			fread(&plansa[i]->puncte[j].y, sizeof(double), 1, input);
			fread(&plansa[i]->puncte[j].id, sizeof(unsigned char), 1, input);
		}
		/*
		 * Consideram ca exista padding in fisier
		 * fread(plansa[i]->puncte[j], sizeof(TPunct2D), 1, input);
		 */
	}

	free(nrPuncte);
	return plansa;
}

double distanta(TPunct2D *a, TPunct2D *b)
{
	return sqrt((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
}

void asocieazaFunctieArie(TFigura2D **plansa, unsigned int nrFiguri)
{
	int i;
	for(i = 0; i < nrFiguri; i++) {
		if(plansa[i]->nrPuncte == 3) {
			double dist_p01 = distanta(&plansa[i]->puncte[0], &plansa[i]->puncte[1]);
			double dist_p12 = distanta(&plansa[i]->puncte[1], &plansa[i]->puncte[2]);
			double dist_p20 = distanta(&plansa[i]->puncte[2], &plansa[i]->puncte[0]);
			if(dist_p01 == dist_p12 && dist_p12 == dist_p20)
				plansa[i]->funArie = funcArieTriEchi;
		}
		else if(plansa[i]->nrPuncte == 4) {
			double dist_p01 = distanta(&plansa[i]->puncte[0], &plansa[i]->puncte[1]);
			double dist_p12 = distanta(&plansa[i]->puncte[1], &plansa[i]->puncte[2]);
			double dist_p23 = distanta(&plansa[i]->puncte[2], &plansa[i]->puncte[3]);
			double dist_p30 = distanta(&plansa[i]->puncte[3], &plansa[i]->puncte[0]);
			if(dist_p01 == dist_p12 && dist_p12 == dist_p23 && dist_p23 == dist_p30) {
				double dist_p02 = distanta(&plansa[i]->puncte[0], &plansa[i]->puncte[2]);
				if(dist_p02 == dist_p30 * sqrt(2))
					plansa[i]->funArie = funcAriePatrat;
			}
		}
		else plansa[i]->funArie = funcArieFiguraComplexa;
	}
}

int compare(const void *a, const void *b)
{
	TFigura2D **el1 = (TFigura2D **)a;
	TFigura2D **el2 = (TFigura2D **)b;

	return  (*el1)->funArie((*el1)->puncte, (*el1)->nrPuncte) -
		(*el2)->funArie((*el2)->puncte, (*el2)->nrPuncte);
}

void sorteazaFiguriArie(TFigura2D **plansa, unsigned int nrFiguri)
{
	qsort(plansa, sizeof(TFigura2D *), nrFiguri, compare);
}

int main()
{
	return 0;
}
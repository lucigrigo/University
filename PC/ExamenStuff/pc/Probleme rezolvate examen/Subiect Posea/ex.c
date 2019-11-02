#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
	unsigned int id;
	char *nume;
} TPers;

typedef struct
{
	TPers *pers;
	char rol;
} TRol;

typedef struct 
{
	TRol roluri[50];
	int nrCrtActori;
	char *numeFilm;
} TFilm;

typedef struct 
{
	TPers *pers;
	TFilm *filme;
	int nrCrtActori, nrCrtFilme;
	int nrMaxActori, nrMaxFilme;
} TColectie;

TColectie *creazaColectie(int nrMaxFilme, int nrMaxActori)
{
	TColectie *colectie = calloc(1, sizeof(TColectie));

	colectie->nrMaxActori = nrMaxActori;
	colectie->nrMaxFilme = nrMaxFilme;

	colectie->pers = calloc(nrMaxActori, sizeof(TPers));
	colectie->filme = calloc(nrMaxFilme, sizeof(TFilm));
	return colectie;
}

void adaugaRol(TFilm *f, TPers *p, char rol)
{
	int i;
	for (i = 0; i < f->nrCrtActori; i++)
		if (f->roluri[i].pers == p) {
			f->roluri[i].rol |= rol;
			return;
		}

	f->nrCrtActori++;
	f->roluri[i].pers = p;
	f->roluri[i].rol = rol;
}

int verificaExistenta(TPers *vect, TPers *pers, int n)
{
	int i;
	for (i = 0; i < n; i++)
		if (strcmp(vect[i].nume, pers->nume) == 0)
			return 1;

	return 0;
}

TPers *cautaActorRegizor(TColectie *c, int *nrPers)
{
	int n = 0;

	char x = 128 + 64;

	TPers *vect = calloc(c->nrCrtActori, sizeof(TPers));

	int i, j;
	for (i = 0; i < c->nrCrtFilme; i++)
		for(j = 0; j < c->filme[i].nrCrtActori; j++)
			if (c->filme[i].roluri[j].rol & x == x)
				if (!verificaExistenta(vect, c->filme[i].roluri[j].pers, n)) {
					vect[n] = *(c->filme[i].roluri[j].pers);
					n++;
				}

	*nrPers = n;
	return vect;
}

int AddRegizor(TColectie *c, TFilm *f, unsigned int id)
{
	int i;
	for (i = 0; i < c->nrCrtActori; i++)
		if (c->pers[i].nume && c->pers[i].id == id)
			break;

	if (i == c->nrCrtActori) return 0;

	adaugaRol(f, &(c->pers[i]), 64);
	return 1;
}

int eliminaPers(TColectie *c, int (*fcond)(TPers *))
{
	int i;
	for (i = 0; i < c->nrCrtActori; i++)
		if (fcond(&(c->pers[i]))) {
			int j, k, l;
			for (j = 0; j < c->nrCrtFilme; j++)
				for (k = 0; k < c->filme[j].nrCrtActori; k++)
					if (c->filme[j].roluri[k].pers == &(c->pers[i])) {
						for (l = k + 1; l < c->filme[j].nrCrtActori; l++)
							c->filme[j].roluri[l - 1] = c->filme[j].roluri[l];
						c->filme[j].nrCrtActori--;
						break;
					}

			free(c->pers[i].nume);
			c->pers[i].nume = NULL;
			c->pers[i].id = 0;
			// Cand se adauga o noua persoana se va verifica daca exista o pozitie libera
			// in vector inainte de a se adauga la final. Daca asta se intampla, numarul
			// curent de actori nu va creste.
			return 1;
		}

	return 0;
}

void elibereazaColectie(TColectie *colectie)
{
	int i;
	for (i = 0; i < colectie->nrCrtFilme; i++)
		free(colectie->filme[i].numeFilm);
	free(colectie->filme);

	for(i = 0; i < colectie->nrCrtActori; i++)
		if(colectie->pers[i].nume)
			free(colectie->pers[i].nume);
	free(colectie->pers);

	free(colectie);
}

int main()
{
	return 0;
}
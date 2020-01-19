#include <stdio.h>
#include <stdlib.h>

#pragma pack(1)

typedef struct 
{
	int id;
	int val;
} TBec;

typedef struct 
{
	TBec **becuriCamera;
	int nrCrt;
} TCamera;

typedef struct
{
	TCamera *camere;
	TBec *becuri;
	int nrCrtCam, nrMaxCam, nrCrtBec, nrMaxBec, nrMaxBecPerCamera;
} TComanda;

#pragma pack()

TComanda *alocaComanda(int nrMaxCam, int nrMaxBec, int nrMaxBecPerCamera)
{
	TComanda *comanda = calloc(1, sizeof(TComanda));
	if (comanda == NULL)
		return NULL;

	comanda->nrMaxCam = nrMaxCam;
	comanda->nrMaxBec = nrMaxBec;
	comanda->nrMaxBecPerCamera = nrMaxBecPerCamera;
	
	comanda->camere = calloc(nrMaxCam, sizeof(TCamera));
	if (comanda->camere == NULL) {
		free(comanda);
		return NULL;
	}

	int i, j;
	for(i = 0; i < nrMaxCam; i++) {
		comanda->camere[i].becuriCamera = calloc(nrMaxBecPerCamera, sizeof(TBec *));
		if (comanda->camere[i].becuriCamera == NULL) {
			for (j = 0; j < i; j++)
				free(comanda->camere[j].becuriCamera);
			free(comanda->camere);
			free(comanda);
			return NULL;
		}
	}

	comanda->becuri = calloc(nrMaxBec, sizeof(TBec));
	if (comanda->becuri == NULL) {
		for (i = 0; i < nrMaxCam; i++)
			free(comanda->camere[i].becuriCamera);
		free(comanda->camere);
		free(comanda);
		return NULL;
	}

	for (i = 0; i < nrMaxCam; i++) {
		/*for(j = 0; j < nrMaxBecPerCamera; j++) {
			comanda->camere[i].becuriCamera[j] = &comanda->becuri[i * nrMaxBecPerCamera + j];
		}*/
		*comanda->camere[i].becuriCamera = &(comanda->becuri[i * nrMaxBecPerCamera]);
	}

	return comanda;
}



TComanda *adaugaBec(TComanda *c, char rosu, char verde, char albastru, 
	char intensitate, TCamera *cam)
{
	c->becuri[c->nrCrtBec].id = c->nrCrtBec;
	c->becuri[c->nrCrtBec].val = ((int)(rosu) << 24) + ((int)(verde) << 16)
		 + ((int)(albastru) << 8) + (int)(intensitate);

	cam->becuriCamera[cam->nrCrt] = &c->becuri[c->nrCrtBec++];
	cam->nrCrt++;

	return c;		
}


TComanda *eliminaBec(TComanda *c, int id)
{
	int i, j;
	int id1, id2, id3;
	for (i = 0; i < c->nrCrtBec; i++)
		if (id == c->becuri[i].id) {
			id1 = i;
			break;
		}

	for (i = 0; i < c->nrCrtCam; i++)
		for (j = 0; j < c->camere[i].nrCrt; j++)
			if (id == c->camere[i].becuriCamera[j]->id) {
				id2 = i;
				id3 = j;
				break;
			}

	for (i = id1; i < c->nrCrtBec - 1; i++)
		c->becuri[i] = c->becuri[i + 1];

	for (i = id3; i < c->camere[id2].nrCrt - 1; j++)
		c->camere[id2].becuriCamera[i] = c->camere[id2].becuriCamera[i + 1];

	c->nrCrtBec--;
	c->camere[id2].nrCrt--;

	return c;
}

int cmp(TBec *b1, TBec *b2)
{
	if(b1->val << 24 > b2->val << 24)
		return 1;
	else if(b1->val << 24 < b2->val << 24)
		return -1;
	else return 0;
}

void updateCamera(TCamera *cam, TBec *etalon, int (*cmp)(TBec*, TBec*))
{
	int i;
	for (i = 0; i < cam->nrCrt; i++)
		if(cmp(cam->becuriCamera[i], etalon) == 0)
			cam->becuriCamera[i]->val = ((cam->becuriCamera[i]->val << 24) >> 24) + ((etalon->val >> 8) << 8);
}

void dezalocaComanda(TComanda *c) 
{
	int i;

	free(c->becuri);
	for(i = 0; i < c->nrCrtCam; i++)
		free(c->camere[i].becuriCamera);
	free(c->camere);
	free(c);
}

int main()
{
	return 0;
}

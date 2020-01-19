#include <stdio.h>
#include "recapitulare.h"
#include<stdlib.h>
#include<string.h>

//fisier binar contine nr de unitati si unitatile
//numele fisierului se primeste in main
//functia de citire primeste un fisier deschis
//
Unit * readFromBinary(FILE*f, int *nrUnitTypes)
{
        int nrUnitTest;
        fread(nrUnitTypes,sizeof(int),1,f);
        Unit * unitTypes=(Unit*)calloc(*nrUnitTypes,sizeof(Unit));
        if(!unitTypes)
                //n-am putut efectua alocarea
                return NULL;
        nrUnitTest=fread(unitTypes,sizeof(Unit),*nrUnitTypes,f);
        if (nrUnitTest!=*nrUnitTypes)
        {
                //n-am putut citi toate unitatile din fisier
                return NULL;
        }
        return unitTypes;
}

//citim numele de la tastatura, aloca spatiu, genereaza aleator unitatile
//din vectorul de tipuri
Player* generatePlayer(int nrUnits, Unit* unitTypes, int nrUnitTypes)
{       //alocare dinamica
        Player *p=(Player*)calloc(1, sizeof(Player));
        if (!p) 
                return NULL;

        char name[100]; 
        int i, type;
        //initializare generator de numere aleatoare
        srand(time(NULL));
        printf("\nenter player name:");
        fgets(name, 100,stdin);
        //eliminam \n de la final adaugat de fgets
        int nameLength=strlen(name);
        if (name[nameLength-1]=='\n')
                name[nameLength-1]='\0';//folosire null terminator pentru scurtarea sirului
        //alocarea sirurilor cu copiere
        p->name=strdup(name);
        if(!p->name)
        {
                free(p);
                return NULL;
        }
        //alocare membri structura cu eliberare memorie in caz de nereusita
        p->units=(UnitPlayer*)calloc(nrUnits,sizeof(UnitPlayer));
        if(!p->units)
        {
                free(p->name);
                free(p);
                return NULL;
        }
        //initializare structuri, generare de numere aleatoare intr-un interval dat
        //adresare membri structuri cu . si ->
        //structuri care contin alte structuri
        for(i=0;i<nrUnits;i++)
        {
                type=rand()%nrUnitTypes;
                p->units[i].id=unitTypes[type].id;
                p->units[i].currentLife=unitTypes[type].maxLife;
        }
        //intoarcerea corecta a unei adrese pentru care am alocat memorie in interiorul functiei
        return p;
}

Unit* find(int id, Unit* units, int indMin, int indMax)
{  
    //algoritmul de cautare binara
    //iesirea din recurenta    
    if(indMin>indMax)
        return NULL;
    //daca am gasit elementul cautat pe pozitia din mijloc il intorc
    int mid=(indMin+indMax)/2;
    if(units[mid].id==id)
        return units+mid;//intorc adresa; puteam scrie &units[mid]
    //caut in stanga
    else if(units[mid].id>id)
        return find(id,units,indMin,mid-1);
    else
    //caut in dreapta
        return find(id,units,mid+1,indMax);
    
}



//cauta id-ul unei unitati in vectorul de tipuri si intoarce adresa
//intoarce null daca nu gaseste
//presupune vectorul sortat
Unit* getById( int id, Unit* units, int nrUnits)
{
    //functie recursiva, cautare binara
    return find(id,units,0,nrUnits-1);
}

int cmpUnitById(const void*a, const void *b)
{
    //functie de comparatie pt qsort    
    return ((Unit*)a)->id-((Unit*)b)->id;
}







int main(int argc, char** argv)
{
    int nrTypes,i;    
    Player *p1;
    //verificarea parametrilor din linia de comanda
    if(argc!=2)
    {
            printf("usage: play unitfile");
            return 1;
    }
    //fisier binar deschis pentru citire
    FILE *f=fopen(argv[1],"rb");
    if(!f)
    {
            printf("could not open unitfile");
            return 2;
    }
    //transmitere parametri prin adresa
    Unit* unitTypes=readFromBinary(f,&nrTypes);
    //sortare utilizand qsort
    qsort(unitTypes, nrTypes, sizeof(Unit), cmpUnitById);    
    
    for(i=0;i<nrTypes;i++)
    {//adresare campuri structuri folosind .
        printf("\n%d %s %d %d %d",unitTypes[i].id,unitTypes[i].name,unitTypes[i].minDmg, unitTypes[i].maxDmg,unitTypes[i].maxLife);
    }
    p1=generatePlayer(6,unitTypes, nrTypes);
    for(i=0;i<6;i++)
    {//adresare campuri structuri folosind ->
        Unit *u=getById(p1->units[i].id, unitTypes, nrTypes);        
        printf("\nunit name: %s current life: %d max life: %d maxDmg:%d",u->name,p1->units[i].currentLife, u->maxLife,u->maxDmg);

    }
}

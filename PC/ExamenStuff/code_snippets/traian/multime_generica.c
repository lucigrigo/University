#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VidaM(m) ((m)->s == (m)->p) 
#define PlinaM(m) ((m)->s == (m)->t) 

typedef int(*TFComp)(const void *, const void *);

typedef struct
{ 
    size_t d;                   /* dimensiune elemente */
    void *p, *s, *t;          /* adrese vector, sfarsit zona utila, disponibila */
    TFComp cmp;          /* functia care induce o relație de ordine în mulțime */
} TMultime;

int compInt(const void *a, const void *b) 
{
    return *(int*)a - *(int*)b;
}

int compString(const void* a, const void* b)
{
    return strcmp((char*) a, (char*) b);
}
 /* creeaza multime, alocand dinamic spatiu pentru descriptor
    si n elemente de dimensiune d; intoarce adr. multime sau NULL */  
TMultime *InitD(size_t n, size_t d, TFComp fcmp) 
{
    TMultime* m = (TMultime*) malloc(sizeof(TMultime));
    if (m)
    {
        m->d = d;
        m->p = malloc(d*n);
        if (m->p)
        {
            m->s = m->p;
            m->t = (char*)m->p + d*n;
            m->cmp = fcmp;
        }
        else
        {
            free(m);
            m = NULL;
        }
    }
    return m;
}
      
void DistrugeM(TMultime **m)
{
    free((*m)->p);
    free(*m);
    *m = NULL;
}

/*--- operatii asupra multimilor NESORTATE ---*/
/* intoarce numarul de elemente din multime */
int Cardinal(TMultime * m)
{
    return ((char*)m->s - (char*)m->p) / m->d;
}

/* intoarce 1/0 - elementul x exista/nu exista in multimea m */
int Apartine(void *x, TMultime *m)
{
    int i;
    for (i = 0; i < Cardinal(m); i++)
        if (m->cmp(x, (char*)m->p + i * m->d) == 0)
            return 1;
    return 0;
}

 /* obiectiv: adaugarea unui nou element la sfarsitul vectorului;
    intoarce 1/0/-1 - succes/exista deja/lipsa spatiu */
int Adauga(void *nou, TMultime *m) 
{
    if (PlinaM(m))
        return -1;
    if (Apartine(nou, m))
        return 0;
        
    memcpy(m->s, nou, m->d);
    m->s = (char*)m->s + m->d;
    return 1;
}

void AfisareMultime_int(TMultime *m)
{
    int *x = (int*)(m->p), n = Cardinal(m), i = 0;
    printf("[");
    for( ; i < n; i++) 
        if (i != n-1) 
            printf(" %i,", x[i]);
        else 
            printf(" %i ]\n", x[i]);
}
     
int main()
{
    TMultime* mInt = InitD(10, sizeof(int), compInt);
    printf("%d\n", Cardinal(mInt));
    
    int x = 5, y = 5;
    Adauga(&x, mInt);
    printf("%d\n", Cardinal(mInt));
    
    Adauga(&y, mInt);
    printf("%d\n", Cardinal(mInt));
    
    for (x = 6; x <= 20; x++)
    {
        Adauga(&x, mInt);
        printf("%d %d\n", Cardinal(mInt), PlinaM(mInt));       
    }
    AfisareMultime_int(mInt);
    
    TMultime* mString = InitD(20, sizeof(char*), compString);
    char c[] = "aaaa", d[] = "aaaa";
    
    Adauga(c, mString);
    printf("%d\n", Cardinal(mString));
    
    Adauga(d, mString);
    printf("%d\n", Cardinal(mString));
    
    DistrugeM(&mInt);
    DistrugeM(&mString);
    return 0;
}
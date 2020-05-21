#include <stdio.h>
#include <stdlib.h>

// #define INPUT_FILENAME "./private_tests/holograme/input/test3.in"
#define INPUT_FILENAME "holograme.in"
#define OUTPUT_FILENAME "holograme.out"

struct adj_list
{
    int dest;
    struct adj_list *next;
};

// structura pentru coada
struct queue
{
    int start; // indexul de inceput al cozii
    int size;  // numarul de elemente din coada (si indexul de final din coada)
    int *arr; // vectorul de elemente
};

// functia care initializeaza o coada goala
struct queue *create_queue(int n)
{
    struct queue *q = (struct queue *)malloc(sizeof(struct queue));
    q->size = 0;  // dimensiunea initiala
    q->start = 0; // indexul initial de start (nu are niciun element coada)
    q->arr = (int *) malloc(n * sizeof(int));
    return q;
}

// functia care adauga un element in coada
struct queue *enqueue(struct queue *q, int elem)
{
    q->arr[q->size] = elem; // adauga elementul pe ultima pozitie
    q->size = q->size + 1;  // incrementeaza dimensiunea
    return q;
}

// functia care returneaza primul element din coada
struct queue *top(struct queue *q, int *x)
{
    *x = q->arr[q->start]; // returneaza elementul de pe pozitia indexului 'start'
    return q;
}

// functia care elimina un element din coada
struct queue *dequeue(struct queue *q)
{
    q->start = q->start + 1; // incrementeaza indexul de start
    return q;
}

// functia care verifica daca o coada este goala
int is_empty(struct queue *q)
{
    // verifica daca indexul de start este egal cu cel de final
    if (q->size == q->start)
    {
        return 1; // coada este goala
    }
    return 0; // coada inca mai are elemente in ea
}

int contains(struct queue *q, int x)
{
    int i = q->start;
    while (i < q->size)
    {
        if (q->arr[i] == x)
        {
            return 1;
        }
        i++;
    }
    return 0;
}

struct queue *delete (struct queue *q, int x)
{
    int i = q->start;
    while (i < q->size)
    {
        if (q->arr[i] == x)
        {
            q->arr[i] = q->arr[q->size - 1];
            q->size = q->size - 1;
            return q;
        }
        i++;
    }
    return q;
}

//int viz[MAXN], parent[MAXN], v[MAXN];
int nr;

int find_parent(int u, int *parent)
{
    return parent[u] == u ? u : find_parent(parent[u], parent);
}

void DFS(int u, struct adj_list **edges, struct queue **q, int *viz, int *parent, int *v)
{
    //printf("%d\n", u);
    viz[u] = 1;
    struct adj_list *ptr = edges[u];
    *q = enqueue(*q, u);

    while (ptr != NULL)
    {
        int d = ptr->dest;
        if (find_parent(u, parent) != find_parent(d, parent))
        {
            ptr = ptr->next;
            continue;
        }
        if (viz[d] == 1 && contains(*q, d) == 1)
        {
            //printf("aici\n");
            v[find_parent(d, parent)] = 1;
        }
        if (viz[d] == 0)
        {
            DFS(d, edges, q, viz, parent, v);
        }
        ptr = ptr->next;
    }

    *q = delete (*q, u);
}

struct adj_list **add_edge(struct adj_list **edges, int n, int u, int v, int *parent)
{
    if (edges[u] == NULL)
    {
        // printf("1. aici cu %d - %d\n", u, v);
        struct adj_list *new_edge = (struct adj_list *)malloc(sizeof(struct adj_list));
        new_edge->dest = v;
        new_edge->next = NULL;
        edges[u] = new_edge;
    }
    else
    {
        // printf("2. aici cu %d - %d\n", u, v);
        struct adj_list *ptr = edges[u];
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        struct adj_list *new_edge = (struct adj_list *)malloc(sizeof(struct adj_list));
        new_edge->dest = v;
        new_edge->next = NULL;
        ptr->next = new_edge;
    }
    parent[find_parent(u, parent)] = find_parent(v, parent);
    return edges;
}

int main()
{
    int n, m, i;

    // citirea datelor de intrare
    FILE *ffile = fopen(INPUT_FILENAME, "r");
    fscanf(ffile, "%d %d\n", &n, &m);
    int *parent = (int *) malloc(n * sizeof(int));
    int *viz = (int *) malloc(n * sizeof(int));
    int *v = (int *) malloc(n * sizeof(int));
    struct adj_list **edges = (struct adj_list **)malloc(n * sizeof(struct adj_list *));

    // initializari
    for (int i = 0; i < n; ++i)
    {
        viz[i] = 0;
        v[i] = 0;
        parent[i] = i;
        edges[i] = NULL;
    }
    nr = n;

    for (i = 0; i < m; ++i)
    {
        int u, v;
        fscanf(ffile, "%d %d\n", &u, &v);
        edges = add_edge(edges, n, u - 1, v - 1, parent);
    }
    fclose(ffile);

    // printf("%d %d\n", n, m);
    // for (i = 0; i < n; ++i)
    // {
    //     viz[i] = 0;
    //     // parent[i] = i;
    //     // struct adj_list *ptr = edges[i];
    //     // while (ptr != NULL)
    //     // {
    //     //     printf("(%d,%d)\n", i, ptr->dest);
    //     //     ptr = ptr->next;
    //     // }
    // }

    for (i = 0; i < n; ++i)
    {
        int p = find_parent(i, parent);
        if (v[p] == 1)
        {
            viz[i] = 1;
        }
        if (viz[i] == 0)
        {
            struct queue *q = create_queue(n);
            DFS(i, edges, &q, viz, parent, v);
            free(q->arr);
            free(q);
        }
    }

    for (i = 0; i < n; ++i)
    {
        int p = find_parent(i, parent);
        if (viz[i] == 1 && v[p] == 0)
        {
            v[p] = 1;
            nr--;
        }
    }

    // nr = m;
    // BFS(edges, n);

    // scrierea datelor de iesire
    ffile = fopen(OUTPUT_FILENAME, "w");
    fprintf(ffile, "%d", nr);
    printf("%d\n", nr);
    fclose(ffile);

    free(parent);
    free(viz);
    free(v);
    for(i = 0; i < n; ++i) {
        // struct adj_list *ptr = edges[i];
        // if(ptr != NULL) {
        //     struct adj_list *temp = ptr->next;
        //     do{
        //         free(ptr);
        //         ptr = temp;
        //         temp = temp->next;
        //     } while(temp != NULL);
        // }
    }
    free(edges);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int n = 10;
int M[10][10];
int d_bfs[10][10];
int vizitat_bfs[10];
int p_bfs[10];
int vizitat_dfs[10];
int d_dfs[10];
int f_dfs[10];
int p_dfs[10];

struct queue {
  int start;
  int size;
  int arr[];
};

struct queue *create_queue() {
  struct queue *q = (struct queue *)malloc(sizeof(struct queue));
  q->size = 0;
  q->start = 0;
  return q;
}

struct queue *enqueue(struct queue *q, int elem) {
  q->arr[q->size] = elem;
  q->size = q->size + 1;
  return q;
}

struct queue *top(struct queue *q, int *x) {
  *x = q->arr[q->start];
  return q;
}

struct queue *dequeue(struct queue *q) {
  q->start = q->start + 1;
  return q;
}

int is_empty(struct queue *q) {
  if (q->size == q->start) {
    return 1;
  }
  return 0;
}

void printare_coada(struct queue *q) {
  int i;
  printf("Q: ");

  for (i = q->start; i < q->size; ++i) {
    printf("   \t%c p(%c)=%c d(%c)=%d c(%c)=%s\n", (char)q->arr[i] + 65,
           (char)q->arr[i] + 65, (char)p_bfs[q->arr[i]] + 65,
           (char)q->arr[i] + 65, (*d_bfs)[q->arr[i]], (char)q->arr[i] + 65,
           vizitat_bfs[q->arr[i]] == 1 ? "gri" : "alb");
  }
  printf("\n");
}

void printare_rezultate_BFS() {
  int i;
  printf("\nRezultate finale BFS:\n");

  for (i = 0; i < n; ++i) {
    printf("\tNod %c: p(%c)=%c d(%c)=%d c(%c)=%s\n", (char)i + 65, (char)i + 65,
           p_bfs[i] == i ? '-' : (char)p_bfs[i] + 65, (char)i + 65, (*d_bfs)[i],
           (char)i + 65, vizitat_bfs[i] == 1 ? "negru" : "alb");
  }
}

void BFS() {
  int i;
  int t;

  for (i = 0, t = 1; i < n; ++i, ++t) {
    if (vizitat_bfs[i] == 0) {
      struct queue *q = create_queue();
      q = enqueue(q, i);
      d_bfs[i][i] = 0;
      vizitat_bfs[i] = 1;

      while (is_empty(q) == 0) {
        printare_coada(q);
        int current_elem;
        q = top(q, &current_elem);
        int j;

        for (j = 0; j < n; ++j) {
          if ((M[current_elem][j] == 1) && (vizitat_bfs[j] == 0)) {
            q = enqueue(q, j);
            d_bfs[i][j] = d_bfs[i][current_elem] + 1;
            p_bfs[j] = current_elem;
            vizitat_bfs[j] = 1;
          }
        }

        vizitat_bfs[current_elem] = 1;
        q = dequeue(q);
      }
    }
  }

  printare_rezultate_BFS();
}

void explorare(int timp, int u) {
  d_dfs[u] = ++timp;
  int j;
  vizitat_dfs[u] = 1;
  printf("\n");
  for (j = 0; j < timp; j++) {
    printf("\t");
  }
  printf("Nod %c d(%c)=%d", (char)u + 65, (char)u + 65, d_dfs[u]);

  for (j = 0; j < n; ++j) {
    if (M[u][j] == 1 && vizitat_dfs[j] == 0) {
      // printf("aici niciodata?");
      p_dfs[j] = u;
      // printf("\n");
      explorare(timp, j);
    }
  }

  vizitat_dfs[u] = 2;
  f_dfs[u] = ++timp;
}

void DFS() {
  int t = 0;
  int i;

  for (i = 0; i < n; ++i) {
    if (vizitat_dfs[i] == 0) {
      printf("\n\t\t---\n");
      explorare(t, i);
      int j;
      for (j = 0; j < n; j++) {
        if (j != i) {
          vizitat_dfs[j] = 0;
        }
      }
    }
  }
}

int main() {
  M[0][1] = 1;
  M[0][2] = 1;
  M[0][7] = 1;
  M[1][3] = 1;
  M[1][4] = 1;
  M[1][7] = 1;
  M[1][8] = 1;
  M[2][3] = 1;
  M[3][4] = 1;
  M[3][9] = 1;
  M[4][5] = 1;
  M[4][6] = 1;
  M[5][6] = 1;
  M[7][8] = 1;
  M[8][0] = 1;

  printf("\n------------------------------\n");
  printf("\n--- Parcurgere pe latime --- \n");
  BFS();

  printf("\n------------------------------\n--- Parcurgere pe adancime ---\n");
  DFS();
  printf("\n------------------------------\n");
  return 0;
}

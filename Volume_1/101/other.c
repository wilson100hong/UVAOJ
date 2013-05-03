/* ACM 101
 * mythnc
  * 2011/10/14 16:08:24   
   * run time: 0.008
    */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXARY 25

typedef struct robot {
      int *block;
          int count;
} Action;

void init(Action *[], int n);
int position(Action *[], int *, int);
void clear(Action *[], int *);
void move(Action *[], int *, int *);
void print(Action *[], int);

int main(void)
{
      /* a[3]: 0 for a, 1 for position a, 2 for block a */
          /* same as b */
              int n, a[3], b[3];
                  char str1[MAXARY], str2[MAXARY];
                      Action *arm[MAXARY];

                          scanf("%d", &n);
                              init(arm, n);
                                  while (scanf("%s %d %s %d", str1, a, str2, b) == 4) {
                                            if (a[0] == b[0])
                                                          continue;
                                                                  if ((a[1]= position(arm, a, n)) ==
                                                                                (b[1]= position(arm, b, n)))
                                                                                continue;
                                                                                        if (strcmp(str1, "move") == 0)
                                                                                                      clear(arm, a);
                                                                                                              if
                                                                                                                (strcmp(str2,
                                                                                                                "onto")
                                                                                                                == 0)
                                                                                                                            clear(arm,
                                                                                                                            b);
                                                                                                                                    move(arm,
                                                                                                                                    b,
                                                                                                                                    a);
                                                                                                                                        }
                                                                                                                                            print(arm,
                                                                                                                                            n);
                                                                                                                                                return
                                                                                                                                                0;
}

/* init: initialize arm */
void init(Action *arm[], int n)
{
      int i;

          for (i = 0; i < n; i++) { /* initialize arm */
                    arm[i] = (Action *)malloc(sizeof(Action));
                            arm[i]->block = (int *)malloc(sizeof(int) * n);
                                    arm[i]->count = 0;
                                            arm[i]->block[arm[i]->count++] = i;
                                                }
}

/* position: return position and block of pt[0] */
int position(Action *arm[], int *pt, int n)
{
      int i, j;

          for (i = 0; i < n; i++)
                    for (j = 0; j < arm[i]->count; j++)
                                  if (arm[i]->block[j] == pt[0]) {  /* position i, block j */
                                                    pt[2] = j;
                                                                    return i;
                                                                                }
}

/* clear: clear blocks above x */
void clear(Action *arm[], int *x)
{
      int tmp;

          while (arm[x[1]]->count != x[2] + 1) {  /* return tmp to it's position */
                    tmp = arm[x[1]]->block[--arm[x[1]]->count];
                            arm[tmp]->block[arm[tmp]->count++] = tmp;
                                }
}

/* move: move a to b */
void move(Action *arm[], int *b, int *a)
{
      int i;

          for (i = a[2]; i < arm[a[1]]->count; i++)
                    arm[b[1]]->block[arm[b[1]]->count++] = arm[a[1]]->block[i];
                        arm[a[1]]->count = a[2];
}

/* print: print out final state */
void print(Action *arm[], int n)
{
      int i, j;

          for (i = 0; i < n; i++) {
                    printf("%d:", i);
                            for (j = 0; j < arm[i]->count; j++)
                                          printf(" %d", arm[i]->block[j]);
                                                  free(arm[i]->block);
                                                          free(arm[i]);
                                                                  printf("\n");
                                                                      }
}

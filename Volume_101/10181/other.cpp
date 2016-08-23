#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define HASH_SIZE 500000
#define HEAP_SIZE 3234567
#define abs(x)( ((x)>0)?(x):-(x) )
struct Hash{
  char board[4][4];
  char step;
  struct Hash *last;
  struct Hash *next;
  int ssss;
}hash[HASH_SIZE],*heap[HEAP_SIZE];
int heapNum;

void input(char board[4][4]){
  int i,j,num;
  for(i=0;i<4;++i){
    for(j=0;j<4;++j){
      scanf("%d",&num);
      board[i][j] = num;
    }
  }
}

int check(char board[4][4]){
  int inversion = 0;
  int a,b,i,j,ii,jj;
  for(a=0;a<16;++a){
    for(b=0;b<a;++b){
      i = a/4, j = a%4;
      ii= b/4, jj= b%4;
      if(board[i][j] && board[ii][jj] && board[i][j]<board[ii][jj])
        ++inversion;
      if(board[i][j]==0){
        inversion += i+1;
      }
    }
  }
  return (inversion&1);
}

void boardCpy(char to[4][4],char from[4][4]){
  int i,j;
  for(i=0;i<4;++i){
    for(j=0;j<4;++j){
      to[i][j] = from[i][j];
    }
  }
}

int boardCmp(char A[4][4],char B[4][4]){
  int i,j;
  for(i=0;i<4;++i){
    for(j=0; j<4&&A[i][j]==B[i][j]; ++j);
    if(j<4)break;
  }
  if(i>=4)return 0;
  return A[i][j] - B[i][j];
}

void whitePos(char board[4][4],int *x,int *y){
  int i,j;
  for(i=0;i<4;++i){
    for(j=0;j<4;++j){
      if(!board[i][j]){
        *x = i;
        *y = j;
        return;
      }
    }
  }
  *x = -1;
  *y = -1;
}

void boardPrint(char board[4][4]){
  int i,j;
  for(i=0;i<4;++i){
    for(j=0;j<4;++j){
      printf("%d%c",board[i][j],(j==3)?'\n':' ');
    }
  }
}

char site[16][2]={
  {3,3},{0,0},{0,1},{0,2},
  {0,3},{1,0},{1,1},{1,2},
  {1,3},{2,0},{2,1},{2,2},
  {2,3},{3,0},{3,1},{3,2},
};

char initialBoard[4][4] = {
  {1,2,3,4},
  {5,6,7,8},
  {9,10,11,12},
  {13,14,15,0},
};

int cpF(struct Hash *cur){
  // mahantan distance * 3 + g
  int i,j,v=0;
  for(i=0;i<4;++i){
    for(j=0;j<4;++j){
      if(cur->board[i][j]){
        v += abs(i-site[(int)cur->board[i][j]][0])
            +abs(j-site[(int)cur->board[i][j]][1]);
      }
    }
  }
  return 3*v+cur->ssss;
}

void push(struct Hash *node){
  int now = ++heapNum;
  while(now>1 && cpF(node) < cpF(heap[now/2])){
    heap[now] = heap[now/2];
    now /= 2;
  }
  heap[now] = node;
}

struct Hash* pop(){
  struct Hash *re = heap[1];
  struct Hash *node = heap[heapNum--];
  int now = 1,next = 2;
  while(next<=heapNum){
    if(next<heapNum && cpF(heap[next])>cpF(heap[next+1])){
      ++next;
    }
    if(cpF(heap[next])<cpF(node)){
      heap[now] = heap[next];
      now = next;
      next = now*2;
    }else break;
  }
  heap[now] = node;
  return re;
}

int hashFun(char board[4][4]){
  int i,j;
  unsigned int val = 0;
  for(i=0;i<4;++i){
    for(j=0;j<4;++j){
      val = (val<<4) + (val>>4) + board[i][j];
    }
  }
  return val % HASH_SIZE;
}

struct Hash* search(char board[4][4]) {
  struct Hash *cur = hash[hashFun(board)].next;
  while(cur != NULL && boardCmp(cur->board,board)!=0){
    cur = cur->next;
  }
  return cur;
}

struct Hash* insert(char board[4][4],char step,struct Hash* last){
  struct Hash *head = &hash[hashFun(board)];
  struct Hash *cur = (struct Hash*)malloc(sizeof(struct Hash));
  boardCpy(cur->board,board);
  cur->last = last;
  cur->step = step;
  cur->next = head->next;
  if(last==NULL)cur->ssss = 0;
  else cur->ssss = last->ssss+1;
  head->next = cur;
  return cur;
}

void initial(){
  int i;
  struct Hash *cur,*tmp;
  for(i=0;i<HASH_SIZE;++i){
    cur = hash[i].next;
    hash[i].next = NULL;
    while(cur!=NULL){
      tmp = cur;
      cur = cur->next;
      free(tmp);
    }
  }
  heapNum = 0;
}

void inQ(char board[4][4], char step, struct Hash *last){
  if(search(board)!=NULL)
    return;
  struct Hash *cur = insert(board,step,last);
  push(cur);
}

void L(char board[4][4],int x,int y,struct Hash *last){
  if(y<=0)return;
  board[x][y] = board[x][y-1];
  board[x][y-1] = 0;
  inQ(board,'L',last);
  board[x][y-1] = board[x][y];
  board[x][y] = 0;
}
void R(char board[4][4],int x,int y,struct Hash *last){
  if(y>=3)return;
  board[x][y] = board[x][y+1];
  board[x][y+1] = 0;
  inQ(board,'R',last);
  board[x][y+1] = board[x][y];
  board[x][y] = 0;
}
void U(char board[4][4],int x,int y,struct Hash *last){
  if(x<=0)return;
  board[x][y] = board[x-1][y];
  board[x-1][y] = 0;
  inQ(board,'U',last);
  board[x-1][y] = board[x][y];
  board[x][y] = 0;
}
void D(char board[4][4],int x,int y,struct Hash *last){
  if(x>=3)return;
  board[x][y] = board[x+1][y];
  board[x+1][y] = 0;
  inQ(board,'D',last);
  board[x+1][y] = board[x][y];
  board[x][y] = 0;
}

void (*transF[4])(char[4][4],int,int,struct Hash*)={L,R,U,D};

struct Hash* spfa(char board[4][4]){
  initial();
  struct Hash *cur;
  int x,y;
  int i;
  inQ(board,-1,NULL);
  while(1){
    cur = pop();
    if(boardCmp(cur->board,initialBoard)==0){
      return cur;
    }
    whitePos(cur->board,&x,&y);
    for(i=0;i<4;++i){
      transF[i](cur->board,x,y,cur);
    }
  }
  return NULL;
}

void reStep(struct Hash* cur){
  if(cur->step==-1) return;
  reStep(cur->last);
  putchar(cur->step);
}

int main(){
  int t;
  char board[4][4];
  scanf("%d",&t);
  while(t--){
    input(board);
    if(check(board))
      puts("This puzzle is not solvable.");
    else {
      reStep(spfa(board));
      putchar('\n');
    }
  }
  return 0;
}

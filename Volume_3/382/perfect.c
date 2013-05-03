#include "stdio.h"
#include "math.h"
int perfect(int n) {
  if (n == 1)
    return -1;
  int sum = 1;
  int sq = (int) sqrt(n);
  int i, q;
  for (i = 2; i <= sq; ++i) {
    if (n % i == 0) {
      sum += i;
      q = n / i;
      if (q != i && q > sq) {
         sum += q;
      }
    }  
  } 


  if (sum == n) {
    return 0;  
  } else if (sum > n) {
    return 1;  
  } else {
    return -1;  
  }
}


int main() {
  int n;
  printf("PERFECTION OUTPUT\n");
  while (scanf("%d ", &n) == 1) {
    if (n == 0) {
      break;  
    }  

    switch(perfect(n)) {
      case 0:
        printf("%5d  PERFECT\n", n);
      break;
      case -1:
        printf("%5d  DEFICIENT\n", n);
      break;
      case 1:
        printf("%5d  ABUNDANT\n", n);
      default:
      break;

    } 
  }
  printf("END OF OUTPUT\n");
  return 0;
}

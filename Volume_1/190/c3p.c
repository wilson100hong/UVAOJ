#include <stdio.h>



int main() {
  double x1, y1, x2, y2, x3, y3;
  while (scanf("%lf %lf %lf %lf %lf %lf", 
    &x1, &y1, &x2, &y2, &x3, &y3) != -1) {
    printf("%lf %lf\n", x1, y1);
  }
  return 0;
}

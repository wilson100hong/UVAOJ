#include "stdio.h"
float abs(float a) {
  return a > 0 ? a : -a;  
}

int main() {
  int h, m;
  while (scanf("%d:%d\n", &h, &m)) {
    if (h== 0 && m==0) {
      break;  
    }
    float am =  m*6 ; 
    float ah = 30*h + m*0.5f;
    float angle = abs(am-ah);
    angle = angle > 180.f ? 360.f - angle : angle;
    printf("%.3f\n", angle);
  }
  return 0;
}

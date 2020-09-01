#include <stdio.h>

int main(){

int x = 3;
/*
goto label0;

label1: x += 3;
goto label0;

label2: x--;
goto label0;

label0:

if(x < 10){
  printf("%d : ", x);
  if(x % 2 == 0){
    printf("goto label1\n");
    goto label1;
  }
  else {
    printf("goto label2\n");
    goto label2;
    }
  }*/

  while(x < 10){
    printf("%d : ", x);
    if(x % 2 == 0){
      printf("goto label1\n");
      x += 3;
    }
    else {
      printf("goto label2\n");
      x--;
    }
  }

  return 0;
}

#include <stdio.h>

int main(){
  int counter = 1;
  do{
    printf("%d\n", counter);
    counter++;
  } while (counter <= 3);
  printf("next statement after the loop\n");
  return 0;
}

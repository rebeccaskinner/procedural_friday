#include <stdlib.h>
#include <stdio.h>
#include <our_so.h>

int main(int argc, char** argv)
{
  int num = 0;
  if(argc >= 2) {
    num = atoi(argv[1]);
  }
  printf("%d! = %d\n", num, factorial(num));
  return 0;
}

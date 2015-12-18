#include <unistd.h>
int factorial(int num)
{
  int product = 1;
  while(num) {
    product *= num;
    --num;
    sleep(1);
  }
  return product;
}

#include <stdio.h>
#include <string.h>
#include <stdint.h>



int main()
{
  double a = 0xffffffffffffffff;
  double b = 0xffffffffffffffff;
  double result = a + b;
  printf("%d + %d = %f\n", a, b, result);
  return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdint.h>



int main()
{
  uint8_t a = 13;
  a = ~a;
  printf("%d\n", a);

  return 0;
}

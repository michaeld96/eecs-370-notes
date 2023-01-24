#include <stdio.h>
#include <string.h>
#include <stdint.h>


int main()
{
  int beq = 0b010;
  int result = beq << 22;
  printf("%d\n", result);
  printf("%d\n", result >> 22);
}

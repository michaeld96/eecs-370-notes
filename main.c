#include <stdio.h>
#include <string.h>

int main(void)
{
    int64_t a;
    int64_t b;
    int64_t c;
    a = 50;
    printf("%llx\n", a);
    b = a & 15;
    printf("%llx\n", b);
    c = b << 2;
    
    return 0;
}
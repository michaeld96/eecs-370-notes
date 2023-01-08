#include <stdio.h>
#include <string.h>

struct double_string_ptrs
{
    char *a;
    char *b;
};

struct double_string_char_arrs
{
    char a[80];
    char b[80];
};

int main(void)
{
    struct double_string_ptrs ptrs;
    ptrs.a = "hi";
    ptrs.b = "there";

    struct double_string_char_arrs arrs;
    strcpy(arrs.a, "hello");
    strcpy(arrs.b, "awesome");

    return 0;
}
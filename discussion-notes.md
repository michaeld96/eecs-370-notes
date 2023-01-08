# EECS 370 Discussion Notes

## Discussion 1:

The "translations" from C++ to C:

|C++|C|
|:--|:--|
|`new`, `delete`|`malloc()`, `free()`|
|`std::string`|`char*`, `strcmp()`, `strcpy()`|
|`std::vector, std::set, std::map`|Only arrays|
|`std::cout, std::cin, std::fstream`|`printf(), scanf(), fopen(), fgets()`|

*Note:* To make a string in C, we will use a different syntax. This is displayed in the example below:

```c
#include <stdio.h>

int main(void)
{
    char *cstring = "Hello World";
    printf("%s\n", cstring);
    return 0;
}
```

### The Size of Common Data Types

<img src = "imgs/common-data-types.png" align = "center">

Below is a chart of primitive types. As a reminder, primitive types are types that are given to the programmer by the language; they are not defined by the programmer.

### Decimal, Binary, and Hexadecimal in C

C doesn't have `bool` types. To include `bool` types we need to include `#include <stdbool.h>`. We usually use `int` instead.

Any `_t` data type like `uint32_t` are in `#include <stdint.h>`.

### Strings in C and C++

When we are messing around with strings in C we need to think about them as just a `char` array. In C, when we say `char* hello = "Hello there";`, `hello` is just a pointer to the first character in the array:

$$
\overbrace{\fbox{H}}\fbox{e}\fbox{l}\fbox{l}\fbox{o}\fbox{/0}
$$

Where the brace is, this is where `hello` is pointing to. To actually copy two strings we would do the following.

```c
#include <stdio.h>
// need to include to get string functions.
#include <string.h>

int main(void)
{
    char* hello = "Hello World!";
    // allocate space for jello.
    char jello[strlen(hello) + 1];
    // dst, org
    strcpy(jello, hello);
    jello[0] = 'J';
    printf("%s\n", jello);
    return 0;
}
```

In the code above we want to have the string `jello` to say `Jello World!`. To do this we need to allocate space for `jello`, if we don't then we when are calling `strcpy()`, this function will segfault because there is no space to put the copy of `hello`. To allocate the correct size of the space needed we will call another `<string.h>` function called `strlen()` which gets the size of the string. We add `1` to this for the null terminating character `\0`.

### C Strings and Structs

Let's look at the two structs below:

```c
#include <stdio.h>
#include <string.h>

// first.
struct double_string_ptrs
{
    char *a;
    char *b;
};
// second.
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
```

The first struct `double_string_ptrs` contains only pointers, so the actual C-strings are elsewhere. So the struct can go out of scope before or after the C-strings.

The second struct, `double_string_char_arrs` contains actual C-strings, so when the struct goes out of scope, so do the C-strings!

### `printf()` and `fprintf()`

`printf()` and `fprintf()` use formatted strings to produce output. The formatted string is then followed by the ordered list of values to insert.

Formatted strings contain *format specifiers* to insert useful values into output and these specifiers begin with %:

* %c: character
* %s: string (null-terminated)
* %d: decimal number.
* %x: hexadecimal number (great for P1a debugging)


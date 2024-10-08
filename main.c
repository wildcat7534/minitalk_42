#include <stdio.h>
#include "include/ft_printf.h"

int main()
{

    char *s = "\u20AC1.23";
    // unicode character emoji pizza
    char *emoji_pizza = "\U0001F355";

    printf("%s\n", s);  // €1.23
    ft_printf("%s\n", s);  // €1.23
    ft_printf("%s\n", emoji_pizza);  // €1.23
}
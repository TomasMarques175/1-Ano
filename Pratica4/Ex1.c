#include <stdio.h>
#include <stdlib.h>

void x(char * a, char *b)
{
    char *c;

    c = a;
    a = b;
    b = c;
    *c = *c + (*a-*b)/2;
    *b = '\0';
}

void y(char ** a, char ** b)
{
    char *c;

    c = *b;
    *b = *a;
    *a = c+1;
}

int main()
{
    char s1[] = "1234567890";
    char s2[] = "abcdefghij";
    char * a, *b;

    a = s2;
    b = s2+5;

    x(&s1[7], s1);
    y(&a, &b);
    *a = ' ';

    printf("%s\n", s1);
    printf("%s\n", s2);
    exit(0);
}

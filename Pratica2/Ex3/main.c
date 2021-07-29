#include <stdio.h>
#include <stdlib.h>

/* programa principal */
int main()
{
    int linha, simbolos, altura;

    /* Lê altura do triângulo e valida. Se for zero ou negativo, os ciclos seguintes não fazem nada. */
    printf("Insira altura do triangulo: ");
    if (scanf("%d",&altura)<1)
        return EXIT_FAILURE;

    /* escrever a parte crescente do triângulo */
    for(linha= 1 ; linha <= altura ; linha++)
    {
        for(simbolos= 1 ; simbolos <= linha ; simbolos++)
            printf("* ");
        printf("\n");
    }
    /* escrever a parte decrescente do triângulo */
    for(linha= altura - 1 ; linha >= 1 ; linha--)
    {
        for(simbolos= 1;  simbolos <= linha ; simbolos++)
            printf("* ");
        printf("\n");
    }
    return EXIT_SUCCESS;
}


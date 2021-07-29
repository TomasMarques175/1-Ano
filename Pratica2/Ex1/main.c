#include <stdio.h>
#include <stdlib.h>


/* programa principal */
int main()
{
    int n_natural;
    int divisor, n_divisores= 0, soma_divisores= 0;
    double media_divisores;

    /* lê um número natural do teclado, validando o que é lido */
    do {
        printf("Insira número natural\n");
        if (scanf("%d",&n_natural) != 1) {  /* se o scanf não devolve 1, é porque não conseguiu ler um número */
            printf("Faltam dados. Tente novamente...\n");
            scanf("%*s"); /* descartar uma string */
        }
    } while (n_natural < 1);

    /* percorrer todos os números de n_natural..1 e verificar se é divisor */
    for (divisor = n_natural ; divisor != 0 ; divisor--)   {
        if (n_natural%divisor == 0)  {
            /* "divisor" é mais um divisor: contabilizar e escrever */
            soma_divisores+= divisor;
            n_divisores++;
            printf("Divisor: %d\n", divisor);
        }
    }

    /* calcular e escrever a média dos divisores */
    media_divisores = (double)soma;
}

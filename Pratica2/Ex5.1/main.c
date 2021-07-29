#include <stdio.h>
#include <stdlib.h>

/* função que verifica se um número é primo: retorna 1 se é primo, 0 se não é primo */
int eprimo(int number){
    int i;

    /* por definição, números abaixo de 2 não são primos */
    if (number < 2)
        return 0;
    else
        if (number == 2) /* por definição, número 2 é primo */
            return 1;
        else
            for (i = 2 ; i < number ; i++)
            {
                if ( number%i == 0 )  /* se é divisível, não é primo */
                    return 0;
            }
    /* se não encontrou nenhum divisor, é primo */
    return 1;
}

/* programa principal */
int main()
{
    int n1;

    printf("Primos casados entre 1 e 1000:\n");
    /* percorre os números impares de dois em dois */
    for (n1 = 1 ; n1 <= 1000 ; n1+=2)
    {
        if (eprimo(n1) && eprimo(n1+2))
           printf("%d %d\n", n1, n1+2);
    }

    return EXIT_SUCCESS;
}

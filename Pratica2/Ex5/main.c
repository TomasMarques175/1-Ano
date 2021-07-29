/* ----------------------------------------------------------------------------------------
    P-2:
    Programa que lê diversos caracteres do teclado, escreve-os no écran, mas convertendo
todas as letras minúsculas para maiúsculas.
    A leitura termina no fim de uma linha: quando o utilizador carregar na tecla ENTER
------------------------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

/* Esta função converte uma letra minúscula em maiúscula. Outros caracteres não são alterados. */
char converte_maiuscula(char c)
{
    if((c >= 'a') && (c <= 'z'))
        /* se é minúscula, converte */
        c = c - 'a' + 'A';
    return c;
}

/* programa principal */
int main()
{
    char c = '\0'; /* inicializar com caracter zero para entrar no ciclo while em baixo */

    printf("Insert characters: ");
    while(c != '\n')
    {
        /* le caracter e guarda na variável c, validando a leitura */
        if (scanf("%c", &c) < 1)
            return EXIT_FAILURE;
        printf("%c", converte_maiuscula(c));
    }

    return EXIT_SUCCESS;
}


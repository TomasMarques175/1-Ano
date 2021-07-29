#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

/** \brief função que procura e devolve a última ocorrência do caractere "c" na string "str"
 *
 * \param str char*: string a usar
 * \param c char: caractere a pesquisar
 * \return char*: apontador para última ocorrência do caractere, ou NULL se não encontrar
 *
 */
char *my_strrchr(char *str, char c)
{
    char *ptr, *result=NULL;

    /* se a string for NULL, não se procura */
    if (str!=NULL)
        /* percorrer a string toda até ao terminador '\0' */
        for (ptr=str ; *ptr ; ptr++)
            if (*ptr==c) /* se encontrar o caractere, actualizar o resultado a devolver */
                result= ptr;
    return result;
}

int main()
{
    char string[MAX_LEN], caracter_a_procurar, *posicao_my_strrchr, *posicao_strrchr;

    printf("Introduza a string: ");
    fgets(string, MAX_LEN, stdin);
    printf("Introduza o caractere a procurar: ");
    scanf("%c", &caracter_a_procurar);

    printf("String lida: %s\n", string);
    posicao_my_strrchr= my_strrchr(string, caracter_a_procurar);
    /* confirmar resultado com a função da biblioteca */
    posicao_strrchr= strrchr(string, caracter_a_procurar);
    if (posicao_my_strrchr==posicao_strrchr)
        printf("my_strrchr deu igual ao strrchr\n");
    else
        printf("my_strrchr deu diferente do strrchr\n");
    /* escrever resultado */
    if (posicao_my_strrchr==NULL)
        printf("Não foi encontrada nenhuma ocorrência do caractere \"%c\" na string\n", caracter_a_procurar);
    else
        printf("A última ocorrência do caractere \"%c\" na string é na posição %d: %s\n",
            caracter_a_procurar, (int)(posicao_my_strrchr-string), posicao_my_strrchr);
    return EXIT_SUCCESS;
}

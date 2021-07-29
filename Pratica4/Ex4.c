#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* nome do ficheiro a ler */
//#define NOME_FICHEIRO "/usr/share/dict/words"
#define NOME_FICHEIRO "ficheiro.txt"
/* tamanho máximo de uma palavra */
#define MAX_LEN 100
/* de quantas em quantas palavras se realloca memória */
#define REALLOC_SIZE 10


/** \brief liberta a memória alocada num vector de strings
 *
 * \param lista_palavras[] char*: vector de strings a libertar
 * \param n_palavras int: quantas strings tem o vector de strings
 * \return void
 *
 */
void liberta_lista_palavras(char *lista_palavras[], int n_palavras)
{
    int i;

    if (lista_palavras!=NULL) {
        for (i=0 ; i < n_palavras ; i++)
            if (lista_palavras[i]!=NULL)
                free(lista_palavras[i]);
        free(lista_palavras);
    }
}


/** \brief procura uma string "palavra" numa vector de strings "lista_palavras" com "n_palavras" strings
 *
 * \param palavra char*: string a pesquisar
 * \param lista_palavras[] char*: vector de strings
 * \param n_palavras int: numero de strings no vector
 * \return int: -1 se não encontrou; posição no vector, se encontrou
 *
 */
int pesquisa_palavra(char *palavra, char *lista_palavras[], int n_palavras)
{
    int i;

    if (lista_palavras!=NULL && palavra!=NULL) {
        for (i=0 ; i < n_palavras ; i++)
            if (strcmp(lista_palavras[i], palavra)==0)
                return i;
    }
    return -1;
}


int main()
{
    FILE *ficheiro;
    char **lista_palavras= NULL, string[MAX_LEN], formato[MAX_LEN];
    int n_palavras; /* número de palavras lidas do ficheiro */
    int result, n;

    /* abrir o ficheiro */
    printf("Lendo o ficheiro \"%s\"\n", NOME_FICHEIRO);
    if ((ficheiro= fopen(NOME_FICHEIRO, "r"))==NULL)  {
        printf("Não consegui abrir o ficheiro. Programa terminado\n");
        exit(EXIT_FAILURE);
    }

    /* ler o ficheiro */
    n_palavras= 0;
    sprintf(formato, "%%%ds", MAX_LEN-1); // formato="%99s"
    do {
        if ((result= fscanf(ficheiro, formato, string))==1)  {
            /* fazer crescer o vector de palavras REALLOC_SIZE de cada vez */
            if (lista_palavras==NULL || (n_palavras%REALLOC_SIZE)==0)  {
                lista_palavras= (char**)realloc(lista_palavras, (n_palavras+REALLOC_SIZE)*sizeof(char*));
                if (lista_palavras==NULL)  {
                    printf("realloc falhou. ficheiro demasiado grande. programa terminado.\n");
                    exit(EXIT_FAILURE);
                }
            }
            /* alocar memória para a palavra lida: contar com o caractere '\0' terminador de string */
            if ((lista_palavras[n_palavras]= (char*)malloc(strlen(string)+1))==NULL)  {
                printf("malloc falhou. ficheiro demasiado grande. programa terminado.\n");
                liberta_lista_palavras(lista_palavras, n_palavras);
                exit(EXIT_FAILURE);
            }
            /* guarda a palavra e contabiliza mais uma palavra memorizada */
            strcpy(lista_palavras[n_palavras++], string);
        }
    } while (result != EOF);
    fclose(ficheiro);
    printf("Ficheiro lido. Total de %d palavras lidas.\n", n_palavras);

    /* pesquisar uma palavra */
    printf("Introduza a palavra a procurar: ");
    if ((result= scanf(formato, string))==1)  {
        printf("Li a palavra \"%s\"\n", string);
        n= pesquisa_palavra(string, lista_palavras, n_palavras);
        if (n<0)
            printf("Não encontrei essa palavra no ficheiro.\n");
        else
            printf("Encontrei a palavra no ficheiro. É a palavra #%d.\n", n+1);
    } else
        printf("Não consegui ler uma palavra.\n");
    /* libertar memória antes de terminar */
    liberta_lista_palavras(lista_palavras, n_palavras);
    return EXIT_SUCCESS;
}

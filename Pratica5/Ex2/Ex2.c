#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* nossos includes */
#include "phonebook.h"

/* tamanho máximo de uma palavra */
#define STR_SIZE 200

/* nome do ficheiro com a lista telefónica */
#define NOME_FICHEIRO "phonebook.txt"


/** \brief programa para gerir uma lista telefónica, utilizando vectores alocados dinamicamente
 *
 * \return int: 0 em caso se sucesso, 1 em caso de erro
 *
 */

int main()
{
    phoneEntry *phonebook= NULL;    /* vector com a lista telefónica a ser alocado dinamicamente */

    char pname[STR_SIZE]= "end";    /* nome a pesquisar */

    FILE *fp;

    fp= fopen(NOME_FICHEIRO, "r");

    if (fp == NULL)  {
        printf("ERROR 1: Can't open input file %s!\n", NOME_FICHEIRO);
        exit(EXIT_FAILURE);
    }

    load_phonebook(fp, &phonebook);

    fclose(fp);

    printf("===== Phonebook Original =====\n");
    print_number(phonebook, "*");
    sort_phonebook(phonebook);
    printf("===== Phonebook Sorted =====\n");
    print_number(phonebook, "*");

    do  {
        printf("\nName to find or \"*\" to show all or \"end\" to finish: ");
        scanf("%s", pname);
        print_number(phonebook, pname);
    } while(strcmp(pname, "end") != 0);

    free_phonebook(phonebook);
    
    return EXIT_SUCCESS;
}

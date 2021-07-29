#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* nossos includes */
#include "phonebook.h"

/* tamanho máximo de uma linha */
#define LINE_SIZE 200
/* tamanho máximo de uma palavra */
#define STR_SIZE 200
/* de quantas em quantas entradas na lista telefónica se realloca memória */
#define REALLOC_SIZE 10 //Dúvida: porque 10?

//Dúvidas: pointers em funções

/** \brief lê uma lista telefónica de um ficheiro
 *
 * \param fp FILE*: ponteiro para o ficheiro já aberto
 * \param phonebook phoneEntry**: vector de entradas da lista telefónica. Como não é passado o número de entradas,
 *                                convenciona-se que o vector acaba com um nome a NULL.
 * \return void
 *
 */
void load_phonebook(FILE *fp, phoneEntry **phonebook)
{
    int contact_number= 0;  /* para contar o número de registos preenchidos no vector */
    char line[LINE_SIZE];   /* para guardar uma linha lida do ficheiro */
    char name[STR_SIZE];    /* para guardar um nome da lista telefónica */
    unsigned int telephone; /* para guardar um número de telefone */

    phoneEntry *ptr_phoneEntry, *aux_ptr_phoneEntry;

    ptr_phoneEntry= NULL; // alternativamente, podeia-se utilizar (*phonebook)
    while( fgets(line, LINE_SIZE, fp) != NULL )  { // ler uma linha do ficheiro
    
        if (sscanf(line, "%s %u", name, &telephone) != 2) { // ler a informação da linha
            printf("ERROR parsing phonebook line\n");
            continue;  // saltar para a próxima linha
        }

        /* aumentar o tamanho do vector lista telefónica REALLOC_SIZE de cada vez */
        if (ptr_phoneEntry==NULL || (contact_number%REALLOC_SIZE)==0)  {
            aux_ptr_phoneEntry= (phoneEntry *)realloc(ptr_phoneEntry, (contact_number+REALLOC_SIZE)*sizeof(phoneEntry));
            if (aux_ptr_phoneEntry==NULL)  {
                printf("ERROR 2: Memory allocation for phonebook failed.\n");
                contact_number--; /* sair do ciclo para pôr o terminador no vector na última posição alocada */
                break;
            } else
                ptr_phoneEntry= aux_ptr_phoneEntry;
        }

        /* alocar memória para o nome, incluíndo o caractere terminador de string '\0' */
        if ((ptr_phoneEntry[contact_number].name= (char*)malloc((strlen(name)+1)*sizeof(char)))==NULL) {
            printf("ERROR 3: Memory allocation for string failed.\n");
            break; /* sair do ciclo para pôr o terminador do vector */
        }
        /* guardar a informação no vector da lista telefónica */
        strcpy(ptr_phoneEntry[contact_number].name, name);
        ptr_phoneEntry[contact_number].number= telephone;
        contact_number++;
    }

    /* colocar uma estrutura phoneEntry com name a NULL no fim do vector para marcar o seu fim */
    if (ptr_phoneEntry==NULL || (contact_number%REALLOC_SIZE)==0)  {
        /* neste caso, basta aumentar a dimensão do vector por uma unidade */
        aux_ptr_phoneEntry= (phoneEntry*)realloc(ptr_phoneEntry, (contact_number+1)*sizeof(phoneEntry));
        if (aux_ptr_phoneEntry==NULL)  {
            printf("ERROR 4: Memory allocation for phonebook failed.\n");
            contact_number--; /* pôr o terminador na última posição do vector alocada */
        } else
            ptr_phoneEntry= aux_ptr_phoneEntry;
    }
    if (ptr_phoneEntry!=NULL)  {
        ptr_phoneEntry[contact_number].name= NULL;
        ptr_phoneEntry[contact_number].number= 0;
        contact_number++;
    }

    /* retornar a lista telefónica, preenchendo o parâmetro da função */
    *phonebook= ptr_phoneEntry;
}


 /** \brief escrever o conteúdo de uma ou mais entradas da lista telefónica no écran
  *
  * \param phonebook phoneEntry*: vector de entradas da lista telefónica. Como não é passado o número de entradas,
  *                               convenciona-se que o vector acaba com um nome a NULL.
  * \param pname char*: nome a procurar, ou "*" para mostrar toda a lista telefónica
  * \return void
  *
  */
 void print_number(phoneEntry *phonebook, char *pname)
{
    bool print_all_flag= false;

    if (phonebook==NULL || pname==NULL)
        return;
    if (strcmp(pname, "*") == 0)
        print_all_flag= true;
    while((*phonebook).name != NULL)  { /* pode-se fazer: phonebook->name como na linha seguinte */
        if (print_all_flag || (strcmp(pname, phonebook->name) == 0)) {
            //printf("%s %u\n", (*phonebook).name, (*phonebook).number);  /* é igual à linha seguinte */
            printf("%s %u\n", phonebook->name, phonebook->number);  /* é igual à linha anterior */
        }
        phonebook++;
    }
}


/** \brief libertar a memória alocada para a lista telefónica
 *
 * \param phonebook phoneEntry*: vector de entradas da lista telefónica. Como não é passado o número de entradas,
 *                               convenciona-se que o vector acaba com um nome a NULL.
 * \return void
 *
 */
void free_phonebook(phoneEntry *phonebook)
{
    phoneEntry *aux_phonebook;

    if (phonebook!=NULL)  {
        for (aux_phonebook= phonebook ; aux_phonebook->name != NULL ; aux_phonebook++) {
            free(aux_phonebook->name);  /* libertar nome de uma entrada da lista telefónica */
        }
        free(phonebook);  /* libertar o vector da lista telefónica */
    }
}


/** \brief troca o conteúdo de 2 entradas da lista telefónica
 *
 * \param phonebook1 phoneEntry*: apontador para a 1a entrada da lista telefónica
 * \param phonebook2 phoneEntry*: apontador para a 2a entrada da lista telefónica
 * \return void
 *
 */
void swap_phoneEntry(phoneEntry *phonebook1, phoneEntry *phonebook2)
{
    phoneEntry aux;

    if (phonebook1==NULL || phonebook2==NULL)
        return;
    /* troca estruturas */
    aux= *phonebook1;
    *phonebook1= *phonebook2;
    *phonebook2= aux;
    /* alternativamente, podia-se copiar campo a campo */
    /* ou usar a função memcpy() para copiar as estruturas */
}


/** \brief ordena uma lista telefónica por ordem alfabética do nome
 *
 * \param phonebook phoneEntry*: vector de entradas da lista telefónica. Como não é passado o número de entradas,
 *                               convenciona-se que o vector acaba com um nome a NULL.
 * \return void
 *
 */
void sort_phonebook(phoneEntry *phonebook)
{
    phoneEntry *left, *right;
    bool trocas= true;

    /* se a lista telefónica está vazia, não há nada a fazer */
    if (phonebook==NULL || phonebook->name==NULL)
        return;
    /* algoritmo de ordenação BubbleSort */
    /* percorrer a lista toda, enquanto houver trocas */
    while (trocas) {
        trocas= false;
        for (left= phonebook, right= left + 1 ; right->name != NULL ; left++, right++) {
            /* se encontra 2 entradas consecutivas fora de ordem, troca-as de ordem */
            if (strcmp(left->name, right->name) > 0)  {
                swap_phoneEntry(left, right);
                trocas= true;
            }
        }
    }
}

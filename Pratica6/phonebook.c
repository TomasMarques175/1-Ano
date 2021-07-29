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



/** \brief cria um elemento da lista, alocando memória para o novo elemento da lista e para o nome
 *
 * \param name char*: ponteiro para o nome
 * \param number unsigned int: número de telefone
 * \return DLLNode*: ponteiro para o elemento da lista criado, NULL se não houver memória
 *
 */
DLLNode *create_phoneEntry(char *name, unsigned int number)
{
    DLLNode *ptr;

    ptr= (DLLNode *)malloc(sizeof(DLLNode));
    if (ptr!=NULL)  {
        /* alocar memória para a string do nome, incluíndo o caractere terminador de string '\0' */
        if ((ptr->data.name= (char *)malloc(strlen(name)+1))==NULL)  {
            /* se falhou a alocação, liberta a estrutura e retorna NULL */
            free(ptr);
            return NULL;
        }
        strcpy(ptr->data.name, name);
        ptr->data.number= number;
        /* por segurança, pôr os ponteiros a NULL */
        ptr->next= ptr->prev= NULL;
    }
    return ptr;
}


/** \brief libertar a memória alocada para um elemento da lista telefónica
 *
 * \param ptr DLLNode*: ponteiro para o elemento a libertar.
 * \return void
 *
 */
void free_node(DLLNode *ptr)
{
    if (ptr != NULL)  {
        if (ptr->data.name!=NULL)
            free(ptr->data.name);  /* libertar primeiro a string com o nome */
        free(ptr);
    }
}


/** \brief libertar a memória alocada para toda a lista telefónica
 *
 * \param head DLLNode*: cabeça da lista.
 * \return void
 *
 */
void free_list(DLLNode *head)
{
    DLLNode *aux;

    while (head!=NULL) {
        /* avançar na lista */
        aux= head;
        head= head->next;
        /* libertar elemento */
        free_node(aux);
    }
}


/** \brief insere um elemento no início da lista
 *
 * \param head DLLNode*: cabeça de lista
 * \param ptr DLLNode*: ponteiro para o novo elemento a inserir no início da lista
 * \return DLLNode*: novo cabeça de lista, que deve ter sido alterado para ptr
 *
 */
DLLNode *insert_head(DLLNode *head, DLLNode *ptr)
{
    if (head==NULL)  {
        /* lista vazia: insere primeiro elemento da lista */
        head= ptr;
        ptr->next= ptr->prev= NULL;
    } else {
        /* pôr no início da lista */
        head->prev= ptr;
        ptr->next= head;
        ptr->prev= NULL;
        head= ptr;
    }
    return head;
}


/** \brief insere um elemento no fim da lista
 *
 * \param head DLLNode**: cabeça de lista
 * \param tail DLLNode**: cauda da lista
 * \param ptr DLLNode*: ponteiro para o novo elemento a inserir no fim da lista
 * \return void
 *
 */
void insert_end(DLLNode **head, DLLNode **tail, DLLNode *ptr)
{
    if (*tail==NULL)  {
        /* primeiro elemento da lista */
        *head= *tail= ptr;
        ptr->next= ptr->prev= NULL;
    } else {
        /* pôr no fim */
        ptr->next= NULL;
        ptr->prev= *tail;
        (*tail)->next= ptr;
        *tail= ptr;
    }
}


/** \brief lê uma lista telefónica de um ficheiro para uma lista
 *
 * \param fp FILE*: ponteiro para o ficheiro já aberto
 * \return DLLNode*cabeça de lista da lista criada
 *
 */
DLLNode *load_phonebook(FILE *fp)
{
    char line[LINE_SIZE];   /* para guardar uma linha lida do ficheiro */
    char name[STR_SIZE];    /* para guardar um nome da lista telefónica */
    unsigned int telephone; /* para guardar um número de telefone */
    DLLNode *head,          /* cabeça da lista: ponteiro para o primeiro elemento da lista */
            *tail,          /* cauda da lista: ponteiro para o último elemento da lista */
            *aux_ptr;       /* ponteiro auxiliar para a nova entrada criada para inserir na lista */

    head= tail= NULL;
    while( fgets(line, LINE_SIZE, fp) != NULL )  { // ler uma linha do ficheiro
        if (sscanf(line, "%s %u", name, &telephone) != 2) { // ler a informação da linha
            printf("ERROR parsing phonebook line\n");
            continue;  // saltar para a próxima linha
        }
        aux_ptr= create_phoneEntry(name, telephone);
        if (aux_ptr==NULL)  {
            printf("ERROR 1: Memory allocation for list element failed.\n");
            return head;
        } else
            insert_end(&head, &tail, aux_ptr);
    }
    /* retornar a lista telefónica */
    return head;
}


/** \brief contar o número de entradas da lista telefónica
 *
 * \param head DLLNode*: cabeça de lista
 * \return unsigned: o número de entradas encontradas
 *
 */
unsigned contar_elementos(DLLNode *head)
{
    unsigned int count;

    for (count= 0 ; head!=NULL ; head= head->next, count++)
        ;
    return count;
}


/** \brief escrever o conteúdo de uma ou mais entradas da lista telefónica no écran para um dado nome
 *
 * \param head DLLNode*: cabeça de lista da lista telefónica.
 * \param pname char*: nome a procurar, ou "*" para mostrar todas as entradas
 * \return void
 *
 */
void print_number(DLLNode *head, char *pname)
{
    bool print_all_flag= false;
    DLLNode *ptr;

    if (pname==NULL)
        return;
    if (strcmp(pname, "*") == 0)
        print_all_flag= true;
    for (ptr= head ; ptr!=NULL ; ptr= ptr->next)
        if (print_all_flag || (strcmp(pname, ptr->data.name) == 0))
            printf("%s %u\n", ptr->data.name, ptr->data.number);
}


/** \brief escrever o conteúdo de uma ou mais entradas da lista telefónica no écran, procurando por número de telefone
 *
 * \param head DLLNode*: cabeça de lista da lista telefónica.
 * \param number unsigned int: número de telefone a procurar
 * \return void
 *
 */
void print_by_number(DLLNode *head, unsigned int number)
{
    DLLNode *ptr;

    for (ptr= head ; ptr!=NULL ; ptr= ptr->next)
        if (ptr->data.number == number)
            printf("%s %u\n", ptr->data.name, ptr->data.number);
}


/** \brief escrever o conteúdo da lista telefónica num ficheiro
 *
 * \param fp FILE*: ficheiro aberto para escrita
 * \param head DLLNode*: cabeça de lista da lista telefónica.
 * \return void
 *
 */
void write_phonebook(FILE *fp, DLLNode *head)
{
    DLLNode *ptr;

    if (fp==NULL || head==NULL)
        return;
    for (ptr= head ; ptr!=NULL ; ptr= ptr->next)
            fprintf(fp, "%s %u\n", ptr->data.name, ptr->data.number);
}


/** \brief troca a ordem de 2 entradas consecutivas da lista telefónica
 *
 * \param head DLLNode*: cabeça de lista da lista telefónica.
 * \param ptr1 DLLNode*: apontador para a 1a entrada da lista telefónica
 * \param ptr2 DLLNode*: apontador para a 2a entrada da lista telefónica
 * \return DLLNode*: o cabeça de lista, que pode ter sido alterado
 *
 */
DLLNode *swap(DLLNode *head, DLLNode *ptr1, DLLNode *ptr2)
{
    if (head==NULL || ptr1==NULL || ptr2==NULL)
        return head;
    /* troca elementos da lista */
    ptr1->next= ptr2->next;
    ptr2->prev= ptr1->prev;
    if (ptr1->prev==NULL)  {
        /* é o primeiro da lista */
        head= ptr2;
    } else {
        ptr1->prev->next= ptr2;
    }
    if (ptr2->next==NULL) {
        /* é o último da lista */
    } else {
        ptr2->next->prev= ptr1;
    }
    ptr2->next= ptr1;
    ptr1->prev= ptr2;
    return head;
}


/** \brief ordena uma lista telefónica por ordem alfabética do nome
 *
 * \param head DLLNode*: cabeça de lista da lista telefónica.
 * \param ordem ordenacao: define se ordena por nome ou número de telefone
 * \return DLLNode*: o cabeça de lista, que pode ter sido alterado
 *
 */
DLLNode *sort_phonebook(DLLNode *head, ordenacao ordem)
{
    DLLNode *left, *right;
    bool trocas= true;

    /* se a lista telefónica está vazia, não há nada a fazer */
    if (head==NULL)
        return head;

    /* algoritmo de ordenação BubbleSort */
    /* percorrer a lista toda, enquanto houver trocas */
    while (trocas) {
        trocas= false;
        left= head;
        right= head->next;
        while (right!=NULL )  {
            /* se encontra 2 entradas consecutivas fora de ordem, troca-as de ordem */
            if ((ordem==NOME && strcmp(left->data.name, right->data.name) > 0) ||
                (ordem==TELEFONE && left->data.number > right->data.number) )  {
                trocas= true; /* houve 1 troca, necessário percorrer a lista toda novamente */
                head= swap(head, left, right);
                /* avançar os ponteiros sabendo que left e right estão trocados */
                right= left->next;
            } else { /* estão na ordem, avança para as 2 entradas seguintes */
                left= right;
                right= right->next;
            }
        }
    }
    return head;
}


/** \brief apagar uma entrada da lista
 *
 * \param head DLLNode*: cabeça de lista da lista telefónica.
 * \param ptr DLLNode*: apontador para a entrada a apagar
 * \return DLLNode*: novo cabeça de lista, que pode ter sido alterado
 *
 */
DLLNode *remove_from_list(DLLNode *head, DLLNode *ptr)
{
    if (ptr!=NULL && head!=NULL)  {
        if (ptr==head) {
            /* primeiro da lista */
            head= head->next;
            if (head!=NULL)  /* se a lista não ficou vazia */
                head->prev= NULL;
        } else  {
            ptr->prev->next= ptr->next;
            if (ptr->next!=NULL)
                ptr->next->prev= ptr->prev;
        }
        /* libertar o elemento apagado */
        free_node(ptr);
    }
    return head;
}


/** \brief apagar uma entrada da lista telefónica
 *
 * \param head DLLNode*: cabeça de lista de entradas da lista telefónica.
 * \param name char*: nome a procurar
 * \param number unsigned int: número de telefone a procurar
 * \return DLLNode*: novo cabeça de lista, que pode ter sido alterado
 *
 */
DLLNode *delete_entry(DLLNode *head, char* name, unsigned int number)
{
    DLLNode *ptr;

    for (ptr= head ; ptr!=NULL ; ptr= ptr->next)
        if (ptr->data.number == number && strcmp(ptr->data.name, name)==0 )
            return remove_from_list(head, ptr);
    /* não encontrou */
    return head;
}


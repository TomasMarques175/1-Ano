#ifndef PHONEBOOK_H_INCLUDED
#define PHONEBOOK_H_INCLUDED

/* Estrutura que guarda uma entrada da lista telefónica */
typedef struct  {
    char *name;           /* nome */
    unsigned int number;  /* número de telefone */
} phoneEntry;

/* Nó da lista duplamente ligada */
typedef struct _DLLNode  {
    phoneEntry data;
    struct _DLLNode *prev;
    struct _DLLNode *next;
} DLLNode;

/* qual o critério de ordenação a usar */
typedef enum _ordenacao {
    NOME,
    TELEFONE
} ordenacao;


/* cabeçalhos das funções para gerir uma lista telefónica */

/** \brief cria um elemento da lista, alocando memória para o novo elemento da lista e para o nome
 *
 * \param name char*: ponteiro para o nome
 * \param number unsigned int: número de telefone
 * \return DLLNode*: ponteiro para o elemento da lista criado, NULL se não houver memória
 *
 */
DLLNode *create_phoneEntry(char *name, unsigned int number);

/** \brief libertar a memória alocada para toda a lista telefónica
 *
 * \param head DLLNode*: cabeça da lista.
 * \return void
 *
 */
void free_list(DLLNode *head);

/** \brief insere um elemento no início da lista
 *
 * \param head DLLNode*: cabeça de lista
 * \param ptr DLLNode*: ponteiro para o novo elemento a inserir no início da lista
 * \return DLLNode*: novo cabeça de lista, que deve ter sido alterado para ptr
 *
 */
DLLNode *insert_head(DLLNode *head, DLLNode *ptr);

/** \brief lê uma lista telefónica de um ficheiro para uma lista
 *
 * \param fp FILE*: ponteiro para o ficheiro já aberto
 * \return DLLNode*cabeça de lista da lista criada
 *
 */
DLLNode *load_phonebook(FILE *fp);

/** \brief contar o número de entradas da lista telefónica
 *
 * \param head DLLNode*: cabeça de lista
 * \return unsigned: o número de entradas encontradas
 *
 */
unsigned contar_elementos(DLLNode *head);

/** \brief escrever o conteúdo de uma ou mais entradas da lista telefónica no écran para um dado nome
 *
 * \param head DLLNode*: cabeça de lista da lista telefónica.
 * \param pname char*: nome a procurar, ou "*" para mostrar todas as entradas
 * \return void
 *
 */
void print_number(DLLNode *head, char *pname);

/** \brief escrever o conteúdo de uma ou mais entradas da lista telefónica no écran, procurando por número de telefone
 *
 * \param head DLLNode*: cabeça de lista da lista telefónica.
 * \param number unsigned int: número de telefone a procurar
 * \return void
 *
 */
void print_by_number(DLLNode *head, unsigned int number);

/** \brief escrever o conteúdo da lista telefónica num ficheiro
 *
 * \param fp FILE*: ficheiro aberto para escrita
 * \param head DLLNode*: cabeça de lista da lista telefónica.
 * \return void
 *
 */
void write_phonebook(FILE *fp, DLLNode *head);

/** \brief ordena uma lista telefónica por ordem alfabética do nome
 *
 * \param head DLLNode*: cabeça de lista da lista telefónica.
 * \param ordem ordenacao: define se ordena por nome ou número de telefone
 * \return DLLNode*: o cabeça de lista, que pode ter sido alterado
 *
 */
DLLNode *sort_phonebook(DLLNode *head, ordenacao ordem);


/** \brief apagar uma entrada da lista telefónica
 *
 * \param head DLLNode*: cabeça de lista de entradas da lista telefónica.
 * \param name char*: nome a procurar
 * \param number unsigned int: número de telefone a procurar
 * \return DLLNode*: novo cabeça de lista, que pode ter sido alterado
 *
 */
DLLNode *delete_entry(DLLNode *head, char* name, unsigned int number);


#endif // PHONEBOOK_H_INCLUDED

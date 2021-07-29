#ifndef PHONEBOOK_H_INCLUDED
#define PHONEBOOK_H_INCLUDED

/* Estrutura que guarda uma entrada da lista telefónica */
typedef struct  {
    char *name;           /* nome */
    unsigned int number;  /* número de telefone */
} phoneEntry;

/* cabeçalhos das funções para gerir uma lista telefónica */
void load_phonebook(FILE *, phoneEntry **);
void print_number(phoneEntry *, char *);
void sort_phonebook(phoneEntry *);
void free_phonebook(phoneEntry *);

#endif // PHONEBOOK_H_INCLUDED
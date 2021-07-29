#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>

/* nossos includes */
#include "phonebook.h"

/* nome do ficheiro com a lista telefónica por omissão */
#define NOME_FICHEIRO "phonebook.txt"


/* algumas opções da linha de comando */
typedef enum _opcoes {
    NENHUMA,
    PESQUISAR,
    ADICIONAR,
    REMOVER
} opcoes;


/** \brief mostra as instruções de utilização
 *
 * \param programa char*: nome do programa
 * \return void
 *
 */
void usage(char *programa)
{
    printf("Utilização: %s [opções] [nome]\n", programa);
    printf("opções válidas:\n");
    printf("[-h]\t\t   mostrar instruções\n");
    printf("[-i ficheiro]\t   usar <ficheiro> de entrada/saída em vez de \"%s\"\n", NOME_FICHEIRO);
    printf("[-o nome|telefone] ordenar por nome ou por telefone\n");
    printf("[-n nome]\t   definir <nome> a pesquisar/adicionar/remover\n");
    printf("[-t telefone]\t   definir <telefone> a pesquisar/adicionar/remover\n");
    printf("[-a]\t\t   adicionar nova entrada, sendo necessário nome e telefone\n");
    printf("[-r]\t\t   remover uma entrada, sendo necessário nome e telefone\n");
    printf("[-p]\t\t   pesquisar entradas, sendo necessário nome ou telefone; nome=\"*\" mostra todas\n");
    printf("[-c]\t\t   contar entradas na lista telefónica\n");
}


/** \brief programa principal para gerir uma lista telefónica usando lista duplamente ligadas
 *
 * \param argc int:     número de argumentos na linha de comando
 * \param argv[] char*: vector de strings com os argumentos na linha de comando
 * \return int:         sucesso do programa
 *
 */
 int main(int argc, char *argv[])
{
    DLLNode *phonebook_head= NULL;  /* lista de entradas na lista telefónica */
    DLLNode *ptr;                   /* apontador auxiliar */
    char *pname= "*";               /* nome */
    unsigned int telefone=0;        /* número de telefone */
    char *ficheiro= NOME_FICHEIRO;  /* nome do ficheiro com a lista telefónica */
    FILE *fp;                       /* para ler ou escrever o ficheiro */
    ordenacao ordem= NOME;          /* modo de ordenação: por omissão é por ordem alfabética de nome */
    bool ordenar= false;            /* flag auxiliar: true se for preciso ordenar a lista */
    bool contar= false;             /* flag auxiliar: true se for preciso contar a entradas na lista */
    bool escrever= false;           /* flag auxiliar: true se for preciso re-escrever o ficheiro no fim */
    bool nomevalido= false, telefonevalido= false;  /* flags para indicar se recebemos nome válido e telefone válido  */
    opcoes opcao= NENHUMA;          /* opção escolhida: pesquisar/adicionar/remover */
    int opt= 'h';    /* para getopt() */

    opterr= 0; /* para getopt() não gerar erros por opções inválidas */
    /* processar as opções da linha de comando */
    while ((opt= getopt(argc, argv, "i:n:t:arpco:h")) != -1) {
        switch (opt) {
            case 'i': /* nome do ficheiro de entrada/saída */
                ficheiro= optarg;
                break;
            case 'n': /* nome a adicionar/remover/pesquisar */
                pname= optarg;
                nomevalido= true;
                if (opcao==NENHUMA)
                    opcao= PESQUISAR;
                break;
            case 't': /* telefone a adicionar/remover/pesquisar */
                if (sscanf(optarg, "%u", &telefone)==1) {
                    telefonevalido= true;
                    if (opcao==NENHUMA)
                        opcao= PESQUISAR;
                } else
                    printf("Número de telefone \"%s\" inválido. Ignorado\n", optarg);
                break;
            case 'a':
                opcao= ADICIONAR;
                break;
            case 'r':
                opcao= REMOVER;
                break;
            case 'p':
                opcao= PESQUISAR;
                break;
            case 'c': /* contar */
                contar= true;
                break;
            case 'o': /* ordenar: verificar o parâmetro com modo de ordenação */
                if (strcmp(optarg, "nome")==0) {
                    ordem= NOME;
                    ordenar= true;
                } else if (strcmp(optarg, "telefone")==0) {
                    ordem= TELEFONE;
                    ordenar= true;
                } else {
                    printf("opção de ordenação \"%s\" desconhecida. ignorada.\n", optarg);
                    usage(argv[0]);
                }
                break;
            default: /* '?' opções inválidas, continua para o próximo case */
                printf("Erro: opção '%c' desconhecida.\n\n", optopt);
            case 'h': /* help */
                usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    if (optind<argc)  { /* há argumentos que não são opções: é um nome e dá para pesquisar */
        pname= argv[optind];
        nomevalido= true;
        if (opcao==NENHUMA)
            opcao= PESQUISAR;
    }

    /* ler o ficheiro para a lista */
    fp= fopen(ficheiro, "r");
    if (fp == NULL)  {
        printf("Cannot open input file \"%s\". A new file will be created.\n", ficheiro);
        escrever= true; /* forçar a criação do ficheiro no fim */
    } else {
        phonebook_head= load_phonebook(fp);
        fclose(fp);
    }
#ifdef DEBUG
    printf("===== Phonebook Original =====\n");
    print_number(phonebook_head, "*");
#endif // DEBUG

    /* executar as opções lidas */
    switch (opcao) {
        case ADICIONAR:
            if (nomevalido && telefonevalido)  {
                ptr= create_phoneEntry(pname, telefone);
                if (ptr==NULL)  {
                    printf("ERROR 1: Memory allocation for list element failed.\n");
                    free_list(phonebook_head);
                    exit(EXIT_FAILURE);
                } else { /* inserir nova entrada no início da lista */
                    phonebook_head= insert_head(phonebook_head, ptr);
                    escrever= true; /* deve escrever o ficheiro no fim */
                }
            } else {
                printf("Faltam parâmetros para inserir nova entrada na lista telefónica\n");
                usage(argv[0]);
            }
            break;
        case REMOVER:
            if (nomevalido && telefonevalido)  {
                phonebook_head= delete_entry(phonebook_head, pname, telefone);
                escrever= true; /* deve escrever o ficheiro no fim */
            } else {
                printf("Faltam parâmetros para apagar entrada da lista telefónica\n");
                usage(argv[0]);
            }
            break;
        case PESQUISAR:
            if (nomevalido)
                print_number(phonebook_head, pname);
            else if (telefonevalido)
                print_by_number(phonebook_head, telefone);
            if (!nomevalido && !telefonevalido) {
                printf("Faltam parâmetros para a pesquisa\n");
                usage(argv[0]);
            }
            break;
        case NENHUMA:
            if (!contar && !ordenar && !escrever)
                usage(argv[0]);
            break;
    }
    if (contar)
        printf("A lista telefónica tem %u entradas\n", contar_elementos(phonebook_head));
    if (ordenar) {
        phonebook_head= sort_phonebook(phonebook_head, ordem);
        escrever= true;  /* é preciso re-escrever o ficheiro já ordenado */
    }
    if (escrever) {
        fp= fopen(ficheiro, "w");
        if (fp == NULL)  {
            printf("ERROR: Cannot open output file \"%s\"!\n", ficheiro);
            free_list(phonebook_head);
            exit(EXIT_FAILURE);
        }
        write_phonebook(fp, phonebook_head);
        fclose(fp);
    }
#ifdef DEBUG
    printf("===== Phonebook Final =====\n");
    print_number(phonebook_head, "*");
#endif // DEBUG

    free_list(phonebook_head);
    return EXIT_SUCCESS;
}

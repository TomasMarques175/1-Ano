/*=======================================================================================================*/
/*Programa: covid19                                                                                      */
/*                                                                                                       */
/*Descrição: Este programa recebe de um ficheiro de dados selecionado pelo utilizador                    */
/*           um conjunto de dados cria uma lista com esses mesmos dados e faz a sua seleção,             */
/*           restrição e ordenação de acordo com as opções escolhidas pelo utilizador,                   */
/*           após realizar as alterações imprime para o terminal e para o ficheiro de escrita escolhido  */
/*           a lista.                                                                                    */
/*                                                                                                       */
/*Ficheiros:                                                                                             */
/*  (1) main.c: prog: principal main() e função com as instruções de utilização                          */
/*  (2) covid19.c: funções utilizadas no main()                                                          */
/*  (3) covid19.h: cabeçalhos das funções e estruturas utilizadas para definir a lista com os dados      */  
/*                                                                                                       */
/*Autoria: Tomás Marques nº100104                                       Data: 2020/2021                  */
/*=======================================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <getopt.h>

/* nossos includes */
#include "covid19.h"


/** \brief mostra as instruções de utilização
 *
 * \return void
 *
 */
void guia()
{
    printf  ("\
    Instruções de utilização:\n\n\
    Opções de Leitura(campo obrigatório):\n\
        -i filename.csv ->ler ficheiro de texto\n\
        -i filename.dat ->ler ficheiro binário\n\
    Opções de Escrita(campo obrigatório):\n\
        -o filename.csv ->ecrever ficheiro de texto\n\
        -o filename.dat ->ecrever ficheiro de binário\n\
    Opções de Leitura dos dados:\n\
        -L all -> lê todos os países\n\
        -L (continente) -> lê todos os países do continente expecificado\n\
    Opções de ordenação dos dados:\n\
        -S alfa -> ordena por ordem alfabética os países selecionados\n\
        -S pop -> ordenda por ordem decrescente de acordo com a população dos países selecionados\n\
        -S inf (yyyy-ww) -> ordenda por ordem decrescente de acordo com o total de infetados por países numa determinada data yyyy-ww\n\
        -S dea (yyyy-ww) -> ordenda por ordem decrescente de acordo com o total de mortes por países numa determinada data yyyy-ww\n\
    Opções de Seleção dos dados:\n\
        -D inf -> selecionar para cada país a semana com mais infectados.\n\
        -D dea -> selecionar para cada país a semana com mais mortes.\n\
        -D racioinf -> o selecionar para cada país a semana com maior rácio de infectados por 100000 habitantes.\n\
        -D raciodea -> selecionar para cada país a semana com maior rácio de mortes por milhão de habitantes.\n\
    Opções de Restrição dos dados:\n\
        -P min (n) -> restringe os dados a apenas países com mais de n mil habitantes (sendo n um inteiro)\n\
        -P max (n) -> restringe os dados a apenas países com menos de n mil habitantes (sendo n um inteiro)\n\
        -P date (yyyy-ww) -> restringe os dados apenas a dados relativos à semana indicada\n\
        -P dates (yyyy-ww) (yyyy-ww) -> restringe os dados apenas a dados entre as semanas indicadas (a ordem pela qual são especificadas a semana inicial e final deve ser irrelevante)\n\
            ");
           exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    FILE *fp_in; /* apontador do ficheiro de leitura */
    FILE *fp_out; /* apontador do ficheiro de escrita */
    Pais *ListHead = NULL; /* cabeça da lista principal */

    char nome_do_continente[30] = "all"; /* dado que faz a seleção dos países no campo -L(Leitura) */
    char ordenacao[30] = "alfa"; /* 1º dado do campo -S(Ordenação) */
    char selecao[30] = {0}; /* dado do campo -D(Seleção) */
    char dataS1[30] = {0}; /* data utilizada no campo -S(Ordenação) */
    char restricao[30] = {0}; /* dado do campo -P(Restrição) */
    int num_habitantes = 0;  /* numero maximo ou minimo de habitatents no campo -P(Restrição) */
    char dataP1[30] = {0}; /* 1ª data utilizada no campo -P(Restrição) */
    char dataP2[30] = {0}; /* 2ª data utilizada no campo -P(Restrição) */
    char input_filename[30] = {0}; /* nome do ficheiro a ler */
    char output_filename[30] = {0}; /* nome do ficheiro a escrever */

    int option; /* para getopt() */

    /* processar as opções da linha de comando */
    while ((option = getopt(argc, argv, "L:S:D:P:i:o:")) != -1)
    {
        switch(option)
        {
            case 'L': /* Opções de Leitura dos Dados */
                if ( strcmp(optarg, "America") == 0 || strcmp(optarg, "Europe") == 0 || strcmp(optarg, "Asia") == 0 || strcmp(optarg, "Oceania") == 0 || strcmp(optarg, "Africa") == 0 || strcmp(optarg, "all") == 0 || strcmp(optarg, "") == 0 )
                {
                sscanf(optarg, "%s" , &nome_do_continente); 
                }else
                {
                    fprintf(stderr,"Erro: parâmetro desconhecido na opção -L.\n\n");
                    guia();
                    break;
                }
                break;
            case 'S': /* Opções de Ordenação */
                if( strcmp(optarg, "alfa") == 0 || strcmp(optarg, "pop") == 0 )
                {
                    strcpy(ordenacao,optarg);
                }else if( strcmp(optarg, "inf") == 0 || strcmp(optarg, "dea") == 0)
                {
                    strcpy(ordenacao, optarg);
                    strcpy(dataS1, argv[optind]);
                    optind++;
                }else
                {
                    fprintf(stderr,"Erro: parâmetro desconhecido na opção -S.\n\n");
                    guia();
                    break;
                }
                break;
            case 'D': /* Opções de Seleção */
                if ( strcmp(optarg, "inf") == 0 || strcmp(optarg, "dea") == 0 || strcmp(optarg, "racioinf") == 0 || strcmp(optarg, "raciodea") == 0)
                {
                    sscanf(optarg, "%s", &selecao); /* se houver erro, fica o valor por omissão */
                }else
                {
                    fprintf(stderr,"Erro: parâmetro desconhecido na opção -D.\n\n");
                    guia();
                    break;
                }
            case 'P': /* Opções de Restrição */
                if( strcmp(optarg, "min") == 0 || strcmp(optarg, "max") == 0 )
                {
                    strcpy(restricao,optarg);
                    strcpy(num_habitantes, argv[optind]);
                }else if( strcmp(optarg, "date") == 0 )
                {
                    strcpy(restricao, optarg);
                    strcpy(dataP1, argv[optind]);
                    optind++;
                }else if( strcmp(optarg, "dates") == 0 )
                {
                    strcpy(restricao, optarg);
                    strcpy(dataP1, argv[optind]);
                    optind++;
                    strcpy(dataP2, argv[optind]);
                    optind++;
                }else
                {
                    fprintf(stderr,"Erro: parâmetro desconhecido na opção -P.\n\n");
                    guia();
                    break;
                }
                break;
            case 'i': /* Opções de Leitura */
                sscanf(optarg, "%s", &input_filename); 
                break;
            case 'o': /* Opções de Escrita */
                sscanf(optarg, "%s", &output_filename); 
                break;
            default: /* Opções Inválidas */
                fprintf(stderr,"Erro: opção '%c' desconhecida.\n\n", optopt);
                guia();
                break;
        }
    }

    /* no caso de o utilizador não selecionar nenhum ficheiro de leitura ou escrita o programa é abortado e é mostrado um guia de utilização */
    if ( strcmp(input_filename, "") == 0 || strcmp(output_filename, "") == 0)
    {
        fprintf(stderr,"Erro: o campo de leitura e escrita são de opção obrigatória.\n\n");
        guia();
    }

    /* no caso de o utilizador selecionar uma data inexistente o programa é abortado e é mostrado um guia de utilização */
    if ( ( strcmp("2021-52", dataS1) == -1 || strcmp("2020-00", dataS1) == 1 || (strcmp("2020-53", dataS1) == -1 && strcmp("2021-00", dataS1) == 1) ) && strcmp(dataS1, "") != 0 )
    {
        guia();
    }
    if ( ( strcmp("2021-52", dataP1) == -1 || strcmp("2020-00", dataP1) == 1 || (strcmp("2020-53", dataP1) == -1 && strcmp("2021-00", dataP1) == 1) ) && strcmp(dataP1, "") != 0 )
    {
        guia();
    }
    if ( (strcmp("2021-52", dataP2) == -1 || strcmp("2020-00", dataP2) == 1 || (strcmp("2020-53", dataP2) == -1 && strcmp("2021-00", dataP2) == 1) ) && strcmp(dataP2, "") != 0 )
    {
        guia();
    }

    /* troca o valor das datas para a dataP1 passar a ser a menor das 2 */
    if ( strcmp(dataP2, dataP1) == -1)
    {
        char tempP[30] = {0};

        strcpy(tempP, dataP2);
        strcpy(dataP2, dataP1);
        strcpy(dataP1, tempP);
    }

    /* verifica se o ficheiro de leitura é um ficheiro csv ou dat */
    int len_in = strlen(input_filename);
    const char *last_four_in = &input_filename[len_in-3];

    if  ( strcmp(last_four_in, "csv") == 0 )
    {
        fp_in = fopen(input_filename, "r");
    }else
    {
        fp_in = fopen(input_filename, "rb");
    }

    /* verifica se o ficheiro de escrita é um ficheiro csv ou dat */
    int len_out = strlen(output_filename);
    const char *last_four_out = &output_filename[len_out-3];

    if  ( strcmp(last_four_out, "csv") == 0 )
    {
        fp_out = fopen(output_filename, "w");
    }else
    {
        fp_out = fopen(output_filename, "wb");
    }

    /* valida a abertura dos ficheiros */
    if (fp_in == NULL)  {
        printf("ERROR 1: Can't open input file %s!\n", input_filename);
        exit(EXIT_FAILURE);
    }
    if (fp_out == NULL)  {
        printf("ERROR 1: Can't open output file %s!\n", output_filename);
        fclose(fp_in);
        exit(EXIT_FAILURE);
    }

    /* se o ficheiro de leitura escolhido for do tipo csv lê o ficheiro como um ficheiro de texto */
    if  ( strcmp(last_four_in, "csv") == 0 )
    {
    ListHead = cria_ficheiro_de_dados(fp_in, fp_out, ListHead, nome_do_continente, selecao, restricao, num_habitantes, dataP1, dataP2);
    }

    /* se o ficheiro de leitura escolhido for do tipo dat lê o ficheiro como um ficheiro binário */
    if  ( strcmp(last_four_in, "dat") == 0 )
    {
    ListHead = cria_ficheiro_de_dados_dat(ListHead, fp_in, fp_out);
    }

    /* organiza a lista de acordo com as opções do utilizador */
    ListHead = ordena_lista_alf(ListHead, ordenacao);
    ListHead = ordena_lista_pop(ListHead, ordenacao);
    ListHead = ordena_indicator_decrescente(ListHead, selecao);
    ListHead = ordena_racio_decrescente(ListHead, selecao);
    ListHead = ordena_indicador_paises(fp_in, fp_out, ListHead, ordenacao, dataS1, restricao, dataP1, dataP2);

    /* imprime lista para o terminal */
    print_lista_terminal(ListHead, selecao);

    /* se o ficheiro de escrita escolhido for do tipo csv escreve o ficheiro em formato de texto */
    if  ( strcmp(last_four_out, "csv") == 0 )
    {
    printf_lista_Stdout_csv(ListHead, selecao, fp_out, output_filename);
    }

    /* se o ficheiro de escrita escolhido for do tipo dat escreve o ficheiro em formato binário */
    if  ( strcmp(last_four_out, "dat") == 0 )
    {
    printf_lista_Stdout_bin(ListHead, selecao, fp_out, output_filename);
    }

    /* liberta a lista e fecha os ficheiros de leitura e escrita */
    free_lista(ListHead);
    fclose(fp_in);
    fclose(fp_out);

    return EXIT_SUCCESS;
}
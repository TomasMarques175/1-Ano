/* Trabalho realizado por:
   Tomás Marques nº100104 MEEC */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <getopt.h>

typedef struct _Dados{
    /* dados que variam para um dado país */
    char indicator[40];
    int weekly_count;
    char data[40];
    int cumulative_count;
    double rate_14_day;
    struct _Dados *nextD;
} Dados;

typedef struct _Pais{
    /* dados fixos para um dado país */
    char country[40];
    char country_code[40];
    char continent[40];
    int population;
    Dados *nextD;
    struct _Pais *nextP;
} Pais;


Pais *cria_ficheiro_de_dados(FILE*, Pais*, char*, char*, char*, int, char*, char*);
Pais *cria_ficheiro_de_dados_dat(Pais*, FILE*);
Pais *Lee_ficheiro_dat(Pais*, FILE*);
void print_lista_terminal(Pais*, char*);
void printf_lista_Stdout_csv(Pais*, char*, FILE*, char*);
void printf_lista_Stdout_bin(Pais*, char*, FILE*, char*);
void free_lista(Pais*);
Pais *procurapais(Pais*, char*, int*);
Pais *ordena_lista_alf(Pais*, char*);
Pais *trocaP(Pais*,Pais*);
Dados *trocaD(Dados*,Dados*);
Pais *ordena_indicator_decrescente(Pais*, char*);
Pais *ordena_racio_decrescente(Pais*, char*);
Pais *ordena_lista_pop(Pais*, char*);
Pais *ordena_indicador_paises(Pais*, char*, char*, char*, char*, char*);
void swap(Dados*, Dados*);


void guia()
{
    printf("\
           erro\
           ");
           exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    FILE *fp_in;
    FILE *fp_out;
    Pais *ListHead = NULL;

    char nome_do_continente[30] = "all"; /* dado que faz a seleção dos países no campo -L(Leitura) */
    char ordenacao[30] = {0}; /* 1º dado do campo -S(Ordenação) */
    char selecao[30] = {0}; /* dado do campo -D(Seleção) */
    char dataS1[30] = {0}; /* data utilizada no campo -S(Ordenação) */
    char restricao[30] = {0}; /* dado do campo -P(Restrição) */
    int num_habitantes = 0;  /* numero maximo ou minimo de habitatents no campo -P(Restrição) */
    char dataP1[30] = {0}; /* 1ª data utilizada no campo -P(Restrição) */
    char dataP2[30] = {0}; /* 2ª data utilizada no campo -P(Restrição) */

    char input_filename[30] = {0}; /* nome do ficheiro a ler */
    char output_filename[30] = {0}; /* nome do ficheiro a escrever */

    printf("inicio\n");

    int option;

    while ((option = getopt(argc, argv, "L:S:D:P:i:o:")) != -1)
    {
        switch(option)
        {
            case 'L': /* Expecificação do Continente que pertende fazer a leitura sendo possível fazer a leitura de todos os continents */
                sscanf(optarg, "%s" , &nome_do_continente); /* se houver erro, fica o valor por omissão (all)*/
                break;
            case 'S': /*  */
                if( strcmp(optarg, "alf") == 0 || strcmp(optarg, "pop") == 0 )
                {
                    strcpy(ordenacao,optarg);
                }else if( strcmp(optarg, "inf") == 0 || strcmp(optarg, "dea") == 0)
                {
                    strcpy(ordenacao, optarg);
                    strcpy(dataS1, argv[optind]);
                    optind++;
                }else
                {
                    break;
                }
                break;
            case 'D': /*  */
                sscanf(optarg, "%s", &selecao); /* se houver erro, fica o valor por omissão */
            case 'P': /*  */
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
                    guia();
                    break;
                }
                break;
            case 'i': /*  */
                strcpy(input_filename, optarg);
                break;
            case 'o': /*  */
                strcpy(output_filename, optarg);
                break;
            case ':': /*  */
                if (optopt == 'i'|| optopt == 'o') /*  */
                {
                    fprintf(stderr,"tanto a opção -i como a opção -o precisam de 1 argumento\n");
                    guia(); /*  */
                }
                return 1;
            case '?': /*  */
                if (isprint (optopt)) /*  */
                {
                    fprintf (stderr, "opção/opções inválidas\n");
                    guia(); /*  */
                }
                return 1;
        }
    }

    printf("nome_do_continente =%s\n", nome_do_continente);
    printf("ordenacao =%s\n", ordenacao);
    printf("selecão =%s\n", selecao);
    printf("dataS1 =%s\n", dataS1);
    printf("dataP1 =%s\n", dataP1);
    printf("dataP2 =%s\n", dataP2);
    printf("restricao =%s\n", restricao);
    printf("num_habitantes =%d\n", num_habitantes);
    printf("input_filename =%s\n", input_filename);
    printf("output_filename =%s\n", output_filename);

    if ( strcmp(input_filename, "") == 0 || strcmp(output_filename, "") == 0)
    {
        guia();
    }

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


    if ( strcmp(dataP2, dataP1) == -1)
    {
        char tempP[30] = {0};

        strcpy(tempP, dataP2);
        strcpy(dataP2, dataP1);
        strcpy(dataP1, tempP);
    }

    int len_in = strlen(input_filename);
    const char *last_four_in = &input_filename[len_in-3];

    if  ( strcmp(last_four_in, "csv") == 0 )
    {
        fp_in = fopen(input_filename, "r");
        printf("entrou\n");
    }else
    {
        fp_in = fopen(input_filename, "rb");
    }

    int len_out = strlen(output_filename);
    const char *last_four_out = &output_filename[len_out-3];

    if  ( strcmp(last_four_out, "csv") == 0 )
    {
        fp_out = fopen(output_filename, "w");
        printf("entrou\n");
    }else
    {
        fp_out = fopen(output_filename, "wb");
    }


    if (fp_in == NULL)  {
        printf("ERROR 1: Can't open input file %s!\n", input_filename);
        exit(EXIT_FAILURE);
    }
    if (fp_out == NULL)  {
        printf("ERROR 1: Can't open output file %s!\n", output_filename);
        exit(EXIT_FAILURE);
    }


    if  ( strcmp(last_four_in, "csv") == 0 )
    {
        printf("entrou\n");
    ListHead = cria_ficheiro_de_dados(fp_in, ListHead, nome_do_continente, selecao, restricao, num_habitantes, dataP1, dataP2);
    }


    if  ( strcmp(last_four_out, "dat") == 0 )
    {
    ListHead = cria_ficheiro_de_dados_dat(ListHead, fp_in);
    }


    ListHead = ordena_lista_alf(ListHead, ordenacao);
    ListHead = ordena_lista_pop(ListHead, ordenacao);
    ListHead = ordena_indicator_decrescente(ListHead, selecao);
    ListHead = ordena_racio_decrescente(ListHead, selecao);
    ListHead = ordena_indicador_paises(ListHead, ordenacao, dataS1, restricao, dataP1, dataP2);

    print_lista_terminal(ListHead, selecao);

    if  ( strcmp(last_four_in, "csv") == 0 )
    {
    printf_lista_Stdout_csv(ListHead, selecao, fp_out, output_filename);
    }

    if  ( strcmp(last_four_out, "d") == 0 )
    {
    printf_lista_Stdout_bin(ListHead, selecao, fp_out, output_filename);
    }

    free_lista(ListHead);
    fclose(fp_in);
    fclose(fp_out);

    printf("fim");

    return 0;
}


Pais *cria_ficheiro_de_dados(FILE *fp_in, Pais *ListHead, char *nome_do_continente, char *selecao,  char *restricao, int num_habitantes, char *dataP1, char *dataP2)
{

    Pais *novopais, *Countryptr;
    Dados *novodado;

    char line[300];   /* para guardar uma linha lida do ficheiro */
    char *dado[10];
    char newcountry[40] = {0};
    char *token;
    int populationval = 0;
    int weekly_countval = 0;
    char dataval[40] = {0};
    float rate_14_dayval = 0;
    int cumulative_countval = 0;

    int i = 0, j = 0;
    int t = 0;

    while(fgets(line, 300, fp_in) != NULL ) // ler uma linha do ficheiro
    {

        token = strtok(line,",");
        dado[0] = token;
        i = 1;

        while (token != NULL)
        {
            token = strtok(NULL,",");
            dado[i] = token;
            i++;
        }

        sscanf(dado[3],"%d", &populationval);

        strcpy(dataval, dado[6]);

        if ( t != 0 )
        {
            if  (
                    (strcmp(dado[2], nome_do_continente) == 0) ||
                    (strcmp(nome_do_continente, "all") == 0 )
                )
            {
                if  (
                        ( strcmp(selecao, "inf") == 0 && strcmp(dado[4], "cases") == 0 )        ||
                        ( strcmp(selecao, "dea") == 0 && strcmp(dado[4], "deaths") == 0 )       ||
                        ( strcmp(selecao, "racioinf") == 0 && strcmp(dado[4], "cases") == 0 )   ||
                        ( strcmp(selecao, "raciodea") == 0 && strcmp(dado[4], "deaths") == 0 )  ||
                        ( strcmp(selecao, "") == 0)
                    )
                {
                    if  (
                            ( strcmp(restricao, "min") == 0 &&  populationval > num_habitantes )                    ||
                            ( strcmp(restricao, "max") == 0 &&  populationval < num_habitantes )                    ||
                            ( strcmp(restricao, "date") == 0 && strcmp(dataP1, dataval) == 0 )                      ||
                            ( strcmp(restricao, "dates") == 0 &&
                                (
                                    ( strcmp(dataP1, dataval) == -1 && strcmp(dataP2, dataval) == 1 )               ||
                                    ( strcmp(dataP1, dataval) == 0 || strcmp(dataP2, dataval) == 0 )
                                )
                            )                                                                                       ||
                            ( strcmp(restricao, "") == 0 && strcmp(dataP1, "") == 0 && strcmp(dataP2, "") == 0 )
                        )
                    {
                        j = 0;

                        strcpy(newcountry, dado[0]);

                        Countryptr = procurapais(ListHead, newcountry, &j); /* Função responsável por procurar se já há dados sobre este país */
                        /* retorna o valor de Auxptr(pointeiro que indica o local do país na lista principal)*/

                        if ( j == 0 )
                        {
                            if ((novopais = (Pais*) calloc(1,sizeof(Pais))) == NULL)
                            {
                                printf("Erro: Não foi possível alocar o bloco de memória\n");
                                exit(EXIT_FAILURE);
                            }

                            strcpy(novopais->country, dado[0]);

                            strcpy(novopais->country_code, dado[1]);

                            strcpy(novopais->continent, dado[2]);

                            novopais->population = populationval;
                        }

                        if ( j == 0 || j == 1 )
                        {
                            if ((novodado = (Dados*) calloc(1,sizeof(Dados))) == NULL)
                            {
                                printf("Erro: Não foi possível alocar o bloco de memória\n");
                                exit(EXIT_FAILURE);
                            }

                            strcpy(novodado->indicator, dado[4]);

                            sscanf(dado[5],"%d", &weekly_countval);
                            novodado->weekly_count = weekly_countval;

                            strcpy(novodado->data, dataval);

                            sscanf(dado[7],"%g", &rate_14_dayval);
                            novodado->rate_14_day = rate_14_dayval;

                            sscanf(dado[8],"%d", &cumulative_countval);
                            novodado->cumulative_count = cumulative_countval;

                            if(i == 9)
                            {
                                novodado->cumulative_count = novodado->rate_14_day;
                                novodado->rate_14_day = 0;
                            }

                            novodado->nextD = NULL;
                        }

                        if ( j == 0 )
                        {

                            novopais->nextD = novodado;

                            novopais->nextP = NULL;

                            Pais *AuxT;

                            if(ListHead == NULL)
                            {
                                ListHead = novopais;
                            }
                            else
                            {
                                AuxT = ListHead;
                                while(AuxT->nextP != NULL)
                                {
                                    AuxT = AuxT->nextP;
                                }
                                AuxT->nextP = novopais;
                            }
                        }

                        if ( j == 1 )
                        {
                            Dados *auxptrD;

                            auxptrD = Countryptr->nextD;

                            while (auxptrD->nextD != NULL) /* percorre os dados todos do país até ao último dado */
                            {
                                auxptrD = auxptrD->nextD;
                            }

                            auxptrD->nextD = novodado;
                        }

                    }
                }
            }
        }else
        {
            t++;
        }
    }

    return ListHead;
}


/* ver se estou a fazer bem ?? */
Pais *cria_ficheiro_de_dados_dat(Pais *ListHead, FILE *fp_in)
{
    fseek(fp_in, 0, SEEK_END);
    long fileSize = ftell(fp_in);
    rewind(fp_in);

    int num_linhas = (int)(fileSize / ( sizeof(Dados)+sizeof(Pais) ) );

    int loop = 0;

    for ( loop = 0; loop < num_linhas; loop++)
    {
        fseek(fp_in, ( sizeof(Dados)+sizeof(Pais) )*loop, SEEK_SET);
        ListHead = Lee_ficheiro_dat(ListHead, fp_in);
    }
    return ListHead;
}

/* ver se estou a fazer bem ?? */
Pais *Lee_ficheiro_dat(Pais *ListHead, FILE *fp_in)
{
    if (ListHead == NULL)
    {
        Dados *novodado;

        if ((ListHead = (Pais*) calloc(1,sizeof(Pais))) == NULL)
        {
            printf("Erro: Não foi possível alocar o bloco de memória\n");
            exit(EXIT_FAILURE);
        }
        fread(ListHead, sizeof(Pais), 1, fp_in);
        ListHead->nextP = NULL;

        if ((novodado = (Dados*) calloc(1,sizeof(Dados))) == NULL)
        {
            printf("Erro: Não foi possível alocar o bloco de memória\n");
            exit(EXIT_FAILURE);
        }
        fread(novodado, sizeof(Dados), 1, fp_in);
        ListHead->nextD = novodado;
        novodado->nextD = NULL;
    }else
    {
        Pais *novopais, *AuxP;
        Dados *novodado;

        AuxP = ListHead;
        if ((novopais = (Pais*) calloc(1,sizeof(Pais))) == NULL)
        {
            printf("Erro: Não foi possível alocar o bloco de memória\n");
            exit(EXIT_FAILURE);
        }

        if ((novodado = (Dados*) calloc(1,sizeof(Dados))) == NULL)
        {
            printf("Erro: Não foi possível alocar o bloco de memória\n");
            exit(EXIT_FAILURE);
        }

        while (AuxP->nextP != NULL)
        {
            AuxP = AuxP->nextP;
        }

        if ( strcmp(AuxP->country, novopais->country) != 0 )
        {
            fread(novopais, sizeof(Pais), 1, fp_in);
            AuxP->nextP = novopais;
            novopais->nextP = NULL;
            while (AuxP->nextP != NULL)
            {
                AuxP = AuxP->nextP;
            }
            fread(novodado, sizeof(Dados), 1, fp_in);
            AuxP->nextD = novodado;
        }else
        {
            fread(novopais, sizeof(Pais), 1, fp_in);
            free(novopais);
            fread(novodado, sizeof(Dados), 1, fp_in);
            AuxP->nextD = novodado;
        }
    }
    return ListHead;
}

/* Não mexer */
void print_lista_terminal(Pais *ListHead, char *selecao)
{
    if ( ListHead != NULL)
    {
        Pais *AuxP;
        Dados *AuxD;

        printf("country,country_code,continent,population,indicator,weekly_count,year_week,rate_14_day,cumulative_count\n");
        for( AuxP = ListHead; AuxP != NULL; AuxP = AuxP->nextP )
        {
            if  (
                    ( strcmp(selecao, "inf") == 0 )         ||
                    ( strcmp(selecao, "dea") == 0 )         ||
                    ( strcmp(selecao, "racioinf") == 0 )    ||
                    ( strcmp(selecao, "raciodea") == 0 )
                )
            {
            AuxD = AuxP->nextD;
            printf("%s,%s,%s,%d,",AuxP->country, AuxP->country_code, AuxP->continent, AuxP->population);
            printf("%s,%d,%s,%g,%d\n",AuxD->indicator, AuxD->weekly_count, AuxD->data, AuxD->rate_14_day, AuxD->cumulative_count);
            }else
            {
                for( AuxD = AuxP->nextD; AuxD != NULL; AuxD = AuxD->nextD)
                {
                    printf("%s,%s,%s,%d,",AuxP->country, AuxP->country_code, AuxP->continent, AuxP->population);
                    printf("%s,%d,%s,%g,%d\n",AuxD->indicator, AuxD->weekly_count, AuxD->data, AuxD->rate_14_day, AuxD->cumulative_count);
                }
            }

        }
    }
}

/* Deixou de dar */
void printf_lista_Stdout_csv(Pais *ListHead, char *selecao, FILE *fp_out, char*output_filename)
{
    if ( ListHead != NULL)
    {
        Pais *AuxP;
        Dados *AuxD;

        fprintf(fp_out, "country,country_code,continent,population,indicator,weekly_count,year_week,rate_14_day,cumulative_count\n");
        for( AuxP = ListHead; AuxP != NULL; AuxP = AuxP->nextP )
        {
            if  (
                    ( strcmp(selecao, "inf") == 0 )         ||
                    ( strcmp(selecao, "dea") == 0 )         ||
                    ( strcmp(selecao, "racioinf") == 0 )    ||
                    ( strcmp(selecao, "raciodea") == 0 )
                )
            {
            AuxD = AuxP->nextD;
            fprintf(fp_out, "%s,%s,%s,%d,",AuxP->country, AuxP->country_code, AuxP->continent, AuxP->population);
            fprintf(fp_out, "%s,%d,%s,%g,%d\n",AuxD->indicator, AuxD->weekly_count, AuxD->data, AuxD->rate_14_day, AuxD->cumulative_count);
            }else
            {
                for( AuxD = AuxP->nextD; AuxD != NULL; AuxD = AuxD->nextD)
                {
                    fprintf(fp_out, "%s,%s,%s,%d,",AuxP->country, AuxP->country_code, AuxP->continent, AuxP->population);
                    fprintf(fp_out, "%s,%d,%s,%g,%d\n",AuxD->indicator, AuxD->weekly_count, AuxD->data, AuxD->rate_14_day, AuxD->cumulative_count);
                }
            }

        }
    }
}

/* ver se estou a fazer bem ?? */
void printf_lista_Stdout_bin(Pais *ListHead, char *selecao, FILE *fp_out, char *output_filename)
{
    if ( ListHead != NULL)
    {
        Pais *AuxP , *AuxP2, *HoldNextP;

        AuxP = ListHead;
        while (AuxP != NULL)
        {
            AuxP2 = AuxP;
            HoldNextP = AuxP->nextP;
            AuxP->nextP = NULL;

            Dados *AuxD, *HoldNextD;

            AuxD = AuxP2->nextD;
            while (AuxD != NULL)
            {
                HoldNextD = AuxD->nextD;
                AuxD->nextD = NULL;

                fseek(fp_out, 0, SEEK_END);
                fwrite( AuxP, sizeof(Pais), 1, fp_out);
                fseek(fp_out, 0, SEEK_END);
                fwrite( AuxD, sizeof(Dados), 1, fp_out);

                AuxD->nextD = HoldNextD;

                HoldNextD = NULL;

                AuxD = AuxD->nextD;
            }
            AuxP->nextP = HoldNextP;

            HoldNextP = NULL;

            AuxP = AuxP->nextP;
        }
    }
}

/* Não mexer */
void free_lista(Pais *ListHead)
{
    Pais *AuxfreeP;

    while( ListHead != NULL )
    {
        AuxfreeP = ListHead;
        ListHead = ListHead->nextP;

        Dados *AuxfreeD1, *AuxfreeD2;

        AuxfreeD1 = AuxfreeP->nextD;

        while ( AuxfreeD1 != NULL )
        {
            AuxfreeD2 = AuxfreeD1;
            AuxfreeD1 = AuxfreeD1->nextD;
            free(AuxfreeD2);
        }
        free(AuxfreeP);
    }
}

/* Não mexer */
Pais *procurapais(Pais *ListHead, char *newcountry, int *j)
{
    Pais *Auxptr;

    Auxptr = ListHead;
    if (Auxptr != NULL){
        while( Auxptr != NULL ) /* Auxptr != NULL ou Auxptr->next != NULL */
        {
            if (strcmp(Auxptr->country, newcountry) == 0){
                (*j)++;
                return Auxptr;
            }else{
                Auxptr = Auxptr->nextP;
            }
        }
    }else{
        return Auxptr;
    }
    return Auxptr;
}

/* Não mexer */
Pais *ordena_lista_alf(Pais *ListHead, char *ordenacao)
{
    if (strcmp(ordenacao, "alfa") == 0)
    {
        int trocas = 1;
        Pais *leftP, *rightP, *headP, aux_structP;

        headP = &aux_structP;
        headP->nextP = ListHead;
        if ((ListHead != NULL ) && ((ListHead->nextP != NULL )))
        {
            while(trocas)
            {
                trocas = 0;
                leftP = headP;
                rightP = headP->nextP;
                while(rightP->nextP != NULL)
                {
                    if (strcmp(rightP->country, rightP->nextP->country) > 0)
                    {
                        leftP->nextP = trocaP(rightP,rightP->nextP);
                        trocas = 1;
                    }
                    leftP = rightP;
                    if (rightP->nextP != NULL)
                        rightP = rightP->nextP;
                }
            }
        }
        ListHead = headP->nextP;
    }
    return ListHead;
}

/* Não mexer */
Pais *trocaP(Pais *leftP,Pais *rightP)
{
    leftP->nextP = rightP->nextP;
    rightP->nextP = leftP;
    return rightP;
}

/* Não mexer */
Pais *ordena_indicator_decrescente(Pais *ListHead, char *selecao)
{
    if  ( ( strcmp(selecao, "inf") == 0 ) || ( strcmp(selecao, "dea") == 0 ) )
    {
        Pais *auxptrind;

        for( auxptrind = ListHead; auxptrind != NULL; auxptrind = auxptrind->nextP )
        {
            Dados *SubListHeadD;

            SubListHeadD = auxptrind->nextD;

            int swapped;
            Dados *ptr1;
            Dados *lptr = NULL;

            do
            {
                swapped = 0;
                ptr1 = SubListHeadD;

                while (ptr1->nextD != lptr)
                {
                    if (ptr1->weekly_count < ptr1->nextD->weekly_count)
                    {
                        swap(ptr1, ptr1->nextD);
                        swapped = 1;
                    }else if (ptr1->weekly_count == ptr1->nextD->weekly_count)
                    {
                        if (ptr1->data < ptr1->nextD->data)
                        {
                            swap(ptr1, ptr1->nextD);
                            swapped = 1;
                        }
                    }
                    ptr1 = ptr1->nextD;
                }
                lptr = ptr1;
            }
            while (swapped);
        }
    }
    return ListHead;
}

/* Não mexer */
void swap(Dados *a, Dados *b)
{
    char temp_indicator[40] = {0};
    int temp_weekly_count = 0;
    char temp_data[40] = {0};
    int temp_cumulative_count = 0;
    float temp_rate_14_day = 0;

    strcpy(temp_indicator, a->indicator);
    strcpy(a->indicator, b->indicator);
    strcpy(b->indicator, temp_indicator);

    temp_weekly_count = a->weekly_count;
    a->weekly_count = b->weekly_count;
    b->weekly_count = temp_weekly_count;

    strcpy(temp_data, a->data);
    strcpy(a->data, b->data);
    strcpy(b->data, temp_data);

    temp_cumulative_count = a->cumulative_count;
    a->cumulative_count = b->cumulative_count;
    b->cumulative_count = temp_cumulative_count;

    temp_rate_14_day = a->rate_14_day;
    a->rate_14_day = b->rate_14_day;
    b->rate_14_day = temp_rate_14_day;

}

/* Não mexer */
Pais *ordena_racio_decrescente(Pais *ListHead, char *selecao)
{

    if  (
            ( strcmp(selecao, "racioinf") == 0 )                                    ||
            ( strcmp(selecao, "raciodea") == 0 )
        )
    {
        Pais *auxptrind;

        for( auxptrind = ListHead; auxptrind != NULL; auxptrind = auxptrind->nextP )
        {
            Dados *SubListHeadD;

            SubListHeadD = auxptrind->nextD;

            int swapped;
            Dados *ptr1;
            Dados *lptr = NULL;

            do
            {
                swapped = 0;
                ptr1 = SubListHeadD;

                while (ptr1->nextD != lptr)
                {
                    if ( ptr1->rate_14_day < ptr1->nextD->rate_14_day ) // ver se é rate_14_day ou indicator // double vs float
                    {
                        swap(ptr1, ptr1->nextD);
                        swapped = 1;
                    }
                    ptr1 = ptr1->nextD;
                }
                lptr = ptr1;
            }
            while (swapped);
        }
    }
    return ListHead;
}

/* Não mexer */
Dados *trocaD(Dados *leftD,Dados *rightD)
{
    leftD->nextD = rightD->nextD;
    rightD->nextD = leftD;
    return rightD;
}


Pais *ordena_indicador_paises(Pais *ListHead, char *ordenacao, char *dataS1, char *restricao, char *dataP1, char *dataP2)
{
    printf("banana1");
    if ( strcmp(ordenacao, "inf") == 0 || strcmp(ordenacao, "dea") == 0 )
    {
        if  (
                ( strcmp(restricao, "date") == 0 && strcmp(dataS1, dataP1) == 0 )                                  ||
                ( strcmp(restricao, "dates") == 0 && strcmp(dataS1, dataP1) == 1 && strcmp(dataS1, dataP2) == -1 ) ||
                ( strcmp(restricao, "") == 0 )
            )
        {
            printf("banana2");
            int trocas = 1;
            Pais *leftP, *rightP, *headP, aux_structP;

            headP = &aux_structP;
            headP->nextP = ListHead;
            if ((ListHead != NULL ) && ((ListHead->nextP != NULL )))
            {
                while(trocas)
                {
                    trocas = 0;
                    leftP = headP;
                    rightP = headP->nextP;
                    while( rightP->nextP != NULL )
                    {

                        Dados *rightD, *rightDnext;

                        printf("fora\n");


                        rightD = rightP->nextD;

                        while ( rightD != NULL )
                        {
                            if ( strcmp(rightD->data, dataS1) == 0)
                            {
                                break;
                            }else
                            {
                                rightD = rightD->nextD;
                            }
                        }

                        rightDnext = rightP->nextP->nextD;

                        while ( rightDnext != NULL)
                        {
                            if ( strcmp(rightDnext->data, dataS1) == 0)
                            {
                                break;
                            }else
                            {
                                rightDnext = rightDnext->nextD;
                            }
                        }



                        if (rightD == NULL)
                        {
                            Dados *novodado;

                            if ((novodado = (Dados*) calloc(1,sizeof(Dados))) == NULL)
                            {
                                printf("Erro: Não foi possível alocar o bloco de memória\n");
                                exit(EXIT_FAILURE);
                            }

                            if ( strcmp(ordenacao, "inf") == 0 )
                            {
                            strcpy(novodado->indicator, "cases");
                            }else
                            {
                                strcpy(novodado->indicator, "deaths");
                            }

                            novodado->weekly_count = 0;

                            strcpy(novodado->data, dataS1);

                            novodado->rate_14_day = 0;

                            novodado->cumulative_count = 0;

                            Dados *auxptrD;

                            auxptrD = rightP->nextD;

                            while (auxptrD->nextD != NULL) /* percorre os dados todos do país até ao último dado */
                            {
                                auxptrD = auxptrD->nextD;
                            }

                            auxptrD->nextD = novodado;

                        }


                        if (rightDnext == NULL)
                        {
                            Dados *novodado;

                            if ((novodado = (Dados*) calloc(1,sizeof(Dados))) == NULL)
                            {
                                printf("Erro: Não foi possível alocar o bloco de memória\n");
                                exit(EXIT_FAILURE);
                            }

                            if ( strcmp(ordenacao, "inf") == 0 )
                            {
                            strcpy(novodado->indicator, "cases");
                            }else
                            {
                                strcpy(novodado->indicator, "deaths");
                            }

                            novodado->weekly_count = 0;

                            strcpy(novodado->data, dataS1);

                            novodado->rate_14_day = 0;

                            novodado->cumulative_count = 0;

                            Dados *auxptrD;

                            auxptrD = rightP->nextP->nextD;

                            while (auxptrD->nextD != NULL) /* percorre os dados todos do país até ao último dado */
                            {
                                auxptrD = auxptrD->nextD;
                            }

                            auxptrD->nextD = novodado;

                        }


                        if ( ( rightD != NULL ) && ( rightDnext != NULL ) )
                        {
                            if ( rightD->weekly_count < rightDnext->weekly_count )
                            {
                                leftP->nextP = trocaP(rightP,rightP->nextP);
                                trocas = 1;
                                leftP = rightP;
                            }else if( ( rightD->weekly_count == rightDnext->weekly_count ) && ( strcmp(rightP->country, rightP->nextP->country) > 0 ) )
                            {
                                if(strcmp(rightP->country, rightP->nextP->country) > 0)
                                {
                                    leftP->nextP = trocaP(rightP,rightP->nextP);
                                    trocas = 1;
                                }
                                leftP = rightP;
                            }else
                            {
                                leftP = rightP;
                            }
                        }
                        if (rightP->nextP != NULL)
                        {
                            rightP = rightP->nextP;
                        }
                    }
                }
                ListHead = headP->nextP;
            }
        }
    }
    return ListHead;
}


/* Não mexer */
Pais *ordena_lista_pop(Pais *ListHead, char *ordenacao)
{
    if ( strcmp(ordenacao, "pop") == 0 )
    {
        int trocas = 1;
        Pais *leftP, *rightP, *headP, aux_structP;

        headP = &aux_structP;
        headP->nextP = ListHead;
        if ((ListHead != NULL ) && ((ListHead->nextP != NULL )))
        {
            while(trocas)
            {
                trocas = 0;
                leftP = headP;
                rightP = headP->nextP;
                while(rightP->nextP != NULL)
                {
                    if ((rightP->population) < (rightP->nextP->population))
                    {
                        leftP->nextP = trocaP(rightP,rightP->nextP);
                        trocas = 1;
                        leftP = rightP;
                        if (rightP->nextP != NULL)
                        {
                            rightP = rightP->nextP;
                        }
                    }else if((rightP->population == rightP->nextP->population) && (strcmp(rightP->country, rightP->nextP->country) > 0))
                    {
                        leftP->nextP = trocaP(rightP,rightP->nextP);
                        trocas = 1;
                        leftP = rightP;
                        if (rightP->nextP != NULL)
                        {
                            rightP = rightP->nextP;
                        }
                    }else
                    {
                        leftP = rightP;
                        if (rightP->nextP != NULL)
                        {
                            rightP = rightP->nextP;
                        }
                    }
                }
            }
        }
        ListHead = headP->nextP;
    }
    return ListHead;
}

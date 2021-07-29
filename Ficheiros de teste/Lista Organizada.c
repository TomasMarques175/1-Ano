#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

typedef struct _Dados{
    /* dados que variam para um dado país */
    char indicator[40];
    int weekly_count;
    int year;
    int week;
    int cumulative_count;
    float rate_14_day;
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

Pais *cria_ficheiro_de_dados(FILE*, Pais*, char*);
Pais *remove_firstline(Pais*);
void print_lista_terminal(Pais*);
void free_lista(Pais*);
Pais *procurapais(Pais*, char*, int*);

int main()
{
    FILE *fp;
    Pais *ListHead = NULL;

    char nome_do_continente[40] = "all";

    printf("inicio");


    fp = fopen("covid19_w_t01.csv", "r");

    if (fp == NULL)  {
        printf("ERROR 1: Can't open input file %s!\n", "covid19_w_t01.csv");
        exit(EXIT_FAILURE);
    }

    printf("inicio");
    ListHead = cria_ficheiro_de_dados(fp, ListHead, nome_do_continente);
    printf("\t\t teste 1\n");

    ListHead = remove_firstline(ListHead);
    printf("\t\t teste 2\n");

    print_lista_terminal(ListHead);
    printf("\t\t teste 3\n");

    free_lista(ListHead);
    printf("\t\t teste 4\n");

    fclose(fp);
    printf("\t \t teste 5\n");

    printf("fim");

    return 0;
}

Pais *cria_ficheiro_de_dados(FILE *fp, Pais *ListHead, char *nome_do_continente)
{

    Pais *novopais, *Countryptr;
    Dados *novodado;

    char line[300];   /* para guardar uma linha lida do ficheiro */
    char *dado[10];
    char newcountry[40] = {0};
    char all[4] = "all";
    char *token;
    int populationval = 0;
    int weekly_countval = 0;
    int yearval = 0;
    int weekval = 0;
    float rate_14_dayval = 0;
    int cumulative_countval = 0;

    int i, j;

    while(fgets(line, 300, fp) != NULL ) // ler uma linha do ficheiro
    {

        token = strtok(line,",");
        dado[0] = token;
        i = 1;

        while (token != NULL)
        {
            token = strtok(NULL,",-");
            dado[i] = token;
            i++;
        }

        if ((strcmp(dado[0], nome_do_continente) == 0) || (strcmp(nome_do_continente, all) == 0 ))
        {

            j = 0;

            strcpy(newcountry, dado[0]);

            Countryptr = procurapais(ListHead, newcountry, &j); /* Função responsável por procurar se já há dados sobre este país */
            /* retorna o valor de Auxptr(pointeiro que indica o local do país na lista principal)*/

            if (j == 1){

                Dados *auxptrD;

                auxptrD = Countryptr->nextD;

                while (auxptrD->nextD != NULL) /* percorre os dados todos do país até ao último dado */
                {
                    auxptrD = auxptrD->nextD;
                }

                if ((novodado = (Dados*) calloc(1,sizeof(Dados))) == NULL)
                {
                    printf("Erro: Não foi possível alocar o bloco de memória2\n");
                    exit(EXIT_FAILURE);
                }

                strcpy(novodado->indicator, dado[4]);
                sscanf(dado[5],"%d", &weekly_countval);
                novodado->weekly_count = weekly_countval;
                sscanf(dado[6],"%d", &yearval);
                novodado->year = yearval;
                sscanf(dado[7],"%d", &weekval);
                novodado->week = weekval;
                sscanf(dado[8],"%g", &rate_14_dayval);
                novodado->rate_14_day = rate_14_dayval;
                sscanf(dado[9],"%d", &cumulative_countval);
                novodado->cumulative_count = cumulative_countval;

                if(i == 10)
                {
                    novodado->cumulative_count = novodado->rate_14_day;
                    novodado->rate_14_day = 0;
                }

                novodado->nextD = NULL;

                /* ver apontador de dados */

                auxptrD->nextD = novodado; /* o apontador do último dado da lista aponta agora para o novo dado */

            } else{

                if ((novodado = (Dados*) calloc(1,sizeof(Dados))) == NULL)
                {
                    printf("Erro: Não foi possível alocar o bloco de memória\n");
                    exit(EXIT_FAILURE);
                }

                if ((novopais = (Pais*) calloc(1,sizeof(Pais))) == NULL)
                {
                    printf("Erro: Não foi possível alocar o bloco de memória\n");
                    exit(EXIT_FAILURE);
                }

                strcpy(novopais->country, dado[0]);
                strcpy(novopais->country_code, dado[1]);
                strcpy(novopais->continent, dado[2]);
                sscanf(dado[3],"%d", &populationval);
                novopais->population = populationval;
                strcpy(novodado->indicator, dado[4]);
                sscanf(dado[5],"%d", &weekly_countval);
                novodado->weekly_count = weekly_countval;
                sscanf(dado[6],"%d",&yearval);
                novodado->year = yearval;
                sscanf(dado[7],"%d", &weekval);
                novodado->week = weekval;
                sscanf(dado[8],"%g", &rate_14_dayval);
                novodado->rate_14_day = rate_14_dayval;
                sscanf(dado[9],"%d", &cumulative_countval);
                novodado->cumulative_count = cumulative_countval;

                if(i == 10)
                {
                    novodado->cumulative_count = novodado->rate_14_day;
                    novodado->rate_14_day = 0;
                }

                novodado->nextD = NULL;
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
        }
    }
    return ListHead;
}


/* dar nomes diferentes aos pointers auxiliares */
/* Não mexer */
void print_lista_terminal(Pais *ListHead)
{
    Pais *AuxP;
    Dados *AuxD;

    for( AuxP = ListHead; AuxP != NULL; AuxP = AuxP->nextP )
    {
        //printf("%s,%s,%s,%d,",AuxP->country, AuxP->country_code, AuxP->continent, AuxP->population);
        for( AuxD = AuxP->nextD; AuxD != NULL; AuxD = AuxD->nextD)
        {
            printf("%s,%s,%s,%d,",AuxP->country, AuxP->country_code, AuxP->continent, AuxP->population);
            printf("%s,%d,%d-%d,%g,%d\n",AuxD->indicator, AuxD->weekly_count, AuxD->year, AuxD->week, AuxD->rate_14_day, AuxD->cumulative_count);
        }
    }
}


/* Não mexer */
/* Remove linha informativa que não corresponde a nenhum país */
Pais *remove_firstline(Pais *ListHead)
{
    Pais *AuxR;

    AuxR = ListHead;
    ListHead = ListHead->nextP;

    free(AuxR->nextD);
    free(AuxR);

    return ListHead;
}


/* Não mexer */
void free_lista(Pais *ListHead)
{
    Pais *Auxfree;

    Auxfree = ListHead;
    while( ListHead != NULL)
    {
        Auxfree = ListHead;
        ListHead = ListHead->nextP;
        free(Auxfree->nextD);
        free(Auxfree);
    }
}


Pais *procurapais(Pais *ListHead, char *newcountry, int *j)
{
    Pais *Auxptr;

    Auxptr = ListHead;
    if (Auxptr != NULL){
        while( Auxptr != NULL ) /* Auxptr != NULL ou Auxptr->next != NULL */{
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

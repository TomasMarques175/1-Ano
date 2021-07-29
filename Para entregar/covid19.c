/* Trabalho realizado por:
   Tomás Marques nº100104 MEEC */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <getopt.h>

/* nossos includes */
#include "covid19.h"

/** \brief libertar a memória alocada para todos os elementos da lista principal e das listas secundárias
 *
 * \param ListHead Pais*: Cabeça da Lista principal que aponta
 * para o primeiro nodo da lista principal e ao qual é recorrido 
 * para percorrer a lista e as suas sublistas 
 * \return void
 *
 */
void free_lista(Pais *ListHead)
{
    Pais *AuxfreeP; /* apontador auxiliar do tipo Pais */

    while( ListHead != NULL )
    {
        AuxfreeP = ListHead;
        ListHead = ListHead->nextP;

        Dados *AuxfreeD1, *AuxfreeD2; /* apontadores auxiliares do tipo Dados */

        AuxfreeD1 = AuxfreeP->nextD;
        
        while ( AuxfreeD1 != NULL )
        {
            AuxfreeD2 = AuxfreeD1;
            AuxfreeD1 = AuxfreeD1->nextD;
            free(AuxfreeD2); /* libertar primeiro os elementos da lista secundária com a ajuda de um apontador auxiliar */
        }
        free(AuxfreeP); /* depois de libertar a lista secundária liberta o nodo da lista princiapal que tinha os dados */
    }
}

/** \brief imprime a lista de acordo com as opções de seleção do utilizador no terminal
 *
 * \param ListHead Pais*: Cabeça da Lista principal que aponta
 * para o primeiro nodo da lista principal e ao qual é recorrido 
 * para percorrer a lista
 * \param selecao char*: de acordo com o modo de seleção do utilizador só é impresso
 * uma linha para os paises selecionados
 * \return void
 *
 */
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


/** \brief imprime a lista de acordo com as opções de seleção do utilizador para um ficheiro do tipo .csv
 *
 * \param ListHead Pais*: Cabeça da Lista principal que aponta
 * para o primeiro nodo da lista principal e ao qual é recorrido 
 * para percorrer a lista 
 * \param selecao char*: de acordo com o modo de seleção do utilizador só é impresso
 * uma linha para os paises selecionados
 * \param fp_out FILE*: apontador do ficheiro csv onde será impressa a lista
 * \param output_filename  char*: nome do ficheiro csv onde será impressa a lista
 * \return void
 *
 */
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


/** \brief imprime a lista de acordo com as opções de seleção do utilizador para um ficheiro do tipo .dat
 *
 * \param ListHead Pais*: Cabeça da Lista principal que aponta
 * para o primeiro nodo da lista principal e ao qual é recorrido 
 * para percorrer a lista 
 * \param selecao char*: de acordo com o modo de seleção do utilizador só é impresso
 * uma linha para os paises selecionados
 * \param fp_out FILE*: apontador do ficheiro dat onde será impressa a lista
 * \param output_filename  char*: nome do ficheiro dat onde será impressa a lista
 * \return void
 *
 */
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

/** \brief troca o conteudo de 2 sub listas
 *
 * \param a Dados*: ponteiro de uma sublista do tipo Dados
 * \param a Dados*: ponteiro de uma sublista do tipo Dados
 * \return void
 *
 */
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

/** \brief lee o ficheiro de dados do tipo .csv escolhido pelo utilizador e cria uma lista com esses mesmos dados, 
 * restringido e selecionado os dados presentes no ficheiro de acordo com as opções escolhidas pelo utilidazor
 *
 * \param fp_in FILE*: apontador do ficheiro de onde se pretendem tirar os dados
 * \param ListHead Pais*: Cabeça da Lista principal que aponta
 * para o primeiro nodo da lista principal e ao qual é recorrido 
 * para percorrer a lista 
 * \param nome_do_continente char*: nome do continente a que o utilizador quer restringir os dados
 * \param selecao char*: de acordo com a opção de seleção são selecionados apenas selecionados
 * os dados correspondentes a infetados ou mortos
 * \param restricao char*: de acordo com a opção de restrição os dados são restringidos a países com mais ou menos n mil habitantes
 * (de acordo com a opção do utilizador) ou a uma certa data ou intervalo de datas 
 * \param num_habitantes int: restrição selecionada para o número de habitantes pelo utilizador
 * \param dataP1 char*: restrição selecionada para a data selecionada pelo utilizador ou a menor data do intervalo de datas
 * \param dataP2 char*: maior data no intervalo de datas
 * \return ListHead Pais*: Nova cabeça da lista
 *
 */
Pais *cria_ficheiro_de_dados(FILE *fp_in, Pais *ListHead, char *nome_do_continente, char *selecao,  char *restricao, int num_habitantes, char *dataP1, char *dataP2)
{

    Pais *novopais, *Countryptr;
    Dados *novodado;

    char line[300];   /* para guardar uma linha lida do ficheiro */
    char *dado[10];
    char newcountry[40] = {0};
    char country_codeval[40] = {0};
    char continentval[40] = {0};
    char *token;
    int populationval = 0;
    int weekly_countval = 0;
    char dataval[40] = {0};
    float rate_14_dayval = 0;
    int cumulative_countval = 0;

    int i = 0, j = 0, f = 0;
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

/** \brief lee o ficheiro de dados do tipo .dat escolhido pelo utilizador e cria uma lista com esses mesmos dados
 *
 * \param ListHead Pais*: Cabeça da Lista principal que aponta
 * para o primeiro nodo da lista principal e ao qual é recorrido 
 * para percorrer a lista 
 * \param fp_in FILE*: apontador do ficheiro de onde se pretendem tirar os dados
 * \return ListHead Pais*: Nova cabeça da lista
 *
 */
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

/** \brief função presente na função cria_ficheiro_de_dados_dat que lee os dados do ficheiro de dados do tipo .dat e mete-os em nodos na lista
 *
 * \param ListHead Pais*: Cabeça da Lista principal que aponta
 * para o primeiro nodo da lista principal e ao qual é recorrido 
 * para percorrer a lista 
 * \param fp_in FILE*: apontador do ficheiro de onde se pretendem tirar os dados
 * \return ListHead Pais*: Nova cabeça da lista
 * 
 */
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

/** \brief percorre a lista principal toda com o objetivo de saber se o pais da linha que estamos a ler já está na lista
 *
 * \param ListHead Pais*: Cabeça da Lista principal que aponta
 * para o primeiro nodo da lista principal e ao qual é recorrido 
 * para percorrer a lista 
 * \param newcountry char*: nome do continente que se pretende saber se já está presente na lista
 * \param j int*: valor j passado por referência que indica se foi encontrado ou não um nodo com o país que se procura, 
 * o valor serve depois de auxilio na função cria_ficheiro_de_dados;
 * \return Auxptr Pais*: NULL se ainda n há um nodo principal com o país que estamos a ler da linha e igual ao nodo com o país que estamos a ler 
 * se já tiver sido lida uma linha com esse país 
 *
 */
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

/** \brief organiza a lista principal de forma alfabética de acordo com o nome de cada país
 *
 * \param ListHead Pais*: Cabeça da Lista principal que aponta
 * para o primeiro nodo da lista principal e ao qual é recorrido 
 * para percorrer a lista
 * \param ordenacao char*: se foi selecionada a opção "alfa" pelo utilizador a função ordena_lista_alf ordena a lista de forma alfabética pelo nome dos país, 
 * caso contrário sai e retorna List Head com o mesmo valor
 * \return ListHead Pais*: Nova cabeça da lista
 *
 */
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

/** \brief recebe dois ponteiros da lista principal e troca as suas posições na lista principal 
 *
 * \param leftP Pais*: ponteiro de um dos nodos da lista princiapl
 * \param rightP Pais*: ponteiro de um dos nodos da lista princiapl
 * \return rightP Pais*: retorna a nova posição de rightP
 *
 */
Pais *trocaP(Pais *leftP,Pais *rightP)
{
    leftP->nextP = rightP->nextP;
    rightP->nextP = leftP;
    return rightP;
}

/** \brief recebe dois ponteiros da lista secundária e troca as suas posições na lista secundária
 * 
 * \param leftD Pais*: ponteiro de um dos nodos da lista secundária
 * \param rightD Pais*: ponteiro de um dos nodos da lista secundária
 * \return rightD Pais*: retorna a nova posição de rightD
 *
 */
Dados *trocaD(Dados *leftD,Pais *rightD)
{
    leftD->nextD = rightD->nextD;
    rightD->nextD = leftD;
    return rightD;
}

/** \brief organiza por ordem decrescente o número de casos ou mortos da listas secundárias de todos os paises
 *
 * \param ListHead Pais*: Cabeça da Lista principal que aponta
 * para o primeiro nodo da lista principal e ao qual é recorrido 
 * para percorrer a lista
 * \param selecao char*: se foi selecionada a opção "inf" ou "dea" pelo utilizador a função ordena_indicator_decrescente 
 * ordena a lista secundária por weekly_count de forma decrescente, 
 * caso contrário sai e retorna List Head com o mesmo valor
 * \return ListHead Pais*: Nova cabeça da lista
 *
 */
Pais *ordena_indicator_decrescente(Pais *ListHead, char *selecao)
{
    if  ( ( strcmp(selecao, "inf") == 0 ) || ( strcmp(selecao, "dea") == 0 ) )
    {
        Pais *auxptrind;

        for( auxptrind = ListHead; auxptrind != NULL; auxptrind = auxptrind->nextP )
        {
            Dados *SubListHeadD;

            SubListHeadD = auxptrind->nextD;

            int swapped, i;
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

/** \brief organiza por ordem decrescente o rácio de mortos ou infetados das listas secundárias de todos os paises
 *
 * \param ListHead Pais*: Cabeça da Lista principal que aponta
 * para o primeiro nodo da lista principal e ao qual é recorrido 
 * para percorrer a lista
 * \param selecao char*: se foi selecionada a opção "racioinf" ou "raciodea" pelo utilizador a função ordena_racio_decrescente 
 * ordena a lista secundária por rate_14_day de forma decrescente, 
 * caso contrário sai e retorna List Head com o mesmo valor
 * \return ListHead Pais*: Nova cabeça da lista
 *
 */
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

            int swapped, i;
            Dados *ptr1;
            Dados *lptr = NULL;

            do
            {
                swapped = 0;
                ptr1 = SubListHeadD;

                while (ptr1->nextD != lptr)
                {
                    if ( ptr1->rate_14_day < ptr1->nextD->rate_14_day ) 
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

/** \brief organiza a lista principal por ordem decrescente do número da população de cada país
 *
 * \param ListHead Pais*: Cabeça da Lista principal que aponta
 * para o primeiro nodo da lista principal e ao qual é recorrido 
 * para percorrer a lista
 * \param ordenacao char*: se foi selecionada a opção "pop" pelo utilizador a função ordena_lista_pop ordena por ordem decrescente do número da população de cada país, 
 * caso contrário sai e retorna List Head com o mesmo valor
 * \return ListHead Pais*: Nova cabeça da lista
 *
 */
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

/** \brief ordena os paises por ordem decrescente do número total de mortes ou casos numa determinada data
 *
 * \param ListHead Pais*: Cabeça da Lista principal que aponta
 * para o primeiro nodo da lista principal e ao qual é recorrido 
 * para percorrer a lista
 * \param ordenacao char*: se foi selecionada a opção "inf" ou "dea" pelo utilizador a função ordena_indicador_paises ordena os paises da lista principal 
 * de forma decrescente segundo o número de casos ou mortos nessa semana servindo de desempate a semana mais recente no caso de 2 paises terem o mesmo valor, 
 * se não for selecionada nenhuma opção sai da função e retorna List Head com o mesmo valor
 * \param dataS1 char*: se a data selecionada para ordenação
 * \param restricao char*: 
 * \param dataP1 char*: utilizado para comparar a data ou intervalo de datas escolhido para a seleção dos dados
 * \param dataP2 char*: utilizado para o intervalo de datas escolhido para a seleção dos dados
 * \return ListHead Pais*: Nova cabeça da lista
 *
 */
Pais *ordena_indicador_paises(Pais *ListHead, char *ordenacao, char *dataS1, char *restricao, char *dataP1, char *dataP2)
{
    printf("ordena1");
    if ( strcmp(ordenacao, "inf") == 0 || strcmp(ordenacao, "dea") == 0 )
    {
        printf("ordena2");
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
        /* elimina dados não selecionados que foram criados para auxilio na ordenação */
        if  (
                ( strcmp(restricao, "date") == 0 && strcmp(dataS1, dataP1) != 0 )                                                                                                       ||
                ( strcmp(restricao, "dates") == 0 && ( strcmp(dataS1, dataP1) == -1 || strcmp(dataS1, dataP1) != 0 ) && ( strcmp(dataS1, dataP2) == 1 || strcmp(dataS1, dataP2) != 0 ) )
            )
        {
            Pais *AuxcleanP;

            AuxcleanP = ListHead;
            
            while (AuxcleanP != NULL)
            {
                Dados *AuxcleanD;

                AuxcleanD = AuxcleanP->nextD;
                
                while ( AuxcleanD != NULL )
                {
                    if ( strcmp(AuxcleanD->nextD->data, dataS1) == 0 )
                    {
                        free(AuxcleanD->nextD);
                        break;
                    }else
                    {
                        AuxcleanD = AuxcleanD->nextD;
                    }
                }
                AuxcleanP = AuxcleanP->nextP;
            }
        }
    }
    return ListHead;
}
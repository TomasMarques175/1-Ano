/* Trabalho realizado por:
   Tomás Marques nº100104 MEEC */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
{   /* se ListHead for igual a NULL n é impresso para o terminal nenhuma lista */
    if ( ListHead != NULL)
    {
        Pais *AuxP; 
        Dados *AuxD;

        printf("country,country_code,continent,population,indicator,weekly_count,year_week,rate_14_day,cumulative_count\n");
        for( AuxP = ListHead; AuxP != NULL; AuxP = AuxP->nextP )
        {
            if  ( /* se foi selecionada alguma das opções de seleção pelo utilizador apenas é impressa a primeira linha para cada país */                                               
                    ( strcmp(selecao, "inf") == 0 )         || 
                    ( strcmp(selecao, "dea") == 0 )         ||  
                    ( strcmp(selecao, "racioinf") == 0 )    ||
                    ( strcmp(selecao, "raciodea") == 0 )  
                )
            {
            AuxD = AuxP->nextD;
            printf("%s,%s,%s,%d,",AuxP->country, AuxP->country_code, AuxP->continent, AuxP->population);
            printf("%s,%d,%s,%g,%d\n",AuxD->indicator, AuxD->weekly_count, AuxD->data, AuxD->rate_14_day, AuxD->cumulative_count);
            }else /* se não foi selecionada nenhuma das opções de seleção pelo utilizador é impressa a lista sem qualquer alteração */
            {   
                for( AuxD = AuxP->nextD; AuxD != NULL; AuxD = AuxD->nextD) /* percorre todos os elementos da sublista com os dados variáveis */
                {
                    printf("%s,%s,%s,%d,",AuxP->country, AuxP->country_code, AuxP->continent, AuxP->population); /* é primeiro impresso os dados do nodo da lista principal */
                    printf("%s,%d,%s,%g,%d\n",AuxD->indicator, AuxD->weekly_count, AuxD->data, AuxD->rate_14_day, AuxD->cumulative_count); /* seguidamente são impressos os dados variáveis */
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
{   /* se ListHead for igual a NULL n é impresso para o ficheiro nenhuma lista */
    if ( ListHead != NULL)
    {
        Pais *AuxP;
        Dados *AuxD;

        fprintf(fp_out, "country,country_code,continent,population,indicator,weekly_count,year_week,rate_14_day,cumulative_count\n");
        for( AuxP = ListHead; AuxP != NULL; AuxP = AuxP->nextP )
        {
            if  ( /* se foi selecionada alguma das opções de seleção pelo utilizador apenas é impressa a primeira linha para cada país */
                    ( strcmp(selecao, "inf") == 0 )         ||
                    ( strcmp(selecao, "dea") == 0 )         ||
                    ( strcmp(selecao, "racioinf") == 0 )    ||
                    ( strcmp(selecao, "raciodea") == 0 )
                )
            {
            AuxD = AuxP->nextD; /* se não foi selecionada nenhuma das opções de seleção pelo utilizador é impressa a lista sem qualquer alteração */
            fprintf(fp_out, "%s,%s,%s,%d,",AuxP->country, AuxP->country_code, AuxP->continent, AuxP->population);
            fprintf(fp_out, "%s,%d,%s,%g,%d\n",AuxD->indicator, AuxD->weekly_count, AuxD->data, AuxD->rate_14_day, AuxD->cumulative_count);
            }else
            {
                for( AuxD = AuxP->nextD; AuxD != NULL; AuxD = AuxD->nextD) /* percorre todos os elementos da sublista com os dados variáveis */
                {
                    fprintf(fp_out, "%s,%s,%s,%d,",AuxP->country, AuxP->country_code, AuxP->continent, AuxP->population); /* é primeiro impresso os dados do nodo da lista principal */
                    fprintf(fp_out, "%s,%d,%s,%g,%d\n",AuxD->indicator, AuxD->weekly_count, AuxD->data, AuxD->rate_14_day, AuxD->cumulative_count); /* seguidamente são impressos os dados variáveis */
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
{   /* se ListHead for igual a NULL n é impresso para o ficheiro nenhuma lista */
    if ( ListHead != NULL)
    {
        Pais *AuxP , *AuxP2, *HoldNextP;

        AuxP = ListHead;
        while (AuxP != NULL) /* percorre a lista até ao fim */
        {
            AuxP2 = AuxP;
            HoldNextP = AuxP->nextP; /* guarda em HoldnexP o local para onde AuxP aponta para que quando utilizado o AuxP se consiga voltar a inseri-lo na lista */
            AuxP->nextP = NULL;

            Dados *AuxD, *HoldNextD;

            AuxD = AuxP2->nextD;
            while (AuxD != NULL)
            {
                HoldNextD = AuxD->nextD; /* guarda em HoldnexD o local para onde AuxD aponta para que quando utilizado o AuxD seja depois possivel voltar a inseri-lo na lista */
                AuxD->nextD = NULL;

                fseek(fp_out, 0, SEEK_END); /* aponta para o fim fo ficheiro de saída para começar a escrever no fim */
                fwrite( AuxP, sizeof(Pais), 1, fp_out); /* escreve a estrutura de dados do tipo Pais no ficheiro de saida */ 
                fseek(fp_out, 0, SEEK_END); /* aponta para o fim fo ficheiro de saída para começar a escrever no fim */
                fwrite( AuxD, sizeof(Dados), 1, fp_out); /* escreve a estrutura de dados do tipo Dados no ficheiro de saida */ 

                AuxD->nextD = HoldNextD; /* repoem AuxD na lista */

                HoldNextD = NULL;

                AuxD = AuxD->nextD;
            }
            AuxP->nextP = HoldNextP; /* repoem AuxP na lista */

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
{   /* troca os valores das lsitas secundárias */

    /* variáveis auxiliares */
    char temp_indicator[40] = {0};
    int temp_weekly_count = 0;
    char temp_data[40] = {0};
    int temp_cumulative_count = 0;
    float temp_rate_14_day = 0;

    /* troca os valores do indicator das 2 sublistas */
    strcpy(temp_indicator, a->indicator);
    strcpy(a->indicator, b->indicator);
    strcpy(b->indicator, temp_indicator);

    /* troca os valores da weekly_count das 2 sublistas */
    temp_weekly_count = a->weekly_count;
    a->weekly_count = b->weekly_count;
    b->weekly_count = temp_weekly_count;

    /* troca os valores da data das 2 sublistas */
    strcpy(temp_data, a->data);
    strcpy(a->data, b->data);
    strcpy(b->data, temp_data);

    /* troca os valores da cumulative_count das 2 sublistas */
    temp_cumulative_count = a->cumulative_count;
    a->cumulative_count = b->cumulative_count;
    b->cumulative_count = temp_cumulative_count;

    /* troca os valores do rate_14_day das 2 sublistas */
    temp_rate_14_day = a->rate_14_day;
    a->rate_14_day = b->rate_14_day;
    b->rate_14_day = temp_rate_14_day;

}


/** \brief lee o ficheiro de dados do tipo .csv escolhido pelo utilizador e cria uma lista com esses mesmos dados, 
 * restringido e selecionado os dados presentes no ficheiro de acordo com as opções escolhidas pelo utilidazor
 *
 * \param fp_in FILE*: apontador do ficheiro de onde se pretendem tirar os dados, em caso de algum erro é utilizado para fechar o ficheiro
 * \param fp_out FILE*: apontador do ficheiro onde serão escritos os dados, em caso de algum erro é utilizado para fechar o ficheiro
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
Pais *cria_ficheiro_de_dados(FILE *fp_in, FILE *fp_out, Pais *ListHead, char *nome_do_continente, char *selecao,  char *restricao, int num_habitantes, char *dataP1, char *dataP2)
{

    Pais *novopais, *Countryptr;
    Dados *novodado;

    char line[300]; /* variável onde é guardada uma linha lida do ficheiro */
    char *token; /* token retirado da linha com o strtok */
    char *dado[10]; /* local onde os dados são colocados depois de serem retirados da linha e metidos no token */
    
    /* variáveis de auxilio para validação dos dados e para serem colocadas nas estruturas das listas */
    char newcountry[30] = {0};
    char country_codeval[30] = {0};
    char continentval[30] = {0};
    char indicatorval[30] = {0};
    char populationval[30] = {0};
    char weekly_countval[30] = {0};
    char dataval[30] = {0};
    char rate_14_dayval[30] = {0};
    char cumulative_countval[30] = {0};
    int population_num = 0;
    int weekly_count_num = 0;
    float rate_14_day_num = 0;
    int cumulative_count_num = 0;

    /* variáveis de auxilio */
    int i = 0, j = 0;
    int t = 0;
    int letra = 0, numero = 0, c;

    while(fgets(line, 300, fp_in) != NULL ) /* faz a leitura de uma linha do ficheiro e coloca na variável line */
    {
        /* no primeiro caso t = 0 logo não vão ser tratados os dados da 1ª linha mas sim incrementado 1 a t para só se começarem a tratar os dados a partir da 2ª linha do ficheiro */
        if ( t != 0 )
        {
            /* retira os dados das linhas que estão delimitados por "," */
            token = strtok(line,",");
            dado[0] = token;
            i = 1;

            while (token != NULL)
            {
                token = strtok(NULL,",");
                dado[i] = token;
                i++;
            }

            if ( i < 9) /* se i < 9 falta um dado para além do dado rácio que é normal nem sempre estar presente */
            {
                printf("Erro de leitura: Valores em falta\n");
                free_lista(ListHead);
                fclose(fp_in);
                fclose(fp_out);
                exit(EXIT_FAILURE);
            }
            
            /* validação dos dados para os casos onde está presentes números onde deviam estar letras e letras onde deviam estar números */
            numero = 0;
            strcpy(newcountry, dado[0]); 
            for (c = 0; newcountry[c] != '\0'; c++)
            {
                // procura números na string
                if (isdigit(newcountry[c]) != 0)
                    numero++;
            }
            if (numero != 0)
            {
                printf("Erro de Leitura do dado country\n");
                free_lista(ListHead);
                exit(EXIT_FAILURE);
            }
            
            numero = 0;
            strcpy(country_codeval, dado[1]);
            for (c = 0; country_codeval[c] != '\0'; c++)
            {
                // procura números na string
                if (isdigit(country_codeval[c]) != 0)
                    numero++;
            }
            if (numero != 0)
            {
                printf("Erro de Leitura do dado country code\n");
                free_lista(ListHead);
                fclose(fp_in);
                fclose(fp_out);
                exit(EXIT_FAILURE);
            }
            
            numero = 0;
            strcpy(continentval, dado[2]);
            for (c = 0; continentval[c] != '\0'; c++)
            {
                // procura números na string
                if (isdigit(continentval[c]) != 0)
                    numero++;
            }
            if (numero != 0)
            {
                printf("Erro de Leitura do dado continent\n");
                free_lista(ListHead);
                fclose(fp_in);
                fclose(fp_out);
                exit(EXIT_FAILURE);
            }

            letra = 0;
            strcpy(populationval, dado[3]);
            for (c = 0; populationval[c] != '\0'; c++)
            {
                // procura letras na string
                if (isalpha(populationval[c]) != 0)
                    letra++;
            }
            if (letra != 0)
            {
                printf("Erro de Leitura do dado population\n");
                free_lista(ListHead);
                fclose(fp_in);
                fclose(fp_out);
                exit(EXIT_FAILURE);
            }
            
            numero = 0;
            strcpy(indicatorval, dado[4]);
            for (c = 0; indicatorval[c] != '\0'; c++)
            {
                // procura números na string
                if (isdigit(indicatorval[c]) != 0)
                    numero++;
            }
            if (numero != 0)
            {
                printf("Erro de Leitura do dado indicator\n");
                free_lista(ListHead);
                fclose(fp_in);
                fclose(fp_out);
                exit(EXIT_FAILURE);
            }

            letra = 0;
            strcpy(weekly_countval, dado[5]);
            for (c = 0; weekly_countval[c] != '\0'; c++)
            {
                // procura letras na string
                if (isalpha(weekly_countval[c]) != 0)
                    letra++;
            }
            if (letra != 0)
            {
                printf("Erro de Leitura do dado weekly_count\n");
                free_lista(ListHead);
                fclose(fp_in);
                fclose(fp_out);
                exit(EXIT_FAILURE);
            }

            strcpy(dataval, dado[6]); /* no caso da data é apenas validado se o valor da data é ou não um valor possível, sendo que um ano n tem mais que 54 semanas */
            if ( ( strcmp("2021-52", dataval) == -1 || strcmp("2020-00", dataval) == 1 || (strcmp("2020-53", dataval) == -1 && strcmp("2021-00", dataval) == 1) ) && strcmp(dataval, "") != 0 )
            {
                printf("Erro de Leitura do dado data\n");
                free_lista(ListHead);
                fclose(fp_in);
                fclose(fp_out);
                exit(EXIT_FAILURE);
            }

            letra = 0;
            strcpy(rate_14_dayval, dado[7]);
            for (c = 0; rate_14_dayval[c] != '\0'; c++)
            {
                // procura letras na string
                if (isalpha(rate_14_dayval[c]) != 0)
                    letra++;
            }
            if (letra != 0)
            {
                printf("Erro de Leitura do dado rate_14_day\n");
                free_lista(ListHead);
                fclose(fp_in);
                fclose(fp_out);
                exit(EXIT_FAILURE);
            }

            if ( dado[8] != NULL )
            {
                strcpy(cumulative_countval, dado[8]);
                letra = 0;
                for (c = 0; cumulative_countval[c] != '\0'; c++)
                {
                    // procura letras na string
                    if (isalpha(cumulative_countval[c]) != 0)
                        letra++;
                }
                if (letra != 0)
                {
                    printf("Erro de Leitura do dado cumulative_countval\n");
                    free_lista(ListHead);
                    fclose(fp_in);
                    fclose(fp_out);
                    exit(EXIT_FAILURE);
                }
            }
            
            /* passagem dos dados que não são strings de chars para uma variável */
            sscanf(dado[3],"%d", &population_num);

            sscanf(dado[5],"%d", &weekly_count_num);

            sscanf(dado[7],"%g", &rate_14_day_num); 

            sscanf(dado[8],"%d", &cumulative_count_num);

            if  (   /* apenas trata os dados dos países escolhidos pelo utilizador */
                    (strcmp(dado[2], nome_do_continente) == 0) || 
                    (strcmp(nome_do_continente, "all") == 0 )
                )
            {
                if  (   /* apenas trata os dados selecionados pelo utilizador */
                        ( strcmp(selecao, "inf") == 0 && strcmp(dado[4], "cases") == 0 )        ||
                        ( strcmp(selecao, "dea") == 0 && strcmp(dado[4], "deaths") == 0 )       ||
                        ( strcmp(selecao, "racioinf") == 0 && strcmp(dado[4], "cases") == 0 )   ||
                        ( strcmp(selecao, "raciodea") == 0 && strcmp(dado[4], "deaths") == 0 )  ||
                        ( strcmp(selecao, "") == 0)
                    )
                { 
                    if  (   /* apenas trata os dados restringidos pelo utilizador */
                            ( strcmp(restricao, "min") == 0 &&  population_num > num_habitantes )                   ||
                            ( strcmp(restricao, "max") == 0 &&  population_num < num_habitantes )                   ||
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
                        j = 0; /* o valor de j indica se já foram lidos dados sobre o país que está a ser lido da linha */

                        Countryptr = procurapais(ListHead, newcountry, &j); /* Função responsável por procurar se já há dados sobre este país */
                        /* retorna o valor de Auxptr(pointeiro que indica o local do país na lista principal) */

                        if ( j == 0 )
                        {
                            /* cria um nodo para a lista principal do tipo Pais no caso de j ser igual a 0, logo não foi encontrado nenhum dado sobre o país que estamos a ler da linha */
                            if ((novopais = (Pais*) calloc(1,sizeof(Pais))) == NULL)
                            {
                                printf("Erro: Não foi possível alocar o bloco de memória\n");
                                free_lista(ListHead);
                                fclose(fp_in);
                                fclose(fp_out);
                                exit(EXIT_FAILURE);
                            }

                            /* passa os valores dos dados retirados da linha para a estrutura novopais */
                            strcpy(novopais->country, dado[0]);

                            strcpy(novopais->country_code, dado[1]);
                            
                            strcpy(novopais->continent, dado[2]);
                            
                            novopais->population = population_num;
                    
                        }

                        if ( j == 0 || j == 1 )
                        {
                            /* cria um nodo para a lista secundária com os dados do país na linha que estamos a ler */
                            if ((novodado = (Dados*) calloc(1,sizeof(Dados))) == NULL)
                            {
                                printf("Erro: Não foi possível alocar o bloco de memória\n");
                                free_lista(ListHead);
                                fclose(fp_in);
                                fclose(fp_out);
                                exit(EXIT_FAILURE);
                            }
                            
                            /* passa os valores dos dados retirados da linha para a estrutura novodado */
                            strcpy(novodado->indicator, dado[4]);

                            novodado->weekly_count = weekly_count_num;

                            strcpy(novodado->data, dataval);
                            
                            novodado->rate_14_day = rate_14_day_num;

                            novodado->cumulative_count = cumulative_count_num;

                            if(i == 9) /* no caso de só terem sido lidos 9 dados significa que falta um dado na coluna rate_14_day para aquela linha e é feita uma troca dos 2 últimos elementos */
                            {
                                novodado->cumulative_count = novodado->rate_14_day;
                                novodado->rate_14_day = 0;
                            }

                            novodado->nextD = NULL;
                        }

                        if ( j == 0 ) 
                        {
                            /* coloca o novopais criado no final da lista */
                            novopais->nextD = novodado; /* o primeiro nodo da lista secundária é o primeiro novo dado criado da leitura da primeira linha lida daquele país */

                            novopais->nextP = NULL;

                            Pais *AuxT;

                            if(ListHead == NULL)
                            {
                                ListHead = novopais;
                            }
                            else
                            {
                                /* percorre os dados todos da lista principal até ao último país adicionado */
                                AuxT = ListHead;
                                while(AuxT->nextP != NULL) 
                                {
                                    AuxT = AuxT->nextP;
                                }

                                AuxT->nextP = novopais; /* o último nodo da lista principal aponta agora para o novo dado */
                            }
                        }

                        if ( j == 1 )
                        {
                            Dados *auxptrD;

                            /* percorre os dados todos da sublista até aos útimos dados variáveis adicionado */
                            auxptrD = Countryptr->nextD;
                            while (auxptrD->nextD != NULL) 
                            {
                                auxptrD = auxptrD->nextD;
                            }

                            auxptrD->nextD = novodado; /* o último nodo da lista secundária aponta agora para o novo dado */
                        }

                    }
                }
            }
        }else
        {
            t++; /* incrementa 1 para começar a ler apenas a partir da 2ª linha do  ficheiro */
        }
    }
    return ListHead; /* retorna a nova cabeça da lista */
}


/** \brief lee o ficheiro de dados do tipo .dat escolhido pelo utilizador e cria uma lista com esses mesmos dados
 *
 * \param ListHead Pais*: Cabeça da Lista principal que aponta
 * para o primeiro nodo da lista principal e ao qual é recorrido 
 * para percorrer a lista 
 * \param fp_in FILE*: apontador do ficheiro de onde se pretendem tirar os dados, em caso de algum erro é utilizado para fechar o ficheiro
 * \param fp_out FILE*: apontador do ficheiro onde serão escritos os dados, em caso de algum erro é utilizado para fechar o ficheiro
 * \return ListHead Pais*: Nova cabeça da lista
 *
 */
Pais *cria_ficheiro_de_dados_dat(Pais *ListHead, FILE *fp_in, FILE *fp_out)
{
    fseek(fp_in, 0, SEEK_END); /* vai para o fim do ficheiro que se pretende ler */
    long fileSize = ftell(fp_in); /* conta o número de bites do ficheiro e guarda em fileSize */
    rewind(fp_in); /* volta para o início do ficheiro */


    /* sendo que na criação do ficheiro binário se considerou que cada linha tinha uma estrutura de dados do tipo Dados e outra com o tipo Pais, 
    contou-se o número de linhas verificando quantas vezes foram passados 1 estrutura do tipo Dados e uma estrutura do tipo Pais*/
    int num_linhas = (int)( fileSize / ( sizeof(Dados)+sizeof(Pais) ) );

    int loop = 0;

    for ( loop = 0; loop < num_linhas; loop++) /* lê uma linha do ficheiro de cada vez */
    {
        fseek(fp_in, ( sizeof(Dados)+sizeof(Pais) )*loop, SEEK_SET); /* vai andado de linha em linha de forma a ler 1 linha de cada vez */
        ListHead = Lee_ficheiro_dat(ListHead, fp_in, fp_out); /* lê uma linha do ficheiro e cria uma estrutura que junta à lista com os dados */
    }
    return ListHead; /* retorna a nova cabeça da lista com os dados */
}


/** \brief função presente na função cria_ficheiro_de_dados_dat que lee os dados do ficheiro de dados do tipo .dat e mete-os em nodos na lista
 *
 * \param ListHead Pais*: Cabeça da Lista principal que aponta
 * para o primeiro nodo da lista principal e ao qual é recorrido 
 * para percorrer a lista 
 * \param fp_in FILE*: apontador do ficheiro de onde se pretendem tirar os dados
 * \param fp_out FILE*: apontador do ficheiro onde serão escritos os dados, em caso de algum erro é utilizado para fechar o ficheiro
 * \return ListHead Pais*: Nova cabeça da lista
 * 
 */
Pais *Lee_ficheiro_dat(Pais *ListHead, FILE *fp_in, FILE *fp_out)
{
    if (ListHead == NULL) /* se a cabeça da lista for igual a NULL é criada a nova lista */
    {
        Pais *novopais;
        Dados *novodado;

        /* cria um nodo para a lista principal do tipo Pais */
        if ((novopais = (Pais*) calloc(1,sizeof(Pais))) == NULL)
        {
            printf("Erro: Não foi possível alocar o bloco de memória\n");
            free_lista(ListHead);
            fclose(fp_in);
            fclose(fp_out);
            exit(EXIT_FAILURE);
        }
        fread(novopais, sizeof(Pais), 1, fp_in); /* lê do ficheiro os dados da primeira parte da linha a que correspondem os dados da struct Pais e coloca-os na struct com o novo dado */

        ListHead = novopais; /* o novopais criado é agora a primeira struct da lista */
        
        /* cria um nodo para a lista principal do tipo Dados */
        if ((novodado = (Dados*) calloc(1,sizeof(Dados))) == NULL)
        {
            printf("Erro: Não foi possível alocar o bloco de memória\n");
            free_lista(ListHead);
            fclose(fp_in);
            fclose(fp_out);
            exit(EXIT_FAILURE);
        }
        fread(novodado, sizeof(Dados), 1, fp_in); /* lê do ficheiro os dados da segunda parte da linha a que correspondem os dados da struct Dados */
        
        /* coloca na sublista do país lido os dados correspondentes ao novodado */
        novopais->nextD = novodado;
        novodado->nextD = NULL;
    }else /* no caso da cabeça da lista não ser igual a NULL são adicionados à lista já existente os novos dados */
    {
        Pais *novopais, *AuxP;
        Dados *novodado;

        /* cria um nodo para a lista principal do tipo Pais */
        if ((novopais = (Pais*) calloc(1,sizeof(Pais))) == NULL)
        {
            printf("Erro: Não foi possível alocar o bloco de memória\n");
            free_lista(ListHead);
            fclose(fp_in);
            fclose(fp_out);
            exit(EXIT_FAILURE);
        }
        
        /* cria um nodo para a lista principal do tipo Dados */
        if ((novodado = (Dados*) calloc(1,sizeof(Dados))) == NULL)
        {
            printf("Erro: Não foi possível alocar o bloco de memória\n");
            free_lista(ListHead);
            fclose(fp_in);
            fclose(fp_out);
            exit(EXIT_FAILURE);
        }

        /* percorre toda a lista principal até ao último nodo */
        AuxP = ListHead;
        while (AuxP->nextP != NULL)
        {
            AuxP = AuxP->nextP;
        }

        fread(novopais, sizeof(Pais), 1, fp_in); /* lê os dados da linha correspondestes aos dados que não variam para o mesmo país */
        fread(novodado, sizeof(Dados), 1, fp_in); /* lê os dados da linha correspondestes aos dados que variam para o mesmo país */

        if ( strcmp(AuxP->country, novopais->country) != 0 ) /* se o último país lido for diferente do novo país lido é adicionado um novo nodo na lista principal */
        {
            AuxP->nextP = novopais;
            novopais->nextP = NULL;
            
            /* percorre toda a lista principal até ao último nodo */
            while (AuxP->nextP != NULL) 
            {
                AuxP = AuxP->nextP;
            }

            AuxP->nextD = novodado; /* coloca na sublista do país lido os dados correspondentes ao novodado */

        }else /* no caso de o último país lido ser igual ao novo país lido são libertados os dados correspondeste ao novopaís e adicionados no final da lista principal */
        {
            free(novopais); /* liberta toda a memoria alocada para a struct novopais */

            Dados *AuxDdat;

            /* percorre toda a lista secundária até ao último nodo */
            AuxDdat = AuxP->nextD;
            while (AuxDdat->nextD != NULL)
            {
                AuxDdat = AuxDdat->nextD;
            }

            AuxDdat->nextD = novodado; /* coloca no final da sublista do país lido os dados correspondentes ao novodado */
        }
    }
    return ListHead; /* retorna a nova cabeça da lista */
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
    if (Auxptr != NULL)
    {
        /* percorre toda a lista principal até ao último nodo */
        while( Auxptr != NULL ) 
        {
            /* compara o nome do país com os restantes nomes presentes na lista principal */
            if (strcmp(Auxptr->country, newcountry) == 0) /* se encontrar um nodo com um país igual ao da linha j passa a 1 e retorna o valor do nodo onde encontrou o país com o mesmo nome */
            {
                (*j)++;
                return Auxptr;
            }else{ /* se não encontrou continua a procurar até Auxptr ser diferente de NULL */
                Auxptr = Auxptr->nextP;
            }
        }
    }else{
        return Auxptr; /* retorna o valor de Auxptr inalterado */
    }
    return Auxptr; /* retorna o valor de Auxptr inalterado */
}


/** \brief organiza a lista principal por ordem alfabética de acordo com o nome de cada país
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
    if (strcmp(ordenacao, "alfa") == 0) /* se a opção selecionada para ordenação foi "alfa" organiza a lista */
    {
        int trocas = 1;
        Pais *leftP, *rightP, *headP, aux_structP;

        headP = &aux_structP;
        headP->nextP = ListHead;

        /* se a lista tiver mais que 2 nodos */
        if ( (ListHead != NULL ) && ( (ListHead->nextP != NULL ) ) )
        {
            while(trocas) /* enquanto trocas for igual a 1 no final do while procura-se se a lista está ou n organizada alfabéticamente */
            {
                trocas = 0;
                leftP = headP;
                rightP = headP->nextP;
                while(rightP->nextP != NULL) /* percorre a lista principal até ao último nodo */
                {
                    if (strcmp(rightP->country, rightP->nextP->country) > 0) /* se o nome da country de rightP não estiver organizada alfabeticaemnte com o nodo seguinte faz a troca dos valores */
                    {
                        leftP->nextP = trocaP(rightP,rightP->nextP); /* para se fazer a troca recorre-se à função troca que altera para onde os nodos apontam */
                        trocas = 1;
                    }
                    /* no caso de o nome da country de rightP estar organizada alfabeticaemnte com o nodo seguinte avança-se até ao fim da lista principal */
                    leftP = rightP;
                    if (rightP->nextP != NULL)
                        rightP = rightP->nextP;
                }
            }
        }
        ListHead = headP->nextP;
    } 
    /* se a opção selecionada para ordenação não foi "alfa" a lista não é organizada e é retornado o valor de ListHead sem alterações */
    return ListHead; /* retorna a nova cabeça da lista */
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
    leftP->nextP = rightP->nextP; /* leftP passa a apontar para onde rightP apontava */
    rightP->nextP = leftP; /* rightP passa a apontar para onde leftP apontava */
    return rightP; /* retorna a nova posição de rightP */
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
    if  ( ( strcmp(selecao, "inf") == 0 ) || ( strcmp(selecao, "dea") == 0 ) ) /* se a opção selecionada para seleção foi "inf" ou "dea" organiza a lista */
    {
        Pais *auxptrind;

        for( auxptrind = ListHead; auxptrind != NULL; auxptrind = auxptrind->nextP ) /* percorre a lista principal até auxptrind ser NULL */
        {
            Dados *SubListHeadD;

            SubListHeadD = auxptrind->nextD; /* cabeça da lista secundária ligada a auxptrind */

            int swapped, i;
            Dados *ptr1;
            Dados *lptr = NULL;

            do /* enquanto swapped for igual a 1 no final do do while continua a procurar na lista até ela estar organizada por weekly_count */
            {
                swapped = 0;
                ptr1 = SubListHeadD;

                /* percorre a lista secundária até ao último nodo */
                while (ptr1->nextD != lptr)
                {
                    if (ptr1->weekly_count < ptr1->nextD->weekly_count) /* se o valor da weekly_count do nodo onde estamos na lista secundária for menor ao do nodo seguinte entram trocam-se os valores dos dados presentes em ambos */
                    {
                        swap(ptr1, ptr1->nextD); /* função que troca os valores do nodo onde estamos e do nodo seguinte */
                        swapped = 1;
                    }else if (ptr1->weekly_count == ptr1->nextD->weekly_count) /* no caso de ambos os nodos terem o mesmo valor para weekly_count */
                    {
                        if (ptr1->data < ptr1->nextD->data) /* ocorre a troco dos valores se a data do nodo for menor que a data do nodo seguinte */
                        {
                            swap(ptr1, ptr1->nextD); /* função que troca os valores do nodo onde estamos e do nodo seguinte */
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
    /* se a opção selecionada para seleção não foi "inf" ou "dea" a lista não é organizada e é retornado o valor de ListHead sem alterações */
    return ListHead; /* retorna o valor da cabeça da lista principal não alterada */
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
    if  ( ( strcmp(selecao, "racioinf") == 0 ) || ( strcmp(selecao, "raciodea") == 0 ) ) /* se a opção selecionada para seleção foi "racioinf" ou "raciodea" organiza a lista */
    {
        Pais *auxptrind;

        for( auxptrind = ListHead; auxptrind != NULL; auxptrind = auxptrind->nextP ) /* percorre a lista principal até auxptrind ser NULL */
        {
            Dados *SubListHeadD;

            SubListHeadD = auxptrind->nextD; /* cabeça da lista secundária ligada a auxptrind */

            int swapped, i;
            Dados *ptr1;
            Dados *lptr = NULL;

            do /* enquanto swapped for igual a 1 no final do do while continua a procurar na lista até ela estar organizada por rate_14_day */
            {
                swapped = 0;
                ptr1 = SubListHeadD;

                /* percorre a lista secundária até ao último nodo */
                while (ptr1->nextD != lptr)
                {
                    if ( ptr1->rate_14_day < ptr1->nextD->rate_14_day ) /* se o valor da weekly_count do nodo onde estamos na lista secundária for menor ao do nodo seguinte entram trocam-se os valores dos dados presentes em ambos */
                    {
                        swap(ptr1, ptr1->nextD); /* função que troca os valores do nodo onde estamos e do nodo seguinte */
                        swapped = 1;
                    }
                    ptr1 = ptr1->nextD;
                }
                lptr = ptr1;
            }
            while (swapped);
        }
    }
    /* se a opção selecionada para seleção não foi "racioinf" ou "raciodea" a lista não é organizada e é retornado o valor de ListHead sem alterações */
    return ListHead; /* retorna o valor da cabeça da lista principal não alterada */
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
    if ( strcmp(ordenacao, "pop") == 0 ) /* se a opção selecionada para ordenação foi "pop" organiza a lista */
    {
        int trocas = 1;
        Pais *leftP, *rightP, *headP, aux_structP;

        headP = &aux_structP;
        headP->nextP = ListHead;
        /* se a lista tiver mais que 2 nodos */
        if ((ListHead != NULL ) && ((ListHead->nextP != NULL )))
        {
            while(trocas) /* enquanto trocas for igual a 1 no final do while procura-se se a lista está ou n organizada por ordem decrescente de population */
            {
                trocas = 0;
                leftP = headP;
                rightP = headP->nextP;
                while(rightP->nextP != NULL) /* percorre a lista principal até ao último nodo */
                {
                    if ((rightP->population) < (rightP->nextP->population)) /* se a population do nodo onde estamos for maior que a population do nodo seguinte faz a troca dos valores */
                    {
                        leftP->nextP = trocaP(rightP,rightP->nextP); /* para se fazer a troca recorre-se à função troca que altera para onde os nodos apontam */
                        trocas = 1;
                        /* avança-se até ao fim da lista principal */
                        leftP = rightP;
                        if (rightP->nextP != NULL)
                        {
                            rightP = rightP->nextP;
                        }
                    }else if((rightP->population == rightP->nextP->population) && (strcmp(rightP->country, rightP->nextP->country) > 0)) /* no caso do valor population se igual em ambos os nodos serve como desempate a ordem alfabética segundo a country do nodo */
                    {
                        leftP->nextP = trocaP(rightP,rightP->nextP); /* para se fazer a troca recorre-se à função troca que altera para onde os nodos apontam */
                        trocas = 1;
                        /* avança até ao fim da lista principal */
                        leftP = rightP;
                        if (rightP->nextP != NULL)
                        {
                            rightP = rightP->nextP;
                        }
                    }else
                    {
                        /* no caso de o nome da country de rightP estar organizado de forma decrescente pelo valor da population com o nodo seguinte avança-se até ao fim da lista principal */
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
    /* se a opção selecionada para ordenação não foi "pop" a lista não é organizada e é retornado o valor de ListHead sem alterações */
    return ListHead; /* retorna a nova cabeça da lista */
}


/** \brief ordena os paises por ordem decrescente do número total de mortes ou casos numa determinada data
 *
 * \param fp_in FILE*: apontador do ficheiro de onde se pretendem tirar os dados, em caso de algum erro é utilizado para fechar o ficheiro
 * \param fp_out FILE*: apontador do ficheiro onde serão escritos os dados, em caso de algum erro é utilizado para fechar o ficheiro
 * \param ListHead Pais*: Cabeça da Lista principal que aponta
 * para o primeiro nodo da lista principal e ao qual é recorrido 
 * para percorrer a lista
 * \param ordenacao char*: se foi selecionada a opção "inf" ou "dea" pelo utilizador a função ordena_indicador_paises ordena os paises da lista principal 
 * de forma decrescente segundo o número de casos ou mortos nessa semana servindo de desempate a semana mais recente no caso de 2 paises terem o mesmo valor, 
 * se não for selecionada nenhuma opção sai da função e retorna List Head com o mesmo valor
 * \param dataS1 char*: se a data selecionada para ordenação
 * \param restricao char*: se foi utilizada uma data fora de intervalo de datas da restrição este parâmetro permite determinar se é necessário apagar alguma 
 * data criada com o objetivo de facilitar a ordenação
 * \param dataP1 char*: utilizado para comparar a data ou intervalo de datas escolhido para a seleção dos dados
 * \param dataP2 char*: utilizado para o intervalo de datas escolhido para a seleção dos dados
 * \return ListHead Pais*: Nova cabeça da lista
 *
 */
Pais *ordena_indicador_paises(FILE *fp_in, FILE *fp_out,Pais *ListHead, char *ordenacao, char *dataS1, char *restricao, char *dataP1, char *dataP2)
{
    if ( strcmp(ordenacao, "inf") == 0 || strcmp(ordenacao, "dea") == 0 ) /* se a opção selecionada para ordenação foi "inf" ou "dea" organiza a lista */
    {
        int trocas = 1;
        Pais *leftP, *rightP, *headP, aux_structP;

        headP = &aux_structP;
        headP->nextP = ListHead;
        /* se a lista tiver mais que 2 nodos */
        if ((ListHead != NULL ) && ((ListHead->nextP != NULL )))
        {
            while(trocas) /* enquanto trocas for igual a 1 no final do while procura-se se a lista está ou n organizada por ordem decrescente de weekly_count por pais numa dada data */
            {
                trocas = 0;
                leftP = headP;
                rightP = headP->nextP;
                while( rightP->nextP != NULL ) /* percorre a lista principal até ao último nodo */
                {

                    Dados *rightD, *rightDnext;

                    rightD = rightP->nextD;

                    while ( rightD != NULL ) /* percorre a lista secundária até ao último nodo */
                    {
                        /* se o valor da data do nodo da lista secundária for igual ao da data escolhida para ordenar a lista,
                        rightD sai da função com o valor do nodo com a mesma data que a data selecionada para ordenação */
                        if ( strcmp(rightD->data, dataS1) == 0) 
                        {
                            break;
                        }else /* se o valor da data for diferente continua a percorrer a lista secundária */
                        {
                            rightD = rightD->nextD;
                        }
                    }

                    rightDnext = rightP->nextP->nextD; /* nodo que vem depois de rightP na lista principal */

                    while ( rightDnext != NULL) /* percorre a lista secundária até ao último nodo */
                    {
                        /* se o valor da data do nodo da lista secundária for igual ao da data escolhida para ordenar a lista,
                        rightD sai da função com o valor do nodo com a mesma data que a data selecionada para ordenação */
                        if ( strcmp(rightDnext->data, dataS1) == 0)
                        {
                            break;
                        }else /* se o valor da data for diferente continua a percorrer a lista secundária */
                        {
                            rightDnext = rightDnext->nextD;
                        }
                    }

                    /* se não for encontrado nenhum nodo na lista secundária com o valor da data escolhida para organizar a lista
                    é criado um novo dado com essa data e sem valores para servir de ordenação */
                    if (rightD == NULL)
                    {
                        Dados *novodado;

                        /* cria um nodo para a lista secundária do tipo Dados */
                        if ((novodado = (Dados*) calloc(1,sizeof(Dados))) == NULL)
                        {
                            printf("Erro: Não foi possível alocar o bloco de memória\n");
                            free_lista(ListHead);
                            fclose(fp_in);
                            fclose(fp_out);
                            exit(EXIT_FAILURE);
                        }

                        /* consoante a ordenação escolhida pelo utilizador é criado um dado com o indicador que se pretende ordenar */
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

                        /* percorre os dados todos do país até ao último dado */
                        auxptrD = rightP->nextD;
                        while (auxptrD->nextD != NULL) 
                        {
                            auxptrD = auxptrD->nextD;
                        }

                        auxptrD->nextD = novodado; /* coloca o novo dado no fim da lista */

                        rightD = novodado; /* rightD aponta agora para o novo dado que tem o valor para a data que se pretende ordenar */

                    }

                    /* se não for encontrado nenhum nodo na lista secundária com o valor da data escolhida para organizar a lista
                    é criado um novo dado com essa data e sem valores para servir de ordenação */
                    if (rightDnext == NULL)
                    {
                        Dados *novodado;

                        /* cria um nodo para a lista secundária do tipo Dados */
                        if ((novodado = (Dados*) calloc(1,sizeof(Dados))) == NULL)
                        {
                            printf("Erro: Não foi possível alocar o bloco de memória\n");
                            free_lista(ListHead);
                            fclose(fp_in);
                            fclose(fp_out);
                            exit(EXIT_FAILURE);
                        }

                        /* consoante a ordenação escolhida pelo utilizador é criado um dado com o indicador que se pretende ordenar */
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

                        /* percorre os dados todos do país até ao último dado */
                        auxptrD = rightP->nextP->nextD;
                        while (auxptrD->nextD != NULL)
                        {
                            auxptrD = auxptrD->nextD;
                        }

                        auxptrD->nextD = novodado; /* coloca o novo dado no fim da lista */

                        rightDnext = novodado; /* rightDnext aponta agora para o novo dado que tem o valor para a data que se pretende ordenar */

                    }

                    if ( rightD->weekly_count < rightDnext->weekly_count ) /* se a weekly_count do nodo principal que estamos a ler para uma dada semana for menor do que a do nodo seguinte faz a troca dos valores */
                    {
                        leftP->nextP = trocaP(rightP,rightP->nextP); /* para se fazer a troca recorre-se à função troca que altera para onde os nodos apontam */
                        trocas = 1;
                        leftP = rightP;
                    }else if( ( rightD->weekly_count == rightDnext->weekly_count ) && ( strcmp(rightP->country, rightP->nextP->country) > 0 ) )
                    {
                        if(strcmp(rightP->country, rightP->nextP->country) > 0) /* no caso dos valores serem iguais serve como desempate a ordem alfabética de acordo com a country de cada nodo principal */
                        {
                            leftP->nextP = trocaP(rightP,rightP->nextP); /* para se fazer a troca recorre-se à função troca que altera para onde os nodos apontam */
                            trocas = 1;
                        }
                        leftP = rightP;
                    }else
                    {
                        leftP = rightP;
                    }
                    /* no caso de o nome da country de rightP estar organizado de forma decrescente pelo valor da population com o nodo seguinte avança-se até ao fim da lista principal */
                    if (rightP->nextP != NULL)
                    {
                        rightP = rightP->nextP;
                    }
                }
            }
            ListHead = headP->nextP;
        }
        /* elimina dados não selecionados que foram criados para auxilio na ordenação */
        if  (   /* se a data selecionada n está dentro dos valores de seleção apaga a data */
                ( strcmp(restricao, "date") == 0 && strcmp(dataS1, dataP1) != 0 )                                                                                                       ||
                ( strcmp(restricao, "dates") == 0 && ( strcmp(dataS1, dataP1) == -1 || strcmp(dataS1, dataP1) != 0 ) && ( strcmp(dataS1, dataP2) == 1 || strcmp(dataS1, dataP2) != 0 ) )
            )
        {
            Pais *AuxcleanP;

            AuxcleanP = ListHead;
            
            /* percorre todos os nodos da lista principal */
            while (AuxcleanP != NULL)
            {
                Dados *AuxcleanD;

                AuxcleanD = AuxcleanP->nextD;
                
                /* percorre todos os nodos da lista secundária */
                while ( AuxcleanD != NULL )
                {
                    if ( strcmp(AuxcleanD->nextD->data, dataS1) == 0 ) /* se o próximo nodo da lista secundária tiver a mesma data que a data selecionada ou intervalo de datas do campo seleção */
                    {
                        free(AuxcleanD->nextD); /* liberta nodo com a data criada */
                        AuxcleanD->nextD = NULL;
                        break;
                    }else /* se não tiver a mesma data continua a percorrer a sublista */
                    {
                        AuxcleanD = AuxcleanD->nextD;
                    }
                }
                AuxcleanP = AuxcleanP->nextP;
            }
        }
    }
    /* se a opção selecionada para ordenação não foi "inf" ou "dea" a lista não é organizada e é retornado o valor de ListHead sem alterações */
    return ListHead;
}

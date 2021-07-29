/* Trabalho realizado por:
   Tomás Marques nº100104 MEEC */

#ifndef covid19_H_INCLUDED
#define covid19_H_INCLUDED


/* Estrutura de dados utilizada para guardar os dados sobre os países */
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


/* cabeçalhos das funções para criar, selecionar, restringir e ordenar os Dados */

/** \brief libertar a memória alocada para todos os elementos da lista principal e das listas secundárias
 *
 * \param ListHead Pais*: Cabeça da Lista principal que aponta
 * para o primeiro nodo da lista principal e ao qual é recorrido 
 * para percorrer a lista 
 * \return void
 *
 */
void free_lista(Pais *ListHead);

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
void print_lista_terminal(Pais *ListHead, char *selecao);

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
void printf_lista_Stdout_csv(Pais *ListHead, char *selecao, FILE *fp_out, char *output_filename);

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
void printf_lista_Stdout_bin(Pais *ListHead, char *selecao, FILE *fp_out, char *output_filename);

/** \brief troca o conteudo de 2 sub listas
 *
 * \param a Dados*: ponteiro de uma sublista do tipo Dados
 * \param a Dados*: ponteiro de uma sublista do tipo Dados
 * \return void
 *
 */
void swap(Dados *a, Dados *b);

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
Pais *cria_ficheiro_de_dados(FILE *fp_in, Pais *ListHead, char *nome_do_continente, char *selecao,  char *restricao, int num_habitantes, char *dataP1, char *dataP2);

/** \brief lee o ficheiro de dados do tipo .dat escolhido pelo utilizador e cria uma lista com esses mesmos dados
 *
 * \param ListHead Pais*: Cabeça da Lista principal que aponta
 * para o primeiro nodo da lista principal e ao qual é recorrido 
 * para percorrer a lista 
 * \param fp_in FILE*: apontador do ficheiro de onde se pretendem tirar os dados
 * \return ListHead Pais*: Nova cabeça da lista
 *
 */
Pais *cria_ficheiro_de_dados_dat(Pais *ListHead, FILE *fp_in);

/** \brief função presente na função cria_ficheiro_de_dados_dat que lee os dados do ficheiro de dados do tipo .dat e mete-os em nodos na lista
 *
 * \param ListHead Pais*: Cabeça da Lista principal que aponta
 * para o primeiro nodo da lista principal e ao qual é recorrido 
 * para percorrer a lista 
 * \param fp_in FILE*: apontador do ficheiro de onde se pretendem tirar os dados
 * \return ListHead Pais*: Nova cabeça da lista
 * 
 */
Pais *Lee_ficheiro_dat(Pais *ListHead, FILE *fp_in);

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
Pais *procurapais(Pais *ListHead, char *newcountry, int *j);

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
Pais *ordena_lista_alf(Pais *ListHead, char *ordenacao);

/** \brief recebe dois ponteiros da lista principal e troca as suas posições na lista principal 
 *
 * \param leftP Pais*: ponteiro de um dos nodos da lista princiapl
 * \param rightP Pais*: ponteiro de um dos nodos da lista princiapl
 * \return rightP Pais*: retorna a nova posição de rightP
 *
 */
Pais *trocaP(Pais *leftP,Pais *rightP);

/** \brief recebe dois ponteiros da lista secundária e troca as suas posições na lista secundária
 * 
 * \param leftD Pais*: ponteiro de um dos nodos da lista secundária
 * \param rightD Pais*: ponteiro de um dos nodos da lista secundária
 * \return rightD Pais*: retorna a nova posição de rightD
 *
 */
Dados *trocaD(Dados *leftD,Pais *rightD);

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
Pais *ordena_indicator_decrescente(Pais *ListHead, char *selecao);

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
Pais *ordena_racio_decrescente(Pais *ListHead, char *selecao);

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
Pais *ordena_lista_pop(Pais *ListHead, char *ordenacao);

/** \brief libertar a memória alocada para todos os elementos da lista principal e das listas secundárias
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
Pais *ordena_indicador_paises(Pais *ListHead, char *ordenacao, char *dataS1, char *restricao, char *dataP1, char *dataP2);

/* retirar a parte da restrição se n necessitar */

#endif // covid19_H_INCLUDED
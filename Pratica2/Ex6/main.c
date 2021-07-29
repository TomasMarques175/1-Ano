#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#define MAX_VECTOR 10   /* tamanho máximo do vector */
#define DEFAULT_MIN 1   /* valor por omissão para o mínimo número aleatório */
#define DEFAULT_MAX 6   /* valor por omissão para o máximo número aleatório */
#define DEFAULT_NUM 3   /* valor por omissão para o número de números aleatórios a gerar */


/** \brief função que gera um vector com "num" números aleatórios entre "min" e "max", inclusivé, com ou sem números repetidos
 *
 * \param min int:  valor mais baixo para os números aleatórios
 * \param max int:  valor mais alto para os números aleatórios
 * \param num int:  quantos números aleatórios devem ser gerados
 * \param repeticoes int:  1 se são permitidas repetições de números aleatórios, 0 se não são permitidas repetições
 * \return int*:    vector com os números aleatórios gerados, ou NULL se não é possível.
 *
 */
int *gera_aleatorios(int min, int max, int num, int repeticoes)
{
    static int vector_numeros[MAX_VECTOR]; /* esta variável mantém-se de forma permanente */
    int i, j, incremento, modulo;

    /* validar argumentos: é impossível se gama não tem números, ou há mais números que posições do vector,
      ou não são permitidas repetições de números e há mais números a sortear que números diferentes possíveis */
    modulo= max-min+1;
    if (modulo<1 || num>MAX_VECTOR || (!repeticoes && num>modulo))
        return NULL;
    /* gerar números aleatórios */
    for (i= 0 ; i < num ; i+= incremento) {
        vector_numeros[i]= min + (rand()%modulo);
        incremento= 1; /* por omissão, passa ao próximo número */
        /* verificar números duplicados: compara o número gerado "i" com todos os já gerados anteriormente */
        if (!repeticoes)
            for (j= 0 ; j < i ; j++)
                if (vector_numeros[i]==vector_numeros[j]){
                    incremento= 0; /* achei um duplicado: forçar repetçião da geração do número "i" */
                    break;
                }
    }
    return vector_numeros;
}
/** \brief mostra as instruções de utilização do programa
 *
 * \param programa char*: nome do programa
 * \return void
 *
 */
void utilizacao(char *programa)
{
    printf("Programa que gera números aleatórios.\n\n");
    printf("Utilização: %s [opções]\n", programa);
    printf("opções válidas:\n");
    printf("[-h]\t\t   mostrar instruções\n");
    printf("[-n num]\t   define quantos números aleatórios são gerados (por omissão %d)\n", DEFAULT_NUM);
    printf("[-m num]\t   define o menor valor para os números aleatórios a gerar (por omissão %d)\n", DEFAULT_MIN);
    printf("[-M num]\t   define o maior valor para os números aleatórios a gerar (por omissão %d)\n", DEFAULT_MAX);
    printf("[-r]\t\t   não permite utilização de repetições de números aleatórios\n");
    printf("[-R]\t\t   permite utilização de repetições de números aleatórios (por omissão)\n");
    printf("\nexemplos:\n");
    printf("%s -n 3 -m 1 -M 6 -R\t\t   gera o valor de 3 dados de 1 a 6\n", programa);
    printf("%s -n 5 -m 1 -M 49 -r\t\t gera 5 números de 1 a 49 sem repetições\n", programa);
}


/** \brief programa principal para gerar números aleatórios
 *
 * \param argc int:     número de argumentos na linha de comando
 * \param argv[] char*: vector de strings com os argumentos na linha de comando
 * \return int:         sucesso do programa
 *
 */
int main(int argc, char *argv[])
{
    int *meu_vector;
    int i,
        minimo= DEFAULT_MIN,
        maximo= DEFAULT_MAX,
        numeros= DEFAULT_NUM,
        repeticoes= 1;
    int opt= 'h';    /* opção para getopt() */

    opterr= 0; /* para getopt() não gerar erros por opções inválidas */
    /* processar as opções da linha de comando */
    while ((opt= getopt(argc, argv, "hrRn:m:M:")) != -1) {
        switch (opt) {
            case 'n': /* quantos números devem ser gerados */
                sscanf(optarg, "%d", &numeros); /* se houver erro, fica o valor por omissão */
                break;
            case 'm': /* mínimo */
                sscanf(optarg, "%d", &minimo);
                break;
            case 'M': /* máximo */
                sscanf(optarg, "%d", &maximo);
                break;
            case 'r': /* sem repetições */
                repeticoes= 0;
                break;
            case 'R': /* com repetições */
                repeticoes= 1;
                break;
case 'h': /* help */
            default: /* '?' opções inválidas */
                printf("Erro: opção '%c' desconhecida.\n\n", optopt);
                utilizacao(argv[0]);
                return EXIT_FAILURE;
                break;
        }
    }
    /* iniciar semente dos números aleatórios com base na hora actual */
    srand((unsigned)time(NULL));

    /* gerar números aleatórios */
    meu_vector= gera_aleatorios(minimo, maximo, numeros, repeticoes);
    /* escrever os números do vector no écran */
    if (meu_vector==NULL) {
        printf("Parâmetros inválidos.\n\n");
        utilizacao(argv[0]);
        return EXIT_FAILURE;
    } else {
        for (i= 0 ; i < numeros ; i++)
            printf("%d ", meu_vector[i]);
        printf("\n");
    }

    return EXIT_SUCCESS;
}



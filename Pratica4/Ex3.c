#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int n_inteiros=0, indice, maximo, minimo, *vector_inteiros=NULL, result;
    double soma=0, soma_quadrados=0, media, desvio_padrao;

    do {
        printf("Introduza o número de inteiros a ler: ");
        if ((result= scanf("%d", &n_inteiros)) < 1) {
            printf("Não consegui ler um número\n");
            if (result==EOF)
                exit(EXIT_FAILURE);
            scanf("%*[^\n]");  /* deitar fora a linha */
        } else if (n_inteiros>0)
                if ((vector_inteiros=(int*)malloc(n_inteiros*sizeof(int)))==NULL)  {
                    printf("Erro de alocação de memória. Número demasiado grande.\n");
                }
    } while (n_inteiros<1 || vector_inteiros==NULL);
    /* ler os inteiros e processá-los */
    for (indice=0 ; indice < n_inteiros ; indice++)  {
        printf("Introduza número %d: ", indice+1);
        if ((result= scanf("%d", &vector_inteiros[indice])) < 1){
            printf("Não consegui ler um número\n");
            if (result==EOF)  {
                free(vector_inteiros);
                exit(EXIT_FAILURE);
            }
            scanf("%*[^\n]");   /* deitar fora a linha */
            indice--;   /* voltar a ler o mesmo número */
        } else {
            /* actualizar soma, soma dos quadrados, máximo e mínimo */
            soma+= vector_inteiros[indice];
            soma_quadrados+= (double)vector_inteiros[indice]*vector_inteiros[indice]; // cast para double para evitar overflows
            if (indice==0)
                maximo= minimo= vector_inteiros[0];
            else {
                if (vector_inteiros[indice] > maximo)
                    maximo= vector_inteiros[indice];
                if (vector_inteiros[indice] < minimo)
                    minimo= vector_inteiros[indice];
            }
        }
    }
    /* cálculo e escrita das estatísticas */
    printf("Máximo: %d\n", maximo);
    printf("Mínimo: %d\n", minimo);
    media= soma/n_inteiros;
    printf("Média: %f\n", media);
    /* Desvio padrão= Raiz Quadrada(Média dos Quadrados - (Média)^2)  */
    desvio_padrao=sqrt(soma_quadrados/n_inteiros - media*media);
    printf("Desvio padrão: %f\n", desvio_padrao);
    /* escrever os valores que distam mais que um desvio padrão do valor médio */
    printf("Lista de inteiros que distam mais que um desvio padrão do valor médio:\n");
    for (indice=0 ; indice < n_inteiros ; indice++)  {
        if (fabs(vector_inteiros[indice] - media) > desvio_padrao) {
            printf("%d\n", vector_inteiros[indice]);
        }
    }
    /* libertar a memória alocada antes de terminar */
    free(vector_inteiros);
    return EXIT_SUCCESS;
}

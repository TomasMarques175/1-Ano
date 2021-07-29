#include <stdio.h>
#include <stdlib.h>

/* programa principal */
int main()
{
    int mes;

    do {
        /* Lê o mês e valida */
        printf("Insira mês (1-12): ");
        if (scanf("%d",&mes)<1)
            return EXIT_FAILURE;
        /* escreve o número de dias */
        switch (mes) {
            case 2:
                printf("Dias: 29\n");
                break; /* break para sair do switch */
            case 4:
            case 6:
            case 9:
            case 11: /* todos estes casos executam o mesmo código */
                printf("Dias: 30\n");
                break;
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                printf("Dias: 31\n");
                break;
            default:
                break;
        }
    } while ((mes <= 12) && (mes >=1));
    printf("FIM: O número não está entre 1 e 12\n");

    return EXIT_SUCCESS;
}

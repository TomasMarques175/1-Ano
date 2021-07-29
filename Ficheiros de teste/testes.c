#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <getopt.h>

typedef struct  _Teste
{
    int Nota;
    char cadeira[30];
}Teste;

typedef struct  _Caneta
{
    int EX1;
    char cadeira[30];
}Caneta;

void Pain(char *teste)
{
    printf("%s", teste);
}

int main()
{
    /*
    char *dado[10];
    char teste[30] = "bola";

    Teste *ListHead = NULL;
    Teste *valor;

    if ((valor = (Teste*) calloc(1,sizeof(Teste))) == NULL)
    {
        printf("Erro: Não foi possível alocar o bloco de memória\n");
        exit(EXIT_FAILURE);
    }

    char str[80] = "This is - www.tutorialspoint.com - website";
    const char s[2] = "-";
    char *token;
    int i = 0;
    
    token = strtok(str, s);
    printf("valor de token=%s\n", token);
    strcpy(dado[0], token);
    printf("valor dado =%s\n",dado[0]);

    while( token != NULL ) {
        token = strtok(NULL, s);
        dado[i]= token;
        printf("valor de token=%s\n", token);
        printf("valor dado =%s\n",dado[i]);
        i++;
    }
    */

    char value1[10] = "1";
    char dataval[10] = "2021-20";
    char value3[10] = "2020-20";

    if ( ( strcmp("2021-52", dataval) == -1 || strcmp("2020-00", dataval) == 1 || (strcmp("2020-53", dataval) == -1 && strcmp("2021-00", dataval) == 1) ) && strcmp(dataval, "") != 0 )
    {
        printf("Erro de Leitura do dado data");
    }


    char str[30] = "8901064";
 
    int alphabet = 0, number = 0, i;
    for (i = 0; str[i] != '\0'; i++)
    {
     
        // check for alphabets
        if (isalpha(str[i]) != 0)
            alphabet++;
 
        // check for decimal digits
        else if (isdigit(str[i]) != 0)
            number++;
    }
 
    printf("Alphabetic_letters = %d, "
           "Decimal_digits = %d\n",
           alphabet, number);




/*
    if (strcmp(teste, "bola") == 0)
    {
        printf("lol");

    }
*/
    return 0;
}
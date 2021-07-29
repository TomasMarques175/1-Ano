#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


void liberta_mem(char *linhas[], int n_strings)
{
    int i;

    if (linhas!=NULL) {
        for (i=0 ; i < n_strings ; i++)
            if (linhas[i]!=NULL)
                free(linhas[i]);
        free(linhas);
    }
}

void main(){
    FILE *fp;
    char  string[140];
    char **linhas=NULL;
    int n_strings=0; 
    int i;
    char nome[99];

    if ((fp= fopen("RunResults.txt", "r"))==NULL)  {
        printf("Não consegui abrir o ficheiro. Programa terminado\n");
        exit(EXIT_FAILURE);
    }

    fgets(string,140,fp);
    
    while (fgets(string,141,fp)!=NULL)
    {
        if (linhas==NULL|| (n_strings%10)==0)  
        {
    
            linhas= (char**)realloc(linhas, (n_strings+10)*sizeof(char*));
            if (linhas==NULL)
            {
                printf("realloc falhou. ficheiro demasiado grande. programa terminado.\n");
                exit(EXIT_FAILURE);
            }
        }

        linhas[n_strings]= (char*)malloc(strlen(string)+2);
        strcpy(linhas[n_strings++], string);
    }
    fclose(fp);
    
    scanf("%[^\n]%*c",nome);

    if (linhas!=NULL) {
        for (i=0 ; i < n_strings ; i++)
            if (linhas[i]!=NULL)
            if(strstr(linhas[i],nome)!=NULL){
                printf("%s",linhas[i]);
            }         
    }

liberta_mem(linhas,n_strings);

}
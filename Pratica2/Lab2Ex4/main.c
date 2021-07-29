#include <stdio.h>
#include <stdlib.h>

#define MAX_R 9
#define MAX_VECTOR 100

int le_inteiros(int vector[])
void code_vector(int vector[], int n_ints, int codes[], int * code_size);

/*
int main()
{
    int vector[MAX_VECTOR];
    int code[MAX_VECTOR * 2];

    int n_ints;
    int code_size;

    int i;

    n_ints = le_inteiros(vector);

    printf("Ve ctor to encode: \n");
    for(i=0; i < n_ints; i++) {
        printf("%d", vector[i]);
    }
    code_vector(vector, n_ints, code , &code_size)i;
}

void decode_vector(int code[], int code_size, int vector[]) {

    int n_int = 0;

    for(int i= 0; i < code_size; i+= 2) {
        for(int j = 0; j < code[i]; j++) {
            vector[]
        }
    }



}












void code_vector(int vector[], int n_ints, int codes[], int * code_size) {
    int i, a_rep, a_num;

    for(i = 0, *code_size = 0, a_rep = 0, a_num=-1; i < n_ints; i++) {
     if(a_rep = 0 || a_rep > MAX_R || a_num!=vector[i] {

        a_num = vector [i];
        a_rep = 1;
        code[(*code_size)++] = a_rep;
        code[(*code_size)++] = a_num;
        }else {
        code[(*code_size) - 2]++;
        a_rep++;
        }
    }
}






int le_inteiros(int vector[]){

    printf("Quantos numeros quer inserir? (1-%d)", MAX_VECTOR);

    do{
        scanf(("%1d", &n_int) < 0) {
        printf("Erro na leitura!\n");
        exit(EXIT_FAILURE)
        }
    }while((n_int > MAX_VECTOR || (n_int < 1));

    printf("insira os algarismos \n");

    for(i = 0; i < n_int; i++){
     do {

   if(scanf("%1d", &vector[i] < 1){
        printf("Erro na leitura!\n");
        exit(EXIT_FAILURE);
        }
    }
}

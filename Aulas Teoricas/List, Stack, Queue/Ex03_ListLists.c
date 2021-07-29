#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Notas{
    float   Nota;
    struct  Notas *nextN;
} Notas;

typedef struct _Student_Data{
    char    ID[20];
    float   NF;
    Notas   *nextN;
    struct  _Student_Data *nextS;
} Student_Data;

Student_Data *cria_aluno(int);
Student_Data *insere_aluno_na_listaordenada(Student_Data*, Student_Data*);
Student_Data *insere_aluno_no_fim_lista(Student_Data*, Student_Data*);
Student_Data *insere_aluno_no_topo_lista(Student_Data*, Student_Data*);
Student_Data *remove_aluno_da_lista(Student_Data*, char*);
void print_lista(Student_Data*);
void free_list(Student_Data*);
Student_Data *ordena_lista(Student_Data *);
Student_Data *troca(Student_Data*, Student_Data*);

int main()
{
    Student_Data *ListHead = NULL, *NewStudent;
    char DelStd[10];
    int NAlunos = 10, i;

    printf("Size of Notas: %ld bytes\nSize of Student_Data: %ld bytes\n",sizeof(Notas),sizeof(Student_Data));
    printf("Insira o num. de alunos: ");
    scanf("%d",&NAlunos);
    for(i=0; i<NAlunos; i++)
    {   // cria aluno
        NewStudent = cria_aluno(i);
        // Insere Elemento
        //ListHead = insere_aluno_na_listaordenada(ListHead, NewStudent);
        //ListHead = insere_aluno_no_fim_lista(ListHead, NewStudent);
        ListHead = insere_aluno_no_topo_lista(ListHead, NewStudent);
    }
    // Apresenta Lista
    printf("===== Lista ====\n");
    print_lista(ListHead);
    // Remove Elemento da lista
    sprintf(DelStd,"ISTID_%03d",rand()%NAlunos+1);
    ListHead = remove_aluno_da_lista(ListHead, DelStd);
    printf("===== Lista sem o elemento %s ====\n",DelStd);
    print_lista(ListHead);
    // Ordena Lista
    ListHead = ordena_lista(ListHead);
    printf("===== Lista ordenada ====\n");
    print_lista(ListHead);
    // Liberta Memória
    free_list(ListHead);
    return 0;
}

Student_Data *cria_aluno(int n_aluno)
{
    Student_Data *NewStd;
    Notas *ListaNotas;
    int N_notas, i;
    float soma = 0;

    N_notas = rand()%5+1;
    if ((ListaNotas = (Notas*) calloc(N_notas,sizeof(Notas))) == NULL)
    {
        printf("Erro: Não foi possível alocar o bloco de memória\n");
        exit(EXIT_FAILURE);
    }
    if ((NewStd = (Student_Data*) calloc(1,sizeof(Student_Data))) == NULL)
    {
        printf("Erro: Não foi possível alocar o bloco de memória\n");
        exit(EXIT_FAILURE);
    }
    for(i=0;i<N_notas;i++)
        // Embora fosse possível aqui utilizar um vector de estruturas é intencional
        //a criação de uma lista para ilustrar a manipulação de lista de listas
    {
        (ListaNotas+i)->Nota = rand()%1000/100.0+10;
        soma += (ListaNotas+i)->Nota;
        if (i!=(N_notas-1))
            (ListaNotas+i)->nextN = ListaNotas+i+1;
        else
            (ListaNotas+i)->nextN = NULL;
    }
    NewStd->nextN = ListaNotas;
    sprintf(NewStd->ID,"ISTID_%03d",n_aluno+1);
    NewStd->NF = soma/N_notas;
    NewStd->nextS = NULL;
    return NewStd;
}

void print_lista(Student_Data *ListHead)
{
    Student_Data *Aux;
    Notas *Aux_N;

    for( Aux = ListHead; Aux != NULL; Aux = Aux->nextS)
    {
        printf("%s %.2f -> ",Aux->ID,Aux->NF);
        for( Aux_N = Aux->nextN; Aux_N != NULL; Aux_N = Aux_N->nextN)
            printf("%.2f ",Aux_N->Nota);
        printf("\n");
    }
}

void free_list(Student_Data *ListHead)
{
    Student_Data *Aux;

    Aux = ListHead;
    while( ListHead != NULL)
    {
        Aux = ListHead;
        ListHead = ListHead->nextS;
        free(Aux->nextN);
        free(Aux);
    }
}

Student_Data *ordena_lista(Student_Data *ListHead)
{
    int trocas = 1;
    Student_Data *left, *right, *head, aux_struct;

    head = &aux_struct;
    head->nextS = ListHead;
    if ((ListHead != NULL ) && ((ListHead->nextS != NULL )))
    {
        while(trocas)
        {
            trocas = 0;
            left = head;
            right = head->nextS;
            while(right->nextS != NULL)
            {
                if (right->NF < right->nextS->NF)
                {
                    left->nextS = troca(right,right->nextS);
                    trocas = 1;
                }
                left = right;
                if (right->nextS != NULL)
                    right = right->nextS;
            }
        }
    }
    ListHead = head->nextS;
    return ListHead;
}

Student_Data *troca(Student_Data *left,Student_Data *right)
{
    left->nextS = right->nextS;
    right->nextS = left;
    return right;
}

Student_Data *insere_aluno_na_listaordenada(Student_Data *ListHead, Student_Data *NewStudent)
{
        Student_Data *AuxH, *AuxT;

        if(ListHead == NULL)
        {
            ListHead = NewStudent;
        }
        else
        {
            if (ListHead->NF < NewStudent->NF)
            {
                NewStudent->nextS = ListHead;
                ListHead = NewStudent;
            }
            else
                {
                    AuxH = ListHead;
                    AuxT = ListHead->nextS;
                    if (AuxT == NULL)
                    {
                        ListHead->nextS = NewStudent;
                    }
                    else
                    {
                        while((AuxT != NULL) && (AuxT->NF > NewStudent->NF))
                        {
                            AuxH = AuxT;
                            AuxT = AuxT->nextS;
                        }
                        NewStudent->nextS = AuxT;
                        AuxH->nextS = NewStudent;
                    }
                }
        }
        return ListHead;
}

Student_Data *insere_aluno_no_fim_lista(Student_Data *ListHead, Student_Data *NewStudent)
{
        Student_Data *AuxH, *AuxT;

        if(ListHead == NULL)
        {
            ListHead = NewStudent;
        }
        else
        {
            AuxH = ListHead;
            AuxT = ListHead->nextS;
            while(AuxT != NULL)
            {
                AuxH = AuxT;
                AuxT = AuxT->nextS;
            }
            AuxH->nextS = NewStudent;
        }
        return ListHead;
}

Student_Data *insere_aluno_no_topo_lista(Student_Data *ListHead, Student_Data *NewStudent)
{
        if(ListHead == NULL)
        {
            ListHead = NewStudent;
        }
        else
        {
            NewStudent->nextS = ListHead;
            ListHead = NewStudent;
        }
        return ListHead;
}

Student_Data *remove_aluno_da_lista(Student_Data *ListHead, char *DelStd)
{
    Student_Data *AuxH, *AuxT;

    AuxH = ListHead;
    AuxT = ListHead->nextS;
    if (strcmp(AuxH->ID, DelStd) == 0)
    {
        ListHead = ListHead->nextS;
        free(AuxH->nextN);
        free(AuxH);
    }
    else
    {
        while(strcmp(AuxT->ID, DelStd) != 0)
        {
            AuxH = AuxT;
            AuxT = AuxT->nextS;
        }
        AuxH->nextS = AuxT->nextS;
        free(AuxT->nextN);
        free(AuxT);
    }
    return ListHead;
}

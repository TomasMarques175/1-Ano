#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Data{
    char    Student_ID[20];
    float   Nota_Final;
} Data; // Estrutura de Dados

typedef struct _DLLNode{
    Data    D;
    struct  _DLLNode *prev;
    struct  _DLLNode *next;
} DLLNode; // Doubly Linked List Node

DLLNode *cria_aluno(int);
DLLNode *insere_aluno_na_listaordenada(DLLNode*, DLLNode*);
DLLNode *insere_no_fim_lista(DLLNode*, DLLNode*);
DLLNode *insere_no_topo_lista(DLLNode*, DLLNode*);
DLLNode *remove_aluno_da_lista(DLLNode*, char*);
DLLNode *remove_do_fim_lista(DLLNode*);
DLLNode *remove_do_topo_lista(DLLNode*);
void print_lista(DLLNode*);
void free_list(DLLNode*);

int main()
{
    DLLNode *ListHead = NULL, *NewStudent;
    char DelStd[10];
    int NAlunos = 10000, i;

    printf("Insira o num. de alunos: ");
    scanf("%d",&NAlunos);
    for(i=0; i<NAlunos; i++)
    {   // cria aluno
        NewStudent = cria_aluno(i);
        // Insere Elemento
        ListHead = insere_aluno_na_listaordenada(ListHead, NewStudent);
        //ListHead = insere_no_fim_lista(ListHead, NewStudent);
        //ListHead = insere_no_topo_lista(ListHead, NewStudent);
    }
    // Apresenta Lista
    printf("===== Lista ====\n");
    print_lista(ListHead);
    // Remove Elemento da lista
    sprintf(DelStd,"ISTID_%03d",rand()%NAlunos+1);
    ListHead = remove_aluno_da_lista(ListHead, DelStd);
    printf("===== Lista sem o elemento %s ====\n",DelStd);
    print_lista(ListHead);
    ListHead = remove_do_fim_lista(ListHead);
    ListHead = remove_do_topo_lista(ListHead);
    printf("===== Lista sem el. topo e fim ====\n");
    print_lista(ListHead);
    // Liberta Memória
    free_list(ListHead);
    return 0;
}

DLLNode *cria_aluno(int i)
{
    DLLNode *NewStd;

    if ((NewStd = (DLLNode*) calloc(1,sizeof(DLLNode))) == NULL)
    {
        printf("Erro: Não foi possível alocar o bloco de memória\n");
        exit(EXIT_FAILURE);
    }
    sprintf(NewStd->D.Student_ID,"ISTID_%03d",i+1);
    NewStd->D.Nota_Final = rand()%1000/100.0+10;
    NewStd->prev = NULL;
    NewStd->next = NULL;
    printf("%s %.2f\n",NewStd->D.Student_ID,NewStd->D.Nota_Final);
    return NewStd;
}

void print_lista(DLLNode *ListHead)
{
    DLLNode *Aux;

    for( Aux = ListHead; Aux != NULL; Aux = Aux->next)
    {
        printf("%s %.2f\n",Aux->D.Student_ID,Aux->D.Nota_Final);
    }
}

void free_list(DLLNode *ListHead)
{
    DLLNode *Aux;

    Aux = ListHead;
    while( ListHead != NULL)
    {
        Aux = ListHead;
        ListHead = ListHead->next;
        free(Aux);
    }
}

DLLNode *insere_aluno_na_listaordenada(DLLNode *ListHead, DLLNode *NewStudent)
{
    DLLNode *Aux;

    if(ListHead == NULL)
        ListHead = NewStudent;
    else
    {   // 1º elemento
        if (ListHead->D.Nota_Final < NewStudent->D.Nota_Final)
        {
            NewStudent->next = ListHead;
            ListHead->prev = NewStudent;
            ListHead = NewStudent;
        }
        else
        {
            Aux = ListHead;
            while((Aux->next != NULL) && (Aux->D.Nota_Final >= NewStudent->D.Nota_Final))
                Aux = Aux->next;
            if (Aux->D.Nota_Final >= NewStudent->D.Nota_Final) // Último Elemento
            {
                Aux->next = NewStudent;
                NewStudent->prev = Aux;
            }
            else // Elemento do meio
            {
                NewStudent->next = Aux;
                NewStudent->prev = Aux->prev;
                Aux->prev->next = NewStudent;
                Aux->prev = NewStudent;
            }
        }
    }
    return ListHead;
}

DLLNode *insere_no_fim_lista(DLLNode *ListHead, DLLNode *NewStudent)
{
        DLLNode *Aux;

        if(ListHead == NULL)
            ListHead = NewStudent;
        else
        {
            Aux = ListHead;
            while(Aux->next != NULL)
                Aux = Aux->next;
            Aux->next = NewStudent;
            NewStudent->prev = Aux;
        }
        return ListHead;
}

DLLNode *insere_no_topo_lista(DLLNode *ListHead, DLLNode *NewStudent)
{
        if(ListHead == NULL)
            ListHead = NewStudent;
        else
        {
            NewStudent->next = ListHead;
            ListHead->prev = NewStudent;
            ListHead = NewStudent;
        }
        return ListHead;
}

DLLNode *remove_aluno_da_lista(DLLNode *ListHead, char *DelStd)
{
    DLLNode *Aux;

    Aux = ListHead;
    while(strcmp(Aux->D.Student_ID, DelStd) != 0)
        Aux = Aux->next;
    if (Aux->prev != NULL)  // Elemento 2 a N
        (Aux->prev)->next = Aux->next;
    if (Aux->next != NULL)  // Elemento 1 a N-1
        (Aux->next)->prev = Aux->prev;
    if (Aux == ListHead)    // 1º Elemento
        ListHead = Aux->next;
    free(Aux);
    return ListHead;
}

DLLNode *remove_do_fim_lista(DLLNode *ListHead)
{
    DLLNode *Aux;

    if (ListHead == NULL)
        return ListHead;
    Aux = ListHead;
    while(Aux->next != NULL)
        Aux = Aux->next;
    if (Aux->prev != NULL)  // Elemento 2 a N
        (Aux->prev)->next = Aux->next;
    if (Aux == ListHead)    // 1º Elemento
        ListHead = NULL;
    free(Aux);
    return ListHead;
}

DLLNode *remove_do_topo_lista(DLLNode *ListHead)
{
    DLLNode *Aux;

    if (ListHead == NULL)
        return ListHead;
    Aux = ListHead;
    if (ListHead->next == NULL)
        ListHead = NULL;
    else
    {
        ListHead = ListHead->next;
        ListHead->prev = NULL;
    }
    free(Aux);
    return ListHead;
}

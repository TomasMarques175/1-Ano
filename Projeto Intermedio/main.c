//Trabalho realizado por:
//Francisco Borges nº 99975 MEEC
//Tomás Marques nº 100104 MEEC

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>

void help() // quando o utilizador escolhe a opção h ou insere opções inválidas é lhe fornecido uma lista com as intruções de jogo
    {
    printf("%s", "Instruções:\n\n-t\tdimensões do tabuleiro, deverá ser apresentada linhaxcoluna (ex: -t 9x9)\n-j x\tmodo de jogo, x varia de 0 a 2 (ex: -j 1)\n-p x\tmodo de posicionamento das peças, x varia de 1 a 2 (ex:-p 1)\n-d x\tmodo de disparo de peças pelo computador, x varia de 1 a 3 (ex:-d 3)\n-1 x\tnúmero de peças tipo 1, x varia de 1 a 8\n-2 x\tnúmero de peças tipo 2, x varia de 0 a 8\n-3 x\tnúmero de peças tipo 3, x varia de 0 a 8\n-4 x\tnúmero de peças tipo 4, x varia de 0 a 8\n-5 x\tnúmero de peças tipo 5, x varia de 0 a 8\n-6 x\tnúmero de peças tipo 6, x varia de 0 a 8\n-7 x\tnúmero de peças tipo 7, x varia de 0 a 8\n-8 x\tnúmero de peças tipo 8, x varia de 0 a 8\n\nOpções de -j:\n-j 0\to programa gera o tabuleiro sozinho de acordo com o modo de posicionamento referido\n-j 1\tjogador tenta acertar as peças colocadas pelo computador dependo do modo de posicionamento referido\n-j 2\to computador tenta acertar nas posições definidas pelo jogador dependo do modo de disparo\n\nOpções de -p:\n-p 1\tO computador coloca peças de tipo e variante aleatória no tabuleiro\n-p 2\tFornecidos o número, tipo de peças a posicionar e a dimensão do tabuleiro pelo jogador, o computador coloca as peças aleatoriamente\n\nOpções de -d:\n-d 1\tEscolhe aleatoriamente as coordenas de disparo, sem que haja tiros repetidos\n-d 2\tPrimeiro tiro na célula central da primeira matriz 3x3, seguindo depois uma sequência de tiros dentro dessa matriz definida pelo código\n-d 3\tIgual a -d 2 com a diferença que reduz os tiros efetuados pois a medida que vai descobrindo os navios, elimina todos os quadrados a volta do “barco”\n\nOpções de -1, -2, -3, -4, -5, -6, -7, -8:\nA não especificação de algum tipo de peças é assumida como “0”");
    }

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int i=0, j=0, k=0, l=0, m=0;       //constantes sem significado proprio a que foram recorridas para auxilio
    int num_linhas = 9,                //inicializado a 9 como pre defenição para um tabuleiro minimo 9x9
        num_colunas =9;                //inicializado a 9 como pre defenição para um tabuleiro minimo 9x9
    int board[15][24];                 //tabuleiro com dimensao maxima 15x24
    int num_pecas[9];                  //array responsável por armazenar o numero de pecas de cada tipo
    char Letras[27]={ ' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    int Peca[43][3][3]={    //43 pecas defenidas em matrizes 3x3 incluindo a matriz nula
                                                // Matriz Nula
                                                    {{0,0,0},
                                                     {0,0,0},
                                                     {0,0,0}},
                                                // Variantes da peça 1
                                                    {{1,0,0},
                                                     {0,0,0},
                                                     {0,0,0}},

                                                    {{0,1,0},
                                                     {0,0,0},
                                                     {0,0,0}},

                                                    {{0,0,1},
                                                     {0,0,0},
                                                     {0,0,0}},

                                                    {{0,0,0},
                                                     {1,0,0},
                                                     {0,0,0}},

                                                    {{0,0,0},
                                                     {0,1,0},
                                                     {0,0,0}},

                                                    {{0,0,0},
                                                     {0,0,1},
                                                     {0,0,0}},

                                                    {{0,0,0},
                                                     {0,0,0},
                                                     {1,0,0}},

                                                    {{0,0,0},
                                                     {0,0,0},
                                                     {0,1,0}},

                                                    {{0,0,0},
                                                     {0,0,0},
                                                     {0,0,1}},
                                                // Variantes da peça 2
                                                    {{2,2,0},
                                                     {0,0,0},
                                                     {0,0,0}},

                                                    {{0,2,2},
                                                     {0,0,0},
                                                     {0,0,0}},

                                                    {{0,0,0},
                                                     {2,2,0},
                                                     {0,0,0}},

                                                    {{0,0,0},
                                                     {0,2,2},
                                                     {0,0,0}},

                                                    {{0,0,0},
                                                     {0,0,0},
                                                     {2,2,0}},

                                                    {{0,0,0},
                                                     {0,0,0},
                                                     {0,2,2}},

                                                    {{2,0,0},
                                                     {2,0,0},
                                                     {0,0,0}},

                                                    {{0,0,0},
                                                     {2,0,0},
                                                     {2,0,0}},

                                                    {{0,2,0},
                                                     {0,2,0},
                                                     {0,0,0}},

                                                    {{0,0,0},
                                                     {0,2,0},
                                                     {0,2,0}},

                                                    {{0,0,2},
                                                     {0,0,2},
                                                     {0,0,0}},

                                                    {{0,0,0},
                                                     {0,0,2},
                                                     {0,0,2}},
                                                // Variantes da peça 3
                                                    {{3,3,3},
                                                     {0,0,0},
                                                     {0,0,0}},

                                                    {{0,0,0},
                                                     {3,3,3},
                                                     {0,0,0}},

                                                    {{0,0,0},
                                                     {0,0,0},
                                                     {3,3,3}},

                                                    {{3,0,0},
                                                     {3,0,0},
                                                     {3,0,0}},

                                                    {{0,3,0},
                                                     {0,3,0},
                                                     {0,3,0}},

                                                    {{0,0,3},
                                                     {0,0,3},
                                                     {0,0,3}},
                                                // Variantes da peça 4
                                                    {{4,4,0},
                                                     {4,4,0},
                                                     {0,0,0}},

                                                    {{0,4,4},
                                                     {0,4,4},
                                                     {0,0,0}},

                                                    {{0,0,0},
                                                     {4,4,0},
                                                     {4,4,0}},

                                                    {{0,0,0},
                                                     {0,4,4},
                                                     {0,4,4}},
                                                // Variantes da peça 5
                                                    {{5,5,5},
                                                     {0,5,0},
                                                     {0,5,0}},

                                                    {{5,0,0},
                                                     {5,5,5},
                                                     {5,0,0}},

                                                    {{0,5,0},
                                                     {0,5,0},
                                                     {5,5,5}},

                                                    {{0,0,5},
                                                     {5,5,5},
                                                     {0,0,5}},
                                                // Variantes da peça 6
                                                    {{0,6,0},
                                                     {6,0,6},
                                                     {6,6,6}},

                                                    {{0,6,6},
                                                     {6,0,6},
                                                     {0,6,6}},

                                                    {{6,6,6},
                                                     {6,0,6},
                                                     {0,6,0}},

                                                    {{6,6,0},
                                                     {6,0,6},
                                                     {6,6,0}},
                                                // Variantes da peça 7
                                                    {{7,7,7},
                                                     {0,7,0},
                                                     {7,7,7}},

                                                    {{7,0,7},
                                                     {7,7,7},
                                                     {7,0,7}},
                                                // Variante da peça 8
                                                    {{8,8,8},
                                                     {8,0,8},
                                                     {8,8,8}}
                                                };
    int option,
        modo_jogo = 0,                 //inicializado a 0 pois é o modo default de jogo
        modo_de_posicionamento = 1,    //inicializado a 1 pois é o modo default de jogo
        modo_de_disparo = 1,           //inicializado a 1 pois é o modo default de jogo
        num_totalpecas=0,
        num_total_posicoes=0,
        jogadas = 0,
        acertos = 0;
        num_pecas[1] = 1;              //numero minimo de pecas do tipo 1 é 0
        num_pecas[2] = 0;              //inicializado a 0 pois nao tem numero minimo de pecas
        num_pecas[3] = 0;              //inicializado a 0 pois nao tem numero minimo de pecas
        num_pecas[4] = 0;              //inicializado a 0 pois nao tem numero minimo de pecas
        num_pecas[5] = 0;              //inicializado a 0 pois nao tem numero minimo de pecas
        num_pecas[6] = 0;              //inicializado a 0 pois nao tem numero minimo de pecas
        num_pecas[7] = 0;              //inicializado a 0 pois nao tem numero minimo de pecas
        num_pecas[8] = 0;              //inicializado a 0 pois nao tem numero minimo de pecas

        opterr= 0; //utilizado com o objetivo de o getopt() não gerar erros quando inseridas opcoes invalidas

    while ((option = getopt(argc, argv, "ht:j:p:d:1:2:3:4:5:6:7:8:")) != -1)
        {
            switch(option)
            {
                case 'h':
                    help();/* envia as instruções de jogo */
                    break;
                case 't': /* dimensoes do tabuleiro */
                    sscanf(optarg, "%d""%c""%d", &num_linhas,&Letras[24],&num_colunas); /* se houver erro, fica o valor por omissão */
                    break;
                case 'j': /* modo de jogo */
                    sscanf(optarg, "%d", &modo_jogo); /* se houver erro, fica o valor por omissão */
                    break;
                case 'p': /* modo de posicionamento */
                    sscanf(optarg, "%d", &modo_de_posicionamento); /* se houver erro, fica o valor por omissão */
                    break;
                case 'd': /* modo de disparo */
                    sscanf(optarg, "%d", &modo_de_disparo); /* se houver erro, fica o valor por omissão */
                    break;
                case '1': /* numero de pecas do tipo 1 */
                    sscanf(optarg, "%d", &num_pecas[1]); /* se houver erro, fica o valor por omissão */
                    break;
                case '2': /* numero de pecas do tipo 2 */
                    sscanf(optarg, "%d", &num_pecas[2]); /* se houver erro, fica o valor por omissão */
                    break;
                case '3': /* numero de pecas do tipo 3 */
                    sscanf(optarg, "%d", &num_pecas[3]); /* se houver erro, fica o valor por omissão */
                    break;
                case '4': /* numero de pecas do tipo 4 */
                    sscanf(optarg, "%d", &num_pecas[4]); /* se houver erro, fica o valor por omissão */
                    break;
                case '5': /* numero de pecas do tipo 5 */
                    sscanf(optarg, "%d", &num_pecas[5]); /* se houver erro, fica o valor por omissão */
                    break;
                case '6': /* numero de pecas do tipo 6 */
                    sscanf(optarg, "%d", &num_pecas[6]); /* se houver erro, fica o valor por omissão */
                    break;
                case '7': /* numero de pecas do tipo 7 */
                    sscanf(optarg, "%d", &num_pecas[7]); /* se houver erro, fica o valor por omissão */
                    break;
                case '8': /* numero de pecas do tipo 8 */
                    sscanf(optarg, "%d", &num_pecas[8]); /* se houver erro, fica o valor por omissão */
                    break;
                default: /* se forem inseridas opções inválidas o programa mostra as instruções ao utilizador */
                    help();
                    return -1;

            }
        }


    num_totalpecas = (num_pecas[1] + num_pecas[2] + num_pecas[3] + num_pecas[4] + num_pecas[5] + num_pecas[6] + num_pecas[7] + num_pecas[8]);                               //define o numero total de pecas que o utilizador quer colocar
    num_total_posicoes = (num_pecas[1] + num_pecas[2]*2 + num_pecas[3]*3 + num_pecas[4]*4 + num_pecas[5]*5 + num_pecas[6]*6 + num_pecas[7]*7 + num_pecas[8]*8);             //define o numero total de posicoes ocupadas pelas pecas que o utilizador escolheu colocar

/////////////////////////////////////INICIO DO JOGO/////////////////////////////////////////////////////////
    printf("* Modo de Jogo %d \n", modo_jogo);                                                                                                                              //indica o modo de jogo consoante o que é defenido pelo utilizador com recurso à flag j
    printf("%d""%c""%d", num_linhas, Letras[24], num_colunas);                                                                                                              //indica as dimensoes do tabuleiro
    printf(" %d"" %d"" %d"" %d"" %d"" %d"" %d"" %d\n", num_pecas[1], num_pecas[2], num_pecas[3], num_pecas[4], num_pecas[5], num_pecas[6], num_pecas[7], num_pecas[8]);     //indica o numero de pecas de cada tipo por ordem desde o tipo 1 ao tipo 8
////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////função responsável por criar o tabuleiro sem pecas com as dimensões escolhidas pelo utilizador
    for(i = 0 ; i < num_linhas; i++)
    {
        for(j = 0; j < num_colunas; j++)
        {
            board[i][j]= 0;
        }
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////função responsável por posicionar as peças aleatoriamente no tabuleiro de acordo com o modo de jogo atribuido pelo utilizador//

//////Modo de Jogo 0
    if(modo_jogo == 0)
    {
            if(modo_de_posicionamento == 1)
                {
                //modo de posicionamento 1//sem a restrição 1//imprime as peças da esquerda para a direita começando sempre no inicio de cada linhas e em matrizes 3 por 3
                for (k = 0; k < num_linhas;k+=3)
                    {
                        for (l = 0; l < num_colunas; l+=3)
                        {
                            int RAND_NUM,                                 //número a que corresponde uma peça
                                num_minpecas=0,                           //número minimo da peça
                                num_maxpecas=42;                          //número maximo da peça

                            RAND_NUM = (rand() % (num_maxpecas - num_minpecas + 1)) + num_minpecas;    // é gerado um número aleatório para a peça a posicionar no tabuleiro dentro das possibilidades das peças previamente defenidas em matrizes 3x3

                                    for (i = 0; i < 3; i++)
                                    {
                                        for (j = 0; j < 3; j++)
                                        {
                                        board[i + k][j + l] = Peca[RAND_NUM][i][j];
                                        }
                                    }
                        }
                    }

            }else if(modo_de_posicionamento == 2)
                {
                     if(num_totalpecas*9 > num_linhas*num_colunas)      //se o numero total de pecas for maior que o (numero de linha da matriz * o numero de colunas da matriz)/9 são mostradas ao utilizador as intruções de jogo e retornado um valor de erro -1
                        {
                        help();
                        return -1;
                     }else if(num_pecas[8]<=num_pecas[7] && num_pecas[7]<=num_pecas[6]  && num_pecas[6]<=num_pecas[5] && num_pecas[5]<=num_pecas[4] && num_pecas[4]<=num_pecas[3] && num_pecas[3]<=num_pecas[2] && num_pecas[2]<=num_pecas[1])  //se um numero de pecas de um tipo de maior dimensão for maior que um de menor dimensão são mostradas ao utilizador as intruções de jogo e retornado um valor de erro -1
                        {
                    //modo de posicionamento 2//sem a restrição 1

                                int pecas[num_totalpecas];          //array com a função de armazenar as pecas que o jogador escolheu


                                ////////////////função responsável por guardar por tipo de peca as pecas escolhidas pelo jogador//no caso do jogador escolher 3 pecas do tipo 1 as mesmas são armazenadas individualmente como 3 uns dentro do array
                                for(i=0; i<num_pecas[0]; i++)
                                {
                                    pecas[i]= 1;
                                }
                                for(i=0; i<num_pecas[1]; i++)
                                {
                                    pecas[i+num_pecas[0]]= 2;
                                }
                                for(i=0; i<num_pecas[2]; i++)
                                {
                                    pecas[i+num_pecas[0]+num_pecas[1]]= 3;
                                }
                                for(i=0; i<num_pecas[3]; i++)
                                {
                                    pecas[i+num_pecas[0]+num_pecas[1]+num_pecas[2]]= 4;
                                }
                                for(i=0; i<num_pecas[4]; i++)
                                {
                                    pecas[i+num_pecas[0]+num_pecas[1]+num_pecas[2]+num_pecas[3]]= 5;
                                }
                                for(i=0; i<num_pecas[5]; i++)
                                {
                                    pecas[i+num_pecas[0]+num_pecas[1]+num_pecas[2]+num_pecas[3]+num_pecas[4]]= 6;
                                }
                                for(i=0; i<num_pecas[6]; i++)
                                {
                                    pecas[i+num_pecas[0]+num_pecas[1]+num_pecas[2]+num_pecas[3]+num_pecas[4]+num_pecas[5]]= 7;
                                }
                                for(i=0; i<num_pecas[7]; i++)
                                {
                                    pecas[i+num_pecas[0]+num_pecas[1]+num_pecas[2]+num_pecas[3]+num_pecas[4]+num_pecas[5]+num_pecas[6]]= 8;
                                }
                                /////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                /////função responsável por agarrar nas pecas armazenada e trocar a sua ordem para uma ordem aleatoria dentro do array

                                for(i=0;i<num_totalpecas;i++)
                                    {
                                    int temp;               //constante utilizada para misturar os valores metidos no array pecas
                                    j = (rand()%num_totalpecas)+1;

                                    temp = pecas[i];
                                    pecas[i] = pecas[j];
                                    pecas[j] = temp;
                                    }
                                /////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                // São posicionadas de forma aleatória peças dos tipos escolhidos pelo jogador
                                    for (k = 0; k < num_linhas;k+=3)
                                    {
                                        for (l = 0; l < num_colunas; l+=3)
                                        {
                                                int RAND_NUM ,num_minpecas=0 ,num_maxpecas=num_totalpecas;

                                                RAND_NUM= pecas[i];
                                                pecas[i]=0;

                                                i = (rand() % (num_maxpecas - num_minpecas + 1)) + num_minpecas;
                                                RAND_NUM= pecas[i];

                                                //////consoante o tipo de peca escolhido pelo utilizador é eleita de forma aleatória uma variante dessa mesma peca
                                                    if(RAND_NUM == 1)
                                                    {
                                                        int RAND_NUM ,num_minpecas=1 ,num_maxpecas=9;
                                                        RAND_NUM = (rand() % (num_maxpecas - num_minpecas + 1)) + num_minpecas;
                                                        for (i = 0; i < 3; i++)
                                                            {
                                                                for (j = 0; j < 3; j++)
                                                                {
                                                                    board[i + k][j + l] = Peca[RAND_NUM][i][j];
                                                                }
                                                            }
                                                    }else if(RAND_NUM == 2)
                                                        {
                                                        int RAND_NUM ,num_minpecas=10 ,num_maxpecas=21;
                                                        RAND_NUM = (rand() % (num_maxpecas - num_minpecas + 1)) + num_minpecas;
                                                        for (i = 0; i < 3; i++)
                                                            {
                                                                for (j = 0; j < 3; j++)
                                                                {
                                                                    board[i + k][j + l] = Peca[RAND_NUM][i][j];
                                                                }
                                                            }
                                                    }else if(RAND_NUM == 3)
                                                        {
                                                        int RAND_NUM ,num_minpecas=22 ,num_maxpecas=27;
                                                        RAND_NUM = (rand() % (num_maxpecas - num_minpecas + 1)) + num_minpecas;
                                                        for (i = 0; i < 3; i++)
                                                            {
                                                                for (j = 0; j < 3; j++)
                                                                {
                                                                    board[i + k][j + l] = Peca[RAND_NUM][i][j];
                                                                }
                                                            }
                                                    }else if(RAND_NUM == 4)
                                                        {
                                                        int RAND_NUM ,num_minpecas=28 ,num_maxpecas=31;
                                                        RAND_NUM = (rand() % (num_maxpecas - num_minpecas + 1)) + num_minpecas;
                                                        for (i = 0; i < 3; i++)
                                                            {
                                                                for (j = 0; j < 3; j++)
                                                                {
                                                                    board[i + k][j + l] = Peca[RAND_NUM][i][j];
                                                                }
                                                            }
                                                    }else if(RAND_NUM == 5)
                                                        {
                                                        int RAND_NUM ,num_minpecas=32 ,num_maxpecas=35;
                                                        RAND_NUM = (rand() % (num_maxpecas - num_minpecas + 1)) + num_minpecas;
                                                        for (i = 0; i < 3; i++)
                                                            {
                                                                for (j = 0; j < 3; j++)
                                                                {
                                                                    board[i + k][j + l] = Peca[RAND_NUM][i][j];
                                                                }
                                                            }
                                                    }else if(RAND_NUM == 6)
                                                        {
                                                        int RAND_NUM ,num_minpecas=36 ,num_maxpecas=39;
                                                        RAND_NUM = (rand() % (num_maxpecas - num_minpecas + 1)) + num_minpecas;
                                                        for (i = 0; i < 3; i++)
                                                            {
                                                                for (j = 0; j < 3; j++)
                                                                {
                                                                    board[i + k][j + l] = Peca[RAND_NUM][i][j];
                                                                }
                                                            }
                                                    }else if(RAND_NUM == 7)
                                                        {
                                                        int RAND_NUM ,num_minpecas=40 ,num_maxpecas=41;
                                                        RAND_NUM = (rand() % (num_maxpecas - num_minpecas + 1)) + num_minpecas;
                                                        for (i = 0; i < 3; i++)
                                                            {
                                                                for (j = 0; j < 3; j++)
                                                                {
                                                                    board[i + k][j + l] = Peca[RAND_NUM][i][j];
                                                                }
                                                            }
                                                    }else if(RAND_NUM == 8)
                                                        {
                                                        int RAND_NUM = 42;
                                                            for (i = 0; i < 3; i++)
                                                            {
                                                                for (j = 0; j < 3; j++)
                                                                {
                                                                    board[i + k][j + l] = Peca[RAND_NUM][i][j];
                                                                }
                                                            }
                                                        }
                                                ////////////////////////////////////////////////////////////////
                                        }
                                    }
                        //////Fim do modo de posicionamento 2/////
                        }else
                            {
                            help();
                            return -1;
                            }
            }else if(modo_de_posicionamento != 1 && modo_de_posicionamento != 2)    //se o modo de posicionamento escolhido for diferente dos modos existentes são mostradas ao utilizador as intruções de jogo e retornado um valor de erro -1
                {
                help();
                return -1;
                }

////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////Modo de Jogo 1
    }else if(modo_jogo == 1)
    {
            if(modo_de_posicionamento == 1)
                {
            //modo de posicionamento 1//sem a restrição 1//imprime as peças da esquerda para a direita começando sempre no inicio de cada linha e em matrizes 3 por 3

                        for (k = 0; k < num_linhas;k+=3)
                        {
                            for (l = 0; l < num_colunas; l+=3)
                            {
                                int RAND_NUM,                             //número a que corresponde uma peça
                                num_minpecas=0,                           //número minimo da peça
                                num_maxpecas=42;                          //número maximo da peça

                                RAND_NUM = (rand() % (num_maxpecas - num_minpecas + 1)) + num_minpecas;    // é gerado um número aleatório para a peça a posicionar no tabuleiro dentro das possibilidades das peças previamente defenidas em matrizes 3x3

                                        for (i = 0; i < 3; i++)
                                        {
                                            for (j = 0; j < 3; j++)
                                            {
                                            board[i + k][j + l] = Peca[RAND_NUM][i][j];
                                            }
                                        }
                            }
                        }
                        if(modo_de_disparo == 2 || modo_de_disparo == 3)                                        //se o jogador escolher um modo de disparo diferente de 1 são mostradas ao jogador as intruções de jogo e retornado um valor de erro -1
                        {
                            help();
                            return -1;
                        }else
                            {
                                while(acertos != num_total_posicoes || jogadas != (num_colunas*num_linhas))    //enquanto o jogador não acertar em todas as peças do barco ou em todas as opções possiveis continua a jogar
                                    {

                                        char letra_coluna;                                                      //local onde será colocada a coluna do disparo
                                        int coordenada_linha;                                                   //local onde será colocada a linha do disparo
                                        int coordenada_coluna;                                                  //local onde será colocada a coluna do disparo num numero representativo da letra da coluna

                                            scanf(" %c", &letra_coluna);                                        // Recebe do jogador o valor da coordenada da colunas no formato de uma letra maiuscula
                                            scanf(" %d", &coordenada_linha);                                    // Recebe do jogador o valor da coordenada da linha

                                            coordenada_coluna=letra_coluna-64;                                  // converte a letra fornecida para a coordenada da coluna num numero de 0 a 26

                                                if(board[coordenada_linha][coordenada_coluna] == 0)             // se a posição escolhida pelo jogador não for um barco é impresso o caracter '-' como forma de indicar ao jogador que acertou na água e não num barco, sendo tambem incrementado 1 ao numero de tentativas do jogador
                                                    {
                                                    printf("-\n");
                                                    jogadas++;
                                                }else{                                                          // se a posição escolhida pelo jogador for um barco é impresso o numero correspondente ao tipo do barco e incrementa 1 tanto ao contador de acertos como ao numero de jogadas totais
                                                    printf("%d\n", board[coordenada_linha][coordenada_coluna]);
                                                    jogadas++;
                                                    acertos++;
                                                }
                                    }
                                printf("Fim de Jogo: %d jogadas em %u segundos\n", jogadas,clock()/CLOCKS_PER_SEC);//no final do jogo indica o numero de jogadas realizadas e o numero de segundos que o jogador demorou até acabar o jogo
                            }
            }else if(modo_de_posicionamento != 1)   //se o modo de posicionamento escolhido for diferente dos modos existentes são mostradas ao utilizador as intruções de jogo e retornado um valor de erro -1
                    {
                    help();
                    return -1;
                    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////Modo de Jogo 2
    }else if(modo_jogo == 2)
    {
            if(modo_de_posicionamento == 2)
                {
                     if(num_totalpecas*9 > num_linhas*num_colunas)                                                                      //se o numero total de pecas for maior que o (numero de linha da matriz * o numero de colunas da matriz)/9 são mostradas ao utilizador as intruções de jogo e retornado um valor de erro -1
                        {
                        help();
                        return -1;
                     }else if(num_pecas[8]<=num_pecas[7] && num_pecas[7]<=num_pecas[6]  && num_pecas[6]<=num_pecas[5] && num_pecas[5]<=num_pecas[4] && num_pecas[4]<=num_pecas[3] && num_pecas[3]<=num_pecas[2] && num_pecas[2]<=num_pecas[1])  //se um numero de pecas de um tipo de maior dimensão for maior que um de menor dimensão são mostradas ao utilizador as intruções de jogo e retornado um valor de erro -1
                        {
                    //modo de posicionamento 2//sem a restrição 1

                                int pecas[num_totalpecas];          //array com a função de armazenar as pecas que o jogador escolheu


                                ////////////////função responsável por guardar por tipo de peca as pecas escolhidas pelo jogador//no caso do jogador escolher 3 pecas do tipo 1 as mesmas são armazenadas individualmente como 3 uns dentro do array
                                for(i=0; i<num_pecas[0]; i++)
                                {
                                    pecas[i]= 1;
                                }
                                for(i=0; i<num_pecas[1]; i++)
                                {
                                    pecas[i+num_pecas[0]]= 2;
                                }
                                for(i=0; i<num_pecas[2]; i++)
                                {
                                    pecas[i+num_pecas[0]+num_pecas[1]]= 3;
                                }
                                for(i=0; i<num_pecas[3]; i++)
                                {
                                    pecas[i+num_pecas[0]+num_pecas[1]+num_pecas[2]]= 4;
                                }
                                for(i=0; i<num_pecas[4]; i++)
                                {
                                    pecas[i+num_pecas[0]+num_pecas[1]+num_pecas[2]+num_pecas[3]]= 5;
                                }
                                for(i=0; i<num_pecas[5]; i++)
                                {
                                    pecas[i+num_pecas[0]+num_pecas[1]+num_pecas[2]+num_pecas[3]+num_pecas[4]]= 6;
                                }
                                for(i=0; i<num_pecas[6]; i++)
                                {
                                    pecas[i+num_pecas[0]+num_pecas[1]+num_pecas[2]+num_pecas[3]+num_pecas[4]+num_pecas[5]]= 7;
                                }
                                for(i=0; i<num_pecas[7]; i++)
                                {
                                    pecas[i+num_pecas[0]+num_pecas[1]+num_pecas[2]+num_pecas[3]+num_pecas[4]+num_pecas[5]+num_pecas[6]]= 8;
                                }
                                /////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                /////função responsável por agarrar nas pecas armazenada e trocar a sua ordem para uma ordem aleatoria dentro do array

                                for(i=0;i<num_totalpecas;i++)
                                    {
                                    int temp;                   //constante utilizada para misturar os valores metidos no array pecas
                                    j = (rand()%num_totalpecas)+1;

                                    temp = pecas[i];
                                    pecas[i] = pecas[j];
                                    pecas[j] = temp;
                                    }
                                /////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                // São posicionadas de forma aleatória peças dos tipos escolhidos pelo jogador
                                    for (k = 0; k < num_linhas;k+=3)
                                    {
                                        for (l = 0; l < num_colunas; l+=3)
                                        {
                                                int RAND_NUM ,num_minpecas=0 ,num_maxpecas=num_totalpecas;

                                                RAND_NUM= pecas[i];
                                                pecas[i]=0;

                                                i = (rand() % (num_maxpecas - num_minpecas + 1)) + num_minpecas;
                                                RAND_NUM= pecas[i];

                                                //////consoante o tipo de peca escolhido pelo utilizador é eleita de forma aleatória uma variante dessa mesma peca
                                                    if(RAND_NUM == 1)
                                                    {
                                                        int RAND_NUM ,num_minpecas=1 ,num_maxpecas=9;
                                                        RAND_NUM = (rand() % (num_maxpecas - num_minpecas + 1)) + num_minpecas;
                                                        for (i = 0; i < 3; i++)
                                                            {
                                                                for (j = 0; j < 3; j++)
                                                                {
                                                                    board[i + k][j + l] = Peca[RAND_NUM][i][j];
                                                                }
                                                            }
                                                    }else if(RAND_NUM == 2)
                                                        {
                                                        int RAND_NUM ,num_minpecas=10 ,num_maxpecas=21;
                                                        RAND_NUM = (rand() % (num_maxpecas - num_minpecas + 1)) + num_minpecas;
                                                        for (i = 0; i < 3; i++)
                                                            {
                                                                for (j = 0; j < 3; j++)
                                                                {
                                                                    board[i + k][j + l] = Peca[RAND_NUM][i][j];
                                                                }
                                                            }
                                                    }else if(RAND_NUM == 3)
                                                        {
                                                        int RAND_NUM ,num_minpecas=22 ,num_maxpecas=27;
                                                        RAND_NUM = (rand() % (num_maxpecas - num_minpecas + 1)) + num_minpecas;
                                                        for (i = 0; i < 3; i++)
                                                            {
                                                                for (j = 0; j < 3; j++)
                                                                {
                                                                    board[i + k][j + l] = Peca[RAND_NUM][i][j];
                                                                }
                                                            }
                                                    }else if(RAND_NUM == 4)
                                                        {
                                                        int RAND_NUM ,num_minpecas=28 ,num_maxpecas=31;
                                                        RAND_NUM = (rand() % (num_maxpecas - num_minpecas + 1)) + num_minpecas;
                                                        for (i = 0; i < 3; i++)
                                                            {
                                                                for (j = 0; j < 3; j++)
                                                                {
                                                                    board[i + k][j + l] = Peca[RAND_NUM][i][j];
                                                                }
                                                            }
                                                    }else if(RAND_NUM == 5)
                                                        {
                                                        int RAND_NUM ,num_minpecas=32 ,num_maxpecas=35;
                                                        RAND_NUM = (rand() % (num_maxpecas - num_minpecas + 1)) + num_minpecas;
                                                        for (i = 0; i < 3; i++)
                                                            {
                                                                for (j = 0; j < 3; j++)
                                                                {
                                                                    board[i + k][j + l] = Peca[RAND_NUM][i][j];
                                                                }
                                                            }
                                                    }else if(RAND_NUM == 6)
                                                        {
                                                        int RAND_NUM ,num_minpecas=36 ,num_maxpecas=39;
                                                        RAND_NUM = (rand() % (num_maxpecas - num_minpecas + 1)) + num_minpecas;
                                                        for (i = 0; i < 3; i++)
                                                            {
                                                                for (j = 0; j < 3; j++)
                                                                {
                                                                    board[i + k][j + l] = Peca[RAND_NUM][i][j];
                                                                }
                                                            }
                                                    }else if(RAND_NUM == 7)
                                                        {
                                                        int RAND_NUM ,num_minpecas=40 ,num_maxpecas=41;
                                                        RAND_NUM = (rand() % (num_maxpecas - num_minpecas + 1)) + num_minpecas;
                                                        for (i = 0; i < 3; i++)
                                                            {
                                                                for (j = 0; j < 3; j++)
                                                                {
                                                                    board[i + k][j + l] = Peca[RAND_NUM][i][j];
                                                                }
                                                            }
                                                    }else if(RAND_NUM == 8)
                                                        {
                                                        int RAND_NUM = 42;
                                                            for (i = 0; i < 3; i++)
                                                            {
                                                                for (j = 0; j < 3; j++)
                                                                {
                                                                    board[i + k][j + l] = Peca[RAND_NUM][i][j];
                                                                }
                                                            }
                                                        }
                                                ////////////////////////////////////////////////////////////////
                                        }
                                    }
                                    //////Fim do modo de posicionamento 2/////
                                    if(modo_de_disparo == 1 || modo_de_disparo == 2 || modo_de_disparo == 3)
                                    {
                                    //modo de disparo 1
                                        while(acertos != num_total_posicoes || jogadas != (num_colunas*num_linhas))    //enquanto o computador não acertar em todas as peças do barco ou em todas as opções possiveis continua a tentar descobrir
                                            {

                                                int coordenada_linha=0,                                                 //coordenada da linha do disparo
                                                    coordenada_coluna=0;                                                //coordenada da coluna do disparo


                                                int lower = 0,                                                          //valor minimo para ambas as coordenadas
                                                    upperlinhas = num_linhas,                                           //valor maximo da coordenada linha
                                                    uppercolunas = num_colunas;                                         //valor maximo da coordenada coluna


                                                    coordenada_linha = (rand() % (upperlinhas - lower )) + lower;       //coordenada linha será um numero aleatório com valor entre o numero de linhas dos tabuleiro e 0
                                                    coordenada_coluna = (rand() % (uppercolunas - lower )) + lower;     //coordenada coluna será um numero aleatório com valor entre o numero de colunas dos tabuleiro e 0

                                                        if(board[coordenada_linha][coordenada_coluna] == 0)             // se a posição escolhida pelo computador não for um barco é imprimido o caracter '-' como forma de indicar identificar que acertou na água e não num barco, sendo tambem incrementado 1 ao numero de tentativas
                                                            {
                                                            printf("-\n");
                                                            jogadas++;
                                                        }else{                                                          // se a posição escolhida pelo computador for um barco é impresso o numero correspondente ao tipo do barco e incrementa 1 tanto ao contador de acertos como ao numero de jogadas totais
                                                            printf("%d\n", board[coordenada_linha][coordenada_coluna]);
                                                            jogadas++;
                                                            acertos++;
                                                        }
                                            }
                                        printf("Fim de Jogo: %d jogadas em %u segundos\n", jogadas,clock()/CLOCKS_PER_SEC);//no final do jogo indica o numero de jogadas realizadas e o numero de segundos que o computador demorou até descobrir todas as pecas
                                    }else
                                        {
                                        help();
                                        return -1;
                                        }
                        }else
                            {
                            help();
                            return -1;
                            }
            }else if(modo_de_posicionamento != 2)   //se o modo de posicionamento escolhido for diferente dos modos existentes são mostradas ao utilizador as intruções de jogo e retornado um valor de erro -1
                {
                help();
                return -1;
                }

////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////Modo de Jogo nao definido

    }else if(modo_jogo != 0 && modo_jogo != 1 && modo_jogo != 2)    //se o modo de jogo escolhido for diferente dos modos existentes são mostradas ao utilizador as intruções de jogo e retornado um valor de erro -1
        {
        help();
        return -1;
        }

////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////função responsável por imprimir o tabuleiro com as respetivas coordenadas trocando os 0 por '-' e identificando as linhas e colunas com números e letras respetivamente
    m = num_linhas;
    for (i = 0; i < num_linhas; i++)
    {
        printf("%2d ", m);
        for(j=0;j<num_colunas;j++)
            {
                if(board[i][j] == 0)
                    {
                    printf("- ");
                }else if(board[i][j] != 0)
                    {
                    printf("%d ", board[i][j]);
                    }
            }
            printf("\n");
            m--;
    }

    for (j=0;j<num_colunas+1;j++)
    {
        printf("%2c", Letras[j]);
    }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    return 0;
}

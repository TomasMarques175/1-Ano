//======================================================================
// Exemplo de utilização do getopt para opções sem argumentos, com
// argumentos opcionais e com argumentos obrigatórios. 
// Exemplo de leitura de multiplos argumentos para uma opção
// 
// ./a.out -x -y argobrigatorio -z argob 123 2021-05-12 -wargopcional
//======================================================================
#include <stdio.h>
//#include <unistd.h>
#include <getopt.h>

#define LISTA_OPCOES "-:xy:w::z:"
//#define LISTA_OPCOES ":xy:w::z:"

int main(int argc, char *argv[])
{
	int xflag = 0, yflag = 0, wflag = 0, zflag = 0;
	char  *yvalue = NULL, *wvalue = NULL;	
	int index;
	int opt;

	opterr = 0;
	
	//optind - index do próximo elemento a ser processado no argv, inicializado a 1 
	//optopt - guarda o caracter da opção, quando a opcao nao é reconhecida
	//opterr - quando colocado a 0 evita a mensagem de erro
	//optarg - apontador para texto do mesmo argumento
	//optstring - string que contém a descrição das opções
	
	while((opt = getopt(argc, argv, LISTA_OPCOES)) != -1)  
	// -1 quando não há mais opções para processar
	// optstring : para indicar que a opção requer um parametro
	// optstring :: para indicar que o parametro da opção é opcional, o parametro deve estar junto à opção sem espaço
	// optstring - no começo quando se pretende processar os argumentos sem opção no loop while
	{
	  printf(">optind %d\n",optind);
	  switch (opt)
      {
      case 'x': // opção sem argumentos
        xflag = 1;
        break;
      case 'y': // opção com argumentos obrigatórios
        yflag = 1;
        yvalue = optarg;
        break;
      case 'w': // opção com argumento opcional
        wflag = 1;
        wvalue = optarg;
        break;
      case 'z': // opção com argumentos obrigatórios
		zflag = 1;
		optind--;
		for(;optind < argc && *argv[optind] != '-'; optind++)
			printf(">> Vários Argumentos: %s\n",argv[optind]);
        break;
	  case 1:
		printf("Argumento sem opção %s\n",optarg);
		break;
      case ':':
        if (optopt == 'y')
          fprintf (stderr, "> a opcao -%c requere um argumento.\n", optopt);
        return 1;
      case '?':
		if (isprint (optopt))
          fprintf (stderr, "> opcao `-%c' desconhecida.\n", optopt);
        return 1;
      }
    }
	printf("xflag = %d, yflag = %d, yvalue = %s, wflag = %d, wvalue = %s, zflag = %d\n",
            xflag, yflag, yvalue, wflag, wvalue, zflag);

	for(index = optind; index < argc; index++)
		printf ("index%d argumento não obrigatórios %s\n", index, argv[index]);
	return 0;
}

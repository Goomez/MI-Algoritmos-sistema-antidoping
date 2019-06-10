#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <windows.h>

/*Lista respons�vel por guardar os dados dos jogadores*/
typedef struct cadastro{
	int posiNaLista;/*Varialvel que quarda a posi��o do jogador na lista*/
	int veriSorteio;/*Variavel que guarda o numero do sorteio que o jogador foi sorteado, inicialmente � iniciada com 0 (n�o sorteado)*/
	
	char nomeJogador[50];/*Nome do jogador*/
	int anoNasci;/*Ano de nascimento*/
	char paisSelecao[50];/*Sele��o do jogador*/
	int numCamisa;/*N�mero da camisa*/
	char posiTime[50];/*Posi��o do jogador no time*/
	
	struct cadastro *proxiJogador;/*Ponteira pra apontar para o pr�ximo n�*/
}jogadores;

/*Lista respons�vel por guardar os sorteios*/
typedef struct sorteios{
	int numeroDoSorteio;/*Guarda o numero do sorteio*/
	int quantidadeDeSorteados;/*Guarda a quantidade de jogadores que foram sorteados*/
	struct sorteios *proxiNo;
}sort;

void cabecalho();/*Cabe�alho do programa*/
jogadores* cadastroJogadores(int CJcontJogador, jogadores *CJjogadorTopo); /*Prot�tipo da fun��o de cadastro dos jogadores*/
void buscaCamisa(int BCcontJogador, jogadores *BJjogadorTopo);/*Prot�tipo da fun��o que busca e altera o n�mero do jogador*/
jogadores* removerJogador(jogadores *RJjogadorTopo, int *RJcontJogador);/*Prot�tipo da fun��o que remove jogadores*/
sort* sortearJogadores(jogadores *SJjogadorTopo, sort *SJsorteio, int SJcontJogador, int *SJnumSorteio);/*Prot�tipo da fun��o que sorteia jogadores para a realiza��o de exames antidoping*/
void filtragemSorteio(jogadores *FSjogadorTopo, int FScontJogador);/*Prot�tipo da fun��o que filtra os jogadores sorteados por posi��o*/
void exibirTodosJogadores(jogadores *ETJjogadorTopo, int ETJcontJogador);/*Prot�tipo da fun��o que exibe todos os jogadores cadastrados*/
void exibirJogadoresSorteados(int EJScontJogador, jogadores *EJSjogadoresTopo, int EJSnumSorteio, sort *EJSsorteio);/*Prot�tipo da fun��o que exibe todos os jogadores sorteados*/

int main(){
	int menu;
	int contJogador=0;/*Variavel que conta a quantidade de jogadores*/
	int numSorteio=-1;/*Variavel que guarda o n�mero do sorteio, � inicializada com 0 para evitar erros na fun��o de exibir os jogadores sorteados*/
	jogadores *jogadoresTopo=NULL;/*Ponteiro que aponta para o topo da lista encadeada dos jogadores*/
	sort *sorteioTopo=NULL;/*Ponteiro que aponta para o topo da lista encadeada do sorteio*/
	setlocale(LC_ALL, "Portuguese");
	
    while(1){/*La�o de repeti��o do menu*/
    	system("CLS");
    	cabecalho();
    	printf("\n\n> MENU:\n\t[1] - CADASTRAR JOGADORES;\n\t[2] - ALTERAR N�MERO DA CAMISA DO JOGADOR;\n\t[3] - REMOVER CADASTRO DO JOGADOR;\n\t[4] - SORTEAR JOGADORES PARA O EXAME;\n\t[5] - MOSTRAR JOGADORES SORTEADOS PELA POSI��O (FILTRAR);\n\t[6] - EXIBIR TODOS OS JOGADORES;\n\t[7] - EXIBIR TODOS OS JOGADORES SORTEADOS;\n\t[8] - SAIR DO PROGRAMA.");
		printf("\n>>>: ");
		fflush(stdin);
		scanf("%d", &menu);
		
		
		switch(menu){
	    	case 1:/*Cadastrar Jogador*/
	    		contJogador++;
	    		jogadoresTopo = cadastroJogadores(contJogador, jogadoresTopo);
	    		break;
	    		
	    	case 2:/*Alterar n�mero da camisa*/
	    		buscaCamisa(contJogador, jogadoresTopo);
	    		break;
	    		
	    	case 3:/*Remover cadastro do jogador*/
	    		jogadoresTopo = removerJogador(jogadoresTopo, &contJogador);
	    		break;
	    		
	    	case 4:/*Sortear jogador(es)*/
	    		if(numSorteio==-1)/*Caso seja a primeira vez que o usuario v� sortear jogadores*/
	    			numSorteio=1;/*Transformando o -1 em 1*/
				else/*Caso n�o seja primeira vez, apenas acrescenta*/
	    			numSorteio++;
	    		sorteioTopo = sortearJogadores(jogadoresTopo, sorteioTopo, contJogador, &numSorteio);
	    		break;
	    		
	    	case 5:/*Filtrar jogadores sorteados por posi��o*/
	    		filtragemSorteio(jogadoresTopo, contJogador);
	    		break;
	    		
	    	case 6:/*Exibir todos os jogadores*/
	    		exibirTodosJogadores(jogadoresTopo, contJogador);
	    		break;
	    		
	    	case 7:/*Exibir todos os jogadores sorteados*/
	    		exibirJogadoresSorteados(contJogador, jogadoresTopo, numSorteio, sorteioTopo);
	    		break;
	    		
	    	case 8:/*Sair do programa*/
	    		printf("\n\n\t[Aplica��o encerrada. Obrigado por usar nosso sistema!]");
	    		Sleep(1500);
	    		exit(0);
	    		
	    	default:
	    		printf("\n\t[Op��o inv�lida! Por favor tente novamente.]");
				break;
		}
	}/*Fim do la�o while*/
	return 0;
}
void cabecalho(){
    printf("\t\t+===============================================+\n");
    printf("\t\t     Sistema Antidoping - COPA DO MUNDO 2018\n");
    printf("\t\t+===============================================+\n");
}


/*Fun��o de cadastro dos jogadores*/
jogadores* cadastroJogadores(int CJcontJogador, jogadores *CJjogadoresTopo){
	
	system("CLS");
	cabecalho();
	if(CJjogadoresTopo == NULL){
		
		/*Alocando o primeiro n� da lista*/
		CJjogadoresTopo = (jogadores *) malloc(sizeof(jogadores));
		CJjogadoresTopo->proxiJogador=NULL;
		
		/*Preenchendo com os valores recebido pelo usuario/arquivo*/
		printf("\n\n [1] - CADASTRAR NOVO JOGADOR: ");
		printf("\n\n - Nome do Jogador: ");
		fflush(stdin);
		scanf("%[^\n]s", CJjogadoresTopo->nomeJogador);
		
		printf(" - Ano de nascimento do jogador (ex: 1989): ");
		scanf("%d", &CJjogadoresTopo->anoNasci);
		
		printf(" - Pa�s sele��o do jogador: ");
		fflush(stdin);
		scanf("%[^\n]s", CJjogadoresTopo->paisSelecao);
		
		printf(" - N�mero da camisa do jogador: ");
		scanf("%d", &CJjogadoresTopo->numCamisa);
		
		printf(" - Posi��o do jogador (ex: Atacante): ");
		fflush(stdin);
		scanf("%[^\n]s", CJjogadoresTopo->posiTime);

		CJjogadoresTopo->veriSorteio=0; /*Igualando a variavel de verifica��o de sorteio a 0 (0 = n�o sorteado)*/
		CJjogadoresTopo->posiNaLista = CJcontJogador; /*Dando o n�mero da posi��o a variavel que guarda a posi��o do jogador na lista*/
		
		printf("\n\t[CADASTRO REALIZADO COM SUCESSO!]");
		Sleep(1500);
		return CJjogadoresTopo; /*Retornando a lista*/
	}
	else{ /*Fazendo o mesmo processo descrito anteriormente, s� que com apartir do segundo n� em diante*/
	
		/*Auxiliares para ajudar na cria��o do novo n�, e na busca do final da lsita*/
		jogadores *novoJogador, *auxiliar;
		novoJogador = (jogadores *) malloc(sizeof(jogadores));
		novoJogador->proxiJogador=NULL;
	
		printf("\n\n [1] - CADASTRAR NOVO JOGADOR: ");
		printf("\n\n - Nome do Jogador: ");
		fflush(stdin);
		scanf("%[^\n]s", novoJogador->nomeJogador);
		
		printf(" - Ano de nascimento do jogador (ex: 1989): ");
		scanf("%d", &novoJogador->anoNasci);
		
		printf(" - Pa�s sele��o do jogador: ");
		fflush(stdin);
		scanf("%[^\n]s", novoJogador->paisSelecao);
		
		printf(" - N�mero da camisa do jogador: ");
		scanf("%d", &novoJogador->numCamisa);
			
		printf(" - Posi��o do jogador (ex: Atacante): ");
		fflush(stdin);
		scanf("%[^\n]s", novoJogador->posiTime);
		novoJogador->veriSorteio=0;
		novoJogador->posiNaLista = CJcontJogador;
		
		auxiliar=CJjogadoresTopo; /*Auxiliar para percorrer a lista*/
		
		/*Indo para o final da lista*/
		while(auxiliar->proxiJogador!=NULL)
			auxiliar=auxiliar->proxiJogador;
			
		auxiliar->proxiJogador=novoJogador;/*Conectando o n� no final da lista*/
		printf("\n\t[CADASTRO REALIZADO COM SUCESSO!]");
		Sleep(1500);
		return CJjogadoresTopo;
	}	
}
/*Fun��o de busca e de altera��o da camisa de jogadores*/
void buscaCamisa(int BCcontJogador, jogadores *BJjogadoresTopo){
	system("CLS");
	cabecalho();
	jogadores *auxiliar;
	auxiliar=BJjogadoresTopo;
	char nomeBuscado[30];
	
	printf("\n\n [2] - ALTERAR N�MERO DA CAMISA DO JOGADOR: ");
	printf("\n>>> Digite o nome do jogador: ");
	fflush(stdin);
	scanf("%[^\n]s", nomeBuscado);
	
	while(auxiliar!=NULL){
		if(!strcmp(auxiliar->nomeJogador, nomeBuscado)){
			system("CLS");
			cabecalho();
			printf("\n\n [2] - ALTERAR N�MERO DA CAMISA DO JOGADOR: ");
			printf("\n\n- N�mero antigo: %d\n>>> Digite o novo n�mero: ", auxiliar->numCamisa);
			scanf("%d", &auxiliar->numCamisa);
			printf("\n\t[N�MERO ATUALIZADO COM SUCESSO!]");
			break;
		}
		/*Passando pro pr�ximo n�*/	
		auxiliar=auxiliar->proxiJogador;
	}
	if(auxiliar==NULL){
		system("CLS");
		cabecalho();
		printf("\n\n [2] - ALTERAR N�MERO DA CAMISA DO JOGADOR: ");
		printf("\n\n[JOGADOR %s N�O ENCONTRADO. CADASTRO INEXISTENTE!]", nomeBuscado);
		Sleep(2000);
	}
}
/*Fun��o de remo��o de cadastro de jogadores*/
jogadores* removerJogador(jogadores *RJjogadoresTopo, int *RJcontJogador){
	int cont=0;/*Variavel para saber quantas vezes o la�o de repeti��o se repetiu*/
	jogadores *atual, *anterior;/*auxiliares*/
	atual=RJjogadoresTopo;
	anterior=RJjogadoresTopo;
	char nomeBuscado[30];
	
	system("CLS");
	cabecalho();
	printf("\n\n [3] - REMOVER CADASTRO DO JOGADOR: ");
	printf("\n>>> Digite o nome do jogador: ");
	fflush(stdin);
	scanf("%[^\n]s", nomeBuscado);
	
		while(atual!=NULL){/*La�o que ser� percorrido at� encontrar o jogador, ou at� chegar no final da lista*/
			if(strcmp(atual->nomeJogador, nomeBuscado)==0){/*Caso encontre o jogador*/
				if(cont==0){/*Caso seja o primeira vez que o la�o while esteja se repetindo*/
					if((*RJcontJogador)==1){/*Caso s� tenha um n� na lista*/
						free(atual);/*Libera o n�*/
						RJjogadoresTopo=NULL;/*A lista � zerada*/
						(*RJcontJogador)=0;/*A quantidade de jogadores passa a ser 0*/
						printf("\n\t[CADASTRO REMOVIDO!]");
						Sleep(2000);
						return RJjogadoresTopo;
					}
					else{/*Caso seja o primeiro no da lista*/
						anterior=anterior->proxiJogador;/*Conectando no pr�ximo n�*/
						free(atual);/*Liberando o n� atual*/
						RJjogadoresTopo=anterior;
						(*RJcontJogador)--;/*Decrementando a vari�vel que guarda a quantidade de jogadores*/
						printf("\n\t[CADASTRO REMOVIDO!]");
						Sleep(2000);
						return RJjogadoresTopo;
					}
				}
				else if(atual->proxiJogador!=NULL){/*Caso o n� do jogador se encontre no meio da lista*/
					anterior->proxiJogador=atual->proxiJogador;
					free(atual);
					(*RJcontJogador)--;
					printf("\n\t[CADASTRO REMOVIDO!]");
					Sleep(2000);
					return RJjogadoresTopo;
				}
				else if(atual->proxiJogador==NULL){/*Caso o n� do jogador seja o ultimo da lista*/
					anterior->proxiJogador=NULL;
					free(atual);
					(*RJcontJogador)--;
					printf("\n\t[CADASTRO REMOVIDO!]");
					Sleep(2000);
					return RJjogadoresTopo;
				}
			}	
			/*Passando para o pr�ximo n�*/	
			anterior=atual;
			atual=atual->proxiJogador;
			cont++;
		}
		
		if(atual==NULL){/*Caso chegue no final da lista, significa que n�o foi encontrado*/
			printf("\n\t[N�O FOI POSS�VEL A REMO��O DE %s]", nomeBuscado);
			printf("\n\t     [CADASTRO INEXISTENTE!]");
			Sleep(3000);
			return RJjogadoresTopo;
		}
}

/*Fun��o para sortear os jogadores*/
sort* sortearJogadores(jogadores *SJjogadoresTopo, sort *SJsorteioTopo, int SJcontJogador, int *SJnumSorteio){
	int trava=0, contador, numero, quant;/*"trava" para saber se o n�mero sorteado foi encontrado na lista, "contador" utilizado no for como variavel de contagem, "numero" variavel que recebera o numero sorteado, "quant" quantidade de jogadores que o usu�rio pediu*/
	jogadores *atual;/*auxiliar*/
	atual = SJjogadoresTopo;
	
	srand(time(NULL));/*Fun��o para poder usar o rand da biblioteca "time.h"*/
	
	system("CLS");
	cabecalho();
	printf("\n\n [4] - SORTEAR JOGADORES PARA O EXAME: ");
	
	if(SJsorteioTopo==NULL){/*Caso seja a primeira vez que esteja sendo feito o sorteio*/
		printf("\n>>> Digite a quantidade de jogadores para serem sorteados: ");
		fflush(stdin);
		scanf("%d", &quant);
		
		if(SJcontJogador==0){/*Caso n�o haja jogadores registrados, torna invalida a chamada da fun��o e � preciso decrementar a variavel que guarda o numero do sorteio*/
			printf("\n\t[N�O H� JOGADORES RESISTRADOS!]");
			Sleep(2000);
			(*SJnumSorteio)--;
			return SJsorteioTopo;
		}
		else if(quant>SJcontJogador){/*Caso o usuario pe�a mais jogadores do que tem registrados*/
			printf("\n\t[QUANTIDADE M�XIMA DE JOGADORES EXCEDIDA! H� %d JOGADORES CADASTRADOS]", SJcontJogador);
			Sleep(3000);
			(*SJnumSorteio)--;
			return SJsorteioTopo;
		}
		/*Alocando um novo n� para a lista dos sorteios*/
		SJsorteioTopo = (sort*) malloc(sizeof(sort));
		SJsorteioTopo->proxiNo=NULL;
		
		SJsorteioTopo->numeroDoSorteio=(*SJnumSorteio);
		SJsorteioTopo->quantidadeDeSorteados=quant;
		
		for(contador=0; contador<quant; contador++){
			numero = rand() % (SJcontJogador*50);/*Pegando o resto da divis�o do numero do rand com o n�mero de jogadores multiplicado por 50*/
			while(atual!=NULL){
				if(atual->posiNaLista==numero){/*Caso encontre o numero na lista encadeada*/
					if(atual->veriSorteio==0){/*Verificando se o jogador j� foi ou n�o sorteado*/
						atual->veriSorteio=SJsorteioTopo->numeroDoSorteio;/*Atribuindo a variavel de verifica��o de sorteio da lista dos jogadores ao numero desse sorteio*/
						trava=1;/*Para mostrar que ouve um jogador sorteado*/
						break;
					}
				}
				/*Passando para o pr�ximo n�*/
				atual=atual->proxiJogador;
			}
			atual=SJjogadoresTopo;/*Reiniciando o ponteiro auxiliar*/
			if(trava==0){/*Caso n�o tenha encontrado o n�mero sorteado na lista*/
				contador--;/*Decrementando a variavel de contagem do la�o for*/
			}
			//else
				//printf("\n\n\t[Sorteio realizado com sucesso]");
			trava=0;/*Reiniciando a variavel de verifica��o*/
		}
		
		return SJsorteioTopo;
	}
	else{/*Caso n�o seja a primeira vez que esteja feito o sorteio, ir� fazer as mesmas coisas descritas acima, s� que com auxiliares*/
		printf("\n>>> Digite a quantidade de jogadores para serem sorteados: ");
		fflush(stdin);
		scanf("%d", &quant);
		if(SJcontJogador==0){
			printf("\n\t[N�O H� JOGADORES RESISTRADOS!]");
			Sleep(2000);
			(*SJnumSorteio)--;
			return SJsorteioTopo;
		}
		else if(quant>SJcontJogador){
			printf("\n\t[QUANTIDADE M�XIMA DE JOGADORES EXCEDIDA! H� %d JOGADORES CADASTRADOS]", SJcontJogador);
			Sleep(3000);
			(*SJnumSorteio)--;
			return SJsorteioTopo;
		}
		/*Auxiliares*/
		sort *novoSorteio;
		sort *auxiliar;
		auxiliar=SJsorteioTopo;
		
		novoSorteio = (sort*) malloc(sizeof(sort));
		novoSorteio->proxiNo=NULL;
		
		novoSorteio->numeroDoSorteio=(*SJnumSorteio);
		novoSorteio->quantidadeDeSorteados=quant;
		
		for(contador=0; contador<quant; contador++){
			numero = rand() % (SJcontJogador*100);
			while(atual!=NULL){
				if(atual->posiNaLista==numero){
					if(atual->veriSorteio==0){
						atual->veriSorteio=novoSorteio->numeroDoSorteio;
						trava=1;
						break;
					}
				}
				atual=atual->proxiJogador;
			}
			atual=SJjogadoresTopo;
			if(trava==0){
				contador--;
			}
			trava=0;
		}
		
		while(auxiliar->proxiNo!=NULL)
			auxiliar=auxiliar->proxiNo;
			
		auxiliar->proxiNo=novoSorteio;
		
		return SJsorteioTopo;
		
	}
	
}

/*Fun��o para filtragem os jogadores sorteados por posi��o*/
void filtragemSorteio(jogadores *FSjogadoresTopo, int FScontJogador){
	
	int trava=0, contador=0, verificadorDePosicao=0;/*Variaveis para saber se h� jogadores na posi��o inserida, para saber quantas vezes o la�o se repetiu, e para verificar se a posi��o existe*/
	char nomeBuscado[30];
	jogadores *atual;
	atual= FSjogadoresTopo;
	system("CLS");
	cabecalho();
	printf("\n\n [5] - MOSTRAR JOGADORES SORTEADOS PELA POSI��O (FILTRAR): ");
	fflush(stdin);
	scanf("%[^\n]s", &nomeBuscado);
	int i=1;
	while(atual!=NULL){
		if(strcmp(atual->posiTime, nomeBuscado)!=0)/*Caso a posi��o n�o seja encontrada*/
			verificadorDePosicao++;/*A variavel ser� acrementada e verificada no final da fun��o, para saber se a posi��o inserida existe*/
		if(strcmp(atual->posiTime, nomeBuscado)==0 && atual->veriSorteio>0){/*Caso a posi��o seja encontrada e o jogador j� tenha sido sorteado*/
			if(contador==0){/*Caso seja primeira vez que o la�o tenha se repetido, para mostrar o escopo da fun��o*/
				printf("\n\n - JOGADORES SORTEADOS E QUE OCUPAM A POSI��O: %s", nomeBuscado);
				printf("\n\t(%d) %s\t%s",i, atual->nomeJogador, atual->paisSelecao);
				i++;
			}
			else{/*Caso n�o seja, ser� exibido apenas os jogadores*/
				printf("\n\t(%d) %s\t%s",i, atual->nomeJogador, atual->paisSelecao);
				i++;
			}
			trava=1;
		}
			
		atual=atual->proxiJogador;
		contador++;
	}
	if(trava==0){/*Caso nenhum jogador tenha sido encontrado*/
		if(verificadorDePosicao==FScontJogador)/*Caso a posi��o n�o exista na lista*/
			printf("\n\t[N�O EXISTE A POSICAO INSERIDA: %s!]", nomeBuscado);
		else/*Sen�o ser� mostrado a mensagem normal*/
			printf("\n\t[NENHUM JODAGOR SORTEADO OCUPA A POSICAO: %s]", nomeBuscado);
		Sleep(3000);
	}
	else
		Sleep(4000);
}

/*Fun��o para exibir todos os jogadores*/
void exibirTodosJogadores(jogadores *ETJjogadoresTopo, int ETJcontJogador){
	jogadores *atual;
	atual=ETJjogadoresTopo;
	
	system("CLS");
	cabecalho();
	printf("\n\n [6] - EXIBIR TODOS OS JOGADORES: ");
	fflush(stdin);
	
	if(ETJcontJogador<=0){
		printf("\n\t [N�O EXISTEM JOGADORES REGISTRADOS!]");
		Sleep(3000);
	}
	else{
		printf("\n\n - EXIBI��O DE TODOS OS JOGADORES: ");
		printf("\n\n\tNOME\t");
		printf("ANO\t");
		printf("PA�S\t");
		printf("CAMISA\t");
		printf("POSI��O");
		while(atual!=NULL){/*Exibindo um jogador por vez*/
			printf("\n\t%s\t", atual->nomeJogador);
			printf("%d\t", atual->anoNasci);
			printf("%s\t", atual->paisSelecao);
			printf("%d\t", atual->numCamisa);
			printf("%s", atual->posiTime);
			atual=atual->proxiJogador;/*Passando para o pr�ximo jogador*/
		}
		printf("\n");
		system("pause");
	}	
}

/*Fun��o para exibir todos os jogadores sorteados*/
void exibirJogadoresSorteados(int EJScontJogador, jogadores *EJSjogadoresTopo, int EJSnumSorteio, sort *EJSsorteioTopo){
	jogadores *atualJogador;
	sort *atualSorteio;
	atualSorteio=EJSsorteioTopo;
	int contador;
	system("CLS");
	
	cabecalho();
	printf("\n\n [7] - EXIBIR TODOS OS JOGADORES SORTEADOS: ");
	fflush(stdin);
	
	if(EJScontJogador<=0){
		printf("\n\n\t [N�O EXISTEM JOGADORES REGISTRADOS!]");
		Sleep(3000);
	}
	else if(EJSsorteioTopo==NULL){
		printf("\n\n\t [N�O EXISTEM JOGADORES SORTEADOS!]");
		Sleep(3000);
	}
	else{
		printf("\n\n - EXIBI��O DE JOGADORES SORTEADOS:");
		while(atualSorteio!=NULL){
			contador=0;
			atualJogador = EJSjogadoresTopo;
			while(atualJogador!=NULL){
				if(atualJogador->veriSorteio==atualSorteio->numeroDoSorteio){/*Verificando se o jogador pertence ao sorteio que est� sendo testado*/
					if(contador==0){/*Caso seja a primeira vez que o la�o while se repete, ser� mostrado o escopo da fun��o*/
						printf("\n N� DO SORTEIO %d -> %d JOGADORES SORTEADOS", atualSorteio->numeroDoSorteio, atualSorteio->quantidadeDeSorteados);
					}
						printf("\n\t - %s\t%s - ", atualJogador->nomeJogador, atualJogador->paisSelecao);
					contador++;
				}
				atualJogador=atualJogador->proxiJogador;
			}
			
			atualSorteio=atualSorteio->proxiNo;
		}
		Sleep(5000);
	}
}

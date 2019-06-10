#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <windows.h>

/*Lista responsável por guardar os dados dos jogadores*/
typedef struct cadastro{
	int posiNaLista;/*Varialvel que quarda a posição do jogador na lista*/
	int veriSorteio;/*Variavel que guarda o numero do sorteio que o jogador foi sorteado, inicialmente é iniciada com 0 (não sorteado)*/
	
	char nomeJogador[50];/*Nome do jogador*/
	int anoNasci;/*Ano de nascimento*/
	char paisSelecao[50];/*Seleção do jogador*/
	int numCamisa;/*Número da camisa*/
	char posiTime[50];/*Posição do jogador no time*/
	
	struct cadastro *proxiJogador;/*Ponteira pra apontar para o próximo nó*/
}jogadores;

/*Lista responsável por guardar os sorteios*/
typedef struct sorteios{
	int numeroDoSorteio;/*Guarda o numero do sorteio*/
	int quantidadeDeSorteados;/*Guarda a quantidade de jogadores que foram sorteados*/
	struct sorteios *proxiNo;
}sort;

void cabecalho();/*Cabeçalho do programa*/
jogadores* cadastroJogadores(int CJcontJogador, jogadores *CJjogadorTopo); /*Protótipo da função de cadastro dos jogadores*/
void buscaCamisa(int BCcontJogador, jogadores *BJjogadorTopo);/*Protótipo da função que busca e altera o número do jogador*/
jogadores* removerJogador(jogadores *RJjogadorTopo, int *RJcontJogador);/*Protótipo da função que remove jogadores*/
sort* sortearJogadores(jogadores *SJjogadorTopo, sort *SJsorteio, int SJcontJogador, int *SJnumSorteio);/*Protótipo da função que sorteia jogadores para a realização de exames antidoping*/
void filtragemSorteio(jogadores *FSjogadorTopo, int FScontJogador);/*Protótipo da função que filtra os jogadores sorteados por posição*/
void exibirTodosJogadores(jogadores *ETJjogadorTopo, int ETJcontJogador);/*Protótipo da função que exibe todos os jogadores cadastrados*/
void exibirJogadoresSorteados(int EJScontJogador, jogadores *EJSjogadoresTopo, int EJSnumSorteio, sort *EJSsorteio);/*Protótipo da função que exibe todos os jogadores sorteados*/

int main(){
	int menu;
	int contJogador=0;/*Variavel que conta a quantidade de jogadores*/
	int numSorteio=-1;/*Variavel que guarda o número do sorteio, é inicializada com 0 para evitar erros na função de exibir os jogadores sorteados*/
	jogadores *jogadoresTopo=NULL;/*Ponteiro que aponta para o topo da lista encadeada dos jogadores*/
	sort *sorteioTopo=NULL;/*Ponteiro que aponta para o topo da lista encadeada do sorteio*/
	setlocale(LC_ALL, "Portuguese");
	
    while(1){/*Laço de repetição do menu*/
    	system("CLS");
    	cabecalho();
    	printf("\n\n> MENU:\n\t[1] - CADASTRAR JOGADORES;\n\t[2] - ALTERAR NÚMERO DA CAMISA DO JOGADOR;\n\t[3] - REMOVER CADASTRO DO JOGADOR;\n\t[4] - SORTEAR JOGADORES PARA O EXAME;\n\t[5] - MOSTRAR JOGADORES SORTEADOS PELA POSIÇÃO (FILTRAR);\n\t[6] - EXIBIR TODOS OS JOGADORES;\n\t[7] - EXIBIR TODOS OS JOGADORES SORTEADOS;\n\t[8] - SAIR DO PROGRAMA.");
		printf("\n>>>: ");
		fflush(stdin);
		scanf("%d", &menu);
		
		
		switch(menu){
	    	case 1:/*Cadastrar Jogador*/
	    		contJogador++;
	    		jogadoresTopo = cadastroJogadores(contJogador, jogadoresTopo);
	    		break;
	    		
	    	case 2:/*Alterar número da camisa*/
	    		buscaCamisa(contJogador, jogadoresTopo);
	    		break;
	    		
	    	case 3:/*Remover cadastro do jogador*/
	    		jogadoresTopo = removerJogador(jogadoresTopo, &contJogador);
	    		break;
	    		
	    	case 4:/*Sortear jogador(es)*/
	    		if(numSorteio==-1)/*Caso seja a primeira vez que o usuario vá sortear jogadores*/
	    			numSorteio=1;/*Transformando o -1 em 1*/
				else/*Caso não seja primeira vez, apenas acrescenta*/
	    			numSorteio++;
	    		sorteioTopo = sortearJogadores(jogadoresTopo, sorteioTopo, contJogador, &numSorteio);
	    		break;
	    		
	    	case 5:/*Filtrar jogadores sorteados por posição*/
	    		filtragemSorteio(jogadoresTopo, contJogador);
	    		break;
	    		
	    	case 6:/*Exibir todos os jogadores*/
	    		exibirTodosJogadores(jogadoresTopo, contJogador);
	    		break;
	    		
	    	case 7:/*Exibir todos os jogadores sorteados*/
	    		exibirJogadoresSorteados(contJogador, jogadoresTopo, numSorteio, sorteioTopo);
	    		break;
	    		
	    	case 8:/*Sair do programa*/
	    		printf("\n\n\t[Aplicação encerrada. Obrigado por usar nosso sistema!]");
	    		Sleep(1500);
	    		exit(0);
	    		
	    	default:
	    		printf("\n\t[Opção inválida! Por favor tente novamente.]");
				break;
		}
	}/*Fim do laço while*/
	return 0;
}
void cabecalho(){
    printf("\t\t+===============================================+\n");
    printf("\t\t     Sistema Antidoping - COPA DO MUNDO 2018\n");
    printf("\t\t+===============================================+\n");
}


/*Função de cadastro dos jogadores*/
jogadores* cadastroJogadores(int CJcontJogador, jogadores *CJjogadoresTopo){
	
	system("CLS");
	cabecalho();
	if(CJjogadoresTopo == NULL){
		
		/*Alocando o primeiro nó da lista*/
		CJjogadoresTopo = (jogadores *) malloc(sizeof(jogadores));
		CJjogadoresTopo->proxiJogador=NULL;
		
		/*Preenchendo com os valores recebido pelo usuario/arquivo*/
		printf("\n\n [1] - CADASTRAR NOVO JOGADOR: ");
		printf("\n\n - Nome do Jogador: ");
		fflush(stdin);
		scanf("%[^\n]s", CJjogadoresTopo->nomeJogador);
		
		printf(" - Ano de nascimento do jogador (ex: 1989): ");
		scanf("%d", &CJjogadoresTopo->anoNasci);
		
		printf(" - País seleção do jogador: ");
		fflush(stdin);
		scanf("%[^\n]s", CJjogadoresTopo->paisSelecao);
		
		printf(" - Número da camisa do jogador: ");
		scanf("%d", &CJjogadoresTopo->numCamisa);
		
		printf(" - Posição do jogador (ex: Atacante): ");
		fflush(stdin);
		scanf("%[^\n]s", CJjogadoresTopo->posiTime);

		CJjogadoresTopo->veriSorteio=0; /*Igualando a variavel de verificação de sorteio a 0 (0 = não sorteado)*/
		CJjogadoresTopo->posiNaLista = CJcontJogador; /*Dando o número da posição a variavel que guarda a posição do jogador na lista*/
		
		printf("\n\t[CADASTRO REALIZADO COM SUCESSO!]");
		Sleep(1500);
		return CJjogadoresTopo; /*Retornando a lista*/
	}
	else{ /*Fazendo o mesmo processo descrito anteriormente, só que com apartir do segundo nó em diante*/
	
		/*Auxiliares para ajudar na criação do novo nó, e na busca do final da lsita*/
		jogadores *novoJogador, *auxiliar;
		novoJogador = (jogadores *) malloc(sizeof(jogadores));
		novoJogador->proxiJogador=NULL;
	
		printf("\n\n [1] - CADASTRAR NOVO JOGADOR: ");
		printf("\n\n - Nome do Jogador: ");
		fflush(stdin);
		scanf("%[^\n]s", novoJogador->nomeJogador);
		
		printf(" - Ano de nascimento do jogador (ex: 1989): ");
		scanf("%d", &novoJogador->anoNasci);
		
		printf(" - País seleção do jogador: ");
		fflush(stdin);
		scanf("%[^\n]s", novoJogador->paisSelecao);
		
		printf(" - Número da camisa do jogador: ");
		scanf("%d", &novoJogador->numCamisa);
			
		printf(" - Posição do jogador (ex: Atacante): ");
		fflush(stdin);
		scanf("%[^\n]s", novoJogador->posiTime);
		novoJogador->veriSorteio=0;
		novoJogador->posiNaLista = CJcontJogador;
		
		auxiliar=CJjogadoresTopo; /*Auxiliar para percorrer a lista*/
		
		/*Indo para o final da lista*/
		while(auxiliar->proxiJogador!=NULL)
			auxiliar=auxiliar->proxiJogador;
			
		auxiliar->proxiJogador=novoJogador;/*Conectando o nó no final da lista*/
		printf("\n\t[CADASTRO REALIZADO COM SUCESSO!]");
		Sleep(1500);
		return CJjogadoresTopo;
	}	
}
/*Função de busca e de alteração da camisa de jogadores*/
void buscaCamisa(int BCcontJogador, jogadores *BJjogadoresTopo){
	system("CLS");
	cabecalho();
	jogadores *auxiliar;
	auxiliar=BJjogadoresTopo;
	char nomeBuscado[30];
	
	printf("\n\n [2] - ALTERAR NÚMERO DA CAMISA DO JOGADOR: ");
	printf("\n>>> Digite o nome do jogador: ");
	fflush(stdin);
	scanf("%[^\n]s", nomeBuscado);
	
	while(auxiliar!=NULL){
		if(!strcmp(auxiliar->nomeJogador, nomeBuscado)){
			system("CLS");
			cabecalho();
			printf("\n\n [2] - ALTERAR NÚMERO DA CAMISA DO JOGADOR: ");
			printf("\n\n- Número antigo: %d\n>>> Digite o novo número: ", auxiliar->numCamisa);
			scanf("%d", &auxiliar->numCamisa);
			printf("\n\t[NÚMERO ATUALIZADO COM SUCESSO!]");
			break;
		}
		/*Passando pro próximo nó*/	
		auxiliar=auxiliar->proxiJogador;
	}
	if(auxiliar==NULL){
		system("CLS");
		cabecalho();
		printf("\n\n [2] - ALTERAR NÚMERO DA CAMISA DO JOGADOR: ");
		printf("\n\n[JOGADOR %s NÃO ENCONTRADO. CADASTRO INEXISTENTE!]", nomeBuscado);
		Sleep(2000);
	}
}
/*Função de remoção de cadastro de jogadores*/
jogadores* removerJogador(jogadores *RJjogadoresTopo, int *RJcontJogador){
	int cont=0;/*Variavel para saber quantas vezes o laço de repetição se repetiu*/
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
	
		while(atual!=NULL){/*Laço que será percorrido até encontrar o jogador, ou até chegar no final da lista*/
			if(strcmp(atual->nomeJogador, nomeBuscado)==0){/*Caso encontre o jogador*/
				if(cont==0){/*Caso seja o primeira vez que o laço while esteja se repetindo*/
					if((*RJcontJogador)==1){/*Caso só tenha um nó na lista*/
						free(atual);/*Libera o nó*/
						RJjogadoresTopo=NULL;/*A lista é zerada*/
						(*RJcontJogador)=0;/*A quantidade de jogadores passa a ser 0*/
						printf("\n\t[CADASTRO REMOVIDO!]");
						Sleep(2000);
						return RJjogadoresTopo;
					}
					else{/*Caso seja o primeiro no da lista*/
						anterior=anterior->proxiJogador;/*Conectando no próximo nó*/
						free(atual);/*Liberando o nó atual*/
						RJjogadoresTopo=anterior;
						(*RJcontJogador)--;/*Decrementando a variável que guarda a quantidade de jogadores*/
						printf("\n\t[CADASTRO REMOVIDO!]");
						Sleep(2000);
						return RJjogadoresTopo;
					}
				}
				else if(atual->proxiJogador!=NULL){/*Caso o nó do jogador se encontre no meio da lista*/
					anterior->proxiJogador=atual->proxiJogador;
					free(atual);
					(*RJcontJogador)--;
					printf("\n\t[CADASTRO REMOVIDO!]");
					Sleep(2000);
					return RJjogadoresTopo;
				}
				else if(atual->proxiJogador==NULL){/*Caso o nó do jogador seja o ultimo da lista*/
					anterior->proxiJogador=NULL;
					free(atual);
					(*RJcontJogador)--;
					printf("\n\t[CADASTRO REMOVIDO!]");
					Sleep(2000);
					return RJjogadoresTopo;
				}
			}	
			/*Passando para o próximo nó*/	
			anterior=atual;
			atual=atual->proxiJogador;
			cont++;
		}
		
		if(atual==NULL){/*Caso chegue no final da lista, significa que não foi encontrado*/
			printf("\n\t[NÃO FOI POSSÍVEL A REMOÇÃO DE %s]", nomeBuscado);
			printf("\n\t     [CADASTRO INEXISTENTE!]");
			Sleep(3000);
			return RJjogadoresTopo;
		}
}

/*Função para sortear os jogadores*/
sort* sortearJogadores(jogadores *SJjogadoresTopo, sort *SJsorteioTopo, int SJcontJogador, int *SJnumSorteio){
	int trava=0, contador, numero, quant;/*"trava" para saber se o número sorteado foi encontrado na lista, "contador" utilizado no for como variavel de contagem, "numero" variavel que recebera o numero sorteado, "quant" quantidade de jogadores que o usuário pediu*/
	jogadores *atual;/*auxiliar*/
	atual = SJjogadoresTopo;
	
	srand(time(NULL));/*Função para poder usar o rand da biblioteca "time.h"*/
	
	system("CLS");
	cabecalho();
	printf("\n\n [4] - SORTEAR JOGADORES PARA O EXAME: ");
	
	if(SJsorteioTopo==NULL){/*Caso seja a primeira vez que esteja sendo feito o sorteio*/
		printf("\n>>> Digite a quantidade de jogadores para serem sorteados: ");
		fflush(stdin);
		scanf("%d", &quant);
		
		if(SJcontJogador==0){/*Caso não haja jogadores registrados, torna invalida a chamada da função e é preciso decrementar a variavel que guarda o numero do sorteio*/
			printf("\n\t[NÃO HÁ JOGADORES RESISTRADOS!]");
			Sleep(2000);
			(*SJnumSorteio)--;
			return SJsorteioTopo;
		}
		else if(quant>SJcontJogador){/*Caso o usuario peça mais jogadores do que tem registrados*/
			printf("\n\t[QUANTIDADE MÁXIMA DE JOGADORES EXCEDIDA! HÁ %d JOGADORES CADASTRADOS]", SJcontJogador);
			Sleep(3000);
			(*SJnumSorteio)--;
			return SJsorteioTopo;
		}
		/*Alocando um novo nó para a lista dos sorteios*/
		SJsorteioTopo = (sort*) malloc(sizeof(sort));
		SJsorteioTopo->proxiNo=NULL;
		
		SJsorteioTopo->numeroDoSorteio=(*SJnumSorteio);
		SJsorteioTopo->quantidadeDeSorteados=quant;
		
		for(contador=0; contador<quant; contador++){
			numero = rand() % (SJcontJogador*50);/*Pegando o resto da divisão do numero do rand com o número de jogadores multiplicado por 50*/
			while(atual!=NULL){
				if(atual->posiNaLista==numero){/*Caso encontre o numero na lista encadeada*/
					if(atual->veriSorteio==0){/*Verificando se o jogador já foi ou não sorteado*/
						atual->veriSorteio=SJsorteioTopo->numeroDoSorteio;/*Atribuindo a variavel de verificação de sorteio da lista dos jogadores ao numero desse sorteio*/
						trava=1;/*Para mostrar que ouve um jogador sorteado*/
						break;
					}
				}
				/*Passando para o próximo nó*/
				atual=atual->proxiJogador;
			}
			atual=SJjogadoresTopo;/*Reiniciando o ponteiro auxiliar*/
			if(trava==0){/*Caso não tenha encontrado o número sorteado na lista*/
				contador--;/*Decrementando a variavel de contagem do laço for*/
			}
			//else
				//printf("\n\n\t[Sorteio realizado com sucesso]");
			trava=0;/*Reiniciando a variavel de verificação*/
		}
		
		return SJsorteioTopo;
	}
	else{/*Caso não seja a primeira vez que esteja feito o sorteio, irá fazer as mesmas coisas descritas acima, só que com auxiliares*/
		printf("\n>>> Digite a quantidade de jogadores para serem sorteados: ");
		fflush(stdin);
		scanf("%d", &quant);
		if(SJcontJogador==0){
			printf("\n\t[NÃO HÁ JOGADORES RESISTRADOS!]");
			Sleep(2000);
			(*SJnumSorteio)--;
			return SJsorteioTopo;
		}
		else if(quant>SJcontJogador){
			printf("\n\t[QUANTIDADE MÁXIMA DE JOGADORES EXCEDIDA! HÁ %d JOGADORES CADASTRADOS]", SJcontJogador);
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

/*Função para filtragem os jogadores sorteados por posição*/
void filtragemSorteio(jogadores *FSjogadoresTopo, int FScontJogador){
	
	int trava=0, contador=0, verificadorDePosicao=0;/*Variaveis para saber se há jogadores na posição inserida, para saber quantas vezes o laço se repetiu, e para verificar se a posição existe*/
	char nomeBuscado[30];
	jogadores *atual;
	atual= FSjogadoresTopo;
	system("CLS");
	cabecalho();
	printf("\n\n [5] - MOSTRAR JOGADORES SORTEADOS PELA POSIÇÃO (FILTRAR): ");
	fflush(stdin);
	scanf("%[^\n]s", &nomeBuscado);
	int i=1;
	while(atual!=NULL){
		if(strcmp(atual->posiTime, nomeBuscado)!=0)/*Caso a posição não seja encontrada*/
			verificadorDePosicao++;/*A variavel será acrementada e verificada no final da função, para saber se a posição inserida existe*/
		if(strcmp(atual->posiTime, nomeBuscado)==0 && atual->veriSorteio>0){/*Caso a posição seja encontrada e o jogador já tenha sido sorteado*/
			if(contador==0){/*Caso seja primeira vez que o laço tenha se repetido, para mostrar o escopo da função*/
				printf("\n\n - JOGADORES SORTEADOS E QUE OCUPAM A POSIÇÃO: %s", nomeBuscado);
				printf("\n\t(%d) %s\t%s",i, atual->nomeJogador, atual->paisSelecao);
				i++;
			}
			else{/*Caso não seja, será exibido apenas os jogadores*/
				printf("\n\t(%d) %s\t%s",i, atual->nomeJogador, atual->paisSelecao);
				i++;
			}
			trava=1;
		}
			
		atual=atual->proxiJogador;
		contador++;
	}
	if(trava==0){/*Caso nenhum jogador tenha sido encontrado*/
		if(verificadorDePosicao==FScontJogador)/*Caso a posição não exista na lista*/
			printf("\n\t[NÃO EXISTE A POSICAO INSERIDA: %s!]", nomeBuscado);
		else/*Senão será mostrado a mensagem normal*/
			printf("\n\t[NENHUM JODAGOR SORTEADO OCUPA A POSICAO: %s]", nomeBuscado);
		Sleep(3000);
	}
	else
		Sleep(4000);
}

/*Função para exibir todos os jogadores*/
void exibirTodosJogadores(jogadores *ETJjogadoresTopo, int ETJcontJogador){
	jogadores *atual;
	atual=ETJjogadoresTopo;
	
	system("CLS");
	cabecalho();
	printf("\n\n [6] - EXIBIR TODOS OS JOGADORES: ");
	fflush(stdin);
	
	if(ETJcontJogador<=0){
		printf("\n\t [NÃO EXISTEM JOGADORES REGISTRADOS!]");
		Sleep(3000);
	}
	else{
		printf("\n\n - EXIBIÇÃO DE TODOS OS JOGADORES: ");
		printf("\n\n\tNOME\t");
		printf("ANO\t");
		printf("PAÍS\t");
		printf("CAMISA\t");
		printf("POSIÇÃO");
		while(atual!=NULL){/*Exibindo um jogador por vez*/
			printf("\n\t%s\t", atual->nomeJogador);
			printf("%d\t", atual->anoNasci);
			printf("%s\t", atual->paisSelecao);
			printf("%d\t", atual->numCamisa);
			printf("%s", atual->posiTime);
			atual=atual->proxiJogador;/*Passando para o próximo jogador*/
		}
		printf("\n");
		system("pause");
	}	
}

/*Função para exibir todos os jogadores sorteados*/
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
		printf("\n\n\t [NÃO EXISTEM JOGADORES REGISTRADOS!]");
		Sleep(3000);
	}
	else if(EJSsorteioTopo==NULL){
		printf("\n\n\t [NÃO EXISTEM JOGADORES SORTEADOS!]");
		Sleep(3000);
	}
	else{
		printf("\n\n - EXIBIÇÃO DE JOGADORES SORTEADOS:");
		while(atualSorteio!=NULL){
			contador=0;
			atualJogador = EJSjogadoresTopo;
			while(atualJogador!=NULL){
				if(atualJogador->veriSorteio==atualSorteio->numeroDoSorteio){/*Verificando se o jogador pertence ao sorteio que está sendo testado*/
					if(contador==0){/*Caso seja a primeira vez que o laço while se repete, será mostrado o escopo da função*/
						printf("\n N° DO SORTEIO %d -> %d JOGADORES SORTEADOS", atualSorteio->numeroDoSorteio, atualSorteio->quantidadeDeSorteados);
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

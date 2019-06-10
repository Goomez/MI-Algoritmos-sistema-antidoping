/*******************************************************************************
Autor: Kevin Cerqueira Gomes
Componente Curricular: Algoritmos I
Concluido em: 16/07/2018
Declaro que este código foi elaborado por mim de forma individual e não contém nenhum
trecho de código de outro colega ou de outro autor, tais como provindos de livros e
apostilas, e páginas ou documentos eletrônicos da Internet. Qualquer trecho de código
de outra autoria que não a minha está destacado com uma citação para o autor e a fonte
do código, e estou ciente que estes trechos não serão considerados para fins de avaliação.
******************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

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
	
	printf("Sistema Antidoping - COPA DO MUNDO 2018");
    while(1){/*Laço de repetição do menu*/
		scanf("%d\n", &menu);
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
	    		printf("\n\nAplicação encerrada. Obrigado por usar nosso sistema!");
	    		exit(0);
	    		
	    	default:
	    		printf("\n\t[Opção inválida! Por favor tente novamente.]");
				break;
		}
	}/*Fim do laço while*/
	return 0;
}

/*Função de cadastro dos jogadores*/
jogadores* cadastroJogadores(int CJcontJogador, jogadores *CJjogadoresTopo){
	
	if(CJjogadoresTopo == NULL){
		
		/*Alocando o primeiro nó da lista*/
		CJjogadoresTopo = (jogadores *) malloc(sizeof(jogadores));
		CJjogadoresTopo->proxiJogador=NULL;
		
		/*Preenchendo com os valores recebido pelo usuario/arquivo*/
		scanf("%[^\n]s", CJjogadoresTopo->nomeJogador);

		scanf("%d\n", &CJjogadoresTopo->anoNasci);
	
		scanf("%[^\n]s", CJjogadoresTopo->paisSelecao);
	
		scanf("%d\n", &CJjogadoresTopo->numCamisa);
	
		scanf("%[^\n]s", CJjogadoresTopo->posiTime);

		CJjogadoresTopo->veriSorteio=0; /*Igualando a variavel de verificação de sorteio a 0 (0 = não sorteado)*/
		CJjogadoresTopo->posiNaLista = CJcontJogador; /*Dando o número da posição a variavel que guarda a posição do jogador na lista*/
		
		return CJjogadoresTopo; /*Retornando a lista*/
	}
	else{ /*Fazendo o mesmo processo descrito anteriormente, só que com apartir do segundo nó em diante*/
	
		/*Auxiliares para ajudar na criação do novo nó, e na busca do final da lsita*/
		jogadores *novoJogador, *auxiliar;
		novoJogador = (jogadores *) malloc(sizeof(jogadores));
		novoJogador->proxiJogador=NULL;
	
		scanf("%[^\n]s", novoJogador->nomeJogador);

		scanf("%d\n", &novoJogador->anoNasci);
		
		scanf("%[^\n]s", novoJogador->paisSelecao);
	
		scanf("%d\n", &novoJogador->numCamisa);
			
		scanf("%[^\n]s", novoJogador->posiTime);

		novoJogador->veriSorteio=0;
		novoJogador->posiNaLista = CJcontJogador;
		
		auxiliar=CJjogadoresTopo; /*Auxiliar para percorrer a lista*/
		
		/*Indo para o final da lista*/
		while(auxiliar->proxiJogador!=NULL)
			auxiliar=auxiliar->proxiJogador;
			
		auxiliar->proxiJogador=novoJogador;/*Conectando o nó no final da lista*/
	
		return CJjogadoresTopo;
	}	
}
/*Função de busca e de alteração da camisa de jogadores*/
void buscaCamisa(int BCcontJogador, jogadores *BJjogadoresTopo){
	jogadores *auxiliar;
	auxiliar=BJjogadoresTopo;
	char nomeBuscado[30];
	
	scanf("%[^\n]s", nomeBuscado);
	
	while(auxiliar!=NULL){
		if(!strcmp(auxiliar->nomeJogador, nomeBuscado)){
			scanf("%d\n", &auxiliar->numCamisa);
			break;
		}
		/*Passando pro próximo nó*/	
		auxiliar=auxiliar->proxiJogador;
	}
	if(auxiliar==NULL){
		printf("\n\nJOGADOR %s NÃO ENCONTRADO. CADASTRO INEXISTENTE!", nomeBuscado);
	}
}
/*Função de remoção de cadastro de jogadores*/
jogadores* removerJogador(jogadores *RJjogadoresTopo, int *RJcontJogador){
	int cont=0;/*Variavel para saber quantas vezes o laço de repetição se repetiu*/
	jogadores *atual, *anterior;/*auxiliares*/
	atual=RJjogadoresTopo;
	anterior=RJjogadoresTopo;
	char nomeBuscado[30];
	
	scanf("%[^\n]s", nomeBuscado);
		while(atual!=NULL){/*Laço que será percorrido até encontrar o jogador, ou até chegar no final da lista*/
			if(strcmp(atual->nomeJogador, nomeBuscado)==0){/*Caso encontre o jogador*/
				if(cont==0){/*Caso seja o primeira vez que o laço while esteja se repetindo*/
					if((*RJcontJogador)==1){/*Caso só tenha um nó na lista*/
						free(atual);/*Libera o nó*/
						RJjogadoresTopo=NULL;/*A lista é zerada*/
						(*RJcontJogador)=0;/*A quantidade de jogadores passa a ser 0*/
						return RJjogadoresTopo;
					}
					else{/*Caso seja o primeiro no da lista*/
						anterior=anterior->proxiJogador;/*Conectando no próximo nó*/
						free(atual);/*Liberando o nó atual*/
						RJjogadoresTopo=anterior;
						(*RJcontJogador)--;/*Decrementando a variável que guarda a quantidade de jogadores*/
						return RJjogadoresTopo;
					}
				}
				else if(atual->proxiJogador!=NULL){/*Caso o nó do jogador se encontre no meio da lista*/
					anterior->proxiJogador=atual->proxiJogador;
					free(atual);
					(*RJcontJogador)--;
					return RJjogadoresTopo;
				}
				else if(atual->proxiJogador==NULL){/*Caso o nó do jogador seja o ultimo da lista*/
					anterior->proxiJogador=NULL;
					free(atual);
					(*RJcontJogador)--;
					return RJjogadoresTopo;
				}
			}	
			/*Passando para o próximo nó*/	
			anterior=atual;
			atual=atual->proxiJogador;
			cont++;
		}
		
		if(atual==NULL){/*Caso chegue no final da lista, significa que não foi encontrado*/
			printf("\n\nNÃO FOI POSSÍVEL A REMOÇÃO DE %s.\nCADASTRO INEXISTENTE.", nomeBuscado);
			return RJjogadoresTopo;
		}
}

/*Função para sortear os jogadores*/
sort* sortearJogadores(jogadores *SJjogadoresTopo, sort *SJsorteioTopo, int SJcontJogador, int *SJnumSorteio){
	int trava=0, contador, numero, quant;/*"trava" para saber se o número sorteado foi encontrado na lista, "contador" utilizado no for como variavel de contagem, "numero" variavel que recebera o numero sorteado, "quant" quantidade de jogadores que o usuário pediu*/
	jogadores *atual;/*auxiliar*/
	atual = SJjogadoresTopo;
	
	srand(time(NULL));/*Função para poder usar o rand da biblioteca "time.h"*/
	
	if(SJsorteioTopo==NULL){/*Caso seja a primeira vez que esteja sendo feito o sorteio*/
		scanf("%d\n", &quant);
		if(SJcontJogador==0){/*Caso não haja jogadores registrados, torna invalida a chamada da função e é preciso decrementar a variavel que guarda o numero do sorteio*/
			printf("NÃO HÁ JOGADORES RESISTRADOS!");
			(*SJnumSorteio)--;
			return SJsorteioTopo;
		}
		else if(quant>SJcontJogador){/*Caso o usuario peça mais jogadores do que tem registrados*/
			printf("\n\nQUANTIDADE MÁXIMA DE JOGADORES EXCEDIDA! HÁ %d JOGADORES CADASTRADOS", SJcontJogador);
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
			trava=0;/*Reiniciando a varialvel de verificação*/
		}
		
		return SJsorteioTopo;
	}
	else{/*Caso não seja a primeira vez que esteja feito o sorteio, irá fazer as mesmas coisas descritas acima, só que com auxiliares*/
	
		scanf("%d\n", &quant);
		if(SJcontJogador==0){
			printf("NÃO HÁ JOGADORES RESISTRADOS!");
			(*SJnumSorteio)--;
			return SJsorteioTopo;
		}
		else if(quant>SJcontJogador){
			printf("\n\nQUANTIDADE MÁXIMA DE JOGADORES EXCEDIDA! HÁ %d JOGADORES CADASTRADOS", SJcontJogador);
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
	printf("\n\nFILTRO PELA POSIÇÃO");
	scanf("%[^\n]s", &nomeBuscado);
	while(atual!=NULL){
		if(strcmp(atual->posiTime, nomeBuscado)!=0)/*Caso a posição não seja encontrada*/
			verificadorDePosicao++;/*A variavel será acrementada e verificada no final da função, para saber se a posição inserida existe*/
		if(strcmp(atual->posiTime, nomeBuscado)==0 && atual->veriSorteio>0){/*Caso a posição seja encontrada e o jogador já tenha sido sorteado*/
			if(contador==0){/*Caso seja primeira vez que o laço tenha se repetido, para mostrar o escopo da função*/
				printf("\nJOGADORES SORTEADOS E QUE OCUPAM A POSIÇÃO: %s", nomeBuscado);
				printf("\n%s\t%s", atual->nomeJogador, atual->paisSelecao);
			}
			else/*Caso não seja, será exibido apenas os jogadores*/
				printf("\n%s\t%s", atual->nomeJogador, atual->paisSelecao);
			trava=1;
		}
			
		atual=atual->proxiJogador;
		contador++;
	}
	if(trava==0){/*Caso nenhum jogador tenha sido encontrado*/
		if(verificadorDePosicao==FScontJogador)/*Caso a posição não exista na lista*/
			printf("\nNÃO EXISTE A POSICAO INSERIDA: %s", nomeBuscado);
		else/*Senão será mostrado a mensagem normal*/
			printf("\nNENHUM JODAGOR SORTEADO OCUPA A POSICAO: %s", nomeBuscado);
	}
}

/*Função para exibir todos os jogadores*/
void exibirTodosJogadores(jogadores *ETJjogadoresTopo, int ETJcontJogador){
	jogadores *atual;
	atual=ETJjogadoresTopo;
	
	if(ETJcontJogador<=0){
		printf("\n\nNÃO EXISTEM JOGADORES REGISTRADOS");
	}
	else{
		printf("\n\nEXIBIÇÃO DE TODOS OS JOGADORES");
		while(atual!=NULL){/*Exibindo um jogador por vez*/
			printf("\n%s\t", atual->nomeJogador);
			printf("%d\t", atual->anoNasci);
			printf("%s\t", atual->paisSelecao);
			printf("%d\t", atual->numCamisa);
			printf("%s", atual->posiTime);
			atual=atual->proxiJogador;/*Passando para o próximo jogador*/
		}
	}	
}

/*Função para exibir todos os jogadores sorteados*/
void exibirJogadoresSorteados(int EJScontJogador, jogadores *EJSjogadoresTopo, int EJSnumSorteio, sort *EJSsorteioTopo){
	jogadores *atualJogador;
	sort *atualSorteio;
	atualSorteio=EJSsorteioTopo;
	int contador;
	
	if(EJScontJogador<=0){
		printf("\n\nNÃO EXISTEM JOGADORES REGISTRADOS");
	}
	else if(EJSsorteioTopo==NULL){
		printf("\n\nNÃO EXISTEM JOGADORES SORTEADOS");
	}
	else{
		printf("\n\nEXIBIÇÃO DE JOGADORES SORTEADOS");
		while(atualSorteio!=NULL){
			contador=0;
			atualJogador = EJSjogadoresTopo;
			while(atualJogador!=NULL){
				if(atualJogador->veriSorteio==atualSorteio->numeroDoSorteio){/*Verificando se o jogador pertence ao sorteio que está sendo testado*/
					if(contador==0){/*Caso seja a primeira vez que o laço while se repete, será mostrado o escopo da função*/
						printf("\nSORTEIO %d -> %d JOGADORES SORTEADOS", atualSorteio->numeroDoSorteio, atualSorteio->quantidadeDeSorteados);
					}
						printf("\n%s\t%s", atualJogador->nomeJogador, atualJogador->paisSelecao);
					contador++;
				}
				atualJogador=atualJogador->proxiJogador;
			}
			
			atualSorteio=atualSorteio->proxiNo;
		}
	}
}

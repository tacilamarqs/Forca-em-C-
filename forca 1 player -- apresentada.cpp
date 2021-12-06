#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

typedef struct{
    char palavra[50];
    char dica[100];
} Palavras;

typedef struct {
    int acertopartida;
    int erro;
    int partida;
} Ranking;

//ARQUIVO E FUNÇÃO SEMPRE FORA DO MAIN

FILE *arq;
FILE *pontuacao;
void menu();
void forca(int chute);
void Cadastro();
void jogar();
void ranking();
void creditos();
void tutorial(int opcao);

//entrada
int main(){
	setlocale(LC_ALL, "Portuguese");
	FILE *arq;
	menu();
	
}

void menu() {  
	
	system("cls");
	int opcao;

	printf("\n\t*************************************************\n\n");
	printf("\n\t\t   BEM-VINDO AO JOGO DA FORCA!\n\n");
	printf("\n\t*************************************************\n\n");
	
	printf("\n\n\t 1 - PARA DAR PLAY\n\t");
	printf(" 2 - TUTORIAL DE FUNCIONAMENTO DA FORCA \n\t"); // resolvido
	printf(" 3 - RANKING \n \t"); 
	printf(" 4 - CADASTRAR PALAVRA E DICA \n \t"); // resolvido
	printf(" 5 - CRÉDITOS \n \t");  // resolvido
	printf(" 6 - SAIR DO JOGO \n\n\t"); // resolvido
	printf("\n\n\t DIGITE: ");
	scanf("%d", &opcao);
	fflush(stdin);
	
	switch(opcao) {
		case 1: // ----> jogar
			printf("\n\t*************************************************\n\n");
			printf("\n\n\t\t\t O JOGO VAI COMEÇAR!\n\n\t");
			printf("\n\t*************************************************\n\n");
			Sleep(2000);
			system("cls");
			jogar();
			//menu();
			break;
		case 2: // ----> tutorial
			tutorial(opcao);
			break;
		case 3: // ----> ranking
			ranking();
			break;
		case 4: // ----> cadastro palavra e dica
			FILE *arq;	
			Cadastro();
			menu();
			break;
		case 5: // ----> créditos
			creditos();
			Sleep(5000);
			menu();
			break;
		case 6: // ----> tutorial
			printf("\n\t OPS! VOCÊ SAIU DO JOGO!");
			system("cls");
		default: 
			printf("\n\tENTRADA INVÁLIDA!\n");
			Sleep(1000); // se não colocar tempo some mto rápido 
			menu();
	} 
}

void jogar() {
	
	char dica[50], palavra[100], *palavrafgets, *dicafgets;
	int tentativas = 5, acertou = 0, tamanhopalavra = 0, erros = 0, i;
	char tela [50];
	Palavras p;
	Ranking r;
  	FILE *arq;

	arq = fopen ("palavraedica.txt", "r"); 
	
	if (arq == NULL) { //tratamento de erro de arquivo
	 	printf("Problemas na abertura do arquivo\n");
	 	return;
	}
	
	palavrafgets = fgets(p.palavra, 100, arq);  
	dicafgets = fgets(p.dica, 100, arq);
	
	strcpy(tela, palavrafgets); // FAZ UMA COPIA PARA A STRING TELA
	
	tela[strlen(tela)-1]='\0'; //
	
	tamanhopalavra = strlen(tela);
	
	for(i = 0; i < strlen(tela); i++) {
		tela[i]='_'; // tentando preencher com os tracinhos _ //DEU CERTO FINALMENTE
	}
	
		printf("\n\tA PALAVRA TEM %d letras!\n\n", strlen(tela));
		printf("\n\tA DICA É: %s\n\n", dicafgets);

	while(acertou != tamanhopalavra) {
		forca(erros);
		int chute = 1;
		char letra;
		
		printf("\n\t");
		
		for(i=0; i<strlen(tela); i++) { 
		
			//para que haja espaço entre os _
			printf("%c ", tela[i]);
		}
		
		printf("\n\n\n\tDIGITE UMA LETRA: ");
		scanf(" %c", &letra);
	
		//verificar se a letra esta correto
		for(i=0;i<strlen(tela); i++) {
			
			if(letra==palavrafgets[i]) {
				
				tela[i] = letra;
				chute = 0; //chute igual a 0 comprova que ele não errou, entao a forca imprime
				acertou++;
			}	
		}
		
		//incrementa erro
		if(chute == 1) {
			erros++;
		}
		if(erros == 6){
			
			forca(erros);
			break;
		}	
		else if(acertou == tamanhopalavra) {
			
			system("cls");
			printf("\n\tVOCÊ GANHOU! PARABÉNS!\n\n");
			printf("A PALAVRA SECRETA É %s", palavrafgets);
			printf("\n\nRETORNANDO AO MENU...");
			Sleep(3000);
			menu();
			r.acertopartida = acertou;
			r.partida++;
			r.erro = erros;
			break;
		}
	}
	FILE * pontuacao;
	pontuacao = fopen("ranking.txt", "r+");
	
	fscanf(pontuacao, "%d", r.acertopartida);
	fscanf(pontuacao, "%d", r.partida);
	fscanf(pontuacao, "%d", r.erro);
	
	fclose(pontuacao);
}


void tutorial(int opcao) {
	
		printf("\n\n\t OLÁ JOGADOR! QUER SABER UM POUCO MAIS SOBRE O JOGO DA FORCA? \n");
		printf("\n\n\t O jogo da forca é um jogo em que o jogador tem que acertar qual é a palavra proposta,");
		printf("\n\t tendo como dica o número de letras e o tema ligado à palavra. \n\n\t A cada letra errada, é desenhado uma parte do corpo do enforcado. ");
		printf("\n\n\t O jogo termina ou com o acerto da palavra ou com o \n\t término do preenchimento das partes corpóreas do enforcado. \n\n");
		printf("\n\t 1 - MENU \n\t 2 - SAIR DO JOGO \n\n\t DIGITE: ");
		printf("\t ");
		
		scanf("%d", &opcao);
		fflush(stdin);
	
		if(opcao == 1) {
			menu();
		} else {
			printf("\n\t OPS! VOCÊ SAIU DO JOGO!");
			system("cls");
		}
}

void ranking() { 
	char resposta;

	Ranking r;
	FILE *pontuacao;

	pontuacao = fopen("ranking.txt", "r+");
	
	fprintf(pontuacao, "\n\tNA %d PARTIDA O JOGADOR TEVE %d ACERTOS E %d ERROS\n", r.partida, r.acertopartida, r.erro);
  	fclose(pontuacao);

	system("cls");	
	printf("\n ************************************************************ \n");
	printf("\n\n\t\t\t  RANKING  \n\n");
	printf("\n ************************************************************ \n");
	
	printf("\n\tNA %d PARTIDA O JOGADOR TEVE %d ACERTOS E %d ERROS\n\n", r.partida, r.acertopartida, r.erro);
	
	printf("\n\nDIGITE 's' PARA VOLTAR O MENU OU 'n' PARA SAIR DO JOGO: \t");
		scanf(" %c", &resposta);
		
		if(resposta == 's' || resposta == 'S') {
			menu();
		} else {
			exit(0);
		}
} 

void Cadastro(){
	
	Palavras p;
	FILE *arq;
	//char palavra[50];
	int i = 0, opcao;
	
	system("cls");
	printf("\n\tPalavra: ");
	fgets(p.palavra,sizeof(p.palavra),stdin);
	fflush(stdin);
	
	printf("\npalavra cadastrada: %s", p.palavra);	
	
	printf("\n\tDica: ");
	fgets(p.dica,sizeof(p.dica),stdin);
	fflush(stdin);
	
	printf("\ndica cadastrada: %s", p.dica);
		
	arq = fopen ("palavraedica.txt", "w+"); //Abre para leitura e escrita. O arquivo é criado se não existir. O fluxo é posicionado no fim do arquivo
	
	if(arq == NULL){
		printf("Erro na abertura do arquivo.");
		system("pause");
		exit(1); //aborta programa
	}
	
	fprintf(arq, p.palavra);
	fprintf(arq, p.dica);
	fflush(arq); //limpa os bunkers
	fclose(arq); // fecha arquivo
	Sleep(1000); // se tirar sai muito rapido 

	printf("\n\n\tDeseja cadastrar outra palavra?\n\n");
	printf("\n\t1- SIM \t 2 - NÃO\n\n\t");
	scanf("%d", &opcao);
	fflush(stdin);
	
	if(opcao == 1) {
		Cadastro();
	} else {
		menu();
	}
}

void creditos() {

	printf("\n\n\tCRÉDITOS DO PROJETO:");
	printf("\n\n\t- GABRIELA BORGES DOS SANTOS");
	printf("\n\t- TÁCILA COSTA MARQUES");
	printf("\n\t- VICTOR NERY ");

}

	
void forca(int erros){
	switch(erros) {
	
			case 0:
					printf("\n\n\tBOA SORTE!!! hahaha >:D \n");
					printf("\t_________ \n");
					printf("\t|       |\n");
					printf("\t|    \n");
					printf("\t|    \n");
					printf("\t|    \n");
					printf("\t|         \n ");
					printf("\n\n");
					Sleep(1000);
					break;
				
			case 1:
					printf("\n\n\tOPS! VOCÊ JÁ ERROU\n\tRESTAM 5 TENTATIVAS!\n");
					printf("\t_________\n ");
					printf("\t|       O\n");
					printf("\t|         \n");
					printf("\t|         \n");
					printf("\t|         \n");
					printf("\t|         \n ");
					printf("\n\n");
					Sleep(1000);
					break;
				
			case 2:
					printf("\n\n\tVOCÊ ERROU DE NOVO!\n\tRESTAM 4 TENTATIVAS!\n");
					printf("\t_________\n ");
					printf("\t|       O\n");
					printf("\t|       |\n");
					printf("\t|         \n");
					printf("\t|         \n");
					printf("\t|         \n ");
					printf("\n\n");
					Sleep(1000);
					break;
				
			case 3:
					printf("\n\n\tVOCÊ ERROU DE NOVO\n\tRESTAM 3 TENTATIVAS!\n");
					printf(" \t_________ \n");
					printf("\t|        O\n");
					printf("\t|       <|\n");
					printf("\t|    \n");
					printf("\t|    \n");
					printf("\t|         \n ");
					printf("\n\n");
					Sleep(1000);
					break;
				
			case 4:
					printf("\n\n\tSERÁ QUE AINDA TEM SALVAÇÃO????\n\tRESTAM 2 TENTATIVAS!\n");
					printf("\t_________\n ");
					printf("\t|       O\n");
					printf("\t|      <|>\n");
					printf("\t|          \n");
					printf("\t|         \n ");
					printf("\t|         \n ");
					printf("\n\n");
					Sleep(1000);	
					break;
				
			case 5:
					printf("\n\n\tA SITUAÇÃO TÁ COMPLICADA, EIN? \n\tERROU MAIS UMA VEZ!\n\tRESTA 1 TENTATIVA!\n");
					printf("\t_________ \n");
					printf("\t|       O\n");
					printf("\t|      <|>\n");
					printf("\t|      I  \n");
					printf("\t|          \n");
					printf("\t|         \n ");
					Sleep(1000);	
					break;
				
			case 6:
					
					printf("\n\n\tOH NÃO!!!! \n\tVOCÊ MORREU! :/ \n\tBOA SORTE NA PRÓXIMA!\n\n");
					printf("\t _________ \n");
					printf("\t|        O\n");
					printf("\t|       <|>\n");
					printf("\t|       I I \n");
					printf("\t|          \n");
					printf("\t|         \n ");
					Sleep(5000);	
					break;
				}
}

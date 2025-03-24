 //Bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <windows.h>

const int MAX=50;
int ordenado=0;

// Escopo de fun��es
typedef struct TProduto {
    long int codigo;
    char grupo[30];          
    char descricao[41];   
    char unidade[3];        
    char fornecedor[41];
	int quantidade;    
    float pr_compra;      
    float pr_venda;     
    float lucro_minimo;      
    int quantidade_minima;  
} TProduto;

void leitura(TProduto estoque[], int *tamanho); 
void gravacao(TProduto estoque[], int tamanho);
void cadastrar(TProduto estoque[], int *tamanho);
void excluir(TProduto estoque[], int *tamanho);  
void editar(TProduto estoque[], int tamanho);
int vazio(int tamanho);
int pesquisabinaria(TProduto estoque[], int chave, int tamanho);
void mostra(TProduto estoque[], int chave);
void classifica(TProduto estoque[], int tamanho);
void MenuPrincipal();
void BoasVindas();
void lista_precos(TProduto estoque[], int tamanho);
void relatorio_produtos(TProduto estoque[], int tamanho);
void aumento_preco_fornecedor(TProduto estoque[], int tamanho);
void relatorio_produtos_por_fornecedor(TProduto estoque[], int tamanho);

//Fun��o que verifica c�digos duplicados
int verificar_codigo_duplicado(TProduto estoque[], int tamanho, long int codigo) {
    for (int i = 0; i < tamanho; i++) { 
        if (estoque[i].codigo == codigo) {
            return 1; 
        }
    }
    return 0; 
}

//Main
int main() {
    MenuPrincipal();
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////

// Fun��es de cores
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_CYAN (FOREGROUND_BLUE | FOREGROUND_GREEN) 

void setarCor(int cor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, cor);
}

void resetarCor() {
    setarCor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
}

/////////////////////////////////////////////////////////////////////////////////////

//Fun��es

//Menu de Boas Vindas (Antecede o menu principal)
void BoasVindas() {
	setlocale(LC_ALL, "Portuguese");
    system("cls"); //limpa a tela
    setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("=================================================================================================\n");
    resetarCor();

    setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
    printf("\tBEM-VINDO(A) AO SISTEMA DE CONTROLE DE ESTOQUE PARA MEC�NICAS AUTOMOTIVAS (SCEMA)\n");
    resetarCor();

    setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("=================================================================================================\n\n");
    resetarCor();
	
    setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
    printf("\n\t\t\t\tPressione ENTER para iniciar o menu...\n");
    resetarCor();

    fflush(stdin); 
    getchar();     //espera o usuario pressionar ENTER
    system("cls"); //limpa a tela
}

//Menu Principal (Se encontram as fun��es principais)
void MenuPrincipal() {
	BoasVindas();
    TProduto estoque[MAX]; 
    int tamanho = 0, opcao;
    
    leitura(estoque, &tamanho); 
    setlocale(LC_ALL, "Portuguese");
    
    do {
    	setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    	printf("=================================================================================================\n");
    	resetarCor();
    	
    	setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);	
		printf("\t\tSISTEMA DE CONTROLE DE ESTOQUE PARA MEC�NICAS AUTOMOTIVAS (SCEMA)\n");
		resetarCor();
		
		setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);						
		printf("=================================================================================================\n");
		resetarCor();
		
		printf("\n Escolha uma op��o para continuar:\n\n");
		setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf("=================================================================================================\n");
		resetarCor();
		
		setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY); //todas as fun��es do menu
		printf(" 1 - INCLUIR NOVO PRODUTO\n");
		printf(" 2 - EXCLUIR PRODUTO REGISTRADO\n");
		printf(" 3 - EDITAR PRODUTO REGISTRADO\n");
		printf(" 4 - LISTA DE PRE�OS\n");
		printf(" 5 - RELAT�RIO DE PRODUTOS\n"); 
		printf(" 6 - AUMENTAR PRE�O DE COMPRA POR FORNECEDOR\n");  
		printf(" 7 - RELAT�RIO DE PRODUTOS POR FORNECEDOR\n");  
		printf(" 0 - SAIR\n");
		resetarCor();
		setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf("=================================================================================================\n");
		resetarCor();
		
		printf("\n Digite o n�mero da op��o desejada: "); 
		resetarCor();
		
        scanf("%d", &opcao);
        system("cls"); 

        switch (opcao) { //switch case das op��es do menu
            case 1: { //op��o de cadastro
                cadastrar(estoque, &tamanho); 
                gravacao(estoque, tamanho); 
                break;
            }
            case 2: { //op��o de exclus�o
                excluir(estoque, &tamanho); 
                gravacao(estoque, tamanho); 
                break;
            }
            case 3: { //op��o de edi��o
                editar(estoque, tamanho);
                gravacao(estoque, tamanho); 
                break;
            }
            case 4: { //op��o de lista de pre�os
                lista_precos(estoque, tamanho); 
                break;
            }
            case 5: { //op��o de relat�rios
                relatorio_produtos(estoque, tamanho); 
                break;
            }
            case 6: { //op��o de aumento de pre�o de produtos por fornecedor
                aumento_preco_fornecedor(estoque, tamanho); 
                gravacao(estoque, tamanho);  
                break;
            }
            case 7: { //op��o de relat�rio de produtos por fornecedor
                relatorio_produtos_por_fornecedor(estoque, tamanho);  
                break;
            }
            case 0: { //se escolhida a op��o 0 (encerrar o sistema)
            system("cls");
            
			setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    		printf("=================================================================================================\n");
    		resetarCor();
    	
    		setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);	
			printf("\t\tSISTEMA DE CONTROLE DE ESTOQUE PARA MEC�NICAS AUTOMOTIVAS (SCEMA)\n");
			resetarCor();
		
			setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);						
			printf("=================================================================================================\n");
			resetarCor();
				
				setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);	
                printf("\n O PROGRAMA FOI FINALIZADO COM SUCESSO!\n");
                resetarCor();
                
				exit(0);
                break;
        }
            default: //se escolhida uma op��o inv�lida 
	            system("cls");
					
	            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		    	printf("=================================================================================================\n");
		    	resetarCor();
		    	
		    	setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);	
				printf("\t\tSISTEMA DE CONTROLE DE ESTOQUE PARA MEC�NICAS AUTOMOTIVAS (SCEMA)\n");
				resetarCor();
				
				setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);						
				printf("=================================================================================================\n");
				resetarCor();
				
				setarCor(FOREGROUND_RED);	
				printf("\n OP��O INV�LIDA! Voltando ao menu...\n\n");
				resetarCor();
				
				printf(" Aperte ENTER para retornar ao menu...");
				fflush(stdin);
				getchar();
				system("cls");
            break;
        }
    } while (opcao != 0); 
}

//Fun��o que cadastra os produtos
void cadastrar(TProduto estoque[], int *tamanho) {
    setlocale(LC_ALL, "Portuguese");
    if (*tamanho == MAX) {
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY); 
        printf("\n ERRO! \n ARQUIVO CHEIO.\n"); //informa se o .dat estiver cheio
        resetarCor();
        return;
    }

    TProduto aux;
    char correto = 'n';
    int codigo_duplicado; 

    while (1) { //apresenta o menu de cadastro
        do {
            system("cls"); 
            
            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("=============================================================================\n");
            resetarCor();
            
            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);  
            printf("\t\t\tMENU DE INCLUS�O DE PRODUTOS\n");
            resetarCor();
            
            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);                     
            printf("=============================================================================\n");
            resetarCor();

            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY); 
            printf("\n Digite o c�digo do novo produto ..............................: ");
            scanf("%ld", &aux.codigo);
            getchar();  

            codigo_duplicado = verificar_codigo_duplicado(estoque, *tamanho, aux.codigo); //puxa a fun��o que checa se o c�digo n�o � duplicado

            if (codigo_duplicado) { //se duplicado, consta
            	
                setarCor(FOREGROUND_RED); 
                printf("\n ERRO! O C�DIGO \"%ld\" J� EST� CADASTRADO.\n", aux.codigo);
                resetarCor();
                
                setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY); 
                printf("\n Por favor, informe um c�digo diferente...\n\n");
                resetarCor();
                
                printf("\n Aperte ENTER para informar outro c�digo");
                getchar();
            }
        } while (aux.codigo <= 0 || codigo_duplicado); //se n�o duplicado, continua

        system("cls"); //limpa a tela anterior com o objetivo de manter o padr�o no menu

	        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	        printf("=============================================================================\n");
	        resetarCor();
	        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);  
	        printf("\t\t\tMENU DE INCLUS�O DE PRODUTOS\n");
	        resetarCor();
	        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);                     
	        printf("=============================================================================\n");
	        resetarCor();
	
	        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
	        printf("\n C�digo ...............................: %ld\n", aux.codigo); //re-apresenta o c�digo informado pelo usuario
	        resetarCor();  
	
        do { 
            setarCor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printf(" Quantidade do produto ................: ");
            scanf("%i", &aux.quantidade);
            getchar(); 
        } while (aux.quantidade < 0);

        do {
            printf(" Grupo do produto .....................: ");
            scanf("%29s", aux.grupo);
            getchar();
        } while (aux.grupo[0] == '\0');

        do {
            printf(" Descri��o do produto .................: ");
            scanf("%99[^\n]", aux.descricao);
            getchar();
        } while (aux.descricao[0] == '\0');

        do {
            printf(" Unidade (KG, PC, UN) .................: ");
            scanf("%19s", aux.unidade);
            getchar();
        } while (aux.unidade[0] == '\0');

        do {
            printf(" Fornecedor do produto ................: ");
            scanf("%99[^\n]", aux.fornecedor);
            getchar();
        } while (aux.fornecedor[0] == '\0');

        do {
            printf(" Pre�o de compra ......................: ");
            scanf("%f", &aux.pr_compra);
            getchar();
        } while (aux.pr_compra < 0);

        do {
            printf(" Pre�o de venda .......................: ");
            scanf("%f", &aux.pr_venda);
            getchar();
        } while (aux.pr_venda < 0);

        do {
            printf(" Lucro m�nimo em porcentagem ..........: ");
            scanf("%f", &aux.lucro_minimo);
            getchar();
        } while (aux.lucro_minimo < 0);

        do {
            printf(" Quantidade m�nima em estoque .........: ");        
            scanf("%d", &aux.quantidade_minima);
            getchar();
        } while (aux.quantidade_minima < 0);

		resetarCor();
		
        printf("\n Os dados informados est�o corretos? (S/N): "); //questiona o usuario se os dados informados est�o corretos
        correto = getchar();
        getchar(); 

        system("cls");

        if (correto == 's' || correto == 'S') { //se sim, informa a inclus�o do produto
            estoque[*tamanho] = aux;
            (*tamanho)++;

            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("=============================================================================\n");
            resetarCor();
            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);  
            printf("\t\t\tMENU DE INCLUS�O DE PRODUTOS\n");
            resetarCor();
            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);                     
            printf("=============================================================================\n");
            resetarCor();

            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
            printf("\n O PRODUTO FOI INCLU�DO COM SUCESSO!\n");
            resetarCor();
            break;  
        } else { //se n�o, informa o cancelamento do cadastro
        	
        	setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("=============================================================================\n");
            resetarCor();
            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);  
            printf("\t\t\tMENU DE INCLUS�O DE PRODUTOS\n");
            resetarCor();
            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);                     
            printf("=============================================================================\n");
            resetarCor();
            setarCor(FOREGROUND_RED); 
            
            printf("\n Cadastro cancelado. Voltando ao menu...\n");
            resetarCor();
            break;  
        }
    }
 
    printf("\n Aperte ENTER para retornar ao menu");  
    getchar(); //aguarda o ENTER
    system("cls"); //limpa a tela
}

//Fun��o que exclui produtos
void excluir(TProduto estoque[], int *tamanho) {
    setlocale(LC_ALL, "Portuguese");

    if (*tamanho == 0) { //se registro estiver vazio
        system("cls");
        
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("=============================================================================\n");
        resetarCor();
        
        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
        printf("\t\t\tMENU DE EXCLUS�O DE PRODUTOS\n");
        resetarCor();
        
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("=============================================================================\n");
        resetarCor();
        
        setarCor(FOREGROUND_RED);
        printf("\n REGISTRO VAZIO!\n\n(N�o h� itens a serem exclu�dos)\n\n");
        resetarCor();
        
        printf("\n Aperte ENTER para retornar ao menu");
        getchar();
        system("cls");
        return;
    }

    int posicao, i;
    long int codigo; 
    char confirma = 'n';

    while (1) { 
        system("cls");
        
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("=============================================================================\n");
        resetarCor();
        
        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
        printf("\t\t\tMENU DE EXCLUS�O DE PRODUTOS\n");
        resetarCor();
        
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("=============================================================================\n");
        resetarCor();

		setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
        printf("\n Digite o c�digo do produto a ser exclu�do......: "); //requisita o codigo do produto que o usuario quer excluir
        resetarCor();
        scanf("%ld", &codigo);
        fflush(stdin); 

        posicao = pesquisabinaria(estoque, codigo, *tamanho); 

        if (posicao >= 0) { 
            system("cls");
            
            setarCor(FOREGROUND_RED| FOREGROUND_INTENSITY);
            printf("=============================================================================\n");
            resetarCor();
            
            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
            printf("\t\t\tMENU DE EXCLUS�O DE PRODUTOS\n");
            resetarCor();
            
            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("=============================================================================\n");
            resetarCor();
            
            setarCor(FOREGROUND_YELLOW| FOREGROUND_INTENSITY);
            printf("\n Produto encontrado:\n"); //informa que o produto foi encontrado
            resetarCor();
            mostra(estoque, posicao);

            printf("\n Confirmar a exclus�o do registro desse produto? (S/N) "); //questiona a certeza do usuario sobre sua escolha
            fflush(stdin); 
            confirma = getchar();
            fflush(stdin);

            if (confirma == 's' || confirma == 'S') { //se sim, exclui o produto e informa o usuario
                for (i = posicao; i < (*tamanho) - 1; i++) 
                    estoque[i] = estoque[i + 1];
                (*tamanho)--;

                system("cls");
                setarCor(FOREGROUND_RED| FOREGROUND_INTENSITY);
                printf("=============================================================================\n");
                resetarCor();
                
                setarCor(FOREGROUND_YELLOW| FOREGROUND_INTENSITY);
                printf("\t\t\tMENU DE EXCLUS�O DE PRODUTOS\n");
                resetarCor();
                
                setarCor(FOREGROUND_RED| FOREGROUND_INTENSITY);
                printf("=============================================================================\n");
                resetarCor();
                
                setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                printf("\n REGISTRO REMOVIDO COM SUCESSO!\n\n");
                resetarCor();
                break;
            } else { //se n�o, informa que o produto n�o foi excluido
                system("cls");
                
                setarCor(FOREGROUND_RED| FOREGROUND_INTENSITY);
                printf("=============================================================================\n");
                resetarCor();
                
                setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                printf("\t\t\tMENU DE EXCLUS�O DE PRODUTOS\n");
                resetarCor();
                
                setarCor(FOREGROUND_RED| FOREGROUND_INTENSITY);
                printf("=============================================================================\n");
                resetarCor();
                
                setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                printf("\n O REGISTRO N�O FOI EXCLU�DO!\n\n");
                resetarCor();
                break;
            }
        } else { //se o produto n�o for encontrado
            system("cls");
            
            setarCor(FOREGROUND_RED| FOREGROUND_INTENSITY);
            printf("=============================================================================\n");
            resetarCor();
            
            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
            printf("\t\t\tMENU DE EXCLUS�O DE PRODUTOS\n");
            
            setarCor(FOREGROUND_RED| FOREGROUND_INTENSITY);
            printf("=============================================================================\n");
            resetarCor();
            
            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
            printf("\n O REGISTRO N�O FOI LOCALIZADO!\n\n");
            resetarCor();
        }

        printf("\n Deseja tentar novamente? (S/N): "); //questiona se o usuario deseja tentar novamente
        confirma = getchar();
        fflush(stdin);
        if (confirma != 's' && confirma != 'S') { //se sim, retorna a escolha, se n�o, volta ao menu
            break;
        }
    }

    printf("\n Aperte ENTER para retornar ao menu");
    getchar(); //aguarda o ENTER
    system("cls"); //limpa a tela
    return;
}

//Fun��o que edita produtos
void editar(TProduto estoque[], int tamanho) {
    setlocale(LC_ALL, "Portuguese");

    if (tamanho == 0) { //se o registro estiver vazio
        system("cls");
        
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("=============================================================================\n");
        resetarCor();
        
        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
        printf("\t\t\tMENU DE EDI��O DE PRODUTOS\n");
        resetarCor();
        
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("=============================================================================\n");
        resetarCor();
        
        setarCor(FOREGROUND_RED);
        printf("\n REGISTRO VAZIO!\n\n");
        resetarCor();
        
        printf(" Aperte ENTER para retornar ao menu");
        getchar();
        getchar();
        system("cls");
        return;
    }

    long int codigo;
    int posicao, opcao;
    char confirma = 'n';

    while (1) { 
        system("cls");
        
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("=============================================================================\n");
        resetarCor();
        
        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
        printf("\t\t\tMENU DE EDI��O DE PRODUTOS\n");
        resetarCor();
        
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("=============================================================================\n");
		resetarCor();
		
		setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
        printf("\n Digite o c�digo do produto a ser editado: "); //requisita o codigo do produto a ser editado
        resetarCor();
        
        scanf("%ld", &codigo);
        fflush(stdin);

        posicao = pesquisabinaria(estoque, codigo, tamanho);

        if (posicao >= 0) {
            system("cls");
            
            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("=============================================================================\n");
            resetarCor();
            
            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
            printf("\t\t\tMENU DE EDI��O DE PRODUTOS\n");
            resetarCor();
            
            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("=============================================================================\n");
            resetarCor();
            
            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
            printf("\n Produto encontrado:\n"); //informa o produto
            resetarCor();
            mostra(estoque, posicao);

            printf("\n Deseja editar este produto? (S/N): "); //questiona a certeza do usuario sobre sua escolha
            confirma = getchar();
            fflush(stdin);

            if (confirma == 's' || confirma == 'S') { //se sim, continua
                while (1) {
                    system("cls");
                    
                    setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("=============================================================================\n");
                    resetarCor();
                    
                    setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                    printf("\t\t\tMENU DE EDI��O DE PRODUTOS\n");
                    resetarCor();
                    
                    setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("=============================================================================\n");
                    resetarCor();
                    
                    setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                    printf("\n Produto selecionado:\n");
                    resetarCor();
                    mostra(estoque, posicao);
					
					setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                    printf("\n Escolha a op��o que deseja editar:\n\n"); //permite o usuario editar 3 informa��es principais do produto: Quantidade; Valor; Descri��o (Nome), ou voltar ao menu principal
                    printf(" 1 - Editar quantidade\n");
                    printf(" 2 - Editar valor\n");
                    printf(" 3 - Editar descri��o\n\n");
                    printf(" 0 - Voltar para o menu principal\n");
                    resetarCor();
                    
                    printf("\n Digite a op��o desejada: ");
                    scanf("%d", &opcao);
                    fflush(stdin);

                    switch (opcao) { //se escolhida a op��o 1
                        case 1: {
                            system("cls");
                            
                            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                            printf("=============================================================================\n");
                            resetarCor();
                            
                            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                            printf("\t\t\tMENU DE EDI��O DE PRODUTOS\n");
                            resetarCor();
                            
                            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                            printf("=============================================================================\n");
                            resetarCor();
                            
                            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                            printf("\n Produto selecionado:\n");
                            resetarCor();
                            mostra(estoque, posicao);

                            printf("\n Digite a nova quantidade do produto: "); //pede para o usuario informar uma nova quantidade
                            scanf("%d", &estoque[posicao].quantidade);
                            fflush(stdin);

                            system("cls");
                            
                            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                            printf("=============================================================================\n");
                            resetarCor();
                            
                            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                            printf("\t\t\tMENU DE EDI��O DE PRODUTOS\n");
                            resetarCor();
                                  
                            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                            printf("=============================================================================\n");
                            resetarCor();
                            
                            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                            printf("\n Quantidade atualizada com sucesso!\n"); //informa que deu certo
                            resetarCor();
                            
                            printf("\n Aperte ENTER para retornar a editar o produto selecionado"); //requisita que o usuario aperte ENTER para continuar a editar os proximos produtos
                            getchar();
                            break;
                        }
                        case 2: { //se escolhida a op��o 2
                            system("cls");
                            
                            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                            printf("=============================================================================\n");
                            resetarCor();
                            
                            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                            printf("\t\t\tMENU DE EDI��O DE PRODUTOS\n");
                            resetarCor();
                            
                            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                            printf("=============================================================================\n");
                            resetarCor();
                            
                            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                            printf("\n Produto selecionado:\n");
                            resetarCor();
                            mostra(estoque, posicao);

                            printf("\n Digite o novo pre�o de venda do produto: "); //pede para o usuario informar um novo valor
                            scanf("%f", &estoque[posicao].pr_venda);
                            fflush(stdin);

                            system("cls");
                            
                            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                            printf("=============================================================================\n");
                            resetarCor();
                            
                            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                            printf("\t\t\tMENU DE EDI��O DE PRODUTOS\n");
                            resetarCor();
                            
                            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                            printf("=============================================================================\n");
                            resetarCor();
                            
                            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                            printf("\n Valor atualizado com sucesso!\n"); //informa que deu certo
                            resetarCor();
                            
                            printf("\n Aperte ENTER para retornar a editar o produto selecionado"); //requisita que o usuario aperte ENTER para continuar a editar os proximos produtos
                            getchar();
                            break;
                        }
                        case 3: { //se escolhida a op��o 3
                            system("cls");
                            
                            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                            printf("=============================================================================\n");
                            resetarCor();
                            
                            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                            printf("\t\t\tMENU DE EDI��O DE PRODUTOS\n");
                            resetarCor();
                            
                            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                            printf("=============================================================================\n");
                            resetarCor();
                            
                            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                            printf("\n Produto selecionado:\n");
                            resetarCor();
                            mostra(estoque, posicao);

                            printf("\n Digite a nova descri��o do produto: "); //pede para o usuario informar uma nova descri��o
                            scanf("%49[^\n]", estoque[posicao].descricao);
                            fflush(stdin);

                            system("cls");
                            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                            printf("=============================================================================\n");
                            resetarCor();
                            
                            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                            printf("\t\t\tMENU DE EDI��O DE PRODUTOS\n");
                            resetarCor();
                            
                            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                            printf("=============================================================================\n");
                            resetarCor();
                            
                            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                            printf("\n Descri��o atualizada com sucesso!\n"); //informa que deu certo
                            resetarCor();
                            
                            printf("\n Aperte ENTER para retornar a editar o produto selecionado"); //requisita que o usuario aperte ENTER para continuar a editar os proximos produtos
                            getchar();
                            break;
                        }
                        case 0: { //se escolhida a op��o 0
                            system("cls");
                      
                            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                            printf("=============================================================================\n");
                            resetarCor();
                            
                            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                            printf("\t\t\tMENU DE EDI��O DE PRODUTOS\n");
                            resetarCor();
                            
                            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                            printf("=============================================================================\n");
                            resetarCor();
                            
                            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                            printf("\n Voltando ao menu principal...\n\n"); //informa o retorno ao menu principal
                            resetarCor();
                            
                            printf("\n Aperte ENTER para retornar ao menu\n");
                            getchar(); //aguarda o ENTER
                            system("cls"); //limpa a tela
                            return;
                        }
                        default: {
                            system("cls");
                            
                            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                            printf("=============================================================================\n");
                            resetarCor();
                            
                            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                            printf("\t\t\tMENU DE EDI��O DE PRODUTOS\n");
                            resetarCor();
                            
                            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                            printf("=============================================================================\n");
                            resetarCor();
                            
                            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                            printf("\n Op��o inv�lida! Tente novamente.\n");
                            resetarCor();
                            getchar();
                            break;
                        }
                    }
                }
            } else {
                system("cls");
                
                setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("=============================================================================\n");
                resetarCor();
                
                setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                printf("\t\t\tMENU DE EDI��O DE PRODUTOS\n");
                resetarCor();
                
                setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("=============================================================================\n");
                resetarCor();
                
                setarCor(FOREGROUND_RED);
                printf("\n Edi��o cancelada. Voltando ao menu principal...\n");
                resetarCor();
                getchar();
                system("cls");
                return;
            }
        } else {
            system("cls");
            
            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("=============================================================================\n");
            resetarCor();
            
            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
            printf("\t\t\tMENU DE EDI��O DE PRODUTOS\n");
            resetarCor();
            
            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("=============================================================================\n");
            resetarCor();
            
            setarCor(FOREGROUND_RED);
            printf("\n Produto n�o encontrado.\n");
            resetarCor();
            
            printf("\n Deseja tentar novamente? (S/N): ");
            confirma = getchar();
            fflush(stdin);

            if (confirma != 's' && confirma != 'S') {
                system("cls");
                
                setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("=============================================================================\n");
                resetarCor();
                
                setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                printf("\t\t\tMENU DE EDI��O DE PRODUTOS\n");
                resetarCor();
                
                setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("=============================================================================\n");
                resetarCor();
                
                setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                printf("\n Voltando ao menu principal...\n");
                resetarCor();
                getchar();
                system("cls");
                return;
            }
        }
    }
}

//Fun��o que l� o .dat
void leitura(TProduto estoque[], int *tamanho) {
	setlocale(LC_ALL, "Portuguese");
    FILE *arquivo;
    arquivo = fopen("estoque.dat", "a+b"); 
    if (!arquivo) {
        printf(" Erro ao abrir arquivo!");
        return;
    }

    while (fread(&estoque[*tamanho], sizeof(TProduto), 1, arquivo) == 1) {
        (*tamanho)++;
    }

    fclose(arquivo);
}

//Fun��o que grava no .dat 
void gravacao(TProduto estoque[], int tamanho) {
	setlocale(LC_ALL, "Portuguese");
    FILE *arquivo;
    arquivo = fopen("estoque.dat", "wb"); 
    if (!arquivo) {
        printf(" Erro ao abrir arquivo para grava��o!");
        return;
    }

    fwrite(estoque, sizeof(TProduto), tamanho, arquivo);

    fclose(arquivo);
}

//Fun��o que apresenta um dos menus
void mostra(TProduto estoque[], int chave) {
	setlocale(LC_ALL, "Portuguese");
	
	setarCor(FOREGROUND_YELLOW| FOREGROUND_INTENSITY);
    printf("\n C�digo...............................: %ld\n", estoque[chave].codigo);
    printf(" Quantidade...........................: %i\n", estoque[chave].quantidade);
    printf(" Descri��o................................: %s\n", estoque[chave].descricao);
    printf(" Valor................................: %.2f\n\n", estoque[chave].pr_venda);
    resetarCor();
}

//Fun��o da pesquisa bin�ria
int pesquisabinaria(TProduto estoque[], int chave, int tamanho) {
    static int ordenado = 0;  

    if (vazio(tamanho))
        return -1;

    if (!ordenado) {
        classifica(estoque, tamanho);
        ordenado = 1;
    }

    int inicio = 0, final = tamanho - 1, meio;

    while (inicio <= final) {
        meio = (inicio + final) / 2;
        if (estoque[meio].codigo == chave)
            return meio;

        if (estoque[meio].codigo < chave)
            inicio = meio + 1;
        else
            final = meio - 1;
    }
    return -1;
}

//Fun��o que checa se o .dat est� vazio
int vazio(int tamanho) {
    if (tamanho == 0) {
        printf("\nREGISTRO VAZIO!\n");
        return 1;
    }
    return 0;
}

//Fun��o que classifica os produtos no vetor
void classifica(TProduto estoque[], int tamanho) { 
    int i, j;
    TProduto aux;
    for (i = 0; i < tamanho - 1; i++)
        for (j = i + 1; j < tamanho; j++)
            if (estoque[i].codigo > estoque[j].codigo) {
                aux = estoque[i];
                estoque[i] = estoque[j];
                estoque[j] = aux;
            }
}

//Fun��o de lista de pre�os de produtos
void lista_precos(TProduto estoque[], int tamanho) {
    setlocale(LC_ALL, "Portuguese");
    int i = 0;
    char tecla;

    if (tamanho == 0) { //se n�o houver produtos cadastrados
    	
		setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("=============================================================================\n");
        resetarCor();
        
        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
        printf("\t\t\tMENU DE LISTA DE PRE�O DE PRODUTOS\n");
        resetarCor();
        
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("=============================================================================\n");
        resetarCor();
        
    	setarCor(FOREGROUND_RED);
        printf("\n Nenhum produto cadastrado.\n\n");
        resetarCor();
        
        fflush(stdin); //limpa buffer
        printf(" Aperte ENTER para retornar ao menu");
        getchar(); //aguarda o ENTER  
        system("cls"); 
        return;
    }

    while (1) { //apresenta a lista de pre�os
        system("cls");
        
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("=============================================================================\n");
        resetarCor();
        
        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
        printf("\t\t\tMENU DE LISTA DE PRE�O DE PRODUTOS\n");
        resetarCor();
        
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("=============================================================================\n\n");
        resetarCor();

	
        for (int j = 0; j < 2 && (i + j) < tamanho; j++) {
        	
        	setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        	printf("=============================================================================\n");
        	resetarCor();
        	
        	setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
            printf("\t\t\t\tPRODUTO %d:\n\n", i + j + 1); 
            printf(" C�digo:                                                 %-15ld\n", estoque[i + j].codigo);
            printf(" Descri��o:                                              %-40s\n", estoque[i + j].descricao);
            printf(" Pre�o de Compra:                                        %-10.2f\n", estoque[i + j].pr_compra);
            printf(" Pre�o de Venda:                                         %-10.2f\n", estoque[i + j].pr_venda);
            printf(" Lucro M�nimo:                                           %-5.2f%%\n\n", estoque[i + j].lucro_minimo);
            resetarCor();
            
            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("=============================================================================\n\n");
            resetarCor();
        }
		
		setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
        printf("\n Navegue com as setas para cima/baixo para ver outros produtos.\n\n");
        resetarCor();
        
        printf(" Aperte ENTER para retornar ao menu\n");

        tecla = _getch(); //navega��o por teclas direcionais

        if (tecla == 80) { 
            if (i < tamanho - 2) {
                i += 2;  
            }
        }
        else if (tecla == 72) {
            if (i > 0) {
                i -= 2; 
            }
        }
        else if (tecla == 13) { 
            break;  
        }
    }

    system("cls");
    return;
}

//Fun��o de relat�rio de produtos
void relatorio_produtos(TProduto estoque[], int tamanho) {
    setlocale(LC_ALL, "Portuguese");
    int i = 0;
    char tecla;

    if (tamanho == 0) { //se nenhum produto estiver cadastrado
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("=============================================================================\n");
        resetarCor();

        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
        printf("\t\t\tMENU DE RELAT�RIO DE PRODUTOS\n");
        resetarCor();

        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("=============================================================================\n");
        resetarCor();

        setarCor(FOREGROUND_RED);
        printf("\n Nenhum produto cadastrado.\n\n");
        resetarCor();

        printf(" Aperte ENTER para retornar ao menu");
        getchar();
        getchar();
        system("cls");
        return;
    }

    while (1) { //menu de op��es, onde permite o usu�rio escolher entre: Navegar por todos os produtos; Consultar por c�digo espec�ficio; Consultar por in�cio de descri��o
        system("cls");

        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("=============================================================================\n");
        resetarCor();

        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
        printf("\t\t\tMENU DE RELAT�RIO DE PRODUTOS\n");
        resetarCor();

        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("=============================================================================\n");
        resetarCor();

        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
        printf("\n Escolha uma op��o:\n\n");
        
        printf(" 1 - Navegar pelos produtos\n");
        printf(" 2 - Consultar por c�digo\n");
        printf(" 3 - Consultar por descri��o\n");
        printf(" 0 - Retornar ao menu principal\n");
        resetarCor();
        
        printf("\n Digite a op��o desejada: ");
        int opcao;
        scanf("%d", &opcao);
        getchar();

        if (opcao == 0) { 
            system("cls");
            return;
        } else if (opcao == 1) { //se escolhida a op��o 1
            while (1) { 
                system("cls");

                setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("=============================================================================\n");
                resetarCor();

                setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                printf("\t\t\tMENU DE RELAT�RIO DE PRODUTOS\n");
                resetarCor();

                setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("=============================================================================\n");
                resetarCor();

                for (int j = 0; j < 15 && (i + j) < tamanho; j++) {
                    setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\n=============================================================================\n");
                    resetarCor();

                    setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                    printf("\t\t\t\tPRODUTO %d:\n\n", i + j + 1);
                    resetarCor();

                    if (estoque[i + j].quantidade < estoque[i + j].quantidade_minima) {
                        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                    } else {
                        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                    }

                    printf(" C�digo:                                                  %-15ld\n", estoque[i + j].codigo);  
                    printf(" Grupo:                                                   %-20s\n", estoque[i + j].grupo);  
                    printf(" Descri��o:                                               %-40s\n", estoque[i + j].descricao); 
                    printf(" Unidade:                                                 %-15s\n", estoque[i + j].unidade); 
                    printf(" Fornecedor:                                              %-30s\n", estoque[i + j].fornecedor);  
                    printf(" Pre�o de Compra:                                         %-10.2f\n", estoque[i + j].pr_compra);  
                    printf(" Pre�o de Venda:                                          %-10.2f\n", estoque[i + j].pr_venda);
                    printf(" Lucro M�nimo:                                            %-5.2f%%\n", estoque[i + j].lucro_minimo); 
                    printf(" Quantidade em Estoque:                                   %-10d\n", estoque[i + j].quantidade);
                    printf(" Quantidade M�nima:                                       %-10d\n\n", estoque[i + j].quantidade_minima);
                    resetarCor();

                    if (j != 14) {
                        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                        printf("=============================================================================\n");
                        resetarCor();
                    }
                }

                setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                printf("\n Navegue com as setas para cima/baixo para ver outros produtos.\n");
                setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("\n Produtos abaixo do estoque apareceram com a cor destacada.\n\n");
                resetarCor();

                printf("\n Aperte ENTER para retornar ao menu\n");

                //navega��o por teclas direcionais
		        tecla = _getch();
		        if (tecla == -32 || tecla == 224) { // teclas especiais 
		            tecla = _getch(); // captura o c�digo da tecla de dire��o
		            if (tecla == 80 && i + 15 < tamanho) { // seta para baixo
		                i += 15;
		            } else if (tecla == 72 && i - 15 >= 0) { // seta para cima
		                i -= 15;
		            }
		        } else if (tecla == 13) { // ENTER
		            break;
		        }
		    }
        } else if (opcao == 2) { //se escolhida a op��o 2
            long codigo_pesquisa;
            int encontrado = 0;

			system("cls");

	        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	        printf("=============================================================================\n");
	        resetarCor();
	
	        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
	        printf("\t\t\tMENU DE RELAT�RIO DE PRODUTOS\n");
	        resetarCor();
	
	        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	        printf("=============================================================================\n");
	        resetarCor();
	
	        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
	        
            printf("\n Digite o c�digo do produto: "); //requisita o c�digo do produto desejado
            scanf("%ld", &codigo_pesquisa);
			
            for (int j = 0; j < 15 && (i + j) < tamanho; j++) {
                if (estoque[i + j].codigo == codigo_pesquisa) { //apresenta as infos do produto resuisitado
                    system("cls");

                    setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("=============================================================================\n");
                    resetarCor();

                    setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                    printf("\t\t\tMENU DE RELAT�RIO DE PRODUTOS\n");
                    resetarCor();

                    setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("=============================================================================\n\n");
                    resetarCor();
					
					setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("=============================================================================\n");
                    resetarCor();
                    setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                    printf("\t\t\t\tPRODUTO %d:\n", j + 1);
                    resetarCor();
                    setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("=============================================================================\n\n");
                    resetarCor();
					
					if (estoque[i + j].quantidade < estoque[i + j].quantidade_minima) { //se o produto estiver abaixo do estoque registrado, ser� destacado em vermelho
                        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                    } else {
                        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                    }
					
                    printf(" C�digo:                                                  %-15ld\n", estoque[i + j].codigo);
                    printf(" Grupo:                                                   %-20s\n", estoque[i + j].grupo);
                    printf(" Descri��o:                                               %-40s\n", estoque[i + j].descricao);
                    printf(" Unidade:                                                 %-15s\n", estoque[i + j].unidade);
                    printf(" Fornecedor:                                              %-30s\n", estoque[i + j].fornecedor);
                    printf(" Pre�o Compra:                                            %-10.2f\n", estoque[i + j].pr_compra);
                    printf(" Pre�o Venda:                                             %-10.2f\n", estoque[i + j].pr_venda);
                    printf(" Lucro M�nimo:                                            %-5.2f%%\n", estoque[i + j].lucro_minimo);
                    printf(" Quantidade:                                              %-10d\n", estoque[i + j].quantidade);
                    printf(" Quantidade M�nima:                                       %-10d\n", estoque[i + j].quantidade_minima);
                    
                    setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\n=============================================================================\n");
					resetarCor();
					
                    encontrado = 1;
                    break;
                }
            }

            if (!encontrado) { //se o produto n�o for encontrado
            	
            	system("cls");
            	
            	setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		        printf("=============================================================================\n");
		        resetarCor();
		
		        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
		        printf("\t\t\tMENU DE RELAT�RIO DE PRODUTOS\n");
		        resetarCor();
		
		        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		        printf("=============================================================================\n");
		        resetarCor();
                setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            	
                setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("\n Nenhum produto encontrado com o c�digo '%ld'.\n", codigo_pesquisa);
                resetarCor();
            }
			
			fflush(stdin); //limpa buffer
            printf("\n Aperte ENTER para retornar ao menu");
            getchar(); //aguarda o ENTER
            
        } else if (opcao == 3) { //se escolhida a op��o 3
            char descricao_pesquisa[50];
            int encontrado = 0;

			system("cls");

	        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	        printf("=============================================================================\n");
	        resetarCor();
	
	        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
	        printf("\t\t\tMENU DE RELAT�RIO DE PRODUTOS\n");
	        resetarCor();
	
	        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	        printf("=============================================================================\n");
	        resetarCor();
			
            printf("\n Digite o in�cio da descri��o do produto: ");
            fgets(descricao_pesquisa, sizeof(descricao_pesquisa), stdin);
            descricao_pesquisa[strcspn(descricao_pesquisa, "\n")] = '\0'; // remove o '\n' do final
			
			system("cls");
			
			setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("=============================================================================\n");
            resetarCor();

            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
            printf("\t\t\tMENU DE RELAT�RIO DE PRODUTOS\n");
            resetarCor();

            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("=============================================================================\n");
            resetarCor();
			
			setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY); 
            printf("\n Resultados encontrados por descri��o:\n\n"); 
			resetarCor();

            for (int j = 0; j < 15 && (i + j) < tamanho; j++) {
                if (strncmp(estoque[i + j].descricao, descricao_pesquisa, strlen(descricao_pesquisa)) == 0) { //apresenta os produtos com o in�cio da descri��o informada
                	
                    setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("=============================================================================\n\n");
                    resetarCor();
                    
                    if (estoque[i + j].quantidade < estoque[i + j].quantidade_minima) { //se o produto estiver abaixo do estoque registrado, ser� destacado em vermelho
                        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                    } else {
                        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY); 
                    }
                         
                    printf(" C�digo:                                                  %-15ld\n", estoque[i + j].codigo);
                    printf(" Grupo:                                                   %-20s\n", estoque[i + j].grupo);
                    printf(" Descri��o:                                               %-40s\n", estoque[i + j].descricao);
                    printf(" Unidade:                                                 %-15s\n", estoque[i + j].unidade);
                    printf(" Fornecedor:                                              %-30s\n", estoque[i + j].fornecedor);
                    printf(" Pre�o Compra:                                            %-10.2f\n", estoque[i + j].pr_compra);
                    printf(" Pre�o Venda:                                             %-10.2f\n", estoque[i + j].pr_venda);
                    printf(" Lucro M�nimo:                                            %-5.2f%%\n", estoque[i + j].lucro_minimo);
                    printf(" Quantidade:                                              %-10d\n", estoque[i + j].quantidade);
                    printf(" Quantidade M�nima:                                       %-10d\n", estoque[i + j].quantidade_minima);
                    resetarCor();   
					            
                    setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                    printf("\n=============================================================================\n");
					resetarCor();
					
                    encontrado = 1;
                }
            }

            if (!encontrado) { //se o produto n�o for encontrado com a descri��o informada
            	
            	system("cls");
            	
            	setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		        printf("=============================================================================\n");
		        resetarCor();
		
		        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
		        printf("\t\t\tMENU DE RELAT�RIO DE PRODUTOS\n");
		        resetarCor();
		
		        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		        printf("=============================================================================\n");
		        resetarCor();
                setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("\n Nenhum produto encontrado com o in�cio da descri��o '%s'.\n", descricao_pesquisa);
                resetarCor();
            }

            printf("\n Aperte ENTER para retornar ao menu");
            getchar();
        } else { //se escolhida uma op��o inv�lida
        	
        	system("cls");
            	
            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		    printf("=============================================================================\n");
		    resetarCor();
		
		    setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
		    printf("\t\t\tMENU DE RELAT�RIO DE PRODUTOS\n");
		    resetarCor();
		
		    setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		    printf("=============================================================================\n");
			resetarCor();
        	
            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("\n Op��o inv�lida! Tente novamente.\n");
            resetarCor();
            fflush(stdin); //limpa buffer
            printf("\n Aperte ENTER para continuar...");
            getchar(); //aguarda o ENTER
        }
    }
}

//Fun��o de aumento de pre�o de produtos por fornecedor
void aumento_preco_fornecedor(TProduto estoque[], int tamanho) {
    setlocale(LC_ALL, "Portuguese");
    char fornecedor[41];
    float percentual;
    char confirma;
    int i, produtos_reajustados = 0;
    int fornecedores_distintos = 0;
    char fornecedores[100][41];  

    if (tamanho == 0) { //se n�o houver produto cadastrado
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("============================================================================\n");
        resetarCor();
        
        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
        printf("\t\tMENU DE AUMENTO DE PRE�O POR FORNECEDOR\n");
        resetarCor();
        
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("============================================================================\n");
        resetarCor();
        
        setarCor(FOREGROUND_RED);
        printf("\n Nenhum produto cadastrado.\n\n");
        resetarCor();
        
        printf(" Aperte ENTER para retornar ao menu");
        getchar();  
        getchar();  
        system("cls");  
        return;
    }

    for (i = 0; i < tamanho; i++) {
        int ja_adicionado = 0;
        for (int j = 0; j < fornecedores_distintos; j++) {
            if (strcmp(estoque[i].fornecedor, fornecedores[j]) == 0) {
                ja_adicionado = 1;
                break;
            }
        }
        if (!ja_adicionado) {
            strcpy(fornecedores[fornecedores_distintos], estoque[i].fornecedor);
            fornecedores_distintos++;
        }
    }

    while (1) { //se n�o houver fornecedor cadastrado
        system("cls");
        
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("============================================================================\n");
        resetarCor();
        
        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
        printf("\t\tMENU DE AUMENTO DE PRE�O POR FORNECEDOR\n");
        resetarCor();
        
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("============================================================================\n");
        resetarCor();
        
        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
        printf("\n Fornecedores cadastrados:\n\n");
        resetarCor();
        
        if (fornecedores_distintos == 0) {
            setarCor(FOREGROUND_RED);
            printf("\n Nenhum fornecedor encontrado.\n");
            resetarCor();
        } else {
            for (i = 0; i < fornecedores_distintos; i++) {
                setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                printf(" %d - %s\n", i + 1, fornecedores[i]);
                resetarCor();
            }
        }

        printf("\n Informe o n�mero do fornecedor que aplicar� o aumento: ");
        int fornecedor_num;
        scanf("%d", &fornecedor_num);
        getchar();  

        if (fornecedor_num < 1 || fornecedor_num > fornecedores_distintos) { //se numero de fornecedor invalido for informado
        	
        	system("cls"); 
        	
        	setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	        printf("============================================================================\n");
	        resetarCor();
	        
	        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
	        printf("\t\tMENU DE RELAT�RIO DE PRODUTOS POR FORNECEDOR\n");
	        resetarCor();
	        
	        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	        printf("============================================================================\n");
	        resetarCor();
        	
            setarCor(FOREGROUND_RED);
            printf("\n N�mero de fornecedor inv�lido.\n\n");
            resetarCor();
            
            fflush(stdin);
            printf(" Aperte ENTER para tentar novamente\n");
	        getchar();  
	        system("cls"); 
            continue;  
        }

        strcpy(fornecedor, fornecedores[fornecedor_num - 1]);

        while (1) { //informar percentual de aumento
            system("cls");
            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("============================================================================\n");
            resetarCor();
            
            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
            printf("\t\tMENU DE AUMENTO DE PRE�O POR FORNECEDOR\n");
            resetarCor();
            
            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("============================================================================\n");
            resetarCor();

            printf("\n Informe o percentual de aumento (Ex: 10 para 10%%): ");
            
            int resultado = scanf("%f", &percentual);

            if (resultado != 1 || percentual <= 0) { //se valor invalido for inserido
                system("cls"); 
                
                setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("============================================================================\n");
                resetarCor();
                
                setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                printf("\t\tMENU DE AUMENTO DE PRE�O POR FORNECEDOR\n");
                resetarCor();
                
                setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("============================================================================\n");
                resetarCor();
                
                setarCor(FOREGROUND_RED);
                printf("\n O valor inserido n�o pode ser menor ou igual a 0, ou conter caracteres inv�lidos.\n");
                resetarCor();
                
                printf("\n Deseja tentar novamente? (S/N): "); //pergunta ao usuario se deseja tentar novamente
                getchar();  
                getchar();
                char confirma;
                scanf("%c", &confirma);

                if (confirma == 'S' || confirma == 's') { //se sim, continua
                    while (getchar() != '\n');  
                    continue;  
                } else { //se n�o, limpa a tela e retorna
                	system("cls");
                    return;  
                }
            } else {
                break;  
            }
        }

        for (i = 0; i < tamanho; i++) { //apresenta os valores antigos e novos
            if (strcmp(estoque[i].fornecedor, fornecedor) == 0) {  
                system("cls");  
                
                setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("============================================================================\n");
                resetarCor();
                
                setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                printf("\t\tMENU DE AUMENTO DE PRE�O POR FORNECEDOR\n");
                resetarCor();
                
                setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("============================================================================\n\n");
                resetarCor();
                
                setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("============================================================================\n");
                resetarCor();
                
                setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                printf("\n PRODUTO %d:\n\n", i + 1);
                printf(" C�digo: %ld\n", estoque[i].codigo);
                printf(" Descri��o: %s\n", estoque[i].descricao);
                printf(" Pre�o de compra atual: %.2f\n", estoque[i].pr_compra);
                printf(" Novo pre�o de compra: %.2f\n", estoque[i].pr_compra * (1 + percentual / 100));
                resetarCor();
                
                setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("\n============================================================================\n");
                resetarCor();
                
                printf("\n Deseja aplicar este aumento? (S/N): "); //questiona o usuario sobre sua escolha
                scanf(" %c", &confirma);

                if (confirma == 'S' || confirma == 's') {
                    estoque[i].pr_compra *= (1 + percentual / 100);  
                    produtos_reajustados++;
                    
					setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);  
                    printf("\n Aumento aplicado com sucesso!\n"); //se aplicado
                    resetarCor();
                    
                } else if (confirma == 'N' || confirma == 'n') {
                	
                	setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
                	printf("\n O aumento n�o foi aplicado!\n"); //se n�o aplicado
                	resetarCor();
                }

                printf("\n Aperte ENTER para ajustar os pr�ximos produtos\n"); //continua apresentando os proximos produtos
                getchar();
                getchar();
            }
        }
        
        system("cls");
        
        if (produtos_reajustados > 0) { //informa os produtos que foram alterados
            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("============================================================================\n");
            resetarCor();
            
            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
            printf("\t\tMENU DE AUMENTO DE PRE�O POR FORNECEDOR\n");
            resetarCor();
            
            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("============================================================================\n");
            resetarCor();
            
            setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
            printf("\n Aumento aplicado com sucesso em %d produto(s) do fornecedor \"%s\"!\n", produtos_reajustados, fornecedor);
            resetarCor();
        } else {
        	
        	system("cls");
	        
	        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	        printf("============================================================================\n");
	        resetarCor();
	        
	        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
	        printf("\t\tMENU DE AUMENTO DE PRE�O POR FORNECEDOR\n");
	        resetarCor();
	        
	        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	        printf("============================================================================\n");
	        resetarCor();
        	
            setarCor(FOREGROUND_RED);
            printf("\n Nenhum produto foi alterado para o fornecedor \"%s\".\n", fornecedor); //se nenhum produto for alterado
            resetarCor();
        }

        printf("\n Aperte ENTER para retornar ao menu"); 
        getchar(); //espera o ENTER
        system("cls"); //limpa a tela
        break;  
    }
}

//Fun��o de relat�rio de produtos por fornecedor
void relatorio_produtos_por_fornecedor(TProduto estoque[], int tamanho) {
    setlocale(LC_ALL, "Portuguese");
    char fornecedores[100][41];
    int fornecedores_distintos = 0; 
    int i, fornecedor_num, produtos_encontrados = 0;

    if (tamanho == 0) { //se n�o houver produtos cadastrados
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("============================================================================\n");
        resetarCor();
        
        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
        printf("\t\tMENU DE RELAT�RIO DE PRODUTOS POR FORNECEDOR\n");
        resetarCor();
        
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("============================================================================\n");
        resetarCor();
        
        setarCor(FOREGROUND_RED);
        printf("\n Nenhum produto cadastrado.\n\n");
        resetarCor();
        
        printf(" Aperte ENTER para retornar ao menu");  
        getchar();  
        system("cls");  
        return;
    }

    for (i = 0; i < tamanho; i++) { 
        int ja_adicionado = 0;
        for (int j = 0; j < fornecedores_distintos; j++) {
            if (strcmp(estoque[i].fornecedor, fornecedores[j]) == 0) {
                ja_adicionado = 1;
                break;
            }
        }
        if (!ja_adicionado) {
            strcpy(fornecedores[fornecedores_distintos], estoque[i].fornecedor);
            fornecedores_distintos++;
        }
    }

    if (fornecedores_distintos == 0) { //se nenhum fornecedor encontrado
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("============================================================================\n");
        resetarCor();
        
        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
        printf("\t\tMENU DE RELAT�RIO DE PRODUTOS POR FORNECEDOR\n");
        resetarCor();
        
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("============================================================================\n");
        resetarCor();
        
        setarCor(FOREGROUND_RED);
        printf("\n Nenhum fornecedor encontrado.\n\n");
        resetarCor();
        
        printf(" Aperte ENTER para retornar ao menu");
        getchar();  
        getchar();  
        system("cls");
        return;
    }
	    setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("============================================================================\n");
        resetarCor();
        
        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
        printf("\t\tMENU DE RELAT�RIO DE PRODUTOS POR FORNECEDOR\n");
        resetarCor();
        
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("============================================================================\n");
        resetarCor();
        
        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
    	printf("\n Fornecedores cadastrados:\n\n");    	
    for (i = 0; i < fornecedores_distintos; i++) {
        printf(" %d - %s\n", i + 1, fornecedores[i]);
    }
		resetarCor(); 
		   
    	printf("\n Informe o n�mero do fornecedor que deseja gerar o relat�rio: ");
    	scanf("%d", &fornecedor_num);
    	getchar();

    if (fornecedor_num < 1 || fornecedor_num > fornecedores_distintos) { //se informado numero de fornecedor invalido
        system("cls");
        
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("============================================================================\n");
        resetarCor();
        
        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
        printf("\t\tMENU DE RELAT�RIO DE PRODUTOS POR FORNECEDOR\n");
        resetarCor();
        
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("============================================================================\n");
        resetarCor();
        setarCor(FOREGROUND_RED);
        printf("\n N�mero de fornecedor inv�lido.\n\n");
        resetarCor();
        
        fflush(stdin);
        printf(" Aperte ENTER para retornar ao menu");
        getchar();
        system("cls");
        return;
    }

    char fornecedor[41];
    strcpy(fornecedor, fornecedores[fornecedor_num - 1]);

    system("cls");

	    setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("============================================================================\n");
        resetarCor();
        
        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
        printf("\t\tMENU DE RELAT�RIO DE PRODUTOS POR FORNECEDOR\n");
        resetarCor();
        
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("============================================================================\n");
        resetarCor();

    for (i = 0; i < tamanho; i++) {
        if (strcmp(estoque[i].fornecedor, fornecedor) == 0) { //se houver produtos
        	
        	setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("\n============================================================================\n");
            resetarCor();
            
        	setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
            printf("\t\t\t\tPRODUTO %d:\n\n", i + 1);
            printf(" C�digo:                                                            %-15ld\n", estoque[i].codigo);  
            printf(" Grupo:                                                             %-20s\n", estoque[i].grupo);  
            printf(" Descri��o:                                                         %-40s\n", estoque[i].descricao); 
            printf(" Unidade:                                                           %-15s\n", estoque[i].unidade); 
            printf(" Pre�o de Compra:                                                   %-10.2f\n", estoque[i].pr_compra);  
            printf(" Pre�o de Venda:                                                    %-10.2f\n", estoque[i].pr_venda); 
            printf(" Lucro M�nimo:                                                      %-5.2f%%\n", estoque[i].lucro_minimo); 
            printf(" Quantidade em Estoque:                                             %-10d\n", estoque[i].quantidade);
            printf(" Quantidade M�nima:                                                 %-10d\n\n", estoque[i].quantidade_minima);
            resetarCor();
            
            setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("============================================================================\n");
            resetarCor();
            produtos_encontrados++;
        }
    }

    if (produtos_encontrados == 0) { //se nenhum produto encontrado
    	
    	setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("============================================================================\n");
        resetarCor();
        
        setarCor(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
        printf("\t\tMENU DE RELAT�RIO DE PRODUTOS POR FORNECEDOR\n");
        resetarCor();
        
        setarCor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("============================================================================\n");
        resetarCor();
        
        setarCor(FOREGROUND_RED);
        printf("\n Nenhum produto encontrado para o fornecedor \"%s\".\n\n", fornecedor);
        resetarCor();
    }

    printf("\n Aperte ENTER para retornar ao menu"); 
    getchar(); //espera o ENTER
    system("cls"); //limpa a tela
}

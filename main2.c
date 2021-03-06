#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>
#include <stdbool.h>

//gera um relatorio, do dia, m�s, custos e lucros
typedef struct relatorio {
  char dia;
  char mes;
  char codigo;
  float valorCust;
  float valorLucr;
  struct Relatorio *prox;

}Relatorio;

//cadastra um novo produto
struct cadastrarProd {
    char codigo[9];
    char descricao[100];
    int qtd, qtdVenda;
    float precoCusto;
    float precoVenda;
} Produto;

//cadastra um novo cliente
struct cadastrarClie {
    char codigo[9];
    char cpf[14];
    char nome[100];
    char telefone[20];
    char status;
} Cliente;

//cadastra um fornecedor
struct cadastrarFornec {
    char codigo[9];
    char documento[20];
    char nome[100];
    char telefone[20];
    char status;
} Fornecedor;

FILE *fp;
void incluir(void);
void consultar(void);
void excluir(void);
void alterar(void);
void abrir(char[3]);
void listar(void);
void ajuda(void);
int financeiro(void);
void subMenu(void);
void subMenuCadastros(void);
void buscarRelatorio(int, int, int);
void relat(void);

int iTag = 0;

Relatorio *novo;
Relatorio *inicio = NULL;
Relatorio *fim = NULL;
Relatorio *aux = NULL;
Relatorio *ponteiroAux = NULL;
Relatorio *inicioFila = NULL;
float totalVenda, valorVenda, valorLucro= 0, tLucroProd;

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    char opcao[2], op;
    do {
        do {
            system("cls");
            printf("\n\n");

            printf("\n Digite uma das opcoes\n\n");
            printf("\n <C> - Cadastros");
            printf("\n <F> - Financeiro");
            printf("\n <R> - Relatorios");
            printf("\n <H> - Ajuda");
            printf("\n <S> - Sair");
            printf("\n\n\n Digite a sua opcao:");
            gets(opcao);
            setbuf(stdin, NULL);
            op = tolower(*opcao);
        } while (!strchr("cfrhs", op));

        switch (op) {/*D*/
            case 'c': subMenu();
                break;
            case 'f': financeiro();
                break;
            case 'r': relat();
                break;
            case 'h': ajuda();
                break;
            case 's': exit(0);
        }
    } while (1);
}

void subMenu(void) {
    char opcao[2], op;
    do {
        do {
            system("cls");
            printf("\n\n");
            printf("\n Digite uma das opcoes\n\n");
			printf("\n <P> - Produtos");
            printf("\n <F> - Fornecedores");
			printf("\n <C> - Clientes");
            printf("\n <V> - Voltar");
            printf("\n\n\n Digite a Sua Opcaoo:");
            gets(opcao);
            setbuf(stdin, NULL);
            op = tolower(*opcao);
        } while (!strchr("cfpv", op));

        switch (op) {/*D*/
            case 'c':
                iTag = 1;
                subMenuCadastros();
                break;
            case 'f':
                iTag = 2;
                subMenuCadastros();
                break;
            case 'p':
                iTag = 3;
                subMenuCadastros();
                break;
            case 'v':
                main();
                break;
        }
    } while (1);
}

void subMenuCadastros(void) {
    char opcao[2], op;
    do {
        do {
            system("cls");
            printf("\n\n");
            printf("\n Digite uma das opcoes\n\n");
            printf("\n <I> - Incluir");
            printf("\n <A> - Alterar");
            printf("\n <E> - Excluir");
            printf("\n <C> - Consultar");
            printf("\n <L> - Listar");
            printf("\n <V> - Voltar");
            printf("\n\n\n Opcao:");
            gets(opcao);
            setbuf(stdin, NULL);
            op = tolower(*opcao);
        } while (!strchr("iaeclv", op));
        switch (op) {
            case 'i': incluir();
                break;
            case 'a': alterar();
                break;
            case 'e': excluir();
                break;
            case 'c': consultar();
                break;
            case 'l': listar();
                break;
            case 'v': iTag = 0;
                subMenu();
                break;
        }
    } while (1);
}

void ajuda(void) {
    system("cls");
    printf("\a\n");
    printf("\nLUCRO\n\t O lucro � considerado todo o rendimento positivo obtido atraves de uma negociacao economica ou de qualquer outro genero. Na economia, o lucro e tudo o que foi ganhado ou recebido a partir de um ato de comercializacao financeira..\n");
    printf("\nCAIXA DE CUSTO\n\t O preco de custo e aquele cobrado sobre os produtos ou servicos e equivale apenas ao custo necessario para a materia prima e mao de obra. Ou seja, nele nao e acrescentado o lucro por parte de quem vendera� o produto, nem valores referentes a estocagem, custos basicos..\n");
    printf("\nMELHOR FORMA DE INVESTIR\n\t Tao fundamental para a empresa manter certa reserva de seu lucro para eventuais necessidades ou imprevistos. Desta forma, em periodos de baixa ou mesmo falta de caixa, a empresa podera passar pelas ""turbulencias"" de forma muito mais tranquila e sem precisar recorrer a bancos ou outras intituicoes financeiras, consequentemente sem precisar pagar juros a terceiros...\n");
    printf("\t\t\tTecle <ENTER> para voltar");
    getch();
}

void abrir(char tipo[3]) {
    if (iTag == 1) {
        if ((fp = fopen("clientes.txt", tipo)) == NULL) {
            printf("\n O arquivo nao pode ser aberto!!\n");
            getch();
            exit(1);
        }
    } else if (iTag == 2) {
        if ((fp = fopen("fornecedores.txt", tipo)) == NULL) {
            printf("\n O arquivo nao pode ser aberto!!\n");
            getch();
            exit(1);
        }
    } else if (iTag == 3) {
        if ((fp = fopen("produtos.txt", tipo)) == NULL) {
            printf("\n O arquivo nao pode ser aberto!!\n");
            getch();
            exit(1);
        }
    }
}

void incluir(void) { //char *um="0";
    if (iTag == 1) {
        system("cls");
        abrir("ab+");
        fseek(fp, 0L, SEEK_END);
        do {
            printf("\n Digite o nome ou <FIM> para sair:\n\n");
            printf(" ");
            gets(Cliente.nome);
            setbuf(stdin, NULL);
            if ((strcmp(Cliente.nome, "fim") != 0)&&(strcmp(Cliente.nome, "FIM") != 0)) {
                printf("\n Codigo:");
                gets(Cliente.codigo);
                setbuf(stdin, NULL);
                printf("\n CPF:");
                gets(Cliente.cpf);
                setbuf(stdin, NULL);
                printf("\n Telefone:");
                gets(Cliente.telefone);
                setbuf(stdin, NULL);
                Cliente.status = '1';
                if (fwrite(&Cliente, sizeof (struct cadCliente), 1, fp) != 1) {
                    printf("\n Erro de gravacao!!");
                    getch();
                } else {
                    printf("\n Dados gravados com sucesso\n\n");
                }
            }
        } while ((strcmp(Cliente.nome, "fim") != 0)&&(strcmp(Cliente.nome, "FIM") != 0));
        fclose(fp);
    } else if (iTag == 2) {
        system("cls");
        abrir("ab+");
        fseek(fp, 0L, SEEK_END);
        do {
            printf("\n Digite o nome ou <FIM> para sair:\n\n");
            printf(" ");
            gets(Fornecedor.nome);
            setbuf(stdin, NULL);
            if ((strcmp(Fornecedor.nome, "fim") != 0)&&(strcmp(Fornecedor.nome, "FIM") != 0)) {
                printf("\n Codigo:");
                gets(Fornecedor.codigo);
                setbuf(stdin, NULL);
                printf("\n CPF:");
                gets(Fornecedor.documento);
                setbuf(stdin, NULL);
                printf("\n Telefone:");
                gets(Fornecedor.telefone);
                setbuf(stdin, NULL);
                Fornecedor.status = '1';
                if (fwrite(&Fornecedor, sizeof (struct cadFornecedor), 1, fp) != 1) {
                    printf("\n Erro de gravacao!!");
                    getch();
                } else {
                    printf("\n Dados gravados com sucesso\n\n");
                }
            }
        } while ((strcmp(Fornecedor.nome, "fim") != 0)&&(strcmp(Fornecedor.nome, "FIM") != 0));
        fclose(fp);
    } else if (iTag == 3) {
        system("cls");
        abrir("ab+");
        fseek(fp, 0L, SEEK_END);
        do {
            printf("\n Digite A Descricao do Produto ou <FIM> para sair:\n\n");
            printf(" ");
            gets(Produto.descricao);
            setbuf(stdin, NULL);
            if ((strcmp(Produto.descricao, "fim") != 0)&&(strcmp(Produto.descricao, "FIM") != 0)) {
                printf("\n codigo: ");
                gets(Produto.codigo);
                setbuf(stdin, NULL);
                printf("\n Preco de Custo: ");
                scanf("%f", &Produto.precoCusto);
                setbuf(stdin, NULL);
                printf("\n Preco de Venda: ");
                scanf("%f", &Produto.precoVenda);
                setbuf(stdin, NULL);
                printf("\n Quantidade Em Estoque: ");
                scanf("%d", &Produto.qtd);
                setbuf(stdin, NULL);
                if (fwrite(&Produto, sizeof (struct cadProduto), 1, fp) != 1) {
                    printf("\n Erro de gravacao!!");
                    getch();
                } else {
                    printf("\n Dados gravados com sucesso\n\n");
                }
            }
        } while ((strcmp(Produto.descricao, "fim") != 0)&&(strcmp(Produto.descricao, "FIM") != 0));
        fclose(fp);
    }
}

void consultar(void) {

}

void alterar(void) {

}

void listar(void) {

}

void excluir(void) {
	
}

int financeiro(void) {


}

void relat(){

}
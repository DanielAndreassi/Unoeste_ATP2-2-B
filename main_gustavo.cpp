#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include <windows.h>
#include <ctype.h>

typedef struct
{
    int d, m, a;
} tpData;

typedef struct
{
    int codProd, estoque, codForn, ativo;
    char descricao[50];
    float preco;
    tpData data;
} tpProduto;

typedef struct
{
    int codForn, ativo;
    char nomeForn[50], cidadeForn[50];
} tpFornecedor;

typedef struct
{
    long long int cpfCliente, qtdeCompras;
    int ativo;
    char nomeCliente[50];
    float valorTotalComprado;
} tpCliente;

typedef struct
{
    int codVenda, ativo;
    long int cpfCliente;
    tpData data;
    float totalVendas;
} tpVenda;

typedef struct
{
    int codVenda, codProd, qtde, ativo;
    float valorUnitario;
} tpVendasProdutos;

// #FUNÇÕES DE MOLDURA#
void moldura(int CI, int LI, int CF, int LF, int CorT, int CorF);
void exibirMoldura(void);

// #FUNCOES DE MENUS#
char menuPrincipal(void);
char menuVendas(void);
char menuProdutos(void);
char menuFornecedores(void);
char menuClientes(void);
void limparMenu(void);
void limparTitulo(void);

// #FUNCOES DE VENDAS#
// efetuarVenda();
// relatorioDeVendas();
// exclusaoDeVendas();

// #FUNCOES DE PRODUTOS#
int buscaProdutoExaustiva(FILE *ptr, int codProd);
void cadastroProdutos(void);
void consultaProdutos(void);
void alteracaoProdutos(void);
// exclusaoProdutos();
// relatorioProdutos();

// #FUNCOES DE FORNECEDORES#
int buscaFornecedorExaustiva(FILE *ptr, int codForn);
void cadastroFornecedores(void);
void consultaFornecedores(void);
// exclusaoForn();
// alteracaoFornecedores();
// relatorioFornecedores();
// aumentoDePreco();

// #FUNCOES DE CLIENTES#
// cadastroCliente();
// consultaClientes();
// exclusaoClientes();
// alteracaoClientes();
// relatorioClientes();

// #FUNCOES AUXILIARES#
// insercaoAutomDeDados();
void executar(void);
// fazer cupom fiscal
// todas as funcoes do executar estao declaradas mas sem tipo e sem paramentros, pois ainda nao foram feitas
// fazer buscas,remanejamneto de dados, ordenacao, relatorios, exclusoes, alteracoes, cadastros, consultas, etc

// #FUNÇÕES DE MOLDURA
void moldura(int CI, int LI, int CF, int LF, int CorT, int CorF)
{
    int i;
    textcolor(CorT);
    textbackground(CorF);
    gotoxy(CI, LI);
    printf("%c", 201);
    gotoxy(CI, LF);
    printf("%c", 200);
    gotoxy(CF, LI);
    printf("%c", 187);
    gotoxy(CF, LF);
    printf("%c", 188);
    for (i = CI + 1; i < CF; i++)
    {
        gotoxy(i, LI);
        printf("%c", 205);
        gotoxy(i, LF);
        printf("%c", 205);
    }
    for (i = LI + 1; i < LF; i++)
    {
        gotoxy(CI, i);
        printf("%c", 186);
        gotoxy(CF, i);
        printf("%c", 186);
    }

    textcolor(7);
    textbackground(0);
}

void exibirMoldura(void)
{

    // PARTE DE CIMA - TÍTULO
    moldura(1, 1, 80, 5, 10, 2);
    // PARTE DE BAIXO - MENUS
    moldura(1, 6, 80, 25, 10, 2);
    gotoxy(31, 1);
    printf("* * * TITULO * * *");
}

// # FUNÇÕES DE MENU

char menuFornecedores(void)
{
    // limparMenu();
    // limparTitulo();
    // Sleep(500);
    system("cls");
    exibirMoldura();
    gotoxy(27, 3);
    printf("### MENU FORNECEDORES ###");
    gotoxy(2, 8);
    printf("[A] Cadastro de Fornecedores");
    gotoxy(2, 9);
    printf("[B] Consulta de Fornecedores");
    gotoxy(2, 10);
    printf("[C] Exclusao de Fornecedores");
    gotoxy(2, 11);
    printf("[D] Alteracao de Fornecedores");
    gotoxy(2, 12);
    printf("[E] Relatorio de Fornecedores");
    gotoxy(2, 13);
    printf("[F] Aumento de precos de produtos");
    gotoxy(2, 14);
    printf("[ESC] Voltar para menu principal");
    gotoxy(2, 15);
    printf("Opcao desejada: ");
    return toupper(getche());
}

char menuProdutos(void)
{
    // limparMenu();
    // limparTitulo();
    // Sleep(500);
    system("cls");
    exibirMoldura();
    gotoxy(27, 3);
    printf("### MENU PRODUTOS ###");
    gotoxy(2, 8);
    printf("[A] Cadastro de Produtos");
    gotoxy(2, 9);
    printf("[B] Consulta de Produtos");
    gotoxy(2, 10);
    printf("[C] Exclusao de Produtos");
    gotoxy(2, 11);
    printf("[D] Alteracao de Produtos");
    gotoxy(2, 12);
    printf("[E] Relatorio de Produtos");
    gotoxy(2, 13);
    printf("[ESC] Voltar para menu principal");
    gotoxy(2, 14);
    printf("Opcao desejada: ");
    return toupper(getche());
}

char menuVendas(void)
{
    // limparMenu();
    // limparTitulo();
    // Sleep(500);
    system("cls");
    exibirMoldura();
    gotoxy(27, 3);
    printf("### MENU VENDAS ###");
    gotoxy(2, 8);
    printf("[A] Efetuar uma venda");
    gotoxy(2, 9);
    printf("[B] Relatorio de vendas");
    gotoxy(2, 10);
    printf("[C] Exclusao de uma venda");
    gotoxy(2, 11);
    printf("[ESC] Voltar para menu principal");
    gotoxy(2, 12);
    printf("Opcao desejada: ");
    return toupper(getche());
}

char menuClientes(void)
{
    // limparMenu();
    // limparTitulo();
    // Sleep(500);
    system("cls");
    exibirMoldura();
    gotoxy(27, 3);
    printf("### MENU CLIENTES ###");
    gotoxy(2, 8);
    printf("[A] Cadastro de Clientes");
    gotoxy(2, 9);
    printf("[B] Consulta de Clientes");
    gotoxy(2, 10);
    printf("[C] Exclusao de Clientes");
    gotoxy(2, 11);
    printf("[D] Alteracao de Clientes");
    gotoxy(2, 12);
    printf("[E] Relatorio de Clientes");
    gotoxy(2, 13);
    printf("[ESC] Voltar para menu principal");
    gotoxy(2, 14);
    printf("Opcao desejada: ");
    return toupper(getche());
}

char menuPrincipal(void)
{
    system("cls");
    exibirMoldura();
    // limparMenu();
    // limparTitulo();
    // Sleep(500);
    gotoxy(27, 3);
    printf("### MENU PRINCIPAL ###");
    gotoxy(2, 8);
    printf("[A] Secao de Vendas");
    gotoxy(2, 9);
    printf("[B] Secao de Produtos");
    gotoxy(2, 10);
    printf("[C] Secao de Fornecedores");
    gotoxy(2, 11);
    printf("[D] Secao de Clientes");
    gotoxy(2, 12);
    printf("[E] Insercao de dados automaticos");
    gotoxy(2, 13);
    printf("[ESC] Sair");
    gotoxy(2, 14);
    printf("Opcao desejada: ");
    char a = toupper(getche());
    // Sleep(500);
    return a;
}

// #FUNÇÕES DE PRODUTOS#
int buscaProdutoExaustiva(FILE *ptr, int codProd)
{
    tpProduto R;
    rewind(ptr); // fseek(ptr,0,0);

    fread(&R, sizeof(tpProduto), 1, ptr);
    while (!feof(ptr) && codProd != R.codProd)
        fread(&R, sizeof(tpProduto), 1, ptr);

    if (!feof(ptr))
        return ftell(ptr) - sizeof(tpProduto);
    else
        return -1;
}

void cadastroProdutos(void)
{
    system("cls");
    FILE *ptrProdutos = fopen("produtos.bat", "rb+");
    FILE *ptrFornecedores = fopen("fornecedores.bat", "rb+");

    if (ptrProdutos == NULL || ptrFornecedores == NULL)
    {
        printf("\nErro na abertura de arquivo!\n");
    }
    else
    {
        tpProduto prod;
        tpFornecedor forn;

        printf("\n### CADASTRO DE PRODUTOS ###\n");
        printf("\nCodigo do produto: ");
        scanf("%d", &prod.codProd);
        while (prod.codProd > 0)
        {
            int pos = buscaProdutoExaustiva(ptrProdutos, prod.codProd);
            if (pos != -1)
            {
                printf("\nProduto existente!\n");
            }
            else
            {
                printf("\nCodigo de fornecedor: ");
                scanf("%d", &prod.codForn);
                int posForn = buscaFornecedorExaustiva(ptrFornecedores, prod.codForn);
                if (posForn == -1)
                {
                    printf("\nFornecedor nao encontrado, indo para cadastro de fornecedor\n");
                    forn.codForn = prod.codForn;
                    printf("Digite o nome do fornecedor: ");
                    fflush(stdin);
                    gets(forn.nomeForn);
                    printf("\nDigite a cidade do fornecedor: ");
                    fflush(stdin);
                    gets(forn.cidadeForn);
                    forn.ativo = 1;
                    printf("\nRetornando para cadastro do produto");
                }
                printf("\nDigite a descricao: ");
                fflush(stdin);
                gets(prod.descricao);
                printf("\nDigite o estoque: ");
                scanf("%d", &prod.estoque);
                printf("\nDigite o preco: ");
                scanf("%f", &prod.preco);
                printf("Digite a data de validade: ");
                scanf("%d/%d/%d", &prod.data.d, &prod.data.m, &prod.data.a);
                prod.ativo = 1;
                printf("\nConfirma o cadastro do produto? (S/N): ");
                char confirma = toupper(getche());
                if (confirma == 'S')
                {
                    if (posForn == -1)
                    {
                        fseek(ptrFornecedores, 0, 2);
                        fwrite(&forn, sizeof(tpFornecedor), 1, ptrFornecedores);
                    }
                    fseek(ptrProdutos, 0, 2);
                    fwrite(&prod, sizeof(tpProduto), 1, ptrProdutos);
                }
                else
                {
                    printf("\nCadastro de produto abortado!");
                }
            }
            printf("\nDigite outro codigo de produto para continuar cadastro, digite 0 para encerrar: ");
            scanf("%d", &prod.codProd);
        }
        fclose(ptrProdutos);
        fclose(ptrFornecedores);
    }
    system("cls");
    exibirMoldura();
}

void consultaProdutos(void)
{
    system("cls");
    FILE *ptrProdutos = fopen("produtos.bat", "rb+");
    FILE *ptrFornecedores = fopen("fornecedores.bat", "rb+");

    if (ptrProdutos == NULL || ptrFornecedores == NULL)
    {
        printf("\nErro na abertura de arquivo!\n");
    }
    else
    {
        tpProduto prod;
        tpFornecedor forn;
        printf("\n### CONSULTA DE PRODUTOS ###\n");
        printf("\nCodigo do produto: ");
        scanf("%d", &prod.codProd);
        while (prod.codProd > 0)
        {
            int pos = buscaProdutoExaustiva(ptrProdutos, prod.codProd);
            if (pos == -1)
            {
                printf("\nProduto inexistente!\n");
            }
            else
            {
                fseek(ptrProdutos, pos, 0);
                fread(&prod, sizeof(tpProduto), 1, ptrProdutos);
                printf("Descricao: ");
                puts(prod.descricao);
                printf("\nEstoque: %d", prod.estoque);
                printf("\nPreco: R$ %.2f", prod.preco);
                printf("\nData de validade: %d/%d/%d", prod.data.d, prod.data.m, prod.data.a);

                int posForn = buscaFornecedorExaustiva(ptrFornecedores, prod.codForn);
                fseek(ptrFornecedores, posForn, 0);
                fread(&forn, sizeof(tpFornecedor), 1, ptrFornecedores);
                printf("\n\nFornecedor:\n");
                printf("Nome do fornecedor: ");
                puts(forn.nomeForn);
                printf("Codigo do fornecedor: %d", forn.codForn);
                printf("\nCidade do fornecedor: ");
                puts(forn.cidadeForn);
            }
            printf("\nDigite outro codigo de produto para continuar consulta, digite 0 para encerrar: ");
            scanf("%d", &prod.codProd);
        }
    }
    fclose(ptrProdutos);
    fclose(ptrFornecedores);
    system("cls");
    exibirMoldura();
}

void alteracaoProdutos(void)
{
    system("cls");
    FILE *ptrProdutos = fopen("produtos.bat", "rb+");
    FILE *ptrFornecedores = fopen("fornecedores.bat", "rb+");

    if (ptrProdutos == NULL || ptrFornecedores == NULL)
    {
        printf("\nErro na abertura de arquivo!\n");
    }
    else
    {
        tpProduto prod;
        tpFornecedor forn;

        printf("\n### ALTERACAO DE PRODUTOS ###\n");
        printf("\nCodigo do produto que deseja alterar: ");
        scanf("%d", &prod.codProd);
        while (prod.codProd > 0)
        {
            int pos = buscaProdutoExaustiva(ptrProdutos, prod.codProd);
            if (pos == -1)
            {
                printf("\nProduto inexistente!\n");
            }
            else
            {
                printf("Produto que deseja alterar: \n");
                fseek(ptrProdutos, pos, 0);
                fread(&prod, sizeof(tpProduto), 1, ptrProdutos);
                printf("Descricao: ");
                puts(prod.descricao);
                printf("Codigo do produto: %d", prod.codProd);
                printf("\nEstoque: %d", prod.estoque);
                printf("\nPreco: R$ %.2f", prod.preco);
                printf("\nData de validade: %d/%d/%d", prod.data.d, prod.data.m, prod.data.a);
                printf("\nCodigo de fornecedor: %d", prod.codForn);

                printf("\n\nNova descricao: ");
                fflush(stdin);
                gets(prod.descricao);
                printf("\nNovo estoque: ");
                scanf("%d", &prod.estoque);
                printf("\nNovo preco: R$ ");
                scanf("%f", &prod.preco);
                printf("\nNova data de validade: ");
                scanf("%d/%d/%d", &prod.data.d, &prod.data.m, &prod.data.a);
                printf("\nNovo codigo fornecedor: ");
                scanf("%d", &prod.codForn);
                int posForn = buscaFornecedorExaustiva(ptrFornecedores, prod.codForn);
                if (posForn == -1)
                {
                    printf("\nFornecedor nao encontrado, indo para cadastro de fornecedor\n");
                    forn.codForn = prod.codForn;
                    printf("Digite o nome do fornecedor: ");
                    fflush(stdin);
                    gets(forn.nomeForn);
                    printf("\nDigite a cidade do fornecedor: ");
                    fflush(stdin);
                    gets(forn.cidadeForn);
                    forn.ativo = 1;
                    printf("\nRetornando para alteracao do produto");
                }
                printf("\nConfirma a alteracao do produto? (S/N): ");
                char confirma = toupper(getche());
                if (confirma == 'S')
                {
                    if (posForn == -1)
                    {
                        fseek(ptrFornecedores, 0, 2);
                        fwrite(&forn, sizeof(tpFornecedor), 1, ptrFornecedores);
                    }
                    fseek(ptrProdutos, pos, 0);
                    fwrite(&prod, sizeof(tpProduto), 1, ptrProdutos);
                }
                else
                {
                    printf("\nAltercao de produto abortada!");
                }
            }
            printf("\nDigite outro codigo de produto para continuar alteracao, digite 0 para encerrar: ");
            scanf("%d", &prod.codProd);
        }
        fclose(ptrProdutos);
        fclose(ptrFornecedores);
    }
    system("cls");
    exibirMoldura();
}

// #FUNÇÕES DE FORNECEDORES
int buscaFornecedorExaustiva(FILE *ptr, int codForn)
{
    tpFornecedor R;
    rewind(ptr); // fseek(ptr,0,0);

    fread(&R, sizeof(tpFornecedor), 1, ptr);
    while (!feof(ptr) && codForn != R.codForn)
        fread(&R, sizeof(tpFornecedor), 1, ptr);

    if (!feof(ptr))
        return ftell(ptr) - sizeof(tpFornecedor);
    else
        return -1;
}

void cadastroFornecedores(void)
{
    system("cls");
    FILE *ptrFornecedores = fopen("fornecedores.bat", "rb+");

    if (ptrFornecedores == NULL)
    {
        printf("\nErro na abertura de arquivo!\n");
    }
    else
    {
        tpFornecedor forn;

        printf("\n### CADASTRO DE FORNECEDORES ###\n");
        printf("\nCodigo do fornecedor: ");
        scanf("%d", &forn.codForn);
        while (forn.codForn > 0)
        {
            int pos = buscaFornecedorExaustiva(ptrFornecedores, forn.codForn);
            if (pos != -1)
            {
                printf("\nFornecedor existente!\n");
            }
            else
            {
                printf("\nDigite o nome do fornecedor: ");
                fflush(stdin);
                gets(forn.nomeForn);
                printf("\nDigite a cidade do fornecedor: ");
                fflush(stdin);
                gets(forn.cidadeForn);
                forn.ativo = 1;
                printf("\nConfirma o cadastro do fornecedor? (S/N): ");
                char confirma = toupper(getche());
                if (confirma == 'S')
                {
                    fseek(ptrFornecedores, 0, 2);
                    fwrite(&forn, sizeof(tpFornecedor), 1, ptrFornecedores);
                }
                else
                {
                    printf("\nCadastro de fornecedor abortado!");
                }
            }
            printf("\nDigite outro codigo de fornecedor para continuar cadastro, digite 0 para encerrar: ");
            scanf("%d", &forn.codForn);
        }
        fclose(ptrFornecedores);
    }
    system("cls");
    exibirMoldura();
}

void consultaFornecedores(void)
{
    system("cls");
    FILE *ptrFornecedores = fopen("fornecedores.bat", "rb+");

    if (ptrFornecedores == NULL)
    {
        printf("\nErro na abertura de arquivo!\n");
    }
    else
    {
        tpFornecedor forn;
        printf("\n### CONSULTA DE FORNECEDORES ###\n");
        printf("\nCodigo do fornecedor: ");
        scanf("%d", &forn.codForn);
        while (forn.codForn > 0)
        {
            int pos = buscaFornecedorExaustiva(ptrFornecedores, forn.codForn);
            if (pos == -1)
            {
                printf("\nFornecedor inexistente!\n");
            }
            else
            {
                fseek(ptrFornecedores, pos, 0);
                fread(&forn, sizeof(tpFornecedor), 1, ptrFornecedores);
                printf("\nNome do fornecedor: ");
                puts(forn.nomeForn);
                printf("\nCidade do fornecedor: ");
                puts(forn.cidadeForn);
            }
            printf("\nDigite outro codigo de fornecedor para continuar consulta, digite 0 para encerrar: ");
            scanf("%d", &forn.codForn);
        }
    }
    fclose(ptrFornecedores);
    system("cls");
    exibirMoldura();
}

void alteracaoFornecedores(void)
{
    system("cls");
    FILE *ptrFornecedores = fopen("fornecedores.bat", "rb+");

    if (ptrFornecedores == NULL)
    {
        printf("\nErro na abertura de arquivo!\n");
    }
    else
    {
        tpFornecedor forn;

        printf("\n### ALTERACAO DE FORNECEDORES ###\n");
        printf("\nCodigo do fornecedor que deseja alterar: ");
        scanf("%d", &forn.codForn);
        while (forn.codForn > 0)
        {
            int pos = buscaFornecedorExaustiva(ptrFornecedores, forn.codForn);
            if (pos == -1)
            {
                printf("\nFornecedor inexistente!\n");
            }
            else
            {
                printf("Fornecedor que deseja alterar: \n");
                fseek(ptrFornecedores, pos, 0);
                fread(&forn, sizeof(tpFornecedor), 1, ptrFornecedores);
                printf("Nome do fornecedor: ");
                puts(forn.nomeForn);
                printf("Cidade do fornecedor: ");
                puts(forn.cidadeForn);

                printf("\nNovo nome do fornecedor: ");
                fflush(stdin);
                gets(forn.nomeForn);
                printf("\nNova cidade do fornecedor: ");
                fflush(stdin);
                gets(forn.cidadeForn);

                printf("\nConfirma a alteracao do fornecedor? (S/N): ");
                char confirma = toupper(getche());
                if (confirma == 'S')
                {
                    fseek(ptrFornecedores, pos, 0);
                    fwrite(&forn, sizeof(tpFornecedor), 1, ptrFornecedores);
                }
                else
                {
                    printf("\nAltercao de fornecedor abortada!");
                }
            }
            printf("\nDigite outro codigo de fornecedor para continuar alteracao, digite 0 para encerrar: ");
            scanf("%d", &forn.codForn);
        }
        fclose(ptrFornecedores);
    }
    system("cls");
    exibirMoldura();
}
// #FUNÇÕES AUXILIARES
void executar(void)
{
    exibirMoldura();
    char opMenuPrincipal;
    do
    {
        opMenuPrincipal = menuPrincipal();
        switch (opMenuPrincipal)
        {
        case 'A':
            char opMenuVendas;
            do
            {
                opMenuVendas = menuVendas();
                // switch (opMenuVendas)
                // {
                // case 'A':
                //     efetuarVenda();
                //     break;
                // case 'B':
                //     relatorioDeVendas();
                //     break;
                // case 'C':
                //     exclusaoDeVendas();
                //     break;
                // }
            } while (opMenuVendas != 27);
            break;
        case 'B':
            char opMenuProdutos;
            do
            {
                opMenuProdutos = menuProdutos();
                switch (opMenuProdutos)
                {
                case 'A':
                    cadastroProdutos();
                    break;
                case 'B':
                    consultaProdutos();
                    break;
                // case 'C':
                //     exclusaoProdutos();
                //     break;
                case 'D':
                    alteracaoProdutos();
                    break;
                    // case 'E':
                    //     relatorioProdutos();
                    //     break;
                } // }
            } while (opMenuProdutos != 27);
            break;
        case 'C':
            char opMenuFornecedores;
            do
            {
                opMenuFornecedores = menuFornecedores();
                switch (opMenuFornecedores)
                {
                case 'A':
                    cadastroFornecedores();
                    break;
                case 'B':
                    consultaFornecedores();
                    break;
                // case 'C':
                //     exclusaoForn();
                //     break;
                case 'D':
                    alteracaoFornecedores();
                    break;
                    // case 'E':
                    //     relatorioFornecedores();
                    //     break;
                    // case 'F':
                    //     aumentoDePreco();
                    //     break;
                }
            } while (opMenuFornecedores != 27);
            break;
        case 'D':
            char opMenuClientes;
            do
            {
                opMenuClientes = menuClientes();
                // switch (opMenuClientes)
                // {
                // case 'A':
                //     cadastroCliente();
                //     break;
                // case 'B':
                //     consultaClientes();
                //     break;
                // case 'C':
                //     exclusaoClientes();
                //     break;
                // case 'D':
                //     alteracaoClientes();
                //     break;
                // case 'E':
                //     relatorioClientes();
                //     break;
                // }
            } while (opMenuClientes != 27);
            break;
        case 'E':
            // insercaoAutomDeDados();
            break;
        }

    } while (opMenuPrincipal != 27);
}

int main()
{
    executar();
    gotoxy(3, 26);
    return 0;
}

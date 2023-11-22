#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>

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
    long long int cpfCliente;
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

// #FUNCOES DE VENDAS#
void efetuarVenda(void);
void cupomFiscalDeVenda(void);
void recuperarProdutosDeUmaVenda(tpVendasProdutos v[50], int &tl, int codVenda, FILE *ptrVendasProdutos);
int buscaVendaExaustiva(FILE *ptr, int codVenda);
void relatorioDeVendas(void);
void exclusaoLogicaVendas(void);
int buscaVendaEmVendaProd(FILE *ptrVendasProd, int codVenda);

// #FUNCOES DE PRODUTOS#
int buscaProdutoExaustiva(FILE *ptr, int codProd);
void cadastroProdutos(void);
void consultaProdutos(void);
void alteracaoProdutos(void);
void relatorioProdutos(int veioDeVendas);
void ordenarProdutosPorPreco(void);
void exclusaoDeProdutoLogica(void);

// exclusaoProdutos();

// #FUNCOES DE FORNECEDORES#
int buscaFornecedorExaustiva(FILE *ptr, int codForn);
int buscaProdutoPorFornecedor(FILE *ptr, int codForn);
void cadastroFornecedores(void);
void consultaFornecedores(void);
void alteracaoFornecedores(void);
void relatorioFornecedores(void);
void exclusaoLogicaFornecedor(void);
void aumentoDePreco();
int buscaProdVendasProd(FILE *ptr, int codProd);

// #FUNCOES DE CLIENTES#
int buscaClientesExaustiva(FILE *PtrClintes, long long int cpfCli);
int bucaClientesBinaria(FILE *PtrClintes, long long int cpfCli);
void cadastroClienteInsercaoDireta(void);
void consultaClientes(void);
void exclusaoLogicaClientes (void);
void alteraCliente(void);
void relatorioClientes(void);
int buscaVendasCPF (FILE *ptr,long long int CPF);
int buscaCodVendaEmVendaProd (FILE *ptr,int codVenda);

// #FUNCOES AUXILIARES#
int jaEstaContidoNoVetor(tpProduto v[100], int codProd, int tl);
void auxAcharProdutosDoFornecedor(int &tl, FILE *ptr, int codForn, tpProduto produtos[50]);
void insercaoAutomDeDados(void);
void executar(void);

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

    moldura(1, 1, 80, 5, 10, 2);
    moldura(1, 6, 80, 25, 10, 2);
    gotoxy(31, 1);
    printf("* * * TITULO * * *");
}

// # FUNÇÕES DE MENU

char menuFornecedores(void)
{
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
    printf("[F] Ordenar Produtos por Preco");
    gotoxy(2, 14);
    printf("[ESC] Voltar para menu principal");
    gotoxy(2, 15);
    printf("Opcao desejada: ");
    return toupper(getche());
}

char menuVendas(void)
{
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
    printf("[D] Cupom fiscal de uma venda");
    gotoxy(2, 12);
    printf("[ESC] Voltar para menu principal");
    gotoxy(2, 13);
    printf("Opcao desejada: ");
    return toupper(getche());
}

char menuClientes(void)
{
    system("cls");
    exibirMoldura();
    gotoxy(27, 3);
    printf("### MENU CLIENTES ###");
    gotoxy(2, 8);
    printf("[A] Cadastro de Clientes por Insercao Direta");
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
    return toupper(getche());
}

// #FUNÇÕES DE VENDAS#
int buscaVendaExaustiva(FILE *ptr, int codVenda)
{
    tpVenda R;
    rewind(ptr);

    fread(&R, sizeof(tpVenda), 1, ptr);
    while (!feof(ptr) && !(codVenda == R.codVenda && R.ativo == 1))
        fread(&R, sizeof(tpVenda), 1, ptr);

    if (!feof(ptr))
        return ftell(ptr) - sizeof(tpVenda);
    else
        return -1;
}

void efetuarVenda(void)
{
    system("cls");
    FILE *ptrClientes = fopen("clientes.bat", "rb+");
    FILE *ptrVendas = fopen("vendas.bat", "rb+");
    FILE *ptrVendasProdutos = fopen("vendas_produtos.bat", "rb+");
    if (ptrClientes == NULL || ptrVendas == NULL || ptrVendasProdutos == NULL)
    {
        printf("\nErro na abertura de arquivo!\n");
    }
    else
    {
        tpCliente cliente;
        printf("### EFETUAR VENDA ###");
        printf("\nCpf do cliente comprador: ");
        scanf("%lld", &cliente.cpfCliente);
        while (cliente.cpfCliente != 0)
        {
            int posCliente = buscaClientesExaustiva(ptrClientes, cliente.cpfCliente);
            if (posCliente == -1)
            {
                printf("\nCliente nao encontrado, indo para cadastro de clientes: ");
                cliente.qtdeCompras = 0;
                cliente.ativo = 1;
                printf("\nDigite o nome do cliente: ");
                fflush(stdin);
                gets(cliente.nomeCliente);
                cliente.valorTotalComprado = 0.00;
            }
            else
            {
                fseek(ptrClientes, posCliente, 0);
                fread(&cliente, sizeof(tpCliente), 1, ptrClientes);
                printf("\nCliente %s encontrado!\n", cliente.nomeCliente);
            }

            // abriu arq de prod e fornecedores
            relatorioProdutos(1);
            // fechou arq prod e forn
            FILE *ptrProdutos = fopen("produtos.bat", "rb+");
            if (ptrProdutos == NULL)
            {
                printf("\nErro na abertura de arquivo!\n");
            }
            else
            {
                tpProduto v[100], prod;
                int qtd[100], tl = 0;

                printf("\nDigite o codigo do produto que deseja vender, digite 0 para sair: ");
                scanf("%d", &prod.codProd);
                while (prod.codProd != 0)
                {
                    int posProd = buscaProdutoExaustiva(ptrProdutos, prod.codProd);
                    int jaExiste = jaEstaContidoNoVetor(v, prod.codProd, tl);
                    if (posProd == -1 || jaExiste == 1)
                    {
                        printf("\nProduto nao encontrado ou ja foi adicionado!\n");
                    }
                    else
                    {
                        fseek(ptrProdutos, posProd, 0);
                        fread(&prod, sizeof(tpProduto), 1, ptrProdutos);
                        printf("\nProduto: ");
                        printf("\nDescricao: ");
                        puts(prod.descricao);
                        printf("Estoque: %d", prod.estoque);
                        printf("\nPreco: R$ %.2f", prod.preco);
                        printf("\nData de validade: %d/%d/%d", prod.data.d, prod.data.m, prod.data.a);

                        int quant;
                        printf("\nQual a quantidade que deseja? ");
                        scanf("%d", &quant);
                        while (quant == 0 || quant > prod.estoque)
                        {
                            printf("\nQuantidade invalida, verifique o estoque do produto e digite novamente: ");
                            scanf("%d", &quant);
                        }
                        v[tl] = prod;
                        qtd[tl] = quant;
                        tl++;
                    }
                    printf("Digite outro codigo do produto que deseja vender, digite 0 para sair: ");
                    scanf("%d", &prod.codProd);
                }
                if (tl == 0)
                {
                    printf("\nVenda abortada!\n");
                }
                else
                {
                    printf("\n-----------------------------------------------------\n");
                    printf("Resumo da venda para o cliente %s:", cliente.nomeCliente);
                    float total = 0.0;
                    printf("\nProdutos: ");
                    for (int i = 0; i < tl; i++)
                    {
                        printf("\n\nDescricao: ");
                        puts(v[i].descricao);
                        printf("Preco: R$ %.2f", v[i].preco);
                        printf("\nQuantidade: %d", qtd[i]);
                        total += v[i].preco * qtd[i];
                    }
                    printf("\nTotal: %.2f", total);
                    printf("\nConfirma compra? (S/N): ");
                    char confirma = toupper(getche());
                    if (confirma == 'S')
                    {
                        time_t agora;
                        struct tm *infoTempo;
                        time(&agora);
                        infoTempo = localtime(&agora);
                        if (posCliente == -1)
                        {
                            fseek(ptrClientes, 0, 2);
                        }
                        else
                        {
                            fseek(ptrClientes, posCliente, 0);
                        }
                        cliente.qtdeCompras += 1;
                        cliente.valorTotalComprado += total;
                        fwrite(&cliente, sizeof(tpCliente), 1, ptrClientes);

                        tpVenda venda;
                        fseek(ptrVendas, -sizeof(tpVenda), 2);
                        fread(&venda, sizeof(tpVenda), 1, ptrVendas);
                        venda.ativo = 1;
                        venda.codVenda += 1;
                        venda.cpfCliente = cliente.cpfCliente;
                        venda.data.d = infoTempo->tm_mday;
                        venda.data.m = infoTempo->tm_mon + 1;
                        venda.data.a = infoTempo->tm_year + 1900;
                        venda.totalVendas = total;
                        fseek(ptrVendas, 0, 2);
                        fwrite(&venda, sizeof(tpVenda), 1, ptrVendas);

                        // diminuir estoque do produto e criar vendas_produtos
                        for (int i = 0; i < tl; i++)
                        {
                            v[i].estoque -= qtd[i];
                            int posProduto = buscaProdutoExaustiva(ptrProdutos, v[i].codProd);
                            fseek(ptrProdutos, posProduto, 0);
                            fwrite(&v[i], sizeof(tpProduto), 1, ptrProdutos);

                            tpVendasProdutos vend_prod;
                            vend_prod.codVenda = venda.codVenda;
                            vend_prod.codProd = v[i].codProd;
                            vend_prod.ativo = 1;
                            vend_prod.qtde = qtd[i];
                            vend_prod.valorUnitario = v[i].preco;
                            fseek(ptrVendasProdutos, 0, 2);
                            fwrite(&vend_prod, sizeof(tpVendasProdutos), 1, ptrVendasProdutos);
                        }
                    }
                    else
                    {
                        printf("\nVenda abortada!\n");
                    }
                }
                fclose(ptrProdutos);
            }
            printf("\nCpf do cliente comprador, digite 0 para sair: ");
            scanf("%lld", &cliente.cpfCliente);
        }
        fclose(ptrClientes);
        fclose(ptrVendas);
        fclose(ptrVendasProdutos);
    }
    system("cls");
    exibirMoldura();
}

void cupomFiscalDeVenda(void)
{
    system("cls");
    FILE *ptrClientes = fopen("clientes.bat", "rb+");
    FILE *ptrVendas = fopen("vendas.bat", "rb+");
    FILE *ptrVendasProdutos = fopen("vendas_produtos.bat", "rb+");
    FILE *ptrProdutos = fopen("produtos.bat", "rb+");
    FILE *ptrFornecedores = fopen("fornecedores.bat", "rb+");
    if (ptrClientes == NULL || ptrVendas == NULL || ptrVendasProdutos == NULL || ptrProdutos == NULL)
    {
        printf("\nErro na abertura de arquivo!\n");
    }
    else
    {
        tpVenda venda;
        tpCliente cliente;
        printf("### CUPOM FISCAL DE VENDA ###");
        printf("\nDigite o codigo da venda, ou 0 para sair: ");
        scanf("%d", &venda.codVenda);
        while (venda.codVenda != 0)
        {
            int posVenda = buscaVendaExaustiva(ptrVendas, venda.codVenda);
            if (posVenda == -1)
            {
                printf("\nVenda nao encontrada!\n");
            }
            else
            {

                fseek(ptrVendas, posVenda, 0);
                fread(&venda, sizeof(tpVenda), 1, ptrVendas);
                printf("\nVenda:\n");
                printf("Codigo da venda: %d", venda.codVenda);

                int posCliente = buscaClientesExaustiva(ptrClientes, venda.cpfCliente);
                fseek(ptrClientes, posCliente, 0);
                fread(&cliente, sizeof(tpCliente), 1, ptrClientes);
                printf("\nCliente: ");
                puts(cliente.nomeCliente);
                printf("\nProdutos: ");
                tpVendasProdutos v[100];
                int tl = 0;
                recuperarProdutosDeUmaVenda(v, tl, venda.codVenda, ptrVendasProdutos);
                tpProduto prod;
                tpFornecedor forn;
                for (int i = 0; i < tl; i++)
                {
                    int posProd = buscaProdutoExaustiva(ptrProdutos, v[i].codProd);
                    fseek(ptrProdutos, posProd, 0);
                    fread(&prod, sizeof(tpProduto), 1, ptrProdutos);
                    int posForn = buscaFornecedorExaustiva(ptrFornecedores, prod.codForn);
                    fseek(ptrFornecedores, posForn, 0);
                    fread(&forn, sizeof(tpFornecedor), 1, ptrFornecedores);
                    printf("\n%d\t%s\t\t%d\tR$ %.2f\t%s", prod.codProd, prod.descricao, v[i].qtde, v[i].valorUnitario, forn.nomeForn);
                }
                printf("\nTotal R$ %.2f", venda.totalVendas);
            }
            printf("\nDigite o codigo da venda, ou 0 para sair: ");
            scanf("%d", &venda.codVenda);
        }

        fclose(ptrClientes);
        fclose(ptrVendas);
        fclose(ptrVendasProdutos);
        fclose(ptrProdutos);
        fclose(ptrFornecedores);
    }
    system("cls");
    exibirMoldura();
}

void recuperarProdutosDeUmaVenda(tpVendasProdutos v[50], int &tl, int codVenda, FILE *ptrVendasProdutos)
{
    tpVendasProdutos vend_prod;
    rewind(ptrVendasProdutos);
    fread(&vend_prod, sizeof(tpVendasProdutos), 1, ptrVendasProdutos);
    while (!feof(ptrVendasProdutos))
    {
        if (vend_prod.codVenda == codVenda && vend_prod.ativo == 1)
        {
            v[tl] = vend_prod;
            tl++;
        }
        fread(&vend_prod, sizeof(tpVendasProdutos), 1, ptrVendasProdutos);
    }
}

void relatorioDeVendas(void)
{
    FILE *ptrClientes = fopen("clientes.bat", "rb+");
    FILE *ptrFornecedores = fopen("fornecedores.bat", "rb+");
    FILE *ptrProdutos = fopen("produtos.bat", "rb+");
    FILE *ptrVendas = fopen("vendas.bat", "rb+");
    FILE *ptrVendasProds = fopen("vendas_produtos.bat", "rb+");
    system("cls");
    if (ptrClientes == NULL || ptrFornecedores == NULL || ptrProdutos == NULL || ptrVendas == NULL || ptrVendasProds == NULL)
    {
        printf("\nErro na abertura de arquivo!\n");
        printf("\nDigite algo para retornar: ");
        getche();
    }
    else
    {
        tpCliente cliente;
        tpVenda venda;
        printf("\n### RELATORIO DE VENDAS ###\n");
        rewind(ptrVendas);
        fread(&venda, sizeof(tpVenda), 1, ptrVendas);
        while (!feof(ptrVendas))
        {
            if (venda.ativo == 1) {
                printf("\nCodigo da venda: %d", venda.codVenda);
                int posCliente = buscaClientesExaustiva(ptrClientes, venda.cpfCliente);
                fseek(ptrClientes, posCliente, 0);
                fread(&cliente, sizeof(tpCliente), 1, ptrClientes);
                printf("\nCliente: ");
                puts(cliente.nomeCliente);

                printf("\nProdutos: ");
                tpVendasProdutos v[100];
                int tl = 0;
                recuperarProdutosDeUmaVenda(v, tl, venda.codVenda, ptrVendasProds);
                tpProduto prod;
                tpFornecedor forn;
                for (int i = 0; i < tl; i++)
                {
                    int posProd = buscaProdutoExaustiva(ptrProdutos, v[i].codProd);
                    fseek(ptrProdutos, posProd, 0);
                    fread(&prod, sizeof(tpProduto), 1, ptrProdutos);
                    int posForn = buscaFornecedorExaustiva(ptrFornecedores, prod.codForn);
                    fseek(ptrFornecedores, posForn, 0);
                    fread(&forn, sizeof(tpFornecedor), 1, ptrFornecedores);
                    printf("\n%d\t%s\t\t%d\tR$ %.2f\t%s", prod.codProd, prod.descricao, v[i].qtde, v[i].valorUnitario, forn.nomeForn);
                }
                printf("\nTotal R$ %.2f", venda.totalVendas);
                printf("\n----------------------------------------\n");
            }
            fread(&venda, sizeof(tpVenda), 1, ptrVendas);
        }

        fclose(ptrClientes);
        fclose(ptrFornecedores);
        fclose(ptrProdutos);
        fclose(ptrVendas);
        fclose(ptrVendasProds);
        printf("\nDigite algo para retornar: ");
        getche();
    }
    system("cls");
    exibirMoldura();
}

void exclusaoLogicaVendas(void)
{
    FILE *ptrVenda = fopen("vendas.bat", "rb+");
    FILE *ptrVendasProds = fopen("vendas_produtos.bat", "rb+");
    FILE *ptrClientes = fopen("clientes.bat", "rb+");
    FILE *ptrProds = fopen("produtos.bat", "rb+");

    tpCliente regClientes;
    tpVendasProdutos regVendasProd;
    tpVenda regVenda;
    tpProduto regProds;
    system("cls");
    if (ptrClientes == NULL || ptrVendasProds == NULL || ptrVenda == NULL)
    {
        printf("\nerro na abertura de arquivo\n");
        getch();
    }
    else
    {
        printf("\nDigite o codigo da venda a ser excluido: \n");
        scanf("%d", &regVenda.codVenda);

        while (regVenda.codVenda > 0)
        {
            int pos = buscaVendaExaustiva(ptrVenda, regVenda.codVenda);
            if (pos == -1)
            {
                printf("\nvenda inexistente!!\n");
                getch();
            }
            else
            {
                fseek(ptrVenda, pos, 0);
                fread(&regVenda, sizeof(tpVenda), 1, ptrVenda);
                printf("\nCodigo da venda: %d\n", regVenda.codVenda);
                printf("\nCPF do cliente: %lld\n", regVenda.cpfCliente);
                printf("\nData da venda %d/%d/%d", regVenda.data.d, regVenda.data.m, regVenda.data.a);
                printf("\nDeseja mesmo excluir essa venda (S/N): ");

                if (toupper(getche()) == 'S')
                {
                    regVenda.ativo = 0;
                    fseek(ptrVenda, pos, 0);
                    fwrite(&regVenda, sizeof(tpVenda), 1, ptrVenda);
                    //
                    pos = buscaVendaEmVendaProd(ptrVendasProds, regVenda.codVenda);
                    fseek(ptrVendasProds, pos, 0);
                    fread(&regVendasProd, sizeof(tpVendasProdutos), 1, ptrVendasProds);
                    regVendasProd.ativo = 0;
                    int qtde = regVendasProd.qtde;
                    float vUnitario = regVendasProd.valorUnitario;
                    fseek(ptrVendasProds, pos, 0);
                    fwrite(&regVendasProd, sizeof(tpVendasProdutos), 1, ptrVendasProds);
                    //
                    pos = buscaClientesExaustiva(ptrClientes, regClientes.cpfCliente);
                    fseek(ptrClientes, pos, 0);
                    fread(&regClientes, sizeof(tpCliente), 1, ptrClientes);
                    regClientes.valorTotalComprado = regClientes.valorTotalComprado - (qtde * vUnitario);
                    regClientes.valorTotalComprado--;
                    fseek(ptrClientes, pos, 0);
                    fwrite(&regClientes, sizeof(tpCliente), 1, ptrClientes);
                    //
                    pos = buscaProdutoExaustiva(ptrProds, regVendasProd.codProd);
                    fseek(ptrProds, pos, 0);
                    fread(&regProds, sizeof(tpProduto), 1, ptrProds);
                    regProds.estoque += qtde;
                    fseek(ptrProds, pos, 0);
                    fwrite(&regProds, sizeof(tpProduto), 1, ptrProds);
                    printf("\nVenda deletada com sucesso!!\n");
                    getch();
                }
                else
                {
                    printf("\nVenda abortada com sucesso!!\n");
                    getch();
                }
            }
            printf("digite outro codigo ou (0) para sair: ");
            scanf("%d", &regVenda.codVenda);
        }
    }
    fclose(ptrClientes);
    fclose(ptrProds);
    fclose(ptrVenda);
    fclose(ptrVendasProds);
    system("cls");
    exibirMoldura();
}

int buscaVendaEmVendaProd(FILE *ptrVendasProd, int codVenda)
{
    tpVendasProdutos reg;

    rewind(ptrVendasProd);

    fread(&reg, sizeof(tpVendasProdutos), 1, ptrVendasProd);
    while (!feof(ptrVendasProd) && !(codVenda == reg.codVenda && reg.ativo == 1))
        fread(&reg, sizeof(tpVendasProdutos), 1, ptrVendasProd);
    if (!feof(ptrVendasProd))
        ftell(ptrVendasProd) - sizeof(tpVendasProdutos);
    else
        return -1;
}

// #FUNÇÕES DE PRODUTOS#

int buscaProdutoExaustiva(FILE *ptr, int codProd)
{
    tpProduto R;
    rewind(ptr);

    fread(&R, sizeof(tpProduto), 1, ptr);
    while (!feof(ptr) && !(codProd == R.codProd && R.ativo == 1))
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
                printf("Estoque: %d", prod.estoque);
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

void relatorioProdutos(int veioDeVendas = 0)
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
        printf("### RELATORIO DE PRODUTOS ###");
        fread(&prod, sizeof(tpProduto), 1, ptrProdutos);
        while (!feof(ptrProdutos))
        {
            printf("\n-----------------------------------------------------------------------------------");
            printf("\nCodigo de produto: %d", prod.codProd);
            printf("\nDescricao: ");
            puts(prod.descricao);
            printf("Estoque: %d", prod.estoque);
            printf("\nPreco: R$ %.2f", prod.preco);
            printf("\nData de validade: %d/%d/%d", prod.data.d, prod.data.m, prod.data.a);

            if (veioDeVendas == 0)
            {
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

            fread(&prod, sizeof(tpProduto), 1, ptrProdutos);
        }
        fclose(ptrProdutos);
        fclose(ptrFornecedores);
        printf("\n-----------------------------------------------------------------------------------");
        if (veioDeVendas == 0)
        {
            printf("\nTecle algo para voltar");
            getch();
        }
    }
    if (veioDeVendas == 0)
    {
        system("cls");
        exibirMoldura();
    }
}

void ordenarProdutosPorPreco(void)
{
    system("cls");
    int a, b, QtdeReg;
    tpProduto RA, RB;

    FILE *ptrProdutos = fopen("produtos.bat", "rb+");
    printf("\n### ORDENACAO DE PRODUTOS POR PRECO CRESCENTE ###\n");

    if (ptrProdutos == NULL) // O Arquivo n�o existe!
    {
        printf("\nErro de abertura, digite algo para sair: \n");
        getch();
    }
    else
    {
        fseek(ptrProdutos, 0, 2);
        QtdeReg = ftell(ptrProdutos) / sizeof(tpProduto);

        for (a = 0; a < QtdeReg - 1; a++)
            for (b = a + 1; b < QtdeReg; b++)
            {
                fseek(ptrProdutos, a * sizeof(tpProduto), 0);
                fread(&RA, sizeof(tpProduto), 1, ptrProdutos);

                fseek(ptrProdutos, b * sizeof(tpProduto), 0);
                fread(&RB, sizeof(tpProduto), 1, ptrProdutos);

                if (RA.preco > RB.preco)
                {
                    fseek(ptrProdutos, a * sizeof(tpProduto), 0);
                    fwrite(&RB, sizeof(tpProduto), 1, ptrProdutos);

                    fseek(ptrProdutos, b * sizeof(tpProduto), 0);
                    fwrite(&RA, sizeof(tpProduto), 1, ptrProdutos);
                }
            }
        fclose(ptrProdutos);
        printf("\nArquivo Ordenado, digite algo para sair: ");
        getch();
    }
    system("cls");
    exibirMoldura();
}

void exclusaoDeProdutoLogica(void)
{
    FILE *ptrProd = fopen("produtos.bat", "rb+");
    tpProduto Registro;

    printf("\nDigite o codido do produto a excluir: \n");
    scanf("%d", &Registro.codProd);

    while (!feof(ptrProd) && Registro.codProd > 0)
        ;
    {
        int pos = buscaProdutoExaustiva(ptrProd, Registro.codProd);
        if (pos == -1)
        {
            printf("\nCliente inexistente!\n");
            printf("Digite [ESC] para sair: ");
            getch();
        }
        else
        {
            fseek(ptrProd, pos, 0);
            fread(&Registro, sizeof(tpProduto), 1, ptrProd);
            printf("Codigo do produto: %d\n", Registro.codForn);
            printf("Preco: %.2f\n", Registro.preco);
            printf("Descricao: %s\n", Registro.descricao);
            printf("Data: %d/%d/%d\n", Registro.data.d, Registro.data.m, Registro.data.a);
            printf("\nConfirma exclusao (S/N): ");
            if (toupper(getche()) == 'S')
            {
                fseek(ptrProd, pos, 0);
                Registro.ativo = 0;
                fwrite(&Registro, sizeof(tpProduto), 1, ptrProd);
            }
        }
    }
}

// #FUNÇÕES DE FORNECEDORES

int buscaFornecedorExaustiva(FILE *ptr, int codForn)
{
    tpFornecedor R;
    rewind(ptr); // fseek(ptr,0,0);

    fread(&R, sizeof(tpFornecedor), 1, ptr);
    while (!feof(ptr) && !(codForn == R.codForn && R.ativo == 1))
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

void relatorioFornecedores(void)
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
        printf("### RELATORIO DE FIRNECEDORES ###");
        fread(&forn, sizeof(tpFornecedor), 1, ptrFornecedores);
        while (!feof(ptrFornecedores))
        {
            printf("\n-----------------------------------------------------------------------------------");

            printf("\nCodigo do fornecedor: %d", forn.codForn);
            printf("\nNome do fornecedor: ");
            puts(forn.nomeForn);
            printf("Cidade do fornecedor: ");
            puts(forn.cidadeForn);

            int tl = 0;
            tpProduto v[50];
            auxAcharProdutosDoFornecedor(tl, ptrProdutos, forn.codForn, v);
            if (tl == 0)
            {
                printf("Nao ha produtos fornecidos");
            }
            else
            {
                printf("\nProdutos fornecidos: ");
                int i = 0;
                for (int i = 0; i < tl; i++)
                {
                    printf("\n\nCodigo de produto: %d", v[i].codProd);
                    printf("\nDescricao: ");
                    puts(v[i].descricao);
                    printf("Estoque: %d", v[i].estoque);
                    printf("\nPreco: R$ %.2f", v[i].preco);
                    printf("\nData de validade: %d/%d/%d", v[i].data.d, v[i].data.m, v[i].data.a);
                }
            }
            fread(&forn, sizeof(tpFornecedor), 1, ptrFornecedores);
        }
        fclose(ptrProdutos);
        fclose(ptrFornecedores);
        printf("\n-----------------------------------------------------------------------------------");
        printf("\nTecle algo para voltar");
        getch();
    }
    system("cls");
    exibirMoldura();
}

int buscaProdutoPorFornecedor(FILE *ptr, int codForn)
{
    tpProduto R;

    rewind(ptr);
    fread(&R, sizeof(tpProduto), 1, ptr);
    while (!feof && codForn == R.codForn)
    {
        fread(&R, sizeof(tpProduto), 1, ptr);
    }
    if (!feof)
        return ftell(ptr) - sizeof(tpProduto);
    else
        return -1;
}

void aumentoDePreco()
{
    FILE *ptrForn = fopen("fornecedores.bat", "rb+");
    FILE *ptrProd = fopen("produtos.bat", "rb+");
    tpProduto RegProd;
    int aux;
    system("cls");
    printf("\nDigite o codigo do fornecedor para aumentar o preco dos produtos: \n");
    scanf("%d", &aux);
    while (aux > 0)
    {
        int pos = buscaFornecedorExaustiva(ptrForn, aux);
        if (pos == -1)
        {
            printf("\nFornecedor inexixtente\n");
            getche();
        }
        else
        {
            float porcent;
            printf("Digite a porcentagem a ser aumentada nos produtos: ");
            scanf("%f", &porcent);
            if (toupper(getche()) == 'S')
            {
                int busca = buscaProdutoPorFornecedor(ptrProd, RegProd.codForn);
                fseek(ptrProd, busca, 0);
                fread(&RegProd, sizeof(tpProduto), 1, ptrProd);
                while (!feof)
                {
                    fseek(ptrProd, busca, 0);
                    fwrite(&RegProd, sizeof(tpProduto), 1, ptrProd);
                    if (RegProd.codForn == aux)
                    {
                        RegProd.preco += porcent / 100 * RegProd.preco;
                        fwrite(&RegProd, sizeof(tpProduto), 1, ptrProd);
                    }
                    fread(&RegProd, sizeof(tpProduto), 1, ptrProd);
                }
            }
            else
            {
                printf("\nAumento de preco abortado!!\n");
                getch();
            }
        }
    }
    fclose(ptrForn);
    fclose(ptrProd);
}

void exclusaoLogicaFornecedor(void)
{
    FILE *ptrForn = fopen("fornecedores.bat", "rb+");

    tpFornecedor Reg;

    system("cls");
    if (ptrForn == NULL)
    {
        printf("\nErro na abertura de arquivo\n");
        getch();
    }
    else
    {
        printf("\nDigite o codigo do fornecedor a ser excluido: \n");
        scanf("%d", &Reg.codForn);

        int pos = buscaFornecedorExaustiva(ptrForn, Reg.codForn);

        if (pos == -1)
        {
            printf("\nFornecedor nï¿½o existe!\n");
            getch();
        }
        else
        {
            fseek(ptrForn, pos, 0);
            fread(&Reg, sizeof(tpFornecedor), 1, ptrForn);
            printf("\nNome do fornecedor: %s\n", Reg.nomeForn);
            printf("\nCidade do fornecedor: %s\n", Reg.cidadeForn);
            printf("\nCodigo do fornecedor: %d\n", Reg.codForn);
            printf("\nConfirma exclusao de fornecedor (S/N): ");
            printf("\nTodos os produtos vinculados seram apagados tambem");
            if (toupper(getche()) == 'S')
            {
                Reg.ativo = 0;
                fseek(ptrForn, pos, 0);
                fwrite(&Reg, sizeof(tpFornecedor), 1, ptrForn);

                // excluir todos os produtos vinculados ao forncedor
                FILE *ptrProdutos = fopen("produtos.bat", "rb+");
                tpProduto regProd;
                pos = buscaProdutoPorFornecedor(ptrForn, Reg.codForn);
                while (!feof(ptrForn))
                {
                    if (pos != -1)
                    {
                        fseek(ptrForn, pos, 0);
                        fread(&regProd, sizeof(tpProduto), 1, ptrProdutos);
                        regProd.ativo = 0;
                        fseek(ptrForn, pos, 0);
                        fwrite(&regProd, sizeof(tpProduto), 1, ptrProdutos);
                    }
                    pos = buscaProdutoPorFornecedor(ptrProdutos, Reg.codForn);
                }
                // excluir todas as vendas prods vinculadas aos produtos
                FILE *ptrVendasProdutos = fopen("vendas_produtos.bat", "rb+");
                tpVendasProdutos regVendasProds;
                pos = buscaProdVendasProd(ptrVendasProdutos, Reg.codForn);

                while (!feof(ptrVendasProdutos))
                {
                    if (pos != 1)
                    {
                        fseek(ptrVendasProdutos, pos, 0);
                        fread(&regVendasProds, sizeof(tpVendasProdutos), 1, ptrVendasProdutos);
                        regVendasProds.ativo = 0;
                        fseek(ptrVendasProdutos, pos, 0);
                        fwrite(&regVendasProds, sizeof(tpVendasProdutos), 1, ptrVendasProdutos);
                    }
                    pos = buscaProdVendasProd(ptrVendasProdutos, Reg.codForn);
                }
                // Demonio impossivel
                //  FILE *ptrCliente = fopen("clientes.bat","rb+");
                //  tpCliente regClientes;
                //  FILE *ptrVendas= fopen("vendas.bat","rb+");
                //  tpVenda regVendas;
                //  rewind(ptrCliente);
                //  fread(&regClientes,sizeof(tpCliente),1,ptrCliente);
                //  // pos=buscaCpfClienteVendas(ptrVendas,regClientes.cpfCliente);
                //  while (!feof(ptrCliente))
                //  {
                //      if(pos != -1) {

                //         fwrite(&regClientes,sizeof(tpCliente),1,ptrCliente);
                //     }

                //     pos=buscaCpfClienteVendas(ptrVendas,regClientes.cpfCliente);
                // }

                // fclose(ptrProdutos);
                // fclose(ptrVendasProdutos);
            }
            else
            {
                printf("\nExclusao abortada!");
                getch();
            }
        }
        fclose(ptrForn);
    }
    system("cls");
    exibirMoldura();
}

int buscaProdVendasProd(FILE *ptr, int codProd)
{

    tpVendasProdutos R;
    rewind(ptr);

    fread(&R, sizeof(tpVendasProdutos), 1, ptr);
    while (!feof(ptr) && !(codProd == R.codProd && R.ativo == 1))
        fread(&R, sizeof(tpVendasProdutos), 1, ptr);

    if (!feof(ptr))
        return ftell(ptr) - sizeof(tpCliente);
    else
        return -1;
}

// #FUNÇÕES DE CLIENTES

int buscaClientesExaustiva(FILE *PtrClintes, long long int cpfCli)
{
    tpCliente R;
    rewind(PtrClintes);

    fread(&R, sizeof(tpCliente), 1, PtrClintes);
    while (!feof(PtrClintes) && !(cpfCli == R.cpfCliente && R.ativo == 1))
        fread(&R, sizeof(tpCliente), 1, PtrClintes);

    if (!feof(PtrClintes))
        return ftell(PtrClintes) - sizeof(tpCliente);
    else
        return -1;
}

int bucaClientesBinaria(FILE *PtrClintes, long long int cpfCli)
{

    fseek(PtrClintes, 0, 2);
    int fim = (ftell(PtrClintes) / sizeof(tpCliente)) - 1, inicio = 0;
    while (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;
        fseek(PtrClintes, meio * sizeof(tpCliente), 0);
        tpCliente cliente;
        fread(&cliente, sizeof(tpCliente), 1, PtrClintes);
        if (cliente.cpfCliente == cpfCli && cliente.ativo == 1)
        {
            return ftell(PtrClintes) - sizeof(tpCliente);
        }
        else if (cpfCli > cliente.cpfCliente)
        {
            inicio = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }
    return -1;
}

void cadastroClienteInsercaoDireta(void)
{
    tpCliente cliente, clienteAux;
    FILE *ptr = fopen("clientes.bat", "rb+");

    system("cls");
    if (ptr == NULL)
    {
        printf("\nErro na abertura do arquivo, digite algo para sair: ");
        getch();
    }
    else
    {
        printf("\nDigite o CPF para cadastro (sem pontos): \n");
        scanf("%lld", &cliente.cpfCliente);

        while (cliente.cpfCliente > 0)
        {

            int pos = buscaClientesExaustiva(ptr, cliente.cpfCliente);

            if (pos != -1)
                printf("\nCliente ja cadastrado!!\n");
            else
            {
                printf("\nDigite o nome do cliente: \n");
                fflush(stdin);
                gets(cliente.nomeCliente);
                cliente.qtdeCompras = 0;
                cliente.valorTotalComprado = 0;
                cliente.ativo = 1;
                printf("\nConfirma cadastro (S/N): ");
                if (toupper(getche()) == 'S')
                {
                    fseek(ptr, 0, 2);
                    int qtdeClientes = (ftell(ptr) / sizeof(tpCliente)) - 1;
                    fseek(ptr, qtdeClientes * sizeof(tpCliente), 0);
                    fread(&clienteAux, sizeof(tpCliente), 1, ptr);
                    while (qtdeClientes >= 0 && stricmp(cliente.nomeCliente, clienteAux.nomeCliente) == -1)
                    {
                        fseek(ptr, qtdeClientes * sizeof(tpCliente), 0);
                        fwrite(&cliente, sizeof(tpCliente), 1, ptr);
                        fseek(ptr, (qtdeClientes + 1) * sizeof(tpCliente), 0);
                        fwrite(&clienteAux, sizeof(tpCliente), 1, ptr);
                        qtdeClientes--;
                        fseek(ptr, qtdeClientes * sizeof(tpCliente), 0);
                        fread(&clienteAux, sizeof(tpCliente), 1, ptr);
                    }
                }
                else
                    printf("\nCadastro do cliente abortado\n");
            }
            printf("\nDigite outro CPF ou (0) para cancelar: ");
            scanf("%lld", &cliente.cpfCliente);
        }
        fclose(ptr);
    }

    system("cls");
    exibirMoldura();
}

void consultaClientes(void)
{
    FILE *ptr = fopen("clientes.bat", "rb");
    tpCliente R;
    system("cls");
    if (ptr == NULL)
        printf("\nNao a clientes para consulta\n");
    else
    {
        printf("Digite o CPF do cliente: ");
        scanf("%lld", &R.cpfCliente);

        while (R.cpfCliente > 0)
        {
            int pos = buscaClientesExaustiva(ptr, R.cpfCliente);

            if (pos == -1)
                printf("\nCliente nao encontrado\n");
            else
            {
                fseek(ptr, pos, 0);
                fread(&R, sizeof(tpCliente), 1, ptr);
                printf("\nCPF do cliente: %lld\n", R.cpfCliente);
                printf("\nNome do cliente: %s\n", R.nomeCliente);
                printf("\nQuantidade de compras feitas: %d\n", R.qtdeCompras);
                printf("\nValor total comprado: %.2f\n", R.valorTotalComprado);
            }
            printf("\nDigite o cpf do cliente ou (0) para sair: \n");
            scanf("%lld", &R.cpfCliente);
        }
    }
    fclose(ptr);
    exibirMoldura();
}

void relatorioClientes(void)
{
    FILE *ptr = fopen("clientes.bat", "rb");
    tpCliente R;
    system("cls");

    if (ptr == NULL)
    {
        printf("\nNao foi possivel abrir o arquivo, digite algo para sair\n");
        getch();
    }
    else
    {
        printf("\n### RELATORIO DE CLIENTES ###\n");

        rewind(ptr);
        fread(&R, sizeof(tpCliente), 1, ptr);
        while (!feof(ptr))
        {
            
            if(R.ativo == 1) 
            {
                printf("\n\nCPF: %lld", R.cpfCliente);  
                printf("\nNome: ");
                puts(R.nomeCliente);
                printf("Quantidade de compras: %d", R.qtdeCompras);
                printf("\nValor total comprado: %.2f", R.valorTotalComprado);
            }
            fread(&R, sizeof(tpCliente), 1, ptr);
        }
        fclose(ptr);
        printf("\nDigite algo para sair: ");
        getch();
    }

    system("cls");
    exibirMoldura();
}

void alteraCliente(void)
{
    FILE *ptr = fopen("clientes.bat", "rb+");
    tpCliente registro;

    system("cls");

    if (ptr == NULL)
    {
        printf("\nNao foi possivel de abrir o arquivo!\n");
        getch();
    }
    else
    {

        while (registro.cpfCliente > 0)
        {
            printf("\nDigite o CPF do cliente a ser alterado: ");
            scanf("%lld", &registro.cpfCliente);

            int pos = buscaClientesExaustiva(ptr, registro.cpfCliente);
            if (pos == -1)
            {
                printf("\ncliente nao encontrado\n");
                getch();
            }
            else
            {
                printf("\nDigite o novo nome do cliente: ");
                gets(registro.nomeCliente);
                fread(&registro, sizeof(tpCliente), 1, ptr);
                fseek(ptr, pos, 0);
                fwrite(&registro, sizeof(tpCliente), 1, ptr);

                printf("\nCliente alterado com sucesso!!\n");
            }
            printf("\nDigite o CPF para alterar outro cliente ou (0) para sair!\n");
        }
    }
    fclose(ptr);
}

void exclusaoLogicaClientes (void)
{
    FILE *ptrCliente = fopen ("clientes.bat","rb+");
    FILE *ptrVendas = fopen("vendas.bat","rb+");
    FILE *ptrVendasProd = fopen("vendas_produtos.bat","rb+");
    FILE *ptrProdutos = fopen("produtos.bat","rb+");

    tpCliente regCliente;
    tpVenda regVendas;
    tpProduto regProduto;
    tpVendasProdutos regVendasProds;
    system("cls");
    if (ptrCliente == NULL || ptrVendas == NULL || ptrVendasProd == NULL || ptrProdutos == NULL)
    {
        fclose(ptrCliente);
        fclose(ptrProdutos);
        fclose(ptrVendas);
        fclose(ptrVendasProd);
        printf("\nNao foi possivel abrir o arquivo!\n");
        printf("\nPresione qualquer tecla para voltar ao menu");
        getch();
    }
    else 
    {
        printf("\nDigite o CPF para exclusao: \n");
        scanf("%lld",&regCliente.cpfCliente);
        while(regCliente.cpfCliente > 0){
            int pos = buscaClientesExaustiva(ptrCliente,regCliente.cpfCliente);
            if(pos==-1) {
                printf("\nCliente não existe!\n");
                printf("presione qualquer tecla para continuar");
                getch();
                system("cls");
            }
            else {
                fseek(ptrCliente,pos,0);
                fread(&regCliente,sizeof(tpCliente),1,ptrCliente);
                printf("\nNome do cliente: %s\n",regCliente.nomeCliente);
                printf("\nCPF do cliente %lld\n",regCliente.cpfCliente);
                printf("\nValor total comprado %.2f\n",regCliente.valorTotalComprado);
                printf("\nQuantidade de compras: %d\n",regCliente.qtdeCompras);
                printf("\nConfirma exclusao (S/N): ");
                if(toupper(getche())=='S') {
                    //cliente
                    fseek(ptrCliente,pos,0);
                    regCliente.ativo=0;
                    fwrite(&regCliente,sizeof(tpCliente),1,ptrCliente);
                    //vendas
                    rewind(ptrVendas);
                    int aux = buscaVendasCPF(ptrVendas,regCliente.cpfCliente);
                    fseek(ptrVendas,aux,0);
                    fread(&regVendas,sizeof(tpVenda),1,ptrVendas);
                    //vendasProd
                    rewind(ptrVendasProd);
                    int venda = buscaCodVendaEmVendaProd(ptrVendasProd,regVendas.codVenda);
                    fseek(ptrVendasProd,venda,0);
                    fread(&regVendasProds,sizeof(tpVendasProdutos),1,ptrVendasProd);
                    //Produtos
                    rewind(ptrProdutos);
                    int prod=buscaProdutoExaustiva(ptrProdutos,regVendasProds.codProd);
                    fseek(ptrProdutos,prod,0);
                    fread(&regProduto,sizeof(tpProduto),1,ptrProdutos);
                    int qtde;
                    while(!feof(ptrVendas))
                    {
                        if(aux!=-1)
                        {
                            regVendas.ativo=0;
                            fseek(ptrVendas,aux,0);
                            fwrite(&regVendas,sizeof(tpVenda),1,ptrVendas);

                            regVendasProds.ativo=0;
                            fseek(ptrVendasProd,venda,0);
                            fwrite(&regVendasProds,sizeof(tpVendasProdutos),1,ptrVendasProd);

                            qtde=regVendasProds.qtde;
                            regProduto.estoque+=qtde;
                            fseek(ptrProdutos,prod,0);
                            fwrite(&regProduto,sizeof(tpProduto),1,ptrProdutos);

                        }
                        aux=buscaVendasCPF(ptrVendas,regCliente.cpfCliente);
                        fseek(ptrVendas,aux,0);
                        fread(&regVendas,sizeof(tpVenda),1,ptrVendas);

                        venda = buscaCodVendaEmVendaProd(ptrVendasProd,regVendas.codVenda);
                        fseek(ptrVendasProd,venda,0);
                        fread(&regVendasProds,sizeof(tpVendasProdutos),1,ptrVendasProd);

                        prod=buscaProdutoExaustiva(ptrProdutos,regVendasProds.codProd);
                        fseek(ptrProdutos,prod,0);
                        fread(&regProduto,sizeof(tpProduto),1,ptrProdutos);
                    }
                    printf("\nExclusao feita com sucesso!!\n");
                    printf("\nPressione qualquer tecla para continuar\n");
                    getch();
                    system("cls");
                }
                else
                {
                    printf("\nExclusao de clientes abortada!!\n");
                    printf("\nPresione qualquer tecla para continuar\n");
                    system("cls");
                    getch();

                }
            }
            printf("\nDigite outro cpf para excluir ou (0) para sair\n");
            scanf("%lld",&regCliente.cpfCliente);
        }
        fclose(ptrCliente);
        fclose(ptrProdutos);
        fclose(ptrVendas);
        fclose(ptrVendasProd);
    }
    system("cls");
    exibirMoldura();
}

int buscaVendasCPF (FILE *ptr,long long int CPF)
{
    tpVenda regVendas;

    rewind(ptr);
    fread(&regVendas,sizeof(tpVenda),1,ptr);

    while (!feof(ptr) && !(CPF == regVendas.cpfCliente && regVendas.ativo == 1))
        fread(&regVendas,sizeof(tpVenda),1,ptr);
    
    if(!feof(ptr)) return ftell(ptr) - sizeof(tpVenda);
    
    else return -1;
}

int buscaCodVendaEmVendaProd (FILE *ptr,int codVenda)
{
    tpVenda regVendaProd;
    rewind(ptr);
    fread(&regVendaProd,sizeof(tpVendasProdutos),1,ptr);

    while (!feof && !(codVenda == regVendaProd.codVenda && regVendaProd.ativo == 1))
        fread(&regVendaProd,sizeof(tpVendasProdutos),1,ptr);
    
    if(!feof(ptr)) return ftell(ptr) - sizeof(tpVendasProdutos);

    else return-1;
}
// #FUNÇÕES AUXILIARES

int jaEstaContidoNoVetor(tpProduto v[100], int codProd, int tl)
{
    for (int i = 0; i < tl; i++)
    {
        if (v[i].codProd == codProd)
        {
            return 1;
        }
    }
    return 0;
}

void auxAcharProdutosDoFornecedor(int &tl, FILE *ptr, int codForn, tpProduto produtos[50])
{
    tl = 0;
    tpProduto R;
    rewind(ptr); // fseek(ptr,0,0);

    fread(&R, sizeof(tpProduto), 1, ptr);

    while (!feof(ptr))
    {
        if (R.ativo == 1 && R.codForn == codForn)
        {
            produtos[tl] = R;
            tl++;
        }
        fread(&R, sizeof(tpProduto), 1, ptr);
    }
}

void insercaoAutomDeDados(void)
{
    FILE *PtrClientes = fopen("clientes.bat", "ab");
    FILE *PtrFornecedors = fopen("fornecedores.bat", "ab");
    FILE *PtrProdutos = fopen("produtos.bat", "ab");
    FILE *PtrVendas_Produtos = fopen("vendas_produtos.bat", "ab");
    FILE *PtrVendas = fopen("vendas.bat", "ab");

    tpCliente Cliente;
    tpProduto Produto;
    tpFornecedor Fornecedor;
    tpVenda Venda;
    tpVendasProdutos VendasProds;

    // clientes
    fseek(PtrClientes, 0, 2);
    Cliente.cpfCliente = 38989178860;
    Cliente.ativo = 1;
    Cliente.valorTotalComprado = 4556.60;
    Cliente.qtdeCompras = 1;
    strcpy(Cliente.nomeCliente, "Daniel Andreassi");
    fwrite(&Cliente, sizeof(tpCliente), 1, PtrClientes);

    fseek(PtrClientes, 0, 2);
    Cliente.cpfCliente = 15577433045;
    Cliente.ativo = 1;
    Cliente.valorTotalComprado = 0;
    Cliente.qtdeCompras = 0;
    strcpy(Cliente.nomeCliente, "fernandinho");
    fwrite(&Cliente, sizeof(tpCliente), 1, PtrClientes);

    fseek(PtrClientes, 0, 2);
    Cliente.cpfCliente = 73959525028;
    Cliente.ativo = 1;
    strcpy(Cliente.nomeCliente, "Vitinho");
    Cliente.qtdeCompras = 1;
    Cliente.valorTotalComprado = 10000;
    fwrite(&Cliente, sizeof(tpCliente), 1, PtrClientes);

    // fornecedores
    fseek(PtrFornecedors, 0, 2);
    strcpy(Fornecedor.nomeForn, "Joaozinho da feira");
    strcpy(Fornecedor.cidadeForn, "Anhumas");
    Fornecedor.codForn = 1;
    Fornecedor.ativo = 1;
    fwrite(&Fornecedor, sizeof(tpFornecedor), 1, PtrFornecedors);

    fseek(PtrFornecedors, 0, 2);
    strcpy(Fornecedor.nomeForn, "Osmar da oficina");
    strcpy(Fornecedor.cidadeForn, "Presidente Prudente");
    Fornecedor.codForn = 2;
    Fornecedor.ativo = 1;
    fwrite(&Fornecedor, sizeof(tpFornecedor), 1, PtrFornecedors);

    fseek(PtrFornecedors, 0, 2);
    strcpy(Fornecedor.nomeForn, "matheus do programa");
    strcpy(Fornecedor.cidadeForn, "taciba");
    Fornecedor.codForn = 3;
    Fornecedor.ativo = 1;
    fwrite(&Fornecedor, sizeof(tpFornecedor), 1, PtrFornecedors);

    // produto
    fseek(PtrProdutos, 0, 2);
    Produto.codForn = 1;
    Produto.codProd = 10;
    Produto.estoque = 98;
    strcpy(Produto.descricao, "Melancia");
    Produto.preco = 25.99;
    Produto.data.a = 2023;
    Produto.data.m = 12;
    Produto.data.d = 31;
    Produto.ativo = 1;
    fwrite(&Produto, sizeof(tpProduto), 1, PtrProdutos);

    fseek(PtrProdutos, 0, 2);
    Produto.codForn = 1;
    Produto.codProd = 11;
    Produto.estoque = 8;
    strcpy(Produto.descricao, "Kiwi");
    Produto.preco = 29.98;
    Produto.data.a = 2023;
    Produto.data.m = 11;
    Produto.data.d = 2;
    Produto.ativo = 1;
    fwrite(&Produto, sizeof(tpProduto), 1, PtrProdutos);

    fseek(PtrProdutos, 0, 2);
    Produto.codForn = 1;
    Produto.codProd = 12;
    Produto.estoque = 8;
    strcpy(Produto.descricao, "Banana");
    Produto.preco = 15.49;
    Produto.data.a = 2024;
    Produto.data.m = 1;
    Produto.data.d = 1;
    Produto.ativo = 1;
    fwrite(&Produto, sizeof(tpProduto), 1, PtrProdutos);
    //
    fseek(PtrProdutos, 0, 2);
    Produto.codForn = 2;
    Produto.codProd = 20;
    Produto.estoque = 5;
    strcpy(Produto.descricao, "Bateria de carro");
    Produto.preco = 300;
    Produto.data.a = 2030;
    Produto.data.m = 9;
    Produto.data.d = 7;
    Produto.ativo = 1;
    fwrite(&Produto, sizeof(tpProduto), 1, PtrProdutos);

    fseek(PtrProdutos, 0, 2);
    Produto.codForn = 2;
    Produto.codProd = 21;
    Produto.estoque = 12;
    strcpy(Produto.descricao, "Motor de opala");
    Produto.preco = 4000;
    Produto.data.a = 2040;
    Produto.data.m = 3;
    Produto.data.d = 21;
    Produto.ativo = 1;
    fwrite(&Produto, sizeof(tpProduto), 1, PtrProdutos);

    fseek(PtrProdutos, 0, 2);
    Produto.codForn = 2;
    Produto.codProd = 22;
    Produto.estoque = 16;
    strcpy(Produto.descricao, "Pneu aro 18");
    Produto.preco = 120;
    Produto.data.a = 2029;
    Produto.data.m = 4;
    Produto.data.d = 30;
    Produto.ativo = 1;
    fwrite(&Produto, sizeof(tpProduto), 1, PtrProdutos);
    //
    fseek(PtrProdutos, 0, 2);
    Produto.codForn = 3;
    Produto.codProd = 30;
    Produto.estoque = 90;
    strcpy(Produto.descricao, "Sistema em python");
    Produto.preco = 5000;
    Produto.data.a = 2030;
    Produto.data.m = 5;
    Produto.data.d = 7;
    Produto.ativo = 1;
    fwrite(&Produto, sizeof(tpProduto), 1, PtrProdutos);

    fseek(PtrProdutos, 0, 2);
    Produto.codForn = 3;
    Produto.codProd = 31;
    Produto.estoque = 4;
    strcpy(Produto.descricao, "Sistema em java");
    Produto.preco = 10000;
    Produto.data.a = 2041;
    Produto.data.m = 3;
    Produto.data.d = 21;
    Produto.ativo = 1;
    fwrite(&Produto, sizeof(tpProduto), 1, PtrProdutos);

    fseek(PtrProdutos, 0, 2);
    Produto.codForn = 3;
    Produto.codProd = 32;
    Produto.estoque = 16;
    strcpy(Produto.descricao, "sistema em assembly");
    Produto.preco = 9999999;
    Produto.data.a = 2080;
    Produto.data.m = 2;
    Produto.data.d = 28;
    Produto.ativo = 1;
    fwrite(&Produto, sizeof(tpProduto), 1, PtrProdutos);
    // vendas produtos
    fseek(PtrVendas_Produtos, 0, 2);
    VendasProds.codVenda = 1;
    VendasProds.codProd = 31;
    VendasProds.qtde = 1;
    VendasProds.valorUnitario = 10000;
    VendasProds.ativo = 1;
    fwrite(&VendasProds, sizeof(tpVendasProdutos), 1, PtrVendas_Produtos);
    //
    fseek(PtrVendas_Produtos, 0, 2);
    VendasProds.codVenda = 2;
    VendasProds.codProd = 11;
    VendasProds.qtde = 20;
    VendasProds.valorUnitario = 29.98;
    VendasProds.ativo = 1;
    fwrite(&VendasProds, sizeof(tpVendasProdutos), 1, PtrVendas_Produtos);
    //
    fseek(PtrVendas_Produtos, 0, 2);
    VendasProds.codVenda = 3;
    VendasProds.codProd = 21;
    VendasProds.qtde = 10;
    VendasProds.valorUnitario = 4000;
    VendasProds.ativo = 1;
    fwrite(&VendasProds, sizeof(tpVendasProdutos), 1, PtrVendas_Produtos);
    // vendas
    fseek(PtrVendas, 0, 2);
    Venda.codVenda = 1;
    Venda.cpfCliente = 73959525028;
    Venda.data.a = 2023;
    Venda.data.m = 3;
    Venda.data.d = 19;
    Venda.ativo = 1;
    Venda.totalVendas = 10000;
    fwrite(&Venda, sizeof(tpVenda), 1, PtrVendas);
    //
    fseek(PtrVendas, 0, 2);
    Venda.codVenda = 2;
    Venda.cpfCliente = 38989178860;
    Venda.data.a = 2023;
    Venda.data.m = 10;
    Venda.data.d = 10;
    Venda.ativo = 1;
    Venda.totalVendas = 599.6;
    fwrite(&Venda, sizeof(tpVenda), 1, PtrVendas);
    //
    fseek(PtrVendas, 0, 2);
    Venda.codVenda = 3;
    Venda.cpfCliente = 38989178860;
    Venda.data.a = 2023;
    Venda.data.m = 11;
    Venda.data.d = 10;
    Venda.ativo = 1;
    Venda.totalVendas = 40000;
    fwrite(&Venda, sizeof(tpVenda), 1, PtrVendas);

    fclose(PtrClientes);
    fclose(PtrFornecedors);
    fclose(PtrProdutos);
    fclose(PtrVendas);
    fclose(PtrVendas_Produtos);
}

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
                switch (opMenuVendas)
                {
                case 'A':
                    efetuarVenda();
                    break;
                case 'B':
                    relatorioDeVendas();
                    break;
                case 'C':
                    exclusaoLogicaVendas();
                    break;
                case 'D':
                    cupomFiscalDeVenda();
                    break;
                }
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
                case 'E':
                    relatorioProdutos();
                    break;
                case 'F':
                    ordenarProdutosPorPreco();
                    break;
                }
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
                case 'C':
                    exclusaoLogicaFornecedor();
                    break;
                case 'D':
                    alteracaoFornecedores();
                    break;
                case 'E':
                    relatorioFornecedores();
                    break;
                case 'F':
                    aumentoDePreco();
                    break;
                }
            } while (opMenuFornecedores != 27);
            break;
        case 'D':
            char opMenuClientes;
            do
            {
                opMenuClientes = menuClientes();
                switch (opMenuClientes)
                {
                case 'A':
                    cadastroClienteInsercaoDireta();
                    break;
                case 'B':
                    consultaClientes();
                    break;
                case 'C':
                    exclusaoLogicaClientes();
                    break;
                case 'D':
                    alteraCliente();
                    break;
                case 'E':
                    relatorioClientes();
                    break;
                }
            } while (opMenuClientes != 27);
            break;
        case 'E':
            insercaoAutomDeDados();
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

// oque falta:
// para arranjos desordenados
// Busca Exaustiva com Sentinela.

// metodos de ordenacao
// Seleção Direta (Selection Sort): Fornecedores

// exclusao logica de fornecedores semi feita 
//arrumar efetuar venda
// exclusao logica de produtos incompleta 

//exclusao fisica de tudo 
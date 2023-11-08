#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include <windows.h>
#include <ctype.h>

//#FUNCOES DE MENUS#
menuPrincipal();
menuVendas();
menuProdutos();
menuFornecedores();
menuClientes();
//#FUNCOES DE VENDAS#
efetuarVenda();
relatorioDeVendas();
exclusaoDeVendas();
//#FUNCOES DE PRODUTOS#
cadastroProdutos();
consultaProdutos();
exclusaoProdutos();
alteracaoProdutos();
relatorioProdutos();
//#FUNCOES DE FORNECEDORES#
cadastroForn();
consultaForn();
exclusaoForn();
alteracaoFornecedores();
relatorioFornecedores();
aumentoDePreco();
//#FUNCOES DE CLIENTES#
cadastroCliente();
consultaClientes();
exclusaoClientes();
alteracaoClientes();
relatorioClientes();
//#FUNCOES DE INSERCAO AUTOMATICA DE DADOS#
insercaoAutomDeDados();
//fazer cupo fiscal
//todas as funcoes do executar estao declaradas mas sem tipo e sem paramentros, pois ainda nao foram feitas
//fazer buscas,remanejamneto de dados, ordenacao, relatorios, exclusoes, alteracoes, cadastros, consultas, etc

void executar ()
{

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
                    exclusaoDeVendas();
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
                case 'C':
                    exclusaoProdutos();
                    break;
                case 'D':
                    alteracaoProdutos();
                    break;
                case 'E':
                    relatorioProdutos();
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
                    cadastroForn();
                    break;
                case 'B':
                    consultaForn();
                    break;
                case 'C':
                    exclusaoForn();
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
                    cadastroCliente();
                    break;
                case 'B':
                    consultaClientes();
                    break;
                case 'C':
                    exclusaoClientes();
                    break;
                case 'D':
                    alteracaoClientes();
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
    return 0;
}
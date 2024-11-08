/*=============== Trabalho de Algoritmos II ===============

 ---- Programa para o gerenciamento de uma lanchonete ----

    Grupo:
        >> ANA PAULA GONDIN BASTOS
        >> FELIPE MONEDA GILIOLI
        >> VITOR HUGO RIBEIRO FRANCO

===========================================================
*/

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

//Estruturas
typedef struct{
    int dia;
    int mes;
    int ano;
}Data;

typedef struct{
    int numeroRua;
    char nomeRua[100];
}Endereco;

//Estruturas Base
typedef struct{
    int codigoProduto;
    int qtdProduto;
    float precoProduto;
    char descricaoProduto[200];
}Produto;

typedef struct{
    int cpf;
    int codigoVenda;
    int qtdVenda;
}Venda;

typedef struct{
    int cpfCliente;
    int telefoneCliente;
    char nomeCliente[30];
    Endereco enderecoCliente;
    Data dataCliente;
}Cliente;


//Funções;
void menu();

void adicionarCliente(){}

void excluirCliente(){}

void consultarCliente(){}

void alterarCliente(){}

void listagemClientes(){}

void funcaoCliente(){
    //incluir as funções de adicionar/excluir/consultar/alterar cliente
    int opcao;
    do{
        printf("1. Adicionar\n");
        printf("2. Excluir\n");
        printf("3. Consultar\n");
        printf("4. Alterar\n");
        printf("0. Voltar para o Menu\n>> ");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                adicionarCliente();
                break;
            case 2:
                excluirCliente();
                break;
            case 3:
                consultarCliente();
                break;
            case 4:
                alterarCliente();
                break;
        }
    }while(opcao != 0);
}

void adicionarProduto(){}

void excluirProduto(){}

void consultarProduto(){}

void alterarProduto(){}

void listagemProdutos(){}

void funcaoProduto(){
    //incluir as funções de adicionar/excluir/consultar/alterar produto
    int opcao;
    do{
        printf("1. Adicionar\n");
        printf("2. Excluir\n");
        printf("3. Consultar\n");
        printf("4. Alterar\n");
        printf("0. Voltar para o Menu\n>> ");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                adicionarProduto();
                break;
            case 2:
                excluirProduto();
                break;
            case 3:
                consultarProduto();
                break;
            case 4:
                alterarProduto();
                break;
        }
    }while(opcao != 0);
}

void registrarVenda(){}

void alterarVenda(){}

void consultarVenda(){}

void excluirVenda(){}

void listagemVendas(){}

void funcaoVenda(){
    //incluir as funções de adicionar/excluir/consultar/alterar venda
    int opcao;
    do{
        printf("1. Adicionar\n");
        printf("2. Excluir\n");
        printf("3. Consultar\n");
        printf("4. Alterar\n");
        printf("0. Voltar para o Menu\n>> ");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                registrarVenda();
                break;
            case 2:
                excluirVenda();
                break;
            case 3:
                consultarVenda();
                break;
            case 4:
                alterarVenda();
                break;
        }
    }while(opcao != 0);
}

void menu(){
    int opcao;
    do{
        printf("==================== Menu ====================\n");
        printf("1. Adicionar/Excluir/Consultar/Alterar Cliente\n");
        printf("2. Listagem de Clientes\n");
        printf("3. Adicionar/Excluir/Consultar/Alterar Produto\n");
        printf("4. Listagem de Produtos\n");
        printf("5. Adicionar/Excluir/Consultar/Alterar Venda\n");
        printf("6. Listagem de vendas\n");
        printf("0. Sair\n");
        printf("==============================================\n>> ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                funcaoCliente();
                break;
            case 2:
                listagemClientes();
                break;
            case 3:
                funcaoProduto();
                break;
            case 4:
                listagemProdutos();
                break;
            case 5:
                funcaoVenda();
                break;
            case 6:
                listagemVendas();
                break;
            case 0:
                break;
            default:
                printf("Opção Inválida!\n");
                break;
        }
    }while(opcao != 0);
}


//Início do Programa(chamada da função 'menu')
int main(){
    setlocale(LC_ALL,"portuguese");
    menu();
}


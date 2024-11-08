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

//vetores globais
Cliente clientes[100];
int numeroClientes = 0;
Produto produtos[100];
int numeroProdutos = 0;
Venda vendas[100];
int numeroVendas = 0;

//Funcoes;
void menu();

void adicionarCliente(){

if (numeroClientes < 100) {
        Cliente novoCliente;
        printf("Digite o CPF do cliente: ");
        scanf("%d", &novoCliente.cpfCliente);
        printf("Digite o nome do cliente: ");
        scanf("%s", novoCliente.nomeCliente);
        printf("Digite o telefone do cliente: ");
        scanf("%d", &novoCliente.telefoneCliente);
        printf("Digite o número da rua: ");
        scanf("%d", &novoCliente.enderecoCliente.numeroRua);
        printf("Digite o nome da rua: ");
        scanf("%s", novoCliente.enderecoCliente.nomeRua);
        printf("Digite a data de nascimento (dia mes ano): ");
        scanf("%d %d %d", &novoCliente.dataCliente.dia, &novoCliente.dataCliente.mes, &novoCliente.dataCliente.ano);

        clientes[numeroClientes++] = novoCliente;
        printf("Cliente adicionado com sucesso!\n");
    } else {
        printf("Capacidade máxima de clientes atingida.\n");
    }


}

void excluirCliente(){

    int cpf;
    printf("Digite o CPF do cliente que deseja excluir: ");
    scanf("%d", &cpf);
    
    for (int i = 0; i < numeroClientes; i++) {
        if (clientes[i].cpfCliente == cpf) {
            // Substitui o cliente a ser excluído pelo último cliente do vetor
            clientes[i] = clientes[numeroClientes - 1];
            numeroClientes--; // Reduz o total de clientes
            printf("Cliente excluído com sucesso!\n");
            return;
        }
    }

}

void consultarCliente(){

}

void alterarCliente(){

}

void listagemClientes(){

}

void funcaoCliente(){
    //incluir as funcoes de adicionar/excluir/consultar/alterar cliente
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

void adicionarProduto(){
    /*int codigoProduto;
    int qtdProduto;
    float precoProduto;
    char descricaoProduto[200];*/
}

void excluirProduto(){

    int codigo;
    printf("Digite o CPF do cliente que deseja excluir: ");
    scanf("%d", &codigo);
    
    for (int i = 0; i < numeroProdutos; i++) {
        if (produtos[i].codigoProduto == codigo) {
            produtos[i] = produtos[numeroProdutos - 1];
            numeroProdutos--;
            printf("Produto excluído com sucesso!\n");
            return;
        }
    }

}

void consultarProduto(){}

void alterarProduto(){}

void listagemProdutos(){}

void funcaoProduto(){
    //incluir as funcoes de adicionar/excluir/consultar/alterar produto
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

void registrarVenda(){
    /* int cpf;
    int codigoVenda;
    int qtdVenda;*/
}

void alterarVenda(){
    int codigo;
    printf("Digite o CPF do cliente que deseja excluir: ");
    scanf("%d", &codigo);
    
    for (int i = 0; i < numeroVendas; i++) {
        if (vendas[i].codigoVenda == codigo) {
            vendas[i] = vendas[numeroVendas - 1];
            numeroVendas--; 
            printf("Venda excluído com sucesso!\n");
            return;
        }
    }
}

void consultarVenda(){}

void excluirVenda(){}

void listagemVendas(){}

void funcaoVenda(){
    //incluir as fun��es de adicionar/excluir/consultar/alterar venda
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
                printf("Opcaoo Invalida!\n");
                break;
        }
    }while(opcao != 0);
}


//In�cio do Programa(chamada da fun��o 'menu')
int main(){
    setlocale(LC_ALL,"portuguese");
    menu();
 
}


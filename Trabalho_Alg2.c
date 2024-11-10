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
    char dia[3];
    char mes[3];
    char ano[5];
}Data;

typedef struct{
    int numeroRua;
    char nomeRua[100];
}Endereco;

typedef struct{
    int codigoProduto;
    int qtdProduto;
    float precoProduto;
    char descricaoProduto[200];
}Produto;

typedef struct{
    char cpf[12];
    int codigoVenda;
    int qtdVenda;
}Venda;

typedef struct{
    char cpfCliente[12];
    long int telefoneCliente;
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

//Variaveis Globais
FILE *arq;
fpos_t p0, p1;



//Funcoes;
void menu();

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void adicionarCliente(){

if (numeroClientes < 100) {

    arq=fopen("arquivos/clientes.txt","a+");
    if(arq==NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
        Cliente novoCliente;
        char buffer[100];

        do {
            printf("Digite o CPF do cliente (11 digitos): ");
            fgets(novoCliente.cpfCliente, sizeof(novoCliente.cpfCliente), stdin);
            novoCliente.cpfCliente[strcspn(novoCliente.cpfCliente, "\n")] = 0; 
            if(strlen(novoCliente.cpfCliente) != 11){
            printf("CPF inválido. Digite novamente.\n");
            }
        } while(strlen(novoCliente.cpfCliente) != 11);
        fprintf(arq, "CPF: %s\n", novoCliente.cpfCliente);

        limparBufferEntrada();
        
        printf("Digite o nome do cliente: ");
        fgets(novoCliente.nomeCliente, sizeof(novoCliente.nomeCliente), stdin);
        novoCliente.nomeCliente[strcspn(novoCliente.nomeCliente, "\n")] = 0; 
        fprintf(arq, "Nome: %s\n", novoCliente.nomeCliente);

        printf("Digite o telefone do cliente: ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%ld", &novoCliente.telefoneCliente);
        fprintf(arq, "Telefone: %ld\n", novoCliente.telefoneCliente);

        printf("Digite o numero da rua: ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &novoCliente.enderecoCliente.numeroRua);
        fprintf(arq, "Numero da rua: %d\n", novoCliente.enderecoCliente.numeroRua);

        printf("Digite o nome da rua: ");
        fgets(novoCliente.enderecoCliente.nomeRua, sizeof(novoCliente.enderecoCliente.nomeRua), stdin);
        novoCliente.enderecoCliente.nomeRua[strcspn(novoCliente.enderecoCliente.nomeRua, "\n")] = 0; 
        fprintf(arq, "Nome da rua: %s\n", novoCliente.enderecoCliente.nomeRua);

        printf("Digite a data de nascimento (DD MM YYYY): ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%2s %2s %4s", novoCliente.dataCliente.dia, novoCliente.dataCliente.mes, novoCliente.dataCliente.ano);
        fprintf(arq, "Data de nascimento: %s/%s/%s\n", novoCliente.dataCliente.dia, novoCliente.dataCliente.mes, novoCliente.dataCliente.ano);
        
        fprintf(arq, "\n");

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
        limparBufferEntrada();
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
    //incluir as funcoes de adicionar/excluir/consultar/alterar venda
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
                printf("Opcao Invalida!\n");
                break;
        }
    }while(opcao != 0);
}


//Inicio do Programa(chamada da funcao 'menu')
int main(){
    setlocale(LC_ALL,"portuguese");
    menu();

}


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
#define MAX = 100;

//Estruturas 
typedef struct{
    char dia[3];
    char mes[3];
    char ano[5];
}Data;

typedef struct{
    int numeroCasa;
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
int totalClientes = 0;
Produto produtos[100];
int totalProdutos = 0;
Venda vendas[100];
int totalVendas = 0;

//Arquivos 
// Funções para manipular arquivos
void salvarClientes() {
    FILE *file = fopen("clientes.dat", "wb");
    if (file == NULL) {
        printf("Erro ao abrir arquivo de clientes.\n");
        return;
    }
    fwrite(&totalClientes, sizeof(int), 1, file);
    fwrite(clientes, sizeof(Cliente), totalClientes, file);
    fclose(file);
}

void carregarClientes() {
    FILE *file = fopen("clientes.dat", "rb");
    if (file == NULL) {
        printf("Nenhum cliente encontrado. Criando novo arquivo...\n");
        return;
    }
    fread(&totalClientes, sizeof(int), 1, file);
    fread(clientes, sizeof(Cliente), totalClientes, file);
    fclose(file);
}

void salvarProdutos() {
    FILE *file = fopen("produtos.dat", "wb");
    if (file == NULL) {
        printf("Erro ao abrir arquivo de produtos.\n");
        return;
    }
    fwrite(&totalProdutos, sizeof(int), 1, file);
    fwrite(produtos, sizeof(Produto), totalProdutos, file);
    fclose(file);
}

void carregarProdutos() {
    FILE *file = fopen("produtos.dat", "rb");
    if (file == NULL) {
        printf("Nenhum produto encontrado. Criando novo arquivo...\n");
        return;
    }
    fread(&totalProdutos, sizeof(int), 1, file);
    fread(produtos, sizeof(Produto), totalProdutos, file);
    fclose(file);
}

void salvarVendas() {
    FILE *file = fopen("vendas.dat", "wb");
    if (file == NULL) {
        printf("Erro ao abrir arquivo de vendas.\n");
        return;
    }
    fwrite(&totalVendas, sizeof(int), 1, file);
    fwrite(vendas, sizeof(Venda), totalVendas, file);
    fclose(file);
}

void carregarVendas() {
    FILE *file = fopen("vendas.dat", "rb");
    if (file == NULL) {
        printf("Nenhuma venda encontrada. Criando novo arquivo...\n");
        return;
    }
    fread(&totalVendas, sizeof(int), 1, file);
    fread(vendas, sizeof(Venda), totalVendas, file);
    fclose(file);
}


//Funcoes;
void menu();

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void adicionarCliente(){
 
    if (totalClientes >= 100) {
        printf("Limite de clientes atingido.\n");
        return;
    }
    
    Cliente c;
    printf("CPF: ");
    scanf("%s", c.cpfCliente);
    printf("Nome: ");
    scanf("%s", c.nomeCliente);
    printf("Telefone: ");
    scanf("%s", c.telefoneCliente);
    printf("Endereço: ");
    scanf("%s", c.enderecoCliente);
    printf("Data de nascimento (dia mes ano): ");
    scanf("%d %d %d", &c.dataCliente);

    clientes[totalClientes++] = c;
    salvarClientes();
    printf("Cliente cadastrado com sucesso!\n");

      
}

void excluirCliente() {

    /*O Cliente so podera ser excluıdo se o mesmo, nao estiver cadastrado em nenhuma venda;*/
     
    int cpf;
    printf("Digite o CPF do cliente que deseja excluir: ");
    scanf("%d", &cpf);
    
    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].cpfCliente == cpf) {
            clientes[i] = clientes[totalClientes - 1];
            totalClientes--; 
            printf("Cliente excluído com sucesso!\n");
            return;
        }
    }
    printf("Cliente não encontrado.\n");

}

void consultarCliente() {

    char cpf[12];
    printf("Digite o CPF do cliente que deseja consultar: ");
    scanf("%s", cpf);

    for (int i = 0; i < totalClientes; i++) {
        if (strcmp(clientes[i].cpfCliente, cpf) == 0) {
            printf("Cliente encontrado!\n");
            printf("Nome: %s\n", clientes[i].nomeCliente);
            printf("Telefone: %ld\n", clientes[i].telefoneCliente);
            printf("Endereço: Rua %s, Número %d\n", clientes[i].enderecoCliente.nomeRua, clientes[i].enderecoCliente.numeroCasa);
            printf("Data de nascimento: %s/%s/%s\n", clientes[i].dataCliente.dia, clientes[i].dataCliente.mes, clientes[i].dataCliente.ano);
            return;
        }
    }
    printf("Cliente não encontrado.\n");
      
}

void alterarCliente() {

    char cpf[12];
    printf("Digite o CPF do cliente que deseja alterar: ");
    scanf("%s", cpf);

    for (int i = 0; i < totalClientes; i++) {
        if (strcmp(clientes[i].cpfCliente, cpf) == 0) {
            printf("Cliente encontrado, atualize os dados:\n");
            printf("Nome: ");
            scanf("%s", clientes[i].nomeCliente);
            printf("Telefone: ");
            scanf("%ld", &clientes[i].telefoneCliente);
            printf("Endereço (Rua, Número): ");
            scanf("%s %d", clientes[i].enderecoCliente.nomeRua, &clientes[i].enderecoCliente.numeroCasa);
            printf("Data de nascimento (dia, mês, ano): ");
            scanf("%s %s %s", clientes[i].dataCliente.dia, clientes[i].dataCliente.mes, clientes[i].dataCliente.ano);
            salvarClientes();
            printf("Cliente alterado com sucesso!\n");
            return;
        }
    }
    printf("Cliente não encontrado.\n");
     
}

void listagemClientes() {

     if (totalClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    printf("Listagem de Clientes:\n");
    for (int i = 0; i < totalClientes; i++) {
        printf("%d. CPF: %s, Nome: %s\n", i + 1, clientes[i].cpfCliente, clientes[i].nomeCliente);
    }
       
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

    if (totalProdutos >= 100) {
        printf("Limite de clientes atingido.\n");
        return;
    }
    
    Produto p;
    printf("CODIGO: ");
    scanf("%d", p.codigoProduto);
    printf("PRECO: ");
    scanf("%f",  p.precoProduto);
    printf("QUANTIDADE: ");
    scanf("%d", p.qtdProduto);
    printf("DESCRICAO: ");
    scanf("%s", p.descricaoProduto);
   

    produtos[totalProdutos++] = p;
    salvarProdutos();
    printf("Produto cadastrado com sucesso!\n");
 

}

void consultarProduto(){

    int codigo;
    printf("Digite o código do produto que deseja consultar: ");
    scanf("%d", &codigo);
    getchar(); 

    int encontrado = 0;

    for (int i = 0; i < totalClientes; i++) {
        if (produtos[i].codigoProduto == codigo) {
            encontrado = 1;
            printf("Produto encontrado!\n");
            printf("Código: %d\n", produtos[i].codigoProduto);
            printf("Quantidade: %d\n", produtos[i].qtdProduto);
            printf("Preço: %.2f\n", produtos[i].precoProduto);
            printf("Descrição: %s\n", produtos[i].descricaoProduto);
            break;
        }
    }

    if (!encontrado) {
        printf("Produto não encontrado.\n");
    }

}

void alterarProduto(){

    int codigo;
    printf("Digite o código do Produto que deseja alterar: ");
    scanf("%s", codigo);

    for (int i = 0; i < totalProdutos; i++) {
        if (strcmp(produtos[i].codigoProduto, codigo) == 0) {
            printf("Produto encontrado, atualize os dados:\n");
            printf("CODIGO: ");
            scanf("%d", produtos[i].codigoProduto);
            printf("PRECO: ");
            scanf("%f",  produtos[i].precoProduto);
            printf("QUANTIDADE: ");
            scanf("%d", produtos[i].qtdProduto);
            printf("DESCRICAO: ");
            scanf("%s", produtos[i].descricaoProduto);
            printf("Cliente alterado com sucesso!\n");
            return;
        }
    }
    printf("Cliente não encontrado.\n");

}

void listagemProdutos(){

    if (totalProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("Listagem de Produtos:\n");
    for (int i = 0; i < totalProdutos; i++) {
        printf("%d. Codigo: %s, Preco: %s\n", i + 1, produtos[i].codigoProduto, produtos[i].precoProduto);
    }


}

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
    /*int cpf;
    int codigoVenda;
    int qtdVenda;*/
    /*Se o produto estiver com a quantidade em estoque menor que a quantidade a ser vendida,
    a venda nao podera ser efetivada; 
    O cliente so podera comprar um produto, se o mesmo ja estiver cadastrado;*/

if (totalVendas >= 100) {
        printf("Limite de vendas atingido.\n");
        return;
    }

    Venda v;
    char cpf[12];
    int codigoProduto;
    int qtdVenda;

    // verificacao cliente
    printf("Digite o CPF do cliente: ");
    scanf("%s", cpf);
    int clienteEncontrado = 0;
    for (int i = 0; i < totalClientes; i++) {
        if (strcmp(clientes[i].cpfCliente, cpf) == 0) {
            clienteEncontrado = 1;
            strcpy(v.cpf, cpf);
            break;
        }
    }
    if (!clienteEncontrado) {
        printf("Cliente não cadastrado!\n");
        return;
    }

    // verificacao produto
    printf("Digite o código do produto: ");
    scanf("%d", &codigoProduto);
    int produtoEncontrado = -1;
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].codigoProduto == codigoProduto) {
            produtoEncontrado = i;
            break;
        }
    }
    if (produtoEncontrado == -1) {
        printf("Produto não cadastrado!\n");
        return;
    }

    // verificacao quantidade/estoque
    printf("Digite a quantidade de produtos para a compra: ");
    scanf("%d", &qtdVenda);
    if (produtos[produtoEncontrado].qtdProduto < qtdVenda) {
        printf("Estoque insuficiente. Quantidade disponível: %d\n", produtos[produtoEncontrado].qtdProduto);
        return;
    }

    v.codigoVenda = codigoProduto;
    v.qtdVenda = qtdVenda;
    vendas[totalVendas++] = v;
    produtos[produtoEncontrado].qtdProduto -= qtdVenda;

    salvarVendas();
    salvarProdutos();
    printf("Venda efetuada com sucesso!\n");

}

void alterarVenda(){

    int codigoVenda;
    printf("Digite o código da venda que deseja alterar: ");
    scanf("%d", &codigoVenda);

    int vendaEncontrada = -1;
    for (int i = 0; i < totalVendas; i++) {
        if (vendas[i].codigoVenda == codigoVenda) {
            vendaEncontrada = i;
            break;
        }
    }
    if (vendaEncontrada == -1) {
        printf("Venda não encontrada!\n");
        return;
    }

    Venda *v = &vendas[vendaEncontrada];
    printf("Venda encontrada! Atualize os dados:\n");
 
}

void consultarVenda(){

    int codigoVenda;
    printf("Digite o código da venda que deseja consultar: ");
    scanf("%d", &codigoVenda);

    for (int i = 0; i < totalVendas; i++) {
        if (vendas[i].codigoVenda == codigoVenda) {
            printf("Venda encontrada!\n");
            printf("CPF do cliente: %s\n", vendas[i].cpf);
            printf("Código do produto: %d\n", vendas[i].codigoVenda);
            printf("Quantidade vendida: %d\n", vendas[i].qtdVenda);
            return;
        }
    }
    printf("Venda não encontrada.\n");

}

void excluirVenda(){


}

void listagemVendas() {
    if (totalVendas == 0) {
        printf("Nenhuma venda registrada.\n");
        return;
    }

    printf("Listagem de Vendas:\n");
    for (int i = 0; i < totalVendas; i++) {
        printf("%d. CPF do cliente: %s, Código do produto: %d, Quantidade: %d\n",
               i + 1, vendas[i].cpf, vendas[i].codigoVenda, vendas[i].qtdVenda);
    }
}

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


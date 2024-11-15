/*=============== Trabalho de Algoritmos II ===============

 ---- Programa para o gerenciamento de uma lanchonete ----

    Grupo:
        >> ANA PAULA GONDIN BASTOS
        >> FELIPE MONEDA GILIOLI
        >> VITOR HUGO RIBEIRO FRANCO

===========================================================
*/

#include <stdio.h>D
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 100

//Estruturas
typedef struct{
    char dia[3];
    char mes[3];
    char ano[5];
}Data;

typedef struct{
    int numeroCasa;
    char nomeRua[100];
    char cidade[100];
    char estado[100];
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
    int codProdutoVenda;
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

//VALIDACOES E CONDICOES
int codigoProdutoJaCadastrado(int codigo) {
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].codigoProduto == codigo) {
            return 1;
        }
    }
    return 0;
}

int cpfJaCadastrado(const char *cpf) {
    for (int i = 0; i < totalClientes; i++) {
        if (strcmp(clientes[i].cpfCliente, cpf) == 0) {
            return 1; // CPF já existe
        }
    }
    return 0; // CPF nao encontrado
}


void adicionarCliente(){

    if (totalClientes >= 100) {
        printf("Limite de clientes atingido.\n");
        return;
    }
    carregarClientes();

    Cliente c;
    printf("CPF: ");
    scanf("%s", c.cpfCliente);

    if (cpfJaCadastrado(c.cpfCliente)) {
        printf("Cliente com este CPF ja esta cadastrado.\n");
        return;
    }

    printf("Nome: ");
    scanf(" %[^\n]", c.nomeCliente);
    printf("Telefone: ");
    scanf("%ld", &c.telefoneCliente);
    printf("Nome da rua: ");
    scanf(" %[^\n]", c.enderecoCliente.nomeRua);
    printf("Numero da casa: ");
    scanf("%d", &c.enderecoCliente.numeroCasa);
    printf("Data de nascimento (dia mes ano): ");
    scanf("%s %s %s", c.dataCliente.dia, c.dataCliente.mes, c.dataCliente.ano);

    clientes[totalClientes++] = c;
    salvarClientes();
    printf("Cliente cadastrado com sucesso!\n");


}

void excluirCliente() {

    /*O Cliente so podera ser excluıdo se o mesmo, nao estiver cadastrado em nenhuma venda;*/
    carregarClientes();

    char cpf[12];
    printf("Digite o CPF do cliente que deseja excluir: ");
    scanf("%s", &cpf);

   for (int i = 0; i < totalVendas; i++) {
        if (strcmp(vendas[i].cpf, cpf) == 0) {
            printf("Cliente nao pode ser excluido pois está relacionado a uma venda.\n");
            return;
        }
    }

    // Excluir o cliente
    for (int i = 0; i < totalClientes; i++) {
        if (strcmp(clientes[i].cpfCliente, cpf) == 0) {
            clientes[i] = clientes[totalClientes - 1];
            totalClientes--;
            salvarClientes();
            printf("Cliente excluido com sucesso!\n");
            return;
        }
    }
    printf("Cliente nao encontrado.\n");

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
            printf("Endereco: %s, Numero %d\n", clientes[i].enderecoCliente.nomeRua, clientes[i].enderecoCliente.numeroCasa);
            printf("Data de nascimento: %s/%s/%s\n", clientes[i].dataCliente.dia, clientes[i].dataCliente.mes, clientes[i].dataCliente.ano);
            return;
        }
    }
    printf("Cliente nao encontrado.\n");

}

void alterarCliente() {

    char cpf[12];
    printf("Digite o CPF do cliente que deseja alterar: ");
    scanf("%s", cpf);

    for (int i = 0; i < totalClientes; i++) {
        if (strcmp(clientes[i].cpfCliente, cpf) == 0) {
            printf("Cliente encontrado, atualize os dados:\n");
            printf("Nome: ");
            scanf(" %[^\n]", clientes[i].nomeCliente);
            printf("Telefone: ");
            scanf("%ld", &clientes[i].telefoneCliente);
            printf("Nome da rua: ");
            scanf(" %[^\n]", clientes[i].enderecoCliente.nomeRua);
            printf("Número da casa: ");
            scanf("%d", &clientes[i].enderecoCliente.numeroCasa);
            printf("Data de nascimento (dia, mês, ano): ");
            scanf("%s %s %s", clientes[i].dataCliente.dia, clientes[i].dataCliente.mes, clientes[i].dataCliente.ano);
            salvarClientes();
            printf("Cliente alterado com sucesso!\n");
            return;
        }
    }
    printf("Cliente nao encontrado.\n");

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
    
    carregarProdutos();

    if (totalProdutos >= 100) {
        printf("Limite de produtos atingido.\n");
        return;
    }

    Produto p;
    printf("Codigo do Produto: ");
    scanf("%d", &p.codigoProduto);

    if (codigoProdutoJaCadastrado(p.codigoProduto)) {
        printf("Produto com este codigo ja esta cadastrado.\n");
        return;
    }

    printf("Descricao: ");
    scanf(" %[^\n]", p.descricaoProduto);
    printf("Quantidade: ");
    scanf("%d", &p.qtdProduto);
    printf("Preco: ");
    scanf("%f", &p.precoProduto);

    produtos[totalProdutos++] = p;
    salvarProdutos();
    printf("Produto cadastrado com sucesso!\n");

}

void excluirProduto() {

    carregarProdutos();

    int codigoProduto;
    printf("Digite o codigo do produto que deseja excluir: ");
    scanf("%d", &codigoProduto);

    // Verificar se o produto está relacionado a uma venda
    for (int i = 0; i < totalVendas; i++) {
        if (vendas[i].codigoVenda == codigoProduto) {
            printf("Produto nao pode ser excluido pois está relacionado a uma venda.\n");
            return;
        }
    }

    // Excluir o produto
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].codigoProduto == codigoProduto) {
            produtos[i] = produtos[totalProdutos - 1]; // Substituir pelo último produto
            totalProdutos--;
            salvarProdutos();
            printf("Produto excluido com sucesso!\n");
            return;
        }
    }
    printf("Produto nao encontrado.\n");
}

void consultarProduto(){

    carregarProdutos();

    int codigo;
    printf("Digite o Codigo do produto que deseja consultar: ");
    scanf("%d", &codigo);

    int encontrado = 0;

    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].codigoProduto == codigo) {
            encontrado = 1;
            printf("Produto encontrado!\n");
            printf("Codigo: %d\n", produtos[i].codigoProduto);
            printf("Quantidade: %d\n", produtos[i].qtdProduto);
            printf("Preco: %.2f\n", produtos[i].precoProduto);
            printf("Descricao: %s\n", produtos[i].descricaoProduto);
            break;
        }
    }

    if (!encontrado) {
        printf("Produto nao encontrado.\n");
    }

}

void alterarProduto(){

    carregarProdutos();

    int codigo;
    printf("Digite o codigo do Produto que deseja alterar: ");
    scanf("%d", &codigo);

    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].codigoProduto == codigo) {
            printf("Produto encontrado, atualize os dados:\n");
            printf("CODIGO: ");
            scanf("%d", &produtos[i].codigoProduto);
            printf("PRECO: ");
            scanf("%f",  &produtos[i].precoProduto);
            printf("QUANTIDADE: ");
            scanf("%d", &produtos[i].qtdProduto);
            printf("DESCRICAO: ");
            scanf(" %[^\n]", produtos[i].descricaoProduto);
            salvarProdutos();
            printf("Produto alterado com sucesso!\n");
            return;
        }
    }
    printf("Produto nao encontrado.\n");

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
   
    /*Se o produto estiver com a quantidade em estoque menor que a quantidade a ser vendida,
    a venda nao podera ser efetivada;
    O cliente so podera comprar um produto, se o mesmo ja estiver cadastrado;*/

    carregarClientes();
    carregarProdutos();
    carregarVendas();

    if (totalVendas >= 100) {
        printf("Limite de vendas atingido.\n");
        return;
    }

    Venda v;
    char cpf[12];
    int codigoProduto;
    int qtdVenda;
    int codVenda;

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
        printf("Cliente nao cadastrado!\n");
        return;
    }

    // verificacao produto
    printf("Digite o Codigo do produto: ");
    scanf("%d", &codigoProduto);
    int produtoEncontrado = -1;
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].codigoProduto == codigoProduto) {
            produtoEncontrado = i;
            break;
        }
    }
    if (produtoEncontrado == -1) {
        printf("Produto nao cadastrado!\n");
        return;
    }

    // verificacao quantidade/estoque
    printf("Digite a quantidade de produtos para a compra: ");
    scanf("%d", &qtdVenda);
    if (produtos[produtoEncontrado].qtdProduto < qtdVenda) {
        printf("Estoque insuficiente. Quantidade disponivel: %d\n", produtos[produtoEncontrado].qtdProduto);
        return;
    }

    v.codProdutoVenda = codigoProduto;
    v.codigoVenda = rand() % 1000;
    v.qtdVenda = qtdVenda;
    vendas[totalVendas++] = v;
    produtos[produtoEncontrado].qtdProduto -= qtdVenda;

    salvarVendas();
    salvarProdutos();
    printf("Venda efetuada com sucesso!\n");
    printf("Codigo da Venda: %d\n", v.codigoVenda);

}

void alterarVenda(){

    carregarVendas();

    int codigoVenda;
    printf("Digite o Codigo da venda que deseja alterar: ");
    scanf("%d", &codigoVenda);

    int vendaEncontrada = -1;
    for (int i = 0; i < totalVendas; i++) {
        if (vendas[i].codigoVenda == codigoVenda) {
            vendaEncontrada = i;
            break;
        }
    }
    if (vendaEncontrada == -1) {
        printf("Venda nao encontrada!\n");
        return;
    }

    Venda *v = &vendas[vendaEncontrada];
    printf("Venda encontrada! Atualize os dados:\n");
    for(int i = 0; i < totalVendas; i++){
        if(vendas[i].codigoVenda == codigoVenda){
            scanf("CPF:: %s\n", &vendas[i].cpf);
            scanf("Codigo do produto: %d\n", &vendas[i].codProdutoVenda);
            scanf("Quantidade: %d\n", &vendas[i].qtdVenda);
            salvarVendas();
            printf("Venda alterada com sucesso!\n");
        }
    } 

}

void consultarVenda(){

    carregarVendas();

    int codigoVenda;
    printf("Digite o Codigo da venda que deseja consultar: ");
    scanf("%d", &codigoVenda);

    for (int i = 0; i < totalVendas; i++) {
        if (vendas[i].codigoVenda == codigoVenda) {
            printf("Venda encontrada!\n");
            printf("CPF do cliente: %s\n", vendas[i].cpf);
            printf("Codigo do produto: %d\n", vendas[i].codProdutoVenda);
            printf("Quantidade vendida: %d\n", vendas[i].qtdVenda);
            return;
        }
    }
    printf("Venda nao encontrada.\n");

}

void excluirVenda(){

    carregarVendas();
    carregarProdutos();

    int codigoVenda;
    printf("Digite o Codigo da venda que deseja excluir: ");
    scanf("%d", &codigoVenda);

    for (int i = 0; i < totalVendas; i++) {
        if (vendas[i].codigoVenda == codigoVenda) { 
            // Devolver a quantidade de produto ao estoque antes de excluir
            for (int j = 0; j < totalProdutos; j++) {
                if (produtos[j].codigoProduto == vendas[i].codProdutoVenda) {
                    produtos[j].qtdProduto += vendas[i].qtdVenda;
                    break;
                }
            }

            // Substituir a venda excluida pela última venda do vetor
            vendas[i] = vendas[totalVendas - 1];
            totalVendas--;
            salvarVendas();
            salvarProdutos();
            printf("Venda excluida com sucesso!\n");
            return;
        }
    }
    printf("Venda nao encontrada.\n");

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

//RELATORIOS e LISTAGENS

void listagemVendas() {

    carregarVendas();

    if (totalVendas == 0) {
        printf("Nenhuma venda registrada.\n");
        return;
    }

    printf("Listagem de Vendas:\n");
    for (int i = 0; i < totalVendas; i++) {
        printf("%d. CPF do cliente: %s, Codigo do produto: %d, Quantidade: %d\n, Codigo da Venda: %d\n",
               i + 1, vendas[i].cpf, vendas[i].codProdutoVenda, vendas[i].qtdVenda, vendas[i].codigoVenda);
    }
}

void listagemClientes() {

    carregarClientes();

     if (totalClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    printf("Listagem de Clientes:\n");
    for (int i = 0; i < totalClientes; i++) {
        printf("%d. CPF: %s, Nome: %s\n", i + 1, clientes[i].cpfCliente, clientes[i].nomeCliente);
    }

}


void listagemProdutos(){

    carregarProdutos();

    if (totalProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("Listagem de Produtos:\n");
    for (int i = 0; i < totalProdutos; i++) {
        printf("%d. Codigo: %d, Preco: %.2f\n", i + 1, produtos[i].codigoProduto, produtos[i].precoProduto);
    }


}


void listarProdutosEstoqueBaixo() {

    carregarProdutos();

    int limiteEstoque;
    printf("Digite o valor limite de estoque: ");
    scanf("%d", &limiteEstoque);

    printf("Produtos com estoque abaixo de %d:\n", limiteEstoque);

    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].qtdProduto < limiteEstoque) {
            printf("Codigo: %d, Descricao: %s, Estoque: %d\n",
                   produtos[i].codigoProduto, produtos[i].descricaoProduto, produtos[i].qtdProduto);
        }
    }
}

void listarClientesAcimaDeValor() {

    carregarClientes();

    float valorLimite;
    printf("Digite o valor limite para listar clientes: ");
    scanf("%f", &valorLimite);

    printf("Clientes que compraram acima de %.2f:\n", valorLimite);

    for (int i = 0; i < totalClientes; i++) {
        float totalGastoCliente = 0;

        for (int j = 0; j < totalVendas; j++) {
            if (strcmp(clientes[i].cpfCliente, vendas[j].cpf) == 0) {
                for (int k = 0; k < totalProdutos; k++) {
                    if (produtos[k].codigoProduto == vendas[j].codigoVenda) {
                        totalGastoCliente += vendas[j].qtdVenda * produtos[k].precoProduto;
                        break;
                    }
                }
            }
        }

        if (totalGastoCliente > valorLimite) {
            printf("CPF: %s, Nome: %s, Total Gasto: %.2f\n",
                   clientes[i].cpfCliente, clientes[i].nomeCliente, totalGastoCliente);
        }
    }
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
    srand(time(NULL));
    menu();

}


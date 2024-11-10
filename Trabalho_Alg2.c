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

        printf("Digite o numero da casa: ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &novoCliente.enderecoCliente.numeroCasa);
        fprintf(arq, "Numero da casa: %d\n", novoCliente.enderecoCliente.numeroCasa);

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

void excluirCliente() {
    char cpf[12];
    printf("Digite o CPF do cliente que deseja excluir: ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = 0; // Remove o caractere de nova linha

    arq = fopen("arquivos/clientes.txt", "r+");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    FILE *temp = fopen("arquivos/temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao abrir o arquivo temporário\n");
        fclose(arq);
        exit(1);
    }

    char buffer[256];
    int encontrado = 0;

    while (fgets(buffer, sizeof(buffer), arq) != NULL) {
        if (strncmp(buffer, "CPF: ", 5) == 0) {
            char cpfArquivo[12];
            sscanf(buffer + 5, "%s", cpfArquivo);
            if (strcmp(cpfArquivo, cpf) == 0) {
                encontrado = 1;
                while (fgets(buffer, sizeof(buffer), arq) != NULL && strcmp(buffer, "\n") != 0);
                continue;
            }
        }
        fputs(buffer, temp);
    }

    fclose(arq);
    fclose(temp);

    if (encontrado) {
        remove("arquivos/clientes.txt");
        rename("arquivos/temp.txt", "arquivos/clientes.txt");
        printf("Cliente excluido com sucesso!\n");
    } else {
        remove("arquivos/temp.txt");
        printf("Cliente nao encontrado.\n");
    }
}

void consultarCliente() {
    char cpf[12];
    printf("Digite o CPF do cliente que deseja consultar: ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = 0; // Remove o caractere de nova linha

    arq = fopen("arquivos/clientes.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    char buffer[256];
    int encontrado = 0;

    while (fgets(buffer, sizeof(buffer), arq) != NULL) {
        if (strncmp(buffer, "CPF: ", 5) == 0) {
            char cpfArquivo[12];
            sscanf(buffer + 5, "%s", cpfArquivo);
            if (strcmp(cpfArquivo, cpf) == 0) {
                encontrado = 1;
                printf("CPF: %s\n", cpfArquivo);
                fgets(buffer, sizeof(buffer), arq);
                printf("%s", buffer); // Nome
                fgets(buffer, sizeof(buffer), arq);
                printf("%s", buffer); // Telefone
                fgets(buffer, sizeof(buffer), arq);
                printf("%s", buffer); // Numero da casa
                fgets(buffer, sizeof(buffer), arq);
                printf("%s", buffer); // Nome da rua
                fgets(buffer, sizeof(buffer), arq);
                printf("%s", buffer); // Data de nascimento
                break;
            }
        }
    }

    if (!encontrado) {
        printf("Cliente nao encontrado.\n");
    }

    fclose(arq);
}

void alterarCliente() {
    char cpf[12];
    printf("Digite o CPF do cliente que deseja alterar: ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = 0; // Remove o caractere de nova linha

    arq = fopen("arquivos/clientes.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao abrir o arquivo temporario\n");
        fclose(arq);
        return;
    }

    char buffer[256];
    int encontrado = 0;
    Cliente cliente;

    while (fgets(buffer, sizeof(buffer), arq) != NULL) {
        if (strncmp(buffer, "CPF: ", 5) == 0) {
            char cpfArquivo[12];
            sscanf(buffer + 5, "%s", cpfArquivo);
            if (strcmp(cpfArquivo, cpf) == 0) {
                encontrado = 1;
                strcpy(cliente.cpfCliente, cpfArquivo);
                fgets(buffer, sizeof(buffer), arq);
                sscanf(buffer, "Nome: %[^\n]", cliente.nomeCliente);
                fgets(buffer, sizeof(buffer), arq);
                sscanf(buffer, "Telefone: %ld", &cliente.telefoneCliente);
                fgets(buffer, sizeof(buffer), arq);
                sscanf(buffer, "Numero da casa: %d", &cliente.enderecoCliente.numeroCasa);
                fgets(buffer, sizeof(buffer), arq);
                sscanf(buffer, "Nome da rua: %[^\n]", cliente.enderecoCliente.nomeRua);
                fgets(buffer, sizeof(buffer), arq);
                sscanf(buffer, "Data de nascimento: %2s/%2s/%4s", cliente.dataCliente.dia, cliente.dataCliente.mes, cliente.dataCliente.ano);

                // Exibir informações do cliente
                printf("CPF: %s\n", cliente.cpfCliente);
                printf("Nome: %s\n", cliente.nomeCliente);
                printf("Telefone: %ld\n", cliente.telefoneCliente);
                printf("Numero da casa: %d\n", cliente.enderecoCliente.numeroCasa);
                printf("Nome da rua: %s\n", cliente.enderecoCliente.nomeRua);
                printf("Data de nascimento: %s/%s/%s\n", cliente.dataCliente.dia, cliente.dataCliente.mes, cliente.dataCliente.ano);

                int opcao;
                printf("Qual campo deseja alterar?\n");
                printf("1. Nome\n");
                printf("2. Telefone\n");
                printf("3. Numero da casa\n");
                printf("4. Nome da rua\n");
                printf("5. Data de nascimento\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcao);
                limparBufferEntrada(); 

                switch (opcao) {
                    case 1:
                        printf("Digite o novo nome: ");
                        fgets(cliente.nomeCliente, sizeof(cliente.nomeCliente), stdin);
                        cliente.nomeCliente[strcspn(cliente.nomeCliente, "\n")] = 0; // Remove o caractere de nova linha
                        break;
                    case 2:
                        printf("Digite o novo telefone: ");
                        fgets(buffer, sizeof(buffer), stdin);
                        sscanf(buffer, "%ld", &cliente.telefoneCliente);
                        break;
                    case 3:
                        printf("Digite o novo numero da casa: ");
                        fgets(buffer, sizeof(buffer), stdin);
                        sscanf(buffer, "%d", &cliente.enderecoCliente.numeroCasa);
                        break;
                    case 4:
                        printf("Digite o novo nome da rua: ");
                        fgets(cliente.enderecoCliente.nomeRua, sizeof(cliente.enderecoCliente.nomeRua), stdin);
                        cliente.enderecoCliente.nomeRua[strcspn(cliente.enderecoCliente.nomeRua, "\n")] = 0; 
                        break;
                    case 5:
                        printf("Digite a nova data de nascimento (DD MM YYYY): ");
                        fgets(buffer, sizeof(buffer), stdin);
                        sscanf(buffer, "%2s %2s %4s", cliente.dataCliente.dia, cliente.dataCliente.mes, cliente.dataCliente.ano);
                        break;
                    default:
                        printf("Opcao invalida.\n");
                        break;
                }

               
                while (fgets(buffer, sizeof(buffer), arq) != NULL && strcmp(buffer, "\n") != 0);
                continue; 
            }
        }
        fputs(buffer, temp);
    }

    if (encontrado) {
        fprintf(temp, "CPF: %s\n", cliente.cpfCliente);
        fprintf(temp, "Nome: %s\n", cliente.nomeCliente);
        fprintf(temp, "Telefone: %ld\n", cliente.telefoneCliente);
        fprintf(temp, "Numero da casa: %d\n", cliente.enderecoCliente.numeroCasa);
        fprintf(temp, "Nome da rua: %s\n", cliente.enderecoCliente.nomeRua);
        fprintf(temp, "Data de nascimento: %s/%s/%s\n", cliente.dataCliente.dia, cliente.dataCliente.mes, cliente.dataCliente.ano);
        fprintf(temp, "\n");

        fclose(arq);
        fclose(temp);

        remove("arquivos/clientes.txt");
        rename("arquivos/temp.txt", "arquivos/clientes.txt");
        printf("Cliente alterado com sucesso!\n");
    } else {
        fclose(arq);
        fclose(temp);
        remove("arquivos/temp.txt");
        printf("Cliente não encontrado.\n");
    }
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


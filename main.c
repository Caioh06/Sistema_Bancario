//Instruções de Compilação----//

//Pelo terminal integrado do VS Code: 
// 1. Abra o terminal (Ctrl + ') e digite: gcc nome_do_arquivo.c -o banco
// 2. Para executar o código digite: .\banco.exe  

//Pela Extensão C/C++ Compile Run:
// 1. Instalar a extensão.
// 2. Pressionar o botão "Play" no canto superior direito ou pressionar a tecla F6 para compilar e executar o código.

//Pelo IDE Dev-C++:
// 1. Pressione a tecla F9 para compilar o código.
// 2. Pressione a tecla F10 para executar o código, ou também, pressione a tecla F11 para compilar e executar o código.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- CONSTANTES --- //
#define MAX_CONTAS 100
#define TAM_NOME 100
#define TAM_CPF 15
#define TAM_AGENCIA 10
#define TAM_TELEFONE 20
#define ATIVA 1
#define ENCERRADA 0

// --- ESTRUTURA (STRUCT) --- //
typedef struct {
    int numero;
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char agencia[TAM_AGENCIA];
    char telefone[TAM_TELEFONE];
    double saldo;
    int status;
} Conta;

// --- PROTÓTIPOS DAS FUNÇÕES --- //
void limpar_buffer(void);
int encontrar_conta_por_numero(Conta contas[], int qtd, int numero);
int encontrar_conta_por_cpf(Conta contas[], int qtd, char* cpf);
int abrir_conta(Conta contas[], int* qtd, int* proximo_numero, int* seq_agencia);
void depositar(Conta contas[], int qtd);
void sacar(Conta contas[], int qtd);
void transferir(Conta contas[], int qtd);
void consultar_dados(Conta contas[], int qtd);
void atualizar_contato(Conta contas[], int qtd);
void listar_contas(Conta contas[], int qtd);
void encerrar_conta(Conta contas[], int qtd);
void mostrar_dados(Conta* c);

// --- FUNÇÃO PRINCIPAL (MAIN) --- //
int main() {
    Conta contas[MAX_CONTAS]; //Vetor que armazena todas as contas
    int qtd_contas = 0; //A quantidade de contas começa na posição 0
    int proximo_numero = 1001; //A primeira conta começa com o numero 1001
    int sequencia_agencia = 1; //A agencia de todas as contas recebe o numero 1
    int op;

    do {
        printf("\n--- SISTEMA BANCARIO ---\n");
        printf("1. Abrir conta\n");
        printf("2. Depositar\n");
        printf("3. Sacar\n");
        printf("4. Transferir\n");
        printf("5. Consultar saldo e dados\n");
        printf("6. Atualizar telefone e agencia\n");
        printf("7. Listar contas\n");
        printf("8. Encerrar conta\n");
        printf("9. Sair\n");
        printf("Escolha: ");
        
        scanf("%d", &op);
        limpar_buffer(); //Limpar o buffer de entrada após o scanf

        switch(op) {
            case 1: 
                abrir_conta(contas, &qtd_contas, &proximo_numero, &sequencia_agencia); //Colocamos o endereço (&) nas variaveis para que a função incremente.
                break;
            case 2: 
                depositar(contas, qtd_contas); 
                break;
            case 3: 
                sacar(contas, qtd_contas); 
                break;
            case 4: 
                transferir(contas, qtd_contas); 
                break;
            case 5: 
                consultar_dados(contas, qtd_contas); 
                break;
            case 6: 
                atualizar_contato(contas, qtd_contas); 
                break;
            case 7: 
                listar_contas(contas, qtd_contas); 
                break;
            case 8: 
                encerrar_conta(contas, qtd_contas); 
                break;
            case 9: 
                printf("Encerrando sistema...\n"); 
                break;
            default: 
                printf("Opcao invalida.\n");
        }
    } while (op != 9);

    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES --- //

void limpar_buffer(void) { //Limpar o buffer de entrada após o scanf
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { } // Lê caractere por caractere até encontrar o fim do arquivo
}

int encontrar_conta_por_numero(Conta contas[], int qtd, int numero) { //Proucura no vetor o numero da conta indicado pelo usuario, retornando a conta pertencente a esse numero 
    int i;
    for (i = 0; i < qtd; i++) {
        if (contas[i].numero == numero) {
            return i;
        }
    }
    return -1;
}

int encontrar_conta_por_cpf(Conta contas[], int qtd, char* cpf) { //Proucura no vetor uma string (cpf) que o usuario digitou, ela retorna 0 se as strings forem iguais
    int i;
    for (i = 0; i < qtd; i++) {
        if (strcmp(contas[i].cpf, cpf) == 0) {
            return i;
        }
    }
    return -1;
}

void mostrar_dados(Conta* c) { //Função que imprimi os dados de uma conta
    printf("\n--- DADOS DA CONTA ---\n");
    printf("Numero: %d\n", c->numero);
    printf("Nome: %s\n", c->nome);
    printf("CPF: %s\n", c->cpf);
    printf("Agencia: %s\n", c->agencia);
    printf("Telefone: %s\n", c->telefone);
    printf("Saldo: %.2f\n", c->saldo);
    printf("Status: %s\n", c->status == ATIVA ? "ATIVA" : "ENCERRADA"); //Mostra se a conta está ativa ou encerrada
    printf("----------------------\n");
}

int abrir_conta(Conta contas[], int* qtd, int* proximo_numero, int* seq_agencia) { //Função para abrir uma conta 
    Conta nova;
    int idx;

    if (*qtd >= MAX_CONTAS) { //Verifica se há espaço no vetor, se não houver, erro!
        printf("Erro: Limite de contas atingido.\n");
        return 0;
    }
//Lê os dados colocados pelo usuario (nome, CPF, telefone)
    printf("Nome do cliente: ");
    fgets(nova.nome, TAM_NOME, stdin);
    nova.nome[strcspn(nova.nome, "\n")] = 0;

    printf("CPF: ");
    fgets(nova.cpf, TAM_CPF, stdin);
    nova.cpf[strcspn(nova.cpf, "\n")] = 0;

    idx = encontrar_conta_por_cpf(contas, *qtd, nova.cpf); //Verifica se o CPF já está cadastrado em uma conta
    if (idx != -1 && contas[idx].status == ATIVA) {
        printf("Erro: CPF ja cadastrado em conta ativa.\n");
        return 0;
    }

    snprintf(nova.agencia, TAM_AGENCIA, "%03d", *seq_agencia); //Formata a string em memória. E utilizando '%03d', transforma o numero (1) em (001)
    printf("Agencia: %s\n", nova.agencia);
    limpar_buffer();

    printf("\nTelefone: ");
    fgets(nova.telefone, TAM_TELEFONE, stdin);
    nova.telefone[strcspn(nova.telefone, "\n")] = 0;

     
    nova.numero = *proximo_numero; //Chama por ponteiro o numero de uma nova conta
    nova.saldo = 0.0; //Determina que o saldo de uma nova conta receba 0
    nova.status = ATIVA; //Após criar uma conta ela se tornará Ativa

    contas[*qtd] = nova;
    (*qtd)++;
    (*proximo_numero)++;

    printf("Conta %d aberta com sucesso!\n", nova.numero);
    return 1;
}

void depositar(Conta contas[], int qtd) {
    int num, idx;
    double valor;

    printf("Numero da conta: ");
    scanf("%d", &num);
    
    idx = encontrar_conta_por_numero(contas, qtd, num);
    //Validação de segurança, para ver se a conta existe ou se está encerrada
    if (idx == -1) {
        printf("Conta nao encontrada.\n");
        return;
    }
    
    if (contas[idx].status == ENCERRADA) {
        printf("Erro: Conta encerrada.\n");
        return;
    }

    printf("Valor do deposito: ");
    scanf("%lf", &valor);

    if (valor <= 0) {
        printf("Erro: Valor deve ser positivo.\n");
    } else {
        contas[idx].saldo += valor;
        printf("Sucesso. Novo saldo: %.2f\n", contas[idx].saldo);
    }
}

void sacar(Conta contas[], int qtd) {
    int num, idx;
    double valor;

    printf("Numero da conta: ");
    scanf("%d", &num);

    idx = encontrar_conta_por_numero(contas, qtd, num);
    //Valida se a conta existe ou se está encerrada
    if (idx == -1) {
        printf("Conta nao encontrada.\n");
        return;
    }

    if (contas[idx].status == ENCERRADA) {
        printf("Erro: Conta encerrada.\n");
        return;
    }

    printf("Valor do saque: ");
    scanf("%lf", &valor);
    //Validação do saldo, se for insuficiente o valor não é sacado
    if (valor <= 0) {
        printf("Erro: Valor deve ser positivo.\n");
    } else if (valor > contas[idx].saldo) {
        printf("Erro: Saldo insuficiente.\n");
    } else {
        contas[idx].saldo -= valor;
        printf("Sucesso. Novo saldo: %.2f\n", contas[idx].saldo);
    }
}

void transferir(Conta contas[], int qtd) {
    int origem, destino;
    int idx_orig, idx_dest;
    double valor;

    printf("Conta Origem: ");
    scanf("%d", &origem);
    printf("Conta Destino: ");
    scanf("%d", &destino);
    //Localiza a conta de origem e a conta de destino para realizar transferência
    idx_orig = encontrar_conta_por_numero(contas, qtd, origem);
    idx_dest = encontrar_conta_por_numero(contas, qtd, destino);

    if (idx_orig == -1 || idx_dest == -1) {
        printf("Erro: Uma das contas nao existe.\n");
        return;
    }

    if (contas[idx_orig].status == ENCERRADA || contas[idx_dest].status == ENCERRADA) {
        printf("Erro: Movimentacao nao permitida em conta encerrada.\n");
        return;
    }

    printf("Valor: ");
    scanf("%lf", &valor);
    
    //Valida se há saldo suficiente antes de transferir
    if (valor <= 0 || valor > contas[idx_orig].saldo) { 
        printf("Erro: Saldo insuficiente ou valor invalido.\n");
    } else {
        contas[idx_orig].saldo -= valor;
        contas[idx_dest].saldo += valor;
        printf("Transferencia realizada com sucesso.\n");
    }
}

void consultar_dados(Conta contas[], int qtd) {
    int op_busca, num, idx;
    char cpf[TAM_CPF];

    printf("1. Buscar por numero\n2. Buscar por CPF\nEscolha: ");
    scanf("%d", &op_busca);
    limpar_buffer();

    idx = -1;
    if (op_busca == 1) {
        printf("Numero da conta: ");
        scanf("%d", &num);
        idx = encontrar_conta_por_numero(contas, qtd, num);
    } else if (op_busca == 2) {
        printf("CPF: ");
        fgets(cpf, TAM_CPF, stdin);
        cpf[strcspn(cpf, "\n")] = 0;
        idx = encontrar_conta_por_cpf(contas, qtd, cpf);
    }

    if (idx != -1) {
        mostrar_dados(&contas[idx]);
    } else {
        printf("Conta nao encontrada.\n");
    }
}

void atualizar_contato(Conta contas[], int qtd) {
    int num, idx;
    
    printf("Numero da conta: ");
    scanf("%d", &num);
    limpar_buffer();

    idx = encontrar_conta_por_numero(contas, qtd, num);
    if (idx == -1) {
        printf("Conta nao encontrada.\n");
        return;
    }
    if (contas[idx].status == ENCERRADA) {
        printf("Erro: Nao e possivel atualizar dados de uma conta encerrada.\n");
    return;
}

    printf("Novo Telefone: ");
    fgets(contas[idx].telefone, TAM_TELEFONE, stdin);
    contas[idx].telefone[strcspn(contas[idx].telefone, "\n")] = 0;

    printf("Nova Agencia: ");
    fgets(contas[idx].agencia, TAM_AGENCIA, stdin);
    contas[idx].agencia[strcspn(contas[idx].agencia, "\n")] = 0;

    printf("Dados atualizados com sucesso.\n");
}

void listar_contas(Conta contas[], int qtd) {
    int i;
    printf("\n--- LISTAGEM GERAL ---\n");
    //Laço for para imprimir linha por linha
    for (i = 0; i < qtd; i++) {
        printf("%d | %s | R$ %.2f | %s\n", 
            contas[i].numero, 
            contas[i].nome, 
            contas[i].saldo,
            contas[i].status == ATIVA ? "ATIVA" : "ENCERRADA");
    }
}

void encerrar_conta(Conta contas[], int qtd) {
    int num, idx;

    printf("Numero da conta para encerrar: ");
    scanf("%d", &num);

    idx = encontrar_conta_por_numero(contas, qtd, num);
    if (idx == -1) {
        printf("Conta nao encontrada.\n");
        return;
    }

    if (contas[idx].status == ENCERRADA) {
        printf("Conta ja esta encerrada.\n");
        return;
    }

    if (contas[idx].saldo != 0.0) { //Verifica se há saldo na conta, se houver, a conta não será encerrada
        printf("Erro: Para encerrar, o saldo deve ser zero.\n");
    } else {
        contas[idx].status = ENCERRADA; // Confirma a conta encerrada e mantém os dados
        printf("Conta %d encerrada com sucesso.\n", num);
    }
}
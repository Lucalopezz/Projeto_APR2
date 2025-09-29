#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STRING 100
#define MAX_TELEFONE 20
#define MAX_CPF 16
#define MAX_ENDERECO 200
#define MAX_REGISTROS 1000

#define CLIENTE_INICIAL 50
#define SERVICO_INICIAL 20
#define CLIENTE_SERVICO_INICIAL 20

#define ARQUIVO_CLIENTES "clientes.dat"
#define ARQUIVO_SERVICOS "servicos.dat"
#define ARQUIVO_CLIENTE_SERVICO  "cliente_servico.dat"

// =============== Estruturas de dados =======================
typedef struct {
    int dia, mes, ano;
} Data;

typedef struct {
    char cpf[MAX_CPF];
    char nome[MAX_STRING];
    char endereco[MAX_ENDERECO];
    char telefone_fixo[MAX_TELEFONE];
    char telefone_celular[MAX_TELEFONE];
    Data data_nascimento;
} Cliente;

typedef struct {
    int codigo;
    char descricao[MAX_STRING];
    float preco;
} Servico;

typedef struct {
    char cpf_cliente[MAX_CPF];
    int codigo_servico;
    Data data;
} ClienteServico;

// =============== Prototipos ==================
// Menus
void menu_principal();
void submenu_clientes();
void submenu_servicos();
void submenu_cliente_servico();
void submenu_relatorios();

// Funções de arquivo para clientes
void carregar_clientes(Cliente **clientes, int *count, int *capacidade);
void salvar_clientes(Cliente *clientes, int count);

// Funções de arquivo para serviços
// void carregar_servicos(Servico **servicos, int *count, int *capacidade);
// void salvar_servicos(Servico *servicos, int count);

// Funções de arquivo para cliente_servico
// void carregar_cliente_servicos(ClienteServico **cs, int *count, int *capacidade);
// void salvar_cliente_servicos(ClienteServico *cs, int count);

// Funções para clientes
// void listar_todos_clientes(Cliente *clientes, int count);
// void listar_cliente_especifico(Cliente *clientes, int count);
// int incluir_cliente(Cliente **clientes, int *count, int *capacidade);
// int alterar_cliente(Cliente *clientes, int count);
// int excluir_cliente(Cliente **clientes, int *count);
// int buscar_cliente_por_cpf(Cliente *clientes, int count, const char cpf[]);
// int cliente_existe(Cliente *clientes, int count, const char cpf[]);

// Funções para serviços
// void listar_todos_servicos(Servico *servicos, int count);
// void listar_servico_especifico(Servico *servicos, int count);
// int incluir_servico(Servico **servicos, int *count, int *capacidade);
// int alterar_servico(Servico *servicos, int count);
// int excluir_servico(Servico **servicos, int *count);
// int buscar_servico_por_codigo(Servico *servicos, int count, int codigo);
// int servico_existe(Servico *servicos, int count, int codigo);

// Funções para cliente_servico
// void listar_todos_cliente_servico(ClienteServico *cs, int count);
// void listar_cliente_servico_especifico(ClienteServico *cs, int count);
// int incluir_cliente_servico(ClienteServico **cs, int *count, int *capacidade, Cliente *clientes, int clientes_count, Servico *servicos, int servicos_count);
// int alterar_cliente_servico(ClienteServico *cs, int count);
// int excluir_cliente_servico(ClienteServico **cs, int *count);
// int buscar_cliente_servico(ClienteServico *cs, int count, const char cpf[], int codigo, Data data);
// int cliente_servico_existe(ClienteServico *cs, int count, const char cpf[], int codigo, Data data);

// Funções de relatórios
// void relatorio_clientes_servico_ultimo_mes(ClienteServico *cs, int cs_count, Cliente *clientes, int clientes_count);
// void relatorio_servicos_data_especifica(ClienteServico *cs, int cs_count, Cliente *clientes, int clientes_count, Servico *servicos, int servicos_count);
// void relatorio_servicos_periodo(ClienteServico *cs, int cs_count, Servico *servicos, int servicos_count);



// Funções auxiliares
// não sei se vou precisar
Data ler_data();
void imprimir_data(Data data);
int comparar_datas(Data d1, Data d2);
int data_no_ultimo_mes(Data data);

int main() {
    printf("=== SISTEMA DE SALAO DE BELEZA ===\n\n");
    
    menu_principal();
    
}

void menu_principal() {
    int opcao;
    
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Submenu de Clientes\n");
        printf("2. Submenu de Servicos\n");
        printf("3. Submenu de Cliente/Servico\n");
        printf("4. Submenu Relatorios\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                submenu_clientes();
                break;
            case 2:
                submenu_servicos();
                break;
            case 3:
                submenu_cliente_servico();
                break;
            case 4:
                submenu_relatorios();
                break;
            case 5:
                printf("Encerrando sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 5);
}
void submenu_clientes() {
    int opcao;
    Cliente *clientes = NULL;
    int capacidade = 0;
    
    printf("\nCarregando dados dos clientes...\n");
    // como o clientes é um ponteiro, passo o endereço dele
    //carregar_clientes(&clientes, &capacidade);
    
    do {
        printf("\n=== SUBMENU CLIENTES ===\n");
        printf("Clientes carregados: \n");
        printf("1. Listar todos os clientes\n");
        printf("2. Listar cliente especifico\n");
        printf("3. Incluir cliente\n");
        printf("4. Alterar cliente\n");
        printf("5. Excluir cliente\n");
        printf("6. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                //listar_todos_clientes();
                break;
            case 2:
                //listar_cliente_especifico();
                break;
            case 3:
                //incluir_cliente();
                break;
            case 4:
                //alterar_cliente();
                break;
            case 5:
                //excluir_cliente();
                break;
            case 6:
                printf("Salvando dados dos clientes...\n");
                //salvar_clientes();
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 6);
}

void submenu_servicos() {
    int opcao;
    Servico *servicos = NULL;
    int capacidade = 0;
    printf("\nCarregando dados dos servicos...\n");
    //carregar_servicos(&servicos, &capacidade);
    
    do {
        printf("\n=== SUBMENU SERVICOS ===\n");
        printf("Servicos carregados:\n");
        printf("1. Listar todos os servicos\n");
        printf("2. Listar servico especifico\n");
        printf("3. Incluir servico\n");
        printf("4. Alterar servico\n");
        printf("5. Excluir servico\n");
        printf("6. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                //listar_todos_servicos();
                break;
            case 2:
                //listar_servico_especifico();
                break;
            case 3:
                //incluir_servico();
                break;
            case 4:
                //alterar_servico();
                break;
            case 5:
                //excluir_servico();
                break;
            case 6:
                printf("Salvando dados dos servicos...\n");
                //salvar_servicos();
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 6);
}

void submenu_cliente_servico() {
    int opcao;
    ClienteServico *cliente_servicos = NULL;
    int capacidade = 0;
    printf("\nCarregando dados dos agendamentos...\n");
    //carregar_cliente_servicos(&cliente_servicos, &capacidade);
    
    do {
        printf("\n=== SUBMENU CLIENTE/SERVICO ===\n");
        printf("Agendamentos carregados: \n");
        printf("1. Listar todos os agendamentos\n");
        printf("2. Listar agendamento especifico\n");
        printf("3. Incluir agendamento\n");
        printf("4. Alterar agendamento\n");
        printf("5. Excluir agendamento\n");
        printf("6. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                //listar_todos_cliente_servico();
                break;
            case 2:
                //listar_cliente_servico_especifico();
                break;
            case 3:
                //incluir_cliente_servico();
                break;
            case 4:
                //alterar_cliente_servico();
                break;
            case 5:
                //excluir_cliente_servico();
                break;
            case 6:
                printf("Salvando dados dos agendamentos...\n");
                //salvar_cliente_servicos();
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 6);
}

void submenu_relatorios() {
    int opcao;
    Cliente *clientes = NULL;
    int capacidade = 0;
    Servico *servicos = NULL;
    int capacidade_servicos = 0;
    ClienteServico *cliente_servicos = NULL;
    int capacidade_cliente_servicos = 0;
    // Para relatórios, carregamos todos os dados necessários
    printf("\nCarregando dados para relatorios...\n");
    // carregar_clientes(&clientes, &capacidade);
    // carregar_servicos(&servicos, &capacidade_servicos);
    // carregar_cliente_servicos(&cliente_servicos, &capacidade_cliente_servicos);
    
    do {
        printf("\n=== SUBMENU RELATORIOS ===\n");
        printf("1. Clientes que contrataram servico no ultimo mes\n");
        printf("2. Servicos realizados em data especifica\n");
        printf("3. Servicos realizados entre duas datas\n");
        printf("4. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        
        switch(opcao) {
            case 1:
                //relatorio_clientes_servico_ultimo_mes();
                break;
            case 2:
                //relatorio_servicos_data_especifica();
                break;
            case 3:
                //relatorio_servicos_periodo();
                break;
            case 4:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 4);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STRING 100
#define MAX_TELEFONE 20
#define MAX_CPF 16
#define MAX_ENDERECO 200
#define MAX_REGISTROS 1000

#define ARQUIVO_CLIENTES = "clientes.dat";
#define ARQUIVO_SERVICOS = "servicos.dat";
#define ARQUIVO_CLIENTE_SERVICO = "cliente_servico.dat";

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
void carregar_clientes();
void salvar_clientes();

// Funções de arquivo para serviços
void carregar_servicos();
void salvar_servicos();

// Funções de arquivo para cliente_servico
void carregar_cliente_servicos();
void salvar_cliente_servicos();


//Funções para clientes
void listar_todos_clientes();
void listar_cliente_especifico();
int incluir_cliente();
int alterar_cliente();
int excluir_cliente();
int buscar_cliente_por_cpf(char cpf[]);
int cliente_existe(char cpf[]);

// Funções para serviços
void listar_todos_servicos();
void listar_servico_especifico();
int incluir_servico();
int alterar_servico();
int excluir_servico();
int buscar_servico_por_codigo(int codigo);
int servico_existe(int codigo);

// Funções para cliente_servico
void listar_todos_cliente_servico();
void listar_cliente_servico_especifico();
int incluir_cliente_servico();
int alterar_cliente_servico();
int excluir_cliente_servico();
int buscar_cliente_servico(char cpf[], int codigo, Data data);
int cliente_servico_existe(char cpf[], int codigo, Data data);

// Funções de relatórios
void relatorio_clientes_servico_ultimo_mes();
void relatorio_servicos_data_especifica();
void relatorio_servicos_periodo();


// Funções auxiliares
// não sei se vou precisar
Data ler_data();
void imprimir_data(Data data);
int comparar_datas(Data d1, Data d2);
int data_no_ultimo_mes(Data data);
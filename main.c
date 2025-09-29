#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STRING 100
#define MAX_TELEFONE 20
#define MAX_CPF 16
#define MAX_ENDERECO 200
#define MAX_REGISTROS 1000

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

// arquivos
void carregar_clientes();
void salvar_clientes();

//clientes
void listar_todos_clientes();
void listar_cliente_especifico();
void incluir_cliente();
void alterar_cliente();
void excluir_cliente();
int buscar_cliente_por_cpf(char cpf[]);
int cliente_existe(char cpf[]);
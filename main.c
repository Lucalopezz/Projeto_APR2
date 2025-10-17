#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STRING 100
#define MAX_TELEFONE 20
#define MAX_CPF 16
#define MAX_ENDERECO 200
#define MAX_REGISTROS 1000

#define CAPACIDADE_INICIAL 20

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
Servico *carregar_servicos(int *count, int *capacidade);
void salvar_servicos(Servico *servicos, int count);

// Funções de arquivo para cliente_servico
void carregar_cliente_servicos(ClienteServico **cs, int *count, int *capacidade);
void salvar_cliente_servicos(ClienteServico *cs, int count);

// Funções para clientes
void listar_todos_clientes(Cliente *clientes, int count);
void listar_cliente_especifico(Cliente *clientes, int count);
int incluir_cliente(Cliente **clientes, int *count, int *capacidade);
int alterar_cliente(Cliente *clientes, int count);
int excluir_cliente(Cliente *clientes, int *count);
int buscar_cliente_por_cpf(Cliente *clientes, int count, char cpf[]);

// Funções para serviços
void listar_todos_servicos(Servico *servicos, int count);
void listar_servico_especifico(Servico *servicos, int count);
Servico *incluir_servico(Servico *servicos, int *count, int *capacidade);
Servico *alterar_servico(Servico *servicos, int count);
int excluir_servico(Servico *servicos, int *count);
int buscar_servico_por_codigo(Servico *servicos, int count, int codigo);

// Funções para cliente_servico
void listar_todos_cliente_servico(ClienteServico *cs, int count, Cliente *clientes, int clientes_count, Servico *servicos, int servicos_count);
void listar_cliente_servico_especifico(ClienteServico *cs, int count, int *capacidade, Cliente *clientes, int clientes_count, Servico *servicos, int servicos_count);
int incluir_cliente_servico(ClienteServico **cs, int *count, int *capacidade, Cliente *clientes, int clientes_count, Servico *servicos, int servicos_count);
int alterar_cliente_servico(ClienteServico *cs, int count);
int excluir_cliente_servico(ClienteServico **cs, int *count);
int buscar_cliente_servico(ClienteServico *cs, int count, char cpf[], int codigo, Data data);

// Funções de relatórios
int relatorio_clientes_servico_ultimo_mes(ClienteServico *cs, int cs_count, Cliente *clientes, int clientes_count, Servico *servicos, int servicos_count);
int relatorio_servicos_data_especifica(ClienteServico *cs, int cs_count, Cliente *clientes, int clientes_count, Servico *servicos, int servicos_count);
int relatorio_servicos_periodo(ClienteServico *cs, int cs_count, Servico *servicos, int servicos_count);



// Funções auxiliares
Data ler_data();
void imprimir_data(Data data);
int comparar_datas(Data d1, Data d2);
void limpar_buffer();
int confirmar_operacao(char operacao[]);

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

// ================= Cliente ====================
void submenu_clientes() {
    int opcao;
    // Em vez de criar um vetor, criei um ponteiro que vai iniciar um vetor dinâmico
    Cliente *clientes = NULL;
    // Representa quantos clientes estão armazenados
    int count = 0;
    // Representa a capacidade atual do vetor
    int capacidade = 0;
    
    printf("\nCarregando dados dos clientes...\n");
    // Como o clientes é um ponteiro que inicia um vetor de Clientes e pode ser realocado, passo o endereço dele
    // So uso ponteiro de ponteiro pq tenho que realocar o vetor, mechendo no seu tamanho
    carregar_clientes(&clientes,&count, &capacidade);
    
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
                // Passo só o clientes, pq não vou alterar o ponteiro
                // clintes é o endereço do primeiro cliente do vetor
                listar_todos_clientes(clientes, count);
                break;
            case 2:
                listar_cliente_especifico(clientes, count);
                break;
            case 3:
                if (incluir_cliente(&clientes, &count, &capacidade)) {
                    printf("Cliente incluido com sucesso! Total: %d clientes.\n", count);
                }else{
                    printf("Erro ao incluir cliente. Verifique se voce ja nao esta cadastrado.\n");
                }
                break;
            case 4:
                if(alterar_cliente(clientes, count)) {
                    printf("Cliente alterado com sucesso!\n");
                } else {
                    printf("Erro ao alterar cliente. Verifique se o CPF esta correto.\n");
                }
                break;
            case 5:
                if(excluir_cliente(clientes, &count)) {
                    printf("Cliente excluido com sucesso!\n");
                } else {
                    printf("Erro ao excluir cliente. Verifique se o CPF esta correto.\n");
                }
                break;
            case 6:
                printf("Salvando dados dos clientes...\n");
                // Como não vai alterar o ponteiro, passo só o clientes, não o endereço dele
                salvar_clientes(clientes, count);
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 6);
    if (clientes != NULL) free(clientes);
}
void carregar_clientes(Cliente **clientes, int *count, int *capacidade) {
    // Ponteiro de arquivo para leitura
    FILE *arquivo = fopen(ARQUIVO_CLIENTES, "rb");
    
    // Se estiver nulo, o arquivo não existe 
    if (arquivo == NULL) {
        printf("Arquivo de clientes nao existe. Iniciando com lista vazia.\n");
        *clientes = (Cliente*)malloc(CAPACIDADE_INICIAL * sizeof(Cliente));
        *count = 0;
        *capacidade = CAPACIDADE_INICIAL;
        // Criar um arquivo de clientes vazio
        arquivo = fopen(ARQUIVO_CLIENTES, "wb");
        fclose(arquivo);
        return;
    }
    
    
    fseek(arquivo, 0, SEEK_END);// -> move o ponteiro para o final do arquivo
    long tamanho = ftell(arquivo); // -> retorna o tamanho do registro
    // Com o tamanho do arquivo, descubro quantos registros tem
    *count = tamanho / sizeof(Cliente);
    fseek(arquivo, 0, SEEK_SET); //-> move o ponteiro para o início do arquivo para começar a ler os registros
    
    // Aloca memória para os registros
    *capacidade = (*count > CAPACIDADE_INICIAL) ? *count : CAPACIDADE_INICIAL; // If ternario igual do JS
    *clientes = (Cliente*)malloc(*capacidade * sizeof(Cliente));
    
    if (*clientes == NULL) {
        printf("Erro ao alocar memoria!\n");
        *count = 0;
        *capacidade = 0;
        fclose(arquivo);
        return;
    }
    
    // Lê os dados
    if (*count > 0) {
        fread(*clientes, sizeof(Cliente), *count, arquivo);
        printf("Carregados %d clientes do arquivo.\n", *count);
    }
    
    fclose(arquivo);
}

void salvar_clientes(Cliente *clientes, int count) {
    FILE *arquivo = fopen(ARQUIVO_CLIENTES, "wb");
    
    if (arquivo == NULL) {
        printf("Erro ao salvar clientes!\n");
        return;
    }
    
    if (count > 0) {
        fwrite(clientes, sizeof(Cliente), count, arquivo);
        printf("Salvos %d clientes no arquivo.\n", count);
    }
    
    fclose(arquivo);
}

int incluir_cliente(Cliente **clientes, int *count, int *capacidade) {
    // Verifica se precisa aumentar capacidade
    if (*count >= *capacidade) {
        *capacidade += CAPACIDADE_INICIAL;
        *clientes = (Cliente*)realloc(*clientes, *capacidade * sizeof(Cliente));
        if (*clientes == NULL) {
            printf("Erro ao alocar memoria!\n");
            return 0;
        }
        printf("Capacidade aumentada para %d clientes.\n", *capacidade);
    }
    
    Cliente novo;
    
    printf("\n=== INCLUIR CLIENTE ===\n");
    printf("CPF: ");
    scanf("%s", novo.cpf);
    limpar_buffer();
    
    if (buscar_cliente_por_cpf(*clientes, *count, novo.cpf) != -1) {
        return 0;
    }
    
    printf("Nome: ");
    fgets(novo.nome, MAX_STRING, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';


    printf("Endereco: ");
    fgets(novo.endereco, MAX_ENDERECO, stdin);
    novo.endereco[strcspn(novo.endereco, "\n")] = '\0';
    
    printf("Telefone Fixo: ");
    scanf("%s", novo.telefone_fixo);

    
    printf("Telefone Celular: ");
    scanf("%s", novo.telefone_celular);
    
    printf("Data de Nascimento:\n");
    novo.data_nascimento = ler_data();
    
    // Adiciona ao vetor, pegando o endereço do próximo espaço livre
    (*clientes)[*count] = novo;
    (*count)++;
    
    return 1;
}

int buscar_cliente_por_cpf(Cliente *clientes, int count, char cpf[]) {
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            return i;
        }
    }
    return -1;
}

void listar_todos_clientes(Cliente *clientes, int count) {
    if (count == 0) {
        printf("Nenhum cliente cadastrado!\n");
        return;
    }
    int i;
    for (i = 0; i < count; i++) {
        printf("CPF: %s\n", clientes[i].cpf);
        printf("Nome: %s\n", clientes[i].nome);
        printf("Endereco: %s\n", clientes[i].endereco);
        printf("Telefone Fixo: %s\n", clientes[i].telefone_fixo);
        printf("Telefone Celular: %s\n", clientes[i].telefone_celular);
        printf("Data de Nascimento: ");
        imprimir_data(clientes[i].data_nascimento);
        printf("\n-------------------------\n");
    }
}

void listar_cliente_especifico(Cliente *clientes, int count) {
    char cpf[MAX_CPF];
    printf("Digite o CPF do cliente: ");
    scanf("%s", cpf);
    
    // Passo so o clientes(endereço do primeiro cliente do ponteiro/vetor inicial), pq não vou alterar o ponteiro
    int indice = buscar_cliente_por_cpf(clientes, count, cpf);
    if (indice == -1) {
        printf("Cliente nao encontrado!\n");
        return;
    }
    
    printf("CPF: %s\n", clientes[indice].cpf);
    printf("Nome: %s\n", clientes[indice].nome);
    printf("Endereco: %s\n", clientes[indice].endereco);
    printf("Telefone Fixo: %s\n", clientes[indice].telefone_fixo);
    printf("Telefone Celular: %s\n", clientes[indice].telefone_celular);
    printf("Data de Nascimento: ");
    imprimir_data(clientes[indice].data_nascimento);
    printf("\n");
}
int alterar_cliente(Cliente *clientes, int count){
    char cpf[MAX_CPF];
    printf("Digite o CPF do cliente a alterar: ");
    scanf("%s", cpf);
    limpar_buffer();
    
    int indice = buscar_cliente_por_cpf(clientes, count, cpf);
    if (indice == -1) {
        return 0;
    }
    
    printf("\n=== DADOS ATUAIS ===\n");
    printf("Nome: %s\n", clientes[indice].nome);
    printf("Endereco: %s\n", clientes[indice].endereco);
    printf("Telefone Fixo: %s\n", clientes[indice].telefone_fixo);
    printf("Telefone Celular: %s\n", clientes[indice].telefone_celular);
    
    printf("\n=== NOVOS DADOS ===\n");
    
    printf("Nome: ");
    fgets(clientes[indice].nome, MAX_STRING, stdin);
    clientes[indice].nome[strcspn(clientes[indice].nome, "\n")] = 0;
    
    printf("Endereco: ");
    fgets(clientes[indice].endereco, MAX_ENDERECO, stdin);
    clientes[indice].endereco[strcspn(clientes[indice].endereco, "\n")] = 0;
    
    printf("Telefone Fixo: ");
    scanf("%s", clientes[indice].telefone_fixo);
    
    printf("Telefone Celular: ");
    scanf("%s", clientes[indice].telefone_celular);

    return 1;
}

int excluir_cliente(Cliente *clientes, int *count) {
    char cpf[MAX_CPF];
    printf("Digite o CPF do cliente a excluir: ");
    scanf("%s", cpf);
    
    int indice = buscar_cliente_por_cpf(clientes, *count, cpf);
    if (indice == -1) {
        printf("Cliente nao encontrado!\n");
        return 0;
    }
    printf("\n=== DADOS DO CLIENTE ===\n");
    printf("CPF: %s\n", clientes[indice].cpf);
    printf("Nome: %s\n", clientes[indice].nome);

    int confirmar = confirmar_operacao("excluir este cliente");

    if (confirmar == 0) {
        return 0;
    }
    
    int i;
    for (i = indice; i < *count - 1; i++) {
        clientes[i] = clientes[i + 1];
    }
    
    (*count)--;
    return 1;
}

// ================= Servicos ====================
void submenu_servicos() {
    int opcao;
    int capacidade = 0;
    int count = 0;
    printf("\nCarregando dados dos servicos...\n");
    Servico *servicos = carregar_servicos(&count, &capacidade);
    
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
                listar_todos_servicos(servicos, count);
                break;
            case 2:
                listar_servico_especifico(servicos, count);
                break;
            case 3:
                servicos = incluir_servico(servicos, &count, &capacidade);
                break;
            case 4:
                servicos = alterar_servico(servicos, count);
                break;
            case 5:
                if (excluir_servico(servicos, &count)){
                    printf("Servico excluido com sucesso!\n");
                } else {
                    printf("Erro ao excluir servico. Verifique se o codigo esta correto.\n");
                }
                break;
            case 6:
                printf("Salvando dados dos servicos...\n");
                salvar_servicos(servicos, count);
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 6);
    if (servicos != NULL) free(servicos);
}

Servico *carregar_servicos(int *count, int *capacidade) {
    FILE *arquivo = fopen(ARQUIVO_SERVICOS, "rb");
    Servico *servicos = NULL;
    
    if (arquivo == NULL) {
        printf("Arquivo de servicos nao existe. Iniciando com lista vazia.\n");
        servicos = (Servico*)malloc(CAPACIDADE_INICIAL * sizeof(Servico));
        *count = 0;
        *capacidade = CAPACIDADE_INICIAL;
        // Criar um arquivo de servicos vazio
        arquivo = fopen(ARQUIVO_SERVICOS, "wb");
        fclose(arquivo);
        return servicos;
    }
    
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    *count = tamanho / sizeof(Servico);
    fseek(arquivo, 0, SEEK_SET);
   
    *capacidade = (*count > CAPACIDADE_INICIAL) ? *count : CAPACIDADE_INICIAL;
    servicos = (Servico*)malloc(*capacidade * sizeof(Servico));
   
    if (servicos == NULL) {
        printf("Erro ao alocar memoria!\n");
        *count = 0;
        *capacidade = 0;
        fclose(arquivo);
        return NULL;
    }
   
    if (*count > 0) {
        fread(servicos, sizeof(Servico), *count, arquivo);
        printf("Carregados %d servicos do arquivo.\n", *count);
    }
   
    fclose(arquivo);
    return servicos;
}

void salvar_servicos(Servico *servicos, int count) {
    FILE *arquivo = fopen(ARQUIVO_SERVICOS, "wb");
    if (arquivo == NULL) {
        printf("Erro ao salvar servicos!\n");
        return;
    }
    fwrite(servicos, sizeof(Servico), count, arquivo);
    fclose(arquivo);
}

Servico *incluir_servico(Servico *servicos, int *count, int *capacidade) {
    if (*count >= *capacidade) {
        *capacidade += CAPACIDADE_INICIAL;
        servicos = (Servico*)realloc(servicos, *capacidade * sizeof(Servico));
        if (servicos == NULL) {
            printf("Erro ao alocar memoria!\n");
            return servicos;
        }
    }
    Servico novo;
    printf("\n=== INCLUIR SERVICO ===\n");
    printf("Codigo: ");
    scanf("%d", &novo.codigo);
    limpar_buffer();
    
    if (buscar_servico_por_codigo(servicos, *count, novo.codigo) != -1) {
        printf("Erro: Servico com este codigo ja existe!\n");
        // retorno serviços para manter a lista antiga
        return servicos;
    }
    
    printf("Descricao: ");
    fgets(novo.descricao, MAX_STRING, stdin);
    novo.descricao[strcspn(novo.descricao, "\n")] = 0;
    
    printf("Preco: ");
    scanf("%f", &novo.preco);
    
    // Como não é ponteiro de ponteiro, igual nos clientes, passo so o valor q é o endereço
    servicos[*count] = novo;
    (*count)++;
    
    // Tratei aqui dentro, pois como retorno um ponteiro não tem como verificar no submenu
    printf("Servico incluido com sucesso! Total: %d servicos.\n", *count);
    return servicos;
}

int buscar_servico_por_codigo(Servico *servicos, int count, int codigo) {
    int i;
    for (i = 0; i < count; i++) {
        if (servicos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void listar_todos_servicos(Servico *servicos, int count ){
    printf("\n=== LISTA DE SERVICOS ===\n");
    
    if (count == 0) {
        printf("Nenhum servico cadastrado.\n");
        return;
    }

    int i;
    for(i=0; i < count; i++){
        printf("Codigo: %d\n", servicos[i].codigo);
        printf("Descricao: %s\n", servicos[i].descricao);
        printf("Preco: R$ %.2f\n", servicos[i].preco);
        printf("-------------------------\n");
    }

}

void listar_servico_especifico(Servico *servicos, int count){
    int codigo;
    printf("Digite o codigo do servico: ");
    scanf("%d", &codigo);

    int indice = buscar_servico_por_codigo(servicos, count, codigo);
    if(indice == -1){
        printf("Servico nao encontrado! \n");
        return;
    }
    printf("\n=== DADOS DO SERVICO ===\n");
    printf("Codigo: %d\n", servicos[indice].codigo);
    printf("Descricao: %s\n", servicos[indice].descricao);
    printf("Preco: R$ %.2f\n", servicos[indice].preco);

}

Servico *alterar_servico(Servico *servicos, int count) {
    int codigo;
    printf("Digite o codigo do servico a alterar: ");
    scanf("%d", &codigo);
    limpar_buffer();
    
    int indice = buscar_servico_por_codigo(servicos, count, codigo);
    if (indice == -1) {
        printf("Servico nao encontrado!\n");
        return servicos;
    }
    
    printf("\n=== DADOS ATUAIS ===\n");
    printf("Descricao: %s\n", servicos[indice].descricao);
    printf("Preco: R$ %.2f\n", servicos[indice].preco);
    
    printf("\n=== NOVOS DADOS ===\n");
    
    printf("Descricao: ");
    fgets(servicos[indice].descricao, MAX_STRING, stdin);
    servicos[indice].descricao[strcspn(servicos[indice].descricao, "\n")] = 0;
    
    printf("Preco: ");
    scanf("%f", &servicos[indice].preco);

    printf("Servico alterado com sucesso!\n");
    return servicos;
}

int excluir_servico(Servico *servicos, int *count){
    int codigo;
    printf("Digite o codigo do servico a excluir: ");
    scanf("%d", &codigo);
    
    int indice = buscar_servico_por_codigo(servicos, *count, codigo);
    if (indice == -1) {
        printf("Servico nao encontrado!\n");
        return 0;
    }
    printf("\n=== DADOS DO SERVICO ===\n");
    printf("Codigo: %d\n", servicos[indice].codigo);
    printf("Descricao: %s\n", servicos[indice].descricao);

    int confirmar = confirmar_operacao("excluir este servico");

    if (confirmar == 0) {
        return 0;
    }
    
    int i;
    for (i = indice; i < *count - 1; i++) {
        servicos[i] = servicos[i + 1];
    }
    
    (*count)--;
    return 1;
}

// ================= Agendamentos ====================

void submenu_cliente_servico() {
    int opcao;
    ClienteServico *cliente_servicos = NULL;
    int count = 0;
    int capacidade = 0;

    // Carrega clientes pelo ponteiro
    Cliente *clientes = NULL;
    int count_clientes = 0;
    int cap_clientes = 0;
    
    int count_servicos = 0;
    int cap_servicos = 0;
    
    
    printf("\nCarregando dados dos agendamentos...\n");
    // Carrega serviços pela função que retorna a o ponteiro inicial do vetor
    Servico *servicos = carregar_servicos(&count_servicos, &cap_servicos);
    carregar_cliente_servicos(&cliente_servicos, &count, &capacidade);
    carregar_clientes(&clientes, &count_clientes, &cap_clientes);
    
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
                listar_todos_cliente_servico(cliente_servicos, count, clientes, count_clientes, servicos, count_servicos);
                break;
            case 2:
                listar_cliente_servico_especifico(cliente_servicos, count, &capacidade, clientes, count_clientes, servicos, count_servicos);
                break;
            case 3:
                if (incluir_cliente_servico(&cliente_servicos, &count, &capacidade, clientes, count_clientes, servicos, count_servicos)){
                    printf("Agendamento incluido com sucesso! Total: %d agendamentos.\n", count);
                } else {
                    printf("Erro ao incluir agendamento. Verifique se os dados estao corretos.\n");
                }
                break;
            case 4:
                if (alterar_cliente_servico(cliente_servicos, count)) {
                    printf("Agendamento alterado com sucesso!\n");
                } else {
                    printf("Erro ao alterar agendamento. Verifique se os dados estao corretos.\n");
                }
                break;
            case 5:
                if (excluir_cliente_servico(&cliente_servicos, &count)) {
                    printf("Agendamento excluido com sucesso!\n");
                } else {
                    printf("Erro ao excluir agendamento. Verifique se os dados estao corretos.\n");
                }
                break;
            case 6:
                printf("Salvando dados dos agendamentos...\n");
                salvar_cliente_servicos(cliente_servicos, count);
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 6);
    if (cliente_servicos != NULL) free(cliente_servicos);
    if (clientes != NULL) free(clientes);
    if (servicos != NULL) free(servicos);
}
void carregar_cliente_servicos(ClienteServico **cs, int *count, int *capacidade) {
    FILE *arquivo = fopen(ARQUIVO_CLIENTE_SERVICO, "rb");
    
    if (arquivo == NULL) {
        printf("Arquivo de cliente servico nao existe. Iniciando com lista vazia.\n");
        *cs = (ClienteServico*)malloc(CAPACIDADE_INICIAL * sizeof(ClienteServico));
        *count = 0;
        *capacidade = CAPACIDADE_INICIAL;
        arquivo = fopen(ARQUIVO_CLIENTE_SERVICO, "wb");
        fclose(arquivo);
        return;
    }
    
    
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    *count = tamanho / sizeof(ClienteServico);
    fseek(arquivo, 0, SEEK_SET);
    
    *capacidade = (*count > CAPACIDADE_INICIAL) ? *count : CAPACIDADE_INICIAL; 
    *cs = (ClienteServico*)malloc(*capacidade * sizeof(ClienteServico));
    
    if (*cs == NULL) {
        printf("Erro ao alocar memoria!\n");
        *count = 0;
        *capacidade = 0;
        fclose(arquivo);
        return;
    }
    
    // Lê os dados
    if (*count > 0) {
        fread(*cs, sizeof(ClienteServico), *count, arquivo);
        printf("Carregados %d clientes servico do arquivo.\n", *count);
    }
    
    fclose(arquivo);
}

void salvar_cliente_servicos(ClienteServico *cs, int count) {
    FILE *arquivo = fopen(ARQUIVO_CLIENTE_SERVICO, "wb");
    
    if (arquivo == NULL) {
        printf("Erro ao salvar agendamentos!\n");
        return;
    }
    
    if (count > 0) {
        fwrite(cs, sizeof(ClienteServico), count, arquivo);
        printf("Salvos %d agendamentos no arquivo.\n", count);
    }
    
    fclose(arquivo);
}
void listar_todos_cliente_servico(ClienteServico *cs, int count, Cliente *clientes, 
    int clientes_count, Servico *servicos, int servicos_count){

    printf("\n=== LISTA DE AGENDAMENTOS ===\n");
    
    if (count == 0) {
        printf("Nenhum agendamento cadastrado.\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        printf("CPF Cliente: %s\n", cs[i].cpf_cliente);
        
        int idx_cli = buscar_cliente_por_cpf(clientes, clientes_count, cs[i].cpf_cliente);
        if (idx_cli != -1) {
            printf("Nome Cliente: %s\n", clientes[idx_cli].nome);
        }
        
        printf("Codigo Servico: %d\n", cs[i].codigo_servico);
        
        int idx_serv = buscar_servico_por_codigo(servicos, servicos_count, cs[i].codigo_servico);
        if (idx_serv != -1) {
            printf("Descricao Servico: %s\n", servicos[idx_serv].descricao);
            printf("Preco: R$ %.2f\n", servicos[idx_serv].preco);
        }
        
        printf("Data: ");
        imprimir_data(cs[i].data);
        printf("\n-------------------------\n");
    }
}
void listar_cliente_servico_especifico(ClienteServico *cs, int count, int *capacidade, Cliente *clientes, 
    int clientes_count, Servico *servicos, int servicos_count){
    char cpf[MAX_CPF];
    int codigo;
    Data data;
    
    printf("Digite o CPF do cliente: ");
    scanf("%s", cpf);
    limpar_buffer();
    
    printf("Digite o codigo do servico: ");
    scanf("%d", &codigo);
    limpar_buffer();
    
    printf("Digite a data:\n");
    data = ler_data();

    int indice = buscar_cliente_servico(cs, count, cpf, codigo, data);
    if (indice == -1) {
        printf("Agendamento nao encontrado!\n");
        return;
    }
    printf("\n=== DADOS DO AGENDAMENTO ===\n");
    printf("CPF Cliente: %s\n", cs[indice].cpf_cliente);
    
    int idx_cli = buscar_cliente_por_cpf(clientes, clientes_count, cpf);
    if (idx_cli != -1) {
        printf("Nome Cliente: %s\n", clientes[idx_cli].nome);
    }
    
    printf("Codigo Servico: %d\n", cs[indice].codigo_servico);
    
    int idx_serv = buscar_servico_por_codigo(servicos, servicos_count , codigo);
    if (idx_serv != -1) {
        printf("Descricao Servico: %s\n", servicos[idx_serv].descricao);
        printf("Preco: R$ %.2f\n", servicos[idx_serv].preco);
    }
    
    printf("Data: ");
    imprimir_data(cs[indice].data);
    printf("\n");


}
int incluir_cliente_servico(ClienteServico **cs, int *count, int *capacidade, Cliente *clientes, 
    int clientes_count, Servico *servicos, int servicos_count){

    if (*count >= *capacidade) {
        *capacidade *= 2;
        *cs = (ClienteServico*)realloc(*cs, *capacidade * sizeof(ClienteServico));
        if (*cs == NULL) {
            return 0;
        }
        printf("Capacidade aumentada para %d agendamentos.\n", *capacidade);
    }
    ClienteServico novo;
    
    printf("\n=== INCLUIR AGENDAMENTO ===\n");
    printf("CPF do Cliente: ");
    scanf("%s", novo.cpf_cliente);
    limpar_buffer();
    
    if (buscar_cliente_por_cpf(clientes, clientes_count, novo.cpf_cliente) == -1) {
        return 0;
    }
    
    printf("Codigo do Servico: ");
    scanf("%d", &novo.codigo_servico);
    limpar_buffer();
    
    if (buscar_servico_por_codigo(servicos, servicos_count, novo.codigo_servico) == -1) {
        return 0;
    }
    
    printf("Data do agendamento:\n");
    novo.data = ler_data();
    
    if (buscar_cliente_servico(*cs, *count, novo.cpf_cliente, novo.codigo_servico, novo.data) != -1) {
        return 0;
    }
    
    (*cs)[*count] = novo;
    (*count)++;
    
    return 1;

}

int buscar_cliente_servico(ClienteServico *cs, int count, char cpf[], int codigo, Data data){
    int i;
    for(i=0; i<count; i++){
        if(strcmp(cs[i].cpf_cliente, cpf) == 0 
        && cs[i].codigo_servico == codigo 
        && comparar_datas(cs[i].data, data) == 0){
            return i;
        }
    }
    return -1;

}

int alterar_cliente_servico(ClienteServico *cs, int count){
    char cpf[MAX_CPF];
    int codigo;
    Data data;

    printf("Digite o CPF do cliente do agendamento a alterar: ");
    scanf("%s", cpf);
    limpar_buffer();

    printf("Digite o codigo do servico do agendamento a alterar: ");
    scanf("%d", &codigo);
    limpar_buffer();

    printf("Digite a data do agendamento a alterar:\n");
    data = ler_data();

    int indice = buscar_cliente_servico(cs, count, cpf, codigo, data);
    if (indice == -1) {
        return 0;
    }
    printf("\n=== DADOS ATUAIS ===\n");
    printf("CPF Cliente: %s\n", cs[indice].cpf_cliente);
    printf("Codigo Servico: %d\n", cs[indice].codigo_servico);
    printf("Data: ");
    imprimir_data(cs[indice].data);
    printf("\n");

    printf("\n=== NOVOS DADOS ===\n");
    
    printf("Nova data: \n");
    cs[indice].data = ler_data();

    return 1;
}
int excluir_cliente_servico(ClienteServico **cs, int *count){
    char cpf[MAX_CPF];
    int codigo;
    Data data;

    printf("Digite o CPF do cliente do agendamento a alterar: ");
    scanf("%s", cpf);
    limpar_buffer();

    printf("Digite o codigo do servico do agendamento a alterar: ");
    scanf("%d", &codigo);
    limpar_buffer();

    printf("Digite a data do agendamento a alterar:\n");
    data = ler_data();

    int indice = buscar_cliente_servico(*cs, *count, cpf, codigo, data);
    if (indice == -1) {
        return 0;
    }
    int confirmar = confirmar_operacao("excluir este agendamento");

    if (confirmar == 0) {
        return 0;
    }

    int i;
    for (i = indice; i < *count - 1; i++) {
        (*cs)[i] = (*cs)[i + 1];
    }

    (*count)--;
    return 1;

}


// ================= Relatorios ====================
void submenu_relatorios() {
    int opcao;
    ClienteServico *cliente_servicos = NULL;
    int count = 0;
    int capacidade = 0;

    Cliente *clientes = NULL;
    int count_clientes = 0;
    int cap_clientes = 0;
    
    int count_servicos = 0;
    int cap_servicos = 0;
    
    
    printf("\nCarregando dados dos agendamentos...\n");
    // Carrega serviços pela função que retorna a o ponteiro inicial do vetor
    Servico *servicos = carregar_servicos(&count_servicos, &cap_servicos);
    carregar_cliente_servicos(&cliente_servicos, &count, &capacidade);
    carregar_clientes(&clientes, &count_clientes, &cap_clientes);
    
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
                if(relatorio_clientes_servico_ultimo_mes(cliente_servicos, count, clientes, count_clientes, servicos, count_servicos)){
                    printf("Relatorio salvo em 'relatorio_clientes_ultimo_mes.txt'\n");
                }
                else {
                    printf("Erro ao gerar relatorio.\n");
                }
                break;
            case 2:
                if(relatorio_servicos_data_especifica(cliente_servicos, count, clientes, count_clientes, servicos, count_servicos)){
                    printf("Relatorio salvo em 'relatorio_servicos_data.txt'\n");
                }
                else {
                    printf("Erro ao gerar relatorio.\n");
                }
                break;
            case 3:
                if(relatorio_servicos_periodo(cliente_servicos, count, servicos, count_servicos)){
                    printf("Relatorio salvo em 'relatorio_servicos_periodo.txt'\n");
                }
                else {
                    printf("Erro ao gerar relatorio.\n");
                }
                break;
            case 4:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 4);
}
int relatorio_clientes_servico_ultimo_mes(ClienteServico *cs, int cs_count, Cliente *clientes, int clientes_count, Servico *servicos, int servicos_count){
    int codigo_servico, mes_consulta, ano_consulta;;
    printf("Digite o codigo do servico: ");
    scanf("%d", &codigo_servico);
    limpar_buffer();
    
    if (buscar_servico_por_codigo(servicos, servicos_count, codigo_servico) == -1) {
        printf("Servico nao encontrado!\n");
        return 0;
    }

    printf("Digite o mes que deseja consultar (1-12): ");
    scanf("%d", &mes_consulta);
    printf("Digite o ano: ");
    scanf("%d", &ano_consulta);

    FILE *relatorio = fopen("relatorio_clientes_ultimo_mes.txt", "w");
    if (relatorio == NULL) {
        printf("Erro ao criar arquivo de relatorio!\n");
        return 0;
    }
    fprintf(relatorio, "=== CLIENTES QUE CONTRATARAM SERVICO %d NO ULTIMO MES ===\n\n", codigo_servico);

    int encontrou = 0, i;
    for(i=0; i<cs_count; i++){
        if (cs[i].codigo_servico == codigo_servico &&
            cs[i].data.mes == mes_consulta &&
            cs[i].data.ano == ano_consulta) {
                
            int idx_cli = buscar_cliente_por_cpf(clientes, clientes_count, cs[i].cpf_cliente);
            if (idx_cli != -1) {
                fprintf(relatorio, "Nome: %s\n", clientes[idx_cli].nome);
                fprintf(relatorio, "Telefone Fixo: %s\n", clientes[idx_cli].telefone_fixo);
                fprintf(relatorio, "Telefone Celular: %s\n", clientes[idx_cli].telefone_celular);
                fprintf(relatorio, "Data do Servico: %d/%d/%d\n", 
                       cs[i].data.dia, cs[i].data.mes, cs[i].data.ano);
                fprintf(relatorio, "-------------------------\n");
                encontrou = 1;
            }
        }   
    }
    if (!encontrou) {
        fprintf(relatorio, "Nenhum cliente encontrado.\n");
    }
    
    fclose(relatorio);
    return 1;
    
}

int relatorio_servicos_data_especifica(ClienteServico *cs, int cs_count, Cliente *clientes, int clientes_count, Servico *servicos, int servicos_count){
    Data data_especifica;
    printf("Digite a data:\n");
    data_especifica = ler_data();

    FILE *relatorio = fopen("relatorio_servicos_data.txt", "w");
    if (relatorio == NULL) {
        printf("Erro ao criar arquivo de relatorio!\n");
        return 0;
    }
    
    fprintf(relatorio, "=== SERVICOS REALIZADOS EM %d/%d/%d ===\n\n", data_especifica.dia, data_especifica.mes, data_especifica.ano);
    int encontrou = 0, i;
    for(i=0; i<cs_count; i++){
        if(comparar_datas(cs[i].data, data_especifica) == 0){
            int idx_cli = buscar_cliente_por_cpf(clientes, clientes_count, cs[i].cpf_cliente);
            int idx_serv = buscar_servico_por_codigo(servicos, servicos_count, cs[i].codigo_servico);
            if (idx_cli != -1 && idx_serv != -1) {
                fprintf(relatorio, "Nome Cliente: %s\n", clientes[idx_cli].nome);
                fprintf(relatorio, "Codigo Servico: %d\n", servicos[idx_serv].codigo);
                fprintf(relatorio, "Descricao Servico: %s\n", servicos[idx_serv].descricao);
                fprintf(relatorio, "Preco: R$ %.2f\n", servicos[idx_serv].preco);
                fprintf(relatorio, "-------------------------\n");
                encontrou = 1;
            }

        }
    }
    if (!encontrou) {
        fprintf(relatorio, "Nenhum servico encontrado para esta data.\n");
    }
    
    fclose(relatorio);
    return 1;
}

int relatorio_servicos_periodo(ClienteServico *cs, int cs_count, Servico *servicos, int servicos_count){
    Data data_inicio;
    Data data_final;
    printf("Digite a data inicial:\n");
    data_inicio = ler_data();
    printf("Digite a data final:\n");
    data_final = ler_data();

    FILE *relatorio = fopen("relatorio_servicos_periodo.txt", "w");
    if (relatorio == NULL) {
        printf("Erro ao criar arquivo de relatorio!\n");
        return 0;
    }
    fprintf(relatorio, "=== SERVICOS REALIZADOS ENTRE %d/%d/%d E %d/%d/%d ===\n\n", 
        data_inicio.dia, data_inicio.mes, data_inicio.ano,
        data_final.dia, data_final.mes, data_final.ano);

    int encontrou = 0, i;
    for(i=0; i<cs_count; i++){
        if (comparar_datas(cs[i].data, data_inicio) >= 0 && comparar_datas(cs[i].data, data_final) <= 0) {
            int idx_serv = buscar_servico_por_codigo(servicos, servicos_count, cs[i].codigo_servico);
            if (idx_serv != -1) {
                fprintf(relatorio, "Codigo Servico: %d\n", servicos[idx_serv].codigo);
                fprintf(relatorio, "Descricao Servico: %s\n", servicos[idx_serv].descricao);
                fprintf(relatorio, "Preco: R$ %.2f\n", servicos[idx_serv].preco);
                fprintf(relatorio, "Data do Servico: %d/%d/%d\n", 
                       cs[i].data.dia, cs[i].data.mes, cs[i].data.ano);
                fprintf(relatorio, "-------------------------\n");
                encontrou = 1;
            }
        }
    }

    if (!encontrou) {
        fprintf(relatorio, "Nenhum servico encontrado neste periodo.\n");
    }
    
    fclose(relatorio);
    return 1;

}











// ================= Funcoes Auxiliares ====================
Data ler_data() {
    Data data;
    printf("Dia: ");
    scanf("%d", &data.dia);
    printf("Mes: ");
    scanf("%d", &data.mes);
    printf("Ano: ");
    scanf("%d", &data.ano);
    return data;
}
void imprimir_data(Data data) {
    printf("%02d/%02d/%04d", data.dia, data.mes, data.ano);
}
void limpar_buffer() {
    int c;
    // EOF = End Of File
    while ((c = getchar()) != '\n' && c != EOF);
}
int confirmar_operacao(char operacao[]) {
    char resposta;
    printf("Tem certeza que deseja %s? (s/n): ", operacao);
    scanf(" %c", &resposta);
    limpar_buffer();
    if (resposta == 's' || resposta == 'S') {
        return 1;
    } 

    return 0;
    
}

int comparar_datas(Data d1, Data d2) {
    // Se os anos forem diferentes, eu retorno em anos
    if (d1.ano != d2.ano) return d1.ano - d2.ano;
    // Se os meses forem diferentes, eu retorno em meses
    if (d1.mes != d2.mes) return d1.mes - d2.mes;
    return d1.dia - d2.dia;
  
}

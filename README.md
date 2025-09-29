# Sistema para salão de beleza

## Descrição
Uma aplicação para um salão de beleza que gerencia informações sobre os clientes, os serviços oferecidos pelos profissionais e os serviços realizados por cada cliente. Os dados devem ser armazenados e manipulados pelo programa em C, com persistência em arquivos.

## Modelo de dados

### Clientes
- **CPF** (chave)
- Nome
- Endereço
- Telefone fixo
- Telefone celular
- Data de nascimento

### Serviços
- **Código** (chave)
- Descrição
- Preço

### Cliente_Serviço
- **CPF do cliente**, **Código do serviço**, **Data** (chave composta)

**Atenção:** os atributos em negrito são chaves. NÃO permitir a inclusão de mais de um cadastro com os mesmos valores para os atributos chave.

## Requisitos do programa
- Implementar em **C**.
- Apresentar um **menu principal** com os submenus e opções descritas abaixo.
- Implementar cada operação por meio de **funções**.
- Utilizar estruturas dinâmicas (vetores e registros alocados dinamicamente) para armazenamento temporário dos dados antes da gravação em arquivos.
- Cada entidade deve ser persistida em seu **próprio arquivo binário** contendo apenas registros daquele tipo.
- Relatórios devem ser gerados em **arquivos texto**.

## Menu Principal
1. Submenu de Clientes  
2. Submenu de Serviços  
3. Submenu de Cliente/Serviço  
4. Submenu Relatórios  
5. Sair

### Cada Submenu (Clientes / Serviços / Cliente-Serviço) deve oferecer:
- Listar todos os elementos  
- Listar um elemento específico (chave informada pelo usuário)  
- Incluir (sem repetição de chaves)  
- Alterar um elemento informado pelo usuário  
- Excluir um elemento informado pelo usuário (exclusão somente após confirmação dos dados)

## Submenu Relatórios
O submenu Relatórios deverá conter uma opção para cada relatório abaixo:

a) Mostrar o nome e os telefones de todos os clientes que contrataram determinado serviço no último mês.  
- O **código do serviço** deve ser fornecido pelo usuário.

b) Mostrar os dados de todos os serviços realizados em uma **data específica** fornecida pelo usuário.  
- Apresentar também o **nome do(a) cliente** associado a cada serviço.

c) Mostrar os dados de todos os serviços (código, descrição e preço) realizados **entre as datas X e Y** (datas fornecidas pelo usuário).

## Persistência de dados
- Arquivos binários separados para cada entidade, por exemplo:
  - `clientes.dat` — registros de Cliente
  - `servicos.dat` — registros de Serviço
  - `cliente_servico.dat` — registros de Cliente_Serviço
- Relatórios gravados em arquivos texto (`.txt`) apropriados.
- Antes de gravar nos arquivos, os registros devem ser mantidos em memória usando estruturas dinâmicas (vetores/arrays realocados dinamicamente ou listas) e só então persistidos.

## Observações de implementação
- Escolher a estrutura de dados mais adequada para cada entidade (ex.: vetor dinâmico, lista encadeada, etc.), considerando facilidade para busca por chave, inclusão sem duplicação e remoção com confirmação.
- Implementar funções separadas e bem nomeadas para cada operação (ex.: `listarClientes()`, `incluirServico()`, `alterarCliente()`, `excluirClienteServico()` etc.).
- Garantir validação das chaves ao incluir/alterar para evitar duplicidade.
- Tratar entradas de data de forma consistente (especificar formato na interface, por exemplo `DD/MM/AAAA`).
- Realizar confirmação explícita antes de excluir um registro (exibir os dados e pedir confirmação).
- Garantir que a leitura/escrita em arquivos binários seja consistente com as estruturas usadas em memória.

---
**Observação final:** seguir as especificações acima para desenvolver o programa em C, respeitando persistência em arquivos binários por entidade e geração de relatórios em arquivos texto.  

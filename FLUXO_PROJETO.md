# Fluxo do Projeto Kanban

## Visão Geral

Este documento descreve o fluxo atual do projeto C++ do Kanban, suas camadas e como os dados e ações se conectam. O objetivo é permitir uma futura migração para uma interface front-end com a mínima reestruturação possível.

## Arquitetura do Projeto

O projeto está organizado em três camadas principais:

1. **Camada de Apresentação (UI/Interação)**
   - Responsável por interagir com o usuário via terminal.
   - Classes principais: `CntrlApresInic`, `CntrlApresAuten`, `CntrlApresConta`, `CntrlApresGeren`.
   - Arquivo base: `controladoras.h` e `Controladoras.cpp`.

2. **Camada de Serviço (Regras de Negócio)**
   - Processa a lógica de autenticação, contas, quadros e cartões.
   - Implementa regras de validação de negócio e uso dos containers.
   - Classes principais: `CntrlServAuten`, `CntrlServConta`, `CntrlServGeren`.
   - Arquivo base: `ControladorasServ.h` e `ControladorasServ.cpp`.

3. **Camada de Persistência em Memória (Repositório)**
   - Armazena objetos em `std::map` e gerencia busca, inclusão, remoção e atualização.
   - Implementa singleton para cada tipo de container.
   - Classes principais: `ContainerConta`, `ContainerQuadro`, `ContainerCartao`.
   - Arquivo base: `Container.h` e `Container.cpp`.

## Ponto de Entrada

O arquivo `main.cpp` configura todas as dependências e inicia o fluxo:

- Cria o controlador inicial `CntrlApresInic`.
- Cria objetos de apresentação (`CntrlApresAuten`, `CntrlApresConta`, `CntrlApresGeren`).
- Cria objetos de serviço (`CntrlServAuten`, `CntrlServConta`, `CntrlServGeren`).
- Liga os controladores de apresentação aos serviços corretos.
- Executa `cntrlApresInicial.StartProgram()`.

## Fluxo de Execução

### Início do programa

1. O usuário vê o menu de inicialização.
2. Opções disponíveis:
   - Login
   - Criar conta
   - Finalizar

### Autenticação

- `CntrlApresAuten::autenticar(Email*)` coleta email e senha.
- Valida entradas usando os domínios `Email` e `Senha`.
- Repassa para o serviço `IServAuten::autenticar(Email, Senha)`.
- Se autenticação for bem-sucedida, o sistema libera o acesso aos menus de conta e gerenciamento.

### Criação de Conta

- `CntrlApresConta::cadastrar()` coleta nome, email e senha.
- Valida usando domínios `Texto`, `Email` e `Senha`.
- Cria um objeto `Conta` e chama `IServContas::criar(Conta)`.
- O serviço verifica duplicidade e armazena a conta em `ContainerConta`.

### Menu de Conta

- Após login, há um menu de conta que permite:
  - Visualizar dados da conta
  - Excluir conta
  - Editar conta

- A interface usa métodos de `CntrlApresConta` para chamar o serviço correspondente.
- As operações sobre conta são realizadas em `ContainerConta`.

### Menu de Gerenciamento

- Após login, há um menu de gerenciamento de quadros e cartões.
- Funcionalidades:
  - Criar quadro
  - Visualizar quadro
  - Excluir quadro
  - Criar cartão
  - Visualizar cartão
  - Mover cartão
  - Excluir cartão

- Cada ação é tratada em `CntrlApresGeren` e repassada para os serviços de gerenciamento.

## Modelo de Dados e Domínios

### Domínios

Os domínios definem regras de formato e validação:

- `Limite`
  - Valores permitidos: `5`, `10`, `15`, `20`.
- `Coluna`
  - Valores permitidos: `SOLICITADO`, `EM EXECUCAO`, `CONCLUIDO`.
- `Codigo`
  - Formato: duas letras maiúsculas + dois dígitos (`LLDD`).
- `Texto`
  - 5 a 30 caracteres.
  - Permite letras, números, pontuação `. , ; ! ?` e espaços.
  - Regras de capitalização e proibição de sequências inválidas.
- `Senha`
  - Exatamente 5 caracteres.
  - Deve conter pelo menos uma letra maiúscula, uma minúscula, um dígito e um sinal de pontuação.
  - Não permite caracteres duplicados.
- `Email`
  - Formato `nome@dominio`.
  - Nome entre 2 e 10 caracteres.
  - Domínio entre 2 e 20 caracteres.
  - Não permite pontos consecutivos.

### Entidades

- `Conta`
  - `Email email`
  - `Texto nome`
  - `Senha senha`

- `Quadro`
  - `Codigo codigo`
  - `Texto nome`
  - `Texto descricao`
  - `Limite limite`
  - `Email email` (dono)
  - `string cartoes` (lista de cartões vinculados)

- `Cartao`
  - `Codigo ident` (identificador do quadro pai)
  - `Codigo codigo`
  - `Texto nome`
  - `Texto descricao`
  - `Coluna coluna`

## Comunicação entre camadas

### Interfaces

A aplicação usa interfaces para desacoplar apresentação de serviço:

- `IApresAuten` -> `CntrlApresAuten`
- `IApresContas` -> `CntrlApresConta`
- `IApresGeren` -> `CntrlApresGeren`
- `IServAuten` -> `CntrlServAuten`
- `IServContas` -> `CntrlServConta`
- `IServGeren` -> `CntrlServGeren`

### Containers Singleton

Os containers preservam o estado em memória e permitem acesso global:

- `ContainerConta`
- `ContainerQuadro`
- `ContainerCartao`

Eles armazenam dados em `std::map<string, T>` e fornecem operações básicas CRUD.

## Pontos de migração para Front-end

### Componentes de UI possíveis

Cada menu de terminal pode virar uma tela ou um conjunto de rotas:

- Tela de login
- Tela de cadastro de conta
- Tela de dashboard (após login)
- Tela de gerenciamento de conta
- Tela de listagem/visualização de quadros
- Tela de criação de quadro
- Tela de visualização de cartão
- Tela de edição de cartão

### Serviço/API

A camada de serviço é ideal para se transformar em uma API ou camada backend:

- `Autenticação` -> endpoint `POST /login`
- `Cadastro de conta` -> endpoint `POST /accounts`
- `Visualizar conta` -> endpoint `GET /accounts/:email`
- `Editar conta` -> endpoint `PUT /accounts/:email`
- `Excluir conta` -> endpoint `DELETE /accounts/:email`
- `Criar quadro` -> endpoint `POST /boards`
- `Visualizar quadro` -> endpoint `GET /boards/:code`
- `Excluir quadro` -> endpoint `DELETE /boards/:code`
- `Criar cartão` -> endpoint `POST /cards`
- `Visualizar cartão` -> endpoint `GET /cards/:code`
- `Mover cartão` -> endpoint `PATCH /cards/:code/move`
- `Excluir cartão` -> endpoint `DELETE /cards/:code`

### Estado e armazenamento

Atualmente, o projeto não tem persistência externa. Para migração, as opções mais naturais são:

- Banco de dados relacional (MySQL / PostgreSQL)
- Banco NoSQL leve (MongoDB)
- Arquivo JSON ou SQLite para protótipo

### Recomendações de migração

1. Separar a lógica de domínio e serviço em classes independentes do terminal.
2. Criar uma camada de adaptadores para entrada/saída:
   - `TerminalAdapter` para a versão atual.
   - `ApiAdapter` para HTTP / front-end.
3. Transformar os containers atuais em repositórios com interface definida.
4. Reusar os domínios (`Email`, `Senha`, `Texto`, `Codigo`, `Coluna`, `Limite`) no backend.
5. Implementar JSON/REST para expor operações do serviço.

## Arquivos principais

- `main.cpp` - injeção de dependências e ponto de partida.
- `controladoras.h` / `Controladoras.cpp` - lógica de apresentação e menus.
- `ControladorasServ.h` / `ControladorasServ.cpp` - regras de serviço.
- `Container.h` / `Container.cpp` - armazenamento em memória.
- `dominios.h` / `dominios.cpp` - regras de validação de formato.
- `entidades.h` - definição das entidades de domínio.
- `interfaces.h` - contratos entre apresentação e serviço.

## Conclusão

O projeto já possui uma boa separação de responsabilidades entre apresentação, serviço e persistência. Para migrar para um front-end, basta:

- manter os domínios e serviços;
- substituir a camada de apresentação por uma camada web/mobile;
- trocar os containers em memória por um repositório persistente.

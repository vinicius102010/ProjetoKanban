# Kanban Web — Backend & Frontend

Sistema de gestão Kanban desenvolvido para a disciplina de Engenharia de Software (UnB).  
Utiliza **FastAPI** (Python) como backend REST, **SQLite** como banco de dados e **Alpine.js** no frontend.

---

## Estrutura do projeto

```
kanban_web/
├── main.py           # Ponto de entrada da aplicação FastAPI
├── database.py       # Configuração do SQLAlchemy e SQLite
├── models.py         # Modelos ORM (tabelas do banco)
├── schemas.py        # Schemas Pydantic (validação de entrada/saída)
├── requirements.txt  # Dependências Python
├── routers/
│   ├── auth.py       # Login e cadastro
│   ├── contas.py     # CRUD de contas de usuário
│   ├── quadros.py    # CRUD de quadros Kanban
│   ├── cartoes.py    # CRUD de cartões
│   └── membros.py    # Gerenciamento de membros de quadros
└── static/
    └── index.html    # Frontend (servido pelo próprio FastAPI)
```

O banco de dados `kanban.db` (SQLite) é criado automaticamente na primeira execução dentro da pasta `kanban_web/`.

---

## Pré-requisitos

- Python **3.10+**
- `pip` atualizado

---

## Como rodar

### 1. Acesse a pasta do projeto web

```bash
cd kanban_web
```

### 2. Crie e ative o ambiente virtual

**Linux / macOS / WSL:**
```bash
python3 -m venv venv
source venv/bin/activate
```

**Windows (PowerShell):**
```powershell
python -m venv venv
.\venv\Scripts\Activate.ps1
```

> Após ativar, o terminal exibirá `(venv)` no início da linha.

### 3. Instale as dependências

```bash
pip install -r requirements.txt
```

### 4. Inicie o servidor

```bash
uvicorn main:app --reload
```

O servidor ficará disponível em: **http://127.0.0.1:8000**

---

## Acessando a aplicação

| URL | Descrição |
|-----|-----------|
| `http://127.0.0.1:8000/` | Frontend (interface Kanban) |
| `http://127.0.0.1:8000/docs` | Documentação interativa (Swagger UI) |
| `http://127.0.0.1:8000/redoc` | Documentação alternativa (ReDoc) |

---

## Endpoints principais

### Autenticação
| Método | Rota | Descrição |
|--------|------|-----------|
| `POST` | `/auth/cadastrar` | Cadastrar nova conta |
| `POST` | `/auth/login` | Login de usuário |

### Contas
| Método | Rota | Descrição |
|--------|------|-----------|
| `GET` | `/contas/{email}` | Buscar conta por e-mail |
| `DELETE` | `/contas/{email}` | Remover conta |

### Quadros
| Método | Rota | Descrição |
|--------|------|-----------|
| `POST` | `/quadros/` | Criar quadro |
| `GET` | `/quadros/{codigo}` | Buscar quadro por código |
| `PUT` | `/quadros/{codigo}` | Atualizar quadro |
| `DELETE` | `/quadros/{codigo}` | Remover quadro |

### Cartões
| Método | Rota | Descrição |
|--------|------|-----------|
| `POST` | `/cartoes/` | Criar cartão |
| `GET` | `/cartoes/{codigo}` | Buscar cartão |
| `PUT` | `/cartoes/{codigo}` | Atualizar cartão |
| `DELETE` | `/cartoes/{codigo}` | Remover cartão |

### Membros
| Método | Rota | Descrição |
|--------|------|-----------|
| `POST` | `/membros/` | Adicionar membro a um quadro |
| `DELETE` | `/membros/{quadro}/{email}` | Remover membro de um quadro |

---

## Regras de validação (espelham os domínios C++)

- **Código** — 4 caracteres no formato `LLDD` (2 letras maiúsculas + 2 dígitos, ex: `AB12`)
- **Texto / Nome** — entre 5 e 30 caracteres, deve começar com letra maiúscula, sem espaços duplos
- **E-mail** — parte local entre 2–10 chars, domínio entre 2–20 chars, apenas letras e pontos
- **Senha** — entre 5 e 8 caracteres, deve conter letras e dígitos, sem espaços
- **Limite WIP** — inteiro entre 1 e 10
- **Coluna** — `A FAZER` | `FAZENDO` | `FEITO`
- **Prioridade** — `BAIXA` | `MEDIA` | `ALTA`
- **Status do quadro** — `A FAZER` | `EM ANDAMENTO` | `EM TESTES` | `CONCLUIDO`

---

## Observações importantes

- O arquivo `kanban.db` (banco SQLite) é gerado automaticamente — **não precisa criar manualmente**.
- A pasta `venv/` deve ser ignorada pelo Git (já configurada no `.gitignore` da raiz).
- O servidor `--reload` reinicia automaticamente ao salvar alterações nos arquivos `.py` — útil para desenvolvimento.
- Para rodar em outra porta: `uvicorn main:app --reload --port 8080`

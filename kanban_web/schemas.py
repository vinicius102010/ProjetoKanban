import re
from pydantic import BaseModel, field_validator, model_validator
from typing import Optional, List
from datetime import datetime
from enum import Enum


# ── Enums ──────────────────────────────────────────────────────────────────────

class ColunaEnum(str, Enum):
    A_FAZER = "A FAZER"
    FAZENDO = "FAZENDO"
    EM_TESTE = "EM TESTE"
    FEITO = "FEITO"


class PrioridadeEnum(str, Enum):
    BAIXA = "BAIXA"
    MEDIA = "MEDIA"
    ALTA = "ALTA"


class StatusQuadroEnum(str, Enum):
    A_FAZER = "A FAZER"
    EM_ANDAMENTO = "EM ANDAMENTO"
    EM_TESTES = "EM TESTES"
    CONCLUIDO = "CONCLUIDO"


# ── Validators reutilizáveis (espelham domínios do C++) ──────────────────────

def validar_codigo(v: str) -> str:
    if not re.fullmatch(r"[A-Z]{2}[0-9]{2}", v):
        raise ValueError("Código deve ter formato LLDD (ex: AB12)")
    return v


def validar_texto(v: str) -> str:
    if not (5 <= len(v) <= 30):
        raise ValueError("Texto deve ter entre 5 e 30 caracteres")
    if not v[0].isupper():
        raise ValueError("Texto deve começar com letra maiúscula")
    if "  " in v:
        raise ValueError("Texto não pode ter espaços duplos")
    return v


def validar_email(v: str) -> str:
    partes = v.split('@')
    if len(partes) != 2:
        raise ValueError("Email deve conter exatamente um '@'")
    nome, dominio = partes
    if not (2 <= len(nome) <= 10):
        raise ValueError("Parte local do email deve ter entre 2 e 10 caracteres")
    if not (2 <= len(dominio) <= 20):
        raise ValueError("Domínio do email deve ter entre 2 e 20 caracteres")
    if nome.endswith('.') or dominio.startswith('.'):
        raise ValueError("Email não pode ter ponto adjacente ao '@'")
    for parte in (nome, dominio):
        if not all(c.isalpha() or c == '.' for c in parte):
            raise ValueError("Email pode conter apenas letras e pontos (ex: pedro@gmail.com)")
        if '..' in parte:
            raise ValueError("Email não pode ter pontos consecutivos")
    return v


def validar_senha(v: str) -> str:
    if len(v) != 5:
        raise ValueError("Senha deve ter exatamente 5 caracteres")
    if len(set(v)) != len(v):
        raise ValueError("Senha não pode ter caracteres repetidos")
    if not any(c.isupper() for c in v):
        raise ValueError("Senha deve ter ao menos uma letra maiúscula")
    if not any(c.islower() for c in v):
        raise ValueError("Senha deve ter ao menos uma letra minúscula")
    if not any(c.isdigit() for c in v):
        raise ValueError("Senha deve ter ao menos um dígito")
    if not any(c in ".,;!?" for c in v):
        raise ValueError("Senha deve ter ao menos um sinal de pontuação (.,;!?)")
    return v


def validar_limite(v) -> int:
    try:
        v = int(v)
    except (TypeError, ValueError):
        raise ValueError("Limite deve ser um número inteiro")
    if v not in (5, 10, 15, 20):
        raise ValueError("Limite deve ser 5, 10, 15 ou 20")
    return v


# ── Conta ────────────────────────────────────────────────────────────────────

class ContaCreate(BaseModel):
    email: str
    nome: str
    senha: str

    @field_validator("email")
    @classmethod
    def check_email(cls, v): return validar_email(v)

    @field_validator("nome")
    @classmethod
    def check_nome(cls, v): return validar_texto(v)

    @field_validator("senha")
    @classmethod
    def check_senha(cls, v): return validar_senha(v)


class ContaUpdate(BaseModel):
    nome: Optional[str] = None
    senha: Optional[str] = None

    @field_validator("nome")
    @classmethod
    def check_nome(cls, v):
        if v is not None:
            return validar_texto(v)
        return v

    @field_validator("senha")
    @classmethod
    def check_senha(cls, v):
        if v is not None:
            return validar_senha(v)
        return v


class ContaOut(BaseModel):
    email: str
    nome: str

    class Config:
        from_attributes = True


# ── Autenticação ─────────────────────────────────────────────────────────────

class LoginRequest(BaseModel):
    email: str
    senha: str


# ── Quadro ───────────────────────────────────────────────────────────────────

class QuadroCreate(BaseModel):
    codigo: str
    nome: str
    descricao: str
    limite_wip: int = 10

    @field_validator("codigo")
    @classmethod
    def check_codigo(cls, v): return validar_codigo(v)

    @field_validator("nome")
    @classmethod
    def check_nome(cls, v): return validar_texto(v)

    @field_validator("descricao")
    @classmethod
    def check_descricao(cls, v): return validar_texto(v)

    @field_validator("limite_wip")
    @classmethod
    def check_limite(cls, v): return validar_limite(v)


class QuadroOut(BaseModel):
    codigo: str
    nome: str
    descricao: str
    limite_wip: int
    status: str
    email_dono: str

    class Config:
        from_attributes = True


class QuadroMoverStatus(BaseModel):
    status: StatusQuadroEnum


# ── Membros ───────────────────────────────────────────────────────────────────

class MembroConvidar(BaseModel):
    email_usuario: str


class MembroOut(BaseModel):
    email_usuario: str
    papel: str
    nome: Optional[str] = None

    class Config:
        from_attributes = True



class CartaoCreate(BaseModel):
    codigo: str
    codigo_quadro: str
    nome: str
    descricao: str
    responsavel: str
    prioridade: PrioridadeEnum = PrioridadeEnum.MEDIA
    data_limite: Optional[str] = None
    coluna: ColunaEnum = ColunaEnum.A_FAZER

    @field_validator("codigo", "codigo_quadro")
    @classmethod
    def check_codigo(cls, v): return validar_codigo(v)

    @field_validator("nome", "descricao", "responsavel")
    @classmethod
    def check_texto(cls, v): return validar_texto(v)


class CartaoUpdate(BaseModel):
    nome: str
    descricao: str
    responsavel: str
    prioridade: PrioridadeEnum = PrioridadeEnum.MEDIA
    data_limite: Optional[str] = None

    @field_validator("nome", "descricao", "responsavel")
    @classmethod
    def check_texto(cls, v): return validar_texto(v)


class CartaoMover(BaseModel):
    coluna: ColunaEnum


class CartaoOut(BaseModel):
    codigo: str
    codigo_quadro: str
    nome: str
    descricao: str
    responsavel: str
    prioridade: str
    data_limite: Optional[str]
    coluna: str
    criado_em: Optional[datetime]
    iniciado_em: Optional[datetime]
    concluido_em: Optional[datetime]

    class Config:
        from_attributes = True


# ── Métricas ─────────────────────────────────────────────────────────────────

class MetricasOut(BaseModel):
    wip_atual: int
    throughput: int
    lead_time_medio_dias: Optional[float]
    cycle_time_medio_dias: Optional[float]

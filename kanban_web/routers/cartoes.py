from fastapi import APIRouter, Depends, HTTPException, status
from sqlalchemy.orm import Session
from typing import List
from datetime import datetime, timezone
from database import get_db
import models
import schemas

router = APIRouter(prefix="/cartoes", tags=["Cartões"])


@router.post("/", response_model=schemas.CartaoOut, status_code=status.HTTP_201_CREATED)
def criar_cartao(payload: schemas.CartaoCreate, db: Session = Depends(get_db)):
    quadro = db.query(models.Quadro).filter(models.Quadro.codigo == payload.codigo_quadro).first()
    if not quadro:
        raise HTTPException(status_code=404, detail="Quadro não encontrado")

    # Verificar limite WIP na coluna destino
    qtd_coluna = db.query(models.Cartao).filter(
        models.Cartao.codigo_quadro == payload.codigo_quadro,
        models.Cartao.coluna == payload.coluna.value
    ).count()
    if qtd_coluna >= quadro.limite_wip:
        raise HTTPException(status_code=409, detail=f"Limite WIP atingido na coluna '{payload.coluna.value}'")

    existente = db.query(models.Cartao).filter(models.Cartao.codigo == payload.codigo).first()
    if existente:
        raise HTTPException(status_code=409, detail="Código de cartão já existe")

    cartao = models.Cartao(
        codigo=payload.codigo,
        codigo_quadro=payload.codigo_quadro,
        nome=payload.nome,
        descricao=payload.descricao,
        responsavel=payload.responsavel,
        prioridade=payload.prioridade.value,
        data_limite=payload.data_limite,
        coluna=payload.coluna.value,
    )
    db.add(cartao)
    db.commit()
    db.refresh(cartao)
    return cartao


@router.get("/quadro/{codigo_quadro}", response_model=List[schemas.CartaoOut])
def listar_cartoes(codigo_quadro: str, db: Session = Depends(get_db)):
    return db.query(models.Cartao).filter(models.Cartao.codigo_quadro == codigo_quadro).all()


@router.get("/{codigo}", response_model=schemas.CartaoOut)
def visualizar_cartao(codigo: str, db: Session = Depends(get_db)):
    cartao = db.query(models.Cartao).filter(models.Cartao.codigo == codigo).first()
    if not cartao:
        raise HTTPException(status_code=404, detail="Cartão não encontrado")
    return cartao


@router.patch("/{codigo}/mover", response_model=schemas.CartaoOut)
def mover_cartao(codigo: str, payload: schemas.CartaoMover, db: Session = Depends(get_db)):
    cartao = db.query(models.Cartao).filter(models.Cartao.codigo == codigo).first()
    if not cartao:
        raise HTTPException(status_code=404, detail="Cartão não encontrado")

    quadro = db.query(models.Quadro).filter(models.Quadro.codigo == cartao.codigo_quadro).first()

    # Verificar limite WIP na coluna destino (excluindo o próprio cartão)
    qtd_coluna = db.query(models.Cartao).filter(
        models.Cartao.codigo_quadro == cartao.codigo_quadro,
        models.Cartao.coluna == payload.coluna.value,
        models.Cartao.codigo != codigo,
    ).count()
    if qtd_coluna >= quadro.limite_wip:
        raise HTTPException(status_code=409, detail=f"Limite WIP atingido na coluna '{payload.coluna.value}'")

    agora = datetime.now(timezone.utc)
    nova_coluna = payload.coluna.value

    # Registrar timestamps de ciclo
    if nova_coluna == "FAZENDO" and cartao.iniciado_em is None:
        cartao.iniciado_em = agora
    if nova_coluna == "FEITO" and cartao.concluido_em is None:
        cartao.concluido_em = agora

    cartao.coluna = nova_coluna
    db.commit()
    db.refresh(cartao)
    return cartao


@router.put("/{codigo}", response_model=schemas.CartaoOut)
def editar_cartao(codigo: str, payload: schemas.CartaoUpdate, db: Session = Depends(get_db)):
    cartao = db.query(models.Cartao).filter(models.Cartao.codigo == codigo).first()
    if not cartao:
        raise HTTPException(status_code=404, detail="Cartão não encontrado")
    cartao.nome = payload.nome
    cartao.descricao = payload.descricao
    cartao.responsavel = payload.responsavel
    cartao.prioridade = payload.prioridade.value
    cartao.data_limite = payload.data_limite
    db.commit()
    db.refresh(cartao)
    return cartao


@router.delete("/{codigo}", status_code=status.HTTP_204_NO_CONTENT)
def excluir_cartao(codigo: str, db: Session = Depends(get_db)):
    cartao = db.query(models.Cartao).filter(models.Cartao.codigo == codigo).first()
    if not cartao:
        raise HTTPException(status_code=404, detail="Cartão não encontrado")
    db.delete(cartao)
    db.commit()


@router.get("/quadro/{codigo_quadro}/metricas", response_model=schemas.MetricasOut)
def metricas(codigo_quadro: str, db: Session = Depends(get_db)):
    todos = db.query(models.Cartao).filter(models.Cartao.codigo_quadro == codigo_quadro).all()

    wip_atual = sum(1 for c in todos if c.coluna == "FAZENDO")
    throughput = sum(1 for c in todos if c.coluna == "FEITO")

    concluidos = [c for c in todos if c.criado_em and c.concluido_em]
    lead_time = None
    if concluidos:
        lead_time = sum((c.concluido_em - c.criado_em).days for c in concluidos) / len(concluidos)

    ciclo = [c for c in todos if c.iniciado_em and c.concluido_em]
    cycle_time = None
    if ciclo:
        cycle_time = sum((c.concluido_em - c.iniciado_em).days for c in ciclo) / len(ciclo)

    return schemas.MetricasOut(
        wip_atual=wip_atual,
        throughput=throughput,
        lead_time_medio_dias=lead_time,
        cycle_time_medio_dias=cycle_time,
    )

from fastapi import APIRouter, Depends, HTTPException, status, Query
from sqlalchemy.orm import Session
from typing import List
from database import get_db
import models
import schemas

router = APIRouter(prefix="/quadros", tags=["Membros"])


def _get_quadro_ou_403(codigo: str, email_solicitante: str, db: Session) -> models.Quadro:
    quadro = db.query(models.Quadro).filter(models.Quadro.codigo == codigo).first()
    if not quadro:
        raise HTTPException(status_code=404, detail="Quadro não encontrado")
    if quadro.email_dono != email_solicitante:
        raise HTTPException(status_code=403, detail="Apenas o dono pode gerenciar membros")
    return quadro


@router.get("/{codigo}/membros", response_model=List[schemas.MembroOut])
def listar_membros(codigo: str, db: Session = Depends(get_db)):
    quadro = db.query(models.Quadro).filter(models.Quadro.codigo == codigo).first()
    if not quadro:
        raise HTTPException(status_code=404, detail="Quadro não encontrado")

    resultado = []
    # dono sempre aparece primeiro
    dono = db.query(models.Conta).filter(models.Conta.email == quadro.email_dono).first()
    resultado.append(schemas.MembroOut(email_usuario=dono.email, papel="DONO", nome=dono.nome))

    for m in quadro.membros:
        conta = db.query(models.Conta).filter(models.Conta.email == m.email_usuario).first()
        resultado.append(schemas.MembroOut(
            email_usuario=m.email_usuario,
            papel=m.papel,
            nome=conta.nome if conta else None,
        ))
    return resultado


@router.post("/{codigo}/membros", status_code=status.HTTP_201_CREATED)
def convidar_membro(
    codigo: str,
    payload: schemas.MembroConvidar,
    email_dono: str = Query(...),
    db: Session = Depends(get_db),
):
    quadro = _get_quadro_ou_403(codigo, email_dono, db)

    if payload.email_usuario == email_dono:
        raise HTTPException(status_code=400, detail="O dono já pertence ao projeto")

    convidado = db.query(models.Conta).filter(models.Conta.email == payload.email_usuario).first()
    if not convidado:
        raise HTTPException(status_code=404, detail="Usuário não encontrado")

    ja_membro = db.query(models.QuadroMembro).filter(
        models.QuadroMembro.codigo_quadro == codigo,
        models.QuadroMembro.email_usuario == payload.email_usuario,
    ).first()
    if ja_membro:
        raise HTTPException(status_code=409, detail="Usuário já é membro deste projeto")

    novo = models.QuadroMembro(
        codigo_quadro=codigo,
        email_usuario=payload.email_usuario,
        papel="MEMBRO",
    )
    db.add(novo)
    db.commit()
    return {"message": f"{convidado.nome} adicionado ao projeto com sucesso"}


@router.delete("/{codigo}/membros/{email_usuario}", status_code=status.HTTP_204_NO_CONTENT)
def remover_membro(
    codigo: str,
    email_usuario: str,
    email_dono: str = Query(...),
    db: Session = Depends(get_db),
):
    _get_quadro_ou_403(codigo, email_dono, db)

    membro = db.query(models.QuadroMembro).filter(
        models.QuadroMembro.codigo_quadro == codigo,
        models.QuadroMembro.email_usuario == email_usuario,
    ).first()
    if not membro:
        raise HTTPException(status_code=404, detail="Membro não encontrado")
    db.delete(membro)
    db.commit()

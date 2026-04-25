from fastapi import APIRouter, Depends, HTTPException, status
from sqlalchemy.orm import Session
from typing import List
from database import get_db
import models
import schemas

router = APIRouter(prefix="/contas", tags=["Contas"])


@router.get("/{email}", response_model=schemas.ContaOut)
def visualizar(email: str, db: Session = Depends(get_db)):
    conta = db.query(models.Conta).filter(models.Conta.email == email).first()
    if not conta:
        raise HTTPException(status_code=404, detail="Conta não encontrada")
    return conta


@router.put("/{email}", response_model=schemas.ContaOut)
def editar(email: str, payload: schemas.ContaUpdate, db: Session = Depends(get_db)):
    conta = db.query(models.Conta).filter(models.Conta.email == email).first()
    if not conta:
        raise HTTPException(status_code=404, detail="Conta não encontrada")
    if payload.nome is not None:
        conta.nome = payload.nome
    if payload.senha is not None:
        conta.senha = payload.senha
    db.commit()
    db.refresh(conta)
    return conta


@router.delete("/{email}", status_code=status.HTTP_204_NO_CONTENT)
def excluir(email: str, db: Session = Depends(get_db)):
    conta = db.query(models.Conta).filter(models.Conta.email == email).first()
    if not conta:
        raise HTTPException(status_code=404, detail="Conta não encontrada")
    db.delete(conta)
    db.commit()

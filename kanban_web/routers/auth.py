from fastapi import APIRouter, Depends, HTTPException, status
from sqlalchemy.orm import Session
from database import get_db
import models
import schemas

router = APIRouter(prefix="/auth", tags=["Autenticação"])


@router.post("/login")
def login(payload: schemas.LoginRequest, db: Session = Depends(get_db)):
    conta = db.query(models.Conta).filter(models.Conta.email == payload.email).first()
    if not conta or conta.senha != payload.senha:
        raise HTTPException(status_code=status.HTTP_401_UNAUTHORIZED, detail="Email ou senha inválidos")
    return {"message": "Login realizado com sucesso", "email": conta.email, "nome": conta.nome}


@router.post("/cadastrar", response_model=schemas.ContaOut, status_code=status.HTTP_201_CREATED)
def cadastrar(payload: schemas.ContaCreate, db: Session = Depends(get_db)):
    existente = db.query(models.Conta).filter(models.Conta.email == payload.email).first()
    if existente:
        raise HTTPException(status_code=status.HTTP_409_CONFLICT, detail="Email já cadastrado")
    nova_conta = models.Conta(email=payload.email, nome=payload.nome, senha=payload.senha)
    db.add(nova_conta)
    db.commit()
    db.refresh(nova_conta)
    return nova_conta

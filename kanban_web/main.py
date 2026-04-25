from fastapi import FastAPI
from fastapi.staticfiles import StaticFiles
from fastapi.responses import FileResponse
from fastapi.middleware.cors import CORSMiddleware
from database import engine
import models
from routers import auth, contas, quadros, cartoes, membros

# Criar tabelas no banco
models.Base.metadata.create_all(bind=engine)

app = FastAPI(
    title="Kanban API",
    description="Sistema de gestão Kanban — UnB Engenharia de Software",
    version="1.0.0",
)

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# Routers
app.include_router(auth.router)
app.include_router(contas.router)
app.include_router(quadros.router)
app.include_router(cartoes.router)
app.include_router(membros.router)

# Servir frontend
app.mount("/static", StaticFiles(directory="static"), name="static")


@app.get("/", include_in_schema=False)
def root():
    return FileResponse("static/index.html")

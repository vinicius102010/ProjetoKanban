#include "testes.h"

void Teste_Limite::CriarUn(){
    limite = new Limite();
    estado = Sucesso;
}
void Teste_Limite::DestrUn(){
    delete limite;
}
void Teste_Limite::testarSucesso(){
    try{
        limite->setLimite(Valor_Valido);
        if (limite->getLimite() !=Valor_Valido){estado = Falha;}
    }
    catch(invalid_argument &excecao){
        estado = Falha;
    }
}
void Teste_Limite::testarFalha(){
    try{
    limite->setLimite(Valor_Invalido);
    estado = Falha;
    }
    catch(invalid_argument &excecao){
        if(limite->getLimite()== Valor_Invalido){
            estado = Falha;
        }
    }
}
int Teste_Limite::run(){
CriarUn();
testarSucesso();
testarFalha();
DestrUn();
return estado;
}

void Teste_Coluna::CriarUn(){
    coluna = new Coluna();
    estado = Sucesso;
}
void Teste_Coluna::DestrUn(){
    delete coluna;
}
void Teste_Coluna::testarSucesso(){
    try{
        coluna->setColuna(Valor_Valido);
        if (coluna->getColuna() !=Valor_Valido){estado = Falha;}
    }
    catch(invalid_argument &excecao){
        estado = Falha;
    }
}
void Teste_Coluna::testarFalha(){
    try{
    coluna->setColuna(Valor_Invalido);
    estado = Falha;
    }
    catch(invalid_argument &excecao){
        if(coluna->getColuna()== Valor_Invalido){
            estado = Falha;
        }
    }
}
int Teste_Coluna::run(){
CriarUn();
testarSucesso();
testarFalha();
DestrUn();
return estado;
}

void Teste_Codigo::CriarUn(){
    codigo = new Codigo();
    estado = Sucesso;
}
void Teste_Codigo::DestrUn(){
    delete codigo;
}
void Teste_Codigo::testarSucesso(){
    try{
        codigo->setCodigo(Valor_Valido);
        if (codigo->getCodigo() !=Valor_Valido){estado = Falha;}
    }
    catch(invalid_argument &excecao){
        estado = Falha;
    }
}
void Teste_Codigo::testarFalha(){
    try{
    codigo->setCodigo(Valor_Invalido);
    estado = Falha;
    }
    catch(invalid_argument &excecao){
        if(codigo->getCodigo()== Valor_Invalido){
            estado = Falha;
        }
    }
}
int Teste_Codigo::run(){
CriarUn();
testarSucesso();
testarFalha();
DestrUn();
return estado;
}

void Teste_Texto::CriarUn(){
    texto = new Texto();
    estado = Sucesso;
}
void Teste_Texto::DestrUn(){
    delete texto;
}
void Teste_Texto::testarSucesso(){
    try{
        texto->setTexto(Valor_Valido);
        if (texto->getTexto() !=Valor_Valido){estado = Falha;}
    }
    catch(invalid_argument &excecao){
        estado = Falha;
    }
}
void Teste_Texto::testarFalha(){
    try{
    texto->setTexto(Valor_Invalido);
    estado = Falha;
    }
    catch(invalid_argument &excecao){
        if(texto->getTexto()== Valor_Invalido){
            estado = Falha;
        }
    }
}
int Teste_Texto::run(){
CriarUn();
testarSucesso();
testarFalha();
DestrUn();
return estado;
}

void Teste_Senha::CriarUn(){
    senha = new Senha();
    estado = Sucesso;
}
void Teste_Senha::DestrUn(){
    delete senha;
}
void Teste_Senha::testarSucesso(){
    try{
        senha->setSenha(Valor_Valido);
        if (senha->getSenha() !=Valor_Valido){estado = Falha;}
    }
    catch(invalid_argument &excecao){
        estado = Falha;
    }
}
void Teste_Senha::testarFalha(){
    try{
    senha->setSenha(Valor_Invalido);
    estado = Falha;
    }
    catch(invalid_argument &excecao){
        if(senha->getSenha()== Valor_Invalido){
            estado = Falha;
        }
    }
}
int Teste_Senha::run(){
CriarUn();
testarSucesso();
testarFalha();
DestrUn();
return estado;
}

void Teste_Email::CriarUn(){
    email = new Email();
    estado = Sucesso;
}
void Teste_Email::DestrUn(){
    delete email;
}
void Teste_Email::testarSucesso(){
    try{
        email->setEmail(Valor_Valido);
        if (email->getEmail() !=Valor_Valido){estado = Falha;}
    }
    catch(invalid_argument &excecao){
        estado = Falha;
    }
}
void Teste_Email::testarFalha(){
    try{
    email->setEmail(Valor_Invalido);
    estado = Falha;
    }
    catch(invalid_argument &excecao){
        if(email->getEmail()== Valor_Invalido){
            estado = Falha;
        }
    }
}
int Teste_Email::run(){
CriarUn();
testarSucesso();
testarFalha();
DestrUn();
return estado;
}

void Teste_Conta::CriarUn(){
    this->conta = new Conta();
    estado = Sucesso;
}
void Teste_Conta::DestrUn(){
    delete conta;
}
void Teste_Conta::testarSucesso(){
    Email email;
    email.setEmail(Email_valido);
    conta->setEmail(email);
    if(conta->getEmail().getEmail()!= Email_valido){estado = Falha;}
    Texto nome;
    nome.setTexto(Nome_valido);
    conta->setNome(nome);
    if(conta->getNome().getTexto()!= Nome_valido){estado = Falha;}
    Senha senha;
    senha.setSenha(Senha_valido);
    conta->setSenha(senha);
    if(conta->getSenha().getSenha()!= Senha_valido){estado = Falha;}
}
int Teste_Conta::run(){
CriarUn();
testarSucesso();
DestrUn();
return estado;
}

void Teste_Quadro::CriarUn(){
    this->quadro = new Quadro();
    estado = Sucesso;
}
void Teste_Quadro::DestrUn(){
    delete quadro;
}
void Teste_Quadro::testarSucesso(){
    Codigo codigo;
    codigo.setCodigo(Codigo_valido);
    quadro->setCodigo(codigo);
    if(quadro->getCodigo().getCodigo()!= Codigo_valido){estado = Falha;}
    Texto nome;
    nome.setTexto(Nome_valido);
    quadro->setNome(nome);
    if(quadro->getNome().getTexto()!= Nome_valido){estado = Falha;}
    Texto descricao;
    descricao.setTexto(Descricao_valido);
    quadro->setDescricao(descricao);
    if(quadro->getDescricao().getTexto()!= Descricao_valido){estado = Falha;}
    Limite limite;
    limite.setLimite(Limite_valido);
    quadro->setLimite(limite);
    if(quadro->getLimite().getLimite()!= Limite_valido){estado = Falha;}
}
int Teste_Quadro::run(){
CriarUn();
testarSucesso();
DestrUn();
return estado;
}

void Teste_Cartao::CriarUn(){
    this->cartao = new Cartao();
    estado = Sucesso;
}
void Teste_Cartao::DestrUn(){
    delete cartao;
}
void Teste_Cartao::testarSucesso(){
    Codigo codigo;
    codigo.setCodigo(Codigo_valido);
    cartao->setCodigo(codigo);
    if(cartao->getCodigo().getCodigo()!= Codigo_valido){estado = Falha;}
    Texto nome;
    nome.setTexto(Nome_valido);
    cartao->setNome(nome);
    if(cartao->getNome().getTexto()!= Nome_valido){estado = Falha;}
    Texto descricao;
    descricao.setTexto(Descricao_valido);
    cartao->setDescricao(descricao);
    if(cartao->getDescricao().getTexto()!= Descricao_valido){estado = Falha;}
    Coluna coluna;
    coluna.setColuna(Coluna_valido);
    cartao->setColuna(coluna);
    if(cartao->getColuna().getColuna()!= Coluna_valido){estado = Falha;}
}
int Teste_Cartao::run(){
CriarUn();
testarSucesso();
DestrUn();
return estado;
}



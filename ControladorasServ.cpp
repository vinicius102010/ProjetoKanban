#include "ControladorasServ.h"
#include "Container.h"
#include "iostream"
//metodo de autenticao de servico
bool CntrlServAuten::autenticar(Email email, Senha senha){
        ContainerConta *containerconta;
        containerconta = ContainerConta::getInstancia();
        Conta contaAutent;
        if(containerconta->pesquisar(email,&contaAutent)){
            return contaAutent.getSenha().getSenha()==senha.getSenha();
        }
        return false;
}
//metodo para criar conta(servico)
bool CntrlServConta::criar(Conta conta){
    ContainerConta *containerconta;
    containerconta = ContainerConta::getInstancia();
    Conta contacriar;
    if(containerconta->pesquisar(conta.getEmail(),&contacriar)){
        return false;
    }
    return containerconta->incluir(conta);
}
//metodo para eliminar a conta(servico)
bool CntrlServConta::eliminar(Email email){
    ContainerConta *containerconta;
    containerconta=ContainerConta::getInstancia();
    Conta contarem;
    if(!containerconta->pesquisar(email,&contarem)){
        return false;
    }
    ContainerQuadro *containerquadro;
    containerquadro=ContainerQuadro::getInstancia();
    containerquadro->removerQuadro(email);
    return containerconta->remover(email);
}
//metodo para editar a conta(servico)
bool CntrlServConta::editar(Conta conta){
    ContainerConta *containerconta;
    containerconta=ContainerConta::getInstancia();
    Conta contaedit;
    if(!containerconta->pesquisar(conta.getEmail(),&contaedit)){
        return false;
    }
    return containerconta->atualizar(conta);
}
//metodo para ver a conta(servico)
bool CntrlServConta::visualisar(Email email,Conta* conta){
    ContainerConta *containerconta;
    containerconta=ContainerConta::getInstancia();
    return containerconta->pesquisar(email,conta);
}
//metodo para criacao de quadro(servico)
bool CntrlServGeren::criarQuadro(Email email, Quadro quadro){
    ContainerQuadro *containerquadro;
    containerquadro=ContainerQuadro::getInstancia();
    Quadro quadroteste;
    if(containerquadro->pesquisar(quadro.getCodigo(),&quadroteste)){
        return false;
    }
    return containerquadro->incluir(quadro, email);
}
//metodo para eliminar quadro(servico)
bool CntrlServGeren::elimQuadro(Codigo codigo,Email email){
    ContainerQuadro *containerquadro;
    containerquadro= ContainerQuadro::getInstancia();
    Quadro quadro;
    if(!containerquadro->pesquisar(codigo, &quadro)){
        return false;
    }
    if(containerquadro->pesquisar(codigo,&quadro)){
            if(quadro.getEmail().getEmail()==email.getEmail()){
    ContainerCartao *containercartao=ContainerCartao::getInstancia();
    containercartao->removerCartao(codigo);
    return containerquadro->remover(codigo);
    }else{return false;}
    }
    return false;
}
//metodo para ver quadro(servico)
bool CntrlServGeren::visuQuadro(Quadro *quadro,Email email){
    string Cards = "";
    ContainerQuadro *containerquadro=ContainerQuadro::getInstancia();
    if(containerquadro->pesquisar(quadro->getCodigo(),quadro)){
        ContainerCartao *containercartao=ContainerCartao::getInstancia();
        Cards = containercartao->pegarCard(quadro->getCodigo());
        quadro->setCartao(Cards);
        return quadro->getEmail().getEmail()== email.getEmail();
    }
    return false;
}
//metodo para criar cartao(servico)
bool CntrlServGeren::criarCartao(Codigo codigo, Cartao cartao){
    ContainerCartao *containercartao=ContainerCartao::getInstancia();
    Cartao cartaocriar;

    if(containercartao->pesquisar(cartao.getCodigo(),&cartaocriar)){
        return false;
    }

    Quadro quadroteste;
    ContainerQuadro *containerquadro = ContainerQuadro::getInstancia();

    if(containerquadro->pesquisar(cartao.getIdent(),&quadroteste)){
            if(containercartao->maxCard(codigo,cartao.getCodigo(),quadroteste.getLimite().getLimite())){

        return containercartao->incluir(codigo, cartao);
        }else{return false;}

        }

    return false;
}
//metodo para excluir caartao(servico)
bool CntrlServGeren::elimCartao(Codigo codigo){
    ContainerCartao *containercartao=ContainerCartao::getInstancia();
    Cartao cartao;
    if(!containercartao->pesquisar(codigo, &cartao)){
        return false;
    }
    return containercartao->remover(codigo);
}
//metodo para ver o cartao(servico)
bool CntrlServGeren::visuCartao(Cartao *cartao,Codigo ident){
    ContainerCartao *containercartao=ContainerCartao::getInstancia();
    if(containercartao->pesquisar(cartao->getCodigo(),cartao)){
        return cartao->getIdent().getCodigo()==ident.getCodigo();
    }
    return false;
}
//metodo para editar o cartao(servico)
bool CntrlServGeren::moverCartao(Cartao cartao){
    ContainerCartao *containercartao=ContainerCartao::getInstancia();
    Cartao cartaoteste;
    if(!containercartao->pesquisar(cartao.getCodigo(),&cartaoteste)){
        return false;
    }
    return containercartao->atualizar(cartao);
}

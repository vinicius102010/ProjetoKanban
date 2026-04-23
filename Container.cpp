#include "Container.h"

ContainerConta*ContainerConta::instancia=nullptr;
//definindo os metodos da classe
ContainerConta*ContainerConta::getInstancia(){
    if(instancia==nullptr){
        instancia = new ContainerConta();
    }
    return instancia;
}

bool ContainerConta::incluir(Conta conta){
    return container.insert(pair<string,Conta>(conta.getEmail().getEmail(), conta)).second;
}

bool ContainerConta::remover(Email email){
    map<string,Conta>::iterator it = container.find(email.getEmail());
    if(it != container.end()){
        container.erase(it);
        return true;
    }
    return false;
}

bool ContainerConta::pesquisar(Email email,Conta* conta){
    map<string, Conta>::iterator it = container.find(email.getEmail());
    if(it != container.end()){
        *conta = it-> second;
        return true;
    }
    return false;
}

bool ContainerConta::atualizar(Conta conta){
    map<string, Conta>::iterator it = container.find(conta.getEmail().getEmail());
    if(it != container.end()){
        it->second = conta;
        return true;
    }
    return false;
}

ContainerQuadro*ContainerQuadro::instancia=nullptr;
ContainerQuadro*ContainerQuadro::getInstancia(){
    if(instancia==nullptr){
        instancia = new ContainerQuadro();
    }
    return instancia;
}

bool ContainerQuadro::incluir(Quadro quadro, Email email){
    (void)email;
    return container.insert(pair<string,Quadro>(quadro.getCodigo().getCodigo(),quadro)).second;
}

bool ContainerQuadro::remover(Codigo codigo){
   return container.erase(codigo.getCodigo());
}

bool ContainerQuadro::pesquisar(Codigo codigo,Quadro* quadro){
    map<string, Quadro>::iterator it = container.find(codigo.getCodigo());
    if(it != container.end()){
        *quadro = it-> second;
        return true;
    }
    return false;
}

bool ContainerQuadro::atualizar(Quadro quadro){
    map<string,Quadro>::iterator it = container.find(quadro.getCodigo().getCodigo());
    if(it != container.end()){
        it->second = quadro;
        return true;
    }
    return false;
}

bool ContainerQuadro::removerQuadro(Email email){
    map<string,Quadro>::iterator it = container.begin();
    while( it != container.end()){
        if (it->second.getEmail().getEmail() == email.getEmail()){
            it = container.erase(it);
        }else{
            it++;
        }
    }
    return true;
}

ContainerCartao * ContainerCartao::instancia=nullptr;
ContainerCartao*ContainerCartao::getInstancia(){
    if(instancia==nullptr){
        instancia = new ContainerCartao();
    }
    return instancia;
}

bool ContainerCartao::incluir(Codigo codigo,Cartao cartao){
    (void)codigo;
    return container.insert(pair<string,Cartao>(cartao.getCodigo().getCodigo(),cartao)).second;
}
bool ContainerCartao::remover(Codigo ident){
    return container.erase(ident.getCodigo());
}


bool ContainerCartao::pesquisar(Codigo codigo,Cartao* cartao){
    map<string, Cartao>::iterator it = container.find(codigo.getCodigo());
    if(it != container.end()){
            *cartao = it-> second;
            return true;
    }
    return false;
}

bool ContainerCartao::atualizar(Cartao cartao){
    map<string, Cartao>::iterator it = container.find(cartao.getCodigo().getCodigo());
    if(it != container.end()){
        it->second.setColuna(cartao.getColuna());
        return true;
    }
    return false;
}

bool ContainerCartao::removerCartao(Codigo codigo){
    map<string, Cartao>::iterator it = container.begin();

    while (it != container.end()){
        if (it->second.getIdent().getCodigo() == codigo.getCodigo()){
            it = container.erase(it);
        }else{
            it++;
        }
    }
    return true;
}
string ContainerCartao::pegarCard(Codigo codigo){
    string cartoes = "";
    map<string, Cartao>::iterator it = container.begin();
    while(it != container.end()){
            if (it->second.getIdent().getCodigo()== codigo.getCodigo()){
                cartoes = cartoes + it->second.getCodigo().getCodigo() + ", ";
            }
            it++;

    }
    return cartoes;
}
bool ContainerCartao::maxCard(Codigo quadro, Codigo card, int lim){
    (void)card;
    int contador = 1;
    map<string,Cartao>::iterator it=container.begin();
    while(it!=container.end()){
        if(it->second.getIdent().getCodigo()==quadro.getCodigo()){contador+=1;}
        it++;
    }
    if(contador>lim){
        return false;
    }
    return true;
}

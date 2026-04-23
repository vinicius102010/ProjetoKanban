#ifndef CONTAINERS_H_INCLUDED
#define CONTAINERS_H_INCLUDED

#include "dominios.h"
#include "entidades.h"
#include "string.h"
#include <map>

using namespace std;
class ContainerConta{
private:
    map<string,Conta> container;
    static ContainerConta*instancia;
    ContainerConta(){}
public:
    static  ContainerConta* getInstancia();
    bool incluir(Conta);
    bool remover(Email);
    bool pesquisar(Email,Conta*);
    bool atualizar(Conta);
};
class ContainerQuadro{
private:
    map<string, Quadro> container;
    static ContainerQuadro*instancia;
    ContainerQuadro(){};
public:
    static ContainerQuadro* getInstancia();
    bool incluir(Quadro,Email);
    bool remover(Codigo);
    bool pesquisar(Codigo, Quadro*);
    bool atualizar(Quadro);
    bool removerQuadro(Email);
};

class ContainerCartao{
private:
    map<string, Cartao> container;
    static ContainerCartao*instancia;
    ContainerCartao(){};
public:
    static ContainerCartao* getInstancia();
    bool incluir(Codigo,Cartao);
    bool remover(Codigo);
    bool pesquisar(Codigo, Cartao*);
    bool atualizar(Cartao);
    bool removerCartao(Codigo);
    string pegarCard(Codigo);
    bool maxCard(Codigo,Codigo,int);
};

#endif // CONTROLADORAS_H_INCLUDED

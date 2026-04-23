#ifndef CONTROLADORASSERV_H_INCLUDED
#include "interfaces.h"
#include "dominios.h"
#include "entidades.h"
#include "controladoras.h"
#include "Container.h"
#include <stdexcept>
#include <iostream>
//Modulo serrvico autenticacao
class CntrlServAuten:public IServAuten{
public:
    bool autenticar(Email,Senha);
};
//modulo servico conta
class CntrlServConta:public IServContas{
public:
    bool criar(Conta);
    bool eliminar(Email);
    bool editar(Conta);
    bool visualisar(Email, Conta*);
};
//modulo servico gerenciamento
class CntrlServGeren:public IServGeren{
public:
        bool criarQuadro(Email, Quadro);
        bool elimQuadro(Codigo,Email);
        bool visuQuadro(Quadro*,Email);

        bool criarCartao(Codigo, Cartao);
        bool elimCartao(Codigo);
        bool visuCartao(Cartao*,Codigo);
        bool moverCartao(Cartao);

};



#endif // CONTROLADORASSERV_H_INCLUDED

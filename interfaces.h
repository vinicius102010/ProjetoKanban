#ifndef INTERFACES_H_INCLUDED
#define INTERFACES_H_INCLUDED
#include "dominios.h"
#include "entidades.h"
#include <stdexcept>

using namespace std;
class IServAuten;
class IServContas;
class IServGeren;

//interface apresenta��o autentica��o
class IApresAuten {
 public:

    virtual void setCntrlSerLocAuten(IServAuten *) = 0;
    virtual bool autenticar(Email*) = 0;
    virtual ~IApresAuten() {}
};

//interface apresenta��o contas
class IApresContas {
public:
    virtual void setCntrlSerLocConta(IServContas *)=0;
    virtual void cadastrar()=0;
    virtual bool executar(Email*)=0;
    virtual void setCntrlSerLocGeren(IServGeren*)=0;
    virtual ~IApresContas(){}
};

//interface aspresentacao gerenciamento
class IApresGeren {
public:
    virtual void executar(Email*)=0;
    virtual void setCntrlSerLocGeren(IServGeren*)=0;
    virtual ~IApresGeren(){}
};

//interface servi�o autentica��o
class IServAuten {
 public:
    virtual bool autenticar(Email,Senha) = 0;
    virtual ~IServAuten(){}
};

//interface servi�o contas
class IServContas {
public:
    virtual bool criar(Conta)=0;
    virtual bool eliminar(Email)=0;
    virtual bool editar(Conta)=0;
    virtual bool visualisar(Email, Conta*)=0;
    virtual ~IServContas(){}
};

//interface servi�o gerenciamento
class IServGeren {
public:
    virtual bool criarQuadro(Email,Quadro)=0;
    virtual bool visuQuadro(Quadro*,Email)=0;
    virtual bool elimQuadro(Codigo,Email)=0;

    virtual bool criarCartao(Codigo, Cartao)=0;
    virtual bool visuCartao(Cartao*,Codigo)=0;
    virtual bool moverCartao(Cartao)=0;
    virtual bool elimCartao(Codigo)=0;
    virtual ~IServGeren(){}
};
#endif // INTERFACES_H_INCLUDED

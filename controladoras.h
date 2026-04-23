#ifndef CONTROLADORAS_H_INCLUDED
#define CONTROLADORAS_H_INCLUDED
#include "interfaces.h"
#include "dominios.h"
#include "entidades.h"
#include <stdexcept>
#include <iostream>
#include <limits>
#include <cstdlib>

#ifdef _WIN32
    #define CLR_SCR system("cls")
#else
    #define CLR_SCR system("clear")
#endif

inline void pressAnyKey() {
    std::cout << "Pressione Enter para continuar..." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

using namespace std;
 //modulo de apresenta��o inicial;
 class CntrlApresInic{
 private:
     Email email;
     IApresAuten * cntrlApresAuten;
     IApresContas * cntrlApresConta;
     IApresGeren * cntrlApresGeren;
 public:
     void StartProgram();
     void setCntrlApresAuten(IApresAuten*);
     void setCntrlApresConta(IApresContas*);
     void setCntrlApresGeren(IApresGeren*);
 };
 inline void CntrlApresInic::setCntrlApresAuten(IApresAuten *cntrl){
    cntrlApresAuten = cntrl;
 }
 inline void CntrlApresInic::setCntrlApresConta(IApresContas *cntrl){
    cntrlApresConta = cntrl;
 }
 inline void CntrlApresInic::setCntrlApresGeren(IApresGeren *cntrl){
    cntrlApresGeren = cntrl;
 }

//Modulo Apresenta�ao Autentica��o
class CntrlApresAuten:public IApresAuten {
 private:

     IServAuten *cntrlSerLocAuten;
 public:
    bool autenticar(Email*);
    void setCntrlSerLocAuten(IServAuten*);
 };
 void inline CntrlApresAuten::setCntrlSerLocAuten(IServAuten *cntrlSerLocAuten){
 this->cntrlSerLocAuten = cntrlSerLocAuten;
 }

//modulo apresenta��o contas
class CntrlApresConta:public IApresContas{
private:
    IServContas *cntrlSerLocConta;
    IServGeren * cntrlSerLocGeren;
    void visualizar(Email);
    void editar(Email);
    bool eliminar(Email);
public:
    bool executar(Email*);
    void cadastrar();
    void setCntrlSerLocConta(IServContas*);
    void setCntrlSerLocGeren(IServGeren*);
};
void inline CntrlApresConta::setCntrlSerLocConta(IServContas *control){
cntrlSerLocConta = control;
}
void inline CntrlApresConta::setCntrlSerLocGeren(IServGeren *control){
cntrlSerLocGeren = control;
}
//Modulo Apresentacao gerenciamento
class CntrlApresGeren:public IApresGeren{
private:
    IServGeren * cntrlSerLocGeren;
    void criarQuadro(Email);
    void visuQuadro(Email);
    void elimQuadro(Email);
    void criarCartao();
    void visuCartao();
    void moverCartao();
    void elimCartao();
public:
    void executar(Email*);
    void setCntrlSerLocGeren(IServGeren*);
};
void inline CntrlApresGeren::setCntrlSerLocGeren(IServGeren *control){
cntrlSerLocGeren = control;
}

#endif // CONTROLADORAS_H_INCLUDED

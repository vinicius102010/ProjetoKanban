#include <iostream>
#include <typeinfo>
#include <string>
#include <stdexcept>
#include <stdlib.h>
#include "dominios.h"
#include "entidades.h"
#include "testes.h"
#include "interfaces.h"
#include "controladoras.h"
#include "ControladorasServ.h"
#include "Container.h"
using namespace std;

int main(){
    CntrlApresInic cntrlApresInicial;
    //iniciando camada apres
    IApresAuten *cntrlApresAuten = new CntrlApresAuten();
    IApresContas *cntrlApresConta = new CntrlApresConta();
    IApresGeren *cntrlApresGeren = new CntrlApresGeren();
    //ligando camada apres ao modulo de inicializacao
    cntrlApresInicial.setCntrlApresAuten(cntrlApresAuten);
    cntrlApresInicial.setCntrlApresConta(cntrlApresConta);
    cntrlApresInicial.setCntrlApresGeren(cntrlApresGeren);
    //iniciando camada de servico
    IServAuten *cntrlSerAuten = new CntrlServAuten();
    IServContas *cntrlServConta = new CntrlServConta();
    IServGeren *cntrlServGeren = new CntrlServGeren();
    //ligando camada de apres na camada de servico;
    cntrlApresAuten->setCntrlSerLocAuten(cntrlSerAuten);
    cntrlApresConta->setCntrlSerLocConta(cntrlServConta);
    cntrlApresGeren->setCntrlSerLocGeren(cntrlServGeren);
    //rodando o modulo de inicializacao
    cntrlApresInicial.StartProgram();

    delete cntrlApresAuten;
    delete cntrlSerAuten;
    delete cntrlApresConta;
    delete cntrlServConta;
    delete cntrlApresGeren;
    delete cntrlServGeren;

    return 0;

}

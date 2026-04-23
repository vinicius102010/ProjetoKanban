#include "controladoras.h"
//metodo inicializador
void CntrlApresInic::StartProgram(){
    int opcao;
    bool resultado = true;
    while(resultado){
        CLR_SCR;
        cout<<"     Bem vindo ao sistema kanban."<<endl;
        cout<<"Digite 1 caso queira fazer login;"<<endl;
        cout<<"Digite 2 caso queira criar uma conta;"<<endl;
        cout<<"Digite 3 caso queira finalizar."<<endl;
        cout<<"O que gostaria de fazer? "<<endl;
        cin>>opcao;
        switch(opcao){
        case 1: if(cntrlApresAuten->autenticar(&email)){
            bool resultado =true;
            while(resultado){
                CLR_SCR;
                cout<<"O que gostaria de fazer?"<<endl;
                cout<<"Digite 1 para servicos de conta."<<endl;
                cout<<"Digite 2 para servicos de gerenciamento de quadros."<<endl;
                cout<<"Digite 3 para voltar"<<endl;
                cin>>opcao;
                bool autenticar;
                switch(opcao){
                    case 1: autenticar = cntrlApresConta->executar(&email);
                            if(!autenticar){
                                resultado=false;
                            };
                            break;
                    case 2: cntrlApresGeren->executar(&email);
                            break;
                    case 3: resultado=false;
                            break;
                    }
                }
            }else{
                cout<<"Nao foi possivel fazer o login"<<endl;
                pressAnyKey();
            }
            break;
        case 2: cntrlApresConta->cadastrar();
                break;
        case 3: resultado=false;
                break;
        }
    }
    return;
}
//metodo de autenticacao
bool CntrlApresAuten::autenticar(Email *email){
    Senha senha;
    string entrada1,entrada2;
    int confirm;
    while(true) {
            CLR_SCR;
            cout<<"Faca o seu login."<<endl;
            cout << "Digite o email : "<<endl;
            cin >> entrada1;
            cout << "Digite a senha: "<<endl;
            cin >> entrada2;
        try {
            email->setEmail(entrada1);
            senha.setSenha(entrada2);
            break;
        }
        catch (const invalid_argument &exp) {
            cout << endl << "Dado em formato incorreto." << endl;
            cout << "Digite 1 para tentar novamente ou 2 para sair: "<<endl;
            cin >> confirm;
            if(confirm == 2) return false;
        }
    }
    return (cntrlSerLocAuten->autenticar(*email, senha));
}
//metodo para criar conta
void CntrlApresConta::cadastrar(){
    Email email;
    Texto nome;
    Senha senha;
    string entrada1,entrada2,entrada3,entrada4;
    CLR_SCR;
    cout<<"Preencha os dados da sua conta:"<<endl;
    cout<<"Digite o seu nome: "<<endl;
    cin.get();
    getline(cin,entrada1);
    cout<<"Digite o seu email: "<<endl;
    cin>>entrada2;
    cout<<"Digite a senha: "<<endl;
    cin>>entrada3;
    try{
        nome.setTexto(entrada1);
        email.setEmail(entrada2);
        senha.setSenha(entrada3);
    }
    catch(invalid_argument &exp){
        cout<< "Dado em formato invalido. Aperte qualquer tecla para continuar."<<endl;
        pressAnyKey();
        return;
    }
    Conta conta;
    conta.setEmail(email);
    conta.setNome(nome);
    conta.setSenha(senha);
    if(cntrlSerLocConta->criar(conta)){
        cout<<"Conta criada com sucesso. Aperte qualquer tecla para continuar."<<endl;
        pressAnyKey();
        return;
    } else{
        cout<<"Falha na criação da conta. Aperte qualquer tecla para continuar."<<endl;
        pressAnyKey();
        return;
    }
}
//metodo para executar os serviços de conta depois de logado
bool CntrlApresConta::executar(Email* email){
   bool itera=true;
   int entrada;
   while(itera){
        CLR_SCR;
        cout<<"Escolha uma das opcoes: "<<endl;
        cout<<"Digite 1 para visualizar os dados da conta."<<endl;
        cout<<"Digite 2 para excluir a conta"<<endl;
        cout<<"Digite 3 para editar os dados da conta."<<endl;
        cout<<"Digite 4 para voltar."<<endl;

        cin>>entrada;
        switch(entrada){
            case 1: visualizar(*email );
                break;
            case 2: if(eliminar(*email)) return false;
                break;
            case 3: editar(*email );
                break;
            case 4: itera = false;
                break;
        }
    }
    return true;
}
//metodo para visualizar os dados da conta
void CntrlApresConta::visualizar(Email email){
    Conta conta;
    CLR_SCR;
    if(cntrlSerLocConta->visualisar(email, &conta)){
        cout<<"A conta tem os seguintes dados"<<endl;
        cout<<"Nome: "<<conta.getNome().getTexto()<<endl;
        cout<<"Email: "<<conta.getEmail().getEmail()<<endl;
        cout<<"Senha: "<<conta.getSenha().getSenha()<<endl;
        pressAnyKey();
    }else{
        cout<<"Conta nao encontrada"<<endl;
        pressAnyKey();
    }
}
//metodo para exluir a conta
bool CntrlApresConta::eliminar(Email email){
    int resp;
    CLR_SCR;
    cout<<"Voce tem certeza que deseja excluir a conta?"<<endl;
    cout<<"Digite 1 caso a resposta for Sim"<<endl;
    cin>>resp;
    if(resp == 1){
        if(cntrlSerLocConta->eliminar(email)){
            cout<<"Conta excluida com sucesso"<<endl;
            pressAnyKey();
            return true;
        }else{
            cout<<"Nao foi possivel excluir a conta."<<endl;
            pressAnyKey();
        }
    }
    return false;
}
//metodo para editar a conta
void CntrlApresConta::editar(Email email){
    CLR_SCR;
    string entrada1, entrada2;
    cout<<"Digite os novos dados da conta: "<<endl;
    cout<<"Nome: ";
    cin.get();
    getline(cin,entrada1);
    cout<<"Senha: ";
    cin>>entrada2;
    Texto nome;
    Senha senha;
    try{
        nome.setTexto(entrada1);
        senha.setSenha(entrada2);
    }
    catch(invalid_argument &exp){
        cout << "Dado em formato incorreto." << endl;
        pressAnyKey();
        return;
    }
    Conta conta;
    conta.setEmail(email);
    conta.setNome(nome);
    conta.setSenha(senha);
    CLR_SCR;
    if(cntrlSerLocConta->editar(conta)){
        cout<<"Dados alterados com sucesso"<<endl;
        pressAnyKey();
        return;
    }else{
        cout<<"Nao foi possivel alterar os dados"<<endl;
        pressAnyKey();
        return;
    }
}
//metodo que executa serviços relacionados ao gerenciamento
void CntrlApresGeren::executar(Email* email){
    int opcao;
    bool itera = true;
    while(itera){
        CLR_SCR;
        cout<<"Para servicos relacionados aos quadros:"<<endl;
        cout<<"Digite 1 para criar um quadro."<<endl;
        cout<<"Digite 2 para visualizar o quadro."<<endl;
        cout<<"Digite 3 para excluir um quadro."<<endl;
        cout<<"Para servicos relacionados aos cartoes:"<<endl;
        cout<<"Digite 4 para criar um cartao."<<endl;
        cout<<"Digite 5 para visualizar o cartao."<<endl;
        cout<<"Digite 6 para mover um cartao."<<endl;
        cout<<"Digite 7 para excluir um cartao."<<endl;
        cout<<"Digite 8 para voltar."<<endl;
        cin>>opcao;
        switch(opcao){
            case 1: criarQuadro(*email);
                    break;
            case 2: visuQuadro(*email);
                    break;
            case 3 : elimQuadro(*email);
                    break;
            case 4 : criarCartao();
                    break;
            case 5 : visuCartao();
                    break;
            case 6 : moverCartao();
                    break;
            case 7 : elimCartao();
                    break;
            case 8 : itera = false;
                    break;
        }
    }
}
//metodo para criar quadro
void CntrlApresGeren::criarQuadro(Email email){
    string entrada1, entrada2, entrada3;
    int entrada4;
    Texto nome;
    Texto descricao;
    Codigo codigo;
    Limite limite;
    CLR_SCR;
    cout<<"Preencha os seguintes dados: "<<endl;
    cout<<"Nome do quadro: "<<endl;
    cin.get();
    getline(cin,entrada1);
    cout<<"Codigo quadro: "<<endl;
    cin>>entrada3;
    cout<<"Limite do quadro: "<<endl;
    cin>>entrada4;
    cout<<"Descricao do quadro:"<<endl;
    cin.get();
    getline(cin,entrada2);
    try{
        nome.setTexto(entrada1);
        descricao.setTexto(entrada2);
        codigo.setCodigo(entrada3);
        limite.setLimite(entrada4);
    }
    catch(invalid_argument &exp){
        cout<<"Dados em formato incorreto."<<endl;
        pressAnyKey();
        return;
    }
    Quadro quadro;
    quadro.setNome(nome);
    quadro.setDescricao(descricao);
    quadro.setCodigo(codigo);
    quadro.setLimite(limite);
    quadro.setEmail(email);
    if(cntrlSerLocGeren->criarQuadro(email,quadro)){
        cout<<"Quadro criado com sucesso."<<endl;
        pressAnyKey();
        return;
    }else{
        cout<<"Falha na criacao do quadro."<<endl;
        pressAnyKey();
        return;
    }
}
//metodo para excluir um quadro;
void CntrlApresGeren::elimQuadro(Email email){
    string entrada;
    CLR_SCR;
    cout<<"Qual o codigo do quadro que deseja excluir?"<<endl;
    cout<<"Codigo: ";
    cin>>entrada;
    Codigo codigo;
    try{
        codigo.setCodigo(entrada);
    }
    catch(invalid_argument &exp){
        cout<<"Dados em formato incorreto."<<endl;
        pressAnyKey();
        return;
    }
    CLR_SCR;
    if(cntrlSerLocGeren->elimQuadro(codigo,email)){
        cout<<"Quadro excluido com sucesso"<<endl;
        pressAnyKey();
        return;
    }else{
        cout<<"Falha ao excluir quadro."<<endl;
        pressAnyKey();
        return;
    }
}
//metodo para ver quadro
void CntrlApresGeren::visuQuadro(Email email){
    string entrada;
    CLR_SCR;
    cout<<"Qual o codigo do quadro que deseja visualizar?"<<endl;
    cout<<"Codigo: ";
    cin>>entrada;
    Codigo codigo;
    try{
        codigo.setCodigo(entrada);
    }
    catch(invalid_argument &exp){
        cout<<"Dado em formato incorreto."<<endl;
        pressAnyKey();
        return;
    }
    Quadro quadro;
    quadro.setCodigo(codigo);
    CLR_SCR;
    if(cntrlSerLocGeren->visuQuadro(&quadro,email)){
        cout<<"Informacoes do quadro: "<<endl;
        cout<<"Nome: "<<quadro.getNome().getTexto()<<endl;
        cout<<"Descricao: "<<quadro.getDescricao().getTexto()<<endl;
        cout<<"Codigo: "<<quadro.getCodigo().getCodigo()<<endl;
        cout<<"Limite: "<<quadro.getLimite().getLimite()<<endl;
        cout<<"Os cartoes sao: "<<quadro.getCartao()<<endl;
        pressAnyKey();
    }else{
        cout<<"Falha ao recuperar o quadro"<<endl;
        pressAnyKey();
    }
}
//metodo para criar cartao
void CntrlApresGeren::criarCartao(){
    string entrada1,entrada2,entrada3,entrada4, refer;
    CLR_SCR;
    cout<<"Digite o Codigo do quadro que deseja adicionar o cartao."<<endl;
    cout<<"Codigo do quadro: ";
    cin>>refer;
    Codigo codigorefer;
    try{
        codigorefer.setCodigo(refer);
    }
    catch(invalid_argument &exp){
        cout<<"Dados em formato incorreto."<<endl;
        pressAnyKey();
        return;
    }
    Texto nome;
    Texto descricao;
    Codigo codigo;
    Coluna coluna;
    CLR_SCR;
    cout<<"Digite os dados do cartao: "<<endl;
    cout<<"Nome: "<<endl;
    cin.get();
    getline(cin,entrada1);
    cout<<"Codigo: "<<endl;
    cin>>entrada3;
    cout<<"Descricao: "<<endl;
    cin.get();
    getline(cin,entrada2);
    cout<<"Coluna: "<<endl;
    cin>>entrada4;
    try{
        nome.setTexto(entrada1);
        descricao.setTexto(entrada2);
        codigo.setCodigo(entrada3);
        coluna.setColuna(entrada4);
    }
    catch(invalid_argument &exp){
        cout<<"Dado em formato incorreto."<<endl;
        pressAnyKey();
        return;
    }
    Cartao cartao;
    cartao.setNome(nome);
    cartao.setDescricao(descricao);
    cartao.setCodigo(codigo);
    cartao.setColuna(coluna);
    cartao.setIdent(codigorefer);
    if(cntrlSerLocGeren->criarCartao(codigorefer, cartao)){
        cout<<"Cartao criado com sucesso."<<endl;
        pressAnyKey();
        return;
    }else{
        cout<<"Falha ao criar o cartao."<<endl;
        pressAnyKey();
        return;
    }
}
//metodo para eliminar um cartao
void CntrlApresGeren::elimCartao(){
    string refer;
    CLR_SCR;
    cout<<"Qual o codigo do cartao que deseja excluir?"<<endl;
    cout<<"Codigo: ";
    cin>>refer;
    Codigo codigo;
    try{
        codigo.setCodigo(refer);
    }
    catch(invalid_argument &exp){
        cout<<"Dados em formato incorreto."<<endl;
        pressAnyKey();
        return;
    }
    CLR_SCR;
    if(cntrlSerLocGeren->elimCartao(codigo)){
        cout<<"Cartao excluido com sucesso"<<endl;
        pressAnyKey();
        return;
    }else{
        cout<<"Falha ao excluir cartao."<<endl;
        pressAnyKey();
        return;
    }
}
//metodo para visualizar cartao
void CntrlApresGeren::visuCartao(){
    string refer,refer2;
    CLR_SCR;
    cout<<"Qual o codigo do Quadro que o cartao esta associado?"<<endl;
    cout<<"Codigo do quadro: ";
    cin>>refer2;
    cout<<"Qual o codigo do cartao que quer visualizar? "<<endl;
    cout<<"Codigo: ";
    cin>>refer;
    Codigo codigo,codigorefer;
    try{
        codigo.setCodigo(refer);
        codigorefer.setCodigo(refer2);
    }
    catch(invalid_argument &exp){
        cout<<"Dado em formato incorreto."<<endl;
        pressAnyKey();
        return;
    }
    Cartao cartao;
    cartao.setCodigo(codigo);
    CLR_SCR;
    if(cntrlSerLocGeren->visuCartao(&cartao,codigorefer)){
        cout<<"Estes sao dos dados do cartao:"<<endl;
        cout<<"Nome: "<<cartao.getNome().getTexto()<<endl;
        cout<<"Descricao: "<<cartao.getDescricao().getTexto()<<endl;
        cout<<"Codigo: "<<cartao.getCodigo().getCodigo()<<endl;
        cout<<"Coluna: "<<cartao.getColuna().getColuna()<<endl;
        pressAnyKey();
    }else{
        cout<<"Falha ao recuperar dados do cartao."<<endl;
        pressAnyKey();
    }
}
//codigo para mover o cartao
void CntrlApresGeren::moverCartao(){
    string refer;
    CLR_SCR;
    cout<<"Qual o codigo do cartao que quer mover? "<<endl;
    cout<<"Codigo: ";
    cin>>refer;
    Codigo codigo;
    try{
        codigo.setCodigo(refer);
    }
    catch(invalid_argument &exp){
        cout<<"Dado em formato incorreto."<<endl;
        pressAnyKey();
        return;
    }
    CLR_SCR;
    string colun,entrada1,entrada2,entrada3;
    cout<<"Digite a nova coluna do cartao:"<<endl;
    cout<<"Coluna: ";
    cin>>colun;
    Coluna coluna;
    try{
        coluna.setColuna(colun);
    }
    catch(invalid_argument &exp){
        cout<<"Dado em formato incorreto."<<endl;
        pressAnyKey();
        return;
    }
    Cartao cartao;
    cartao.setCodigo(codigo);
    cartao.setColuna(coluna);
    if(cntrlSerLocGeren->moverCartao(cartao)){
        cout<<"Coluna alterada com sucesso."<<endl;
        pressAnyKey();
        return;
    }else{
        cout<<"Falha ao mover o cartao."<<endl;
        pressAnyKey();
        return;
    }
}

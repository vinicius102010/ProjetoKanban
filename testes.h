#ifndef TESTES_H_INCLUDED
#define TESTES_H_INCLUDED
#include "dominios.h"
#include "entidades.h"
using namespace std;

class Teste_Limite {
private:
    const static int Valor_Valido   = 20;
    const static int Valor_Invalido = 16;
    Limite *limite;
    int estado;
    void CriarUn();
    void DestrUn();
    void testarSucesso();
    void testarFalha();

public:
    const static int Sucesso = 0;
    const static int Falha = -1;
    int run();
};
class Teste_Coluna {
private:
    inline const static  string Valor_Valido   ="CONCLUIDO";
    inline const static string Valor_Invalido ="aaaaaaa";
    Coluna *coluna;
    int estado;
    void CriarUn();
    void DestrUn();
    void testarSucesso();
    void testarFalha();

public:
    const static int Sucesso = 0;
    const static int Falha = -1;
    int run();
};
class Teste_Codigo {
private:
    inline const static string Valor_Valido   ="AB01";
    inline const static string Valor_Invalido ="A10B";
    Codigo *codigo;
    int estado;
    void CriarUn();
    void DestrUn();
    void testarSucesso();
    void testarFalha();

public:
    const static int Sucesso = 0;
    const static int Falha = -1;
    int run();
};
class Teste_Texto {
private:
    inline const static string Valor_Valido   ="Abcde. Abcccfedf.";
    inline const static string Valor_Invalido ="A10B";
    Texto *texto;
    int estado;
    void CriarUn();
    void DestrUn();
    void testarSucesso();
    void testarFalha();

public:
    const static int Sucesso = 0;
    const static int Falha = -1;
    int run();
};
class Teste_Senha {
private:
    inline const static string Valor_Valido   = "Ab0.5";
    inline const static string Valor_Invalido = "Jm00,";
    Senha *senha;
    int estado;
    void CriarUn();
    void DestrUn();
    void testarSucesso();
    void testarFalha();

public:
    const static int Sucesso = 0;
    const static int Falha = -1;
    int run();
};
class Teste_Email {
private:
    inline const static string Valor_Valido   = "teste.cer@to.com";
    inline const static string Valor_Invalido = "usuario.@teste.com";
    Email *email;
    int estado;
    void CriarUn();
    void DestrUn();
    void testarSucesso();
    void testarFalha();

public:
    const static int Sucesso = 0;
    const static int Falha = -1;
    int run();
};
class Teste_Conta {
private:
    inline const static string Email_valido = "teste@usuario.com";
    inline const static string Nome_valido = "Usuario da silva";
    inline const static string Senha_valido = "Ab0.5";
    Conta *conta;
    int estado;
    void CriarUn();
    void DestrUn();
    void testarSucesso();

public:
    const static int Sucesso = 0;
    const static int Falha = -1;
    int run();
};
class Teste_Quadro {
private:
    inline const static string Codigo_valido = "AB02";
    inline const static string Nome_valido = "Usuario da silva";
    inline const static string Descricao_valido = "Ab0. Bfg";
    const static int Limite_valido = 10;
    Quadro *quadro;
    int estado;
    void CriarUn();
    void DestrUn();
    void testarSucesso();

public:
    const static int Sucesso = 0;
    const static int Falha = -1;
    int run();
};
class Teste_Cartao {
private:
    inline const static string Codigo_valido = "AB02";
    inline const static string Nome_valido = "Usuario da silva";
    inline const static string Descricao_valido = "Ab0. Bfg";
    inline const static string Coluna_valido = "CONCLUIDO";
    Cartao *cartao;
    int estado;
    void CriarUn();
    void DestrUn();
    void testarSucesso();

public:
    const static int Sucesso = 0;
    const static int Falha = -1;
    int run();
};
#endif // TESTES_H_INCLUDED

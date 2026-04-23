#ifndef ENTIDADES_H_INCLUDED
#define ENTIDADES_H_INCLUDED

#include "dominios.h"
#include <string>

using namespace std;

///
/// Classe que sera ultilizada para acessar o sistema e identificar o usuario. Recebe nome, email e senha. Onde:
///
/// - nome e um objeto do tipo Texto que representa o nome do usuario.
/// - email e um objeto do tipo Email que representa o email do usuario.
/// - senha e um objeto do tipo Senha que representa a senha do usuario.
///
class Conta {
private:
    Email email;
    Texto nome;
    Senha senha;
public:
///
/// Armazena o email.
///
///@param email Email
///

    void setEmail(const Email&);
///
/// Retorna o email
///
///@return email
///
    Email getEmail() const;
///
/// Armazena o nome.
///
///@param nome Texto
///
    void setNome(const Texto&);
///
/// Retorna o nome
///
///@return nome
///
    Texto getNome() const;
///
/// Armazena a senha.
///
///@param senha Senha
///
    void setSenha(const Senha&);
///
/// Retorna a senha
///
///@return senha
///
    Senha getSenha() const;
};
inline void Conta::setEmail(const Email &email){
    this->email = email;
}
inline Email Conta::getEmail() const {
    return email;
}
inline void Conta::setNome(const Texto &nome){
    this-> nome = nome;
}
inline Texto Conta::getNome() const {
    return nome;
}
inline void Conta::setSenha(const Senha &senha){
    this->senha = senha;
}
inline Senha Conta::getSenha()  const  {
    return senha;
}
///
/// Classe que sera ultilizada para criar os quadros onde serao armazenados os cartoes, que se deslocam pelo quadro, representando o status em que a tarefa se encontra. Recebe nome, codigo , descricao e limite. Onde:
///
/// - nome e um objeto do tipo Texto que representa o nome do projeto.
/// - codigo e um objeto do tipo Codigo que representa o codigo identificador do quadro.
/// - descricao e um objeto do tipo Texto que descreve o projeto.
/// - limite e um objeto do tipo Limite que representa a quantidade maxima de quadros.
///
class Quadro {
private:
    Codigo codigo;
    Texto nome;
    Texto descricao;
    Limite limite;
    Email email ;
    string cartoes = "";
public:
    void setCartao(string);
    string getCartao() const;
    void setEmail(const Email&);
    Email getEmail() const;
///
/// Armazena o codigo.
///
///@param codigo Codigo
///
    void setCodigo(const Codigo&);
///
/// Retorna o codigo.
///
///@return codigo
///
    Codigo getCodigo() const;
///
/// Armazena o nome.
///
///@param nome Texto
///
    void setNome(const Texto&);
///
/// Retorna o nome.
///
///@return nome
///
    Texto getNome() const;
///
/// Armazena a descricao.
///
///@param descricao Texto
///
    void setDescricao(const Texto&);
///
/// Retorna a descricao.
///
///@return descricao
///
    Texto getDescricao() const;
///
/// Armazena o limite.
///
///@param limite Limite
///
    void setLimite(const Limite&);
///
/// Retorna o limite.
///
///@return limite
///
    Limite getLimite() const;
};
inline void Quadro::setCartao(string cartoes){
   this->cartoes = cartoes;
}
inline string Quadro::getCartao() const {
    return cartoes;
}
inline void Quadro::setEmail(const Email &email){
   this->email = email;
}
inline Email Quadro::getEmail() const {
    return email;
}
inline void Quadro::setCodigo(const Codigo& codigo){
    this->codigo = codigo;
}
inline Codigo Quadro::getCodigo() const {
    return codigo;
}
inline void Quadro::setNome(const Texto& nome){
    this-> nome=nome;
}
inline Texto Quadro::getNome() const {
    return nome;
}
inline void Quadro::setDescricao(const Texto& descricao){
    this-> descricao=descricao;
}
inline Texto Quadro::getDescricao() const {
    return descricao;
}
inline void Quadro::setLimite(const Limite& limite){
    this->limite=limite;
}
inline Limite Quadro::getLimite()  const  {
    return limite;
}
///
/// Classe que sera ultilizada para representar as tarefas a serem execultadas e o status em que a mesma se encontra(baseado em qual local do quadro esta) e recebe nome, codigo, descricao e coluna. Onde:
///
/// - nome e um objeto do tipo Texto e representa o nome da terefa.
/// - codigo e um objeto do tipo Codigo que representa o codigo identificador do cartao.
/// - descricao e um objeto do tipo Texto que descreve o que deve ser feito na tarefa.
/// - coluna e um objeto do tipo Coluna que representa qual o status da tarefa.
///
class Cartao {
private:
    Codigo ident;
    Codigo codigo;
    Texto nome;
    Texto descricao;
    Coluna coluna;
public:
    void setIdent(const Codigo&);
    Codigo getIdent() const;
///
/// Armazena o codigo.
///
///@param codigo Codigo
///
    void setCodigo(const Codigo&);
///
/// Retorna o codigo.
///
///@return codigo
///
    Codigo getCodigo() const;
///
/// Armazena o nome.
///
///@param nome Texto
///
    void setNome(const Texto&);
///
/// Retorna o nome.
///
///@return nome
///
    Texto getNome() const;
///
/// Armazena a descricao.
///
///@param descricao Texto
///
    void setDescricao(const Texto&);
///
/// Retorna a descricao.
///
///@return descricao
///
    Texto getDescricao() const;
///
/// Armazena a coluna.
///
///@param coluna Coluna
///
    void setColuna(const Coluna&);
///
/// Retorna a coluna.
///
///@return coluna
///
    Coluna getColuna() const;
};
inline void Cartao::setIdent(const Codigo& ident){
  this->ident = ident;
}
inline Codigo Cartao::getIdent() const{
   return ident;
}
inline void Cartao::setCodigo(const Codigo& codigo){
    this->codigo = codigo;
}
inline Codigo Cartao::getCodigo() const {
    return codigo;
}
inline void Cartao::setNome(const Texto& nome){
    this-> nome=nome;
}
inline Texto Cartao::getNome() const {
    return nome;
}
inline void Cartao::setDescricao(const Texto& descricao){
    this-> descricao=descricao;
}
inline Texto Cartao::getDescricao() const {
   return descricao;
}
inline void Cartao::setColuna(const Coluna& coluna){
    this->coluna=coluna;
}
inline Coluna Cartao::getColuna()  const  {
    return coluna;
}
#endif // ENTIDADES_H_INCLUDED


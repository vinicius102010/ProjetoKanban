
#ifndef DOMINIOS_H_INCLUDED
#define DOMINIOS_H_INCLUDED
#include <stdexcept>
#include <string>
using namespace std;
///
/// Valor que limita a quantidade maxima de quadros e de cartoes que o usuario pode ter.
///
/// Regra do formato:
///
/// - Limite e valido se for um dos seguintes valores: 5, 10, 15 ou 20
///
class Limite {
    private:
        int limite;
        void validar(int);
    public:

///
/// Armazena o limite caso ele seja valido.
///
/// Lanca excecao caso o limite informado seja invalido.
///
///@param valor Limite
///
///@throw invalid_argument
///
        void setLimite(int);
///
/// Retorna o limite.
///
///@return limite
///
        int getLimite() const;
};
inline int Limite::getLimite() const{
    return limite;
}
///
/// Representa os diferentes estagios em que a tarefa pode se encontrar.
///
/// Regra do formato:
///
/// - Coluna pode apresentar apenas um dos tres valores: SOLICITADO, EM EXECUCAO ou CONCLUIDO.
///
class Coluna {
    private:
        string coluna;
        void validar(string);
    public:
///
/// Armazena a coluna caso ela seja valida.
///
/// Lanca excecao caso a coluna informada seja invalida.
///
///@param valor Coluna
///
///@throw invalid_argument
///
        void setColuna(string);
///
/// Retorna a coluna.
///
///@return coluna
///
        string getColuna() const;
};
inline string Coluna::getColuna() const{
    return coluna;
}
///
/// Padrao ultilizado para o codigo que vai ser ultilizado para representar os quadros e os cartoes.
///
/// Regra do formato:
///
/// - Codigo deve conter o formato <u><b>LLDD</b></u> onde:
///
///     - L e letra maiuscula
///     - D e um digito de 0 a 9
///
class Codigo {
    private:
        string codigo;
        void validar(string);
    public:
///
/// Armazena o codigo caso ele seja valido.
///
/// Lanca excecao caso o codigo informado seja invalido.
///
///@param valor Codigo
///
///@throw invalid_argument
///
        void setCodigo(string);
///
/// Retorna o codigo.
///
///@return codigo
///
        string getCodigo() const;
};
inline string Codigo::getCodigo() const{
    return codigo;
}
///
///Padrao ultilizado para os textos que representara os nomes e as descricoes.
///
/// Regra do formato:
///
/// - Texto deve conter de 5 a 30 caracteres.
///
/// - Cada caracter deve ser letra maiuscula (A_Z), minuscula(a_z), digito(0_9), sinal de pontuacao(. , ; ! ?) ou espaco em branco.
///
///     - Nao pode ter espacos em branco em sequencia
///     - Nao pode ter pontuacao em sequencia
///     - Nao tem acentuacao
///     - Primeiro caracter e primeiro caracter apos sinal de pontuacao(exceto , e ;) deve ser maiuscula
///
class Texto {
    private:
        string texto;
        void validar(string);
        bool valid_texto(string);
    public:
///
/// Armazena o texto caso ele seja valido.
///
/// Lanca excecao caso o texto informado seja invalido.
///
///@param valor Texto
///
///@throw invalid_argument
///
        void setTexto(string);
///
/// Retorna o texto.
///
///@return texto
///
        string getTexto() const;

};
inline string Texto::getTexto() const{
    return texto;
}
///
/// Padrao ultilizado para a senha que o usuario utilizara para acessar o sistema.
///
/// Regras do formato:
///
/// - Senha deve conter o formato <u><b>XXXXX</b></u> onde:
///
///     - X dev ser letra maiuscula (A_Z), minuscula(a_z), digito(0_9) ou sinal de pontuacao(. , ; ! ?)
///     - Nao pode ter caracter duplicado.
///     - Deve ter pelo menos 1 letra maiuscula.
///     - Deve ter pelo menos 1 letra minuscula.
///     - Deve ter pelo menos 1 digito.
///     - Deve ter pelo menos 1 sinal de pontuacao
class Senha {
    private:
        string senha;
        void validar(string);
        bool valid_senha(string);
    public:
///
/// Armazena a senha caso ela seja valida.
///
/// Lanca excecao caso a senha informada seja invalida.
///
///@param valor Senha
///
///@throw invalid_argument
///
        void setSenha(string);
///
/// Retorna a senha.
///
///@return senha
///
        string getSenha() const;
};
inline string Senha::getSenha() const{
    return senha;
}
///
/// Padrao ultilizado  para os emails que os usuarios vao utilizar para entrar no sistema.
///
/// Regras do formato:
///
/// - Email deve seguir o formato <b><i>nome</i>@<i>dominio</i></b> onde:
///
///     - Cada caracter deve ser letra maiuscula, minuscula, digito ou ponto(.).
///     - Nao podem ter pontos em sequencia.
///     - nome deve conter de 2 a 10 caracteeres, e o ultimo caracter nao pode ser ponto(.).
///     - dominio deve conter de 2 a 20 caracteres, e o primeiro caracter nao pode ser ponto(.).
///
class Email {
    private:
        string email;
        void validar(string);
        bool valid_mail(string);
    public:
///
/// Armazena o email caso ele seja valido.
///
/// Lanca excecao caso o email informado seja invalido.
///
///@param valor Email
///
///@throw invalid_argument
///
        void setEmail(string);
///
/// Retorna o email.
///
///@return email
///
        string getEmail() const;
};
inline string Email::getEmail() const{
    return email;
}
#endif // DOMINIOS_H_INCLUDED

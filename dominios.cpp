
#include "dominios.h"
#include <cstring>
#include <string>
#include <iostream>
#include<bits/stdc++.h>
using namespace std;
void Limite::validar(int limite){
    if (!(limite == 5 || limite == 10 || limite == 15 || limite == 20))
        throw invalid_argument("Argumento invalido.");
}
void Limite::setLimite(int valor){
    validar(valor);
    this->limite = valor;
}
void Coluna::validar(string coluna){
    if (!(coluna == "SOLICITADO" || coluna == "EM EXECUCAO" || coluna == "CONCLUIDO"))
        throw invalid_argument("Argumento invalido.");
}
void Coluna::setColuna(string valor){
    validar(valor);
    this->coluna = valor;
}
void Codigo::validar(string codigo){
    if (!(codigo.length()==4 && codigo[0]>=65 && codigo[0]<=90 && codigo[1]>=65 && codigo[1]<=90 && codigo[2]>=48 && codigo[2]<=57 && codigo[3]>=48 && codigo[3]<=57))
        throw invalid_argument("Argumento invalido.");
}
void Codigo::setCodigo(string valor){
    validar(valor);
    this->codigo = valor;
}
bool Texto::valid_texto(string text){
    //IF PARA VER SE O TAMANHO ESTA ENTRE 5 E 30, E VER SE A PRIMEIRA LETRA � MAIUSCULA
    if (text.length()>=5 && text.length()<=30 && text[0]>=65 && text[0]<=90){
        //FOR PARA PASSAR POR TODAS AS LETRAS
for(size_t i=0; i<text.length(); i++){
            // IF PARA VER SE CADA LETRA � UMA LETRA MAIUSCULA, MINUSCULA, ESPA�O OU ,.;!?
            if((text[i]>=65 && text[i]<=90)||(text[i]>=97 && text[i]<=122)||(text[i]>=48 && text[i]<=57)|| text[i]==32 || text[i]==33 || text[i]==44 || text[i]==46 ||text[i]==59 || text[i]==63){

            }else{
                return  true;
            }
            //IF PARA VER SE NAO TEM 2 ESPA�OS SUBSEQUENTES
            if (text[i]==32 && text[i-1]==32){
                return  true;
            }
            //IF PARA VER SE NAO TEM 2 SINAIS SUBSEQUENTES
            if(((text[i]==33 || text[i]==44 || text[i]==46 ||text[i]==59 || text[i]==63)&&(text[i-1]==33 || text[i-1]==44 || text[i-1]==46 ||text[i-1]==59 || text[i-1]==63))){
                return  true;
            }
            //IF PRA VER SE DEPOIS DE UM PONTO O PROS CARACTERE � MAIUSCULOO
            if((text[i]==33 || text[i]==46 || text[i]==63) && !(text[i+1]>=65 && text[i+1]<=90)){
                    if(i==text.length()-1){return false;}
                    if(text[i+1]==32 && (text[i+2]>=65 && text[i+2]<=90)){return false;}
                    return  true;
            }
        }
    }else{
        return  true;
    }
    return false;
}
void Texto::validar(string texto){
    if (valid_texto(texto))
        throw invalid_argument("Argumento invalido.");
}
void Texto::setTexto(string valor){
    validar(valor);
    this->texto = valor;
}
bool Senha::valid_senha(string senh){
    int maiuscula = 0;
    int minuscula = 0;
    int digito = 0;
    int pont = 0;
    if (senh.length()==5){
            if(senh[0]== senh[1] || senh[0]== senh[2] || senh[0]== senh[3] || senh[0]== senh[4]){
                return true;
            }
            if(senh[1]== senh[2] || senh[1]== senh[3] || senh[1]== senh[4] ){
                return true;
            }
            if(senh[2]== senh[3] || senh[2]== senh[4]){
                return true;
            }
            if(senh[3]== senh[4]){
                return true;
            }
            for(int i=0; i<5; i++){
                if(!((senh[i]>=65 && senh[i]<=90)||(senh[i]>=97 && senh[i]<=122)||(senh[i]>=48 && senh[i]<=57)|| senh[i]==33 || senh[i]==44 || senh[i]==46 ||senh[i]==59 || senh[i]==63)){
                    return true;

                }
                if(senh[i]>=65 && senh[i]<=90){maiuscula = maiuscula+1;}
                if(senh[i]>=97 && senh[i]<=122){minuscula = minuscula+1;}
                if(senh[i]>=48 && senh[i]<=57){digito = digito+1;}
                if(senh[i]==33 || senh[i]==44 || senh[i]==46 ||senh[i]==59 || senh[i]==63){pont=pont+1;}
            }
            if(maiuscula==0 || minuscula==0 || digito==0 || pont==0){return true;}
            return false;

    }else{
        return  true;
    }
}
void Senha::validar(string senha){
    if (valid_senha(senha))
        throw invalid_argument("Argumento invalido.");
}
void Senha::setSenha(string valor){
    validar(valor);
    this->senha = valor;
}
bool Email::valid_mail(string mail){
    int posArroba = -1;
    for (size_t i=0; i<mail.length(); i++){
        if (mail[i]==64){
            posArroba = i;
            break;
        }
    }
    if(posArroba == -1){return true;}
    if(mail[posArroba+1]==46 ||mail[posArroba-1]==46){return true;}
    string nome = mail.substr(0,posArroba);
    string dominio =mail.substr(posArroba+1);
    if(!(nome.length()>=2 && nome.length()<=10)){return true;}
    if(!(dominio.length()>=2 && dominio.length()<=20)){return true;}
    for (size_t i=0; i<nome.length(); i++){
        if(!((nome[i]>=65 && nome[i]<=90) || (nome[i]>=97 && nome[i]<=122)|| nome[i]== 46)){return true;}
        if(nome[i]==46 && nome[i-1]==46){return  true;}
    }
    for (size_t i=0; i<dominio.length(); i++){
        if(!((dominio[i]>=65 && dominio[i]<=90) || (dominio[i]>=97 && dominio[i]<=122)|| dominio[i]== 46)){return true;}
        if(dominio[i]==46 && dominio[i-1]==46){return  true;}
    }
    return false;
}
void Email::validar(string mail){
    if (valid_mail(mail))
        throw invalid_argument("Argumento invalido.");
}
void Email::setEmail(string mail){
    validar(mail);
    this->email = mail;
}

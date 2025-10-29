#ifndef ARVOREPESSOAS_H
#define ARVOREPESSOAS_H

#include "PessoaNo.h"
#include <string>

class ArvorePessoas {
private:
    No* RAIZ;

    void listarPorSexo(No* no, char sexo);
    No* inserir(No* no, std::string nome, char sexo, int idade, double peso);

public:
    ArvorePessoas();
    void inserir(std::string nome, char sexo, int idade, double peso);
    void listarHomens();
    void listarMulheres();
};

#endif
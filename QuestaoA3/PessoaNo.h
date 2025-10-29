#ifndef PESSOANO_H
#define PESSOANO_H

#include <string>
#include <cstddef> 

struct No {
    std::string nome;
    char sexo;
    int idade;
    double peso;

    No *esquerda;
    No *direita;

    No(std::string n, char s, int i, double p)
        : nome(n), sexo(s), idade(i), peso(p), esquerda(NULL), direita(NULL) {}
};

#endif
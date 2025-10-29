#ifndef NOAVL_H
#define NOAVL_H

#include <string>
#include <cstddef> 

struct No {
    std::string nome;
    char sexo;
    int idade;
    double peso;

    No *esquerda;
    No *direita;
    int altura; 

    No(std::string n, char s, int i, double p)
        : nome(n), sexo(s), idade(i), peso(p), esquerda(NULL), direita(NULL), altura(1) {} 
};

#endif
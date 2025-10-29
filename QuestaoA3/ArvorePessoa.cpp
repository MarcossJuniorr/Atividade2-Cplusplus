#include "ArvorePessoas.h"
#include <iostream>
#include <cstddef> 

ArvorePessoas::ArvorePessoas() : RAIZ(NULL) {}

No* ArvorePessoas::inserir(No* no, std::string nome, char sexo, int idade, double peso) {
    if (no == NULL) {
        return new No(nome, sexo, idade, peso);
    }

    if (nome < no->nome) {
        no->esquerda = inserir(no->esquerda, nome, sexo, idade, peso);
    } else if (nome > no->nome) {
        no->direita = inserir(no->direita, nome, sexo, idade, peso);
    }

    return no;
}

void ArvorePessoas::inserir(std::string nome, char sexo, int idade, double peso) {
    RAIZ = inserir(RAIZ, nome, sexo, idade, peso);
}

void ArvorePessoas::listarPorSexo(No* no, char sexo) {
    if (no == NULL) {
        return;
    }

    listarPorSexo(no->esquerda, sexo);

    if (no->sexo == sexo) {
        std::cout << "Nome: " << no->nome
                  << ", Idade: " << no->idade
                  << ", Peso: " << no->peso << std::endl;
    }

    listarPorSexo(no->direita, sexo);
}

void ArvorePessoas::listarHomens() {
    std::cout << "--- HOMENS (Ordenado por Nome) ---" << std::endl;
    listarPorSexo(RAIZ, 'M');
    std::cout << "------------------------------------" << std::endl;
}

void ArvorePessoas::listarMulheres() {
    std::cout << "\n--- MULHERES (Ordenado por Nome) ---" << std::endl;
    listarPorSexo(RAIZ, 'F');
    std::cout << "--------------------------------------" << std::endl;
}
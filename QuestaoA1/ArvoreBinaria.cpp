#include "ArvoreBinaria.h"
#include <iostream>
#include <iomanip>
#include <limits> 

No::No(int val) : valor(val), esquerda(NULL), direita(NULL) {}

ArvoreBinariaBusca::ArvoreBinariaBusca() : raiz(NULL) {}

ArvoreBinariaBusca::~ArvoreBinariaBusca() {
    destruirArvore(raiz);
}

void ArvoreBinariaBusca::destruirArvore(No *no) {
    if (no) {
        destruirArvore(no->esquerda);
        destruirArvore(no->direita);
        delete no;
    }
}


bool ArvoreBinariaBusca::inserir(int valor) {
    if (buscar(raiz, valor)) { 
        return false; 
    }
    raiz = inserir(raiz, valor); 
    return true; 
}

No* ArvoreBinariaBusca::inserir(No *no, int valor) {
    if (no == NULL) {
        return new No(valor);
    }

    if (valor < no->valor) {
        no->esquerda = inserir(no->esquerda, valor);
    }
    else if (valor > no->valor) {
        no->direita = inserir(no->direita, valor);
    }
    
    return no;
}


bool ArvoreBinariaBusca::buscar(int valor) {
    return buscar(raiz, valor);
}

bool ArvoreBinariaBusca::buscar(No* no, int valor) {
    if (no == NULL) {
        return false; 
    }
    if (valor == no->valor) {
        return true; 
    }
    if (valor < no->valor) {
        return buscar(no->esquerda, valor);
    } else {
        return buscar(no->direita, valor);
    }
}



void ArvoreBinariaBusca::remover(int valor) {
    raiz = remover(raiz, valor);
}

No* ArvoreBinariaBusca::encontrarMenor(No *no) {
    No *atual = no;
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

No* ArvoreBinariaBusca::remover(No *no, int valor) {
    if (no == NULL) {
        return no; 
    }

    if (valor < no->valor) {
        no->esquerda = remover(no->esquerda, valor);
    } else if (valor > no->valor) {
        no->direita = remover(no->direita, valor);
    }
    else {
        if (no->esquerda == NULL) {
            No *temp = no->direita;
            delete no;
            return temp;
        } else if (no->direita == NULL) {
            No *temp = no->esquerda;
            delete no;
            return temp;
        }

        No *temp = encontrarMenor(no->direita);
        no->valor = temp->valor;
        no->direita = remover(no->direita, temp->valor);
    }
    return no;
}

void ArvoreBinariaBusca::listarEmOrdem() {
    std::cout << "Listagem (Em-Ordem): ";
    listarEmOrdem(raiz);
    std::cout << std::endl;
}

void ArvoreBinariaBusca::listarEmOrdem(No *no) {
    if (no != NULL) {
        listarEmOrdem(no->esquerda);
        std::cout << no->valor << " ";
        listarEmOrdem(no->direita);
    }
}

void ArvoreBinariaBusca::imprimirArvore() {
    std::cout << "----------------------------------------\n";
    imprimirArvore(raiz, 0);
    std::cout << "----------------------------------------\n";
}

void ArvoreBinariaBusca::imprimirArvore(No *no, int espaco) {
    if (no == NULL) {
        return;
    }
    int COUNT = 5; 
    espaco += COUNT;

    imprimirArvore(no->direita, espaco);

    std::cout << std::endl;
    for (int i = COUNT; i < espaco; i++) {
        std::cout << " ";
    }
    std::cout << no->valor << "\n";

    imprimirArvore(no->esquerda, espaco);
}

int ArvoreBinariaBusca::getMaiorValor() {
    if (raiz == NULL) {
        std::cerr << "Erro: A arvore esta vazia!" << std::endl;
        return std::numeric_limits<int>::min(); 
    }
    No* noMaior = encontrarMaior(raiz);
    return noMaior->valor;
}

No* ArvoreBinariaBusca::encontrarMaior(No *no) {
    if (no->direita == NULL) {
        return no;
    }
    return encontrarMaior(no->direita);
}

int ArvoreBinariaBusca::ehCheia() {
    return ehCheia(raiz);
}

int ArvoreBinariaBusca::ehCheia(No* no) {
    if (no == NULL) {
        return 1;
    }

    if (no->esquerda == NULL && no->direita == NULL) {
        return 1;
    }

  
    if ((no->esquerda == NULL) != (no->direita == NULL)) {
        return 0; 
    }
    return ehCheia(no->esquerda) && ehCheia(no->direita);
}
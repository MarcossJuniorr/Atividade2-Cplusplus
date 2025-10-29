#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H

struct No {
    int valor;
    No *esquerda;
    No *direita;

    No(int val);
};

class ArvoreBinariaBusca {
private:
    No *raiz;

    No* inserir(No *no, int valor);
    No* remover(No *no, int valor);
    No* encontrarMenor(No *no);
    No* encontrarMaior(No* no);
    void listarEmOrdem(No *no);
    void imprimirArvore(No *no, int espaco = 0);
    void destruirArvore(No *no);
    bool buscar(No* no, int valor); 
    int ehCheia(No* no); 

public:
    ArvoreBinariaBusca();
    ~ArvoreBinariaBusca();

    bool inserir(int valor); 
    void remover(int valor);
    bool buscar(int valor); 
    void listarEmOrdem();
    void imprimirArvore();
    int getMaiorValor();
    int ehCheia(); 
};

#endif
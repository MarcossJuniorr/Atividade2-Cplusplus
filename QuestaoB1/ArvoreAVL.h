#ifndef ARVOREAVL_H
#define ARVOREAVL_H

#include "NoAVL.h"
#include <string>

class ArvoreAVL {
private:
    No* RAIZ;

    int altura(No* no);
    int max(int a, int b);
    int fatorBalanceamento(No* no);
    No* rotacionarDireita(No* y);
    No* rotacionarEsquerda(No* x);

    No* inserir(No* no, std::string nome, char sexo, int idade, double peso); 
    void listarTodos(No* no); 
    No* remover(No* no, std::string nome); 
    No* consultar(No* no, std::string nome); 

    void listarPorSexo(No* no, char sexo);
    No* minValorNo(No* no); 
    void destruirArvore(No* no); 

public:
    ArvoreAVL();
    ~ArvoreAVL(); 

    void inserir(std::string nome, char sexo, int idade, double peso); 
    void listarTodos(); 
    void remover(std::string nome); 
    void consultar(std::string nome); 
    
    void listarHomens();
    void listarMulheres();
};

#endif
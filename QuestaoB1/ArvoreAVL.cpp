#include "ArvoreAVL.h"
#include <iostream>
#include <cstddef> 

ArvoreAVL::ArvoreAVL() : RAIZ(NULL) {}

ArvoreAVL::~ArvoreAVL() {
    destruirArvore(RAIZ);
}

void ArvoreAVL::destruirArvore(No* no) {
    if (no != NULL) {
        destruirArvore(no->esquerda);
        destruirArvore(no->direita);
        delete no;
    }
}

int ArvoreAVL::altura(No* no) {
    if (no == NULL)
        return 0;
    return no->altura;
}

int ArvoreAVL::max(int a, int b) {
    return (a > b) ? a : b;
}

int ArvoreAVL::fatorBalanceamento(No* no) {
    if (no == NULL)
        return 0;
    return altura(no->esquerda) - altura(no->direita);
}

No* ArvoreAVL::rotacionarDireita(No* y) {
    No* x = y->esquerda;
    No* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

No* ArvoreAVL::rotacionarEsquerda(No* x) {
    No* y = x->direita;
    No* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}

void ArvoreAVL::inserir(std::string nome, char sexo, int idade, double peso) {
    RAIZ = inserir(RAIZ, nome, sexo, idade, peso);
}

No* ArvoreAVL::inserir(No* no, std::string nome, char sexo, int idade, double peso) {
    if (no == NULL) {
        return new No(nome, sexo, idade, peso);
    }

    if (nome < no->nome) {
        no->esquerda = inserir(no->esquerda, nome, sexo, idade, peso);
    } else if (nome > no->nome) {
        no->direita = inserir(no->direita, nome, sexo, idade, peso);
    } else {
        std::cout << "Erro: Pessoa com nome '" << nome << "' ja existe." << std::endl;
        return no;
    }

    no->altura = 1 + max(altura(no->esquerda), altura(no->direita));

    int fb = fatorBalanceamento(no);

    if (fb > 1 && nome < no->esquerda->nome) {
        return rotacionarDireita(no);
    }

    if (fb < -1 && nome > no->direita->nome) {
        return rotacionarEsquerda(no);
    }

    if (fb > 1 && nome > no->esquerda->nome) {
        no->esquerda = rotacionarEsquerda(no->esquerda);
        return rotacionarDireita(no);
    }

    if (fb < -1 && nome < no->direita->nome) {
        no->direita = rotacionarDireita(no);
        return rotacionarEsquerda(no);
    }

    return no;
}

void ArvoreAVL::remover(std::string nome) {
    RAIZ = remover(RAIZ, nome);
}

No* ArvoreAVL::remover(No* no, std::string nome) {
    if (no == NULL) {
        std::cout << "Erro: Pessoa '" << nome << "' nao encontrada para remocao." << std::endl;
        return no;
    }

    if (nome < no->nome) {
        no->esquerda = remover(no->esquerda, nome);
    } else if (nome > no->nome) {
        no->direita = remover(no->direita, nome);
    } else {
        std::cout << "Pessoa '" << nome << "' removida." << std::endl;
        if (no->esquerda == NULL || no->direita == NULL) {
            No* temp = no->esquerda ? no->esquerda : no->direita;

            if (temp == NULL) { 
                temp = no;
                no = NULL;
            } else { 
                *no = *temp; 
            }
            delete temp;
        } else {
            No* temp = minValorNo(no->direita); 
            no->nome = temp->nome;
            no->sexo = temp->sexo;
            no->idade = temp->idade;
            no->peso = temp->peso;
            no->direita = remover(no->direita, temp->nome);
        }
    }

    if (no == NULL) {
        return no;
    }

    no->altura = 1 + max(altura(no->esquerda), altura(no->direita));

    int fb = fatorBalanceamento(no);

    if (fb > 1 && fatorBalanceamento(no->esquerda) >= 0) {
        return rotacionarDireita(no);
    }
    if (fb > 1 && fatorBalanceamento(no->esquerda) < 0) {
        no->esquerda = rotacionarEsquerda(no->esquerda);
        return rotacionarDireita(no);
    }
    if (fb < -1 && fatorBalanceamento(no->direita) <= 0) {
        return rotacionarEsquerda(no);
    }
    if (fb < -1 && fatorBalanceamento(no->direita) > 0) {
        no->direita = rotacionarDireita(no);
        return rotacionarEsquerda(no);
    }

    return no;
}

No* ArvoreAVL::minValorNo(No* no) {
    No* current = no;
    while (current->esquerda != NULL) {
        current = current->esquerda;
    }
    return current;
}


void ArvoreAVL::consultar(std::string nome) {
    No* resultado = consultar(RAIZ, nome);
    if (resultado == NULL) {
        std::cout << "\n--- CONSULTA ---" << std::endl;
        std::cout << "Pessoa '" << nome << "' nao encontrada." << std::endl;
        std::cout << "------------------" << std::endl;
    } else {
        std::cout << "\n--- CONSULTA (Encontrado) ---" << std::endl;
        std::cout << "Nome: " << resultado->nome
                  << ", Sexo: " << resultado->sexo
                  << ", Idade: " << resultado->idade
                  << ", Peso: " << resultado->peso << std::endl;
        std::cout << "-------------------------------" << std::endl;
    }
}

No* ArvoreAVL::consultar(No* no, std::string nome) {
    if (no == NULL || no->nome == nome) {
        return no;
    }

    if (nome < no->nome) {
        return consultar(no->esquerda, nome);
    } else {
        return consultar(no->direita, nome);
    }
}


void ArvoreAVL::listarTodos() {
    std::cout << "\n--- LISTA GERAL (Ordenado por Nome) ---" << std::endl;
    if (RAIZ == NULL) {
        std::cout << "Arvore vazia." << std::endl;
    } else {
        listarTodos(RAIZ);
    }
    std::cout << "---------------------------------------" << std::endl;
}

void ArvoreAVL::listarTodos(No* no) {
    if (no != NULL) {
        listarTodos(no->esquerda); 
        std::cout << "Nome: " << no->nome
                  << ", Sexo: " << no->sexo
                  << ", Idade: " << no->idade
                  << ", Peso: " << no->peso << std::endl;
        listarTodos(no->direita);
    }
}

void ArvoreAVL::listarHomens() {
    std::cout << "\n--- HOMENS (Ordenado por Nome) ---" << std::endl;
    listarPorSexo(RAIZ, 'M');
    std::cout << "------------------------------------" << std::endl;
}

void ArvoreAVL::listarMulheres() {
    std::cout << "\n--- MULHERES (Ordenado por Nome) ---" << std::endl;
    listarPorSexo(RAIZ, 'F');
    std::cout << "--------------------------------------" << std::endl;
}

void ArvoreAVL::listarPorSexo(No* no, char sexo) {
    if (no == NULL) {
        return;
    }

    listarPorSexo(no->esquerda, sexo);

    if (no->sexo == sexo || no->sexo == (sexo + 32) || no->sexo == (sexo - 32)) { 
        std::cout << "Nome: " << no->nome
                  << ", Idade: " << no->idade
                  << ", Peso: " << no->peso << std::endl;
    }

    listarPorSexo(no->direita, sexo);
}
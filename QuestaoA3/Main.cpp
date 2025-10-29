#include <iostream>
#include <limits>
#include <cstdlib>
#include "ArvorePessoas.h"

void exibirMenu() {
    std::cout << "\n--- MENU ---" << std::endl;
    std::cout << "1. Listar Homens" << std::endl;
    std::cout << "2. Listar Mulheres" << std::endl;
    std::cout << "0. Sair" << std::endl;
    std::cout << "Escolha uma opcao: ";
}

int lerOpcao() {
    int opcao;
    while (!(std::cin >> opcao)) {
        std::cout << "Entrada invalida. Digite um numero: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return opcao;
}

int main() {
    ArvorePessoas arvore;
    int escolha;
    
    //inseridos em ordem alfabetica para ter nós apenas na direita
    arvore.inserir("Ana", 'F', 25, 60.0);
	arvore.inserir("Bruno", 'M', 45, 90.2);   
    arvore.inserir("Carlos", 'M', 30, 80.5);
    arvore.inserir("Denise", 'F', 22, 55.0);
    arvore.inserir("Eduardo", 'M', 19, 70.0);
    arvore.inserir("Fernanda", 'F', 50, 65.5);
 	arvore.inserir("Guilherme", 'M', 19, 72.93 );
    arvore.inserir("Gustavo", 'M', 18, 40.0);
    arvore.inserir("Ingride", 'F', 24, 65.0 );
	arvore.inserir("Lima", 'M', 43, 60.5);
    arvore.inserir("Macedo", 'M', 19, 67.56);
    arvore.inserir("Maria", 'F', 43, 60.0);


    while (true) {
        exibirMenu();
        escolha = lerOpcao();

        switch (escolha) {
            case 1:
            		system("cls");
                arvore.listarHomens();
                break;
            case 2:
            		system("cls");
                arvore.listarMulheres();
                break;
            case 0:
                return 0;
            default:
                std::cout << "Opcao invalida" << std::endl;
                break;
        }
    }

    return 0;
}

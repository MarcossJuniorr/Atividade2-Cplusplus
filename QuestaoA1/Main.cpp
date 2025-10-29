#include <iostream>
#include <limits> 
#include <cstdlib>
#include "ArvoreBinaria.h"

void exibirMenu() {
    std::cout << "\n--- Menu da Arvore Binaria ---" << std::endl;
    std::cout << "1. Inserir Numero" << std::endl;
    std::cout << "2. Remover Numero " << std::endl;
    std::cout << "3. Mostrar Arvore " << std::endl;
    std::cout << "4. Encontrar Maior Valor" << std::endl;
    std::cout << "5. Verificar se esta cheia" << std::endl; 
    std::cout << "0. Sair" << std::endl;
    std::cout << "Escolha uma opcao: ";
}

int lerNumero() {
    int valor;
    while (!(std::cin >> valor)) {
        std::cout << "Entrada invalida. digite um numero: ";
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    }
    return valor;
}

int main() {
    ArvoreBinariaBusca arvore;
    int escolha;
    int valor;
    arvore.inserir(20);
    arvore.inserir(5);
    arvore.inserir(12);
	arvore.inserir(36);
    arvore.inserir(27);
    arvore.inserir(45);
    arvore.inserir(9);
    arvore.inserir(2);
    arvore.inserir(6);
    arvore.inserir(17);
    arvore.inserir(40);
    

    while (true) {
        exibirMenu();
        escolha = lerNumero();

        switch (escolha) {
            case 1: 
                std::cout << "Digite o numero para INSERIR: ";
                valor = lerNumero();
                
              
                if (arvore.inserir(valor)) {
                	system("cls");
                    std::cout << "Numero " << valor << " inserido." << std::endl;
                } else {
                    std::cout << "Numero " << valor << " ja existe. Nao foi inserido." << std::endl;
                }
  
                break;

            case 2:
                std::cout << "Digite o numero para REMOVER: ";
                valor = lerNumero();
                arvore.remover(valor);
                	system("cls");
                std::cout << "Numero " << valor << " removido." << std::endl;
                break;

            case 3: 
           std::cout << "Visualizacao da Arvore:" << std::endl;
           	system("cls");
                arvore.imprimirArvore();
                break;

            case 4: 
            	         { 
                    int maior = arvore.getMaiorValor();
                    if (maior != std::numeric_limits<int>::min()) {
                    		system("cls");
                        std::cout << "O MAIOR valor na arvore e: " << maior << std::endl;
                    }
                }
       
                break;
            
            case 5:
                {
                    if (arvore.ehCheia() == 1) {
                    		system("cls");
                        std::cout << "A arvore ESTA CHEIA ." << std::endl;
                    } else {
                    		system("cls");
                        std::cout << "A arvore NAO ESTA CHEIA ." << std::endl;
                    }
                }
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

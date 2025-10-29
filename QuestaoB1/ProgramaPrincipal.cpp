#include <iostream>
#include <limits>
#include <string>
#include <cstdlib>
#include "ArvoreAVL.h"

void limparBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int lerInteiro(const std::string& prompt) {
    int valor;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valor) {
            if (valor >= 0) {
                limparBuffer();
                return valor;
            } else {
                std::cout << "Entrada invalida. Digite um numero positivo." << std::endl;
            }
        } else {
            std::cout << "Entrada invalida. Digite um numero." << std::endl;
            std::cin.clear();
            limparBuffer();
        }
    }
}

double lerDouble(const std::string& prompt) {
    double valor;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valor) {
             if (valor >= 0) {
                limparBuffer();
                return valor;
            } else {
                std::cout << "Entrada invalida. Digite um numero positivo." << std::endl;
            }
        } else {
            std::cout << "Entrada invalida. Digite um numero." << std::endl;
            std::cin.clear();
            limparBuffer();
        }
    }
}

char lerSexo(const std::string& prompt) {
    char valor;
    while (true) {
        std::cout << prompt;
        std::cin >> valor;
        valor = toupper(valor); 
        if (valor == 'M' || valor == 'F') {
            limparBuffer();
            return valor;
        } else {
            std::cout << "Entrada invalida. Digite 'M' ou 'F'." << std::endl;
            std::cin.clear();
            limparBuffer();
        }
    }
}

void exibirMenu() {
    std::cout << "\n--- MENU ARVORE AVL DE PESSOAS ---" << std::endl;
    std::cout << "1. Inserir Pessoa" << std::endl;
    std::cout << "2. Remover Pessoa (por nome)" << std::endl;
    std::cout << "3. Consultar Pessoa (por nome)" << std::endl;
    std::cout << "4. Listar Todas as Pessoas" << std::endl;
    std::cout << "5. Listar Apenas Homens" << std::endl;
    std::cout << "6. Listar Apenas Mulheres" << std::endl;
    std::cout << "0. Sair" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Escolha uma opcao: ";
}

void inserirPessoa(ArvoreAVL &arvore) {
    std::string nome;
    char sexo;
    int idade;
    double peso;

    std::cout << "\n--- Inserir Pessoa ---" << std::endl;
    std::cout << "Nome: ";
    std::getline(std::cin, nome); 

    sexo = lerSexo("Sexo (M/F): ");
    idade = lerInteiro("Idade: ");
    peso = lerDouble("Peso (kg): ");
    system("cls");

    arvore.inserir(nome, sexo, idade, peso);
}

void removerPessoa(ArvoreAVL &arvore) {
    std::string nome;
    std::cout << "\n--- Remover Pessoa ---" << std::endl;
    std::cout << "Digite o nome da pessoa a ser removida: ";
    std::getline(std::cin, nome);
    arvore.remover(nome);
}

void consultarPessoa(ArvoreAVL &arvore) {
    std::string nome;
    std::cout << "\n--- Consultar Pessoa ---" << std::endl;
    std::cout << "Digite o nome da pessoa a ser consultada: ";
    std::getline(std::cin, nome);
    arvore.consultar(nome);
}


int main() {
    ArvoreAVL arvore;
    int escolha;

    arvore.inserir("Carlos", 'M', 30, 80.5);
    arvore.inserir("Ana", 'F', 25, 60.0);
    arvore.inserir("Bruno", 'M', 45, 90.2);
    arvore.inserir("Denise", 'F', 22, 55.0);
    arvore.inserir("Eduardo", 'M', 19, 70.0);
    arvore.inserir("Fernanda", 'F', 50, 65.5);
    arvore.inserir("Lima", 'M', 43, 60.5);
    arvore.inserir("Gustavo", 'M', 18, 40.0);
    arvore.inserir("Macedo", 'M', 19, 67.56);
    arvore.inserir("Guilherme", 'M', 19, 72.93 );
	arvore.inserir("Ingride", 'F', 24, 65.0 );
	arvore.inserir("Maria", 'F', 43, 60.0);

    while (true) {
        exibirMenu();
        escolha = lerInteiro(""); 

        switch (escolha) {
            case 1:
            	system("cls");
                inserirPessoa(arvore);
                break;
            case 2:
            	system("cls");
                removerPessoa(arvore);
                break;
            case 3:
            	system("cls");
                consultarPessoa(arvore);
                break;
            case 4:
            	system("cls");
                arvore.listarTodos();
                break;
            case 5:
            	system("cls");
                arvore.listarHomens();
                break;
            case 6:
            	system("cls");
                arvore.listarMulheres();
                break;
            case 0:
                system("cls");
                return 0;
            default:
            	system("cls");
                std::cout << "Opcao invalida" << std::endl;
                break;
        }
    }

    return 0;
}

#include <iostream>
#include <fstream>
#include <climits>
#include <string>
#include <vector>

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR_SCREEN "cls"
#else
    #include <cstdlib>
    #define CLEAR_SCREEN "clear"
#endif

#define vertex int
#define INF INT_MAX

using namespace std;

void limparTela() {
    system(CLEAR_SCREEN);
}

void voltarMenu() {
    cout << "\nPressione Enter para voltar ao menu...";
    cin.ignore();
    cin.get();
    limparTela();
}

class Graph {
private:
    int V;
    int A;

public:
    int **adj;
    int **dist; 
    int *grau; 

    Graph(int V) {
        this->V = V;
        this->A = 0;
        
        adj = new int*[V];
        for (int i = 0; i < V; i++) {
            adj[i] = new int[V];
            for (int j = 0; j < V; j++) {
                adj[i][j] = 0;
            }
        }
        
   
        dist = new int*[V];
        for (int i = 0; i < V; i++) {
            dist[i] = new int[V];
            for (int j = 0; j < V; j++) {
                if (i == j)
                    dist[i][j] = 0;
                else
                    dist[i][j] = INF;
            }
        }
        
    
        grau = new int[V];
        for (int i = 0; i < V; i++) {
            grau[i] = 0;
        }
    }

    ~Graph() {
        for (int i = 0; i < V; i++) {
            delete[] adj[i];
            delete[] dist[i];
        }
        delete[] adj;
        delete[] dist;
        delete[] grau;
    }

    void inserirArco(vertex u, vertex v) {
        if (u >= V || v >= V) {
            cout << "Vertice invalido! Vertices devem estar entre 0 e " << V-1 << endl;
            return;
        }
        if (adj[u][v] == 0) {
            adj[u][v] = 1;
            dist[u][v] = 1;
            grau[u]++;
            A++;
            cout << "Arco (" << u << " -> " << v << ") inserido com sucesso!" << endl;
        } else {
            cout << "Arco (" << u << " -> " << v << ") ja existe!" << endl;
        }
    }


    void removerArco(vertex u, vertex v) {
        if (u >= V || v >= V) {
            cout << "Vertice invalido! Vertices devem estar entre 0 e " << V-1 << endl;
            return;
        }
        if (adj[u][v] == 1) {
            adj[u][v] = 0;
            dist[u][v] = INF;
            grau[u]--;
            A--;
            cout << "Arco (" << u << " -> " << v << ") removido com sucesso!" << endl;
        } else {
            cout << "Arco (" << u << " -> " << v << ") nao existe!" << endl;
        }
    }


    void listarGrafo() {
        cout << "\n=== LISTA DE ADJACENCIAS ===" << endl;
        for (int i = 0; i < V; i++) {
            cout << i << " ->";
            bool temAdjacente = false;
            for (int j = 0; j < V; j++) {
                if (adj[i][j] == 1) {
                    cout << " " << j;
                    temAdjacente = true;
                }
            }
            if (!temAdjacente) {
                cout << " nenhum";
            }
            cout << endl;
        }
    }


    void exibirMatrizes() {
        cout << "\n=== MATRIZ DE ADJACENCIA ===" << endl;
        cout << "   ";
        for (int j = 0; j < V; j++) {
            cout << j << " ";
        }
        cout << endl;
        for (int i = 0; i < V; i++) {
            cout << i << ": ";
            for (int j = 0; j < V; j++) {
                cout << adj[i][j] << " ";
            }
            cout << endl;
        }
        
        cout << "\n=== MATRIZ DE DISTANCIAS ===" << endl;
        cout << "   ";
        for (int j = 0; j < V; j++) {
            cout << j << " ";
        }
        cout << endl;
        for (int i = 0; i < V; i++) {
            cout << i << ": ";
            for (int j = 0; j < V; j++) {
                if (dist[i][j] == INF)
                    cout << "9999 ";
                else
                    cout << dist[i][j] << " ";
            }
            cout << endl;
        }
    }

    void exibirGrau() {
        cout << "\n=== GRAU DOS VERTICES ===" << endl;
        for (int i = 0; i < V; i++) {
            cout << "Vertice " << i << ": grau " << grau[i] << endl;
        }
    }

    void exibirInformacoes() {
        cout << "\n=== INFORMAÇÕES DO GRAFO ===" << endl;
        cout << "Numero de vertices: " << V << endl;
        cout << "Numero de arcos: " << A << endl;
    }

    void lerGrafo(const string& nomeArquivo) {
        ifstream arquivo("grafo.txt");
        if (!arquivo.is_open()) {
            cout << "Erro ao abrir o arquivo " << nomeArquivo << "!" << endl;
            return;
        }

        int u, v;
        int count = 0;
        while (arquivo >> u >> v) {
            if (u >= V || v >= V) {
                cout << "Aviso: Arco (" << u << " -> " << v << ") ignorado - vertice invalido!" << endl;
                continue;
            }
            if (adj[u][v] == 0) {
                adj[u][v] = 1;
                dist[u][v] = 1;
                grau[u]++;
                A++;
                count++;
            }
        }
        arquivo.close();
        cout << count << " arcos carregados do arquivo " << nomeArquivo << "!" << endl;
    }


    void floydWarshall() {
        if (V == 0) {
            cout << "Grafo vazio! Carregue um arquivo primeiro." << endl;
            return;
        }

        int **caminhosMinimos = new int*[V];
        for (int i = 0; i < V; i++) {
            caminhosMinimos[i] = new int[V];
            for (int j = 0; j < V; j++) {
                caminhosMinimos[i][j] = dist[i][j];
            }
        }

        // Algoritmo de Floyd-Warshall
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    // Evita overflow
                    if (caminhosMinimos[i][k] != INF && 
                        caminhosMinimos[k][j] != INF &&
                        caminhosMinimos[i][k] + caminhosMinimos[k][j] < caminhosMinimos[i][j]) {
                        caminhosMinimos[i][j] = caminhosMinimos[i][k] + caminhosMinimos[k][j];
                    }
                }
            }
        }

        cout << "\n=== MATRIZ DE CAMINHOS MINIMOS (FLOYD-WARSHALL) ===" << endl;
        cout << "   ";
        for (int j = 0; j < V; j++) {
            cout << j << "     ";
        }
        cout << endl;
        
        for (int i = 0; i < V; i++) {
            cout << i << ": ";
            for (int j = 0; j < V; j++) {
                if (caminhosMinimos[i][j] == INF) {
                    cout << "INF   ";
                } else {
                    if (caminhosMinimos[i][j] < 10) {
                        cout << caminhosMinimos[i][j] << "     ";
                    } else if (caminhosMinimos[i][j] < 100) {
                        cout << caminhosMinimos[i][j] << "    ";
                    } else {
                        cout << caminhosMinimos[i][j] << "   ";
                    }
                }
            }
            cout << endl;
        }

        cout << "\n=== INTERPRETACAO DOS CAMINHOS MINIMOS ===" << endl;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (i != j) {
                    if (caminhosMinimos[i][j] == INF) {
                        cout << "Nao existe caminho de " << i << " para " << j << endl;
                    } else {
                        cout << "Caminho minimo de " << i << " para " << j << ": " 
                             << caminhosMinimos[i][j] << " aresta(s)" << endl;
                    }
                }
            }
        }

        for (int i = 0; i < V; i++) {
            delete[] caminhosMinimos[i];
        }
        delete[] caminhosMinimos;
    }

    void buscarCaminhoMinimo() {
        if (V == 0) {
            cout << "Grafo vazio! Carregue um arquivo primeiro." << endl;
            return;
        }

        int origem, destino;
        cout << "Digite o vertice de origem (0 a " << V-1 << "): ";
        cin >> origem;
        cout << "Digite o vertice de destino (0 a " << V-1 << "): ";
        cin >> destino;

        if (origem < 0 || origem >= V || destino < 0 || destino >= V) {
            cout << "Vertices invalidos!" << endl;
            return;
        }


        int **caminhosMinimos = new int*[V];
        for (int i = 0; i < V; i++) {
            caminhosMinimos[i] = new int[V];
            for (int j = 0; j < V; j++) {
                caminhosMinimos[i][j] = dist[i][j];
            }
        }

        // Algoritmo de Floyd-Warshall
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (caminhosMinimos[i][k] != INF && 
                        caminhosMinimos[k][j] != INF &&
                        caminhosMinimos[i][k] + caminhosMinimos[k][j] < caminhosMinimos[i][j]) {
                        caminhosMinimos[i][j] = caminhosMinimos[i][k] + caminhosMinimos[k][j];
                    }
                }
            }
        }


        cout << "\n=== CAMINHO MiNIMO ENTRE " << origem << " E " << destino << " ===" << endl;
        if (caminhosMinimos[origem][destino] == INF) {
            cout << "Nao existe caminho de " << origem << " para " << destino << endl;
        } else {
            cout << "Distancia minima: " << caminhosMinimos[origem][destino] << " aresta(s)" << endl;
        }

        for (int i = 0; i < V; i++) {
            delete[] caminhosMinimos[i];
        }
        delete[] caminhosMinimos;
    }
};

void criarArquivoExemplo() {
    ofstream arquivo("grafo.txt");
    if (arquivo.is_open()) {
        arquivo << "0 1" << endl;
        arquivo << "0 2" << endl;
        arquivo << "1 2" << endl;
        arquivo << "1 3" << endl;
        arquivo << "2 3" << endl;
        arquivo << "3 0" << endl;
        arquivo.close();
        cout << "Arquivo grafo.txt criado com sucesso!" << endl;
    } else {
        cout << "Erro ao criar arquivo!" << endl;
    }
}


void exibirMenu() {
    cout << "\n========== MENU DO GRAFO ==========" << endl;
    cout << "1. Listar grafo (lista de adjacencias)" << endl;
    cout << "2. Exibir matrizes" << endl;
    cout << "3. Exibir graus dos vertices" << endl;
    cout << "4. Exibir informacoes do grafo" << endl;
    cout << "5. Inserir arco" << endl;
    cout << "6. Remover arco" << endl;
    cout << "7. Carregar grafo de arquivo" << endl;
    cout << "8. Criar arquivo de exemplo" << endl;
    cout << "9. Floyd-Warshall - Todos os caminhos minimos" << endl;
    cout << "10. Buscar caminho minimo entre dois vertices" << endl;
    cout << "0. Sair" << endl;
    cout << "====================================" << endl;
    cout << "Escolha uma opcao: ";
}

int main() {
    limparTela();
    
    int numVertices = 4;
    Graph g(numVertices);
    

    ifstream teste("grafo.txt");
    if (teste.is_open()) {
        cout << "=== SISTEMA DE GERENCIAMENTO DE GRAFOS ===" << endl;
        cout << "Arquivo grafo.txt encontrado! Carregando..." << endl;
        g.lerGrafo("grafo.txt");
        teste.close();
    } else {
        cout << "=== SISTEMA DE GERENCIAMENTO DE GRAFOS ===" << endl;
        cout << "Arquivo grafo.txt nao encontrado." << endl;
        cout << "Use a opcao 8 para criar um arquivo de exemplo." << endl;
    }
    
    voltarMenu();
    
    int opcao;
    do {
        exibirMenu();
        cin >> opcao;
        
        limparTela();
        cout << "=== SISTEMA DE GERENCIAMENTO DE GRAFOS ===" << endl;
        
        switch (opcao) {
            case 1:
                cout << "OPCAO 1 - LISTA DE ADJACENCIAS" << endl;
                g.listarGrafo();
                voltarMenu();
                break;
                
            case 2:
                cout << "OPCAO 2 - MATRIZES DE REPRESENTACAO" << endl;
                g.exibirMatrizes();
                voltarMenu();
                break;
                
            case 3:
                cout << "OPCAO 3 - GRAU DOS VERTICES" << endl;
                g.exibirGrau();
                voltarMenu();
                break;
                
            case 4:
                cout << "OPCAO 4 - INFORMACOES DO GRAFO" << endl;
                g.exibirInformacoes();
                voltarMenu();
                break;
                
            case 5: {
                cout << "OPCAO 5 - INSERIR ARCO" << endl;
                int u, v;
                cout << "Digite o vertice de origem (0 a " << numVertices-1 << "): ";
                cin >> u;
                cout << "Digite o vertice de destino (0 a " << numVertices-1 << "): ";
                cin >> v;
                g.inserirArco(u, v);
                voltarMenu();
                break;
            }
                
            case 6: {
                cout << "OPCAO 6 - REMOVER ARCO" << endl;
                int u, v;
                cout << "Digite o vertice de origem (0 a " << numVertices-1 << "): ";
                cin >> u;
                cout << "Digite o vertice de destino (0 a " << numVertices-1 << "): ";
                cin >> v;
                g.removerArco(u, v);
                voltarMenu();
                break;
            }
                
            case 7: {
                cout << "OPCAO 7 - CARREGAR GRAFO DE ARQUIVO" << endl;
                string nomeArquivo;
                cout << "Digite o nome do arquivo: ";
                cin >> nomeArquivo;
                g.lerGrafo(nomeArquivo);
                voltarMenu();
                break;
            }
                
            case 8:
                cout << "OPCAO 8 - CRIAR ARQUIVO DE EXEMPLO" << endl;
                criarArquivoExemplo();
                voltarMenu();
                break;

            case 9:
                cout << "OPCAO 9 - FLOYD-WARSHALL (TODOS OS CAMINHOS MINIMOS)" << endl;
                g.floydWarshall();
                voltarMenu();
                break;

            case 10:
                cout << "OPCAO 10 - BUSCAR CAMINHO MINIMO ENTRE DOIS VERTICES" << endl;
                g.buscarCaminhoMinimo();
                voltarMenu();
                break;
                
            case 0:
                cout << "Saindo do programa..." << endl;
                break;
                
            default:
                cout << "Opcao invalida! Tente novamente." << endl;
                voltarMenu();
                break;
        }
        
    } while (opcao != 0);
    
    return 0;
}


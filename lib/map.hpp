#pragma once

#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

using std::istream;
using std::map;
using std::ostream;
using std::pair;
using std::queue;
using std::set;
using std::vector;

/// @brief Classe usada para armazenar posição de elemento e distância para BFS
struct Cell {
    // Construtores

    // @brief atribui os membros (x,y,d) a uma célula
    Cell(const int &x, const int &y, const int &d) : row(x), col(y), dist(d) {}

    int row;
    int col;
    int dist;
};

/// @brief Classe usada para representar o "mapa" da orla
class Map {
  public:
    // Construtores

    /// @brief Aloca memória para um mapa de dimensões n x m
    /// @param n, número de linhas do mapa
    /// @param m, número de colunas do mapa
    /// @param _istream, arquivo de entrada
    /// @param _ostream, arquivo de saída
    Map(const int &n, const int &m, istream &_istream = std::cin,
        ostream &_ostream = std::cout);

    // Operações

    /// @brief Lê o mapa, caractere a caractere
    /// @return Número de visitantes que foram contados no mapa
    int read();

    /// @brief Escreve o mapa, caractere a caractere para a saída outStream
    void print() const;

    // Getters

    /// @brief Retorne as bicicletas (números) do mapa
    /// @return Mapa de bicicleta para sua posição
    map<char, pair<int, int>> getBikes() const { return this->digitsPositions; }

    /// @brief Retorne a matriz que representa o mapa
    /// @return Matriz que representa o mapa
    vector<vector<char>> getMap() const { return this->charMap; }

    /// @brief Calcula a distância de cada bicicleta para todos os visitantes
    /// @return Matriz com distâncias: linha -> bicicleta, coluna -> visitante
    vector<vector<int>> getDistances();

    // Lookup

    /// @brief Verifica se a célcula na posição (row,col) é válida
    /// @param visited, matriz de posições visitadas
    /// @param row, linha da célula
    /// @param col, ooluna da célula
    /// @return inválido se proibido, fora do mapa ou visitado
    bool isValid(const vector<vector<bool>> &visited, const int &row,
                 const int &col) const;

  private:
    static constexpr char PROHIBITED = '-';

    // Letras únicas em conformidade com a especificação
    int V = 0; // Número de visitantes
    int N;     // Linhas
    int M;     // Colunas

    vector<vector<char>> charMap;

    istream &inStream;
    ostream &outStream;

    map<char, pair<int, int>> digitsPositions; // Bicicletas

    // Pesquisa

    /// @brief Começando de uma posição (row,col) encontre as distâncias para
    /// todas as letras (visitantes)
    /// @param row, linha inicial
    /// @param col, ooluna inicial
    /// @return Vetor com as distâncias de cada letra, tal que 'a' -> 0, etc
    vector<int> BFS(const int &row, const int &col) const;

    // Ajudantes

    /// @brief Pesquisa os vizinhos de uma dada célula na execução da BFS
    /// @param visited, matriz de posições visitadas
    /// @param queue, fila que controla a execução da BFS
    /// @param cell, célula cujos cizinhos serão buscados
    void BFSHelper(vector<vector<bool>> &visited, queue<Cell> &queue,
                   const Cell &cell) const;
};

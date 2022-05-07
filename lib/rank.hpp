#pragma once

#include <algorithm> // std::stable_sort
#include <numeric>   // std::iota
#include <vector>

using std::pair;
using std::vector;

/// @brief Agrupa métodos relacionados ao "rankeamento" de listas de
/// preferências
struct Rank {

    /// @brief Ordena os índices de um vetor com base na ordenação do vetor
    /// @param v, vetor a ser ordenado
    /// @param isScore, define como a ordem funciona:
    /// isScore = true  -> ordem decrescente, com desempate pelo menor índice
    /// isScore = false -> ordem crescente, com desempate pelo menor índice
    /// @return vetor tal que a i-ésima posição corresponde ao índice do vetor
    /// original, se ele fosse ordenado
    ///
    /// Exemplo: v = {5, 2, 1, 5, 3}, isScore = true => {0, 3, 4, 1, 2}
    vector<int> static sortIndexes(const vector<int> &v, const bool &isScore);

    /// @brief Construa uma lista de preferências com base nos índices dos
    /// scores ordenados
    /// @param scores, matriz que mapeia a "pontuação" (eg, beleza) de cada
    /// elemento A (eg, homens) para todo elemento do tipo B (eg, mulheres)
    /// @param list, lista que recebe a matriz com os índices
    /// @param reverse, define se a pontuação é descrescente (true) ou crescente
    /// (false)
    static void setPreferenceList(const vector<vector<int>> &scores,
                                  vector<vector<int>> &list,
                                  const bool &reverse);
};

// @brief Ordene comparando apenas o primeiro elemento
// @param lhs, par à esquerda
// @param rhs, par à direita
// @return true se o primeiro elemento de lhs é menor que o de rhs
inline bool comparator(const pair<int, int> &lhs, const pair<int, int> &rhs) {
    return lhs.first < rhs.first;
};

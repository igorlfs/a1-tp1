#pragma once

#include <algorithm> // std::stable_sort
#include <numeric>   // std::iota
#include <vector>

using std::vector;

/// @brief Agrupa métodos relacionados ao "rankeamento" de listas de
/// preferências
struct Rank {

    /// @brief Ordena os índices de um vetor com base na ordenação do vetor
    /// @param v, vetor a ser ordenado
    /// @param reverse, define se a ordem é crescente (false) ou decrescente
    /// (true)
    /// @return vetor com os índices ordenados
    vector<int> static sortIndexes(const vector<int> &v, const bool &reverse);

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

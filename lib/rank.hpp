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
    template <typename T>
    vector<int> static sortIndexes(const vector<T> &v, const bool &reverse) {
        // Função implementada no header porque usar templates é chato
        // Referẽncia: https://stackoverflow.com/a/10632266
        vector<int> sortedIndexes(v.size());

        // Cria uma sequência incremental (ie, 0, 1, 2, ...) no array
        iota(sortedIndexes.begin(), sortedIndexes.end(), 0);

        // Use lambdas para comparar os elementos do vetor original
        if (reverse) {
            const auto COMPARATOR = [&v](const int &a, const int &b) {
                return v.at(a) > v.at(b);
            };
            stable_sort(sortedIndexes.begin(), sortedIndexes.end(), COMPARATOR);
        } else {
            const auto COMPARATOR = [&v](const int &a, const int &b) {
                return v.at(a) < v.at(b);
            };
            stable_sort(sortedIndexes.begin(), sortedIndexes.end(), COMPARATOR);
        }

        return sortedIndexes;
    };

    /// @brief Construa uma lista de preferências com base nos índices dos
    /// scores ordenados
    /// @param scores, matriz que mapeia a "pontuação" (eg, beleza) de cada
    /// elemento A (eg, homens) para todo elemento do tipo B (eg, mulheres)
    /// @param list, lista que recebe a matriz com os índices
    /// @param reverse, define se a pontuação é descrescente (true) ou crescente
    /// (false)
    static void setPreferenceList(vector<vector<int>> &scores,
                                  vector<vector<int>> &list,
                                  const bool &reverse);
};

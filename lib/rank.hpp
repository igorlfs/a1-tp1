#pragma once

#include <algorithm> // std::stable_sort
#include <numeric>   // std::iota
#include <vector>

using std::pair;
using std::vector;
using matrix = vector<vector<int>>;

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
    /// elemento do tipo A (eg, homens) para todo elemento do tipo B (eg,
    /// mulheres)
    /// @param isScore, define como as listas devem ser ordenadas
    /// @return matriz, lista de preferência dos A's
    static matrix setPreferenceList(const matrix &scores, const bool &isScore);

    /// @brief Cria um casamento estável a partir de duas listas de preferências
    /// @param manPref, lista de preferências do lado proponente
    /// @param womanPref, lista de preferências do lado que recebe propostas
    /// @return vetor com o casamento, indexado pelo lado que recebe propostas
    ///
    /// Exemplo: manPref = {{1,0}, {1,0}}, womanPref = {{0,1}, {0,1}} => {1, 0}
    /// (mulher 0 fica com o homem 1 e mulher 1 fica com o homem 0)
    static vector<int> galeShapley(const matrix &manPref,
                                   const matrix &womanPref);
};

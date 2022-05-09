#pragma once

#include <iostream>
#include <vector>

using std::istream;
using std::vector;

using matrix = vector<vector<int>>;

class Input {
  public:
    /// @brief leia as pontuações que cada visitante deu pra cada bicicleta
    /// @param _istream, arquivo de entrada
    /// @return matriz com as pontuações atribuídas
    matrix static readScores(istream &_istream = std::cin);

    /// @brief lê e garante que os parâmetros estão corretos
    /// @param _istream, arquivo de entrada
    void static readParameters(istream &_istream = std::cin);
};

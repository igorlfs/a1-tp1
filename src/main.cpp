#include "input.hpp"
#include "map.hpp"
#include "msgassert.hpp"
#include "rank.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::vector;

using matrix = vector<vector<int>>;

int visitors;
int mapRows;
int mapCols;

/// @brief executa o programa principal
int main() {
    // Lê número de visitantes e dimensões do mapa
    Input::readParameters();

    // Leitura do mapa
    Map regionMap(mapRows, mapCols);
    const int V = regionMap.read();
    assert(V == visitors, "O número de visitantes no mapa ("
                              << V << ") não é igual ao passado na entrada ("
                              << visitors << ")\n");

    // Cria "listas de preferências" das bicicletas com base na distância aos
    // visitantes
    const matrix DISTANCES = regionMap.getDistances();
    const matrix LIST_BIKES = Rank::setPreferenceList(DISTANCES, false);

    // Ordena as pontuações dos visitantes para que se comportem como listas de
    // preferências
    const matrix SCORES = Input::readScores();
    const matrix LIST_VISITORS = Rank::setPreferenceList(SCORES, true);

    // Com as listas em mãos, rode o GS para encontrar um casamento estável
    const vector<int> STABLE_MATCHES =
        Rank::galeShapley(LIST_BIKES, LIST_VISITORS);

    // Imprime saída
    for (uint i = 0; i < STABLE_MATCHES.size(); ++i) {
        cout << (char)(i + 'a') << ' ' << STABLE_MATCHES[i] << endl;
    }

    return 0;
}

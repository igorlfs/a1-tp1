#include "map.hpp"
#include "msgassert.hpp"
#include "rank.hpp"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

using matrix = vector<vector<int>>;

/// @brief leia as pontuações que cada visitante deu pra cada bicicleta
/// @param size, quantidade de visitantes
/// @return matriz com as pontuações atribuídas
vector<vector<int>> readScores(const int &size) {
    vector<vector<int>> scores(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int c;
            cin >> c;
            scores.at(i).push_back(c);
        }
    }
    return scores;
}

/// @brief executa o programa principal
int main() {
    // Leitura de parâmetros
    int visitors;
    int mapRows;
    int mapCols;
    cin >> visitors >> mapRows >> mapCols;

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
    const matrix SCORES = readScores(visitors);
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

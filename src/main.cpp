#include "map.hpp"
#include "msgassert.hpp"
#include "rank.hpp"
#include <iostream>

using std::cin;
using std::vector;

/// @brief leia as pontuações que cada visitante deu pra cada bicicleta
/// @param size, quantidade de visitantes
/// @return matriz com as pontuações atribuídas
vector<vector<int>> readScores(const int &size) {
    vector<vector<int>> scores(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            char c;
            cin >> c;
            scores.at(i).push_back(c);
        }
    }
    return scores;
}

/// @brief executa o programa principal
int main() {
    int visitors;
    int mapRows;
    int mapCols;
    cin >> visitors >> mapRows >> mapCols;

    Map regionMap(mapRows, mapCols);
    const int V = regionMap.read();
    assert(V == visitors, "O número de visitantes no mapa ("
                              << V << ") não é igual ao passado na entrada ("
                              << visitors << ")\n");

    vector<vector<int>> distances = regionMap.getDistancesBikesToVisitors();
    vector<vector<int>> prefListBikes(visitors);
    Rank::setPreferenceList(distances, prefListBikes, false);

    vector<vector<int>> bikeScores = readScores(visitors);
    vector<vector<int>> prefListVisitors(visitors);
    Rank::setPreferenceList(bikeScores, prefListVisitors, true);

    return 0;
}

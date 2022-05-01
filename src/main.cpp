#include "map.hpp"
#include "rank.hpp"
#include <iostream>

using std::cin;
using std::vector;

int v; // Visitantes (letra única em conformidade com a especificação)

/// @brief leia as pontuações que cada usuário deu pra cada bike
/// @param scores, matriz que recebe as pontuações
void readScores(vector<vector<int>> &scores) {
    for (int i = 0; i < v; ++i) {
        for (int j = 0; j < v; ++j) {
            char c;
            cin >> c;
            scores[i].push_back(c);
        }
    }
}

/// @brief executa o programa principal
int main() {
    int mapRows;
    int mapCols;
    cin >> v >> mapRows >> mapCols;

    Map regionMap(mapRows, mapCols);
    regionMap.read();

    vector<vector<int>> distances(v);
    vector<vector<int>> prefListBikes(v);
    map<char, pair<int, int>> bikes = regionMap.getBikes();
    int i = 0;
    for (const auto &bike : bikes) {
        const pair<int, int> LOCATION = bike.second;
        distances[i] = regionMap.BFS(LOCATION.first, LOCATION.second);
        i++;
    }
    Rank::setPreferenceList(distances, prefListBikes, false);

    vector<vector<int>> bikeScores(v);
    vector<vector<int>> prefListUsers(v);
    readScores(bikeScores);
    Rank::setPreferenceList(bikeScores, prefListUsers, true);

    return 0;
}

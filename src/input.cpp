#include "input.hpp"
#include "msgassert.hpp"

extern int visitors;
extern int mapRows;
extern int mapCols;

matrix Input::readScores(std::istream &_istream) {
    vector<vector<int>> scores(visitors);
    for (int i = 0; i < visitors; ++i) {
        scores.at(i).resize(visitors);
        for (int j = 0; j < visitors; ++j) {
            _istream >> scores.at(i).at(j);
        }
    }
    return scores;
}

void Input::readParameters(std::istream &_istream) {
    _istream >> visitors >> mapRows >> mapCols;

    assert(visitors > 0,
           "O número de visitantes '" << visitors << "' é negativo");
    assert(mapRows > 0, "O número de linhas '" << mapRows << "' é negativo");
    assert(mapCols > 0, "O número de colunas '" << mapCols << "' é negativo");

    // Não podem existir mais que 10 visitantes pela especificação
    static constexpr int MAX_VISITORS = 10;
    assert(visitors <= MAX_VISITORS, "O número de visitantes '"
                                         << visitors
                                         << "' é maior do que o permitido '"
                                         << MAX_VISITORS << "'");
}

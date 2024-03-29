#include "map.hpp"

#include "msgassert.hpp"
#include <array>

using std::array;

Map::Map(const int &n, const int &m, istream &_istream, ostream &_ostream)
    : N(n), M(m), inStream(_istream), outStream(_ostream) {
    this->charMap.resize(this->N);
    for (auto &it : this->charMap) {
        it.resize(this->M);
    }
}

int Map::read() {
    for (int i = 0; i < this->N; ++i) {
        for (int j = 0; j < this->M; ++j) {
            char c;
            this->inStream >> c;
            if (isdigit(c) != 0) {
                this->digitsPositions[c] = {i, j};
            } else if (isalpha(c) != 0) {
                this->V++;
            }
            this->charMap.at(i).at(j) = c;
        }
    }
    return this->V;
}

void Map::print() const {
    for (int i = 0; i < this->N; ++i) {
        for (int j = 0; j < this->M; ++j) {
            this->outStream << this->charMap.at(i).at(j);
        }
        this->outStream << std::endl;
    }
}

vector<vector<int>> Map::getDistances() {
    vector<vector<int>> distances;
    for (const auto &bike : this->digitsPositions) {
        const pair<int, int> LOCATION = bike.second;
        distances.push_back(this->BFS(LOCATION.first, LOCATION.second));
    }
    return distances;
}

vector<int> Map::BFS(const int &row, const int &col) const {
    short numVisited = 0;
    constexpr short INVALID_DISTANCE = -1;
    vector<int> distances(this->V, INVALID_DISTANCE);

    // Define a matriz de visitados
    vector<vector<bool>> visited(this->N);
    for (auto &vi : visited) {
        vi.assign(this->M, false);
    }

    // Visita a "raiz"
    queue<Cell> queue;
    queue.push({row, col, 0});
    visited.at(row).at(col) = true;

    while (!queue.empty()) {
        const Cell CELL = queue.front();
        queue.pop();

        const char C = this->charMap.at(CELL.row).at(CELL.col);
        if (isalpha(C) != 0) {
            // Converte letra para o correspondente inteiro, eg 'a' -> 0, etc
            distances.at((int)C - 'a') = CELL.dist;
            numVisited++;

            // Em algumas instâncias (mapas grandes mas com objetos próximos)
            // pode ser vantajoso (em termos de eficiência) parar a busca ao
            // encontrar a distância de todos os visitantes
            if (numVisited == this->V) {
                break;
            }
        }

        this->BFSHelper(visited, queue, CELL);
    }

    // Confere se foi possível calcular a distância para toda letra (visitante)
    for (uint i = 0; i < distances.size(); ++i) {
        assert(distances.at(i) != INVALID_DISTANCE,
               "A distância de '" << this->charMap.at(row).at(col) << "' para '"
                                  << char(i + 'a')
                                  << "' não pôde ser calculada");
    }

    return distances;
}

void Map::BFSHelper(vector<vector<bool>> &visited, queue<Cell> &queue,
                    const Cell &cell) const {
    // Arrays de deslocamento para eliminar redundâncias no código
    constexpr int DIRECTIONS = 4;
    const array<int, DIRECTIONS> D_ROWS = {-1, 0, 1, 0};
    const array<int, DIRECTIONS> D_COLS = {0, 1, 0, -1};

    for (int i = 0; i < DIRECTIONS; i++) {
        const int ADJ_X = cell.row + D_ROWS.at(i);
        const int ADJ_Y = cell.col + D_COLS.at(i);

        if (isValid(visited, ADJ_X, ADJ_Y)) {
            queue.push({ADJ_X, ADJ_Y, cell.dist + 1});
            visited.at(ADJ_X).at(ADJ_Y) = true;
        }
    }
}

bool Map::isValid(const vector<vector<bool>> &visited, const int &row,
                  const int &col) const {
    // Checagem de borda
    if (row < 0 || col < 0 || col >= this->M || row >= this->N) {
        return false;
    }

    // Checagem de proibição de caractere
    if (this->charMap.at(row).at(col) == PROHIBITED) {
        return false;
    }

    // Checagem de visita
    if (visited.at(row).at(col)) {
        return false;
    }

    return true;
}

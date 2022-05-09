#include "rank.hpp"
#include "msgassert.hpp"
#include <queue>

vector<int> Rank::sortIndexes(const vector<int> &v, const bool &isScore) {
    vector<int> index(v.size());

    // Preenche o vetor com a sequência incremental 0,1,...
    iota(index.begin(), index.end(), 0);

    // isScore = true  -> ordem decrescente, com desempate pelo menor índice
    // isScore = false -> ordem crescente, com desempate pelo menor índice
    if (isScore) {
        stable_sort(index.begin(), index.end(),
                    [&v, &index](const int &a, const int &b) {
                        return (v[a] > v[b]) ||
                               (v[a] == v[b] && index[a] < index[b]);
                    });
    } else {
        stable_sort(index.begin(), index.end(),
                    [&v, &index](const int &a, const int &b) {
                        return (v[a] < v[b]) ||
                               (v[a] == v[b] && index[a] < index[b]);
                    });
    }

    return index;
};

matrix Rank::setPreferenceList(const matrix &scores, const bool &isScore) {
    matrix list(scores.size());
    for (uint i = 0; i < scores.size(); ++i) {
        const vector<int> PREF_LIST = Rank::sortIndexes(scores.at(i), isScore);
        list.at(i) = PREF_LIST;
    }
    return list;
}

vector<int> Rank::galeShapley(const matrix &manPref, const matrix &womanPref) {
    assert(manPref.size() == womanPref.size(),
           "É necesário que as listas de preferência tenham tamanhos iguais.\n"
               << "O tamanho de manPref é " << manPref.size()
               << " e o de womanPref é " << womanPref.size() << std::endl);

    const int SIZE = manPref.size();

    // Inicializa fila com todos os "homens"
    std::queue<int> freeMen;
    for (int i = 0; i < SIZE; ++i) {
        freeMen.push(i);
    }

    // Armazena a próxima "mulher" para cada "homem"
    vector<int> next(SIZE, 0);

    // Mantém uma lista com os "maridos" atuais de cada "mulher"
    constexpr short UNENGAGED = -1;
    vector<int> current(SIZE, UNENGAGED);

    // Matriz com as posições de cada "homem" em relação a cada "mulher"
    matrix ranking(SIZE);
    for (auto &it : ranking) {
        it.resize(SIZE);
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            ranking[i][womanPref[i][j]] = j;
        }
    }

    while (!freeMen.empty()) {
        const int MAN = freeMen.front();
        const int WOMAN = manPref[MAN][next[MAN]];
        next[MAN]++;
        if (current[WOMAN] == UNENGAGED) {
            current[WOMAN] = MAN;
            freeMen.pop();
        } else if ((ranking[WOMAN][MAN] < ranking[WOMAN][current[WOMAN]])) {
            freeMen.pop();
            freeMen.push(current[WOMAN]);
            current[WOMAN] = MAN;
        }
    }

    return current;
}

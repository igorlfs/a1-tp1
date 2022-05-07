#include "rank.hpp"

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
    }
}

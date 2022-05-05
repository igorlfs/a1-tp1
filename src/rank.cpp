#include "rank.hpp"

vector<int> Rank::sortIndexes(const vector<int> &v, const bool &reverse) {
    vector<int> sortedIndexes(v.size());

    // Cria uma sequência incremental (ie, 0, 1, 2, ...) no array
    iota(sortedIndexes.begin(), sortedIndexes.end(), 0);

    // Use lambdas para comparar os elementos do vetor original
    if (reverse) {
        const auto COMPARATOR = [&v](const int &a, const int &b) {
            return v.at(a) > v.at(b);
        };
        stable_sort(sortedIndexes.begin(), sortedIndexes.end(), COMPARATOR);
    } else {
        const auto COMPARATOR = [&v](const int &a, const int &b) {
            return v.at(a) < v.at(b);
        };
        stable_sort(sortedIndexes.begin(), sortedIndexes.end(), COMPARATOR);
    }

    return sortedIndexes;
};

void Rank::setPreferenceList(const vector<vector<int>> &scores,
                             vector<vector<int>> &list, const bool &reverse) {
    for (uint i = 0; i < scores.size(); ++i) {
        const vector<int> PREF_LIST = Rank::sortIndexes(scores.at(i), reverse);
        list.at(i) = PREF_LIST;
    }
}
    }
}

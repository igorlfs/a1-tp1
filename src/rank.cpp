#include "rank.hpp"

vector<int> Rank::sortIndexes(const vector<int> &v, const bool &reverse) {
    const int SIZE = v.size();
    vector<pair<int, int>> elementsAndIndexes(SIZE);

    for (int i = 0; i < SIZE; ++i) {
        elementsAndIndexes.at(i) = {v[i], i};
    }

    stable_sort(elementsAndIndexes.begin(), elementsAndIndexes.end());

    vector<int> sortedIndexes(SIZE);
    for (int i = 0; i < SIZE; ++i) {
        sortedIndexes[i] = elementsAndIndexes[i].second;
    }

    if (reverse) {
        std::reverse(sortedIndexes.begin(), sortedIndexes.end());
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

#include "rank.hpp"

void Rank::setPreferenceList(vector<vector<int>> &scores,
                             vector<vector<int>> &list, const bool &reverse) {
    for (uint i = 0; i < scores.size(); ++i) {
        const vector<int> PREF_LIST = Rank::sortIndexes(scores.at(i), reverse);
        list.at(i) = PREF_LIST;
    }
}
    }
}

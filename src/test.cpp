#include "map.hpp"
#include "rank.hpp"
#include <gtest/gtest.h>

using namespace std;

TEST(map, readAndPrint) {
    const int NUM_VISITORS = 2;
    const vector<vector<char>> EXPECTED = {{'a', '*', '*', '0'},
                                           {'-', '-', '*', '*'},
                                           {'*', '-', '*', '*'},
                                           {'b', '*', '1', '*'}};
    const map<char, pair<int, int>> EXPECTED_BIKES{{'0', {0, 3}},
                                                   {'1', {3, 2}}};

    const string INPUT = "a**0\n--**\n*-**\nb*1*\n";
    stringstream fakeInput(INPUT);
    ostringstream fakeOutput;
    constexpr int MAP_SIZE = 4;
    Map m(MAP_SIZE, MAP_SIZE, fakeInput, fakeOutput);

    EXPECT_EQ(m.read(), NUM_VISITORS);
    m.print();
    const string ACTUAL_OUTPUT = fakeOutput.str();

    EXPECT_EQ(m.getMap(), EXPECTED);
    EXPECT_EQ(m.getBikes(), EXPECTED_BIKES);
    EXPECT_EQ(ACTUAL_OUTPUT, INPUT);
}

TEST(map, isValid) {
    const string INPUT = "a**0\n--**\n*-**\nb*1*\n";
    const vector<vector<bool>> VISITED = {{false, false, false, false},
                                          {false, true, false, false},
                                          {false, false, false, false},
                                          {false, false, false, false}};
    stringstream fakeInput(INPUT);
    constexpr int MAP_SIZE = 4;
    Map m(MAP_SIZE, MAP_SIZE, fakeInput);

    m.read();

    // Posição visitada
    EXPECT_FALSE(m.isValid(VISITED, 1, 1));
    // Caractere proibido
    EXPECT_FALSE(m.isValid(VISITED, 1, 0));
    // Fora dos limites
    EXPECT_FALSE(m.isValid(VISITED, -1, 0));
    EXPECT_FALSE(m.isValid(VISITED, 0, -1));
    EXPECT_FALSE(m.isValid(VISITED, 0, MAP_SIZE));
    EXPECT_FALSE(m.isValid(VISITED, MAP_SIZE, 0));

    EXPECT_TRUE(m.isValid(VISITED, 0, 0));
}

TEST(map, getDistances) {
    const vector<vector<int>> EXPECTED{{3, 6}, {5, 2}};

    const string INPUT = "a**0\n--**\n*-**\nb*1*\n";
    istringstream fakeInput(INPUT);
    constexpr int MAP_SIZE = 4;
    Map m(MAP_SIZE, MAP_SIZE, fakeInput);

    m.read();

    const vector<vector<int>> ACTUAL = m.getDistances();

    EXPECT_EQ(EXPECTED, ACTUAL);
    EXPECT_EQ(EXPECTED, ACTUAL);
}

TEST(map, distanceImpossibleToCalculate) {
    const string INPUT = "a-*0\n--**\n*-**\nb*1*\n";

    istringstream fakeInput(INPUT);
    constexpr int MAP_SIZE = 4;
    Map m(MAP_SIZE, MAP_SIZE, fakeInput);

    m.read();

    ASSERT_DEATH(m.getDistances(),
                 "A distância de '0' para 'a' não pôde ser calculada");
}

TEST(rank, sortScores) {
    const vector<vector<int>> INPUT = {
        {9, 4, 2, 5, 3, 3, 4, 2},  {10, 9, 10, 9, 9, 9, 9, 1},
        {8, 5, 4, 9, 3, 2, 1, 7},  {11, 3, 3, 4, 9, 8, 3, 5},
        {10, 7, 7, 7, 8, 9, 4, 9}, {1, 3, 4, 5, 3, 4, 5, 1},
        {3, 3, 2, 4, 8, 9, 1, 2},  {1, 1, 1, 1, 1, 1, 1, 1}};

    const vector<vector<int>> EXPECTED = {
        {0, 3, 1, 6, 4, 5, 2, 7}, {0, 2, 1, 3, 4, 5, 6, 7},
        {3, 0, 7, 1, 2, 4, 5, 6}, {0, 4, 5, 7, 3, 1, 2, 6},
        {0, 5, 7, 4, 1, 2, 3, 6}, {3, 6, 2, 5, 1, 4, 0, 7},
        {5, 4, 3, 0, 1, 2, 7, 6}, {0, 1, 2, 3, 4, 5, 6, 7}};

    for (uint i = 0; i < INPUT.size(); ++i) {
        const vector<int> ACTUAL = Rank::sortIndexes(INPUT[i], true);
        EXPECT_EQ(EXPECTED[i], ACTUAL);
    }
}

TEST(rank, sortDistances) {
    const vector<vector<int>> INPUT = {
        {9, 4, 2, 5, 3, 3, 4, 2},  {10, 9, 10, 9, 9, 9, 9, 1},
        {8, 5, 4, 9, 3, 2, 1, 7},  {11, 3, 3, 4, 9, 8, 3, 5},
        {10, 7, 7, 7, 8, 9, 4, 9}, {1, 3, 4, 5, 3, 4, 5, 1},
        {3, 3, 2, 4, 8, 9, 1, 2},  {1, 1, 1, 1, 1, 1, 1, 1}};

    const vector<vector<int>> EXPECTED = {
        {0, 3, 1, 6, 4, 5, 2, 7}, {0, 2, 1, 3, 4, 5, 6, 7},
        {3, 0, 7, 1, 2, 4, 5, 6}, {0, 4, 5, 7, 3, 1, 2, 6},
        {0, 5, 7, 4, 1, 2, 3, 6}, {3, 6, 2, 5, 1, 4, 0, 7},
        {5, 4, 3, 0, 1, 2, 7, 6}, {0, 1, 2, 3, 4, 5, 6, 7}};

    for (uint i = 0; i < INPUT.size(); ++i) {
        const vector<int> ACTUAL = Rank::sortIndexes(INPUT[i], true);
        EXPECT_EQ(EXPECTED[i], ACTUAL);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

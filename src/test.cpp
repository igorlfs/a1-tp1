#include "map.hpp"
#include "rank.hpp"
#include <gtest/gtest.h>

using namespace std;
using matrix = vector<vector<int>>;

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
    const matrix EXPECTED{
        {8, 6, 13, 11, 10, 2, 1, 10}, {4, 6, 1, 3, 4, 10, 11, 2},
        {4, 6, 1, 3, 4, 10, 11, 2},   {10, 10, 7, 5, 4, 6, 7, 8},
        {8, 6, 11, 9, 8, 2, 3, 10},   {6, 8, 1, 1, 2, 12, 13, 4},
        {11, 9, 8, 6, 5, 5, 6, 9},    {9, 11, 6, 4, 3, 7, 8, 7}};

    const string INPUT =
        "*b*a*h*\n*----*2\n*----1c\nfg---*5\n*0---*d\n4----*e\n**637**";
    istringstream fakeInput(INPUT);

    constexpr int MAP_SIZE = 7;
    Map m(MAP_SIZE, MAP_SIZE, fakeInput);

    m.read();

    const matrix ACTUAL = m.getDistances();

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
    const matrix INPUT = {{9, 4, 2, 5, 3, 3, 4, 2},  {10, 9, 10, 9, 9, 9, 9, 1},
                          {8, 5, 4, 9, 3, 2, 1, 7},  {11, 3, 3, 4, 9, 8, 3, 5},
                          {10, 7, 7, 7, 8, 9, 4, 9}, {1, 3, 4, 5, 3, 4, 5, 1},
                          {3, 3, 2, 4, 8, 9, 1, 2},  {1, 1, 1, 1, 1, 1, 1, 1}};

    const matrix EXPECTED = {
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
    const matrix INPUT = {{9, 4, 2, 5, 3, 3, 4, 2},  {10, 9, 10, 9, 9, 9, 9, 1},
                          {8, 5, 4, 9, 3, 2, 1, 7},  {11, 3, 3, 4, 9, 8, 3, 5},
                          {10, 7, 7, 7, 8, 9, 4, 9}, {1, 3, 4, 5, 3, 4, 5, 1},
                          {3, 3, 2, 4, 8, 9, 1, 2},  {1, 1, 1, 1, 1, 1, 1, 1}};

    const matrix EXPECTED = {
        {0, 3, 1, 6, 4, 5, 2, 7}, {0, 2, 1, 3, 4, 5, 6, 7},
        {3, 0, 7, 1, 2, 4, 5, 6}, {0, 4, 5, 7, 3, 1, 2, 6},
        {0, 5, 7, 4, 1, 2, 3, 6}, {3, 6, 2, 5, 1, 4, 0, 7},
        {5, 4, 3, 0, 1, 2, 7, 6}, {0, 1, 2, 3, 4, 5, 6, 7}};

    for (uint i = 0; i < INPUT.size(); ++i) {
        const vector<int> ACTUAL = Rank::sortIndexes(INPUT[i], true);
        EXPECT_EQ(EXPECTED[i], ACTUAL);
    }
}

TEST(rank, invalidMatrices) {
    const matrix A(1);
    const matrix B(2);
    EXPECT_DEATH(
        Rank::galeShapley(A, B),
        "É necesário que as listas de preferência tenham tamanhos iguais.\n");
}

TEST(rank, galeShapley) {
    const vector<int> EXPECTED = {6, 0, 1, 5, 7, 3, 4, 2};

    const matrix PREF_MEN = {
        {6, 5, 1, 0, 4, 7, 3, 2}, {2, 7, 3, 0, 4, 1, 5, 6},
        {2, 7, 3, 0, 4, 1, 5, 6}, {4, 3, 5, 2, 6, 7, 0, 1},
        {5, 6, 1, 0, 4, 3, 7, 2}, {2, 3, 4, 7, 0, 1, 5, 6},
        {4, 5, 3, 6, 2, 1, 7, 0}, {4, 3, 2, 5, 7, 6, 0, 1}};
    const matrix PREF_WOMEN = {
        {0, 3, 1, 6, 4, 5, 2, 7}, {0, 2, 1, 3, 4, 5, 6, 7},
        {3, 0, 7, 1, 2, 4, 5, 6}, {0, 4, 5, 7, 3, 1, 2, 6},
        {0, 5, 7, 4, 1, 2, 3, 6}, {3, 6, 2, 5, 1, 4, 0, 7},
        {5, 4, 3, 0, 1, 2, 7, 6}, {0, 1, 2, 3, 4, 5, 6, 7}};
    const vector<int> ACTUAL = Rank::galeShapley(PREF_MEN, PREF_WOMEN);

    EXPECT_EQ(ACTUAL, EXPECTED);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

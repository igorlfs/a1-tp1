#include "map.hpp"
#include <gtest/gtest.h>

using namespace std;

TEST(map, readAndPrint) {
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

    m.read();
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

    const vector<vector<int>> ACTUAL = m.getDistancesBikesToUsers();

    EXPECT_EQ(EXPECTED, ACTUAL);
    EXPECT_EQ(EXPECTED, ACTUAL);
}

TEST(map, distanceImpossibleToCalculate) {
    const string INPUT = "a-*0\n--**\n*-**\nb*1*\n";

    istringstream fakeInput(INPUT);
    constexpr int MAP_SIZE = 4;
    Map m(MAP_SIZE, MAP_SIZE, fakeInput);

    m.read();

    ASSERT_DEATH(m.getDistancesBikesToUsers(),
                 "A distância de '0' para 'a' não pôde ser calculada");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

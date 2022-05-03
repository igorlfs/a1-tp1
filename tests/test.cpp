#include "map.hpp"
#include <gtest/gtest.h>

using namespace std;

int v = 2;

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

TEST(map, BFS) {
    const vector<int> EXPECTED_0{3, 6};
    const vector<int> EXPECTED_1{5, 2};

    const string INPUT = "a**0\n--**\n*-**\nb*1*\n";
    istringstream fakeInput(INPUT);
    constexpr int MAP_SIZE = 4;
    Map m(MAP_SIZE, MAP_SIZE, fakeInput);

    m.read();

    const vector<int> ACTUAL_0 = m.BFS(0, 3);
    const vector<int> ACTUAL_1 = m.BFS(3, 2);

    EXPECT_EQ(EXPECTED_0, ACTUAL_0);
    EXPECT_EQ(EXPECTED_1, ACTUAL_1);
}

TEST(map, impossibleToCalculateDistance) {
    const string INPUT = "a-*0\n--**\n*-**\nb*1*\n";

    istringstream fakeInput(INPUT);
    constexpr int MAP_SIZE = 4;
    Map m(MAP_SIZE, MAP_SIZE, fakeInput);

    m.read();

    ASSERT_DEATH(m.BFS(0, 3),
                 "A distância de '0' para 'a' não pôde ser calculada");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

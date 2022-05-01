# TODO: use g++
# Compiler
CXX = clang++
#CXX = g++

# Flags
# Compile, more warnings, C++17, enable debugging symbols and include path
CXXFLAGS = -c -Wall -Wextra -Wshadow -Wpedantic -std=c++17 -g -fstandalone-debug -Ilib
### g++ flags
#CXXFLAGS = -c -Wall -Wextra -Wshadow -Wpedantic -std=c++17 -g -Ilib

# Objects
BUILD = obj

# Binaries
BIN = tp1
TEST = test

# Source
CPP_SOURCE=$(filter-out src/main.cpp, $(wildcard src/*))
 
# Headers
HPP_SOURCE=$(wildcard lib/*)
 
# Objects
OBJ=$(subst .cpp,.o,$(subst src,$(BUILD),$(CPP_SOURCE)))
 
# Command used at clean target
RM = rm -rf
 
#
# Compilation and linking
#
all: obj $(BIN) tst

$(BIN): $(OBJ) ./$(BUILD)/main.o
	$(CXX) $^ -o $@
	@ echo ' '
 
./$(BUILD)/main.o: ./src/main.cpp $(HPP_SOURCE)
	$(CXX) $< $(CXXFLAGS) -o $@
	@ echo ' '

tst: obj $(TEST)

$(TEST): $(OBJ) ./$(BUILD)/test.o
	$(CXX) $^ -lgtest -o $@
	@ echo ' '
	./$(TEST)

./$(BUILD)/test.o: ./tests/test.cpp $(HPP_SOURCE)
	$(CXX) $< $(CXXFLAGS) -o $@
	@ echo ' '
 
./$(BUILD)/%.o: ./src/%.cpp ./lib/%.hpp
	$(CXX) $< $(CXXFLAGS) -o $@
	@ echo ' '
 
obj:
	@ mkdir -p $(BUILD)
 
clean:
	@ $(RM) ./$(BUILD)/*.o $(BIN) *~ $(TEST)
	@ rmdir $(BUILD)
 
.PHONY: all clean obj tst

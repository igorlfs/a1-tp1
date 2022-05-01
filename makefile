# TODO: use g++
# Compiler
CXX = clang++
#CXX = g++

# Flags
# Compile, more warnings, C++17, enable debugging symbols and include path
CXXFLAGS = -c -Wall -Wextra -Wshadow -Wpedantic -std=c++17 -g -fstandalone-debug -Ilib
### g++ flags
#CXXFLAGS = -c -Wall -Wextra -Wshadow -Wpedantic -std=c++17 -g -Ilib

BUILD = obj

BIN = tp1

# Source
CPP_SOURCE=$(wildcard src/*)
 
# Headers
HPP_SOURCE=$(wildcard lib/*)
 
# Objects
OBJ=$(subst .cpp,.o,$(subst src,$(BUILD),$(CPP_SOURCE)))
 
# Command used at clean target
RM = rm -rf
 
#
# Compilation and linking
#
all: obj $(BIN)
 
$(BIN): $(OBJ)
	$(CXX) $^ -o $@
	@ echo ' '
 
./$(BUILD)/main.o: ./src/main.cpp $(HPP_SOURCE)
	$(CXX) $< $(CXXFLAGS) -o $@
	@ echo ' '
 
./$(BUILD)/%.o: ./src/%.cpp ./lib/%.hpp
	$(CXX) $< $(CXXFLAGS) -o $@
	@ echo ' '
 
obj:
	@ mkdir -p $(BUILD)
 
clean:
	@ $(RM) ./$(BUILD)/*.o $(BIN) *~
	@ rmdir $(BUILD)
 
.PHONY: all clean obj

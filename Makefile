# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Directories
SRC_DIR = src
OBJ_DIR = build
BIN = liminal

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Default target
all: $(BIN)

# Build the binary
$(BIN): $(OBJS) main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile main separately
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile each object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(OBJ_DIR) *.o $(BIN)

# Run the game
run: all
	./$(BIN)

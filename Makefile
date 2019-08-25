CXX=g++
CXXFLAGS=-std=c++14 -pedantic -Wall -Wextra -Werror
LDFLAGS=
LDLIBS=
MKDIR_P=mkdir -p
RM_RF=rm -rf

SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

LIBRARY_NAME=mbs_analytics.dll

all: directories program
directories: $(OBJ_DIR) $(BIN_DIR)
program: $(BIN_DIR)/$(LIBRARY_NAME)
debug: CXXFLAGS += -DDEBUG -ggdb
debug: all
new: clean all
clean:
	$(RM_RF) $(BIN_DIR)
	$(RM_RF) $(OBJ_DIR)

$(OBJ_DIR):
	$(MKDIR_P) $(OBJ_DIR)
$(BIN_DIR):
	$(MKDIR_P) $(BIN_DIR)

$(BIN_DIR)/$(LIBRARY_NAME): $(OBJ_FILES)
	g++ -shared $(LDFLAGS) $(LDLIBS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CXXFLAGS) -c -o $@ $<

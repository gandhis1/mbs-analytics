ifndef CXX
	CXX=g++
endif
CXXFLAGS+=-std=c++14 -pedantic -Wall -Wextra -Werror -fPIC
LDFLAGS+=
LDLIBS+=
MKDIR_P=mkdir -p
RM_RF=rm -rf

SRC_DIR=.
OBJ_DIR=../../obj
BIN_DIR=../../bin

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

ifeq ($(OS),Windows_NT)
	LIBRARY_NAME=mbs_analytics.dll
else
	LIBRARY_NAME=mbs_analytics.so
endif

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
	$(CXX) -shared $(LDFLAGS) $(LDLIBS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

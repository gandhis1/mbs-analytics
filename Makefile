CXX=g++
CXXFLAGS=-std=c++14 -pedantic -Wall -Wextra -Werror
LDFLAGS=
LDLIBS=
RM=rm -f

SRC_DIR=src
BUILD_DIR=build
BIN_DIR=bin
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
TARGET_NAME=run_analytics.exe

all: $(BIN_DIR)/$(TARGET_NAME)

debug: CXXFLAGS += -DDEBUG -g
debug: all

new: clean all

clean:
	$(RM) $(BIN_DIR)/*.exe
	$(RM) $(BUILD_DIR)/*.o


$(BIN_DIR)/$(TARGET_NAME): $(OBJ_FILES)
	g++ $(LDFLAGS) $(LDLIBS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CXXFLAGS) -c -o $@ $<

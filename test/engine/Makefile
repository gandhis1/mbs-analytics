TEST_SRC_DIR=.
ENGINE_SRC_DIR=../../src/engine
INCLUDES=-I $(ENGINE_SRC_DIR)
OBJ_DIR=../../obj
BIN_DIR=../../bin

SRC_FILES := $(wildcard $(TEST_SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(TEST_SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES)) $(wildcard $(OBJ_DIR)/*.o)

ifeq ($(OS),Windows_NT)
	BINARY_NAME=test_mbs_analytics.exe
else
	BINARY_NAME=test_mbs_analytics
endif

all: $(OBJ_DIR) $(BIN_DIR) $(BIN_DIR)/$(BINARY_NAME)

$(OBJ_DIR):
	$(MKDIR_P) $(OBJ_DIR)
$(BIN_DIR):
	$(MKDIR_P) $(BIN_DIR)

$(BIN_DIR)/$(BINARY_NAME): $(OBJ_FILES)
	$(CXX) $(LDFLAGS) $(LDLIBS) -o $@ $^

$(OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

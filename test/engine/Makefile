include ../../Makefile.config
.DEFAULT_GOAL:=all
TEST_SRC_DIR=.
ENGINE_SRC_DIR=../../src/engine
INCLUDES=-I $(ENGINE_SRC_DIR)

SRC_FILES := $(wildcard $(TEST_SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(TEST_SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES)) $(wildcard $(OBJ_DIR)/*.o)


ifeq ($(OS),Windows_NT)
	BINARY_NAME=test_mbs_analytics.exe
else
	BINARY_NAME=test_mbs_analytics
endif

all: $(OBJ_DIR) $(BIN_DIR) $(BIN_DIR)/$(BINARY_NAME)

$(BIN_DIR)/$(BINARY_NAME): $(OBJ_FILES)
	$(CXX) $(LDFLAGS) $(LDLIBS) -o $@ $^

$(OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

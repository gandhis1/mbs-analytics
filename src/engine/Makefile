include ../../Makefile.config
.DEFAULT_GOAL:=all
SRC_DIR=.

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

ifeq ($(OS),Windows_NT)
	LIBRARY_NAME=mbs_analytics.dll
else
	LIBRARY_NAME=mbs_analytics.so
endif

all: $(OBJ_DIR) $(BIN_DIR) $(BIN_DIR)/$(LIBRARY_NAME)

$(BIN_DIR)/$(LIBRARY_NAME): $(OBJ_FILES)
	$(CXX) -shared $(LDFLAGS) $(LDLIBS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

ifndef CXX
	export CXX=g++
endif
export CXXFLAGS+=-std=c++14 -pedantic -Wall -Wextra -Werror -fPIC
export LDFLAGS+=
export LDLIBS+=
export MKDIR_P=mkdir -p
export RM_RF=rm -rf

all:
	make -C ./src/engine
	make -C ./test/engine
debug:
	make debug -C ./src/engine
	make -C ./test/engine
new:
	make new -C ./src/engine
	make -C ./test/engine
clean:
	make clean -C ./src/engine
	make -C ./test/engine

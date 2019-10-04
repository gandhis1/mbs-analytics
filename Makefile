include Makefile.config

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

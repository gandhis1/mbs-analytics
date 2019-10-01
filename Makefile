all:
	make all -C ./src/engine
	#make all -C ./test/engine
debug:
	make debug -C ./src/engine
new:
	make new -C ./src/engine
clean:
	make clean -C ./src/engine

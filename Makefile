# Makefile - Nick Stommel - Project 3

CCFLAGS = -Wall -ansi -ggdb
OBJ_FILES = Driver.o AVLNode.o AVLTree.o AVLForest.o
SUBMIT_DIR = /afs/umbc.edu/users/s/l/slupoli/pub/cs341/stommel1/proj3/src

# Makefile constants set to default input files, can be overridden
# by specifying values in command line, or changed here.
INPUT = input1.txt
RANGE = range1.txt

Driver.out: $(OBJ_FILES)
	g++ $(CCFLAGS) $(OBJ_FILES) -o Driver.out

# All dependencies reliably found using g++ -MM flag on .cpp file

Driver.o: Driver.cpp AVLTree.h AVLTreeBase.h AVLNode.h AVLNode.cpp AVLTree.cpp
	g++ $(CCFLAGS) -c Driver.cpp

AVLForest.o: AVLForest.cpp AVLForest.h AVLTree.h AVLTreeBase.h AVLNode.h AVLNode.cpp AVLTree.cpp
	g++ $(CCFLAGS) -c AVLForest.cpp

AVLTree.o: AVLTree.cpp AVLTree.h AVLTreeBase.h AVLNode.h AVLNode.cpp
	g++ $(CCFLAGS) -c AVLTree.cpp

AVLNode.o: AVLNode.cpp AVLNode.h
	g++ $(CCFLAGS) -c AVLNode.cpp

.PHONY: clean
clean:
	rm -f *~ *.o *.out

.PHONY: run
run: Driver.out
	./Driver.out $(INPUT) $(RANGE)

.PHONY: mem-check
mem-check: Driver.out
	valgrind ./Driver.out $(INPUT) $(RANGE) 

.PHONY: submit
submit:
	cp *.h *.cpp Makefile $(SUBMIT_DIR)

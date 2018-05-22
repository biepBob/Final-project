#Marjan Demuynck #Tycho Cools #Robbe Ceulemans #Yannick van den Steen

# Shell
SHELL = /bin/bash
# Compiler
COMPILER = g++ -g -std=c++11 -Wall -Wno-deprecated -O3 -DNDEBUG

CPPFLAGS = $(shell pkg-config --cflags opencv)
LDLIBS = $(shell pkg-config --libs opencv)
ROOT1 = $(shell root-config --cflags)
ROOT2 = $(shell root-config --libs)

.PHONY: all clean


all: main

main: main.o batch.o testimage.o propagateRoot.o
	$(COMPILER) main.o  batch.o testimage.o propagateRoot.o ${LDLIBS} ${ROOT2} -lTMVA ${CPPFLAGS} ${ROOT1}  -o main

main.o: main.cpp
	$(COMPILER) -c main.cpp ${ROOT2} -lTMVA ${ROOT1}

propagateinterface.o: propagateinterface.cpp propagateinterface.h propagate.h Network.h batch.h
	$(COMPILER) -c propagateinterface.cpp -o $@

propagateRoot.o: propagateRoot.cpp propagateRoot.h
	$(COMPILER) -c propagateRoot.cpp ${ROOT2} -lTMVA ${ROOT1}

batch.o: batch.cpp batch.h testimage.h
	$(COMPILER) -c batch.cpp ${LDLIBS} ${CPPFLAGS} -o $@

testimage.o: testimage.cpp testimage.h
	$(COMPILER) -c testimage.cpp ${LDLIBS} ${CPPFLAGS} -o $@

clean : 
	rm *.o 



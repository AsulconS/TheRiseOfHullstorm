CXX = g++

CXX_FLAGS 	= -std=c++11
OBJECTS 	= main.o
INCLUDE 	= -Iinclude/

C_OS	:=
ifeq ($(OS),Windows_NT)
	C_OS	+= Windows
else
	C_OS	+= Linux
endif

all: os build trash

os:
	@echo $(C_OS)

build: $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $(OBJECTS) $(INCLUDE) -o main

main.o: main.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -c main.cpp

trash:
	rm -rf *.o

clean:
	rm -rf *.o main.exe

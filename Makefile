CC 	= gcc
CXX = g++

CXX_FLAGS 	= -std=c++11
INCLUDE 	= -Iinclude/
OBJECTS 	= main.o glad.o

C_OS		:=
LIBS		:=
ifeq ($(OS),Windows_NT)
	C_OS += Windows
	LIBS += -lglfw3 -lopengl32 -lglu32 -lgdi32 -luser32 -lkernel32 -lassimp
else
	C_OS += Linux
	LIBS += -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lassimp
endif

all: os build trash

os:
	@echo $(C_OS)

build: $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $(OBJECTS) $(INCLUDE) $(LIBS) -o main

main.o: main.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -c main.cpp

glad.o: glad.c
	$(CC) -c glad.c

trash:
	rm -rf *.o

clean:
	rm -rf *.o main.exe

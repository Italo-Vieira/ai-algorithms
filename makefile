IDir = include
ODir = obj
BDir = bin
SRCDir = src
Flags = -fopenmp -I\$(IDir)
EXE = NQueens
OBJ = $(SRCDir)/SearchAlgorithms.cpp $(SRCDir)/Path.cpp
INC = $(IDir)/SearchAlgorithms.h $(IDir)/Path.h $(IDir)/State.h

all: nqueens missandcann sin_nqueens sin_missandcann

nqueens: $(ODir)/nqueens

missandcann: $(ODir)/missandcann;

sin_nqueens: $(ODir)/sin_nqueens

sin_missandcann: $(ODir)/sin_missandcann

$(ODir)/nqueens:  $(INC) $(OBJ) $(SRCDir)/NQueens.cpp
	g++ $(Flags) -o $@ $(OBJ) $(SRCDir)/NQueens.cpp

$(ODir)/sin_nqueens:  $(INC) $(OBJ) $(SRCDir)/NQueens.cpp
	g++ -I\$(IDir) -o $@ $(OBJ) $(SRCDir)/NQueens.cpp

$(ODir)/missandcann:  $(INC) $(OBJ) $(SRCDir)/MissionariesAndCannibals.cpp
	g++ -g $(Flags) -o $@ $(OBJ) $(SRCDir)/MissionariesAndCannibals.cpp

$(ODir)/sin_missandcann:  $(INC) $(OBJ) $(SRCDir)/MissionariesAndCannibals.cpp
	g++ -I\$(IDir) -o $@ $(OBJ) $(SRCDir)/MissionariesAndCannibals.cpp

clean:
	rm -r obj/*

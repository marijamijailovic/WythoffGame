PROGRAM = WythoffGame
CXX = g++
CXXFLAGS = -Wall -g
OBJ = main.o	\
	game.o	\
	game_helper.o	\
	arithmetic.o	\
	recursive_and_algebraic.o	\
	recursive.o	\
	algebraic.o \
	measure_time.o

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(PROGRAM): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

.PHONY: clean

clean:
	rm -rf $(PROGRAM)
	rm -rf *.o
	rm -rf *~

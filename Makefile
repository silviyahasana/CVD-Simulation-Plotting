BIN_DIR= .
CC = g++
CFLAGS = -std=c++11 $(shell pkg-config --cflags opencv4)
LIBS = $(shell pkg-config --libs opencv4)

all: $(BIN_DIR)/chromaticity $(BIN_DIR)/simulation $(BIN_DIR)/plot

$(BIN_DIR)/chromaticity: chromaticity.o
	${CC} -o $(BIN_DIR)/chromaticity chromaticity.o $(LIBS)

$(BIN_DIR)/simulation: simulation.o
	${CC} -o $(BIN_DIR)/simulation simulation.o $(LIBS)

$(BIN_DIR)/plot: plot.o
	${CC} -o $(BIN_DIR)/plot plot.o $(LIBS)

chromaticity.o: chromaticity.cpp
	${CC} $(CFLAGS) -c chromaticity.cpp

simulation.o: simulation.cpp
	${CC} $(CFLAGS) -c simulation.cpp

plot.o: plot.cpp
	${CC} $(CFLAGS) -c plot.cpp

clean:
	rm -f *.o
	rm -f $(BIN_DIR)/chromaticity
	rm -f $(BIN_DIR)/simulation
	rm -f $(BIN_DIR)/plot

allclean:
	rm -f *.o
	rm -f $(BIN_DIR)/chromaticity
	rm -f $(BIN_DIR)/simulation
	rm -f $(BIN_DIR)/plot
	rm -f Makefile
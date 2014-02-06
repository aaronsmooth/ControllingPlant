CC = gcc
DEBUG = -g
INCLUDE = -I/usr/local/include
CFLAGS = $(DEBUG) -Wall $(INCLUDE) -Winline -pipe
LDFLAGS = -L/usr/local/lib
LDLIBS = -lwiringPi -lpthread -lm
SRC = plantSimulator.c
PLANTOB = /home/pi/ControllingPlant/plantSim.o
OBJ = $(SRC:.c=.o)
BINS = $(SRC:.c=)

run: sim
	./sim

sim: plantSimulator.o
	@echo [link]
	@$(CC) -o $@ plantSimulaor.o $(PLANTOB) $(LDFLAGS) $(LDLIBS)
	
.c.o:
	@echo [CC] $<
	@$(CC) -c $(CFLAGS) $< -o $@

clean: 
	rm -f $(OBJ) *~ core tags $(BINS)

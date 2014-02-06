CC = gcc
DEBUG = -g
INCLUDE = -I/usr/local/include
CFLAGS = $(DEBUG) -Wall $(INCLUDE) -Winline -pipe
LDFLAGS = -L/usr/local/lib
LDLIBS = -lwiringPi -lpthread -lm
SRC = plantSimulator.c, plantController.c
OBJ = $(SRC:.c=.o)
BINS = $(SRC:.c=)

run:
	@echo help
	@echo 1. type [make sim] to build simulator. 
	@echo 2. type [make control] to build controller.
	@echo 3. type [make clean] to clean object and executive files.

sim: plantSimulator
	./plantSimulator

control: plantController
	./plantController

plantSimulator: plantSimulator.o
	@echo [link]
	@$(CC) -o $@ plantSimulator.o plantSim.o $(LDFLAGS) $(LDLIBS)

plantController: plantController.o
	@echo [link]
	@$(CC) -o $@ plantController.o $(LDFLAGS) $(LDLIBS)

.c.o:
	@echo [CC] $<
	@$(CC) -c $(CFLAGS) $< -o $@

clean: 
	rm plantController; rm plantSimulator; rm -f $(OBJ) *~ core tags $(BINS)

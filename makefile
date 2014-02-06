CC = gcc
DEBUG = -g
INCLUDE = -I/usr/local/include
CFLAGS = $(DEBUG) -Wall $(INCLUDE) -Winline -pipe
LDFLAGS = -L/usr/local/lib
LDLIBS = -lwiringPi -lpthread -lm
SRC = plantSimulator.c
OBJ = $(SRC:.c=.o)
BINS = $(SRC:.c=)

run: main
	./main -d 0 

debug: main
	./main -d 1

main: plantSimulator.o
	@echo [link]
	@$(CC) -o $@ plantSimulaor.o $(LDFLAGS) $(LDLIBS)
	
.c.o:
	@echo [CC] $<
	@$(CC) -c $(CFLAGS) $< -o $@

clean: 
	rm -f $(OBJ) *~ core tags $(BINS)

tags: $(SRC)
	@echo [ctags]
	@ctags $(SRC)

depend: makedepend -Y $(SRC)

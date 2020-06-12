PROGRAM = drumHero
CC      = gcc
CFLAGS  = -g -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): main.o image.o okruzenje.o funkcionalnosti.o
	$(CC) $(LDFLAGS) -o $(PROGRAM) main.o image.o okruzenje.o funkcionalnosti.o $(LDLIBS)
	
image.o: image.c image.h
	$(CC) $(LDFLAGS) $(CFLAGS) -c image.c -o image.o
	
okruzenje.o: okruzenje.c okruzenje.h
	$(CC) $(LDFLAGS) $(CFLAGS) -c okruzenje.c -o okruzenje.o
	
funkcionalnosti.o: funkcionalnosti.c funkcionalnosti.h
	$(CC) $(LDFLAGS) $(CFLAGS) -c funkcionalnosti.c -o funkcionalnosti.o
	
main.o: main.c  image.h okruzenje.h funkcionalnosti.h
	$(CC) $(LDFLAGS) $(CFLAGS) -c main.c -o main.o

.PHONY: beauty clean dist

beauty:
	-indent -kr -nut $(PROGRAM).c
	-rm *~ *BAK

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)

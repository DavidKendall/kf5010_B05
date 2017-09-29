# for Linux use
#LIBS=-lncursesw

# For Mac/OSX use
LIBS= -lcurses

# flags for compiler and linker
CFLAGS= -std=c99
LDFLAGS= -L .

sample: sample.c lcd.h liblcd.a
	cc $(CFLAGS)  -o sample sample.c $(LDFLAGS) -llcd $(LIBS)

liblcd.a: lcd.o lcd.h
	ar rc liblcd.a lcd.o
	ranlib liblcd.a

.PHONY: man
man: lcd.3
	man ./lcd.3

.PHONY: clean
clean:
	rm -f sample
	rm -f lcd.o
	rm -f liblcd.a

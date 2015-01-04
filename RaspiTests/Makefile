DEBUG	= -O3
CC		= gcc
INCLUDE	= -I/usr/local/include -I../libraries/LwTx/
CFLAGS	= $(DEBUG) -Wall $(INCLUDE) -Winline -pipe

LDFLAGS	= -L/usr/local/lib
LDLIBS  = -lwiringPi

.PHONY: all clean

all: LwTxTest

clean:
	-rm -f *.o

LwTxTest: LwTxTest.o LwTx.o
	$(CC) -o LwTxTest LwTxTest.o LwTx.o $(LDFLAGS) $(LDLIBS) $(INCLUDE)

LwTx.o: ../libraries/LwTx/LwTx.cpp ../libraries/LwTx/LwTx.h
	$(CC) $(CFLAGS) -c ../libraries/LwTx/LwTx.cpp


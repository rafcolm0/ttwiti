# Makefile for tweeti.  Libs: libappindicator0.1, twitcurl-master
#g++ tweti.cpp `pkg-config --cflags gtk+-2.0` -I/usr/include/libappindicator-0.1/  -o example `pkg-config --libs gtk+-2.0` -L/usr/lib -lappindicator

CC=g++
CFLAGS=-Wall -c
SETTINGS_LIBS=`pkg-config --libs libconfig`
DEPS= `pkg-config --cflags gtk+-2.0` -I/usr/include/libappindicator-0.1/ `pkg-config --libs gtk+-2.0` -L/usr/lib -lappindicator

all: twiti

twiti: twiti.o settings.o
	$(CC) twiti.o settings.o -o twiti $(DEPS)

twiti.o: twiti.cpp
	$(CC) $(CFLAGS) twiti.cpp $(DEPS)

settings.o: settings.cpp
	$(CC) $(CFLAGS) settings.cpp

clean:
	$(RM) twiti twiti.o settings.o


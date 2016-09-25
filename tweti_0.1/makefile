# Makefile for tweeti.  Libs: libappindicator0.1, twitcurl-master

CC=g++
#DEBUG ON
CFLAGS=-g -Wall -c
SETTINGS_LIBS=`pkg-config --libs libconfig`
DEPS= `pkg-config --cflags gtk+-2.0` -I/usr/include/libappindicator-0.1/ `pkg-config --libs gtk+-2.0 libnotify` -L/usr/lib -lappindicator

all: twiti

twiti: twiti.o settings.o account.o
	$(CC) twiti.o settings.o account.o -o twiti $(DEPS)

twiti.o: twiti.cpp
	$(CC) $(CFLAGS) twiti.cpp $(DEPS)

settings.o: settings.cpp
	$(CC) $(CFLAGS) settings.cpp

account.o: account.cpp account.h
	$(CC) $(CFLAGS) account.cpp account.h

clean:
	$(RM) twiti twiti.o settings.o


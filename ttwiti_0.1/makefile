# Makefile for tweeti.  Libs: libappindicator0.1, twitcurl-master

CC=g++
#DEBUG ON
CFLAGS=-g -Wall -c
DEPS_ttwiti= `pkg-config --cflags gtk+-2.0` -I/usr/include/libappindicator-0.1/ `pkg-config --libs gtk+-2.0 libnotify` -L/usr/lib -lappindicator

DEPS_twitter_man= -ltwitcurl

all: ttwiti

ttwiti: ttwiti.o settings.o twitter_man.o
	$(CC) ttwiti.o settings.o twitter_man.o -o ttwiti $(DEPS_ttwiti) $(DEPS_twitter_man)

ttwiti.o: ttwiti.cpp
	$(CC) $(CFLAGS) ttwiti.cpp $(DEPS_ttwiti)

settings.o: settings.cpp settings.h
	$(CC) $(CFLAGS) settings.cpp settings.h

twitter_man.o: twitter_man.cpp twitter_man.h 
	$(CC) $(CFLAGS) twitter_man.cpp twitter_man.h $(DEPS_twitter_man)

clean:
	$(RM) ttwiti *.o *.gch


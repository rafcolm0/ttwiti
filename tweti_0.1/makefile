# Makefile for tweeti.  Libs: libappindicator0.1, twitcurl-master
#g++ tweti.cpp `pkg-config --cflags gtk+-2.0` -I/usr/include/libappindicator-0.1/  -o example `pkg-config --libs gtk+-2.0` -L/usr/lib -lappindicator

CC=g++
CFLAGS=-g -Wall

DEPS= `pkg-config --cflags gtk+-2.0` -I/usr/include/libappindicator-0.1/ `pkg-config --libs gtk+-2.0` -L/usr/lib -lappindicator

TARGET = tweti

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(TARGET).cpp -o $(TARGET) $(CFLAGS) $(DEPS) 

clean:
	$(RM) $(TARGET)


OBJS = Extractor.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

INCLUDES = -I/usr/include


Extractor : $(OBJS)
	$(CC) $(INCLUDES) $(LFLAGS)  $(OBJS) -o Extractor

Extractor.o : zipcode.h
	$(CC) $(INCLUDES) $(CFLAGS) Extractor.cpp

